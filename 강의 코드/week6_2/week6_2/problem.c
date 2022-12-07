#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main()
{
  DDRB = 0xFF;
  DDRD = 0x00;
  
  while(1)
  {
	if (!(PIND & 0b00000001)) {
		PORTB = 0b00000001;
		_delay_ms(1000);
		PORTB = 0b00000000;
		_delay_ms(1000);
	}
  }
}
