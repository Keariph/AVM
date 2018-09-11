

#ifndef H_MyBigChars
#define H_MyBigChars
#include "../MyTerm/MyTerm.h"
#include "../MySimpleComputer/MySimpleComputer.h"
//enum color {black, red, green, yellow, blue, purple, teal, white};

// static long int masP[2]{4279769112, 404232447};
// static long int mas0[2]{3284386815, 4291019715};
// static long int mas1[2]{3234257088, 3233857728};
// static long int mas2[2]{3233857791, 4278389808};
// static long int mas3[2]{1063305471, 4290822240};
// static long int mas4[2]{4291019715, 3233857728};
// static long int mas5[2]{4278387711, 4290822336};
// static long int mas6[2]{51130560, 4291019775};
// static long int mas7[2]{811647231, 50727960};
// static long int mas8[2]{4291019775, 4291019715};
// static long int mas9[2]{4291019775, 101462112};
static long int masP[2]{4279769112, 404232447};
static long int mas0[2]{3284401920,4291019715};
static long int mas1[2]{3639656448, 3233857740};
static long int mas2[2]{3234070272, 4278389808};
static long int mas3[2]{1623260928, 4290797628};
static long int mas4[2]{3639656448, 3233873868};
static long int mas5[2]{63176448, 4290822399};
static long int mas6[2]{204521472, 4291019775};
static long int mas7[2]{811663104, 50727960};
static long int mas8[2]{3284401920, 4291019775};
static long int mas9[2]{3284401920, 102260991};
/*-------------------WORD---------------------*/
static long int masA[2]{3278247936, 3284386815};
static long int masB[2]{3284352768, 4291019583};
static long int masC[2]{63143680, 2143486723};
static long int masD[2]{3278061312, 1069794243};
static long int masE[2]{63176448, 4278387711};
static long int masF[2]{63176448, 50529087};
static long int chars[22]{4279769112, 404232447, 3284386815, 4291019715, 3234257088, 3233857728, 3233857791, 4278389808, 1063305471, 4290822240, 4291019715, 3233857728, 4278387711, 4290822336, 51130560, 4291019775, 811647231, 50727960, 4291019775, 4291019715, 4291019775, 101462112};
static char gap = 32;
static char block = 97;
static char vertical = 120;
static char horizontal = 114;
static char CorUpRh = 108;
static char CorUpLf = 107;
static char CorDwRh = 109;
static char CorDwLf = 106;
static char limit = 255;
int bc_printA (char * str);//Вывод символов
int bc_box(int x1, int y1, int x2, int y2);//Вывод рамки
int bc_printbigchar (long int [2], int x, int y, enum colors a, enum colors b);//Вывод БЧ
int bc_setbigcharpos (long int * big, int x, int y, int value);//Установка значения  ячейки БЧ
int bc_getbigcharpos(long int * big, int x, int y, long int *value);//Получение значения ячейки БЧ
int bc_bigcharwrite (int fd,long int * big, int count);//Запись в файл
int bc_bigcharread (int fd, long int * big, int need_count, int * count);//Чтение с файла
#endif
