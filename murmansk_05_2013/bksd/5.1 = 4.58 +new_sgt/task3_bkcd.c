/*
 ИЗМЕРИТЕЛЬНЫЙ МОДУЛЬ (BKCD ADuC 848)   2005г.
Задача3 функция измерения 8 аналоговых каналов ( период 100мс.2измерения для каждого),
8 битовый цифровой канал(состояния ключей упраыления,период обработки - 100мс)				   
*/
// FUNCTION task_3 (BEGIN)

//#include <math.h>
//#include "reg816.h"
#include "aduc848.h"
#include "r_main.h"
#include "ADC_bkcd.h"													
#include "define_stuct.h"
#include "Опис_Таб_Кан.h"


// для нового сгт
data unsigned int DAC_PRIN=0;


//extern  xdata unsigned int K1;
// xdata unsigned char DL;
 // xdata unsigned char tmp;
 //extern xdata unsigned int H1;
 idata unsigned long CMRX_K1,CMRX_K2;

 extern bit aktiv;

 idata unsigned char i11;


 xdata unsigned int st_dol;
 extern bit fl_ds;

// extern   xdata unsigned int K2;

//extern  xdata unsigned int H2; 
//extern bit fl_r22, fl_i2;
 xdata unsigned long BUF_FP_100=0;
 extern xdata unsigned int fcnt_k;
// xdata unsigned int BUF_FP_100_o=0;

extern xdata unsigned char POR_R1_ON,POR_R2_ON,POR_R1_OFF,POR_R2_OFF;
extern xdata unsigned int OGR_UR;
extern  xdata unsigned char DL;


//extern xdata unsigned char flz; // флаг защиты буфера результатов
//extern xdata unsigned int zn_ko;
extern xdata unsigned int ob_par;

extern idata unsigned long CNT_SEC_DL;

//extern idata unsigned char	z1,z2,z3,z4; // переменные для перекопирования параметра в случае его порчи
xdata unsigned char	z1=0,z2=0,z3=0,z4=0;
extern  xdata unsigned char  lbuf [LBUF_SIZE];
//extern bit rld,tld,endrx,FL_CMR;
extern data unsigned char bufcht1[2];


idata unsigned long PNT_BUF_TD=0;

xdata unsigned int Mom_tr=0, Ves_kol=0, lopatka=0;
xdata unsigned char ekran=0;

xdata unsigned int REL1_ON=0,REL1_OFF=0,REL2_ON=0,REL2_OFF=0;
xdata unsigned long copy_dol,vel_dol=0;
xdata unsigned int cnt_kol=0, cnt_ves=0;//, cnt_ves_c=4000;

bit fl_v_dol=0,fl_n=1;//FL_KOLIB=0, FL_ERR, fl_v_dol=0,fl_n=1;

//extern code unsigned int  TAB_NO_LINE_1[32],TAB_NO_LINE_2[32],TAB_NO_LINE_3[32] ;//*********************************************
extern code unsigned int  TAB_NO_LINE_25[17],TAB_NO_LINE_28[17],TAB_NO_LINE_32[17],TAB_NO_LINE_36[17];
//extern xdata unsigned long rasx1_s,rasx2_s;
//extern idata unsigned long	rasx11;
extern data unsigned int cop_imp1,cop_imp2;
//extern bit r2_v;
//extern xdata unsigned char vr;
//extern data unsigned int CM1;

//idata unsigned long CNT_1,CNT_2;

idata unsigned int CMRX2_K1=0, CMRX2_K2=0;
idata unsigned long  CMRX1_K1=0, CMRX1_K2=0,cmr=0;
//idata unsigned int MOTO_K1,MOTO_K2;

extern bit FCNT_SEC_V1, FCNT_SEC_V2,fcnt,fcnt_100;//,FCNT_V2;
extern xdata struct  TABX_CH_A Str_CH_A[13];
extern xdata unsigned char ZG_TABX_DAT[4];
//extern xdata unsigned char  BF_ZP_A[16];
extern idata unsigned int cnt_dol;
extern idata unsigned long rasx1, rasx2;//,rasx2_tm,rasx2_t;
extern data unsigned char status;
//extern void ser_int (void);
//extern void timer1int (void);
extern bit rez;
extern data unsigned int new_zn=0;

//extern xdata unsigned int kol_t,kol_kom,kol_e,kol_tsk;

code unsigned int  TAB_ADC[4][9] = {0,0,0,0,0,0,0,0,0,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8,    
                     0,0x0600,0x0608,0x0680,0x0688,0x0620,0x0628,0x00A0,0x00A8,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8};

