/*
Copyright 1995-1996 Keil Software, Inc.  4-задания. task_3 измерение 4 периодов
порт2(0.1.2.3.) 
БАЗОВЫЙ КОНТРОЛЛЕР ИЗМЕРИТЕЛЬНОГО МОДУЛЯ (BKCD-ADuc848)  2005г.
------------------------------------------------------------------------------*/

#include "r_main.h" 
#include "main.h" 
#include "define_stuct.h"
//#include "reg816.h"
#include "aduc848.h"
#include "ADC_bkcd.h"
//#include "rasx.h" 
//#include "Опис_Таб_Кан.h"
//xdata unsigned int kol_t=0,kol_kom=0,kol_e=0,kol_tsk=0,imp2=0;
//data unsigned char nas1,nas2;

// для запуска ацп на минимальное время из таймера
	//	    data unsigned int PNT_BUF_TD;
	

	
 xdata unsigned char tm_kan;
 data unsigned char kn;
 
 extern data int DAC_PRIN;

 bit d1,d2,d11,d22,napr=0;
 bit aktiv;
 xdata unsigned char chp=1,paket=0;

//  data  unsigned char  dis, tdis;
 xdata unsigned char WK_1, WKs;  // байт кнопок
 data  unsigned char  N_K, KOL;
 bit fl_tadc;
 extern code unsigned int  TAB_ADC[4][9];
 extern	xdata unsigned long  BUF_MN[7];
 extern	xdata unsigned long  BUF_vr[7];
//  для увеличения объема каждые 100 мс
 data unsigned char   nas1,nas2;
 xdata unsigned int BUF_FP_100_0=0;
 xdata unsigned int fcnt_k=0;
// xdata unsigned char  cnt_r=0;

xdata unsigned char  b_err_p=0,mi11=30,stat_byte=0, b_err_pit=0;
data unsigned int kol_c=0;
//data unsigned char fk=0;

//xdata unsigned char fl_buf=0;
bit	 fl_buf=0,fl_rgr, v_rgr;
bit fl_sv=0;
bit fl_rest=0;
sbit svet=P2^4;

//xdata unsigned char vr,int_d;
xdata unsigned char POR_R1_ON=0,POR_R2_ON=0,POR_R1_OFF=0,POR_R2_OFF=0;

xdata unsigned char par=0;
//xdata unsigned char  adcbuf[12];
//data unsigned int tmpadc;
//extern xdata unsigned char BUF_S[15];
//extern void Timer1int (void);
void kmd (void);
//xdata unsigned char im_2,buf_sh[4];
extern xdata unsigned long BUF_T[15];
//idata unsigned int nach=0;

data unsigned char zad=0;

extern  void setup (void);
extern  void setup_ADC (void);
//extern  void wradc(void);
//extern void sttim1 (void);
//extern void ser_int (void);
//extern void timer1int (void);
//extern void intWD (void); 

extern void task_3 (unsigned char kan) ;
extern void lbuf_cop();
extern void cop_buf();

//extern xdata unsigned char ZG_TABX_DAT[4];

data unsigned char Len_p=0;
data unsigned char len_o=0;
//xdata unsigned int  zn_ko=0; //kol_o, kol_e, kol_s,kol_n,kol_ez;
data unsigned int ED=0;
bit   rez, fl_r22=0,fl_r11=0, Eprom_zap=0,Eprom_ch=0,FL_BLOK_EPROM=0;
bit  ep2=0;
bit FCNT_SEC_V1=0, FCNT_SEC_V2=0,fcnt=0,fcnt_100=0;//FCNT_V2=0,

		


idata unsigned char  j,j1,i,j2;	  // временно изза зависания макроса сетап адс если их расположить в регистрах майн
data unsigned char i1; 				  // временно изза зависания макроса сетап адс если их расположить в регистрах майн
data unsigned int crc=0;

xdata unsigned int ob_par=0;
//xdata unsigned bit ob_par[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

data unsigned char st_ser=0, r_crc=0;


idata unsigned char tmo=0,nro=0;//,tm_f;
//idata unsigned char tms;
idata unsigned int crco=0;
idata unsigned char tmp=0;
//xdata unsigned char dl_p;


//idata unsigned int CNT_SEC_V=0, CNT_SEC_V2=0;
//idata unsigned long CNT_SEC_DL=0;

data unsigned long H1=0,H2=0;
//bit FCNT_SEC_V,FCNT_SEC_V2;

//extern  data unsigned int CM1,CM2,CM3,CM_RAX1;
//extern data unsigned char N_CH;
//xdata unsigned char a;

 extern xdata struct TABX_CH_A 
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
unsigned int  KF_KORZ1;//KF_KORZ1; //коэффициент коррекции1(делитель) резул.измерения(физ.значен)
//unsigned char  KF_KORZ1; //адрес размещения
}TABX_CH_A;
extern xdata struct  TABX_CH_A Str_CH_A[13]; //0x0494;// адрес и количество структур данного типа

extern   xdata struct TABX_DAT 
{   
unsigned char NAME_PAR; //имя параметра
unsigned char ADR_RZ; //адрес размещения результата в буфер результатов
}TABX_DAT;
extern xdata struct  TABX_DAT Str_TDAT[20];// адрес и количество структур данного типа


//extern code unsigned int  TAB_ADC[4][9];
code unsigned int  VER_PR=0x0501; 

//extern unsigned long idata TEMP_1;
//extern  data unsigned int  cnt_dol,rasx1, rasx1_t,rasx2, rasx2_t, copy_p0,copy_p1; 
idata unsigned char MM[7];
extern  data unsigned int  copy_p, copy_p1; 
//extern idata unsigned int  rasx1_t, rasx2_t;
//extern idata unsigned int cnt_dol,rasx1,rasx2;

//xdata unsigned char flz,flzz; // флаг защиты буфера результатов
//idata unsigned char	z0,z1,z2,z3,z4; // переменные для перекопирования параметра в случае его порчи
//bit er1=0, er2=0;// ens=0;
 // мои

 /*
   описание версий:
   	 3.0 между каналами разнобой
	 3.1 между каналами по 9 мск
	 3.2 между каналами  1 мск	(епром виснет) =3.1+(ИЗЗА ЗАВИСАНИЯ ПРИ ЗАПИСИ ЕПРОМА ПО  КМД 01 И 03) запись епрома вынесена из прерывания в майн по флагу Eprom_zap
	 		  вроде бы очень быстрые зависания при жутком шуме и наложениях в течении 5 мин не наблюдаются..  
			  диодик мигает реже по таймеру и часто по завершению  80ти циклов полной оцифровки и расчета
			  однако на команды перестал реагировать ч\з 5 мин
     3.3 время преобразования ацп настроено на 9мс на обработку общую отводится по 9 мс 
	 	    дополнительный буфер результатов заполняемый по завершению полного цикла преобразования каналов ,
		 	этот буфер теперь и  выдается по команде опроса	
			каждые начала десятка минут происходит автокалибровка ацп
			стек с защитой буфером  вниз 
	 4.3 - почищенная и готовая с накоплением импульсов хода за время, заданное в епроме.

	 4.41 - проверенная испытаниями с отслеживанием по миганию диодика разных неисправностей
	 4.42 - та же 4.41 но с инверсией включения реле(для нягани реле включаются низким потенциалом)

 */


 /************** timer1 *********************/
