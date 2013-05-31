				

 // #include "main.h"
 // #define LBUF_SIZE    28

//extern  xdata unsigned char  lbuf [LBUF_SIZE];	   // первые 64
//extern xdata unsigned char  lbuf_dn [LBUF_SIZE];

void lbuf_cop () //using 0
{//	data unsigned char j3;
 
  // 	for(j3=0;j3<LBUF_SIZE-1;j3++) 	{ 		 
//	  lbuf_dn[j3]=lbuf[j3];	}

#pragma asm

	mov r0,#0
	mov r1,#192
	mov r3,#28
  l1:
	MOVx A,@R0
	movx @r1,a
	inc r0
	inc r1
	djnz r3,  l1

#pragma endasm

}
 /*

void cop_buf () //using 0
{//	data unsigned char j3;
 
  // 	for(j3=0;j3<LBUF_SIZE-1;j3++) 	{ 		 
//	  lbuf_dn[j3]=lbuf[j3];	}




}

*/