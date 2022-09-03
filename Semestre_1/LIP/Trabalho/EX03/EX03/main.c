#define F_CPU 16000000UL

/**
 * Inclui as defini��es dos registrados do ATMEGA328p ou ATMEGA2560;
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
#define Set_bit(y,bit)		(y|=(1<<bit))		// Coloca 1 no bit da vari�vel y
#define Clr_bit(y,bit)		(y&=~(1<<bit))		// Coloca 0 no bit da vari�vel y
#define Cpl_bit(y,bit)		(y^=(1<<bit))		// Troca o estado do bit da vari�vel y
#define Tst_bit(y,bit)		(y&(1<<bit))		// Retorna o estado do bit

/**
 * Fun��o principal e de entrada do programa;
 */
int main( void )
{
	/**
	 * Para usar qualquer GPIO antes � necess�rio configurar o sentido (entrada ou sa�da);
	 * Configura todos os pinos do PORTB como sa�da; 
	 */
    Set_bit( DDRB, 5 ); //Pino RB5 como sa�da;
    Clr_bit( DDRD, 2 ); //Pino PD2 como entrada; 
	Set_bit( PORTD, 2 ); //Pull UP em PD2
	/**
	 * Isso � um pisca led, correto? Portanto, loop infinito!
	 */
    for(;;) 
    {
		/**
		 * Jumpeie no Arduino UNO pino 2 (digital) e GND;
		 */
    	if( !Tst_bit(PIND, 2) )  
    	{
			Cpl_bit( PORTB, 5 );  // Inverte o estado l�gico do pino por meio de um XOR;
			_delay_ms(100);  // Delay de 100 milisegundos;
		}
		
    }

    return 0; 
}
