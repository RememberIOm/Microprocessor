//#include "lcd.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "glcd.h"

void cmd_l( unsigned char cmd )	
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	ClrBit(PORTE,4);	// RS
	ClrBit(PORTE,6);	// CS2
	SetBit(PORTE,7);	// CS1
	PORTA = cmd ;		
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void cmd_r( unsigned char cmd )
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	ClrBit(PORTE,4);	// RS
	SetBit(PORTE,6);	// CS2
	ClrBit(PORTE,7);	// CS1
	PORTA = cmd ;
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void cmd_lr( unsigned char cmd )
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	ClrBit(PORTE,4);	// RS
	SetBit(PORTE,6);	// CS2
	SetBit(PORTE,7);	// CS1
	PORTA = cmd ;
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void data_l( unsigned char data )          
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	SetBit(PORTE,4);	// RS
	ClrBit(PORTE,6);	// CS2
	SetBit(PORTE,7);	// CS1
	PORTA = data ; 
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void data_r( unsigned char data )
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	SetBit(PORTE,4);	// RS
	SetBit(PORTE,6);	// CS2
	ClrBit(PORTE,7);	// CS1
	PORTA = data ;
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void data_lr( unsigned char data )
{
	SetBit(PORTE,5);	// E
	_delay_us(10);
	SetBit(PORTE,4);	// RS
	SetBit(PORTE,6);	// CS2
	SetBit(PORTE,7);	// CS1
	PORTA = data ;
	_delay_us(10);
	ClrBit(PORTE,5);	// E
}

void display_char(unsigned char x, unsigned char y, unsigned char character)
{
	unsigned char i;
	
	cmd_lr(0xB8+x);     // x address
	if( y < 10 )
		cmd_l(0x40+y*6+4); // y address	
	else
		cmd_r(0x40+(y-10)*6); // y address
		
	for(i = 0; i < 5; i++)
	{
		if(y < 10)                 
			data_l(font[character-0x20][i]);
		else                           
			data_r(font[character-0x20][i]);
	}			
		
	if(y < 10)
		data_l(0x00);                   
	else
		data_r(0x00); 				                  	
}

void display_string(unsigned char x, unsigned char y, unsigned char *string)
{
	unsigned char i;
	
	cmd_lr(0xB8+x);     // x address
	if( y < 10 )
		cmd_l(0x40+y*6+4); // y address
	else
		cmd_r(0x40+(y-10)*6); // y address
	
	while( *string != '\0' ){
		if( y == 10 ){
			cmd_r(0x40);
		}
		for(i = 0; i < 5; i++){
			if(y < 10)					   
				data_l(font[*string-0x20][i]);
			else                           
				data_r(font[*string-0x20][i]);
		}
	
		if(y < 10)
			data_l(0x00);                    
		else
			data_r(0x00);
			
		string++;
		y++;
	}	
}

void lcd_clear()
{
	unsigned char i, j, x, y;
	x = 0xB8;                         /* X start address */
	y = 0x40;                         /* Y start address */
	for(i = 0; i < 8; i++)
	{
		cmd_lr(x);    cmd_lr(y);
		for(j = 0; j < 64; j++)
			data_lr(0x00);           /* clear CS1 and CS2 */
		x++;
	}
}

int main(void) 
{	
	//Initialization
	DDRA = 0xFF;
	PORTB = 0xFF; DDRB = 0xFF;
	DDRD = 0x0;
	DDRE = 0xFF;
	PORTG = 0x0; DDRG = 0xFF;

	cmd_lr( 0x3F ); //DISP ON   
	cmd_lr( 0xB8 );
	cmd_lr( 0x40 );
	
	display_char(0, 0, 'H');
	display_char(0, 1, 'e');
	display_char(0, 2, 'l');
	display_char(0, 3, 'l');
	display_char(0, 4, 'o');
	display_char(1, 5, 'H');
	display_char(1, 6, 'e');
	display_char(1, 7, 'l');
	display_char(1, 8, 'l');
	display_char(1, 9, 'o');
	display_char(1, 10, ' ');
	display_char(1, 11, 'W');
	display_char(1, 12, 'o');
	display_char(1, 13, 'r');
	display_char(1, 14, 'l');
	display_char(1, 15, 'd');
	
	lcd_clear();
	display_string(2, 0, "Hello World!!!!!");
	

	while(1){}

	
}