/*
void sttim1 (void) using 0
{			

  //TF1=0;	
 
 // TR1 = 1;

return;
}
*/
 /*
 void intWD (void) interrupt 0xB
{
   	EA=0;
 	WDWR=1;
	WDCON=0x10;		  // 31.2 ms
	EA = 1; 
  
 //IT0=1;
 //IE0=1;
 return;	   
}

 */

 /*
void intIE (void) interrupt 0
{
//extern idata unsigned int CMRX1_K1,CMRX2_K1, CMRX1_K2,CMRX2_K2, cnt_dol;

 /*
  i=0;
  WR=1;
  while (1)
  {
  
  SBUF=0x77;
  while (TI==0)
  {}
  TI=0;
  }
  WR=0;
  */
 // EEPR_ADDBUF[0]=0;
 // EEPR_ADDBUF[1]=0;
 // TEMP=&lbuf[0];
 // FU_wepr(TEMP,4,&EEPR_ADDBUF[0]);
 /*
#pragma asm
//POP B
MOV EADRH, #00H    
MOV EADRL, #58H 
//MOV ECON,   0x01    
MOV EDATA1, #11H 
MOV EDATA2, #22H 
MOV EDATA3, #33H 
MOV EDATA4, #44H 
//MOV     ECON,#05H                                          
MOV     ECON,#02H
MOV     EADRH,#00H 

#pragma endasm
 */
 /*CMRX1_K1=2222;
while(1) {
 CMRX1_K1++;
 FUM_Epr_Wrout((0x160-0x100)>>2,0x33,0x22,CMRX1_K1>>8,CMRX1_K1)
 }
 */
 
 /*
	j=buf_sh[0];
	if (j!=0xFF)
	{ 	TEMP_1=BUF_T[j];   
		FUM_Epr_Wrout((0x160-0x100)>>2,TEMP_1>>24,TEMP_1>>16,TEMP_1>>8,TEMP_1)
	} 
  	j=buf_sh[1];
	if (j!=0xFF)
	{ TEMP_1=BUF_T[j];
	 FUM_Epr_Wrout((0x164-0x100)>>2,TEMP_1>>24,TEMP_1>>16,TEMP_1>>8,TEMP_1)
 	}
  	
	j=buf_sh[2];
	if (j!=0xFF)
	{  TEMP_1=BUF_T[j];
 		FUM_Epr_Wrout((0x168-0x100)>>2,TEMP_1>>24,TEMP_1>>16,TEMP_1>>8,TEMP_1)
	}
  
  	j=buf_sh[3];
	if (j!=0xFF)
	{	TEMP_1=BUF_T[j];
 		FUM_Epr_Wrout((0x16C-0x100)>>2,TEMP_1>>24,TEMP_1>>16,TEMP_1>>8,TEMP_1)
 	}
	

  // раньше было досюда
// FUM_Epr_Wrout((0x100-0x100)>>2,SPH,SP,kol_ez,kol_e)
 
 //FUM_Epr_Wr((0x104-0x100)>>2,kol_s>>8,kol_s,kol_n>>8,kol_n)

//goto  	STARTUP1;
  
  	 while (st_ser==40)
	 {}
	 EA = 0;
	 WDWR=1;
	 WDCON=0x03;  		// 15.6 ms
	 EA = 1;                    


}
*/


void timer1int (void) interrupt 3 using 1
{
//extern idata unsigned char p2cf;
extern xdata unsigned int cnt_ves;
//extern xdata unsigned long BUF_FP_100;


 // TF1=0;
 // TL1 = -0;//0xC4;//-200;
 // TH1 = -49;//-1;

//   status=status|0x04;



//	status=st_ser;
	TF1=0;
	TH1=R_INT_TMR1_H;
  TL1=R_INT_TMR1_L;
	
	copy_p1=copy_p;
 	copy_p=P0;						
 	rasx2_t++;
	rasx1_t++;
//	kol_t++;
//	if (kol_c<=6200)
//		kol_c++;
//   if (kol_c==6200)
//   {
//   		st_ser=5;
//		ES=1;
//   }


	CNT_SEC_V1++;	 // отсчет времени для объема насоса по режиму 0х84
    if (nas2!=0xff)
	{	
	 	if (CNT_SEC_V1==400)
		{ 	extern idata unsigned long  CMRX1_K2; 
			extern xdata unsigned long BUF_FP[15];
				CMRX1_K2+=BUF_FP[nas2];
				CNT_SEC_V1=0;
		}
	}
	else
 		if (CNT_SEC_V1>4000)
		{	CNT_SEC_V1=0;
			FCNT_SEC_V1=1;
		}	


	CNT_SEC_V2++;	 // режим 84
    if (nas1!=0xff)
	{	
 	 	if (CNT_SEC_V2==400)
		{ 	extern idata unsigned long  CMRX1_K1;
			extern xdata unsigned long BUF_FP[15];
				CMRX1_K1+=BUF_FP[nas1];
				CNT_SEC_V2=0;
		}
	}				 
	else
		if (CNT_SEC_V2>4000)
		{	CNT_SEC_V2=0;
			FCNT_SEC_V2=1;
		}

	if (MM[2]!=0)				  // ходы канала 2 режим 0х84   обьем 0x09
	{

		if (((copy_p&MM[2])==MM[2])&((copy_p1&MM[2])!=MM[2]))
		{  

 		   bufcht1[0]++;
		   if (!fl_m2)
		   {	 
				  fl_m2=1;
				 bufcht1[0]=0;fl_r22=0;	rasx2_t=0;rasx2=0;// rasx2_t=rasxti_2;
		   }

		if (H2!=0)
		{		if (rasx2_t>H2)//&(rasx2_t>Ras[bufcht1[0]]))
				{
					fl_r22=1;
					cop_imp2=bufcht1[0];
					rasx2=rasx2_t;
					rasx2_t=0;
					bufcht1[0]=0;
				}
				else 
					if (!fl_r22)
					{
					cop_imp2=bufcht1[0];
					rasx2=rasx2_t;
					}

		   }
		   else
		   {
				cop_imp2=bufcht1[0];
				rasx2=rasx2_t;
				rasx2_t=0;
				bufcht1[0]=0;

		   }
		}


	   if (rasx2_t>((rasx2/cop_imp2)<<1)+H2)
	   {
				rasx2=rasx2_t;	   	
	   }

	   if (rasx2_t>=80000)
	   {
				cop_imp2=0;
				bufcht1[0]=0;
				rasx2=0;	   	
	   		    rasx2_t=0;
				fl_m2=0;
	   }
  	}

// ходы канала 1 по режиму 0х88
	if (MM[1]!=0)
	{
		if (((copy_p&MM[1])==MM[1])&((copy_p1&MM[1])!=MM[1]))
		{  
 		   bufcht1[1]++;
		   if (!fl_m1)
		   {	 
			  fl_m1=1;
			 bufcht1[1]=0;fl_r11=0;	rasx1_t=0; rasx1=0;// rasx2_t=rasxti_2;
		   }

			if (H1!=0)
			{
				if (rasx1_t>H1)//&(rasx1_t>Ras[bufcht1[1]]))
				{
					fl_r11=1;
					cop_imp1=bufcht1[1];
					rasx1=rasx1_t;
					rasx1_t=0;
					bufcht1[1]=0;
				}
				else 
					if (!fl_r11)
					{		cop_imp1=bufcht1[1];
							rasx1=rasx1_t;
					}
			}
			else
			{
				cop_imp1=bufcht1[1];
				rasx1=rasx1_t;	
				rasx1_t=0;
				bufcht1[1]=0;					
			}
	   }
	   if (rasx1_t>((rasx1/cop_imp1)<<1)+H1)
	   {
				rasx1=rasx1_t;	   	
	   }

	   if (rasx1_t>=80000)
	   {
				cop_imp1=0;
				bufcht1[1]=0;
				rasx1=0;	   	
	   			rasx1_t=0;
				fl_m1=0;
	   }

  	}
// когец ходов 1 по режиму 0х88


	if (MM[0]!=0)
	{
	
		if ((copy_p&MM[0])==MM[0])  {d1=1;} else {d1=0;}
		if ((copy_p&MM[6])==MM[6])  {d2=1;} else {d2=0;}
	 	
		if  ((d1==1)&(d11==0))  
		{ if (d2==1) {if (napr) {if (cnt_dol>0) {cnt_dol--;} } else  {if (cnt_dol<65535) {cnt_dol++;}}}
		  else {if (napr) {if (cnt_dol<65535) {cnt_dol++;}} else  {if (cnt_dol>0) {cnt_dol--;}}}		}
	  
		if  ((d1==0)&(d11==1))  
		{ if (d2==1) {if (napr) {if (cnt_dol<65535) {cnt_dol++;}} else  {if (cnt_dol>0) {cnt_dol--;}}}
		  else {if (napr) {if (cnt_dol>0) {if (cnt_dol>0) {cnt_dol--;}}} else  {if (cnt_dol<65535) {cnt_dol++;}}}		}
		
	
	
		if  ((d2==1)&(d22==0))  
		{ if (d1==1) {if (napr) {if (cnt_dol<65535) {cnt_dol++;}} else  {if (cnt_dol>0) {cnt_dol--;}}}
		  else {if (napr) {if (cnt_dol>0) {cnt_dol--;}} else  {if (cnt_dol<65535) {cnt_dol++;}}}		}
	
		if  ((d2==0)&(d22==1))  
		{ if (d1==1) {if (napr) {if (cnt_dol>0) {cnt_dol--;}} else  {if (cnt_dol<65535) {cnt_dol++;}}}
		  else {if (napr) {if (cnt_dol<65535) {cnt_dol++;}} else  {if (cnt_dol>0) {cnt_dol--;}}}		}

		d11=d1;
		d22=d2;
	}

 // начало время для подсчета объема по ходам
	CNT_SEC++;
    if (fl_rgr)
	{	if (CNT_SEC==400)
		{ 	extern idata unsigned long  cmr;
			cmr+=BUF_FP_100_0;
//			cnt_r++;
			CNT_SEC=0;
		}
	}
	else
		if (CNT_SEC>4000)
		{	CNT_SEC=0;
			fcnt=1;
		}
 // конец время для подсчета объема по ходам


	if (zad!=0)
		zad--;
	else
	 	stat_byte=0x66;											    


 // начало проверки вышел ли таймаут после ответа
 priem++;

 if ((priem>2)&((st_ser==5)|(st_ser==10)))
 {
 	WR=0;st_ser=5;nr=0xFF; ES=1;
 }
 // конец проверки вышел ли таймаут после ответа 
 
	if (tmo<1)
	{
		 	if (st_ser==20)
			{
	
			st_ser=40;
			nro=1;
			SBUF=0x7E;
			}
	}
	else 
	{
		if (st_ser==20)
			tmo--;
	}							
	
return;
}


