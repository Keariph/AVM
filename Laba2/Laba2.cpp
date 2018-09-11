#include <iostream>
#include "../Library/MySimpleComputer/MySimpleComputer.h"
#include "../Library/MyTerm/MyTerm.h"
void Simple_computer();
using namespace std;
int main()
{
    int a;
    int x, y;
    int c;
    while(true)
    {
    cout<<"Enter a operation\n";
    cout<<"0. All\n1. Clear\n2. Move the cursor\n3. Background fills\n4. Text fills\n5. Exit\n";
    cin>>a;
    mt_getscreensize(&x,&y);
    switch(a)
    {
        case 0:
        Simple_computer();
        break;
        case 1:
        mt_clrscr ();
        break;
        case 2:
        cout<<"Enter a coordinates\n";
        cin>>x>>y;
        mt_gotoXY (x, y);
        break;
        case 3:
        cout<<"Enter a color\n";
        //cin>>c;
        mt_setbgcolor (RED);
        break;
        case 4:
        cout<<"Enter a color\n";
        //cin>>c;
        mt_setfgcolor (BLUE);
        break;
        case 5:
        exit(0);
        break;
        default:
        cout<<"Incorect a enter\n";
    }
    }
}

void Simple_computer()
{
    int cell = 0;
    int reg;
    mt_clrscr();
    sc_memoryInit();
    sc_memorySet (5, 5);//Установка значений памяти
    //sc_memorySave ("memory.txt");//Запись в файл
    for(int i = 0; i<10;i++)
    {
        for(int j = 0; j<10;j++)
        {
            sc_memoryGet(1, &cell);
            cout<<" ";
            //mt_gotoXY(i+6, j+6);
        }
    }
   
    sc_regInit ();//Зануление регистра
    //sc_regGet (int reg, int * value);
}