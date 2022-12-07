;
; week1.asm
;
; Created: 2021-03-04 오전 11:51:24
; Author : RBIOM
;


; Replace with your application code

.INCLUDE "M128DEF.INC"
    LDI R16,0xFF
    OUT DDRA,R16
L1: OUT PORTA,R16
    LDI R20,0
    OUT PORTA,R20
    RJMP L1