void int_adc (void) interrupt 6
{
	data unsigned int tmadc;
	
	mi++;

 	if (mi>666) 
 	{
		mi=0;
  		ep2=ep2^1;
		if (fl_sv)
	    	if (ep2==1)
				svet=1;
		else
			svet=0;
 	} 
		
  /*
	if 	(RDY0)
	{	 RDY0 = 0;
			 tmadc=TAB_ADC[Str_CH_A[0].N_RAZ&0x03][Str_CH_A[0].N_RAZ>>2];
		 
			 P2=(P2&0x57)|(tmadc&0xA8);

   	
			 SF=bx_sf1;
			 ADC0CON2 = BX_RF | (tmadc>>8); 
			 ADCMODE = BX_MD; //старт ацп 
	}
	*/
 
	if (RDY0)
	{	
		RDY0 = 0;
  
		if (Str_CH_A[N_K].N_RAZ==0xFF)
			tmadc=0;
		else
 	  		tmadc  =  ADC0H<<8 | ADC0M;//int

		ADC0H=0;
		ADC0M=0;

        BUF_MN[N_K]+=tmadc;	
		 
		if (KOL==4)
		{
			BUF_vr[N_K]=BUF_MN[N_K];
		    BUF_MN[N_K]=0;     
		}	
					
		N_K++;
		if (N_K==7)
		{
			N_K=0;
			if (KOL==4)
			{
				KOL=0;
				// проверка кнопок
				WK_1=0;
				for(kn=1;kn<9;kn++)
				{	
					WK_1=WK_1>>1;     
					P2 = (P2&0x57)|(TAB_ADC[2][kn]&0xA8);
					WK_1=WK_1 |((P0&0x04)<<5);
				}
				WK_1=~WK_1;
			}
			KOL++;
		}
	
		 tm_kan= Str_CH_A[N_K].N_RAZ;
		 if  (tm_kan==0xFF)
			 {tm_kan=5;}
	  
		//	 tmadc=TAB_ADC[kanal[N_K]&0x03][kanal[N_K]>>2];
/*
		if (N_K==0)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==1)  {tmadc=TAB_ADC[0x09&0x03][0x09>>2];}
		if (N_K==2)  {tmadc=TAB_ADC[0x0D&0x03][0x0D>>2];}
		if (N_K==3)  {tmadc=TAB_ADC[0x11&0x03][0x11>>2];}
		if (N_K==4)  {tmadc=TAB_ADC[0x15&0x03][0x15>>2];}
		if (N_K==5)  {tmadc=TAB_ADC[0x19&0x03][0x19>>2];}
		if (N_K==6)  {tmadc=TAB_ADC[0xFF&0x03][0xFF>>2];}
		
		if (N_K==0)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==1)  {tmadc=TAB_ADC[0x09&0x03][0x09>>2];}
		if (N_K==2)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==3)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==4)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==5)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}
		if (N_K==6)  {tmadc=TAB_ADC[0x05&0x03][0x05>>2];}					 
*/
		
	//		 P2=(P2&0x57)|(tmadc&0xA8);

 			 tmadc=TAB_ADC[tm_kan&0x03][tm_kan>>2];  	
			 SF=bx_sf1;
			 ADC0CON2 = BX_RF | (tmadc>>8); 
		//	 ADC0CON2 = BX_RF | (0x0108>>8);

			 ADCMODE = BX_MD; //старт ацп 		
		}
		

/*

			N_K++;
			if (N_K==7)
			{
				KOL++;
				N_K=0;
				if (KOL==16)
				{
 					for (i1=0;i1<8;i1++)
					{																														 
						BUF_vr[i1]=BUF_MN[i1];
				//		BUF_MN[i1]=0;									         
					}

			//		cop_buf();

					KOL=0;

 				}
			}
*/		
 return;
}


void ser_int (void) interrupt 4 using 2                             //monitor    monitor
      
