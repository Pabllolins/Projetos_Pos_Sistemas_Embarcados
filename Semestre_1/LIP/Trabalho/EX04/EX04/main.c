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
#define TRUE  			1
#define BUTTON_1 		2
#define LED_BUILDING 	5
#define Set_bit(y,bit)		(y|=(1<<bit))		// Coloca 1 no bit da vari�vel y
#define Clr_bit(y,bit)		(y&=~(1<<bit))		// Coloca 0 no bit da vari�vel y
#define Cpl_bit(y,bit)		(y^=(1<<bit))		// Troca o estado do bit da vari�vel y
#define Tst_bit(y,bit)		(y&(1<<bit))		// Retorna o estado do bit

/**
 * Fun��o principal e de entrada do programa;
 */
int main( void )
{
    uint8_t aux = 0;
	/**
	 * Para usar qualquer GPIO antes � necess�rio configurar o sentido (entrada ou sa�da);
	 * Configura todos os pinos do PORTB como sa�da; 
	 */
    Set_bit( DDRB, LED_BUILDING );  //Pino RB5 como sa�da;
    Clr_bit( DDRD, BUTTON_1 ); 		//Pino PD2 como entrada; 
	Set_bit( PORTD, BUTTON_1 ); 	//Pull UP em PD2
	/**
	 * Isso � um pisca led, correto? Portanto, loop infinito!
	 */
    for(;;) 
    {
		/**
		 * Button pressionado?
		 */
    	if( !Tst_bit( PIND, BUTTON_1 ) && aux == 0 )  
    	{
    		/**
    		 * Inverte o estado l�gico do led building;
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
			_delay_ms(100);  //bounce...
			aux = 0; 
		}
		
    }

    return 0; 
}


