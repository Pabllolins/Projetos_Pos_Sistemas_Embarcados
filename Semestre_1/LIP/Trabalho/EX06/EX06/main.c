/**
 * Necessário para usar as macros (ex: _delay_ms);
 */
#define F_CPU 16000000UL

/**
 * Inclui as definições dos registrados do ATMEGA328p ou ATMEGA2560;
 */
#include <avr/io.h>

/**
 * Necessário para usar as interrupções do AVR;
 */
#include <avr/interrupt.h>

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
 * Setor critico;
 */
#define ENTER_CRITICAL() 	cli()
#define EXIT_CRITICAL() 	sei()

/**
 * Variáveis globais; 
 */
int8_t usart_rx_buffer[100]; 
volatile uint16_t indice = 0;
volatile uint8_t frame_status = 0; 

/**
 * Vetor de Interrupção USART RX
 */
ISR( USART_RX_vect )
{
	unsigned char data;

	/**
	 *  Verifica se houve erro durante a recepção serial;
	 *  FE0 = Frame Error;
	 *  DOR0 = Data OverRun;
	 *  UPE0 = USART Parity Error;
	 */
	 
	 data = UDR0;
	
	if((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0)
	{

		/**
		 * Buffer cheio? Caso sim, reinicia indice
		 */		
		if(indice >= sizeof(usart_rx_buffer))
		{
			indice = 0;
		}
		
		/**
		 * Caractere indicador de fim de frame;
		 */
		if( data == '\n' )
		{
			usart_rx_buffer[indice] = '\0'; 
			frame_status = 1; 
			indice = 0;
		} 
		/* Armazena os bytes recebidos no buffer */
		else {
			usart_rx_buffer[indice++] = data; 
		}
	
	}
}
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
	 * Inicializa a Uart
	 */
	USART_Init(); 
	USART_StrTx("Hello\r\n");
	
	/**
	 * Habilita a interrupção Serial;
	 * sei() -> habilita a chave geral das interrupções;
	 * cli() -> desabilita a chave geral das interrupções;
	 */	
	sei(); 
	USART_rxIE();   
	
    for(;;) 
    {
		
		ENTER_CRITICAL();
		{
			if( frame_status )
			{
				USART_StrTx( (char*)usart_rx_buffer ); 
				
				frame_status = 0; 
			}
		}
		EXIT_CRITICAL();
		
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