{
	data unsigned char i;

	if (RI == 1)
    {  	
		tmp=SBUF;
		RI = 0;
			
		    
		if (WR==1)
		{
			goto kon;
		}
	
	    priem=0; 

		if   (st_ser!=5)
			{goto kon;}
		 
		nr++;
		if (nr>34) 
		{
		 	st_ser=10;
		 	goto kon;
		}

		if (nr==2)
		{
			if ((tmp<36)&(tmp>6))
			{
				Len_p=tmp;
			}
			else
			{ 
			 	st_ser=10;
				goto kon;//	return;
			}
		}
			
			 
		if (nr==0)
		{
		 	if (tmp!=0x7E)
			{	
				st_ser=10;
				goto kon;//	return;
			}
		}

		if (nr==1)
		{
			if ((tmp!=lineadd)&(tmp!=0x3F)&(tmp!=lineadd_dop))
			{
				if (tmp==0xFF)
				{
					st_ser=10;
					goto kon;// return;
				}
				if ((tmp!=rele_prin[0].linaddr)|(tmp!=rele_prin[1].linaddr)|(tmp!=rele_prin[2].linaddr)|(tmp!=rele_prin[3].linaddr)|(tmp!=rele_prin[4].linaddr))
				{
					st_ser=10;
					goto kon;// return;
				}
			}
		}

		xbufin[nr] = tmp;

		if ((nr==Len_p)&(nr>6))
		{  	
			st_ser=50;
			/*
			if ((xbufin[1]==lineadd)|(xbufin[1]==0x3F))
			{
			*/
			crc=0xFFFF;
			if (r_crc==0xFF)
			{
				for(i=0;i<Len_p;i++)
				{
					if (i==1) {crc=0;}
					   crc+=xbufin[i] ;
				}
			}
			else
 				for(i=1;i<Len_p-1;i++)
				{
					data tmpbait=xbufin[i];
					crc = (crc >> 8) ^ Crc16Table[(crc & 0xFF) ^ tmpbait++];
				//	xbufin[i]--;
				}

			if (((crc&0x00FF)==tmp)&((r_crc==0xFF)|(xbufin[nr-1]==crc>>8)))
			{	
			   len_o=xbufin[5];
			   if (len_o>28) 
			   	  {st_ser=10; goto kon;}




			   if ((xbufin[1]==lineadd_dop)&(lineadd_dop!=0xFF))
			   {
					// принята команда как на блок отображения с адресом коробки  и 0x80
				//	if (len_o==4)				
					{
						
						bit bRELE;

						DAC_PRIN=xbufin[paket_BO.off_dac];
						DAC_PRIN<<=8;
						DAC_PRIN+=xbufin[paket_BO.off_dac+1];
						
						bRELE= (xbufin[paket_BO.off_rele1]&0x01);	RELE1=~bRELE;

						bRELE=(xbufin[paket_BO.off_rele2]&0x01);	RD=~bRELE;
						
					
					//	DACH=xbufin[6];
					//	DACL=xbufin[7];	
		/*			
					paket_BO.off_rele1=7;
					paket_BO.off_rele2=9;
					paket_BO.off_dac=10;
			*/	
	
	/*					
						DAC_PRIN=0x04;
						DAC_PRIN<<=8;
						DAC_PRIN+=0xD2;		

						DAC_PRIN=0x04;
						DAC_PRIN<<=8;
						DAC_PRIN+=0xD2;	
*/


/*
						DAC_PRIN=xbufin[10];
						DAC_PRIN<<=8;
						DAC_PRIN+=xbufin[11];

						bRELE= (xbufin[7]&0x01);	RELE1=~bRELE;

						bRELE=(xbufin[9]&0x01);	RD=~bRELE;
	*/					
						
			//			DAC_PRIN=4000;
			//			RELE1=0;
			//			RD=0;
						
						
					//	RELE1=~(xbufin[8]&0x01);
					//	RD=	~(xbufin[8]&0x02);								
					}
					
					st_ser=10; goto kon;
			   }
			   else
			   {
				 
					 if ((xbufin[1]==lineadd)|(xbufin[1]==0x3F))
					 {
				   for(i=0;i<Len_p;i++)
	            	   zbuf[i]=xbufin[i]; 
	                
				   zbuf[1]=xbufin[1]|0x80;
	  			   cmd = zbuf[3] &0x03;
	
				   if ((zbuf[3]&0xE0)!= 0) 	  // команда работы с епромом
				   {
		  		    	if (len_o!=24)
							if (len_o>0x16) 
						   		{st_ser=10; goto kon;}
		  				if ((xbufin[3]&0x1C)!=0) 
						   	{st_ser=10; goto kon;}
						if ((zbuf[3]&0x1C)!= 0) 
							{st_ser=10; goto kon;}
	
						ED=zbuf[3]&0xE0;
						ED=ED<<3;
						ED=ED+zbuf[4]-0x100;
	                    
						// write eeprom
	 					if (((cmd ==1))|(cmd ==3))
						{	 
						   if ((len_o!=Len_p-7)|(FL_BLOK_EPROM!=1))
						    {st_ser=10; goto kon;}
							Eprom_zap=1;
						} 
		
	
						if (cmd ==2)
						{	 
							Eprom_ch=1;
						}
	      
				    }
						
						//*****************************************
					if ((zbuf[3]&0xE0)  == 0) //no EEPROM
					{
						if  (zbuf[4]==0)
						{  
							if ((cmd == 2)&(fl_buf))              // команда выдачи результатов в буфер         
							{ 
								for(i=0;i<len_o;i++)
							  	{
								  	bufout[i+6] =lbuf_dn[i];
							 	}  
								WR=1; len_o=len_o+6;  
								tmo=TM_LINE+TM_LINE;
								st_ser=20;
								bufout[2]=len_o+1;                   
						    }
						}
	
						if  ((zbuf[4]==0x20)&((zbuf[3]==0x01)|(zbuf[3]==0x03)|(zbuf[3]==0x02)))		// спецкоманда			 
						{
						   	if (len_o==Len_p-7)
								kmd();
	 					}          
					} 
	
					if ((zbuf[3] ==5)&(cmd!=0)&(zbuf[4] ==0x10)&(zbuf[5] ==0x01))  	// команда рестарта
					{  
						fl_rest=1;
						EA = 0; 
						WDWR=1;WDCON=0x02;	 // 500 ms
						EA = 1; 
					}
	
				 	if ((st_ser==50)&(Eprom_zap!=1))
						 {st_ser=10; goto kon;}
						 
					}
					else   //  dopolnitelnie linadr for rele
					{
						extern xdata unsigned int REL1_ON,REL1_OFF,REL2_ON,REL2_OFF;
							if (xbufin[1]==rele_prin[0].linaddr)
							{
									xdata int temp_pr_rel=0;						
								temp_pr_rel=xbufin[rele_prin[0].off];
								temp_pr_rel<<=8;
								temp_pr_rel+=xbufin[rele_prin[0].off+1];
								
								if (temp_pr_rel>rele_prin[0].ustavka1)
										REL1_ON++;
								else
										REL1_OFF++;	
										
								if (temp_pr_rel>rele_prin[0].ustavka2)
										REL2_ON++;
								else
										REL2_OFF++;										
							}

							if (xbufin[1]==rele_prin[1].linaddr)
							{
									xdata int temp_pr_rel=0;						
								temp_pr_rel=xbufin[rele_prin[1].off];
								temp_pr_rel<<=8;
								temp_pr_rel+=xbufin[rele_prin[1].off+1];
								
								if (temp_pr_rel>rele_prin[1].ustavka1)
										REL1_ON++;
								else
										REL1_OFF++;	
										
								if (temp_pr_rel>rele_prin[1].ustavka2)
										REL2_ON++;
								else
										REL2_OFF++;										
							}

							if (xbufin[1]==rele_prin[2].linaddr)
							{
									xdata int temp_pr_rel=0;						
								temp_pr_rel=xbufin[rele_prin[2].off];
								temp_pr_rel<<=8;
								temp_pr_rel+=xbufin[rele_prin[2].off+1];
								
								if (temp_pr_rel>rele_prin[2].ustavka1)
										REL1_ON++;
								else
										REL1_OFF++;	
										
								if (temp_pr_rel>rele_prin[2].ustavka2)
										REL2_ON++;
								else
										REL2_OFF++;	
							}
							
							if (xbufin[1]==rele_prin[3].linaddr)
							{
									xdata int temp_pr_rel=0;						
								temp_pr_rel=xbufin[rele_prin[3].off];
								temp_pr_rel<<=8;
								temp_pr_rel+=xbufin[rele_prin[3].off+1];
								
								if (temp_pr_rel>rele_prin[3].ustavka1)
										REL1_ON++;
								else
										REL1_OFF++;	
										
								if (temp_pr_rel>rele_prin[3].ustavka2)
										REL2_ON++;
								else
										REL2_OFF++;	
							}

							if (xbufin[1]==rele_prin[4].linaddr)
							{
									xdata int temp_pr_rel=0;						
								temp_pr_rel=xbufin[rele_prin[4].off];
								temp_pr_rel<<=8;
								temp_pr_rel+=xbufin[rele_prin[4].off+1];
								
								if (temp_pr_rel>rele_prin[4].ustavka1)
										REL1_ON++;
								else
										REL1_OFF++;	
										
								if (temp_pr_rel>rele_prin[4].ustavka2)
										REL2_ON++;
								else
										REL2_OFF++;									
							}

							
							 if (REL1_ON>POR_R1_ON)	 
							 {	RELE1=0; REL1_ON=0;  REL1_OFF=0;}

							 if (REL1_OFF>POR_R1_OFF)	 
							 {  RELE1=1; REL1_ON=0;	 REL1_OFF=0;}

							 if (REL2_ON>POR_R2_ON)	 
							 {	RD=0;    REL2_ON=0;	 REL2_OFF=0;}

							 if (REL2_OFF>POR_R2_OFF)	 
							 {	RD=1;    REL2_ON=0;  REL2_OFF=0;}							
							st_ser=10; goto kon;
					}
				}
			}
			else
			{	
				st_ser=10;
				goto kon;//	return;
			}
			/*
			}
			else 
			{
				st_ser=10;
				goto kon;//	return;
			}
			*/
		}  			   
	}
	// КОНЕЦ РАЗБОРКИ ПРИНЯТОГО ПАКЕТА

	if (TI == 1)
	{
   		TI=0;
   		if (WR!=1)
			{st_ser=10;	goto kon;}

		if (st_ser==40)
		{ 
			if (nro<=5)
			{
				if (nro==2)
				 	tmp=bufout[2];
				else
					if (nro==1)
 			 		{	
						tmp=lineadd|0x80; 
						crco=0;
						if (r_crc!=0xFF)
			         		crco=0xFFFF;
					}
					else
						tmp=zbuf[nro];
			}
			else 
				if (nro==len_o)
				{
					if (r_crc==0xFF)
   						tmp=status;
					else
						tmp=crco>>8;
				}
				else
					if (nro==len_o+1)
							tmp=crco;
					else
						if (nro>len_o+1)
						{
							crco=0;
							st_ser=10;
							goto kon;
						}
						else
							tmp=bufout[nro];
			SBUF=tmp;
			if (r_crc==0xFF)
				crco+=tmp;
			else
				if (nro!=len_o)
			    	crco = (crco >> 8) ^ Crc16Table[(crco & 0xFF) ^ tmp++];

			nro++;
		}
		else
			{st_ser=10;}				 
	}
	//  КОНЕЦ ОБРАБОТКИ ПОСЛЕ ПРИНЯТИЯ ОЧЕРЕДНОГО БАЙТА ПО УСАРТ 

	kon:
	return;
}