void task_3 (unsigned char kan) //using 0
{
//	xdata unsigned int K_D2;
	xdata unsigned int pods=0;
//	idata unsigned long tmpadc_t=0;//, CM_t;
	idata unsigned char  kan_sl=0;
	idata unsigned long  BX_KPH=0; 
	idata unsigned int BX_KOD=0;
	float data  tmp2=0;
	idata unsigned char zadc=0;
	data unsigned int tmpadc=0;
	//	idata unsigned long A1;
//	idata unsigned char  tmt;
//	data unsigned int AA2,AA3;
//	data unsigned int tmadc;
	idata unsigned long TEMP_1=0;
	xdata unsigned int tmp_int=0;
	idata unsigned char i11;//,j2;
	xdata unsigned char tmp_ch=0;
	xdata unsigned char  tmp_ch2=0;
	idata unsigned int per=0;

	idata  unsigned char  wadc=0;
	idata unsigned char N_CH=0;
	idata unsigned long tm=0;
//register unsigned char i11,i1,j2;
//register unsigned char tmp_ch;
//idata unsigned long per;



//register idata unsigned char i1,j2;
//xdata unsigned char Kf_Flt;
//data unsigned long DAT_TEK;
//data unsigned int DAT_IZM;
//xdata unsigned int DAT_MAX;
//data  unsigned int tm;

   /*
 #pragma asm
	PUSH ACC
	PUSH B
	PUSH DPH
	PUSH DPL
	PUSH PSW
#pragma endasm
	
  */
 //  P2 =P2|0x10;
// kol_tsk++;
if (rez==1)
{// 	xdata unsigned char a1;
	xdata unsigned int tmadc;
	xdata unsigned char tmadc1;
	extern  data  unsigned char  N_K, KOL;
	extern  bit fl_tadc;
// for(i11=0;i11<15;i11++)
 //  {
   
   //	 BUF_S[i11]=0;
   	//	BUF_T[i11]=0x4321;
	//	BUF_M[i11]=0x1234;
	//	BUF_N[i11]=0xABCD;
	//	BUF_U[i11]=0xDCAB;
	//	BUF_FP[i11]=0x6789;
//	}
//goto PPK;
//  	zadc = BF_ZP_A[3];
//	if (zadc>8)
 
/*	
	for(a1=0;a1<13;a1++)
    {
	 wadc=Str_CH_A[a1].R_IZM;
		
     if ((wadc!=0x84)&(wadc!=0x88)&(wadc!=0x8C)&(wadc!=0x50)&(wadc!=0xFF)&(Str_CH_A[a1].NAME_PAR!=0xFF))
		{ 
		  break;	
		}
 	}
	// запуск ацепирования канала	
	SF = BX_SF;
	ADC0CON1 = BX_CON1;
	 wadc= Str_CH_A[a1].N_RAZ;
	 tmpadc=TAB_ADC[wadc&0x03][wadc>>2];
	 P2 = (P2&0x57)|(tmpadc&0xB8); //выбрать мультиплексоры (порт Р2.5,7,3)
	 ADC0CON2 = BX_RF | (tmpadc>>8); //канал ацп
	 ADCMODE = BX_MD; //RD=1;//старт АЦП  
 */
//	Str_CH_A[0].NAME_PAR=0x80;
//	Str_CH_A[0].R_IZM=0x00;
	
	KOL=0;
	fl_tadc=1;
	N_K=0;	


			 tmadc1= Str_CH_A[N_K].N_RAZ;
			 tmadc=TAB_ADC[tmadc1&0x03][tmadc1>>2];
		 
			 tmadc1=(P2&0x57)|(tmadc&0xB8);
			 P2 =tmadc1;

			 SF=bx_sf1;
			 ADC0CON2 = BX_RF | (tmadc>>8); 
			 ADCMODE = BX_MD; //старт ацп 		

			
// размер измеряемой цепочки

	for(tmp_ch=0;tmp_ch<13;tmp_ch++)
    {
		if 	((OGR_UR!=0)&(Str_CH_A[tmp_ch].NAME_PAR==OGR_UR))
		{
			 if ((Str_BX1_A[tmp_ch].TAB_BX1[1]!=0)&(Str_BX1_A[tmp_ch].TAB_BX1[0]!=0))
			 	tmp2=(float) 6*Str_BX1_A[tmp_ch].TAB_BX1[1]/7;
			 else
				 if (Str_BX1_A[tmp_ch].TAB_BX1[3]==0xFFFF)
				 	tmp2=0;
				 else
				 	tmp2=(float) 6*Str_BX1_A[tmp_ch].TAB_BX1[3]/7;
/*
			 if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
			 	 tmp2=tmp2*1000;
			 if ((Str_CH_A[N_CH].Frm_Dat&0x80)==0x80)
			 	 tmp2=tmp2*100;
			 if ((Str_CH_A[N_CH].Frm_Dat&0x40)==0x40)
			 	 tmp2=tmp2*10;
  */
			 OGR_UR=(int) (tmp2+0.5);
		
		}
		 BUF_S[tmp_ch]=0;	 
		 BUF_T[tmp_ch] =0; 
		 BUF_N[tmp_ch] =0;
		 BUF_U[tmp_ch] =0;
		 BUF_FP[tmp_ch]=0;
	}
	fcnt_k=0;
	st_dol=cnt_dol;

  goto PPK;
}
//     status=status|0x02;

//if (kan>zadc)
//{
// 	kan=0;
//}
		  // (i1!=0x50)&
 


// status++;

//}

if (ob_par!=0x00)
{ data unsigned char g,g1;
  xdata unsigned char  adcbuf[6];
  extern xdata unsigned char b_err_cl;	
/* if ((ob_par&0x0080)==0x0080)
 {	 
    cnt_dol=0;
	CMRX1_K1=0;
	CMRX2_K1=0;
	CMRX1_K2=0;
	CMRX2_K2=0;
	Ves_kol=0;
	Mom_tr=0;
	cmr=0;
	ob_par=ob_par&0xFFEF;

					adcbuf[0]=0xD0;
					adcbuf[1]=0x1A;  
					adcbuf[2]=cnt_dol>>8; adcbuf[3]=cnt_dol;
					FUM_WR_DAT_CLOCK(adcbuf,4)
					adcbuf[0]=0xD0;
					adcbuf[1]=0x1C;  
					adcbuf[2]=CMRX1_K1>>24;adcbuf[3]=CMRX1_K1>>16;
					adcbuf[4]=CMRX1_K1>>8;adcbuf[5]=CMRX1_K1;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					adcbuf[0]=0xD0;
					adcbuf[1]=0x20;  
					adcbuf[2]=CMRX1_K2>>24;adcbuf[3]=CMRX1_K2>>16;
					adcbuf[4]=CMRX1_K2>>8;adcbuf[5]=CMRX1_K2;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					adcbuf[0]=0xD0;
					adcbuf[1]=0x24;  
					adcbuf[2]=Mom_tr>>8; adcbuf[3]=Mom_tr;
					adcbuf[4]=Ves_kol>>8; adcbuf[5]=Ves_kol;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					adcbuf[0]=0xD0;
					adcbuf[1]=0x28;  
					adcbuf[2]=cmr>>24; adcbuf[3]=cmr>>16;
					adcbuf[4]=cmr>>8; adcbuf[5]=cmr;
					FUM_WR_DAT_CLOCK(adcbuf,6)	
 }
*/	if 	 ((ob_par&0x0001)==0x0001)	   // обнулить объем аналоговый
		{	
			if (fl_ds)
			{
				extern  idata unsigned int CNT_SEC;
				extern xdata unsigned int BUF_FP_100_0;
				fl_ds=0;
				cmr=0;CNT_SEC=0;BUF_FP_100_0=0;fcnt_k=0;ob_par=ob_par&0xFFFE;
				adcbuf[0]=0xD0;
				adcbuf[1]=0x28;  
				adcbuf[2]=cmr>>24; adcbuf[3]=cmr>>16;
				adcbuf[4]=cmr>>8; adcbuf[5]=cmr;
				FUM_WR_DAT_CLOCK(adcbuf,6)		
				fl_ds=1;
			}
		}


		if 	 ((ob_par&0x0002)==0x0002)		// обнулить объем насоса 1
		{
			if (fl_ds)
			{
						fl_ds=0;
						CMRX1_K1=0;CMRX2_K1=0;ob_par=ob_par&0xFFFD;
						adcbuf[0]=0xD0;
						adcbuf[1]=0x1C;  
						adcbuf[2]=CMRX1_K1>>24;adcbuf[3]=CMRX1_K1>>16;
						adcbuf[4]=CMRX1_K1>>8;adcbuf[5]=CMRX1_K1;
						FUM_WR_DAT_CLOCK(adcbuf,6)
						fl_ds=1;
 			}
			//		aktiv=~aktiv;
		}
		//zn_ko;}
		if 	 ((ob_par&0x0004)==0x0004)		// обнулить объем насаса 2
		{
			if (fl_ds)
			{
						fl_ds=0;
						CMRX1_K2=0;CMRX2_K2=0;ob_par=ob_par&0xFFFB;
						adcbuf[0]=0xD0;
						adcbuf[1]=0x20;  
						adcbuf[2]=CMRX1_K2>>24;adcbuf[3]=CMRX1_K2>>16;
						adcbuf[4]=CMRX1_K2>>8;adcbuf[5]=CMRX1_K2;
						FUM_WR_DAT_CLOCK(adcbuf,6)
						fl_ds=1;
			}
		}

	/*			if 	 ((ob_par&0x0008)==0x0008)		// обнулить тальблок
				{  
		 			cnt_dol=0;	 
					ob_par=ob_par&0xFFF7;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x1A;  
					adcbuf[2]=cnt_dol>>8; adcbuf[3]=cnt_dol;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}

				if 	 ((ob_par&0x0010)==0x0010)		// обнулить колонны
				{
					Ves_kol=0;	   ob_par=ob_par&0xFFEF;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x26;  
					adcbuf[2]=Ves_kol>>8; adcbuf[3]=Ves_kol;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}		
		*/
				if 	 ((ob_par&0x0020)==0x0020)		//  обнулить момент трения
				{
			/*		Mom_tr=0;		 ob_par=ob_par&0xFFDF;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x24;  
					adcbuf[2]=Mom_tr>>8; adcbuf[3]=Mom_tr;
					FUM_WR_DAT_CLOCK(adcbuf,4) 
			  */
					aktiv=~aktiv;
					ob_par=ob_par&0xFFDF;
				
				}	 

				if 	 ((ob_par&0x0800)==0x0800)		// установить тальблок
				{
					if (fl_ds)
					{
					data unsigned char k=0,k1=0;
					data unsigned long  P1=0,P2=0;
					fl_ds=0;
					for (k=0;k<13;k++)
						if ((Str_CH_A[k].R_IZM==0x8C))
						{ break;}

				 	if (k<13)	
						if (new_zn>=Str_BX1_A[k].TAB_BX1[k1+1])       
			 		 	{   	idata unsigned long tmpadc_t=0; 
					
						 	wadc= Str_BX1_A[k].ZGL_BX1_A[3];                       
			 				while ((new_zn>Str_BX1_A[k].TAB_BX1[k1+3])&(k1<wadc))    
				  	        {                         
				  		        k1= k1+2;  
							}     
						
							if (k1>=wadc)
				           		cnt_dol=Str_BX1_A[k].TAB_BX1[wadc];   
							else
							{
								if (new_zn!=Str_BX1_A[k].TAB_BX1[k1+3])
								{				             
						           P1=Str_BX1_A[k].TAB_BX1[k1+2]-Str_BX1_A[k].TAB_BX1[k1]; 
						           P2=new_zn-Str_BX1_A[k].TAB_BX1[k1+1];     
						           P1=P1*P2;      
						           tmpadc_t=Str_BX1_A[k].TAB_BX1[k1+3]-Str_BX1_A[k].TAB_BX1[k1+1];  
						           tmp2=(float) P1/tmpadc_t;
								   P1=(long) (tmp2+0.5);       
						           cnt_dol=(int) P1+Str_BX1_A[k].TAB_BX1[k1]; 
								}
								else
								  cnt_dol=Str_BX1_A[k].TAB_BX1[k1+2];
							}                                   
						 }  
						 else
						 {
						 	cnt_dol=Str_BX1_A[k].TAB_BX1[k1];
						 }   			  					
					
						ob_par=ob_par&0xF7FF;
						adcbuf[0]=0xD0;
						adcbuf[1]=0x1A;  
						adcbuf[2]=cnt_dol>>8; adcbuf[3]=cnt_dol;
						FUM_WR_DAT_CLOCK(adcbuf,4)
						fl_ds=1;
					}
				}

				if 	 ((ob_par&0x1000)==0x1000)		// установить колонны
				{
					if (fl_ds)
					{	fl_ds=0;
						Ves_kol=new_zn;	   ob_par=ob_par&0xEFFF;
						adcbuf[0]=0xD0;
						adcbuf[1]=0x26;  
						adcbuf[2]=Ves_kol>>8; adcbuf[3]=Ves_kol;
						FUM_WR_DAT_CLOCK(adcbuf,4)
						fl_ds=1;
					}
				}

				
	/*
				if 	 ((ob_par&0x2000)==0x2000)		//  установить момент трения
				{
					Mom_tr=new_zn;		 ob_par=ob_par&0xDFFF;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x24;  
					adcbuf[2]=Mom_tr>>8; adcbuf[3]=Mom_tr;
					FUM_WR_DAT_CLOCK(adcbuf,4) 
				}
	 */
}

	
if (kan==10)
{  	data unsigned char g,g1;
	data unsigned char  adcbuf[6];
	extern	xdata unsigned char WK_1,WKs;
	kan=0;
/*
   while(RDY0 ==0); 
     WK_1=0;
      for(tmp_ch=1;tmp_ch<9;tmp_ch++)
      {	 xdata unsigned char c_P0;
	     WK_1=WK_1>>1;     
	     P2 = P2&0x57;
		  P2 = P2|(TAB_ADC[2][tmp_ch]&0xB8); //aua?aou ioeuoeieaeni?u (ii?o ?2.5,7,3)
	    P2 = (P2&0x57)|(TAB_ADC[2][tmp_ch]&0xB8);
			c_P0=P0;
			WK_1=WK_1 |((c_P0&0x04)<<5);
      }
       WK_1=~WK_1;
*/	   
/*
	   if ((WK_1&0x01)==0x01) //eiiiea IAA?OCEA
	   {
		if (fl_ds)
		{	fl_ds=0;
			zadc = 13;
			N_CH=zadc;
			for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
			{	
				wadc=Str_CH_A[tmp_ch].NA_P5;
				if (wadc==0x50)
				{	Ves_kol=BUF_FP[tmp_ch];
		
					adcbuf[0]=0xD0;
					adcbuf[1]=0x26;  
					adcbuf[2]=Ves_kol>>8; adcbuf[3]=Ves_kol;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}

				if (wadc==0x60)
				{	Mom_tr=BUF_FP[tmp_ch];
					adcbuf[0]=0xD0;
					adcbuf[1]=0x24;  
					adcbuf[2]=Mom_tr>>8; adcbuf[3]=Mom_tr;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}
			}
			fl_ds=1;
		}
	   }

	   if ((WK_1&0x02)==0x02) //eiiiea IAA?OCEA
	   {
		 cnt_dol=0;
	   }
 */

/*	   if (((WK_1&0x40)==0x40)&(fl_n=1)) //eiiiea IAA?OCEA
	   {
		 if (cnt_ves_c==20000)
		 	cnt_ves_c=8000;
		 else
			 if (cnt_ves_c==8000)
			 	cnt_ves_c=4000;
			 else
				 if (cnt_ves_c==4000)
				 	cnt_ves_c=2000;					  
				 else
					 if (cnt_ves_c==2000)
					 	cnt_ves_c=1000;
					 else
						 if (cnt_ves_c==1000)
						 	cnt_ves_c=500;
						 else
							 if (cnt_ves_c==500)
							 	cnt_ves_c=20000;
		   cnt_ves=0;
		   fl_n=0;
		}
	   if ((WK_1&0x08)==0x08) //eiiiea IAA?OCEA
		{fl_n=1;}
  */

	   	// начало обработки кнопок пульта нового
  	 if (WKs!=WK_1)	
	   {
	   		extern xdata unsigned char ekran;

			if 	((WK_1&0x1f)==0x07)	 // 	экран
			{ 	if (fl_ds)
				{ data unsigned char g,g1;
				  xdata unsigned char  adcbuf[6];
				  xdata unsigned char tmp_ch=0;
				  extern xdata unsigned char b_err_cl;	
				  bit l1=ekran&0x01;	
				  bit l2=ekran&0x02;

					if (l1&l2)			//   l2=1	l1=1	
					{ekran&=0xFD;}
					else
						if (l1)			//	 l2=0	l1=1
						{ekran|=0x02;ekran&=0xFE;}
						else			//	 l2=1	l1=0
							{ekran|=0x01;}
 
					fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x33;  
					adcbuf[2]=ekran; 
 					FUM_WR_DAT_CLOCK(adcbuf,3)
					fl_ds=1;
			}	}


			if 	((WK_1&0x1f)==0x06)	 //    яркость
			{ 	if (fl_ds)
				{ data unsigned char g,g1;
				  xdata unsigned char  adcbuf[6];
				  xdata unsigned char tmp_ch=0;
				  extern xdata unsigned char b_err_cl;	
				  bit l1=ekran^0;	
				  bit l2=ekran^1;

  					g=ekran>>4;
					g++;
					ekran=(ekran&0x0F)|(g<<4);
					fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x33;  
					adcbuf[2]=ekran; 
 					FUM_WR_DAT_CLOCK(adcbuf,3)
					fl_ds=1;
			}	}

		   if 	((WK_1&0x1f)==0x02)	  //сброс тальблока
		   {
		//	 cnt_dol=0;
	//		 copy_dol=0;
		   }

		   if 	((WK_1&0x1f)==0x01)	  //нагрузка
		   {
		if (fl_ds)
		{	fl_ds=0;
			zadc = 13;
			N_CH=zadc;
			for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
			{	
				wadc=Str_CH_A[tmp_ch].NA_P5;
				if (wadc==0x50)
				{	Ves_kol=BUF_FP[tmp_ch];
		
					adcbuf[0]=0xD0;
					adcbuf[1]=0x26;  
					adcbuf[2]=Ves_kol>>8; adcbuf[3]=Ves_kol;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}

				if (wadc==0x60)
				{	Mom_tr=BUF_FP[tmp_ch];
					adcbuf[0]=0xD0;
					adcbuf[1]=0x24;  
					adcbuf[2]=Mom_tr>>8; adcbuf[3]=Mom_tr;
					FUM_WR_DAT_CLOCK(adcbuf,4)
				}
			}
			fl_ds=1;
		   }
		   }

			if ((WK_1&0x1f)==0x05)	 // лопатка
			{
				fl_ds=0;
				zadc = 13;
				N_CH=zadc;
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{	wadc=Str_CH_A[tmp_ch].NA_P5;
					if (wadc==0x20)
					{	lopatka=BUF_FP[tmp_ch];
					
						adcbuf[0]=0xD0;
						adcbuf[1]=0x34;  
						adcbuf[2]=lopatka>>8; adcbuf[3]=lopatka;
						FUM_WR_DAT_CLOCK(adcbuf,4)
					}
				}
				fl_ds=1;				 			
			}

 /*
			if ((WK_1&0x1f)==0x01)	 // рестарт
			{
				extern bit fl_rest;
				fl_rest=1;
				EA = 0; 
				WDWR=1;WDCON=0x02;	 // 500 ms
				EA = 1; 			
			}

			if ((WK_1&0x1f)==0x02)	 // актив
			{
				aktiv=~aktiv;			
			}
 			
			
			if ((WK_1&0x1f)==0x07)	 // сумма
			{	extern data unsigned char r_crc;
				if (r_crc==0xCC)
				{r_crc=0xff;}
				else
				{r_crc=0xCC;}
			}
   */
			WKs=WK_1;
		}
		// конец обрабтки кнопок пульта нового

//		z0=0;
 	while (Str_TDAT[kan].NAME_PAR!=0xFF)   
	{  	   		
		i11=Str_TDAT[kan].ADR_RZ>>3;
		if (i11>=28)
			goto PR;
		if (Str_TDAT[kan].NAME_PAR>=0x80)
			if ((Str_TDAT[kan].NAME_PAR&0x0F)==0x00)
				goto PR;

     tmp_ch2=Str_TDAT[kan].NAME_PAR;

	 //  рассчетный параметр часы
	 if ((tmp_ch2==0x7F)&(i11+3<28))	  // ?anu
	 {
//		 z1=HOUR;
//		 z2=MIN;
//		 z3=SEC;
//		 z4=HTHSEC;
	//	 i11=Str_TDAT[kan].ADR_RZ>>3;
//		z0=4;
//		flz=i11;
		 lbuf[i11]=HOUR;
		 lbuf[i11+1]=MIN;
		 lbuf[i11+2]=SEC;
		 lbuf[i11+3]=HTHSEC;
//		 flz=0xFF;
	 }

	 if (tmp_ch2==0xCC)	  // ?anu
	 {	 extern xdata unsigned char  stat_byte;
		 lbuf[i11]=stat_byte;
		 stat_byte=1;
	 }


	 if (tmp_ch2==0x10)	  // ?anu
	 {	
		 lbuf[i11]=(char) ~RELE1;
		 lbuf[i11+1]=(char) ~RD;
		 
		 /*
		 if (RELE1==1)
				lbuf[i11]=0;
		 else
			  lbuf[i11]=1;
		if (RD==1)
				lbuf[i11+1]=0;
		 else
			  lbuf[i11+1]=1;
		 */
	 }	 
	 
	 //  расссчетный параметр 1 байт - переключение экрана для ИТП 2 байт - состояние кнопок пульта
	 if (tmp_ch2==0x40)	 //ioeuo
	 {	 
		extern xdata unsigned char ekran;

		lbuf[i11]=ekran;
		lbuf[i11+1]=WK_1;

	 }

	 if ((tmp_ch2 & 0x0F)==0x01)	 //  
	 { // только для формата хода!
		 		
	    zadc = 13;
			
		N_CH=zadc;
		for (tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if ((Str_CH_A[tmp_ch].NAME_PAR==(tmp_ch2&0xF0))&((Str_CH_A[tmp_ch].R_IZM==0x88)|(Str_CH_A[tmp_ch].R_IZM==0x84)))
			{N_CH=tmp_ch; break;
			}
		}

 		if (N_CH!=zadc)
	    {	 // только формат хода

			 z1=lbuf[i11]&0xFC;
			 z1=z1|((Str_CH_A[N_CH].Frm_Dat&0x30))>>4;
			 lbuf[i11]=z1;
		}
	 }

 /*	 if (tmp_ch2 == )	 //  
	 {	extern data unsigned long   rasxi_2;
	//	xdata unsigned char t1;

	//	for (t1=0;t1<10;t1++)
	//	{
	//		if (Str_CH_A[t1].R_IZM==0x60)//режим измерения из описания анал.канала (уровень)60
	 	lbuf[i11]=rasxi_2>>24;
		lbuf[i11+1]=rasxi_2>>16;
	 	lbuf[i11+2]=rasxi_2>>8;
		lbuf[i11+3]=rasxi_2;

	//	}


	 }

	 if (tmp_ch2 ==0x20)	 //  
	 {	//	extern data unsigned long		   rasxi_2;
	 xdata unsigned int t=0;
	 extern idata unsigned long delt_r2;
	 extern xdata unsigned int imp2;
//	 t=cop_imp2;
//	 t=imp2;
		lbuf[i11]=cop_imp2>>8;
		lbuf[i11+1]=cop_imp2;
	}
 
	 if (tmp_ch2 ==0x30)	 //  
	 {	
	// xdata unsigned int t=0;
//	 extern data unsigned long rasxi_2;
//	t=rasx2;
		lbuf[i11]=rasx2>>8;
		lbuf[i11+1]=rasx2;
	 }
  */
 /*	 if ((tmp_ch2 & 0xFF)==0x40)	 //  
	 {
	 	xdata unsigned int t=0;
	 	 extern data unsigned long rasxti_2;
		t= rasxti_2;
		lbuf[i11]=t>>8;
		lbuf[i11+1]=t;
	 }


	 if ((tmp_ch2 & 0x0F)==0x02)	 //  
	 {
//		flz=i11;
//		lbuf[i11]=z1;
//		lbuf[i11+1]=z2;
//		flz=0xFF;	 
	 }
 */
 	 if ((tmp_ch2 & 0x0F)==0x03)	 //  ??????? ????????? ????????? 
	 {
		zadc = 13;
		N_CH=zadc;
		for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if (Str_CH_A[tmp_ch].NA_P3==tmp_ch2)
			{N_CH=tmp_ch; break;
			}
		}

 		if (N_CH!=zadc)
	    {	xdata unsigned char c_P0;	 
			extern	xdata unsigned char  BUF_PIT[7];
		// формат основного параметра и расхода
			 z1=lbuf[i11]&0xFC;
			 z1=z1|((Str_CH_A[N_CH].Frm_Dat&0xC0))>>6;
			 lbuf[i11]=z1;

		// контроль питания
/*
   			while(RDY0 ==0); 
	  
    		wadc= Str_CH_A[N_CH].N_RAZ;
			tmpadc=TAB_ADC[wadc&0x03][wadc>>2];
			P2 = (P2&0x57)|(tmpadc&0xB8); //??????? ?????????????? (???? ?2.5,7,3)
			z1=lbuf[i11]&0xCF;
			c_P0=P0;
*/			c_P0=BUF_PIT[N_CH];
			z1=z1|((c_P0&0x03)<<4);  // для аналоговых	 00XX.0000
			lbuf[i11]=z1;
	
			 // превышения порогов	   XX00.0000
			z1=lbuf[i11]&0x3F;

		 if (Str_BX_A[N_CH].ZGL_BX_A[0]==Str_CH_A[N_CH].NAME_PAR)
				 {
					if (Str_BX_A[N_CH].TAB_BX[4]<=BUF_FP[N_CH])
						 z1=z1|0xC0;
					else
			  		{	if (Str_BX_A[N_CH].TAB_BX[2]<=BUF_FP[N_CH])
							z1=z1|0x80;
						else
							if (Str_BX_A[N_CH].TAB_BX[0]<=BUF_FP[N_CH])
								 z1=z1|0x40;
					}
				 }
			 lbuf[i11]=z1;
		}
	 }


	 if ((tmp_ch2 & 0x0F)==0x04)	 //  ??????? ????????? ???????????? 
	 {
		zadc = 13;
		N_CH=zadc;
		for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if (Str_CH_A[tmp_ch].NAME_PAR==(tmp_ch2&0xF0))
			{N_CH=tmp_ch; break;
			}
		}
	 
 		if (N_CH!=zadc)
	    {
	    // формат расчетного параметра	  и суммарнного рассхода
		//	 i11=Str_TDAT[kan].ADR_RZ>>3;
		 	 z1=lbuf[i11]&0xFC;
             z1=z1|((Str_CH_A[N_CH].Frm_Dat&0x0C)>>2);
			 lbuf[i11]=z1;
		}
	 }

	 if ((tmp_ch2 & 0x0F)==0x05)	 // расчетный параметр являющийся сумой основного  
	 {	
		extern bit v_rgr;
		zadc = 13;
		N_CH=zadc;
		for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if (Str_CH_A[tmp_ch].NAME_PAR==(tmp_ch2&0xF0))
			{N_CH=tmp_ch; break;
			}
		}

 		if (N_CH!=zadc)
	    {  extern  idata unsigned int CNT_SEC;

		   if (fcnt==1)	
		   { 
		   	  fcnt=0;
			  if  (BUF_FP[N_CH]!=0)
			  {
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x02)==0x02)
				{										// литры в минуту это
					TEMP_1=0;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
					{
					  tmp2=BUF_FP[N_CH]*100;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
					{
					  tmp2=BUF_FP[N_CH]*10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
					{
					  tmp2=BUF_FP[N_CH];
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
					{
					  tmp2=BUF_FP[N_CH]/10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
					cmr+=TEMP_1;
				}
				else
				{
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
						cmr+=BUF_FP[N_CH]*100;	 
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
						cmr+=BUF_FP[N_CH]*10;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
						cmr+=BUF_FP[N_CH];	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
						cmr+=BUF_FP[N_CH]/10;	
				}
				if (fl_ds)
				{	fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x28;  
					adcbuf[2]=cmr>>24; adcbuf[3]=cmr>>16;
					adcbuf[4]=cmr>>8; adcbuf[5]=cmr;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
				}
			  }
		   }

		   	 	if (cmr>=1000000000)
					{cmr=1000000000; }

		if ((Str_CH_A[N_CH].Frm_Dat&0x01)==0x01)
		{
				Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat&0xF3;
			 	if (cmr<1000000)
					{tmp_int=cmr/100; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x0C;}
				else
				 	if (cmr<10000000)
						{tmp_int=cmr/1000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x08;}
					else
					 	if (cmr<100000000)
							{tmp_int=cmr/10000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x04;}
						else
						 	if (cmr<1000000001)
								{tmp_int=cmr/100000; }
		}
		else
		{
			if 	((Str_CH_A[N_CH].Frm_Dat&0x10)==0x00)		   // раз в секунду увеличение объема
			{
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
				 	  tmp_int=cmr/100000;			   //  объем выводится в кубометрах без запятых
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
					   if (cmr>655350000)
					   		 tmp_int=0xFFFF;
					   else
				 	  tmp_int=cmr/10000;  		   //  объем выводится в кубометрах	  с одной запятой
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
					   if (cmr>65535000)
					   		 tmp_int=0xFFFF;
					   else
				 	  tmp_int=cmr/1000;			  //  объем выводится в кубометрах  с двумя запятыми
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
					   if (cmr>6553500)
					   		 tmp_int=0xFFFF;
					   else
				 	  tmp_int=cmr/100; 			  //  объем выводится в кубометрах  с тремя запятыми
			}
			else
			{											  //  увеличение объема	  каждые 100 мс
		   	 	if (cmr>=1000000000)
					{cmr-=1000000000; }

				if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
			 		tmp2=(float)cmr/100000;			   //  объем выводится в кубометрах без запятых
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
		 	  		tmp2=(float)cmr/10000;  		   //  объем выводится в кубометрах	  с одной запятой
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
					tmp2=(float)cmr/1000;			  //  объем выводится в кубометрах  с двумя запятыми
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
					tmp2=(float)cmr/100; 			  //  объем выводится в кубометрах  с тремя запятыми

				tmp_int=(int)(tmp2+0.5);
				if ((fl_ds)&(SEC%2)&(BUF_FP_100_0!=0))
				{	fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x28;  
					adcbuf[2]=cmr>>24; adcbuf[3]=cmr>>16;
					adcbuf[4]=cmr>>8; adcbuf[5]=cmr;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
				}		
			}
		}
		if (v_rgr)
		{
			lbuf[i11]=cmr>>24;
			lbuf[i11+1]=cmr>>16;
			lbuf[i11+2]=cmr>>8;
			lbuf[i11+3]=cmr;			
		}
		else
		{
	 		lbuf[i11]=tmp_int>>8;
			lbuf[i11+1]=tmp_int;
		}
	  }
   }

	 // anee a no?iea iienaiey  auoiaiuo   aaiiuo anou eiaia ia?aiao?ia ieai?eaa?ueony ia o7  
	 // iiea n?eoaai ?oi yoi noiia?iua ?anoiau ii au?eneyaiiio ia?aiao?o oeo? eaiaea 1

	 if ((tmp_ch2 & 0x0F)==0x07)	 //  	 канал два по режиму 84
	 {
		zadc = 13;
		N_CH=zadc;
		for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if (Str_CH_A[tmp_ch].NA_P5==tmp_ch2)
			{N_CH=tmp_ch; break;
			}
		}
		if (N_CH!=zadc)
	    {  extern data unsigned char    nas1;
		if (FCNT_SEC_V2==1)
	    {	FCNT_SEC_V2=0;
			if (BUF_FP[N_CH]!=0)
			{ 

				// суммирование расхода  с точностью до десятков мл с учетом расхода
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x02)==0x02)
				{										// литры в минуту это
					TEMP_1=0;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
					{
					  tmp2=BUF_FP[N_CH]*100;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
					{
					  tmp2=BUF_FP[N_CH]*10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
					{
					  tmp2=BUF_FP[N_CH];
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
					{
					  tmp2=BUF_FP[N_CH]/10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
					CMRX1_K1+=TEMP_1;
				}
				else				// литры в секунду это
				{
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)	// суммируем в литрах?
						CMRX1_K1+=BUF_FP[N_CH]*100;	 
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)   // суммируем в литрах ?
						CMRX1_K1+=BUF_FP[N_CH]*10;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)   // суммируем в литрах ?
						CMRX1_K1+=BUF_FP[N_CH];	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)   // суммируем в литрах ?
						CMRX1_K1+=BUF_FP[N_CH]/10;	
				}

				if (fl_ds)
				{	fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x1C;  
					adcbuf[2]=CMRX1_K1>>24;adcbuf[3]=CMRX1_K1>>16;
					adcbuf[4]=CMRX1_K1>>8;adcbuf[5]=CMRX1_K1;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
				}
				  CMRX1_K1+=BUF_FP[N_CH];
			}  
		}
		
		if (nas1!=0xff)	 // po 100ms
		{	    idata unsigned int temp2;
			//	CMRX1_K1+=CMRX_K1;
			//	CMRX_K1=0;
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x02)==0x02)
				{										// литры в минуту это
					TEMP_1=0;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
					{
					 // tmp2=BUF_FP[N_CH]*100;
					  tmp2=CMRX1_K1*10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
					{
					//  tmp2=BUF_FP[N_CH]*10;
					  tmp2=CMRX1_K1;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
					{
					 // tmp2=BUF_FP[N_CH];
					  tmp2=CMRX1_K1/10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
					{
					 // tmp2=BUF_FP[N_CH]/10;
					 tmp2=CMRX1_K1/100;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
					CMRX2_K1=TEMP_1;
				}
				else				// литры в секунду это
				{
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)	// суммируем в литрах?
						CMRX2_K1=CMRX1_K1*10;	 
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)   // суммируем в литрах ?
						CMRX2_K1=CMRX1_K1;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)   // суммируем в литрах ?
						CMRX2_K1=CMRX1_K1/10;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)   // суммируем в литрах ?
						CMRX2_K1=CMRX1_K1/100;	
				}

				 	if (CMRX2_K1>=1000000000)
						{CMRX2_K1=1000000000; }
			if ((Str_CH_A[N_CH].Frm_Dat&0x01)==0x01)
			{
					Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat&0xF3;
				 	if (CMRX2_K1<1000000)
						{temp2=CMRX2_K1/100; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x0C;}
					else
					 	if (CMRX2_K1<10000000)
							{temp2=CMRX2_K1/1000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x08;}
						else
						 	if (CMRX2_K1<100000000)
								{temp2=CMRX2_K1/10000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x04;}
							else
							 	if (CMRX2_K1<1000000001)
									{temp2=CMRX2_K1/100000; }
				
			}
			else
			{
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
				 	  temp2=CMRX2_K1/100000;			   //  объем выводится в кубометрах без запятых
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
					   if (CMRX2_K1>655350000)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K1/10000;  		   //  объем выводится в кубометрах	  с одной запятой
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
					   if (CMRX2_K1>65535000)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K1/1000;			  //  объем выводится в кубометрах  с двумя запятыми
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
					   if (CMRX2_K1>6553500)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K1/100; 			  //  объем выводится в кубометрах  с тремя запятыми
			}

			if ((BUF_FP[N_CH]!=0)&(SEC%2)&(fl_ds))		  
			{
				//	CMRX1_K1+=CMRX_K1;
				//	CMRX_K1=0;   
 					fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x1C;  
					adcbuf[2]=CMRX1_K1>>24;adcbuf[3]=CMRX1_K1>>16;
					adcbuf[4]=CMRX1_K1>>8;adcbuf[5]=CMRX1_K1;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
				//	temp2=0;
			}
				if (i11<0xE0)
				{  	
			 		lbuf[i11]=BUF_FP[N_CH]>>8;;
					lbuf[i11+1]=BUF_FP[N_CH];;
	 				lbuf[i11+2]=temp2>>8;
					lbuf[i11+3]=temp2;		
				}
		}
		else
		{								

				 	if (CMRX1_K1>=1000000000)
						{CMRX1_K1=1000000000; }
			if ((Str_CH_A[N_CH].Frm_Dat&0x01)==0x01)
			{
					Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat&0xF3;
				 	if (CMRX1_K1<1000000)
						{CMRX2_K1=CMRX1_K1/100; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x0C;}
					else
					 	if (CMRX1_K1<10000000)
							{CMRX2_K1=CMRX1_K1/1000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x08;}
						else
						 	if (CMRX1_K1<100000000)
								{CMRX2_K1=CMRX1_K1/10000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x04;}
							else
							 	if (CMRX1_K1<1000000001)
									{CMRX2_K1=CMRX1_K1/100000; }
				
			}
			else
			{
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
				 	  CMRX2_K1=CMRX1_K1/100000;			   //  объем выводится в кубометрах без запятых
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
					   if (CMRX1_K1>655350000)
					   		 CMRX2_K1=0xFFFF;
					   else
				 	  CMRX2_K1=CMRX1_K1/10000;  		   //  объем выводится в кубометрах	  с одной запятой
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
					   if (CMRX1_K1>65535000)
					   		 CMRX2_K1=0xFFFF;
					   else
				 	  CMRX2_K1=CMRX1_K1/1000;			  //  объем выводится в кубометрах  с двумя запятыми
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
					   if (CMRX1_K1>6553500)
					   		 CMRX2_K1=0xFFFF;
					   else
				 	  CMRX2_K1=CMRX1_K1/100; 			  //  объем выводится в кубометрах  с тремя запятыми
			}

				if (i11<0xE0)
				{  	
			 		lbuf[i11]=BUF_FP[N_CH]>>8;;
					lbuf[i11+1]=BUF_FP[N_CH];;
	 				lbuf[i11+2]=CMRX2_K1>>8;
					lbuf[i11+3]=CMRX2_K1;		
				}
		}
   
  /* if (FCNT_SEC_V2==1)
	    {	FCNT_SEC_V2=0;
			CMRX1_K1+=BUF_FP[N_CH];
			CMRX2_K1=CMRX1_K1;
		}
  if (nas1!=0xff)
  {
 			CMRX2_K1=CMRX1_K1/10; 
  }
				 	lbuf[i11]=BUF_FP[N_CH]>>8;;
					lbuf[i11+1]=BUF_FP[N_CH];;
	 				lbuf[i11+2]=CMRX2_K1>>8;
					lbuf[i11+3]=CMRX2_K1;
*/
	  }
	 }

	 if ((tmp_ch2 & 0x0F)==0x09)	 //   прибавление объема по ходам насоса 
	 {	   	
		zadc = 13;
		N_CH=zadc;	
		for (tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		{
			if (Str_CH_A[tmp_ch].NA_P5==tmp_ch2)
			{N_CH=tmp_ch; break;}
		}
		if (N_CH!=zadc)
		{ 
		extern data unsigned char nas2;
		if (FCNT_SEC_V1==1)
	    {	FCNT_SEC_V1=0;
		 	
			if (BUF_FP[N_CH]!=0)
			{
				// суммирование расхода  с точностью до десятков мл с учетом расхода
				// приводим текущую точность расхода к десяткам мл/с
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x02)==0x02)
				{	data unsigned long TEMP_l;
					float idata tmp_p;
					TEMP_l=0;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
					{
					  tmp_p=BUF_FP[N_CH]*100;					// л/с в формате без запятых  т.о л/с
					  tmp_p=tmp_p/60;
					  tmp2=tmp2+0.5;
					  TEMP_l=(long) tmp_p;
					}
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
					{
					  tmp_p=BUF_FP[N_CH]*10;
					  tmp_p=tmp_p/60;					   // л/с в формате с запятой то есть точность до десятых	 т.о. десяты
					  tmp2=tmp2+0.5;
					  TEMP_l=(long) tmp_p;
					}	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
					{
					  tmp_p=BUF_FP[N_CH];
					  tmp_p=tmp_p/60;					 // л/с в формате с двумя запятыми то есть точность до сотых
					  tmp2=tmp2+0.5;
					  TEMP_l=(long) tmp_p;
					}
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
					{
					  tmp_p=BUF_FP[N_CH]/10;
					  tmp_p=tmp_p/60;				   // л/с в формате с тремя запятыми то есть точность до десятых	т.о мл/с
					  tmp2=tmp2+0.5;
					  TEMP_l=(long) tmp2;
					}	
					CMRX1_K2+=TEMP_l;
				}
				else
				{	   // приводим текущую точность расхода к десяткам мл/с
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)	 // л/с в формате без запятых  т.о л/с
						CMRX1_K2+=BUF_FP[N_CH]*100;	 
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)	 // л/с в формате с запятой то есть точность до десятых	 т.о. десяты
						CMRX1_K2+=BUF_FP[N_CH]*10;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)	 // л/с в формате с двумя запятыми то есть точность до сотых
						CMRX1_K2+=BUF_FP[N_CH];	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)	 // л/с в формате с тремя запятыми то есть точность до десятых	т.о мл/с
						CMRX1_K2+=BUF_FP[N_CH]/10;	
				}
				if (fl_ds)
				{	
					fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x20;  
					adcbuf[2]=CMRX1_K2>>24;adcbuf[3]=CMRX1_K2>>16;
					adcbuf[4]=CMRX1_K2>>8;adcbuf[5]=CMRX1_K2;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
				}				
			}  
		}

		if (nas2!=0xff)	 // po 100ms
		{	  idata unsigned int temp2;
				idata unsigned long CMRX2_K2;
			 	if ((Str_CH_A[N_CH].Frm_Dat&0x02)==0x02)
				{										// литры в минуту это
					TEMP_1=0;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)
					{
					 // tmp2=BUF_FP[N_CH]*100;
					  tmp2=CMRX1_K2*10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)
					{
					//  tmp2=BUF_FP[N_CH]*10;
					  tmp2=CMRX1_K2;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)
					{
					 // tmp2=BUF_FP[N_CH];
					  tmp2=CMRX1_K2/10;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
					{
					 // tmp2=BUF_FP[N_CH]/10;
					 tmp2=CMRX1_K2/100;
					  tmp2=tmp2/60;
					  tmp2=tmp2+0.5;
					  TEMP_1=(long) tmp2;
					}	
					CMRX2_K2=TEMP_1;
				}
				else				// литры в секунду это
				{
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x00)	// суммируем в литрах?
						CMRX2_K2=CMRX1_K2*10;	 
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x40)   // суммируем в литрах ?
						CMRX2_K2=CMRX1_K2;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0x80)   // суммируем в литрах ?
						CMRX2_K2=CMRX1_K2/10;	
				 	if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)   // суммируем в литрах ?
						CMRX2_K2=CMRX1_K2/100;	
				}

				 	if (CMRX1_K2>=1000000000)
						{CMRX1_K2=1000000000; }
			if ((Str_CH_A[N_CH].Frm_Dat&0x01)==0x01)
			{
					Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat&0xF3;
				 	if (CMRX1_K2<1000000)
						{temp2=CMRX2_K2/100; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x0C;}
					else
					 	if (CMRX1_K2<10000000)
							{temp2=CMRX2_K2/1000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x08;}
						else
						 	if (CMRX1_K2<100000000)
								{temp2=CMRX2_K2/10000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x04;}
							else
							 	if (CMRX1_K2<1000000001)
									{temp2=CMRX2_K2/100000; }
				
			}
			else
			{
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
				 	  temp2=CMRX2_K2/100000;			   //  объем выводится в кубометрах без запятых
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
					   if (CMRX2_K2>655350000)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K2/10000;  		   //  объем выводится в кубометрах	  с одной запятой
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
					   if (CMRX2_K2>65535000)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K2/1000;			  //  объем выводится в кубометрах  с двумя запятыми
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
					   if (CMRX2_K2>6553500)
					   		 temp2=0xFFFF;
					   else
				 	  temp2=CMRX2_K2/100; 			  //  объем выводится в кубометрах  с тремя запятыми
			}

			if ((BUF_FP[N_CH]!=0)&(SEC%2)&(fl_ds))
			{
 					fl_ds=0;
					adcbuf[0]=0xD0;
					adcbuf[1]=0x1C;  
					adcbuf[2]=CMRX1_K2>>24;adcbuf[3]=CMRX1_K2>>16;
					adcbuf[4]=CMRX1_K2>>8;adcbuf[5]=CMRX1_K2;
					FUM_WR_DAT_CLOCK(adcbuf,6)
					fl_ds=1;
			//		temp2=5555;
			}
				if (i11<0xE0)
				{  	
			 		lbuf[i11]=BUF_FP[N_CH]>>8;;
					lbuf[i11+1]=BUF_FP[N_CH];;
	 				lbuf[i11+2]=temp2>>8;
					lbuf[i11+3]=temp2;		
				}
		}
		else
		{
				 if (CMRX1_K1>=1000000000)
					{CMRX1_K1=1000000000; }
								 
			if ((Str_CH_A[N_CH].Frm_Dat&0x01)==0x01)
			{			       // 4294967295
					Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat&0xF3;
				 	if (CMRX1_K1<1000000)			   // объем в  кубических литрах
						{CMRX2_K2=CMRX1_K2/100; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x0C;}
					else
					 	if (CMRX1_K1<10000000)			// объем в 	кубодециметрах
							{CMRX2_K2=CMRX1_K2/1000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x08;}
						else
						 	if (CMRX1_K1<100000000)	   // объем в сотнях литра кубического или десятых кубометра
								{CMRX2_K2=CMRX1_K2/10000; Str_CH_A[N_CH].Frm_Dat=Str_CH_A[N_CH].Frm_Dat|0x04;}
							else
							 	if (CMRX1_K1<1000000001)	   // объем в кубометрах
									{CMRX2_K2=CMRX1_K2/100000; }
			}
			else
			{
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x00)
				 	  CMRX2_K2=CMRX1_K2/100000;			   //  объем выводится в кубометрах без запятых
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x04)
				 {	  		   //  объем выводится в кубометрах	  с одной запятой
					   if (CMRX1_K2>655350000)
					   		 CMRX2_K2=0xFFFF;
					   else
						  CMRX2_K2=CMRX1_K2/10000;  
				 }
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x08)
				 {	 
					   if (CMRX1_K2>65535000)
					   		 CMRX2_K2=0xFFFF;
					   else
						  CMRX2_K2=CMRX1_K2/1000;			  //  объем выводится в кубометрах  с двумя запятыми
				 }
				 if ((Str_CH_A[N_CH].Frm_Dat&0x0C)==0x0C)
				 {
					   if (CMRX1_K2>6553500)
					   		 CMRX2_K2=0xFFFF;
					   else
				 	  	CMRX2_K2=CMRX1_K2/100; 			  //  объем выводится в кубометрах  с тремя запятыми
				 }
			}
					
					if (i11<0xE0)
					{  
				 		lbuf[i11]=BUF_FP[N_CH]>>8;
						lbuf[i11+1]=BUF_FP[N_CH];
		 				lbuf[i11+2]=CMRX2_K2>>8;
						lbuf[i11+3]=CMRX2_K2;	
					}
		}
		}
	}


			if (tmp_ch2==0x30)	 //   Скорость ТБ
			{	CNT_SEC_DL++;
				zadc = 13;					    
				N_CH=zadc;
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{	wadc=Str_CH_A[tmp_ch].NA_P5;
					if ((wadc&0xF0)==0x30)
					{						  
					/*
						if ((fl_v_dol==0)&(copy_dol!=BUF_FP[tmp_ch]))
						{
						  copy_dol=BUF_FP[tmp_ch];fl_v_dol=1;CNT_SEC_DL=0;
						}

							if (fl_v_dol!=0)
							{
								if (CNT_SEC_DL>8000)
								{	
									if (copy_dol>BUF_FP[tmp_ch])
									{	vel_dol+=copy_dol-BUF_FP[tmp_ch];
									}
									if (copy_dol<BUF_FP[tmp_ch])
									{
										vel_dol+=BUF_FP[tmp_ch]-copy_dol;
									}
		
									tmp2=(float) vel_dol*4000/CNT_SEC_DL;
									vel_dol=0;
									copy_dol=BUF_FP[tmp_ch];
									CNT_SEC_DL=0;
									tmp_int= (int) (tmp2+0.5);
									lbuf[i11]=tmp_int>>8;
									lbuf[i11+1]=tmp_int;
								}
    						}

							*/
							if (CNT_SEC_DL>10)
							{
								if (copy_dol>BUF_FP[tmp_ch])
								{	vel_dol=copy_dol-BUF_FP[tmp_ch];
								}
								else
									vel_dol=BUF_FP[tmp_ch]-copy_dol;
 								tmp2=(float) vel_dol*10/CNT_SEC_DL;
								vel_dol=0;
								copy_dol=BUF_FP[tmp_ch];
								CNT_SEC_DL=0;
								tmp_int= (int) (tmp2+0.5);
								lbuf[i11]=tmp_int>>8;
								lbuf[i11+1]=tmp_int;

							}
					  break;
					  }
				}
			}

			if (tmp_ch2==0x20)	 //  лопатка
			{	
				zadc = 13;
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{	wadc=Str_CH_A[tmp_ch].NA_P5;
					if (wadc==0x20)
					{	xdata unsigned int temp2;
					//	temp2=BUF_FP[tmp_ch]-lopatka;
						temp2=32768+BUF_FP[tmp_ch]-lopatka;
				//	    temp2=1234;
						lbuf[i11]=temp2>>8;
						lbuf[i11+1]=temp2;
				  		break;
					}
				}
			}

			if (tmp_ch2==0x50)	 //  нагрузка
			{
				zadc = 13;
				N_CH=zadc;
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{	wadc=Str_CH_A[tmp_ch].NA_P5;
					if ((wadc&0xF0)==0x50)
					{	// Ves_kol=500;
						 if (BUF_FP[tmp_ch]<Ves_kol)
						 {
								tmp_int=(int )(Ves_kol-BUF_FP[tmp_ch])+150; 
								lbuf[i11]=tmp_int>>8;
								lbuf[i11+1]=tmp_int;
						 }
						 else 
						 {
						 	if (BUF_FP[tmp_ch]<Ves_kol+150)
						 	{
 								tmp_int=(int )(Ves_kol-BUF_FP[tmp_ch])+150; 
								lbuf[i11]=tmp_int>>8;
								lbuf[i11+1]=tmp_int;
							}
							else
						    {
								lbuf[i11]=0;
								lbuf[i11+1]=0;
							}
//						
						 }  
					break;
					}
				}
			}
			
			if (tmp_ch2==0x60)	 //  	момент трения
			{	
				zadc = 13;
				N_CH=zadc;
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{	wadc=Str_CH_A[tmp_ch].NA_P5;
					if (wadc==0x60)
					{	
						 if (BUF_FP[tmp_ch]>Mom_tr)
						 {
						  tmp_int=(BUF_FP[tmp_ch]-Mom_tr);
						  z1=tmp_int>>8;
						  z2=tmp_int;
						 }
						 else { z1=0; z2=0;}
						lbuf[i11]=z1;
						lbuf[i11+1]=z2;

					break;
					}
				}
			}

		PR:
    	kan++;
	 }
	 // auiieiy?ony iaei ?ac ca oeee ii?ina

	 	if (st_dol!=cnt_dol)
		if (fl_ds)
		{	
			fl_ds=0;
			adcbuf[0]=0xD0;
			adcbuf[1]=0x1A;  
			adcbuf[2]=cnt_dol>>8; adcbuf[3]=cnt_dol;
			FUM_WR_DAT_CLOCK(adcbuf,4)
			st_dol=cnt_dol;
			fl_ds=1;
		}


	//	N_CH=zadc;
	  zadc = 13;   /*
		REL1_ON=0;	REL1_OFF=0;
		REL2_ON=0;	REL2_OFF=0;		
		*/
		for(N_CH=0;N_CH<zadc;N_CH++)
		{
			wadc = Str_BX_A[N_CH].ZGL_BX_A[0];
		  if (wadc!=0xFF)
		  {
				for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
				{
				 if (Str_CH_A[tmp_ch].NAME_PAR==wadc) break;
				}
				if (tmp_ch<zadc)   
				{	  
				   if (Str_BX_A[N_CH].ZGL_BX_A[1]==0x01)
				   {		
				   		if (Str_BX_A[N_CH].TAB_BX[0]>BUF_FP[tmp_ch])
							{REL1_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[0]<BUF_FP[tmp_ch])
							{REL1_ON++;}
				   }
					 
				   if (Str_BX_A[N_CH].ZGL_BX_A[1]==0x02)
				   {
				   		if (Str_BX_A[N_CH].TAB_BX[2]>BUF_FP[tmp_ch])
						  {REL1_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[2]<BUF_FP[tmp_ch])
						  {REL1_ON++;}
				   }					  

				   if (Str_BX_A[N_CH].ZGL_BX_A[1]==0x03)
				   {
				   		if (Str_BX_A[N_CH].TAB_BX[4]>BUF_FP[tmp_ch])
							{REL1_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[4]<BUF_FP[tmp_ch])
							{REL1_ON++;}
				   }

				   if (Str_BX_A[N_CH].ZGL_BX_A[2]==0x01)
				   {		
				   		if (Str_BX_A[N_CH].TAB_BX[0]>BUF_FP[tmp_ch])
						  {REL2_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[0]<BUF_FP[tmp_ch])
						  {REL2_ON++;}
				   }
					 
				   if (Str_BX_A[N_CH].ZGL_BX_A[2]==0x02)
				   {
				   		if (Str_BX_A[N_CH].TAB_BX[2]>BUF_FP[tmp_ch])
							{REL2_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[2]<BUF_FP[tmp_ch])
							{REL2_ON++;}
				   }

				   if (Str_BX_A[N_CH].ZGL_BX_A[2]==0x03)
				   {
				   		if (Str_BX_A[N_CH].TAB_BX[4]>BUF_FP[tmp_ch])
							{REL2_OFF++;}
				   		if (Str_BX_A[N_CH].TAB_BX[4]<BUF_FP[tmp_ch])
							{REL2_ON++;}
				   }
				}
		   } 
		} 		
		//  sbit RELE1    = P0^3		pervoe v stroke	  contakti 1,2,3    razem 1,4
				   if (REL1_ON>POR_R1_ON)	 
				   {	RELE1=0; REL1_ON=0;  REL1_OFF=0;}

				   if (REL1_OFF>POR_R1_OFF)	 
				   {  RELE1=1; REL1_ON=0;	 REL1_OFF=0;}

		// sbit RD - P3^7						vtoroe v stroke 	contakti 15,7,8 	razem 2,3
				   if (REL2_ON>POR_R2_ON)	 
					 {	RD=0;    REL2_ON=0;	 REL2_OFF=0;}

				   if (REL2_OFF>POR_R2_OFF)	 
					 {	RD=1;    REL2_ON=0;  REL2_OFF=0;}
	}
