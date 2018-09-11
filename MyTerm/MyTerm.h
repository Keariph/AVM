#ifndef H_MyTerm
#define H_MyTerm
enum colors {BLACK, RED, GREEN, BROWN, BLUE, PURPLE, CYAN, LGRAY, DGRAY = 10, LRED, LGREEN, YELLOW, LBLUE, LPURPLE, LCYAN, WHITE, NOT};
int mt_clrscr (void);
int mt_gotoXY (int, int);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (enum colors a);
int mt_setbgcolor (enum colors a);
#endif
