#ifndef TERMINAL_H
#define TERMINAL_H
#include <stddef.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <sys/ioctl.h>

enum colors{
  mt_black,
  mt_red,
  mt_green,
  mt_yellow,
  mt_blue,
  mt_magenta,
  mt_cyan,
  mt_white,
  mt_def
};

int mt_clrscr(void);							//Производит очистку и перемещение курсора в левый верхний угол экрана терминала
int mt_gotoXY(int x,int y);						//Перемещает курсор на указанную позицию
int mt_getscreensize(int* rows, int* columns);				//Определяет размер экрана терминала(кол-во строк и столбцов)
int mt_setfgcolor(enum colors color);					//Устанавливает цвет последующих вводимых символов
int mt_setbgcolor(enum colors color);					//Устанавливает цвет фона

#endif
/*Color       #define       Value     RGB
  black     COLOR_BLACK       0     0, 0, 0
  red       COLOR_RED         1     max,0,0
  green     COLOR_GREEN       2     0,max,0
  yellow    COLOR_YELLOW      3     max,max,0
  blue      COLOR_BLUE        4     0,0,max
  magenta   COLOR_MAGENTA     5     max,0,max
  cyan      COLOR_CYAN        6     0,max,max
  white     COLOR_WHITE       7     max,max,max*/

