 
/*------------------------------------------------------------------
Макрос   FUM_RD_DAT_CLOCK прочитать значение RAM часов 
len-3;adcbuf[12]
------------------------------------------------------------------*/
#define FUM_RD_DAT_CLOCK(Adr,Buf_d,size,wpar)   { \                   
wpar=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0; \
for(j=0;j<2;j++) \
{for(i1=0;i1<8;i1++) \
{if((wpar&0x80)==0)  \
{MDO=0;} else {MDO=1;} 	\
DL=2;while (1){DL--;if(DL==0)break;}MCO=1; 	\
while (1) {if (MCO==1) break;}				\
DL=2;while (1){DL--;if(DL==0)break;}MCO=0;MDO=0; \
wpar = wpar<<1; }                             \           
                 DL=2;while (1){DL--;if(DL==0)break;}  \   
                   MDE=0; MCO=1;  MDO=1;  while (1) {if (MCO==1) break;}  \                
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} \
				    if (DL==0) b_err_cl++;		\
				   MDE=1;  MCO=0;  									 \
wpar = Adr;}                                                       \                     
DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						   \
while (1) {if (MCO==1) break;}											\
DL=2;while (1){DL--;if(DL==0)break;} 									 \
MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						  \
wpar=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						   \
MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					\
MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	\
for(i1=0;i1<8;i1++) 												 \
{ if((wpar&0x80)==0){MDO=0;}else { MDO=1;} 					 \
DL=2;while (1){DL--;if(DL==0)break;}							  \
MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;   \                                                  
wpar= wpar<<1; } 																   \
                 DL=2;while (1){DL--;if(DL==0)break;}    							   \
                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}   \   
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					\
				    if (DL==0) b_err_cl++;															   \
				   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											\
for(j=0;j<size;j++)																									\
{for(i1=0;i1<8;i1++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		   \
if (MDI ==0) 																									   \
{Buf_d[j] = Buf_d[j]<<1;Buf_d[j] = Buf_d[j]&0xFE;} 															   \
else 																											   \
{Buf_d[j] = Buf_d[j]<<1;   																					  \
Buf_d[j] = Buf_d[j]|0x01; }                          					\
MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							 \
MDO=0;																	  \
if (j==(size-1)) {MDO=1;}												   \
MDE=1;                            											\
MCO=1;  while (1) {if (MCO==1) break;}										 \
DL=2;while (1){DL--;if(DL==0)break;} 										  \
MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							   \
MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										\
MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									 \
MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1;   \                    
}																				   \
																					
																					 
/*------------------------------------------------------------------
Макрос   FUM_Wr_DAT_CLOCK записать значения в RAM часов 
len-3;adcbuf[12]
------------------------------------------------------------------*/
#define FUM_WR_DAT_CLOCK(Buf_d,size)   { \ 
MDO=0; \
DL=2;while (1){DL--;if(DL==0)break;} \
MCO=0; \
for(g=0;g<size;g++) \
  {   \
   for(g1=0;g1<8;g1++) \
     { \
      if((Buf_d[g]&0x80)==0) \
        { \
         MDO=0; \ 
         }  \
          else  \
           {  \
            MDO=1;  \
             } \
              DL=2;while (1){DL--;if(DL==0)break;} \ 
              MCO=1; while (1) {if (MCO==1)break;} \
              DL=2;while (1){DL--;if(DL==0)break;} \
              MCO=0;  \                      
              if (tmp_ch!=7) { Buf_d[g] = Buf_d[g]<<1;} \
              MDO=0;  \
               }   \                                
                   DL=2;while (1){DL--;if(DL==0)break;}  \   
                   MDO=1; MDE=0; MCO=1; while (1) {if (MCO==1)break;} \                  
	               	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					\
		   if (DL==0) b_err_cl++;				   \
			   MDE=1;  MCO=0; \ 
               }   \                       
                  DL=2;while (1){DL--;if(DL==0)break;}  \
                  MCO=1; while (1) {if (MCO==1)break;}\
                  DL=2;while (1){DL--;if(DL==0)break;} \
                  MDO=1;  \ 
} 
#define FUM_WR_CLOCK(Buf_d,size)   { \ 
MDO=0; \
DL=2;while (1){DL--;if(DL==0)break;} \
MCO=0; \
for(g=0;g<size;g++) \
  {   \
   for(g1=0;g1<8;g1++) \
     { \
      if((Buf_d[g]&0x80)==0) \
        { \
         MDO=0; \ 
         }  \
          else  \
           {  \
            MDO=1;  \
             } \
              DL=2;while (1){DL--;if(DL==0)break;} \ 
              MCO=1; while (1) {if (MCO==1)break;} \
              DL=2;while (1){DL--;if(DL==0)break;} \
              MCO=0;  \                      
              if (j!=7) { Buf_d[g] = Buf_d[g]<<1;} \
              MDO=0;  \
               }   \                                
                   DL=2;while (1){DL--;if(DL==0)break;}  \   
                   MDO=1; MDE=0; MCO=1; while (1) {if (MCO==1)break;} \                  
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					\
				   if (DL==0) b_err_cl++;													\
				   MDE=1;  MCO=0; \ 
               }   \                       
                  DL=2;while (1){DL--;if(DL==0)break;}  \
                  MCO=1; while (1) {if (MCO==1)break;}\
                  DL=2;while (1){DL--;if(DL==0)break;} \
                  MDO=1;  \ 
} 

