
/*--------------------------------------------------------------------------

Header file for program.
Copyright (c) 2005 Novosibirsk Morozov A.V.****
All rights reserved.
--------------------------------------------------------------------------*/
#define LBUF_SIZE    28
#define BUFOUT_SIZE  34
#define XBUFIN_SIZE  34
#define BUFOUT_LINE_SIZE  34
/*
#define LBUF_SIZE    32
#define BUFOUT_SIZE  32
#define XBUFIN_SIZE  32
#define BUFOUT_LINE_SIZE  32*/
//#define LTKH  11 //размер буфера int BX[]
//#define ATKH  0 //начальный адрес таблицы преобразования
/*--------------------------------------------------------------------
конфигурация констант выбора кристалов(cs)по интерфейсу SPI(порт-P2)
память FLASH D9(P2.6);
---------------------------------------------------------------------*/
#define MOD_FL1  //микросхемы D9
#define TASK2_2 1     //порядок выполнения задач(0,1,2,2,0..)
#define ADC_MULT 1     //модуль 

//#define INT_60  //интервал прерывания таймер1 - 60мкс.
//#define INT_501  //интервал прерывания таймер1 - 501 мкс.
#define INT_250 //интервал прерывания таймер1 - 250 мкс.
#ifdef  INT_60 
#define R_INT_TMR1_L -240 //-17 
#define R_INT_TMR1_H -3
#endif
#ifdef  INT_501 
#define R_INT_TMR1_L -0x17//-0x40 //-17 
#define R_INT_TMR1_H -0x19
#define I_TMR1 1
#endif
#ifdef  INT_250  
#define R_INT_TMR1_L -46//-44//-46 	  превышение интервала 250
#define R_INT_TMR1_H -13  //по 250 мкс
#define I_TMR1 2
#endif
#ifdef  MOD_FL1 // FLASH D9(P2.6);
#define Cfl_L  0x0BF
#define Cfl_R  0x40
#endif

//конфигурация интервала прерывания  таймера1 250мkс.

//#define W_INT_TMR1_L -24 
//#define W_INT_TMR1_H -2
#define R_INT_TMR1 250 
#define W_INT_TMR1 280
//конфигурация скорости передачи в линию (38400;19200;9600)
//EEPROM ADR=0;PAGE=1  "FFh-38400;09h-9600;01h-19200" 
#define C_UART_EPR 0 
#define C_UART 1
//#define C_UART_19200 0x01 
//#define C_UART_9600  0x09
#ifdef  C_UART 
#define C_UART_D 0xFF  
#endif
/*-------------------------------------------------------------------------
                 разбор линейных адресов контроллеров 
 Таблица описания линейных адресов модуля размещена в области EEPROM модуля
 в странице1(Epg1) c адреса Eadr=18h.

 В таблице описания линейных адресов модуля присутствует описания двух
 адресов (LADR1,LADR2 )и маски для каждого (MSK_LADR1,MSK_LADR2).
 Если LADR1= LADR_PAK & MSK_LADR1 либо LADR2= LADR_PAK & MSK_LADR2
 (LADR_PAK - адрес в принятом пакете модулем)адресуемый пакет обрабатывается
 модулем.
 В данном случаи в возвращаемом пакете модуля устанавливается адрес возврата
 ADR1_VR (ADR2_VR)из таблицы описания линейных адресов модуля.
 Пакет выдается в линию по истечению заданного интервала времени(мсек) 
 (T_LADR1,T_LADR2 )
  
 LADR1 - линейный адрес 1 (18h) ADR1_VR - возвращаемый адрес 1 (19h)
 LADR2 - линейный адрес 2 (1Ah) ADR2_VR - возвращаемый адрес 2 (1Bh)
 MSK_LADR1 - маска линейного адреса 1 (1Ch)
 T_LADR1   _ заданный интервал времени на передачу пакета по адресу 1 (1Dh)
 MSK_LADR2 - маска линейного адреса 2 (1Eh)
 T_LADR2   _ заданный интервал времени на передачу пакета по адресу 2 (1Fh)
 LADR_PAK - линейный адрес в приемном пакете.
 NEW_CMD - (NEW_CMD1,NEW_REG1,NEW_LDATA) - параметры для LADR2 команда,регистр,
 длина данных (0Ch,0Dh,0Eh)
-------------------------------------------------------------------------*/  
/*---определение номера страниц EEPROM*/
#define  Epg1 0
#define  Epg2 0x40
#define  Epg3 0x80
#define  Epg4 0xC0

