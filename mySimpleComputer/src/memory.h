#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//Флаги
#define FLAG_P 1								//Переполнение при выполнении операции
#define FLAG_O 2								//Ошибка деления на 0
#define FLAG_M 3								//Ошибка выхода за границы памяти
#define FLAG_T 4								//Игнорирование тактовых импульсов
#define FLAG_E 5								//Указана неверная команда
#define sizeRAM 100
#define commandsCPUSC_COUNT 36 
int RAM[sizeRAM];								//Оперативная память
int reg;									//Регистр флагов

void my_printf(void);								//Вывод на экран ОЗУ
int sc_memoryInit(); 								//Инициализация ОЗУ Simple Computer, задавая всем ее ячейкам нулевые значения
int sc_memorySet(int address, int value);					// Задает значение указанной ячейки памяти как value	
int sc_memoryGet(int address,int* value);					//Возвращает значение указанной ячейки памяти в value
int sc_memorySave(char* filename);						//Сохраняет содержимое ОЗУ в бинарный файл
int sc_memoryLoad(char* filename);						//Загружает из указанного файла содержимое в ОЗУ
int sc_regInit(void);								//Инициализирует регистр флагов нулевым значением
int sc_regSet(int registr, int value);						//Устанавливает значение указаннго регистра флагов
int sc_regGet(int registr, int* value);						//Возвращает значение указанного флага
int sc_commandEncode(int command,int operand, int* value);			//Кодирует команду с указанным номером и опрерандом и помещает результат в value
int sc_commandDecode(int value, int* command,int* operand);			//Декодирует значение как команду Simple Computer

enum commandsCPUSC{
  //Операции I/O put
  READ=10,  WRITE=11,
  //Операции загрузки/выгрузки в аккумулятор
  LOAD=20,  STORE=21,  
  //Арифметические операции
  ADD=30,  SUB=31,  DIVIDE=32,  MUL=33,
  //Операции передачи управления
  JUMP=40,  JNEG=41,  JZ=42,  HALT=43,
  //Пользовательские функции
  NOT=51,  AND=52,   OR=53,    XOR=54,  JNS=55,
  JC=56,   JNC=57,   JP=58,    JNP=59,  CHL=60,
  SHR=61,  RCL=62,   RCR=63,   NEG=64,  ADDC=65,
  SUBC=66, LOGLC=67, LOGRC=68,          RCCL=69,
  RCCR=70, MOVA=71,  MOVR=72,           MOVCA=73,
  MOVCR=74,
};



#endif

