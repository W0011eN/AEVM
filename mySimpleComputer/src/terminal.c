#include "terminal.h" 

/*Color       #define       Value     RGB
  black     COLOR_BLACK       0     0, 0, 0     	mt_black,
  red       COLOR_RED         1     max,0,0		mt_red,
  green     COLOR_GREEN       2     0,max,0		mt_green,
  yellow    COLOR_YELLOW      3     max,max,0		mt_yellow,
  blue      COLOR_BLUE        4     0,0,max		mt_blue,
  magenta   COLOR_MAGENTA     5     max,0,max		mt_magenta,
  cyan      COLOR_CYAN        6     0,max,max		mt_cyan,
  white     COLOR_WHITE       7     max,max,max		mt_white,

  mt_def*/


// Очистка экрана терминала
int mt_clrscr(){
  write(1, "\E[H\E[J", 6);
  return 0;
}

//Устанавливает цвет последующих вводимых символов
int mt_setfgcolor(enum colors color){
 switch(color){
   case mt_black:
    write(1, "\E[30m", 6);
    break;
   case mt_red:
    write(1, "\E[31m", 6);
    break;
    case mt_green:
    write(1, "\E[32m", 6);
    break;
   case mt_yellow:
    write(1, "\E[33m", 6);
    break;
    case mt_blue:
    write(1, "\E[34m", 6);
    break;
   case mt_magenta:
    write(1, "\E[35m", 6);
    break;
    case mt_cyan:
    write(1, "\E[36m", 6);
    break;
   case mt_white:
    write(1, "\E[37m", 6);
    break;
     case mt_def:
    write(1, "\E[39m", 6);
    break;
   default:
      return -1;
  }
return 1;
}

//Устанавливает цвет фона
int mt_setbgcolor(enum colors color){
 switch(color){
   case mt_black:
    write(1, "\E[40m", 6);
    break;
   case mt_red:
    write(1, "\E[41m", 6);
    break;
    case mt_green:
    write(1, "\E[42m", 6);
    break;
   case mt_yellow:
    write(1, "\E[43m", 6);
    break;
    case mt_blue:
    write(1, "\E[44m", 6);
    break;
   case mt_magenta:
    write(1, "\E[45m", 6);
    break;
    case mt_cyan:
    write(1, "\E[46m", 6);
    break;
   case mt_white:
    write(1, "\E[47m", 6);
    break;
     case mt_def:
    write(1, "\E[49m", 6);
    break;
   default:
      return -1;
  }
return 1;
}

//Определяет размер экрана терминала(кол-во строк и столбцов)
int mt_getscreensize(int* rows, int* columns){
  struct winsize{
    unsigned int ws_row;
    unsigned int ws_col;
  };
  struct winsize ws;
  if (!ioctl(1,TIOCGWINSZ,&ws)){
    *rows=ws.ws_row;
    *columns=ws.ws_col;
    printf("The screen size is received.\nNumber of rows: %d .\nNumber of columns: %d.\n",*rows,*columns);
  }else{
    fprintf(stderr,"Error retrieving screen size!\n");
  }
  return 0;
}

//Перемещает курсор на указанную позицию
int mt_gotoXY(int x, int y){
   char buf[15];
    char *gotoxy = "\E[%d;%dH";

    if (sprintf(buf, gotoxy, y, x) > 0) {
	if (write(1, buf, strlen(buf)) == -1)
	    return -1;
    }
return 0;
}