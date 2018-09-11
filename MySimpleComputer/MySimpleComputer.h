#ifndef H_MySimpleComputer
#define H_MySimpleComputer

static int S = 100;
static int *mas =  new int[S];
static int registr, flag;
#define GLUT 1//Перегрузка
#define DIVISION 2//Деление на ноль
#define EXIT 3//Выход за границы
#define IGNORE  4//Игнорирование
#define ERROR 5 //Некоректные данные
int sc_memoryInit ();//Зануление памяти
int sc_memorySet (int address, int value);//Установка значений памяти
int sc_memoryGet (int address, int * value);//Получение значений памяти
int sc_memorySave (char * filename);//Запись в файл
int sc_memoryLoad (char * filename);//Чтение из файла
int sc_regInit (void);//Зануление регистра
int sc_regSet (int reg, int value);//Установка регистра
int sc_regGet (int reg, int * value);//Получение регистра
int sc_commandEncode (int command, int operand, int * value);//Кодирование
int sc_commandDecode (int value, int * command, int * operand);//Раскодировка
#endif
