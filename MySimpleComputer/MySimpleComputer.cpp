#include <iostream>
#include <fstream>
#include <cstdio>
#include "MySimpleComputer.h"

using namespace std;
extern int sc_memoryInit ()
{
    for(int i = 0; i<S; i++)
    {
        mas[i] = 0;
    }
    return 0;
}

extern int sc_memorySet (int address, int value)
{
    if(address > S)
    {
        sc_regSet(EXIT, 1);
        return 1;
    }
    else
    {
        mas[address] = value;
        return 0;
    }
}

extern int sc_memoryGet (int address, int * value)
{
    if(address > S)
    {
        sc_regSet(EXIT, 1);
        return 1;
    }
    else
    {
    *value = mas[address];
    return 0;
    }
}

extern int sc_memorySave (char * filename)
{
    ofstream os(filename, ios::binary);
    os.write(reinterpret_cast<char*>(mas), S*sizeof(int) );
    os.close();  
    return 0;
}

extern int sc_memoryLoad (char *filename)
{
   ifstream is(filename, ios::binary);
   is.read(reinterpret_cast<char*>(mas), S*sizeof(int) );
   is.close();
   return 0;
}

extern int sc_regInit (void)
{  
    registr = 0;
    flag = 0;
    return 0;
}

extern int sc_regSet (int reg, int value)
{
    if(reg > 5 && reg <0)
    {
        registr = sc_regSet(ERROR, 1); 
        return 1;
    }
    else
    {
        if(value == 1)
        {
            registr = registr|(1<<(reg-1));
        }
        if(value == 0)
        {
            registr = registr&(~(1<<(reg-1)));
        }
        return 0;
    }
}

extern int sc_regGet (int reg, int * value)
{
    if(reg > 5 && reg<0)
    {
        sc_regSet(ERROR, 1); 
        return 1;
    }
    else
    {
        *value = (registr>>(reg-1))&0x1;
        return 0; 
    }  
}

extern int sc_commandEncode (int command, int operand, int * value)
{
        
    if(operand <=128 && operand >= 0)
    {
        if(command<10 && command > 76 && command>11 && command < 21 && command>20 && command<30 && command>33 && command<40)
        {
            if(command == 0)
            {                
            *value = operand; 
            //*value = *value | (1 << 15);
            }
            //sc_regSet(flag, ERROR); 
            return 1;
        }  
        else
        {
            *value = (command<<7)|(operand);
            *value = *value &(~(1>>15));
            return 0;
        } 
    }
    else
    {
        sc_regSet(ERROR, 1); 
        return 1;
    }   
}

extern int sc_commandDecode (int value, int * command, int * operand)
{
    if(((registr>>15)& 0x1)== 0)
    {
        *command = value >> 7;
        *operand = value &0x7F; 
        return 0;
    }
    else
    {
        *command = value >> 7;
        *operand = value &0x7F; 
        sc_regSet(flag, GLUT); 
        return 1;
    } 
}
