#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "MyBigChars.h"
//#include "../MyTerm/MyTerm.h"
//#include "../MySimpleComputer/MySimpleComputer.h"
using namespace std;
int bc_printA (char * str)//Вывод символов
{   
        cout<<"\E(0"<< *str <<"\E(B";
        return 0;
}

extern int bc_box(int x1, int y1, int x2, int y2)//Вывод рамки
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(x2 > w.ws_row && y2 > w.ws_col)
    {
        cout<<"Incorrect enter size\n";
        return -1;
    }
    else
    {
        for(int i = y1; i< y2; i++)
        {
            for(int j = x1; j < x2; j ++)
            {
                mt_gotoXY(i, j);
                if(i == y1 && j == x1)
                {
                    bc_printA(&CorUpRh);
                }
                if(i == y1 && j == x2 -1)
                {
                    bc_printA(&CorDwRh);
                }
                if(i == y2 - 1 && j == x1)
                {
                    bc_printA(&CorUpLf);
                }
                if(i == y2 - 1 && j == x2 - 1)
                {
                    bc_printA(&CorDwLf);
                }
                if(i == y1 || i == y2 - 1)
                {
                    if(j != x1 && j != x2 - 1)
                    {
                        bc_printA(&vertical);
                    }
                }
                if(i != y1 && i != y2 - 1)
                {
                    if(j == x1 || j == x2 - 1)
                    {
                        bc_printA(&horizontal);
                    }
                }   
            }
            cout<<endl;
        }
        return 0;
    }
}

int bc_printbigchar (long int mas[2], int x, int y, enum colors a, enum colors b)//Вывод БЧ
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(x > w.ws_row && y > w.ws_col)
    {
        cout<<"Incorrect enter size\n";
        return -1;
    }
    else
    {
    mt_setbgcolor(a);
    mt_setfgcolor(b);
    mt_gotoXY(x, y);
    for(int k = 0; k <2; k++)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j <8;j++)
            {
                mt_gotoXY(x+j, y+i);
                if(((mas[k]>>(j +(i*8)))&1) == 1)
                {bc_printA(&block);}
                else {bc_printA(&gap);}
            }
        }
        y+=4;
    }
    mt_setbgcolor(NOT);
    mt_setfgcolor(NOT);
    return 0;
    }
}

int bc_getbigcharpos (long int * big, int x, int y, long int *value)//Получение значения ячейки БЧ
{
    int n = ((8*x)+y);
    if(n > 64)
    {
        cout<<"Incorrect enter a coordinates\n";
        return -1;
    }
    else
    {
        *value = (*big>>n)&1;
        cout<<*value;
        return 0;
    }
}
int bc_setbigcharpos (long int * big, int x, int y, int value)//Установка значения ячейки БЧ
{
    int n = ((8*x)+y);
    if(n>64)
    {
        cout<<"Incorrect enter a coordinates\n";
        return -1;  
    }
    else
    {
        if(n <32)
        {
            n = n/2;
        }
        *big = (*big<<n)|value;
        bc_printbigchar(big, 2, 2, BLACK, LGRAY);
        return 0;
    }
}
int bc_bigcharwrite (int fd,long int * big, int count)//Запись в файл
{
    //FILE * fm;
    if(fd == -1)
    {
        cout<<"File not open\n";
        return -1;
    }
    else
    {
        /*fm = fopen("filename.txt", "r");
        if(ftell(fm) == count)
        {*/
        bc_printbigchar(big,5,5,GREEN,BLACK);
            write(fd, big,4*count);
            return 0;
        //}
    }
}
int bc_bigcharread (int fd, long int * big, int need_count, int * count)//Чтение с файла
{
    //FILE *fm = fopen("filename.txt", "r");
    if(fd == -1)
    {
        *count = 0;
        cout << "File not open\n Count = "<< *count << endl;
        return -1;
    }
    else
    {

        /*count = ftell(fm);
        if(*count == ((need_count-1)*8))
        {*/
         *count=read(fd, big, 4*need_count);
        //}
        cout << "Count = " << *count << endl;
        bc_printbigchar(big,5,5,GREEN, BLACK);
        return 0;
    }
}