#define FUM_RD_CLOCK(Adr,Buf_d,size,wpar)   { \                   
wpar=0xD0;MDO=0;DL=2;while (1){DL--;if(DL==0)break;} MCO=0; \
for(j=0;j<2;j++) \
{for(i1=0;i1<8;i1++) \
{if((wpar&0x80)==0)  \
{MDO=0;} else {MDO=1;} 	\
DL=2;while (1){DL--;if(DL==0)break;}MCO=1; 	\
while (1) {if (MCO==1) break;}				\
DL=2;while (1){DL--;if(DL==0)break;}MCO=0;MDO=0; \
wpar = wpar<<1; }                             \           
                 DL=2;while (1){DL--;if(DL==0)break;}  \   
                   MDE=0; MCO=1;  MDO=1;  while (1) {if (MCO==1) break;}  \                
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					\
				   if (DL==0) b_err_cl++;										 \
				   MDE=1;  MCO=0;  									 \
wpar = Adr;}                                                       \                     
DL=2;while (1){DL--;if(DL==0)break;} MCO=1;  						   \
while (1) {if (MCO==1) break;}											\
DL=2;while (1){DL--;if(DL==0)break;} 									 \
MDO=1;DL=2;while (1){DL--;if(DL==0)break;}        						  \
wpar=0xD1; DL=2;while (1){DL--;if(DL==0)break;} 						   \
MDO=0; DL=2;while (1){DL--;if(DL==0)break;} 					\
MCO=0; DL=2;while (1){DL--;if(DL==0)break;}                        	\
for(i1=0;i1<8;i1++) 												 \
{ if((wpar&0x80)==0){MDO=0;}else { MDO=1;} 					 \
DL=2;while (1){DL--;if(DL==0)break;}							  \
MCO=1;DL=2;while (1) {if (MCO==1) break;}while (1){DL--;if(DL==0)break;}MCO=0;MDO=0;   \                                                  
wpar= wpar<<1; } 																   \
                 DL=2;while (1){DL--;if(DL==0)break;}    							   \
                   MDE=0; MDO=1; MCO=1;       DL=2;while (1) {if (MCO==1) break;}  while (1){DL--;if(DL==0)break;}   \             
	               DL=200; while (1){DL--; if ((MDI==0)|(DL==0)) break;} 					\
				   MDE=1;  MCO=0; 	DL=2;while (1){DL--;if(DL==0)break;}  											\
for(j=0;j<size;j++)																									\
{for(i1=0;i1<8;i1++){ MDO=1;MDE=0;MCO=1; while (1){if (MCO==1) break;} DL=2;while (1){DL--;if(DL==0)break;}		   \
if (MDI ==0) 																									   \
{Buf_d[j] = Buf_d[j]<<1;Buf_d[j] = Buf_d[j]&0xFE;} 															   \
else 																											   \
{Buf_d[j] = Buf_d[j]<<1;   																					  \
Buf_d[j] = Buf_d[j]|0x01; }                          					\
MCO=0; DL=2;while (1){DL--;if(DL==0)break;}}  							 \
MDO=0;																	  \
if (j==(size-1)) {MDO=1;}												   \
MDE=1;                            											\
MCO=1;  while (1) {if (MCO==1) break;}										 \
DL=2;while (1){DL--;if(DL==0)break;} 										  \
MCO=0;MDE=0;DL=2;while (1){DL--;if(DL==0)break;}} 							   \
MDE=1;DL=2;while (1){DL--;if(DL==0)break;} 										\
MDO=0;DL=2;while (1){DL--;if(DL==0)break;}     									 \
MCO=1;while (1) {if (MCO==1) break;}DL=2;while (1){DL--;if(DL==0)break;} MDO=1;   \                    
}						