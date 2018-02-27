#include "memory.h"
#include "terminal.h"

int main(int argc, char** argv){
	setlocale(LC_ALL, "");
	sc_memoryInit(); //инициализируем память
	//запишем кое-что в память
	//------------------------------------
	sc_memorySet(9,1);
	sc_memorySet(5,2);
	sc_memorySet(60,3);
	sc_memorySet(95,4);
	//------------------------------------
	//получим из памяти что-нибудь
	//------------------------------------
	int m_get1 = sc_memoryGet(5,&m_get1);
	int m_get2 = sc_memoryGet(99,&m_get2);
	mt_setfgcolor(mt_yellow);
	mt_setbgcolor(mt_cyan);
	printf("m_get1=%d, m_get2=%d\n\n", m_get1, m_get2);
	//------------------------------------
	//сохраним память в бинарник и распечатаем память
	//------------------------------------
	sc_memorySave("RAM.bin");
	mt_setfgcolor(mt_green);
	mt_setbgcolor(mt_magenta);
	my_printf();
	//------------------------------------
	int col=0,row=0;
	//загрузим память из бинарника и распечатаем память
	//------------------------------------
	sc_memoryLoad ("RAM.bin");
	mt_setfgcolor(mt_cyan);
	mt_setbgcolor(mt_black);
	my_printf();
	//------------------------------------
	mt_getscreensize(&row,&col);
	//поработаем с регистром флагов
	//------------------------------------
	sc_regInit(); //зануляем все флаги
	mt_setfgcolor(mt_blue);
	mt_setbgcolor(mt_red);
	printf("reg=%d\n",reg); // вывод регистра
	
	sc_regSet(FLAG_T, 1); //установим флаг T в единицу
	
	
	int flg_T = sc_regGet(FLAG_T, &flg_T); // вернем значение флага T
	int flg_O = sc_regGet(FLAG_O, &flg_O); // вернем значение флага O
	printf("\nflg_T=%d, flg_O=%d\n",flg_T, flg_O); // вывод значения флагов T и O
	//------------------------------------
	//кодирование и декодирование команд
	//------------------------------------
	int cmd_encode = sc_commandEncode(SUBC, 4, &cmd_encode); // закодируем команду и операнд
	printf("\ncmd_encode=%d\n",cmd_encode); // вывод полученного
	
	printf("\n Machine command: ");
	for (int i = 15; i > 0; i--){
        printf("%c", '0' + ((cmd_encode & (1<<i))?1:0));
	}
	
	mt_setfgcolor(mt_red);
	mt_setbgcolor(mt_white);
	int op_decode, cmd_decode;
	sc_commandDecode(cmd_encode, &cmd_decode, &op_decode); // декодируем ранее закодированную команду
	printf("\ncmd_decode=%d, op_decode=%d\n",cmd_decode, op_decode); // вывод полученного
//------------------------------------
	mt_setbgcolor(mt_def);
	mt_setfgcolor(mt_def);
	mt_clrscr();
	mt_getscreensize(&row,&col);
	printf(" rows=%d, cols=%d\n", row, col);
	int x=10,y=10;
	mt_gotoXY(x,y);
return 0;
}