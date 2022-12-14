.INCLUDE"M128DEF.INC"
.ORG 0	;location for reset
	JMP	MAIN
.ORG 0x02 ;location for external INT0
	JMP	EX0_ISR	
.ORG 0x04 ;location for external INT1
	JMP EX1_ISR

MAIN:
	LDI R20,HIGH(RAMEND) ;load SPH
	OUT SPH,R16
	LDI R20,LOW(RAMEND)	;load SPL
	OUT SPL,R20
	LDI R20,0x0
	OUT	DDRD,R20
	LDI R20,0xFF
	OUT	DDRB,R20
	OUT	PORTB,R20
		
	LDI	R20,0b00000011 ;enable INT0 and INT1
	OUT	EIMSK,R20
	SEI	; set interrupt

WAIT: ; doing useful work
	CBI PORTB,6
	SBI PORTB,7 
	RCALL DELAY
	SBI PORTB,6 
	CBI PORTB,7
	RCALL DELAY	
	RJMP WAIT

EX0_ISR:
	CBI PORTB,0 
	RETI

EX1_ISR:
	SBI PORTB,0
	RETI

DELAY: 	
	LDI	R20,64
L1:	LDI	R21,200
L2:	LDI	R22,250    
L3:	
	NOP
	NOP
	DEC	R22
	BRNE	L3
	DEC	R21
	BRNE	L2
	DEC	R20
	BRNE	L1
	RET