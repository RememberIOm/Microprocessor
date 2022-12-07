#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF; //make port B as output port
	while(1)
	{
		PORTB = 0xFF; //make all pins HIGH
		_delay_ms(1000); //wait 1 sec
		PORTB = 0x00; //make all pins LOW
		_delay_ms(1000); //wait 1 sec
	}
}