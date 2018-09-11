#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <cmath>
#include <iomanip>
#include <signal.h>
#include <unistd.h>
#include "../Library/MySimpleComputer/MySimpleComputer.h"
#include "../Library/MyTerm/MyTerm.h"
#include "../Library/MyReadKey/MyReadKey.h"
#include "../Library/MyBigChars/MyBigChars.h"
using namespace std;
struct itimerval nval, oval;
int accumulator = 0, x = 0, y = 0;
void Memory();
void Print();
void Keys();
void Signal();
void Flags();
void Timer();
void Chars(int x, int y); 
void signalhandler (int signo);
void handler (int signo);
int Operation(int command, int operand);
int main()
{
    signal (SIGALRM, signalhandler);
    signal (SIGUSR1, handler);
    nval.it_interval.tv_sec = 1;
    nval.it_value.tv_sec = 1;
    sc_memoryInit();
    mt_clrscr();
    Memory();
    Print();
    Keys();
    mt_gotoXY(3,27);
    return 0;
}
 void Memory()
 {
     int value, command, operand;
     mt_clrscr();
     bc_box(3, 3, 15, 64);
     for(int i = 0; i<10;i++)
     {
         for(int j = 0; j <10; j++)
         {
             mt_gotoXY(4 + (6*i), 4 + j);
             sc_memoryGet(i+(j*10),&value);
             sc_commandDecode(value, &command, &operand);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
         }
     }
     mt_gotoXY(32,3);
     cout<<"Memory";
     mt_gotoXY(3, 27);
 }
  void Print()
  {
      int value, command, operand;
       bc_box(3, 64, 6, 84);//accumulator
       mt_gotoXY(68,3);
       cout<<"accumulator";
       mt_gotoXY(71,4);
       if(accumulator>=0)
       printf("+%04d", accumulator);
       if(accumulator<0)
       printf("%05d", accumulator);
       bc_box(6, 64, 9, 84);//instructionCounter
       mt_gotoXY(65,6);
       cout<<"instructionCounter";
       bc_box(9, 64, 12, 84);//operation
       mt_gotoXY(69,9);
       cout<<"operation";
       bc_box(12, 64, 15, 84);//flags
       mt_gotoXY(71,12);
       cout<<"flags";
       bc_box(15, 3, 25, 55);//chars
       bc_box(15, 55, 25, 84);//Keys
       mt_gotoXY(67,15);
       cout<<"Keys:";
       mt_gotoXY(56,16);
       cout<<"l - load";
       mt_gotoXY(56,17);
       cout<<"s - save";
       mt_gotoXY(56,18);
       cout<<"r - run";
       mt_gotoXY(56,19);
       cout<<"t - step";
       mt_gotoXY(56,20);
       cout<<"i - reset";
       mt_gotoXY(56,21);
       cout<<"F5 - accumulator";
       mt_gotoXY(56,22);
       cout<<"F6 - instructionCounter";   
       mt_gotoXY(4,4);
       if(x == 0 && y == 0)       
       mt_gotoXY(4, 4);
    if(x<10 && y < 10 && x >=0 && y >= 0)
    {
     bc_printbigchar(masP,4,16,NOT, WHITE);
     mt_setbgcolor(RED);
     mt_gotoXY(4+(x*6),4+y);
     sc_memoryGet(x+(y*10),&value);
    //  printf("+%04X", value);
    sc_commandDecode(value,&command, &operand);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
     mt_setbgcolor(NOT);
     mt_gotoXY(71,7);
     printf("+%04d", x + (y * 10));
     sc_commandDecode(value,&command, &operand);
     mt_gotoXY(71, 10);
     printf("%02d : %02d", command, operand);
       Chars(x,y);
       Flags();
    }
    else 
    {
        if(x == -1)x++;
        if(x == 10)x--;
        if(y == -1)y++;
        if(y == 10)y--;
        mt_setbgcolor(RED);
        mt_gotoXY(4+(x*6),4+y);
        sc_memoryGet(x+(y*10),&value);
        // printf("+%04X", value);
        sc_commandDecode(value,&command, &operand);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
        mt_setbgcolor(NOT);
        mt_gotoXY(3, 28);
        cout<<"going abroad";
        sc_regSet(EXIT, 1);
        Flags();
    }
    mt_gotoXY(3,27);
    //Keys();
  }
  void Chars(int x, int y)
  {
      int value;
      int reg;
      int buf;
      sc_memoryGet(x+(y*10),&value);
      for(int i = 4; i >= 0; i--)
      {
         if(i == 0)
            {
                bc_printbigchar(masP,4 +(i*9), 16, NOT, WHITE);
                mt_gotoXY(3,27);
                continue;
            }
            else
            {
                buf = value /16;
                if(i!=1){reg = value - buf*16;}
                else{reg = value;} 
                if(reg == 0){bc_printbigchar(mas0,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 1){bc_printbigchar(mas1,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 2){bc_printbigchar(mas2,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 3){bc_printbigchar(mas3,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 4){bc_printbigchar(mas4,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 5){bc_printbigchar(mas5,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 6){bc_printbigchar(mas6,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 7){bc_printbigchar(mas7,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 8){bc_printbigchar(mas8,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 9){bc_printbigchar(mas9,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 10){bc_printbigchar(masA,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 11){bc_printbigchar(masB,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 12){bc_printbigchar(masC,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 13){bc_printbigchar(masD,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 14){bc_printbigchar(masE,4 +(i*9), 16, NOT, WHITE);}
                if(reg == 15){bc_printbigchar(masF,4 +(i*9), 16, NOT, WHITE);}
                value = value/16;
                mt_gotoXY(3, 27);
            }
      }
      mt_gotoXY(3, 27);
  }
  void Keys()
  {
      enum keys key;
      int value, command, operand, input;
      char plus;
      int address;
      while(true)
      {
          rk_readkey(&key);
          if(x < 10 && y < 10 && x >= 0 && y >= 0)
          {
                mt_setbgcolor(NOT);
                mt_gotoXY(4 + (x * 6), 4 + y);
                sc_memoryGet(x+(y*10), &value);
                // printf("+%04X", value);
                sc_commandDecode(value,&command, &operand);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
                Flags();
                sc_regInit();
                mt_gotoXY(3, 27);
                //cout<<"                            ";
                if(key == up){y--;}//Вверх
                if(key == down){y++;}//Вниз
                if(key == lft){x--;}//Влево
                if(key == rght){x++;}//Вправо
          }
              if(x < 10 && y < 10 && x >= 0 && y >= 0)
              {
                mt_setbgcolor(RED);
                mt_gotoXY(4 + (x * 6), 4 + y);
                sc_memoryGet(x + (y * 10), &value);
                // printf("+%04X", value);
                sc_commandDecode(value,&command, &operand);
                if(value/100 == 0 && value%100 != 0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
                mt_setbgcolor(NOT);
                mt_gotoXY(71, 7);
                printf("+%04d", x + (y * 10));
                sc_commandDecode(value, &command, &operand);
                mt_gotoXY(71, 10);
                printf("%02d : %02d", command, operand);
                Chars(x, y);
              }
              else 
              {
                sc_regSet(EXIT, 1);
                Flags();
                if(x == -1)x++;
                if(x == 10)x--;
                if(y == -1)y++;
                if(y == 10)y--;
                mt_setbgcolor(RED);
                mt_gotoXY(4+(x*6),4+y);
                sc_memoryGet(x+(y*10),&value);
                // printf("+%04X", value);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("-%04d", value);
             }
             else
             {
                 printf("+%04d", value);
             }
                mt_setbgcolor(NOT);
                mt_gotoXY(3, 27);
                cout<<"going abroad";
              }
              if(key == s)
              {
                  sc_memorySave("Memory.txt");
                  mt_gotoXY(3,27);
                  cout<<"Saving successfully";
              }
              if(key == l)
          {
              sc_memoryLoad("Memory.txt");
              mt_gotoXY(3,27);
              Memory();
              Print();
              cout<<"Loading is complete";
          }
          if(key == r)//Ran
          {   
                Timer();
          }
          if(key == t)
          {
              sc_memoryGet(x + (y*10), &value);
              sc_commandDecode(value, &command, &operand);
              if(Operation(command,operand) == -1)continue;
          }
          if(key == i)//Reset
          {
              raise(SIGUSR1);
          }
          if(key == f5)//accumulator
          {
              mt_gotoXY(3, 27);
              cout<<"Output\\input: ";
              cin>>accumulator;
              mt_gotoXY(71,4);
              if(accumulator >=0)
              printf("+%04d", accumulator);
              if(accumulator <0)
              printf("%05d", accumulator);
              mt_gotoXY(3,27);
          }
          if(key == f6)//int instructionCounter
          {
              mt_gotoXY(3,27);
              cout<<"Output\\input: ";
              cin>>address;
              mt_gotoXY(4+(x*6),4+y);
              sc_memoryGet(x+(y*10),&value);
              mt_setbgcolor(NOT);
              //("+%04X", value);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("+%04d", value);
             }
             else
             {
                 printf("-%04d", value);
             }
              x = address%10;
              y = address/10;
              mt_gotoXY(71,7);
              printf("+%04d", address);
              mt_gotoXY(4+(x*6),4+y);
              sc_memoryGet(address,&value);
              mt_setbgcolor(RED);
              //printf("+%04X", value);
              sc_commandDecode(value,&command, &operand);
              if(value/100<10 && value/100 > 76 && value/100>11 && value/100 < 21 && value/100>20 && value/100<30 && value/100 >33 && value/100<40 && value%100 !=0)
             {                          
                 printf("+%04d", value);
             }
             else
             {
                 printf("%04d", value);
             }
              mt_setbgcolor(NOT);
              Chars(x,y);
          }
          if(key == enter)
          {
              mt_gotoXY(3, 27);
              cout<<"Output\\input: ";
              
              if(cin.get() != '+')
              {
                  
                sc_regSet(ERROR, 1);
                Flags();
                  continue;
              }
              else
              {
                  cin>>input;
                  if(input/10000 != 0)
                  {
                      sc_regSet(ERROR, 1);
                      Flags();
                      continue;
                  }
                  else
                  {
                      sc_commandEncode(input/100, input%100, &value);
                      sc_memorySet(x +(y * 10), value);
                      Memory();
                      Print();
                  }
              }
          }
          Flags();
          mt_gotoXY(3,27);
      }
  }
void Flags()
{
    int value;
    for(int i = 1; i < 6; i++)
    {
        sc_regGet(i, &value);
        if(value == 1)
        {
            switch(i)
            {
                case 1:
                {
                    mt_gotoXY(68 +(i * 2),13);
                    cout<<"G";
                    break;
                }
                case 2:
                {
                    mt_gotoXY(68 +(i * 2),13);
                    cout<<"D";
                    break;
                }
                case 3:
                {
                    mt_gotoXY(68 +(i * 2),13);
                    cout<<"E";
                    break;
                }
                case 4:
                {
                    mt_gotoXY(68 +(i * 2),13);
                    cout<<"I";
                    break;
                }
                case 5:
                {
                    mt_gotoXY(68 +(i * 2),13);
                    cout<<"ER";
                    break;
                }
            }
        }
        else
        {
            mt_gotoXY(68 + (i*2),13);
            cout<<"   ";
        }
        mt_gotoXY(3, 27);
    }
}
int Operation(int command, int operand)
{
    int value, input, bit, a , buf = 0;
   switch(command)
   {
       case 10://Запись значения в ячейку
       {
          
           if(operand>100)
           {
               sc_regSet(EXIT,1);
               Flags();
           }
           else
           {
                mt_gotoXY(3,27);
                cout<<"Output\\input: ";
                if(cin.get() == '+')
                {
                    cin>>input;
                    sc_memorySet(operand,input);
                    Memory();
                    Print();
                }
                else
                {
                    sc_regSet(ERROR, 1);
                    Flags();
                }
           }
           break;
       }
       case 11://Получение значения из ячейки
       {
           mt_gotoXY(3,28);
           cout<<"Output\\input: ";
           sc_memoryGet(operand,&value);
           printf("+%04X", value);
           break;
       }
       case 20:// Запись в accumulator
       {
           sc_memoryGet(operand, &value);
           accumulator = value;
           Print();
           break;
       }
       case 21://Запись из accumulator
       {
           value = accumulator;
           sc_memorySet(operand,value);
           Memory();
           Print();
           break;
       }
       case 30://Сумма
       {
           sc_memoryGet(operand, &value);
           accumulator = accumulator + value;
           Memory();
           Print();
           break;
       }
       case 31://Разность
       {
           sc_memoryGet(operand, &value);
           accumulator = accumulator - value;  
           Memory();
           Print(); 
           break;
       }
       case 32://Деление
       {
           if(operand == 0)
           {
               sc_memorySet(DIVISION, 1);
               Flags();
           }
           else
           {
               sc_memoryGet(operand, &value);
           accumulator = accumulator / value;
           Memory();
           Print();
           }
           break;
       }
       case 33://Умножение
       {
           sc_memoryGet(operand, &value);
           accumulator = accumulator * value;
           Memory();
           Print();
           break;
       }
       case 40://Перемещение
       {
                y = operand/10;
                x = operand%10;
                Memory();
                Print();
           break;
       }
       case 41:
       {
           if(accumulator < 0)//Перемещение если accumulator < 0
           {
               y = operand/10;
               x = operand%10;
               Memory();
               Print();
           }
           break;
       }
       case 42://Перемещение если accumulator = 0  
       {
           if(accumulator == 0)
           {
               y = operand/10;
               x = operand%10;
               Memory();
               Print();
           }
           break;
       }
       case 43://Выход
       {
           return -1;
       }
       case 62://циклический сдвиг
       {
           Memory();
           Print();
            mt_gotoXY(9,27);
            cout<<bit;
           break;
       }
   }
   return 0;
}
void signalhandler (int signo)
{
    int command, operand, value;
    sc_memoryGet(x + (y*10), &value);
    sc_commandDecode(value,&command, &operand);
    //Operation(command, operand);
    if(Operation(command,operand) == -1){alarm(0);sc_regSet(IGNORE, 1);Flags();return;}
    x++;
    if(x == 10 && x != 0)
    {
        y++;
        x = 0;
    }
    Memory();
    Print();
    mt_gotoXY(3,29);
}
void handler (int signo)
{
    sc_memoryInit();
              sc_regInit();
              x = 0;
              y = 0;
              accumulator = 0;
              sc_regSet(IGNORE,1);
              Memory();
              Print();
              Flags();
}
void Timer()
{   
    setitimer (ITIMER_REAL, &nval, &oval);
}