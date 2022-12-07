#include <avr/io.h>

int main(void)
{
	//Initialization
	PORTB = 0xFF; DDRB = 0xFF;
	DDRD = 0x0;

	TCNT1H = 0x00;	
	TCNT1L = 0x00;	
	OCR1AH = 0x3D; //modify
	OCR1AL = 0x09; //modify	
	TCCR1A = 0x00;
	TCCR1B = 0x0D; //modify

	while(1){
		//Check OCF1A
		if( TIFR & (1<<OCF1A) ){
			PORTB ^= 0x1;			
			TIFR = (1<<OCF1A); 
			//Clear OCF1A						
		}				
	}	
}
	