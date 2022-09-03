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
 * Lib C
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Lib usart
 */
#include "usart.h"

/**
 * Lib adc
 */
#include "adc.h"

/**
 * Lib lcd
 */
#include "lcd.h"

/**
 * Diretivas 
 */
#define TRUE  			1
#define BUTTON_1 		2
#define LED_BUILDING 	5

/**
 * Setor crítico;
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
	char * pot; 
    uint8_t aux = 0;
	uint16_t adc_result;
	uint8_t string_adc[10];
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

	/**
	 * Inicializa AD;
	 */		
	adc_init(); 
	
	DisplayLCD_Init();
	DisplayLCD_Cmd( LCD_Clear );
	DisplayLCD_Cmd( LCD_Cursor_Off );
	DisplayLCD_Out(1, 1, (char*)"Display 16x2" );
	
    for(;;) 
    {
		
		ENTER_CRITICAL();
		{
			if( frame_status )
			{
				//USART_StrTx( (char*)usart_rx_buffer ); 
				
				/**
				 * Comando: 
				 * [AN0] -> Leitura do canal AN0;
				 */
				if( strstr( (char*) usart_rx_buffer, "[AN0]" ) )
				{
					adc_result = adc_read(0);
					
					/* Converte o valor uint16_t para string via utoa da libC stdlib.h */
					utoa( adc_result, (char*)string_adc, 10 ); 
					
				    /**
					 * Formata o retorno com a leitura do conversor AD conforme: "[AD0:XXXXX]\r\n";
					 */
					 				
					USART_StrTx( "[AN0:" );
					USART_StrTx( (char*)string_adc ); 
					USART_StrTx( "]\r\n" ); 
				}
				/**
				 * Comando: 
				 * [LCD:SENAI ANCHIETA] -> Escreve no display LCD
				 */
				if( (pot = strstr( (char*) usart_rx_buffer, "[LCD:" )) != NULL )
				{
					/* substitui o colchete da string por null */
					pot[5 + strlen(&pot[5])-1] = 0;
					DisplayLCD_Out(1, 1, (char*)&pot[5] );
					USART_StrTx( "[LCD:OK]\r\n" );
				}				
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