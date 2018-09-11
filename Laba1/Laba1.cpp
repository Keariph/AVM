#include <iostream>
#include "../Library/MySimpleComputer/MySimpleComputer.h"
using namespace std;
int main()
{
    int address, value, command, operand, a;
    char filename;
    sc_memoryInit();
    sc_regInit ();
    cout<<"Enter namber command"<<endl;
    while(true)
    {
        cout<<"1. Изменить значение ячейки памяти 2. Вывести значение памяти 3. Сохранить в файл 4. Считать с файла 5. Изменить значение регистра 6. Вывести значение регистра 7. Закодировать 8. Раскодировать 0. Выход"<<endl;
        cin>>a;
        switch (a)
        {
            case 1:
            cout<<"Enter the address"<<endl;
            cin>>address;
            sc_memorySet (address, value);
            break;
            case 2:
            cout<<"Enter the value"<<endl;
            cin>>value;
            sc_memoryGet (address, & value);
            break;
            case 3:
            cout<<"Enter the way to file"<<endl;
            cin>>filename;
            sc_memorySave (& filename);
            break;
            case 4:
            cout<<"Enter the way to file"<<endl;
            cin>>filename;
            sc_memoryLoad (& filename);
            break;
            case 5:
            cout<<"Enter the register"<<endl;
            cin>>reg;
            sc_regSet (reg, value);
            break;
            case 6:
            cout<<"Enter the value"<<endl;
            cin>>value;
            sc_regGet (reg, & value);
            break;
            case 7:
            cout<<"Enter number command and operand"<<endl;
            cin>>command>>operand;
            sc_commandEncode (command, operand, & value);
            break;
            case 8:
            cout<<"Enter the value"<<endl;
            cin>>value;
            sc_commandDecode (value, & command, & operand);
            break;
            case 0:
            exit(0);
        }
    }
 return 0;   
}