else
{

	N_CH=kan;

	if   ((Str_CH_A[N_CH].NAME_PAR!=0xFF)&(N_CH<13))
	{	
/*  tmp_ch=Str_CH_A[N_CH].R_IZM;
  if((tmp_ch!=0x84)&(tmp_ch!=0x88)&(tmp_ch!=0x8C)&(tmp_ch!=0x50)&(tmp_ch!=0xFF)&(tmp_ch!=0xCC))
  {	   xdata unsigned char c_P2,cik=0;;
 
       	  //перебирать каналы ацп от 1 до 7
   while(RDY0 ==0); 
	  RDY0 = 0;  
 	  PNT_BUF_TD  =  ADC0H<<8 | ADC0M;//int

	  BUF_T[N_CH]=PNT_BUF_TD;

	  
	 kan_sl=N_CH;
	 wadc=N_CH; 
     zadc=13;	

	 while (1)
	 {  if (wadc>zadc)
	 		{wadc=0;}
		else 
		wadc++;
		i11=Str_CH_A[wadc].R_IZM;
		if (Str_CH_A[wadc].NAME_PAR!=0xFF)
			if ((i11!=0x84)&(i11!=0x88)&(i11!=0x8C)&(i11!=0x50)&(i11!=0xFF)&(i11!=0xCC))
				{ kan_sl=wadc;
				 break;
				}
 	}
	 
	 wadc= Str_CH_A[kan_sl].N_RAZ;
	 tmpadc=TAB_ADC[wadc&0x03][wadc>>2];
  //выбрать мультиплексоры (порт Р2.5,7,3)
	 c_P2=(P2&0x57)|(tmpadc&0xB8);
	 P2 =c_P2;

	 SF=BX_SF;
	 ADC0CON2 = BX_RF | (tmpadc>>8); //канал ацп
	 ADCMODE = BX_MD; //RD=1;//старт АЦП  
 	
 	}
 */

	// не понял зачем это??
//	wadc= Str_CH_A[N_CH].N_RAZ;
//	tmpadc=TAB_ADC[wadc&0x03][wadc>>2];
//	P2 = (P2&0x57)|(tmpadc&0xB8); //выбрать мультиплексоры (порт Р2.5,7,3)


	// конец аналоговых каналов
	 
	       // разбор разных каналов

		//  дол
		if (Str_CH_A[N_CH].R_IZM==0x8C)   
     	{//BUF_ADC[N_CH]=cnt_dol;
		  BX_KPH=cnt_dol;
		  BUF_T[N_CH]=BX_KPH;
		}

		// насосы
		if (Str_CH_A[N_CH].R_IZM==0x88)		    //канал1
	 	{	
		//	extern bit fl_r;
			if (rasx1>=80000)
			{tmp2=0;	
		   	}
  			else
			{tmp2=240000*cop_imp1;
			tmp2= tmp2/rasx1;
			}


			if ((tmp2<4)|(tmp2>18530))
				{tmp2=0;}		
			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x10)
				tmp2=tmp2*10;	
			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x20)
				tmp2=tmp2*100;	
			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x30)
				tmp2=tmp2*1000;
		
			tmpadc=Str_CH_A[N_CH].KF_KORZ;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 

			tmp2=(float)  tmp2*tmpadc/100;

 			tmpadc=Str_CH_A[N_CH].KF_KORZ1;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 
			tmp2=(float)  tmp2/tmpadc;
			tmp2=(float)  tmp2*100;

			TEMP_1=(long) (tmp2+0.5);
	//		if 	(TEMP_1>0xffff)
	//			 TEMP_1=0xffff;
			PNT_BUF_TD=TEMP_1;
								 
			BUF_T[N_CH]=PNT_BUF_TD;
   	  	}

	   	if (Str_CH_A[N_CH].R_IZM==0x84)		   // канал 2
		{
  		if (rasx2>=80000)
			{
				tmp2=0;
			}
			else
			{
				tmp2=240000*cop_imp2;
				tmp2= tmp2/rasx2;
			}


			if (tmp2>=18530)
				{tmp2=0;}
			if (tmp2<4)	
				{tmp2=0;}

			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x10)
				tmp2=tmp2*10;	
			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x20)
				tmp2=tmp2*100;	
			if ((Str_CH_A[N_CH].Frm_Dat&0x30)==0x30)
				tmp2=tmp2*1000;	

			tmpadc=Str_CH_A[N_CH].KF_KORZ;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 

			tmp2=(float)  tmp2*tmpadc/100;

 			tmpadc=Str_CH_A[N_CH].KF_KORZ1;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 
			tmp2=(float)  tmp2/tmpadc;
			tmp2=(float)  tmp2*100;

			TEMP_1=(long) (tmp2+0.5);

			PNT_BUF_TD=TEMP_1;
			BUF_T[N_CH]=PNT_BUF_TD;	  // значение ходов
   		}


		if (Str_CH_A[N_CH].R_IZM==0xCC)
	 	{		
 			wadc=Str_CH_A[N_CH].NA_P5; 
	     //   zadc= ZG_TABX_DAT[3]>>1;
		 //   for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		 	if (wadc==0xCC)
			{
				 
				PNT_BUF_TD=DAC_PRIN;
				BUF_T[N_CH]=PNT_BUF_TD;	
			}
			else
			{
				for(tmp_ch=0;tmp_ch<13;tmp_ch++)
			  {
			       if (Str_CH_A[tmp_ch].NAME_PAR==wadc) break;
			  }
	
		    if (tmp_ch<13)
	      {
					PNT_BUF_TD=BUF_FP[tmp_ch];
					BUF_T[N_CH]=PNT_BUF_TD;			
				} 
				else
				{ //long temp_sum_dac=0;
				  //temp_sum_dac=BUF_FP[(wadc&0xF0)>>4]+BUF_FP[wadc&0x0F];
					PNT_BUF_TD= (BUF_FP[((wadc&0xF0)>>4)-1]+BUF_FP[(wadc&0x0F)-1])>>1;
					BUF_T[N_CH]=PNT_BUF_TD;
				}
			}		

	//		PNT_BUF_TD=DAC_PRIN;
	//		BUF_T[N_CH]=PNT_BUF_TD;	
	//		DAC_PRIN++;
   	 }
		 
	if	(Str_CH_A[N_CH].NA_P1!=0)
	{
		PNT_BUF_TD=0;
		BUF_T[N_CH]=0;	
		Str_CH_A[N_CH].NA_P2-=1;
		if (Str_CH_A[N_CH].NA_P2==0xF5)
		{
			Str_CH_A[N_CH].NA_P1-=1;
			Str_CH_A[N_CH].NA_P2=0;
		}
	} 
 
  per=BUF_S[N_CH];
	tm=BUF_N[N_CH];
 
	pods=Str_CH_A[N_CH].KF_CRD;
 
 if (pods>1)
 {
    if (per<pods)
	{  
		if (tm<=tm+ BUF_T[N_CH])
		{
				tm+=BUF_T[N_CH];
				per++;
		}
		else Str_CH_A[N_CH].KF_CRD=per;
	}
	else
	{
	  idata unsigned long tmpadc_t=0;
		tmpadc_t=tm-BUF_U[N_CH]+BUF_T[N_CH];
		tm=tmpadc_t;
	}
		tmp2=(float) tm/per; 
		tmp2=tmp2+0.5;
		TEMP_1=(long) tmp2;
		if (TEMP_1>0xffff)
			TEMP_1=0xffff; 	
		BUF_U[N_CH]=TEMP_1;
		BX_KOD=(int) TEMP_1;	  // вместо деления на пер
		BUF_N[N_CH]=tm;
		BUF_S[N_CH]=per;
 }
 else
 {
		if (BUF_T[N_CH]>0xFFFF)
			BUF_T[N_CH]=0xFFFF;	
		BX_KOD=BUF_T[N_CH];
 }

  		// плотность по режиму 60

		//------------------вычисление уровня раствора функцией коррекции--------27.07.2006--------------
		//   уровень N = уровень * 1.000 / плотность
	if (Str_CH_A[N_CH].R_IZM==0x60)//режим измерения из описания анал.канала (уровень)60
	{
		  wadc=Str_CH_A[N_CH].NA_P5; // имя параметра плотность (таблица описания анал.каналов)
		//-----------считать значение плотности из буфера результатов ------
		         zadc= ZG_TABX_DAT[3]>>1;
		         for(tmp_ch=0;tmp_ch<zadc;tmp_ch++)
		         {
		         	if (Str_CH_A[tmp_ch].NAME_PAR==wadc) break;
		         }

	           if (tmp_ch<zadc)
               {  
		       		tmpadc= BUF_FP[tmp_ch];	// плотность
					if (tmpadc<OGR_UR)//tmp2)		 
					{
						//	 tmp2=(float) 0,85*Str_BX1_A[tmp_ch].TAB_BX1[1];
						tmpadc=OGR_UR;//tmp2;
					}
					if ((Str_BX1_A[tmp_ch].TAB_BX1[2]!=0xFFFF)&(Str_BX1_A[tmp_ch].TAB_BX1[3]!=0)&(Str_BX1_A[tmp_ch].TAB_BX1[3]!=0xFFFF))
					{
						tmp2=(float) BX_KOD*Str_BX1_A[tmp_ch].TAB_BX1[3];
						if 	(tmpadc!=0)
							tmp2=(float) tmp2/tmpadc;
						else
							tmp2=0;
					}
					else
						tmp2=(float) BX_KOD;
					if ((Str_CH_A[N_CH].Frm_Dat&0xC0)==0xC0)
			 			tmp2=tmp2*1000;
			 		if ((Str_CH_A[N_CH].Frm_Dat&0x80)==0x80)
			 			tmp2=tmp2*100;
			 		if ((Str_CH_A[N_CH].Frm_Dat&0x40)==0x40)
			 			tmp2=tmp2*10;
					tmp2=tmp2+0.5;
					TEMP_1=(long) tmp2;
					if (TEMP_1>0xffff)
						TEMP_1=0xffff;	
					BX_KOD=(int) TEMP_1;	
						//	BX_KOD=(int) tmp2; 
	           }

	}


  	if  (Str_CH_A[N_CH].R_IZM==0x50)//цифровое значение канала
  	{
		xdata unsigned char c_P0;
		wadc= Str_CH_A[N_CH].N_RAZ;
    	switch (wadc&0x1F)  //выделили разъем
     	{
       		case 21: //0x15, разъем-5; подключение 5-GND;  порт- P0.7
        	{c_P0=P0; BX_KOD=(c_P0&0x80)>>7;
         		break;
         	}
       		case 22: //0x16,  разъем i-5; подключение 10-GND; порт - P0.6
          	{c_P0=P0;BX_KOD=(c_P0&0x40)>>6;
           		break;
          	}
       		case 25: //0x19,  разъем -6; подключение 5-GND;  порт - P0.5
          	{c_P0=P0;BX_KOD=(c_P0&0x20)>>5;
           		break;
          	}
       		case 26: //0x1A, разъем -6; подключение 10-GND; порт - P0.4
          	{c_P0=P0;BX_KOD=(c_P0&0x10)>>4;
           		break;
          	}
     	} 
	} 

