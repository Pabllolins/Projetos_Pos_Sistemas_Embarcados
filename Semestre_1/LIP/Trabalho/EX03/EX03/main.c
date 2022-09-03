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
 * Diretivas 
 */
#define TRUE  1
#define Set_bit(y,bit)		(y|=(1<<bit))		// Coloca 1 no bit da variável y
#define Clr_bit(y,bit)		(y&=~(1<<bit))		// Coloca 0 no bit da variável y
#define Cpl_bit(y,bit)		(y^=(1<<bit))		// Troca o estado do bit da variável y
#define Tst_bit(y,bit)		(y&(1<<bit))		// Retorna o estado do bit

/**
 * Função principal e de entrada do programa;
 */
int main( void )
{
	/**
	 * Para usar qualquer GPIO antes é necessário configurar o sentido (entrada ou saída);
	 * Configura todos os pinos do PORTB como saída; 
	 */
    Set_bit( DDRB, 5 ); //Pino RB5 como saída;
    Clr_bit( DDRD, 2 ); //Pino PD2 como entrada; 
	Set_bit( PORTD, 2 ); //Pull UP em PD2
	/**
	 * Isso é um pisca led, correto? Portanto, loop infinito!
	 */
    for(;;) 
    {
		/**
		 * Jumpeie no Arduino UNO pino 2 (digital) e GND;
		 */
    	if( !Tst_bit(PIND, 2) )  
    	{
			Cpl_bit( PORTB, 5 );  // Inverte o estado lógico do pino por meio de um XOR;
			_delay_ms(100);  // Delay de 100 milisegundos;
		}
		
    }

    return 0; 
}
