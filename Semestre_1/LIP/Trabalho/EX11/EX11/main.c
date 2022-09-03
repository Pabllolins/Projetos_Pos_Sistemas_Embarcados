#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "usart.h"

int main( void )
{
	char txt[30];
	
	int leitura1 = 256;
	int leitura2 = 256;
	int leitura3 = 256;
	unsigned long valor_peso;
	
	USART_Init(); 
	
    while (1) 
    {
		/* Qual o problema da equação a seguir? */
		valor_peso = leitura1*256*256+leitura2*256 + leitura3;
		
		sprintf( txt , "%lu\r\n", valor_peso ); //%lu for unsigned long
		USART_StrTx( (char*) txt ); 
		_delay_ms( 5000 ); 
    }
	
	return 0; 
}

