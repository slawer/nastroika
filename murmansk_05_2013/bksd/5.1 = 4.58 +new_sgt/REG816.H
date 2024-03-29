
/*--------------------------------------------------------------------------
REG816.H

Header file for ADUC816.
Copyright (c) 2001 Novosibirsk Morozov A.V.****
All rights reserved.
--------------------------------------------------------------------------*/
//#ifndef REG816_HEADER_FILE
//#define REG816_HEADER_FILE 1
sfr P0    =  0x80; 	
sfr SP    =  0x81;	
sfr DPL   =  0x82; 
sfr DPH   =  0x83;  
sfr DPP   =  0x84; 
sfr PCON  =  0x87; 
sfr TCON  =  0x88; 
sfr TMOD  =  0x89; 
sfr TL0   =  0x8A; 
sfr TL1   =  0x8B; 
sfr TH0   =  0x8C; 
sfr TH1   =  0x8D; 
sfr P1    =  0x90; 
sfr SCON  =  0x98; 
sfr SBUF  =  0x99; 
sfr I2CDAT = 0x9A; 
sfr I2CADD = 0x9B; 
sfr P2    =  0xA0;
sfr TIMECON = 0xA1;
sfr HTHSEC = 0xA2;
sfr SEC   =  0xA3;
sfr MIN   =  0xA4;
sfr HOUR  =  0xA5;
sfr INTVAL = 0xA6; 
sfr IE    =  0xA8; 
sfr IEIP2 =  0xA9; 
sfr CFG836 =  0xAF; 
sfr P3    =  0xB0; 
sfr IP    =  0xB8; 
sfr ECON  =  0xB9; 
sfr EDATA1 = 0xBC; 
sfr EDATA2 = 0xBD; 
sfr EDATA3 = 0xBE; 
sfr EDATA4 = 0xBF; 
sfr WDCON  = 0xC0; 
sfr CHIPID = 0xC2;
sfr EADRL  = 0xC6;
sfr EADRH  = 0xC7; 
sfr T2CON  = 0xC8; 
sfr RCAP2L = 0xCA; 
sfr RCAP2H = 0xCB; 
sfr TL2    = 0xCC; 
sfr TH2    = 0xCD; 
sfr PSW    = 0xD0; 
sfr ADCMODE = 0xD1;
sfr ADC0CON = 0xD2;
sfr ADC1CON = 0xD3;
sfr SF      = 0xD4;
sfr ICON    = 0xD5;
sfr PLLCON  = 0xD7;
sfr ADCSTAT = 0xD8;
sfr ADC0M   = 0xDA; 
sfr ADC0H   = 0xDB;
sfr ADC1L   = 0xDC;
sfr ADC1H   = 0xDD;
sfr PSMCON  = 0xDF; 
sfr ACC     = 0xE0; 
sfr OF0M    = 0xE2;
sfr OF0H    = 0xE3;
sfr OF1L    = 0xE4;
sfr OF1H    = 0xE5;
sfr GN0M    = 0xEA;
sfr GN0H    = 0xEB;
sfr GN1L    = 0xEC;
sfr GN1H    = 0xED;
sfr B       = 0xF0;
sfr SPIDAT  = 0xF7; 
sfr SPICON  = 0xF8; 
sfr DACL    = 0xFB; 
sfr DACH    = 0xFC; 
sfr DACCON  = 0xFD; 


sbit IT0    = 0x88; 
sbit IE0    = 0x89; 
sbit IT1    = 0x8A; 
sbit IE1    = 0x8B; 
sbit TR0    = 0x8C; 
sbit TF0    = 0x8D; 
sbit TR1    = 0x8E; 
sbit TF1    = 0x8F; 
sbit T2     = 0x90;
sbit T2EX   = 0x91; 
sbit RI     = 0x98; 
sbit TI     = 0x99; 
sbit RB8    = 0x9A; 
sbit TB8    = 0x9B; 
sbit REN    = 0x9C; 
sbit SM2    = 0x9D; 
sbit SM1    = 0x9E; 
sbit SM0    = 0x9F; 
sbit EX0    = 0xA8; 
sbit ET0    = 0xA9; 
sbit EX1    = 0xAA; 
sbit ET1    = 0xAB; 
sbit ES     = 0xAC; 
sbit ET2    = 0xAD; 
sbit EADC   = 0xAE; 
sbit EA     = 0xAF;
sbit RXD    = 0xB0; 
sbit TXD    = 0xB1; 
sbit INT0   = 0xB2; 
sbit INT1   = 0xB3; 
sbit T0     = 0xB4; 
sbit T1     = 0xB5; 
sbit WR     = 0xB6; 
sbit RD     = 0xB7; 
sbit PX0    = 0xB8; 
sbit PT0    = 0xB9; 
sbit PX1    = 0xBA; 
sbit PT1    = 0xBB; 
sbit PS     = 0xBC; 
sbit PT2    = 0xBD; 
sbit PADC   = 0xBE; 

sbit WDWR   = 0xC0; 
sbit WDE    = 0xC1;
sbit WDS    = 0xC2; 
sbit WDIR   = 0xC3; 
sbit PRE0   = 0xC4; 
sbit PRE1   = 0xC5; 
sbit PRE2   = 0xC6; 
sbit PRE3   = 0xC7;
sbit CAP2   = 0xC8; 
sbit CNT2   = 0xC9; 
sbit TR2    = 0xCA; 
sbit EXEN2  = 0xCB; 
sbit TCLK   = 0xCC; 
sbit RCLK   = 0xCD; 
sbit EXF2   = 0xCE; 
sbit TF2    = 0xCF; 
sbit P      = 0xD0; 
sbit F1     = 0xD1; 
sbit OV     = 0xD2; 
sbit RS0    = 0xD3; 
sbit RS1    = 0xD4; 
sbit F0     = 0xD5; 
sbit AC     = 0xD6; 
sbit CY     = 0xD7; 

sbit ERR1   = 0xDA; 
sbit ERR0   = 0xDB; 
sbit NOXREF = 0xDC; 
sbit CAL    = 0xDD; 
sbit RDY1   = 0xDE; 
sbit RDY0   = 0xDF; 
sbit I2CI   = 0xE8; 
sbit I2CTX  = 0xE9; 
sbit I2CRS  = 0xEA; 
sbit I2CM   = 0xEB; 
sbit MDI    = 0xEC; 
sbit MCO    = 0xED; 
sbit MDE    = 0xEE; 
sbit MDO    = 0xEF; 
sbit SPR0   = 0xF8; 
sbit SPR1   = 0xF9; 
sbit CPHA   = 0xFA; 
sbit CPOL   = 0xFB; 
sbit SPIM   = 0xFC; 
sbit SPE    = 0xFD; 
sbit WCOL   = 0xFE; 
sbit ISPI   = 0xFF; 
