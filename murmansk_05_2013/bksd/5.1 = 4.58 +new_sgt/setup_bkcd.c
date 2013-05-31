

// »«ћ≈–»“≈Ћ№Ќџ… ћќƒ”Ћ№ (BKCD ADuC 848)   2005г.


//#include <reg816.h>
#include "aduc848.h"
#include "r_main.h"
//#include "ADC_bkcd.h"
#include "define_stuct.h"
//extern bit ffp;//,ffp_l;
//extern  bit  flagadc,FL_20;
//extern bit fzb2,fzb1,fzb0; //fepr0,fepr1,fepr2,flagadc;
//extern  idata unsigned char  bufin[8];
//extern  idata  unsigned char  bufout [24]; 

//extern  idata unsigned char CLK_DAY,Kld_Month,Kld_Year; //,adcbuf[12];

//extern idata unsigned char T_MS_ADC;
//extern  data unsigned int CNT_SEC,CM_RAX1;
//extern  idata unsigned int CM_RAX;
//extern  data unsigned char  /*adr1,adr2,adr3,*/;



//extern idata unsigned int AA;
//extern idata unsigned char size ; 
//extern xdata unsigned char MSK_PW1,MSK_PW2,MSK_ERR;
//extern xdata unsigned char /*buf_msk[17],*/PA_H ,PA_L, ADR_BF;

//extern xdata unsigned char K_PAH;
//extern data unsigned int tmpadc;
//extern data unsigned int CM2,CM1;
//extern data unsigned int CNT_DOL;

 //extern data unsigned char status;
 
 void setup (void)
{ 
/*********************************************/
/*           RESET                           */
/*********************************************/

 register unsigned char  i1;//,j2,j;
 xdata unsigned int tmpadc;
 xdata unsigned int ADR_E;
 xdata  unsigned int CM1,CM2;
 extern  data  unsigned char  bufcht1[2]; //,wadc;
 extern xdata unsigned char DL;
 extern  xdata unsigned char  lbuf[LBUF_SIZE];
   
/*
  PLLCON = 0x0000;
  TIMECON = 0x0001;        //start clock 
  SPICON= 0x3D;//39
SCON=0x50;
TMOD=0x11;
T3CON=0x84;
T3FD= 0x12; 

  TL1 = -250;//-240;//0xC4;//-200;
  TH1 = -6;//-12;//-1;
  TI=1;

  */

//   flagadc = 0;
 
  TMOD = 0x11;
  PLLCON = 0x0000;
 	 EA = 0; 
	  WDWR=1;WDCON=0x72;	 // 0x32 = 125 ms   0x52= 500 ms
	 EA = 1;

while (!(PLLCON&0x40))

  SPICON= 0x3D;//39
  // CNT_SEC=0;
 //  bufcht1[0]=0;
	DACCON=0x03;
// EX0=1 ; IT0 = 1;                   // external interrupt enable
           
        I2CM=1;MCO=1; MDE=1;MDO=1; //мастер I2c
   T2CON = 0x0030;
   ET2 = 0;       
   TR2 = 0;
   ES = 0;
  EADC = 0;
        SCON = 0x0050;
        PCON = 0x0000;
   //        WR =0;                      
//             EADRL = 0x00;
//        ECON =0x01; 
//  	    lbuf[0] = EDATA1;
     
  
//-------------------------------
       T3CON=0x84;
       T3FD= 0x12; 

/*        
           if(lbuf[0]==1)
              {
               T3CON=0x85;                   
              }

             if(lbuf[0]==9)
             {                   
              
             T3CON=0x86;
             }
   */     
//--------------------------------        
            // TR2 = 1;
//------------------------------------------------ 
          
//********************************************              

//--копирование таблиц -----

MAC_Copy_Epr_Ram_TAB_ALL(0x0400,0x0400) //4страница
MAC_Copy_Epr_Ram_TAB_ALL(0x0500,0x0500)
MAC_Copy_Epr_Ram_TAB_ALL(0x0600,0x0600)
MAC_Copy_Epr_Ram_TAB_ALL(0x0700,0x0700)
//MAC_Copy_Epr_Ram(0x0260,0x0270,24)	

	//2страница таблицы режимов записи во FLASH 20 08 08
//читать часы из модул€ часов во внутренние часы контроллера
//FUM_RD_CLOCK //макрос
//----------внутренна€ калибровка 0\1---------------------

ADC0CON2 = BX_RF ; //0x40канал ацп 
//---запустить измерение заданного параметра
SF = BX_SF; //0x03
ADC0CON1 = BX_CON1;//0x27
ADCMODE = 0x24;//калибровка 0
while(RDY0 ==0);  
RDY0 = 0; 
ADCMODE = 0x25;  //калибровка 1
while(RDY0 ==0);  
RDY0 = 0;
//EADRL = 0x20;       
//ECON =  0x01;
//EDATA1= OF0H;
//EDATA2= OF0M;
//EDATA3= GN0H;
//EDATA4= GN0M;
//ECON = 0x05;                     
//ECON = 0x02; 
//------------------------

return;
} 

