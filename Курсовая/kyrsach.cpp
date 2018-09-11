#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include "../Library/MySimpleComputer/MySimpleComputer.h"
#include "../Library/MyTerm/MyTerm.h"
using namespace std;
int main()
{
    string s;
    int x, y = 0, operand, command, value;
    string buf;
    fstream file("//home//evilspirit//Документы//Курсовая//proba.sa");
    while(getline(file,s))
    {
        string buf;
        x = 0; y = 0;
        x = s[0] - 48;
        y = s[1] - 48;
        if(s[0] - 48 == 0)
        x = 0;
        if(s[1]-48 == 0)
        y =0;
        operand = (s[s.size() - 2] - 48)*10 + (s[s.size()- 1] - 48);
        cout<<x<<y<<" ";
        if( s[3] == '=')
        {
            value = (s[s.size() - 4] - 48)*1000 + (s[s.size() - 3] - 48)*100 + ((s[s.size() - 2] - 48)) + (s[s.size()- 1] - 48);
            sc_memorySet(((x*10)+y), value);
            cout<<" = "<<value<<endl;
        }
        else
        {
            for(int i = 3; i <s.size() - 3; i++)
            {
                buf.push_back(s[i]);               
            }
            for(int i = 0; i < buf.size();i++)
            {
                cout<<buf[i];
            }
            cout<<" "<<operand;
            if(buf == "READ")command = 10;
            if(buf == "WRITE")command = 11;
            if(buf == "LOAD")command = 20;
            if(buf == "STORE")command = 21;
            if(buf == "ADD")command = 30;
            if(buf == "SUB")command = 31;
            if(buf == "DIVIDE")command = 32;
            if(buf == "MUL")command = 33;
            if(buf == "JUMP")command = 40;
            if(buf == "JNEG")command = 41;
            if(buf == "JZ")command = 42;
            if(buf == "HALT")command = 43;
            if(buf == "RCL")command = 62;
            sc_commandEncode(command, operand, &value);
            cout<<"\t"<<value<<endl;
            sc_memorySet(((x*10)+y), value);
        }
    }
    sc_memorySave("//home//evilspirit//Документы//Laba3//Memory.txt");
    file.close();
    return 0;
}
