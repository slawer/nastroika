//�������� ������ ������������ ���������� �������
//����_���_���.h
 //--����� ����������� (���� �2.5 �2.4 �2.3)
/*

code unsigned int  TAB_ADC[4][9] = {0,0,0,0,0,0,0,0,0,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8,    
                     0,0x0600,0x0608,0x0680,0x0688,0x0620,0x0628,0x00A0,0x00A8,
                     0,0,0x0108,0x0280,0x0388,0x0420,0x0528,0x00A0,0x00A8};
/*
//--------����� ����������� ���������� --------------
xdata struct BX_SAVE 
{
unsigned char BUF_S[16]; 
}BX_SAVE;
 xdata struct  BX_SAVE Str_BX_SAVE _at_ 0x0590;
//Str_BX_SAVE.BUF_S[16]  
//--------------- ������� ��������� �������� --------------
*/
 xdata struct BX_A 
{
unsigned char ZGL_BX_A[4]; //ZGL_BX_A[1] - ���� ERROR 1x PWU/I; mask POROG
unsigned int  TAB_BX[6]; // _at_ 0x05A0 ;//����� ��������� ���������� ��������
}BX_A;
xdata struct  BX_A Str_BX_A[8] _at_ 0x05E0; 


 //  �� 1� xdata ������ � main.h

 xdata unsigned int BUF_S[15] _at_ 0x0200;	 // ������� �������
 xdata unsigned long BUF_T[15] _at_ 0x01C0; //0x0340; //0x0200;			  7
 xdata unsigned long BUF_N[15] _at_ 0x0100; //0x0370; //0x0230;		   4
 xdata unsigned long BUF_U[15] _at_ 0x0140; //0x0370; //0x0230;			5
 xdata unsigned long BUF_FP[15] _at_ 0x0180; //0x0370; //0x0230;		 6
  
	/*
 xdata unsigned int BUF_S[15] _at_ 0x0200;	 // ������� �������
 xdata unsigned int BUF_T[15] _at_ 0x01C0; //0x0340; //0x0200;			  7
 xdata unsigned long BUF_N[15] _at_ 0x0100; //0x0370; //0x0230;		   4
 xdata unsigned int BUF_U[15] _at_ 0x0140; //0x0370; //0x0230;			5
 xdata unsigned int BUF_FP[15] _at_ 0x0180; //0x0370; //0x0230;		 6
  */
/*	xdata struct MN 
	{
		unsigned long  ZN [7]; //Zn - �������� ����������� �� 100 �� �������� �� ���
//		unsigned char  KOL[7]; // kol - ���������� ����������� ��������
	}MN;
*/  	
//	xdata struct MN BUF_MN[7];
//	xdata unsigned long  BUF_MN[7] _at_ 0x00DD;		 ���������� � main.h 

//xdata unsigned char St[32] _at_ 0x0300;	 // ������� �������

 
//-------------- ������� �������������� ---------------
xdata struct BX1_A 
{
unsigned char ZGL_BX1_A[4];
unsigned int  TAB_BX1[22]; //����� ������� ���������� ����������.��������
}BX1_A;
 xdata struct  BX1_A Str_BX1_A[8] _at_ 0x0400;
//-------------------------------------------------------------------------

//-------------- ������� �������� ������� ������ FLASH 20 08 08 ---------------
/*
R_WR_FLASH; //������ ������
XXXX 0000 - �������� ������������ ������ �� ������ �� FLASH
0000 XXXX - �������� ����������� ������ �� ������ �� FLASH
0010 0010 - ������ ������ ��������� ������������ �������� ����������� � ������������ �������
0100 0100 - ������ ������ ��������� ������� ����. �������� ����������� � ������������ �������
1000 1000 - ������ ������ �������� ��� ���������� �������� PZ ����������� � ������������ �������
*/

//------��������� ������ ��������  ������� � XDATA 
xdata struct TABX_CH_A 
{
//unsigned char ZGL_TABX_CH[4]; 
unsigned char NAME_PAR; //��� ��������� �����������
unsigned char R_IZM;    //����� ��������� ����.�������(task3/task2)
unsigned char Frm_Dat; //�������� ������� 00 40 80 C0; 00 10 20 30; ......
unsigned char LA_TAB; //����� �������
unsigned char NA_P1; //��� ������������ ���������1(�����)
unsigned char NA_P2; //��� ������������ ���������2(I/U)
unsigned char NA_P3; //������ ��������� ��������� {XX,X �������)
unsigned char NA_P5; //��� ������������ ���������5 
unsigned char NA_P4; //������ ������������ ��������� {XX,X �������)
unsigned char N_RAZ; //����� ������� TIP_PAR;
unsigned char KF_CRD; //����������� ����������
unsigned char KF_WIND;
unsigned int  KF_KORZ; //����������� ���������(���������)  �����.���������(���.������)
unsigned int  KF_KORZ1; //KF_KORZ1; //����������� ���������1(��������) �����.���������(���.������)
//unsigned char  KF_KORZ1; //����� ����������
}TABX_CH_A;
xdata struct  TABX_CH_A Str_CH_A[13] _at_ 0x0680; //0x0494;// ����� � ���������� �������� ������� ����

xdata unsigned char ZG_TABX_DAT[4] _at_ 0x07B0; //0x0520;

// xdata unsigned char  BF_ZP_A[16] _at_ 0x0780 ;


 // xdata unsigned int K1  _at_ 0x0760;
 // xdata unsigned int HH1  _at_ 0x0763;
 // xdata unsigned long K2  _at_ 0x0766;
 // xdata unsigned long HH2  _at_ 0x076B;

xdata struct TABX_DAT 
{   
unsigned char NAME_PAR; //��� ���������
unsigned char ADR_RZ; //����� ���������� ���������� � ����� �����������
}TABX_DAT;
 xdata struct  TABX_DAT Str_TDAT[20] _at_ 0x07B4;// ����� � ���������� �������� ������� ����



