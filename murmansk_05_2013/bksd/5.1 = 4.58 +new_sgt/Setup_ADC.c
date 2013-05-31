
#include "aduc848.h"
//#include "r_main.h"
//#include "ADC_bkcd.h"
//#include "define_stuct.h"
//#include "Опис_Таб_Кан.h"
//extern xdata unsigned char FLP;
//extern data unsigned int tmpadc;
extern idata unsigned char N_RZ;
extern idata unsigned char MM[7];
//extern idata unsigned char  p2cf;


extern data unsigned char tmp_ch;
//extern idata unsigned char N_CH3,N_CH4;
//extern  xdata unsigned char  lbuf [LBUF_SIZE]; 
//extern xdata unsigned char buf_ind[32];
//extern bit FL_ERR,FL_PRX,FL_PADC,FL_WFL;
//extern bit F_KRAX,FL_KAL1,TMP_FL;
//extern idata unsigned char  j2,j;
//extern idata unsigned int PNT_adcbuf32,PNT_BUF1_D32,CNT_MCLK1,CNT_MCLK2;

extern idata unsigned long CMRX1_K1, CMRX1_K2,cmr;
extern idata unsigned int CMRX2_K1,CMRX2_K2;
extern idata unsigned int cnt_dol;
//extern xdata unsigned int BUF_CH_LDT[8];
//extern xdata unsigned int adcbuf32[32],BUF1_D32[32];
//extern xdata unsigned char NM_STR_IDF;
//extern idata unsigned int NM_STR_IZM;
//extern xdata unsigned char CNT_IND_H,CNT_IND_L;
//extern idata unsigned N_CH_H,N_CH_H1;
//extern xdata unsigned int buf_adccon2[8];

//extern data  unsigned char adr1;
extern data  unsigned char  wadc; //,wadc1,ADC0,ADC1,ADC2;   
extern xdata unsigned int Mom_tr, Ves_kol;
extern code unsigned int  TAB_ADC[4][9];

//extern xdata unsigned int CH_T;
//extern xdata unsigned int adcbuf40[42];//_at_ 0x0030; 
//extern xdata unsigned int BUF1_D40[42]; //_at_ 0x0080;
//extern code unsigned int  TAB_ADC[4][9]; 
extern xdata struct TABX_CH_A 
{ 
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
unsigned int KF_KORZ1;// KF_KORZ1; //коэффициент коррекции1(делитель) резул.измерения(физ.значен)
//unsigned int  KF_KORZ1; //адрес размещения
}TABX_CH_A;
// непонятно почему только до 5ти.. extern xdata struct  TABX_CH_A Str_CH_A[5];
extern xdata struct  TABX_CH_A Str_CH_A[13];
//extern xdata unsigned char  BF_ZP_A[16];
extern xdata struct BUF_FL_D 
{
unsigned long DAT_CRD;//область рабочих буферов результатов усреднения

}BUF_FL_D;
//extern xdata struct BUF_FL_D lst_PAR[10];