/*-----------------------------------------------------
определение параметров таблицы описания линейных адресов
 модулей в области EEPROM страница1 (Epg1)
Имя параметра и его значение (адрес в формате HEX)
-------------------------------------------------------*/
#define  LADR1      0x118
#define  LADR2      0x11A
#define  ADR1_VR    0x119 
#define  ADR2_VR    0x11B
#define  MSK_LADR1  0x11C
#define  T_LADR1    0x11D  
#define  MSK_LADR2  0x11E 
#define  T_LADR2    0x11F
#define  NEW_CMD    0x10C //структура (NEW_CMD1,NEW_REG1,NEW_LDATA )

//#define  TMP_OUT    0x6C //темр вывода EEPROM стр1 адр 6C -3байт
#define  TMP_FLASH  0x164  //0x230 //Epg2
//структура 4байта CNT_IDF,CNT_IZM,CNT_IDF1,CNT_IZM1(30h-33h) 
//#define  MSK_PAR    0x34//MSK_ERR ;MSK_PW1 ;
#define  START_ADC  0x140 //старт цепочки измерения ADC
#define  FILT_RELE  0x150 //фильтр включения реле               
#define  ADR_FLASH  0x160 //текущий адрес FLASH (3bite 1страница)
#define  ADR_Vz     0xE4
/* ---------------------------------------------------------------------

C_SIN_REPR-константа  в мкс подсинхронизации чтения из EEPROM
----------------------------------------------------------------------*/
#define C_SIN_REPR 0x0FE //0X0B  //0x78 //0x78 //126mkc
/*
Макрос  Epr_Rd(Epg,Eadr) прочитать из EEPROM 4байта 
по заданной странице pg из диапозона (Epg=1/2/3/4)и адресам Eadr  из диапозона
(adr=00h - FFh) c помещением результатов в регистры SFR EDATA1,EDATA2,
 EDATA3,EDATA4;Epg - константы по определению выше (Epg1,Epg2 ...)
------------------------------------------------------------------*/


#define FUM_Epr_Wr(Eadr,E1,E2,E3,E4) { EADRH=(Eadr>>8)&0x03; EADRL=Eadr;ECON=0x01;	\
        EDATA1=E1;EDATA2=E2;EDATA3=E3;EDATA4=E4;	\
		EA=0;ECON=0x05;ECON=0x02;EADRH=0;EA=1;\  
		}

#define FUM_Epr_Wrout(Eadr,E1,E2,E3,E4) { EADRH=(Eadr>>8)&0x03; EADRL=Eadr;ECON=0x01;	\
        EDATA1=E1;EDATA2=E2;EDATA3=E3;EDATA4=E4;	\
		ECON=0x02;EADRH=0;\  
	    }

#define FUM_Epr_Rd(Eadr) {	EADRH=(Eadr>>8)&0x03; \
		EADRL=Eadr;ECON=0x01;EADRH=0;\
        }
/*-----------------------------------------------------------------------*/

 /*------------------------------------------------------------------
Макрос  FUM_MEMO_Rd(ADR_M) прочитать из xdata 2байта
из буфера BUF_CMD[256] адрес 0300Н 
 -ЭТО СТРАНИЦА  ГДЕ РАСПОЛОЖЕНА ПАМЯТЬ ПРОГРАММ АВТОМАТА 
while (TH1>C_SIN_REPR);
------------------------------------------------------------------*/
//--------------------------------------------------------------------------