void kmd (void) //using 3
{ 
	register unsigned char tmp_rw;

	// начало по флагу 21 аналог адц 20
  	if ((zbuf[2]==0x09)&(zbuf[5]==0x02)&(zbuf[6]==0xA0)&(zbuf[7]==0x01)) //  флаг разрешения записи в епром
    {                           			
		FL_BLOK_EPROM=1;
		bufout[6]=zbuf[6];bufout[7]=zbuf[7];
		WR=1;
		tmo=TM_LINE+TM_LINE;
		st_ser=20;
    }

 
    if ((zbuf[2]==0x0B)&(zbuf[5]==0x04)&(zbuf[6]==0xC1)) //  установить новое значение параметров
    {
		extern data unsigned int new_zn;  
		data unsigned char t=0; 

		t=zbuf[7];
	/*			if (t==0x01)	//  	 
				{
				    ob_par=ob_par|0x0001;
				}

				if (t==0x02)	//  	 
				{
				   ob_par=ob_par|0x0002;
				}

				if (t==0x03)	//  	 
				{
				   ob_par=ob_par|0x0004;
				}


				if (t==0x04)	//  обнулить тальблок	 
				{
				    ob_par=ob_par|0x0008;
				}

				if (t==0x05)	//  обнулить колонну	 
				{
				    ob_par=ob_par|0x0010;
				}

				if (t==0x06)	//  обнулить трение	 
				{
				    ob_par=ob_par|0x0020;
				}

				if (t==0x07)	//  	 
				{
				    ob_par=ob_par|0x0040;
				}

				if (t==0x08)	//  	 
				{
				   ob_par=ob_par|0x0080;
				}

				if (t==0x10)	//  корректировать Насаос аналог 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
					    ob_par=ob_par|0x100;
						new_zn=zbuf[7]<<8;
						new_zn+=zbuf[8];
					}
				}

				if (t==0x20)	//   корректировать Насаос 1  	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x200;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}
				
				if (t==0x30)	//  корректировать Насаос 2 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x400;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}
				
	*/			if (t==0x40)	//  корректировать тальблок 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x800;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}

				if (t==0x50)	//  установить новый вес колонны 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x1000;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}

/*				if (t==0x60)	//  корректировать трение	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x2000;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}
				
				if (t==0x70)	//  корректировать тальблок 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x4000;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}

				if (t==0x80)	//  установить новый вес колонны 	 
				{
				    if ((ob_par&0xFF00)==0)
					{ 
				    ob_par=ob_par|0x8000;
					new_zn=zbuf[8]<<8;
					new_zn+=zbuf[9];
					}
				}
  */   

//				bufout[6]=zbuf[6];bufout[7]=zbuf[7];
//				tmo=TM_LINE+TM_LINE;
//				st_ser=20;
		  }


   /*
		   if ((zbuf[6]==0xB2)&(zbuf[7]==0x00)) //  		команда установки 
           {                           
			старший байт дола zbuf[8]
			младший байт дола zbuf[9] 
			bufout[8]=VER_PR>>8;bufout[9]=VER_PR;  bufout[10]=st_ser;
			bufout[11]=SPH;bufout[12]=SP;
				tmo=TM_LINE+TM_LINE;
				zbuf[5]=7;		// длина ответа+1
				st_ser=20;
           }
   */

  		   if ((zbuf[6]==0xB2)&(zbuf[7]==0x34)) //  		команда чтения прошивки
           {                           
		   	//	bufout[6]=;/*bufout[7]=0x01;*/ 
			bufout[6]=zbuf[6];bufout[7]=zbuf[7]; 
			bufout[8]=VER_PR>>8;bufout[9]=VER_PR;  bufout[10]=st_ser;
			bufout[11]=SPH;bufout[12]=SP;
			WR=1;	tmo=TM_LINE+TM_LINE;
				zbuf[5]=7;		// длина ответа+1
				st_ser=20;
           }


		   if ((zbuf[5]==0x02)&(zbuf[6]==0xB0)&(zbuf[7]!=0xFF)) //  обнуления объемов
           {                           
		        if (zbuf[7]==1)					 // аналог
				  ob_par=ob_par|0x01;

		        if (zbuf[7]==2)				  	//  насос 1
				{  ob_par=ob_par|0x02;
				}

		        if (zbuf[7]==3)					//  насос 2
				  ob_par=ob_par|0x04;

		        if (zbuf[7]==0x20)					//  актив-пассив
				  ob_par=ob_par|0x20;

		     //   if (zbuf[7]==0)
			//	  ob_par=ob_par|0x08;

/*
	    	  if (zbuf[7]==1)
				  	vr=1;
				  if ((zbuf[7]==2)&(vr==1))
				  	vr=2;
				  if ((zbuf[7]==3)&(vr==2))
				  	vr=3;
   */
			//	bufout[6]=zbuf[6];bufout[7]=zbuf[7]; bufout[8]=zbuf[8];bufout[9]=zbuf[9];
				//zbuf[5]=4;
			//	tmo=1;
		//		tmo=TM_LINE+TM_LINE;
			//	zbuf[5]=7;		// длина ответа+1
			//	st_ser=20;
           }

 /*		   if ((zbuf[5]==0x04)&(zbuf[6]==0xA3)&(zbuf[7]==0x0B)) //  FLASH
           {                           
		       lineadd=zbuf[8];
			   lineaddo=zbuf[9];
						
				EDATA1=lineadd;
				EDATA2=lineaddo;
				FUM_Epr_Wr(((LADR1-0x100)>>2),lineadd,lineaddo,0xFF,0xFF)
				bufout[6]=zbuf[6];bufout[7]=zbuf[7]; bufout[8]=zbuf[8];bufout[9]=zbuf[9];
			//	zbuf[5]=10;
				tmo=TM_LINE+TM_LINE;
  
           }
 */
         
              
           if (zbuf[6]==0xB5) // R/W CLOCK
           {                           
           		if ((cmd == 1)&(zbuf[5]==0x0A)&(zbuf[2]==0x11))                   //wr
           		{
   /*
adcbuf[0]=0xD0;
adcbuf[1]=0x00;  
adcbuf[2]=0; adcbuf[3]=0;
adcbuf[4]=0;adcbuf[5]=0;
adcbuf[6]=0;adcbuf[7]=0;
adcbuf[8]=0;adcbuf[9]=0;
adcbuf[10]=0;adcbuf[11]=0;
adcbuf[12]=0; adcbuf[13]=0;
adcbuf[14]=0; adcbuf[15]=0;

FUM_WR_DAT_CLOCK(adcbuf,16)
*/

  		SEC=zbuf[9];
		MIN=zbuf[10];
		HOUR=zbuf[11];
		
					zbuf[7]=0xD0;
					zbuf[8]=0x00;
MDO=0; 
DL=2;while (1){DL--;if (DL==0) break;} 
MCO=0; 
for(j=7;j<17;j++) 
  {   
   for(i1=0;i1<8;i1++) 
     { 
      if((zbuf[j]&0x80)==0) 
        { 
         MDO=0;  
         }  
          else  
           {  
            MDO=1;  
             } 
              DL=2;while (1){DL--;if(DL==0)break;} 
              MCO=1; while (1) {if (MCO==1)break;} 
              DL=2;while (1){DL--;if(DL==0)break;} 
              MCO=0;                        
              if (i1!=7) { zbuf[j] = zbuf[j]<<1;} 
              MDO=0;  
               }                                   
                   DL=2;while (1){DL--;if(DL==0)break;}     
                   MDO=1; MDE=0; MCO=1; while (1) {if (MCO==1)break;}                   
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					
				   if (DL==0) b_err_cl++;
				   MDE=1;  MCO=0;  
               }                          
                  DL=2;while (1){DL--;if(DL==0)break;}  
                  MCO=1; while (1) {if (MCO==1)break;}
                  DL=2;while (1){DL--;if(DL==0)break;} 
                  MDO=1;   
									  
				// прочитали в часы внутренние
/*										tmp_rw=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0;  
					for(j=0;j<2;j++)  
					{for(i1=0;i1<8;i1++)  
					{if((tmp_rw&0x80)==0)   
					{MDO=0;} else {MDO=1;} 	 
					DL=2;while (1){DL--;if(DL==0)break;}MCO=1; 	 
					while (1) {if (MCO==1) break;}				 
					DL=2;while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;  
					tmp_rw = tmp_rw<<1; }                                         
					                 DL=2;while (1){DL--;if(DL==0)break;}      
					                   MDE=0; MCO=1;  MDO=1;  while (1) {if (MCO==1) break;}                   
						               while (1){if (MDI==0) break;} 					 
									   MDE=1;  MCO=0;  									  
					tmp_rw = 0x00;}                                                                             
					DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						    
					while (1) {if (MCO==1) break;}											 
					DL=2;while (1){DL--;if(DL==0)break;} 									  
					MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						   
					tmp_rw=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						    
					MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	 
					for(i1=0;i1<8;i1++) 												  
					{ if((tmp_rw&0x80)==0){MDO=0;}else { MDO=1;} 					  
					DL=2;while (1){DL--;if(DL==0)break;}							   
					MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;                                                      
					tmp_rw= tmp_rw<<1; } 																    
					                 DL=2;while (1){DL--;if(DL==0)break;}    							    
					                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}                 
						               while (1){if (MDI==0) break;} 																	  
									   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											 
					for(j=0;j<8;j++)																									 
					{for(i1=0;i1<8;i1++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		    
					if (MDI ==0) 																									    
					{buf_ch[j] = buf_ch[j]<<1;buf_ch[j] = buf_ch[j]&0xFE;} 															    
					else 																											    
					{buf_ch[j] = buf_ch[j]<<1;   																					   
					buf_ch[j] = buf_ch[j]|0x01; }                          					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							  
					MDO=0;																	   
					if (j==(8-1)) {MDO=1;}												    
					MDE=1;                            											 
					MCO=1;  while (1) {if (MCO==1) break;}										  
					DL=2;while (1){DL--;if(DL==0)break;} 										   
					MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							    
					MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										 
					MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									  
					MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1; 
		 tmp_rw=((buf_ch[0]>>4)*10) +(buf_ch[0]&0x0F); 			
		 SEC=tmp_rw;
		 tmp_rw=((buf_ch[1]>>4)*10) +(buf_ch[1]&0x0F); 			
		 MIN=tmp_rw;
		 tmp_rw=((buf_ch[2]>>4)*10) +(buf_ch[2]&0x0F); 			
		 HOUR=tmp_rw;	
	*/	 
//		 bufout[6]=SEC;
//		 bufout[7]=MIN; bufout[8]=HOUR;bufout[5]=17;  zbuf[5]=9;   

		zbuf[5]=2;
		cmd=2;
		zbuf[2]=0x09;

			   
            	}
   
				if ((cmd == 2)&(zbuf[5]==2)&(zbuf[2]==0x09))                   //wr/ rd 
				{
					tmp_rw=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0;  
					for(j=0;j<2;j++)  
					{for(i1=0;i1<8;i1++)  
					{if((tmp_rw&0x80)==0)   
					{MDO=0;} else {MDO=1;} 	 
					DL=2;while (1){DL--;if(DL==0)break;}MCO=1; 	 
					while (1) {if (MCO==1) break;}				 
					DL=2;while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;  
					tmp_rw = tmp_rw<<1; }                                         
					                 DL=2;while (1){DL--;if(DL==0)break;}      
					                   MDE=0; MCO=1;  MDO=1;  while (1) {if (MCO==1) break;}                   
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 
				   				   if (DL==0) b_err_cl++;
				
					 
									   MDE=1;  MCO=0;  									  
					tmp_rw = 0x00;}                                                                             
					DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						    
					while (1) {if (MCO==1) break;}											 
					DL=2;while (1){DL--;if(DL==0)break;} 									  
					MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						   
					tmp_rw=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						    
					MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	 
					for(i1=0;i1<8;i1++) 												  
					{ if((tmp_rw&0x80)==0){MDO=0;}else { MDO=1;} 					  
					DL=2;while (1){DL--;if(DL==0)break;}							   
					MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;                                                      
					tmp_rw= tmp_rw<<1; } 																    
					                 DL=2;while (1){DL--;if(DL==0)break;}    							    
					                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}                 
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 
				  				   if (DL==0) b_err_cl++;
				
																  
									   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											 
					for(j=0;j<8;j++)																									 
					{for(i1=0;i1<8;i1++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		    
					if (MDI ==0) 																									    
					{bufout[9+j] = bufout[9+j]<<1;bufout[9+j] = bufout[9+j]&0xFE;} 															    
					else 																											    
					{bufout[9+j] = bufout[9+j]<<1;   																					   
					bufout[9+j] = bufout[9+j]|0x01; }                          					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							  
					MDO=0;																	   
					if (j==(8-1)) {MDO=1;}												    
					MDE=1;                            											 
					MCO=1;  while (1) {if (MCO==1) break;}										  
					DL=2;while (1){DL--;if(DL==0)break;} 										   
					MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							    
					MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										 
					MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									  
					MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1;       
			//		for(i1=0;i1<8;i1++)
			//		{ 	adcbuf[i1]=i1;}
			//		SEC=bufout[9];
			//		MIN=bufout[10];
			//		HOUR=bufout[11]; 
			//		bufout[9]=zbuf[9];
			//		bufout[10]=zbuf[10];
			//		bufout[11]=zbuf[11]; 
					bufout[6]=zbuf[6];/*bufout[7]=0x01;*/ 
					bufout[7]=zbuf[7]; bufout[8]=zbuf[8];bufout[5]=17;  zbuf[5]=10;//	len_o=17;bufout[2]=17;

			//		for(i1=0;i1<8;i1++)
			//		{ 	bufout[9+i1]=adcbuf[i1];}                            
						
				 // len_o=17;
				 WR=1;
				 tmo=TM_LINE+TM_LINE;
				 st_ser=20;
				 }

            }


       
/*		   if((zbuf[6]&0x3F)==0x37) // read Flash zikl в обратном направлении
           {                           
 		
			EA=0;
			WR=1;
	//		CM1=(zbuf[7]<<8)|zbuf[8];
			CM1=0;
		for  (j=1;j<9;j++)
			for(i1=0;i1<127;i1++)
  			{
				tmpadc=*(int xdata*)CM1;
			SBUF=tmpadc>>8;
				while (TI==0)
				{}
				TI=0;	
				SBUF=tmpadc;
				while (TI==0)
				{}
				TI=0;
				CM1++;
				CM1++;
			}
	
			WR=0;
			EA=1;
           }
 */     
/* 
	       if((zbuf[6]&0x3F)==0x39) // читать RAM
           {                           
             	    tmpadc_m=zbuf[8]<<8|zbuf[9];//адресRAM
					a=zbuf[10];if(a>24)a=24; // длина в байтах
					if(zbuf[7]==2) //обращение к RAM(2k)
					{
 						if ((cmd&0x01) == 1)
  						{
   							if(tmpadc_m<0400) goto PR01;
   							if(a>19)a=19;
   							for(j2=0;j2<a;j2++)
    						{
     							*((char xdata*)tmpadc_m+j2)=zbuf[11+j2] ;
    						}     
   						}
 						if ((cmd&0x02) == 2)
  						{
  		// что делать с этой строчкой??					 while(t==1);
 							for(j2=0;j2<a;j2++)
    						{
    							 bufout[6+j2]= *((char xdata*)tmpadc_m+j2) ;
  							}
						     zbuf[2]=a+7;zbuf[3]=0x02;zbuf[4]=0x20;zbuf[5]=a;//0x18;           
						     bufout[2]=zbuf[2];len=a+6;
							 
	// че то делать надо						 t = 1;//while(t==1);
						     
							 
							 if(tmpadc_m==0x04C0) 
						     {
							       *((char xdata*)tmpadc_m)=0x0FF; *((char xdata*)tmpadc_m+1)=0x0FF;
							        *((char xdata*)tmpadc_m+2)=0x0FF;*((char xdata*)tmpadc_m+3)=0x0FF;
							       *((char xdata*)tmpadc_m+4)=0; *((char xdata*)tmpadc_m+5)=0;
							        *((char xdata*)tmpadc_m+6)=0; *((char xdata*)tmpadc_m+7)=0;
	    					  } 
   						}
					}
					 PR01:
					 cmd=1;   
                 
             }
	 */
          
	/*	   if((zbuf[6]&0x3F)==0x3B) // вкл выкл активность..
           {                           
				
			//	ob_par=zbuf[7];	
			if (zbuf[7]!=0xFF)
			{	if (s_otv==0xFF)
					{s_otv=zbuf[7];
						tms=s_otv+s_otv;}
			}
			else
				{s_otv=0xFF;
				 tms=0xFF;	}
			tmo=TM_LINE+TM_LINE;	
           }
 */
           
/*		   if((zbuf[6]&0x3F)==0x3C) // рестарт модуля
           {                                                    
                  //    cmd=1;
					  while (WR==1)
					  {
					  }
			   EA = 0; 

			   WDWR=1;WDCON=0x03;
			   EA = 1; 
          }
        
       
		   if((zbuf[6]&0x3F)==0x3E) // записать прочитать RAM Clock
           {                                                    
           		if((zbuf[8]+zbuf[9])<0x3F)
  	 			{  
      				if(zbuf[9]>10) {zbuf[9]=10;} 
      				if ((cmd&0x01) == 1)//   записать 
     				{
       			//		adcbuf[0]=0xD0;
       			//		adcbuf[1]=zbuf[8]; wadc=zbuf[9]+2;
        				for (j=0;j<zbuf[9];j++)
        				{
         		//			adcbuf[j+2]=zbuf[10+j];
         				}
      				//	FUM_WR_DAT_CLOCK(adcbuf,wadc)  
     				}
      				if ((cmd&0x02) == 2)   //  читать
       				{
				//		wadc1=zbuf[8]; 
      			//		FUM_RD_DAT_CLOCK(wadc1,adcbuf,zbuf[9],wadc)
		//				if(wadc1==0x10) 
		//				{K_PAH=zbuf[12];}
        				//while(t==1);
       					for (j=0;j<zbuf[9];j++)
       					{
         		//			bufout[10+j]=adcbuf[j];
         				}
          				bufout[6]=zbuf[6];bufout[7]=zbuf[7];bufout[8]=zbuf[8];
         				bufout[9]=zbuf[9];
				        zbuf[5]=zbuf[9]+4;len=6+zbuf[5];
					}
   				}
           }
	   */
  

		 //конец ао флагу 21 аналога адц 20
	 len_o=zbuf[5]+6;
	 bufout[2]=len_o+1;


/*
 #pragma asm
 	POP PSW
	POP DPL
	POP DPH
	POP B
	POP ACC
#pragma endasm
  */

//       status=status&0xEF;
return;
}



/*************** MAIN ************/

void main (void) using 0  
{ 
xdata unsigned char fl_kal=0, kol_cik=0;
extern xdata unsigned long copy_dol;
	ES = 0;
	TR1=0;
 	EA=0;


 P0=0xFF;
 P2=0x40;
 DAC_PRIN=0;


 CFG848=0x81;
// stat_byte=stat_byte|0x01;
while (!int0)
	{kol_c=0;   //	stat_byte=stat_byte|0x10;
	}
 
 IE=0;
 IP=0x08;

 EA=0;

 if (WDS==1)
 {
 	EA=0;
  	WDWR=1;
	WDCON=0x10;
	WDS=0;
//   	stat_byte=stat_byte|0x80;
 }


 svet=0;
 rasx1_t=0;
 rasx2_t=0;
 rasx1=0;
 rasx2=0;
 fl_m1=0;
 fl_m2=0;
 cop_imp1=0;
 cop_imp2=0;
 copy_p=0x00FF;
 copy_p1=0; 
 bufcht1[0] = 0;
 bufcht1[1] = 0;
 FL_BLOK_EPROM=0;
 FCNT_SEC_V1=0;
 FCNT_SEC_V2=0;
 fcnt=0;
 CNT_SEC_V2=0;
 CNT_SEC_V1=0;
 CNT_SEC=0;
 kol_c=0;
 par=0;
 st_ser=0;
 fl_buf=0;
 fl_ds=1;
 BUF_FP_100_0=0;
 
nro=1;  
WR=0; 


setup();	

FUM_Epr_Rd((T_LADR1-0x100)>>2)

TM_LINE=EDATA2;			// 0x011D
if (TM_LINE>0x3F)
	{TM_LINE=0x3F;}
	
TM_LINE+=TM_LINE;

if (TM_LINE==0)
	{TM_LINE=1;}
 
if (EDATA4==0xCC)		// 0x011F
	r_crc=EDATA4;
else
	r_crc=0xFF;

//	r_crc=0xCC;

if (EDATA1==0x64)		// 0x011C
{
	nas1=1; nas2=1;
}
else
{	nas1=0xff; nas2=0xff;
}

FUM_Epr_Rd((LADR1-0x100)>>2)						
lineadd=EDATA1;
if (lineadd==0xFF)
	{lineadd=0x3F;
	lineadd=0x01;
	}

//lineadd_dop=EDATA1;

 aktiv=0;
 if (EDATA3==0)
	aktiv=1;

 //aktiv=1;

/*
lineaddo=EDATA2;
if (lineaddo==0xFF)
	{lineaddo=0xBF;}

*/

v_rgr=0;
if (EDATA4==0x04)
	{v_rgr=1;}		   // obem rgr 4 bytes


 FUM_Epr_Rd((FILT_RELE -0x100)>>2);
 
  POR_R1_ON=EDATA1;
  POR_R1_OFF=EDATA2;
 if (POR_R1_ON>=POR_R1_OFF)
 	{POR_R1_OFF=10;POR_R1_ON=3;}


  POR_R2_ON=EDATA3;
  POR_R2_OFF=EDATA4;
 if (POR_R2_ON>=POR_R2_OFF)
	 	{POR_R2_OFF=10;POR_R2_ON=3;}


// начало чтения 3 страницы для заполнения структуры для реагирования на пакеты от БО
	FUM_Epr_Rd((ARD_STR_PAKET_BO -0x100)>>2);

	paket_BO.linaddr_BO=EDATA1;
	
	if (paket_BO.linaddr_BO!=0xFF)
	{
		unsigned char off=0;
		lineadd_dop=paket_BO.linaddr_BO;
	//	while (EDATA1!=0xFF)
		for(off=1;off<13;off++)  
		{
			FUM_Epr_Rd(((ARD_STR_PAKET_BO+0x10*off) -0x100)>>2);
			switch (EDATA1)  //
     	{
				case 1: //    реле 1
        		{
							paket_BO.off_rele1=(EDATA2>>3)+7;
         			break;
         		}
				case 2: //    реле 2
        		{
							paket_BO.off_rele2=(EDATA2>>3)+7;
         			break;
         		}
				case 0xCC: //    цап
        		{
							paket_BO.off_dac=(EDATA2>>3)+6;
         			break;
         		}
			}
		}
	}
	
// конец чтения 3 страницы для заполнения структуры для реагирования на пакеты от БО

	for(i1=0;i1<DLINA_RELE_PRIEM;i1++)  
	{
		FUM_Epr_Rd(((ARD_BEGIN_RELE_PRIEM+0x10*i1 )-0x100)>>2);
		if (EDATA1!=0xFF)
		{		
			rele_prin[i1].linaddr=EDATA1;
			rele_prin[i1].off=EDATA2;
			rele_prin[i1].ustavka1=EDATA3;
			rele_prin[i1].ustavka1<<=8;
			rele_prin[i1].ustavka1+=EDATA4;
			
			
			FUM_Epr_Rd(((ARD_BEGIN_RELE_PRIEM+0x10*i1+4 )-0x100)>>2);
			rele_prin[i1].ustavka2=EDATA1;
			rele_prin[i1].ustavka2<<=8;
			rele_prin[i1].ustavka2+=EDATA2;
			
		}
	}

ob_par=0x00;  

TH1=R_INT_TMR1_H;
TL1=R_INT_TMR1_L;

OGR_UR=0;
	for(i1=0;i1<13;i1++)
    {
		 if (Str_CH_A[i1].NAME_PAR!=0xFF)
		 {
			 if (Str_CH_A[i1].R_IZM==0x84)		// канал 2 режим 84
			 {	H2= Str_CH_A[i1].KF_WIND;
				H2=H2*400; 
				if (nas1==1)
					nas1=i1;
			 }
	
	 		 if (Str_CH_A[i1].R_IZM==0x88)		 // канал 1 режим 88
			 {	H1= Str_CH_A[i1].KF_WIND;
				H1=H1*400; 
				if (nas2==1)
					nas2=i1;
			 }
	
			 if  (Str_CH_A[i1].R_IZM==0x60)
			 {
			 	 OGR_UR=Str_CH_A[i1].NA_P5;
			 }
	
			 if  ((Str_CH_A[i1].NA_P5&0x0F)==0x05)
			 	if ((Str_CH_A[i1].Frm_Dat&0x10)==0x10)
					fl_rgr=1;
				else
					fl_rgr=0;	
		}
 	}



	for(i1=0;i1<13;i1++)
    {	Str_CH_A[i1].KF_WIND=0xFF;
	}

	j=0;
 	for(i1=0;i1<13;i1++)
    {	if (Str_CH_A[i1].NAME_PAR!=0xFF)
		{
			
		
		Str_CH_A[i1].KF_WIND=0xFF;	
		for(j1=0;j1<21;j1++)
		{
		 if (Str_TDAT[j1].NAME_PAR!=0xFF)
			 if (Str_TDAT[j1].NAME_PAR==Str_CH_A[i1].NAME_PAR) 
			 {
			 	   Str_CH_A[i1].KF_WIND=Str_TDAT[j1].ADR_RZ;
				   break;	
			 }
		}
		}
	}

napr=0;

setup_ADC();

copy_p=P0;
if ((copy_p&MM[0])==MM[0])  {d1=1;} else {d1=0;}
if ((copy_p&MM[6])==MM[6])  {d2=1;} else {d2=0;}
d11=d1;
d22=d2;





rez=1;
task_3(0);
rez=0;
WK_1=0;
WKs=0;
copy_dol=cnt_dol;
//ADCMODE|=0x20;

TR1=0;
TL1 = R_INT_TMR1_L;//0xC4;//-200;
TH1 = R_INT_TMR1_H;//-1;
TF1=0;
ET1=1;
TR1=1;
EA = 1;
PS=1;
EADC=1;
// задержка
	while (kol_c<65000)
		kol_c++;

   		st_ser=5;
		ES=1;
//		aktiv=0;

/*	 Str_CH_A[N_K].N_RAZ;
			 tmadc=TAB_ADC[tmadc1&0x03][tmadc1>>2];
		 
			 tmadc1=(P2&0x57)|(tmadc&0xB8);
			 P2 =tmadc1;

			 SF=bx_sf1;
			 ADC0CON2 = BX_RF | (tmadc>>8); 
			 ADCMODE = BX_MD; //старт ацп 
			 */		
zz1:

 if (!fl_rest)
  {

	if (!PLLCON&0x40)
		b_err_p++;
	 EA = 0; 
	  WDWR=1;WDCON=0x32;	 // 0x32 = 125 ms   0x52= 500 ms
	 EA = 1;

  }

 if (b_err_p>100)
 	mi11=60;

 if (b_err_cl>100)
 	mi11=10;

  if (b_err_pit>100)
 	mi11=0;

	mi1++;
	if (mi1>=mi11)
  	{	if (ep2==1)
		if (fl_sv)
 			svet^=1;
		mi1=0;
	}



  /*
	if (par==0)
	{
	 //  отличие от всех прошивок - кнопки находятся тут!

		if ((!fl_tadc)&(KOL==16))
		{ xdata unsigned char i1,tmp_ch;
			for (i1=0;i1<8;i1++)
			{																														 
				 tmp_ch=Str_CH_A[i1].R_IZM;
	  			if((tmp_ch!=0x84)&(tmp_ch!=0x88)&(tmp_ch!=0x8C)&(tmp_ch!=0x50)&(tmp_ch!=0xFF)&(tmp_ch!=0xCC))
				{
				 	if (BUF_MN[i1]<1048560)
					{
						BUF_T[i1]=BUF_MN[i1]>>4;					  
					    BUF_MN[i1]=0;
					}
					else
						BUF_T[i1]=0xffff;									         
				}
			}  
		// проверка кнопок
		 
	     WK_1=0;
	      for(tmp_ch=1;tmp_ch<9;tmp_ch++)
	      {	 xdata unsigned char c_P00;
		     WK_1=WK_1>>1;     
		     P2 = P2&0x57;
			  P2 = P2|(TAB_ADC[2][tmp_ch]&0xB8); //aua?aou ioeuoeieaeni?u (ii?o ?2.5,7,3)
		    P2 = (P2&0x57)|(TAB_ADC[2][tmp_ch]&0xB8);
				c_P00=P0;
				WK_1=WK_1 |((c_P00&0x04)<<5);
	      }
	       WK_1=~WK_1;
		 
			
			tmp_ch= Str_CH_A[0].N_RAZ;
			i1=TAB_ADC[tmp_ch&0x03][tmp_ch>>2];
			tmp_ch=(P2&0x57)|(i1&0xB8);
			P2 =tmp_ch;
			SF=bx_sf1;
			ADC0CON2 = BX_RF | (i1>>8); 
			ADCMODE = BX_MD; //старт ацп 
	 
			KOL=0;
			fl_tadc=1;	
		}	
	}

	*/ 
 
 if (par==10)
 {
 //	zad=80;			// на общий 20 мс
 	zad=37;

	for (i1=0;i1<7;i1++)
	{	
 	if (BUF_vr[i1]<1048560)
	{
	
		BUF_T[i1]=BUF_vr[i1]>>2;				  
	}
	else
		BUF_T[i1]=0xffff;	
	}								         
 

	for (i1=0;i1<11;i1++)
	{
		task_3(i1);
	}
}
 else
//	zad=32;		  // на каналы по 8 мс	  а нужно по 9,1
	zad=37;
	if (int0)
	{
  	//	task_3(par);
 		par++;
	}
	else
		b_err_pit++;



	  		if (Eprom_ch==1)
			{
				data unsigned char j4;
				ES=0;
     				if ((cmd ==2)&(int0))
					{
						for (j4=0;j4<len_o;j4++)
					    {    
						 	EADRH=ED>>0x0A;
							EADRL=ED>>2;
					//		TR1=0;	
							ECON=0x01;	
					//		TR1=1;
		
	       				 	if ((j4<len_o)&((ED&0x03)==0))
								{bufout[j4+6]=EDATA1;ED++; j4++;}
						
							if ((j4<len_o)&((ED&0x03)==0x01))
								{bufout[j4+6]=EDATA2;ED++; j4++;}
						
							if ((j4<len_o)&((ED&0x03)==0x02))
								{bufout[j4+6]=EDATA3;ED++; j4++;}
						 
							if ((j4<len_o)&((ED&0x03)==0x03))
								{bufout[j4+6]=EDATA4;ED++; j4++;}
							j4--;
					  }
 						len_o =len_o+6;
					 	tmo=TM_LINE+TM_LINE; 
						WR=1;
						st_ser=20;
						bufout[2]=len_o+1; 
			}
			else 
				st_ser=10;
			  Eprom_ch=0;
			  ES=1;
			}

	  		if (Eprom_zap==1)
			{
				data unsigned char i1;
				ES=0;
 					  if ((cmd ==1)&(int0))
					  {	 
					   if (len_o!=Len_p-7)
					    {st_ser=10; goto kon1;}

						for (i1=0;i1<len_o;i1++)
					    {   
 						 	EADRH=ED>>0x0A;
							EADRL=ED>>2;

          					ECON=0x01;

							if ((i1<len_o)&((ED&0x03)==0))
								{EDATA1=zbuf[6+i1]; ED++; i1++;
								}
							
							if ((i1<len_o)&((ED&0x03)==0x01))
								{EDATA2=zbuf[6+i1];ED++; i1++;
								}

							if ((i1<len_o)&((ED&0x03)==0x02))
								{EDATA3=zbuf[6+i1];ED++; i1++;
								}

							if ((i1<len_o)&((ED&0x03)==0x03))
								{EDATA4=zbuf[6+i1];ED++; i1++;
								}
							i1--;
							TR1=0;	
							ECON=0x05;
							TR1=1;
							TR1=0;
							ECON=0x02;
							TR1=1;
						} 				  	
					  st_ser=10;
				  }

 					if ((cmd ==3)&(int0))
					{
					   
					   if (len_o!=Len_p-7)
					    {st_ser=10; goto kon1;}
					  
						for (i1=0;i1<len_o;i1++)
					    {    
						 	EADRH=ED>>0x0A;
							EADRL=ED>>2;
							ECON=0x01;	
	       				 	if ((i1<len_o)&((ED&0x03)==0))
								{EDATA1=zbuf[6+i1]; bufout[6+i1]=zbuf[6+i1]; ED++; i1++;}
							
							if ((i1<len_o)&((ED&0x03)==0x01))
								{EDATA2=zbuf[6+i1];bufout[6+i1]=zbuf[6+i1];ED++; i1++;}

							if ((i1<len_o)&((ED&0x03)==0x02))
								{EDATA3=zbuf[6+i1];bufout[6+i1]=zbuf[6+i1];ED++; i1++;}

							if ((i1<len_o)&((ED&0x03)==0x03))
								{EDATA4=zbuf[6+i1];bufout[6+i1]=zbuf[6+i1];ED++; i1++;}
							i1--;
							TR1=0;
							ECON=0x05;
							TR1=1;
							TR1=0;
							ECON=0x02;
							TR1=1;

						}

				ECON=0x04;
				if (ECON==0)
				{
					    len_o =len_o+6; 
						tmo=TM_LINE+TM_LINE; 
						WR=1;
						st_ser=20;
						bufout[2]=len_o+1; 
				}
				else
					 st_ser=10;
			}
	  kon1: 
	   Eprom_zap=0;
	   ES=1;
//	   kol_e--;
	   }



 if (par==11)
 {//	idata unsigned char j3;
 
 	par=0; 

	if (MIN%10==0)
	{
	  if (fl_kal==30)
	  	fl_kal=10;
	}
	if (MIN%10==9)
	{
	  if (fl_kal==0)
	  	  fl_kal=30;
	}
/*	
	if (fl_kal==10)
	{	idata unsigned long tmp_ln;
		extern idata unsigned long PNT_BUF_TD;

	   fl_kal=0;
		while(RDY0 ==0); 
		tmp_ln=PNT_BUF_TD; 
		RDY0 = 0;		
		ADCMODE = 0x24;//калибровка 0
		while(RDY0 ==0);  
		RDY0 = 0; 
		ADCMODE = 0x25;  //калибровка 1
		while(RDY0 ==0);  
		PNT_BUF_TD=tmp_ln;
	}
 */
	ES=0;
	lbuf_cop();
	fl_buf=1;
	ES=1;

//	status=lineadd;
//	status=paket;


/* начало выдачи пакета в активном режиме  */
chp++;
   
 

if (chp>0) {
chp=1;


	if (st_ser==5)	{

/*		else
  */
			if (aktiv)	
			{//	aktiv=0;		
				st_ser=40;
				WR=1;
				cmd=2;
				len_o=26;
				for(i=0;i<len_o;i++)	{
				 	bufout[i+6] =lbuf_dn[i];} 
				zbuf[0]=0x7e;						  
				zbuf[1]=lineadd|0x80;
			//	zbuf[1]=0x81;
				zbuf[2]=7;
				zbuf[3]=2;
				zbuf[4]=0;
				zbuf[5]=len_o;
					 
			    len_o=len_o+6;  
			//	tmo=TM_LINE+TM_LINE;
			//	st_ser=20;
				bufout[2]=len_o+1; 
				nro=1;
				SBUF=0x7E;
			}		
   
	}
}


/* конец выдачи пакета в активном режиме  */

	if (kol_cik<=50)
		kol_cik++;
	
	if (kol_cik>50)
	{	fl_sv=1;

	}
 }
 // P2=P2|0x10;

 
  while (zad!=0)
 {
  }
 

 goto zz1;                   
 }   
 
// *************return paket *******************