void setup_ADC (void) 
{ 
//register unsigned char tmp_ch;
register unsigned char DL;
register unsigned char tmp_rw, is, js;
xdata unsigned char buf_ch[8];
xdata unsigned char  adcbuf[20];
data  unsigned char  wadc;
idata unsigned char zadc;
data unsigned char N_CH;
extern xdata unsigned char b_err_cl;

extern xdata unsigned int lopatka;
extern xdata unsigned char ekran;
//register unsigned char size;

//data unsigned char g;
//buf_ind[16]=0;buf_ind[17]=0;buf_ind[18]=0;buf_ind[19]=0;buf_ind[20]=0;
// buf_ind[21]=0;buf_ind[22]=0;buf_ind[23]=0;buf_ind[24]=0;buf_ind[25]=0;
// buf_ind[26]=0;buf_ind[27]=0;buf_ind[28]=0;buf_ind[29]=0;buf_ind[30]=0;  
//for(g=0;g<10;g++)
 //{lst_PAR[g].DAT_CRD=0;}
//for(i1=0;i1<40;i1++) {lbuf[i1]=0;}
//for(g=0;g<32;g++) {adcbuf32[g]=0;}
//BUF_CH_LDT[0]=0;BUF_CH_LDT[1]=0;BUF_CH_LDT[2]=0;BUF_CH_LDT[3]=0;
//BUF_CH_LDT[4]=0;BUF_CH_LDT[5]=0;BUF_CH_LDT[6]=0;BUF_CH_LDT[7]=0;
//buf_adccon2[0]=0; buf_adccon2[1]=0; buf_adccon2[2]=0; buf_adccon2[3]=0;
//buf_adccon2[4]=0; buf_adccon2[5]=0; buf_adccon2[6]=0; buf_adccon2[7]=0; 
//F_RST=1;//флаг рестарта контроллера     
//FL_ERR=0;



//******** SETUP входов ЦАП из табличных описаний аналоговых каналов ********
//zadc = BF_ZP_A[3];
zadc=13;
//if((zadc==0)|(zadc >12))
//	zadc=12;//?????????????????????????????????????????????????????????????
//R_IZM = 88h,84h - измерение временного интервала между импульсами канала 1,2
//R_IZM = 8Dh  - счетчик ДОЛ no obratnoe napravlenie.
//R_IZM = 8Ch  - счетчик ДОЛ.
MM[0]=0;MM[3]=0; 
MM[1]=0;MM[2]=0;
    for(js=0;js<zadc;js++)
    {
  
			N_CH=js;
			wadc= Str_CH_A[N_CH].N_RAZ;
			if (Str_CH_A[N_CH].R_IZM==0x88)//канал1 (частота моточасы,расход сумм.расход)
			{
				if(wadc==0x15) {MM[1]=0x80;}
				if(wadc==0x16) {MM[1]=0x40;}
				if(wadc==0x19) {MM[1]=0x20;}
				if(wadc==0x1A) {MM[1]=0x10;}

      }
 
 
			if (Str_CH_A[N_CH].R_IZM==0x84) //канал2 (частота моточасы,расход сумм.расход)
      {
        if(wadc==0x15) {MM[2]=0x80;}
        if(wadc==0x16) {MM[2]=0x40;}
        if(wadc==0x19) {MM[2]=0x20;}
        if(wadc==0x1A) {MM[2]=0x10;}
      }
 
      if (Str_CH_A[N_CH].R_IZM==0x8D)
      {	 extern bit napr;
			 Str_CH_A[N_CH].R_IZM=0x8C;
			 napr=1;
			}
			
      if (Str_CH_A[N_CH].R_IZM==0x8C)
      {
       if(wadc==0x17) {MM[0]=0x80;MM[6]=0x40;}
       if(wadc==0x1B) {MM[0]=0x20;MM[6]=0x10;}
      }
     }
 //----------------цифровой канал 1 (насос)------


   // чтение сохраненных параметров из часов
//FUM_RD_DAT_CLOCK(0x1A,adcbuf,18,js) 
//ADP1:
					tmp_rw=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0;  
					for(js=0;js<2;js++)  
					{for(is=0;is<8;is++)  					
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
					tmp_rw = 0x1A;}                                                                             
					DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						    
					while (1) {if (MCO==1) break;}											 
					DL=2;while (1){DL--;if(DL==0)break;} 									  
					MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						   
					tmp_rw=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						    
					MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	 
					for(is=0;is<8;is++) 												  
					{ if((tmp_rw&0x80)==0){MDO=0;}else { MDO=1;} 					  
					DL=2;while (1){DL--;if(DL==0)break;}							   
					MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;                                                      
					tmp_rw= tmp_rw<<1; } 																    
					                 DL=2;while (1){DL--;if(DL==0)break;}    							    
					                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}                 
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					
 				   	if (DL==0) b_err_cl++;
																	  
									   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											 
					for(js=0;js<18;js++)																									 
					{for(is=0;is<8;is++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		    
					if (MDI ==0) 																									    
					{adcbuf[js] = adcbuf[js]<<1;adcbuf[js] = adcbuf[js]&0xFE;} 															    
					else 																											    
					{adcbuf[js] = adcbuf[js]<<1;   																					   
					adcbuf[js] = adcbuf[js]|0x01; }                          					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							  
					MDO=0;																	   
					if (js==(18-1)) {MDO=1;}												    
					MDE=1;                            											 
					MCO=1;  while (1) {if (MCO==1) break;}										  
					DL=2;while (1){DL--;if(DL==0)break;} 										   
					MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							    
					MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										 
					MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									  
					MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1; 

cnt_dol=(adcbuf[0]<<8)| adcbuf[1];

CMRX1_K1=adcbuf[2];
CMRX1_K1=CMRX1_K1<<8;
CMRX1_K1+=adcbuf[3];
CMRX1_K1=CMRX1_K1<<8;
CMRX1_K1+=adcbuf[4];
CMRX1_K1=CMRX1_K1<<8;
CMRX1_K1+=adcbuf[5];
//CMRX2_K1 = (adcbuf[4]<<8)| adcbuf[5];
//CMRX1_K2 = (adcbuf[6]<<8)| adcbuf[7]; 
//CMRX2_K2=(adcbuf[8]<<8)| adcbuf[9]; 
CMRX1_K2=adcbuf[6];
CMRX1_K2=CMRX1_K2<<8;
CMRX1_K2+=adcbuf[7];
CMRX1_K2=CMRX1_K2<<8;
CMRX1_K2+=adcbuf[8];
CMRX1_K2=CMRX1_K2<<8;
CMRX1_K2+=adcbuf[9];
Mom_tr=(adcbuf[10]<<8)| adcbuf[11]; 
Ves_kol=(adcbuf[12]<<8)| adcbuf[13];
//cmr=(adcbuf[14]<<8)| adcbuf[15]; 
cmr=adcbuf[14];
cmr=cmr<<8;
cmr+=adcbuf[15];
cmr=cmr<<8;
cmr+=adcbuf[16];
cmr=cmr<<8;
cmr+=adcbuf[17];


   // чтение экранов и лопатки из часов		 адрес 0ч33

					tmp_rw=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0;  
					for(js=0;js<2;js++)  
					{for(is=0;is<8;is++)  					
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
					tmp_rw = 0x33;}                                                                             
					DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						    
					while (1) {if (MCO==1) break;}											 
					DL=2;while (1){DL--;if(DL==0)break;} 									  
					MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						   
					tmp_rw=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						    
					MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	 
					for(is=0;is<8;is++) 												  
					{ if((tmp_rw&0x80)==0){MDO=0;}else { MDO=1;} 					  
					DL=2;while (1){DL--;if(DL==0)break;}							   
					MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;                                                      
					tmp_rw= tmp_rw<<1; } 																    
					                 DL=2;while (1){DL--;if(DL==0)break;}    							    
					                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}                 
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					
 				   	if (DL==0) b_err_cl++;
																	  
									   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											 
					for(js=0;js<3;js++)																									 
					{for(is=0;is<8;is++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		    
					if (MDI ==0) 																									    
					{adcbuf[js] = adcbuf[js]<<1;adcbuf[js] = adcbuf[js]&0xFE;} 															    
					else 																											    
					{adcbuf[js] = adcbuf[js]<<1;   																					   
					adcbuf[js] = adcbuf[js]|0x01; }                          					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							  
					MDO=0;																	   
					if (js==(3-1)) {MDO=1;}												    
					MDE=1;                            											 
					MCO=1;  while (1) {if (MCO==1) break;}										  
					DL=2;while (1){DL--;if(DL==0)break;} 										   
					MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							    
					MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										 
					MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									  
					MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1; 



lopatka=(adcbuf[1]<<8)| adcbuf[2];
ekran=adcbuf[0];
	if (((ekran&0x0C)!=0)|(ekran==0)|(ekran==0xff))
	{
		ekran=0x71;
	}


   // чтение времени из часов
					tmp_rw=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0;  
					for(js=0;js<2;js++)  
					{for(is=0;is<8;is++)  
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
					for(is=0;is<8;is++) 												  
					{ if((tmp_rw&0x80)==0){MDO=0;}else { MDO=1;} 					  
					DL=2;while (1){DL--;if(DL==0)break;}							   
					MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;                                                      
					tmp_rw= tmp_rw<<1; } 																    
					                 DL=2;while (1){DL--;if(DL==0)break;}    							    
					                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}                 
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					
 				   if (DL==0) b_err_cl++;
																	  
									   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											 
					for(js=0;js<8;js++)																									 
					{for(is=0;is<8;is++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		    
					if (MDI ==0) 																									    
					{buf_ch[js] = buf_ch[js]<<1;buf_ch[js] = buf_ch[js]&0xFE;} 															    
					else 																											    
					{buf_ch[js] = buf_ch[js]<<1;   																					   
					buf_ch[js] = buf_ch[js]|0x01; }                          					 
					MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							  
					MDO=0;																	   
					if (js==(8-1)) {MDO=1;}												    
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
  TIMECON = 0x0001;        //start clock 
  
return;
}