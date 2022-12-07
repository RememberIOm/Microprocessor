//#include "lcd.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char press_num;

int main(void) 
{	
	//Initialization
	DDRA = 0xFF;
	PORTB = 0xFF; DDRB = 0xFF;
	DDRD = 0x0;
	DDRE = 0xFF;
	PORTG = 0x0; DDRG = 0xFF;
	
	EIMSK = 1; //Enable INT0
	EICRA = (1<<1);
	
	
	sei();	
	
	press_num = 0;

	while(1){		
		PORTB = press_num;
	}			
}


ISR(INT0_vect){
	press_num++;	
}