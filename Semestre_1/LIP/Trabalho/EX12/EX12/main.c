#include "defs.h"
#include "ticks.h"

int main( void )
{
	unsigned int tick1 = 0;
	
	DDRB = 0xFF;										
	PORTB = 0x00;									
	
	ticks_init();
	
	sei();												
	
	for(;;)
	{
		if( ticks( 1000, &tick1 ) )
		{
			PORTB ^= (1 << 5);		// Toggle LED0 each 1000 ms (0,5Hz)
		}
		
	}
	
	return 0;
}
