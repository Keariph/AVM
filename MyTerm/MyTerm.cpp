#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include "MyTerm.h"
using namespace std;
extern int mt_clrscr (void)
{
    printf("\E[H\e[2J");
    return 0;
}

 int mt_gotoXY (int x, int y)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(x > w.ws_row && y > w.ws_col)
    {
        cout<<"Неверные значения\n";
        return -1;
    }
    else
    {
    printf("\E[%d;%dH", y, x);
    return 0;
    }
}

extern int mt_getscreensize (int * rows, int * cols)
{
    struct winsize ws;
    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws))
    {
        fprintf (stderr, "Ошибка получения размера экрана.\n");
        return -1;
    } 
    else 
    {
        printf ("Получен размер экрана.\n");
        printf ("lines %d\n", ws.ws_row);
        printf ("columns %d\n", ws.ws_col);
        ws.ws_row = *rows;
        ws.ws_col = *cols; 
    }
}

int mt_setfgcolor (enum colors a)
{
    if(a > 18 || a < 0)
    {
        cout<<"Неверное значение\n";
        return -1;
    }
    else
    {
        if(a >= 10)
        {
            if(a == 18)
            {
                printf("\E[%dm",0);
            return 0;
            }
            else
            {
                printf("\E[1;%dm",a+20);
                return 0;
            }
        }
        else
        {
            printf("\E[%dm",a+30);
            return 0;
        }
    }
}

extern int mt_setbgcolor (enum colors a)
{
    if(a > 18 || a < 0)
    {
        cout<<"Неверное значение\n";
        return -1;
    }
    else
    {
        if(a>=10)
        {
            if(a == 18)
            {
                printf("\E[%dm",0);
            return 0;
            }
            else
            {
                printf("\E[1;%dm",a+20);
                return 0;
            }
        }
        else
        {
            printf("\E[%dm",a+40);
            return 0;
        }
    }
}