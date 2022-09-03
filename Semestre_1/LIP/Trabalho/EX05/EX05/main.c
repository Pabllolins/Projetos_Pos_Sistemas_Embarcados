#define F_CPU 16000000UL

/**
 * Inclui as definições dos registrados do ATMEGA328p ou ATMEGA2560;
 */
#include <avr/io.h>

/**
 * Biblioteca que inclui a macro _delay_ms;
 */
#include <util/delay.h>

/**
 * Lib Uart
 */
#include "usart.h"
/**
 * Diretivas 
 */
#define TRUE  			1
#define BUTTON_1 		2
#define LED_BUILDING 	5
#define Set_bit(y,bit)		(y|=(1<<bit))		// Coloca 1 no bit da variável y
#define Clr_bit(y,bit)		(y&=~(1<<bit))		// Coloca 0 no bit da variável y
#define Cpl_bit(y,bit)		(y^=(1<<bit))		// Troca o estado do bit da variável y
#define Tst_bit(y,bit)		(y&(1<<bit))		// Retorna o estado do bit

/**
 * Função principal e de entrada do programa;
 */
int main( void )
{
    uint8_t aux = 0;
	/**
	 * Para usar qualquer GPIO antes é necessário configurar o sentido (entrada ou saída);
	 * Configura todos os pinos do PORTB como saída; 
	 */
    Set_bit( DDRB, LED_BUILDING );  //Pino RB5 como saída;
    Clr_bit( DDRD, BUTTON_1 ); 		//Pino PD2 como entrada; 
	Set_bit( PORTD, BUTTON_1 ); 	//Pull UP em PD2
	/**
	 * Isso é um pisca led, correto? Portanto, loop infinito!
	 */
	USART_Init(); 
	USART_StrTx("Hello\r\n");
	
    for(;;) 
    {
		/**
		 * Button pressionado?
		 */
    	if( !Tst_bit( PIND, BUTTON_1 ) && aux == 0 )  
    	{
			
			USART_StrTx("Button Pressionado.\r\n");
			
    		/**
    		 * Inverte o estado lógico do led building;
    		 */
			Cpl_bit( PORTB, LED_BUILDING ); 
			_delay_ms(100);  //bounce...
			aux = 1; 
		}
		/**
		 * Button solto?
		 */
		if( Tst_bit( PIND, BUTTON_1 ) && aux == 1 )
		{
			USART_StrTx("Button Solto.\r\n");
			
			_delay_ms(100);  //bounce...
			aux = 0; 
		}
		
    }

    return 0; 
}


