#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "MyReadKey.h"
using namespace std;
static struct termios stored_setting;


int rk_readkey (enum keys * key)
{
    char buf[15];
    int size;
    if (tcgetattr(0, &stored_setting) != 0)return -1;
    if (rk_mytermregime(0, 0, 1, 0, 1) != 0)return -1;
    size = read(0, buf, 15);
    if(size < 0)
    { 
        return -1;
    }
    buf[size] = '\0';
    cout<<buf<<endl;
    if(strcmp(buf,"l") == 0)
    {
        *key = l;
    }
    else
    {
        if(strcmp(buf,"s") == 0)
        {
            *key = s;
        }
        if(strcmp(buf,"r") == 0)
        {
            *key = r;
        }
        if(strcmp(buf,"t") == 0)
        {
            *key = t;
        }
        if(strcmp(buf,"i") == 0)
        {
            *key = i;
        }
        if(strcmp(buf,"\E[15~") == 0)
        {
            *key = f5;
        }
        if(strcmp(buf,"\E[17~") == 0)
        {
            *key = f6;
        }
        if(strcmp(buf,"\n") == 0)
        {
            *key = enter;
        }
        if (strcmp(buf, "\E[A") == 0)
        {
                *key = up;
        }
        if (strcmp(buf, "\E[B") == 0)
        {
            *key = down;
        }
        if (strcmp(buf, "\E[C") == 0)
        {
            *key = rght;
        }
        if (strcmp(buf, "\E[D") == 0)
        {
            *key = lft;
        }
    }
    if (tcsetattr(0, TCSANOW, &stored_setting) != 0)
        return -1;
    return 0;
}

int rk_mytermsave (void)
{
    tcgetattr(0,&stored_setting);
    return 0;
}

int rk_mytermrestore (void)
{
    tcsetattr(0,TCSANOW, &stored_setting);
    return 0;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
        struct termios new_settings;
            tcgetattr(0,&stored_setting);
            new_settings = stored_setting;
            if(regime==0)
            {
                new_settings.c_lflag &=(~ICANON);
            }
            else
            {
                if(regime==1)
                {
                    new_settings.c_lflag |= ICANON;
                }
                return -1;
            }
            if(regime==0)
            {
            if(echo==1)
                new_settings.c_lflag |= ECHO;
            else
                new_settings.c_lflag &= (~ECHO);
            if(sigint==1)
                new_settings.c_lflag |= ISIG;
            else
                new_settings.c_lflag &= (~ISIG);
                new_settings.c_cc[VTIME] = vtime; 
                new_settings.c_cc[VMIN] = vmin;
            }
         tcsetattr(0,TCSANOW,&new_settings);
         return 0;
}
