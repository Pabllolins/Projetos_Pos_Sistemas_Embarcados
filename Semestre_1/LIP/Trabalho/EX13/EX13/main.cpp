/*
* -lprintf_flt
*/

#include "defs.h"
#include "serial.h"

/**
 * Para chamar funções escritas em C é necessário utilizar "extern "C""; 
 */
extern "C" {
	void ticks_init( void );
	char ticks( unsigned int interval, unsigned int *tickCompareValue );
}

/**
 * Inicio do Programa;
 */
int main( void )
{
	unsigned int tick1 = 0;
	
	/**
	 * Variáveis para teste da Serial;
	 */
	int i = 10;
	float t = 5.4;
	const char * c = "Bom Dia";
	
	/**
	 * Cria objeto serial;
	 */
	Serial serial;
	
	/**
	 * Inicializa ticks;
	 */
	ticks_init();
	
	/**
	 * Habilita interrupção global;
	 */
	sei();

	/**
	 * Todos os pinos do PORTB como saída e em nível zero;
	 */
	DDRB = 0xFF;
	PORTB = 0x00;

	for(;;)
	{
		/**
		 * informa a constante de tempo e a variável ticks
		 */
		if( ticks( 1000, &tick1 ) )
		{
			PORTB ^= (1 << 5);		// Toggle LED0 each 1000 ms (0,5Hz)

			serial.print(i);
			serial.print(t);
			serial.print(c);
		}
		
	}
	
	return 0;
}