//--------------- коррекция нелинейных датчиков ------------------

/*
 if (Str_CH_A[N_CH].R_IZM==0x47) //для датчика веса
 {	idata unsigned long A1;
    wadc=BX_KOD>>8;wadc=wadc&0xF0;wadc=wadc>>3; //адрес таблицы коррекции
   	A1=0;
    tmpadc=TAB_NO_LINE_1[wadc]; //читаем из таблицы >i
    A1=BX_KOD&0x0FFF; //12 младших разряд кода АЦП
	tmp2=(float) A1*tmpadc/16;
	tmp2=tmp2+0.5;
	A1=(long) tmp2;
	tmpadc= TAB_NO_LINE_1[wadc+1]; A1=A1+tmpadc;tmpadc=A1;
	if (BX_KOD>tmpadc) {BX_KOD=BX_KOD-tmpadc;}else {BX_KOD=tmpadc-BX_KOD;}
//	 BX_KOD=12345;
 }
 if((Str_CH_A[N_CH].R_IZM&0xFF)==0x42)
  {	idata unsigned long A1;
    wadc=BX_KOD>>8;wadc=wadc&0xF0;wadc=wadc>>3; //адрес таблицы коррекции
   	A1=0;
   tmpadc=TAB_NO_LINE_2[wadc]; //читаем из таблицы >i
    A1=BX_KOD&0x0FFF; //12 младших разряд кода АЦП
	tmp2=(float) A1*tmpadc/16;
	tmp2=tmp2+0.5;
	A1=(long) tmp2;
	tmpadc= TAB_NO_LINE_2[wadc+1]; A1=A1+tmpadc;tmpadc=A1;
	if (BX_KOD>tmpadc) {BX_KOD=BX_KOD-tmpadc;}else {BX_KOD=tmpadc-BX_KOD;}

   }

  if((Str_CH_A[N_CH].R_IZM&0xFF)==0x43)
  {		idata unsigned long A1;
    wadc=BX_KOD>>8;wadc=wadc&0xF0;wadc=wadc>>3; //адрес таблицы коррекции
   	A1=0;
   tmpadc=TAB_NO_LINE_3[wadc]; //читаем из таблицы >i
    A1=BX_KOD&0x0FFF; //12 младших разряд кода АЦП
	tmp2=(float) A1*tmpadc/16;
	tmp2=tmp2+0.5;
	A1=(long) tmp2;
	tmpadc= TAB_NO_LINE_3[wadc+1]; A1=A1+tmpadc;tmpadc=A1;
	if (BX_KOD>tmpadc) 
		{BX_KOD=BX_KOD-tmpadc;}
	else
	 {BX_KOD=tmpadc-BX_KOD;}

   }

	 старый вес
	 */
   //вставка
   //--------------- коррекция нелинейных датчиков ------------------
