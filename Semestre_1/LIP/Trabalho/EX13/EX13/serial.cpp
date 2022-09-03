#include "serial.h"
#include "defs.h"
/**
 * Construtor da Classe;
 */
Serial::Serial()
{
	UBRR0H = (uint8_t) (MYUBRR>>8);
	UBRR0L = (uint8_t)(MYUBRR);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

int Serial::adc_read( int channel )
{
	switch( channel )
	{
		case 0: 
				return 1023;
	}
	
	return -1; 
}

void Serial::print( int i )
{
	sprintf( txt, "%d\r\n", i );
	writestr( txt );
}
void Serial::print( uint16_t i )
{
	sprintf( txt, "%u\r\n", i );
	writestr( txt );
}
void Serial::print( float  f )
{
	sprintf( txt, "%.2f\r\n", (double)f );
	writestr( txt );
}

void Serial::print( const char * c )
{
	sprintf( txt, "%s\r\n", c );
	writestr( txt );
}

void Serial::writestr( char *ptr )
{
	while(*ptr != '\0')
	{
		writebyte( *ptr );
		ptr++;
	}
}

void Serial::writebyte( char data )
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}