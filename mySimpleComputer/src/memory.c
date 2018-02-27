#include "memory.h"
/*
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
  MOVCR=74,*/

int cCPUSC[36]={READ, WRITE, LOAD, STORE, 
			   ADD, SUB, DIVIDE, MUL, 
			   JUMP, JNEG, JZ, HALT,  
			   NOT, AND, OR, XOR, JNS, 
			   JC, JNC,JP,JNP, CHL, SHR, RCL, 
			   RCR, NEG, ADDC,SUBC,LOGLC, LOGRC, 
			   RCCL, RCCR,MOVA, MOVR, MOVCA, 
			   MOVCR,};


//Вывод на экран ОЗУ
void my_printf(){
	int i;
	for(i = 0; i < sizeRAM; i++){
		if (i != 0 && i % 10 == 0)
			printf("\n");
		printf("%d", RAM[i]);
	}
	printf("\n\n");
}

//Функции работы с ОЗУ
//Инициализация ОЗУ Simple Computer, задавая всем ее ячейкам нулевые значения
int sc_memoryInit(){					
  if(NULL != RAM){
    for(int i=0;i<sizeRAM;i++){
      RAM[i]=0;
    }
  }else{
    printf("Error memory! Memory not initialized.\n");
    free(RAM);
    return 0;
    }

  return 1;
}

//Сохраняет содержимое ОЗУ в бинарный файл
int sc_memorySave(char* filename){
  FILE *save=NULL;
  save= fopen(filename,"wb");
  if(save==NULL){
    printf("Error opening file.\n");
    return 0;
  }
  for(int i=0;i<sizeRAM;i++)
    fwrite(&RAM[i],sizeof(int),1, save);
  fclose(save);
  return 1;
}

//Загружает из указанного файла содержимое в ОЗУ
int sc_memoryLoad(char* filename){
  FILE *load=NULL;
  load= fopen(filename,"rb");
  if(load==NULL){
    printf("Error opening file.\n");
    return 0;
  }
  for(int i=0;i<sizeRAM;i++){

    fread(&RAM[i],sizeof(int),1, load);
  }
  fclose(load);
  return 1;
}

//Функции работы с ячейками памяти
// Задает значение указанной ячейки памяти как value
int sc_memorySet(int address, int value){
  if ((address>=0)&&(address<sizeRAM)){
    RAM[address]=value;
    return 1;
  }else{
    printf("Error!Invocation of non-existent memory.\n");
    return 0;
  }
}

//Возвращает значение указанной ячейки памяти в value
int sc_memoryGet(int address,int* value){
  ;
  if ((address>=0)&&(address<sizeRAM)){
    *value=RAM[address];
    return *value;
  }else{
    printf("Error!Invocation of non-existent memory.\n");
    return 0;
  }
}

//Функции с флагами
//Инициализирует регистр флагов нулевым значением
int sc_regInit(){
  reg=0;
  return 0;
}

//Устанавливает значение указаннго регистра флагов
int sc_regSet(int registr, int value){
  if ((value < 0) || (value > 1)) //некорректное значение
		return -1;
	
	 if ((registr < 0) || (registr > 5)) //некорректное значение флага
		return -1;
	
	if (value == 1)
		reg = reg | (1 << (registr - 1)); //установить значение флага в единицу
	else reg = reg & (~(1 << (registr - 1))); //установить значение флага в ноль
	//reg - переменная хранящая флаги; registr - номер разряда(по порядку)
  return 0;
}

//Возвращает значение указанного флага
int sc_regGet (int registr, int * value){
	if ((registr > 0) && (registr < 5))
		return	*value = (reg >> (registr - 1)) & 0x1; //получаем значение определенного флага
		//reg - переменная хранящая флаги; my_reg - номер разряда(по порядку)
	else //некорректное значение регистра
		return -1;
}

//Кодирование и Декодирование
//Кодирование
int sc_commandEncode (int command, int operand, int * value){
	int i, f = 0;
	
	for (i = 0; i < commandsCPUSC_COUNT; ++i)
		if (cCPUSC[i] == command)	{
			f = 1;
			break;
		}

	if (f) {
		sc_regSet(FLAG_E, 0); //флаг ошибки в ноль(команда верная)
		return *value = (command & 0x7F) << 7 | (operand & 0x7F);
	//	return 0;
	}

	sc_regSet(FLAG_E, 1); //флаг ошибки в единицу(команда неверная)
	return -1;
}

//Декодирование
int sc_commandDecode (int value, int * command, int * operand){
	if (!value || value >> 14 || !command || !operand) {
		sc_regSet(FLAG_E, 1); //флаг ошибки в единицу(команда неверная)
		return -1;
	}

	*operand = value & 0x7F;
	*command = (value >> 7) & 0x7F;
	return 0;
}