//  новая коррекция нелинейности веса для токового выхода датчика 
//  диапазон значений 4-20 мА= 13107 - 65535 кодов АЦП

 //  BX_KOD=ves;

  if((Str_CH_A[N_CH].R_IZM&0xFF)==0x25)
  {	
 	if (BX_KOD>13107)
	{
	    const nol=3276.75;
		unsigned int bx;
		unsigned char wadc1;
		float vrem; 

		bx=BX_KOD-13107;
		wadc1=bx/nol;

		tmp2= bx % nol;
		vrem=(float) (TAB_NO_LINE_25[wadc1+1]-TAB_NO_LINE_25[wadc1])/nol;
		tmp2=(float) tmp2*vrem;
		tmp2+=TAB_NO_LINE_25[wadc1];
		
		tmp2+=0.5;
		BX_KOD=(int) tmp2;
		BX_KOD+=13107;
	}
  }

 if((Str_CH_A[N_CH].R_IZM&0xFF)==0x28)
  {	
  	if (BX_KOD>13107)
	{
	    const nol=3276.75;
		unsigned int bx;
		unsigned char wadc1;
		float vrem; 

		bx=BX_KOD-13107;
		wadc1=bx/nol;

		tmp2= bx % nol;
		vrem=(float) (TAB_NO_LINE_28[wadc1+1]-TAB_NO_LINE_28[wadc1])/nol;
		tmp2=(float) tmp2*vrem;
		tmp2+=TAB_NO_LINE_28[wadc1];
		
		tmp2+=0.5;
		BX_KOD=(int) tmp2;
		BX_KOD+=13107;
	}
   }

 if((Str_CH_A[N_CH].R_IZM&0xFF)==0x32)
 {	
 	if (BX_KOD>13107)
	{
	  const nol=3276.75;
		unsigned int bx;
		unsigned char wadc1;
		float vrem; 

		bx=BX_KOD-13107;
		wadc1=bx/nol;

		tmp2= bx % nol;
		vrem=(float) (TAB_NO_LINE_32[wadc1+1]-TAB_NO_LINE_32[wadc1])/nol;
		tmp2=(float) tmp2*vrem;
		tmp2+=TAB_NO_LINE_32[wadc1];
		
		tmp2+=0.5;
		BX_KOD=(int) tmp2;
		BX_KOD+=13107;
	}
 }

  if((Str_CH_A[N_CH].R_IZM&0xFF)==0x36)
  {	
	if (BX_KOD>13107)
	{
	    const nol=3276.75;
		unsigned int bx;
		unsigned char wadc1;
		float vrem; 

		bx=BX_KOD-13107;
		wadc1=bx/nol;

		tmp2= bx % nol;
		vrem=(float) (TAB_NO_LINE_36[wadc1+1]-TAB_NO_LINE_36[wadc1])/nol;
		tmp2=(float) tmp2*vrem;
		tmp2+=TAB_NO_LINE_36[wadc1];
		
		tmp2+=0.5;
		BX_KOD=(int) tmp2;
		BX_KOD+=13107;
	}
  }
		//начало преобразований всех каналов через общие переменные---------------------------------------



		//калибровка
 		//калибровка
    wadc= Str_BX1_A[N_CH].ZGL_BX1_A[3];
	if (BX_KOD>=0xFFFF)
		BX_KOD=0xFFFF;
	if ((wadc<=0x28)&(wadc>0x07)&(BX_KOD<=0xFFFF))
	{
	 	 i11=0;    
 		 if (BX_KOD>=Str_BX1_A[N_CH].TAB_BX1[i11])       
 		 {   	idata unsigned long tmpadc_t=0;                       
 				while ((BX_KOD>Str_BX1_A[N_CH].TAB_BX1[i11+2])&(i11<(wadc>>1)-2))   
	  	        {                         
	  		        i11= i11+2;  
	        	}     
				if (i11>=(wadc>>1)-2)
	           		BX_KPH=Str_BX1_A[N_CH].TAB_BX1[i11+1];   
				else
				{	
					if (Str_BX1_A[N_CH].TAB_BX1[i11+2]!=BX_KOD)
					{				             
			           TEMP_1=Str_BX1_A[N_CH].TAB_BX1[i11+3]-Str_BX1_A[N_CH].TAB_BX1[i11+1]; 
			           BX_KOD=BX_KOD-Str_BX1_A[N_CH].TAB_BX1[i11];     
			           TEMP_1=TEMP_1*BX_KOD;      
			           tmpadc_t=Str_BX1_A[N_CH].TAB_BX1[i11+2]-Str_BX1_A[N_CH].TAB_BX1[i11];  
			           tmp2=(float) TEMP_1/tmpadc_t;
					   TEMP_1=(long) (tmp2+0.5);       
			           BX_KPH=TEMP_1+Str_BX1_A[N_CH].TAB_BX1[i11+1]; 
				   }					
					else
					  BX_KPH=Str_BX1_A[N_CH].TAB_BX1[i11+3];
  				}                                   
		 }                        
   		 else 
		 { 
		 	BX_KPH=Str_BX1_A[N_CH].TAB_BX1[i11+1];
		 }  	
	}
	else 
	 {BX_KPH=BX_KOD;} 
	//			конец калибровки


 
	     	  //общее умножение на последнее значение

	if ((Str_CH_A[N_CH].R_IZM!=0x88)&(Str_CH_A[N_CH].R_IZM!=0x84))
	{
			tmpadc=Str_CH_A[N_CH].KF_KORZ;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 

			tmp2=(float)  BX_KPH*tmpadc/100;

 			tmpadc=Str_CH_A[N_CH].KF_KORZ1;
			if (tmpadc==0)
			{
			 tmpadc=100;
			} 
			tmp2=(float)  tmp2/tmpadc;
			tmp2=(float)  tmp2*100;

			TEMP_1=(long) (tmp2+0.5);
			BX_KPH=TEMP_1;	
	}

	   	BUF_FP[N_CH]=BX_KPH; //  физицеск значение после применения формата сохраняем в лонг
		if (BUF_FP[N_CH]>65535)
			BUF_FP[N_CH]=65535;	

		if ((Str_CH_A[N_CH].NA_P5&0x0F)==0x05)
		{	extern xdata unsigned int BUF_FP_100_0;

			BUF_FP_100_0=BX_KPH;
		}
	  //  конец общее умножение на последнее значение

	    if	(Str_CH_A[N_CH].R_IZM==0x88)
		 	{BX_KPH=BUF_T[N_CH];} 
		if (Str_CH_A[N_CH].R_IZM==0x84)
		 	{BX_KPH=BUF_T[N_CH];} 

  		if (BX_KPH>0xFFFF)
			BX_KPH=0xFFFF;



		if (Str_CH_A[N_CH].R_IZM==0xCC)
	 	{	
			tmp2=(float) BX_KPH*1.6384;
			tmp2=tmp2+0.5;
			TEMP_1=(long)  tmp2;
			if (TEMP_1>=0xFFF)
				TEMP_1=0xFFF;
			DACH=TEMP_1>>8;
			DACL=TEMP_1;
			if (BX_KPH>2500)
				BX_KPH=2500;	
		}


		if (Str_CH_A[N_CH].KF_WIND<0xE0)
		{  	data unsigned char ind;

	 	   		ind=Str_CH_A[N_CH].KF_WIND>>3;
				lbuf[ind] =BX_KPH>>8;
				lbuf[ind+1] =BX_KPH;
		}
 	}
}
			 	   PPK: 

 return;
}