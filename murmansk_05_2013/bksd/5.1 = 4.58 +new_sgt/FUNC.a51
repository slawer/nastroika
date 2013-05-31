;************КЦС40 Новосибирск май 2005года *********************
;Программный модуль описания функций
;1.чтение из EEPROM repr(*buf_data[],n_page,*adr; ldata) 
;2.запись в  EEPROM wepr(*buf_data[],n_page,*adr; ldata)
;значение указателя '*bufdata[]' содержится в регистре 'R7'
;значение номера страницы ' n_page' содержится в регистре 'R5' 
;значение указателя адреса и количес.байт обмена'*adr;ldata'содержится в регистре'R3' ----
;страница содержит 256 байт 
;3. умножение двухбайтных чисел
;f_mul (unsigned int  A_X, unsigned int  A_Y ,unsigned  char data  *A_Z)
;R4-R5 (аргумент A_X) R6-R7  (аргумент A_Y) A_Z = A_X*A_Y указатель *A_Z -R3 
;***********************************************************************************


#include "r_main.h" 

?_f_mul SEGMENT CODE
EXTRN	CODE (MAIN)
;TL1    DATA 8BH   
ECON   DATA 0B9H
EDATA1 DATA 0BCH
EDATA2 DATA 0BDH
EDATA3 DATA 0BEH
EDATA4 DATA 0BFH
EADRL  DATA 0C6H
EADRH  DATA 0C7H
//extrn  bit(fepr0)
;extrn  DATA (ST_EEPR,zb) 
 
PUBLIC _f_mul            

                                                                                 
;---- Variable 'reg_p' assigned to Register 'R7' ----
;---- Variable 'n_peg' assigned to Register 'R5' ----
;---- Variable 'ad_rg' assigned to Register 'R3' ----
 ;?_f_mul SEGMENT CODE
;EXTRN CODE (MAIN)
;extrn data   (x)
;PUBLIC _f_mul           
RSEG ?_f_mul 
_f_mul:
  ;MOV     R5,A_X+01H
  ;MOV     R4,A_X
  ;MOV     R7,A_Y+01H
  ;MOV     R6,A_Y

;R4-R5 (аргумент A_X) R6-R7  (аргумент A_Y) A_Z = A_X*A_Y  *A_Z -R3
MOV	A,R7 ;L1-x1
MOV	B,R5 ;L2-x2
MUL	AB   ;L1*L2
MOV	R1,A ;R1,R0 - сохраняем результат умножения
MOV	R0,B
XCH	A,R7
MOV	B,R4
MUL	AB
ADD	A,R0
;MOV	R0,A
XCH	A,R6
MOV	B,R5
MUL	AB
ADD	A,R6
MOV	R6,A
MOV     A,R3
MOV     R0,A 
MOV     A,R6 
MOV     @R0,A ;ст.байт
INC     R0
MOV     A,R7 
MOV     @R0,A ;мл.байт
RET
end
	

