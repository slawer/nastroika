//Описания таблиц конфигурации измеряемых каналов
//Опис_Таб_Кан.h
 //--выбор мультиплекс (биты Р2.5 Р2.4 Р2.3)
/*

code unsigned int  TAB_ADC[4][9] = {0,0,0,0,0,0,0,0,0,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8,    
                     0,0x0600,0x0608,0x0680,0x0688,0x0620,0x0628,0x00A0,0x00A8,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8};
/*
//--------буфер сохраняемых параметров --------------
xdata struct BX_SAVE 
{
unsigned char BUF_S[16]; 
}BX_SAVE;
 xdata struct  BX_SAVE Str_BX_SAVE _at_ 0x0590;
//Str_BX_SAVE.BUF_S[16]  
//--------------- таблицы пороговых значений --------------
*/
 xdata struct BX_A 
{
unsigned char ZGL_BX_A[4]; //ZGL_BX_A[1] - байт ERROR 1x PWU/I; mask POROG
unsigned int  TAB_BX[6]; // _at_ 0x05A0 ;//буфер пороговых аналоговых значений
}BX_A;
xdata struct  BX_A Str_BX_A[8] _at_ 0x05E0; 


 //  до 1с xdata занята в main.h

 xdata unsigned int BUF_S[15] _at_ 0x0200;	 // восьмая строчка
 xdata unsigned long BUF_T[15] _at_ 0x01C0; //0x0340; //0x0200;			  7
 xdata unsigned long BUF_N[15] _at_ 0x0100; //0x0370; //0x0230;		   4
 xdata unsigned long BUF_U[15] _at_ 0x0140; //0x0370; //0x0230;			5
 xdata unsigned long BUF_FP[15] _at_ 0x0180; //0x0370; //0x0230;		 6
  
	/*
 xdata unsigned int BUF_S[15] _at_ 0x0200;	 // восьмая строчка
 xdata unsigned int BUF_T[15] _at_ 0x01C0; //0x0340; //0x0200;			  7
 xdata unsigned long BUF_N[15] _at_ 0x0100; //0x0370; //0x0230;		   4
 xdata unsigned int BUF_U[15] _at_ 0x0140; //0x0370; //0x0230;			5
 xdata unsigned int BUF_FP[15] _at_ 0x0180; //0x0370; //0x0230;		 6
  */
/*	xdata struct MN 
	{
		unsigned long  ZN [7]; //Zn - значение накопленных за 100 мс значений из ацп
//		unsigned char  KOL[7]; // kol - количество накопленных значений
	}MN;
*/  	
//	xdata struct MN BUF_MN[7];
//	xdata unsigned long  BUF_MN[7] _at_ 0x00DD;		 перенесено в main.h 

//xdata unsigned char St[32] _at_ 0x0300;	 // восьмая строчка

 
//-------------- таблицы преобразований ---------------
xdata struct BX1_A 
{
unsigned char ZGL_BX1_A[4];
unsigned int  TAB_BX1[22]; //буфер таблицы физических преобразов.аналогов
}BX1_A;
 xdata struct  BX1_A Str_BX1_A[8] _at_ 0x0400;
//-------------------------------------------------------------------------

//-------------- таблица описания режимов записи FLASH 20 08 08 ---------------
/*
R_WR_FLASH; //режимы записи
XXXX 0000 - значение вычисляемого канала не писать во FLASH
0000 XXXX - значение измеряемого канала не писать во FLASH
0010 0010 - запись должна содержать максимальное значения измеряемого и вычислеемого каналов
0100 0100 - запись должна содержать среднее ариф. значения измеряемого и вычислеемого каналов
1000 1000 - данные должны писаться при достижении значений PZ измеряемого и вычислеемого каналов
*/

//------структура таблиц описания  каналов в XDATA 
xdata struct TABX_CH_A 
{
//unsigned char ZGL_TABX_CH[4]; 
unsigned char NAME_PAR; //имя параметра измеряемого
unsigned char R_IZM;    //режим измерения анал.каналов(task3/task2)
unsigned char Frm_Dat; //значение запятой 00 40 80 C0; 00 10 20 30; ......
unsigned char LA_TAB; //длина таблицы
unsigned char NA_P1; //имя производного параметра1(порог)
unsigned char NA_P2; //имя производного параметра2(I/U)
unsigned char NA_P3; //формат основного параметра {XX,X запятая)
unsigned char NA_P5; //имя производного параметра5 
unsigned char NA_P4; //формат производного параметра {XX,X запятая)
unsigned char N_RAZ; //номер разъема TIP_PAR;
unsigned char KF_CRD; //коэффициент усреднения
unsigned char KF_WIND;
unsigned int  KF_KORZ; //коэффициент коррекции(множитель)  резул.измерения(физ.значен)
unsigned int  KF_KORZ1; //KF_KORZ1; //коэффициент коррекции1(делитель) резул.измерения(физ.значен)
//unsigned char  KF_KORZ1; //адрес размещения
}TABX_CH_A;
xdata struct  TABX_CH_A Str_CH_A[13] _at_ 0x0680; //0x0494;// адрес и количество структур данного типа

xdata unsigned char ZG_TABX_DAT[4] _at_ 0x07B0; //0x0520;

// xdata unsigned char  BF_ZP_A[16] _at_ 0x0780 ;


 // xdata unsigned int K1  _at_ 0x0760;
 // xdata unsigned int HH1  _at_ 0x0763;
 // xdata unsigned long K2  _at_ 0x0766;
 // xdata unsigned long HH2  _at_ 0x076B;

xdata struct TABX_DAT 
{   
unsigned char NAME_PAR; //имя параметра
unsigned char ADR_RZ; //адрес размещения результата в буфер результатов
}TABX_DAT;
 xdata struct  TABX_DAT Str_TDAT[20] _at_ 0x07B4;// адрес и количество структур данного типа



