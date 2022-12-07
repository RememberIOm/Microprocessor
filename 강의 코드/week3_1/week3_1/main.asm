;
; week3_1.asm
;
; Created: 2021-03-16 오전 8:55:26
; Author : RBIOM
;


; Replace with your application code

	.ORG 00	 
	LDI  R16, 1
	LDI  R17, 0			;R17 = 0
L1: ADD  R17,R16	;R17 = R17 + R16
	LDI  R19, 2
	ADD  R16, R19
	LDI  R20, 0x1D
	SUB  R20, R16
	BRNE L1	 				;if Z = 0
L2: RJMP L2				;Wait here forever	
