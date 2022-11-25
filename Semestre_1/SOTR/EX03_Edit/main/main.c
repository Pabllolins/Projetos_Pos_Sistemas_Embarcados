/* --------------------------------------------------------------------------
  Co-autor: Pabllo Lins

  Board: DOIT v1
  Hardware: NodeMCU ESP32
  Espressif SDK-IDF

  Baseado no exemplo 03 dado em aula do autor: Prof° Fernando Simplicio;

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdint.h>  
#include <string.h>

/* FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h" //Drivers
#include "esp_log.h" //logs

/*Defines*/
#define GPIO_NUM_0		0
#define LED_BUILT_IN 	2 //Led building azul do kit ESP32
#define BUTTON_BOOT  	GPIO_NUM_0

/*Variaveis globais*/
static const char * TAG = "";

/* Handlers para filas*/
QueueHandle_t HandlerFilaBotaoBoot; 
QueueHandle_t HandlerFilaCountBotaoBoot; 
QueueHandle_t HandlerFilaEstadoBotaoBoot; 

/*Protótipo de funcoes*/
void Tarefa_Botao_Boot(void * pvParameter);
void Tarefa_Imprime_Serial(void * pvParameter);
void Tarefa_LED_BuiltIn(void *pvParameter);


/*****************************************************************************/
void app_main( void )
{
	/*
	Cria uma fila para o botão de boot da placa se valendo do hanlder criado anteriormente 
	@param 1 - 5 posições para a fila
	@param 2 - Elementos do tipo *char
	*/
	if( (HandlerFilaBotaoBoot = xQueueCreate( 5, sizeof( char *)) ) == NULL )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar HandlerFilaBotaoBoot.\n" );
		return;
	} 

	if( (HandlerFilaCountBotaoBoot = xQueueCreate( 1, sizeof( uint8_t *) )) == NULL )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar HandlerFilaCountBotaoBoot .\n" );
		return;
	} 

	if( (HandlerFilaEstadoBotaoBoot = xQueueCreate( 1, sizeof( uint8_t *) )) == NULL )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar HandlerFilaEstadoBotaoBoot.\n" );
		return;
	} 
	
	/*
	Cria tarefa e testa a se a criação dela foi bem sucedida
	@param 1 - Nome da função 
	@param 2 - String de ID da função
	@param 3 - Memoria alocada para a tarefa criada
	@param 4 - parametro privaddo = NULL
	@param 5 - Prioridade = 5
	@param 6 - Handle = NULL 
	*/
    if( ( xTaskCreate( Tarefa_LED_BuiltIn, "Tarefa_LED_BuiltIn", configMINIMAL_STACK_SIZE, NULL, 5, NULL )) != pdTRUE )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar Tarefa_LED_BuiltIn.\n" );	
		return;		
	}
	
	if( (xTaskCreate( Tarefa_Imprime_Serial, "Tarefa_Imprime_Serial", 2048, NULL, 5, NULL )) != pdTRUE )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar Tarefa_Imprime_Serial.\n" );	
		return;		
	}
	
	if( (xTaskCreate( Tarefa_Botao_Boot, "Tarefa_Botao_Boot", 2048, NULL, 5, NULL )) != pdTRUE )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar Tarefa_Botao_Boot.\n" );	
		return;		
	}	
}
/*****************************************************************************/


/*****************************************************************************/
void Tarefa_Botao_Boot( void * pvParameter )
{
	uint32_t status = 0;
	const char * Msg_para_Enviar =  "Msg teste";
	const uint8_t * Counter_Button = 0;				 		

    /* Configuração da GPIO 0 como entrada */
    gpio_pad_select_gpio( BUTTON_BOOT );
    gpio_set_direction( BUTTON_BOOT, GPIO_MODE_INPUT );
    gpio_set_pull_mode( BUTTON_BOOT, GPIO_PULLUP_ONLY );

	for(;;)
	{
		//Botão pressionado?
		if( gpio_get_level(BUTTON_BOOT) == 0 && status == 0)
		{
			/**
			 * Delay necessário para não processar o bounce causado
			 * pelo acionamento do botão;
			 */
			vTaskDelay( 100 / portTICK_PERIOD_MS ); 

			/**
			 * O botão ainda está sendo pressionado? Sim, então...
			 */
			if( gpio_get_level(BUTTON_BOOT) == 0 && status == 0)
			{
				Counter_Button++; 	

				ESP_LOGI( TAG, "Botao Pressionado." );

				//Envia na o endereço do vetor na fila;
				if( xQueueSend( HandlerFilaBotaoBoot, &Msg_para_Enviar, (10/portTICK_PERIOD_MS) ) == pdPASS )
				{
					//ESP_LOGI( TAG, "\n\n Mensagem enviada para a fila com sucesso!");									
				}

				//Envia na o endereço do vetor na fila;
				if( xQueueSend(HandlerFilaCountBotaoBoot, &Counter_Button, (10/portTICK_PERIOD_MS)) == pdPASS )
				{
					ESP_LOGI( TAG, "Contador enviado");
				}
				
				status = 1;			
				xQueueSend(HandlerFilaEstadoBotaoBoot, &status, (10/portTICK_PERIOD_MS));
			}

		}

		/* Botão Solto? */
		if( gpio_get_level(BUTTON_BOOT) == 1 && status == 1)
		{
			/**
			 * Delay necessário para não processar o bounce causado
			 * pelo acionamento do botão;
			 */
			vTaskDelay( 100 / portTICK_PERIOD_MS ); 

			/**
			 * O botão ainda está realmente solto? Sim, então...
			 */
			if( gpio_get_level(BUTTON_BOOT) == 1 && status == 1)
			{
				ESP_LOGI( TAG, "Botao Solto." );
				status = 0; 
				
				xQueueSend(HandlerFilaEstadoBotaoBoot, &status, (10/portTICK_PERIOD_MS));							
			}
		}
		
		/* Bloqueia esta task por 10ms */
		vTaskDelay( 10/portTICK_PERIOD_MS );
	}

	/* Este comando não deve ser executado, será executado se der ruim no laço for */
    vTaskDelete(NULL);	
}
/*****************************************************************************/


/*****************************************************************************/
/*
 * Esta task é responsável em receber o valor de count
 * por meio da leitura da fila e imprimir na saída do console.
*/
void Tarefa_Imprime_Serial( void * pvParameter )
{
	char * Msg_para_Enviar = NULL; 
	uint8_t Contador = 0; 
	
	for(;;)
	{
		/* Aguarda a chegada de algum valor na fila */
		if( xQueueReceive( HandlerFilaBotaoBoot, &Msg_para_Enviar, portMAX_DELAY ) == pdPASS )
		{
			ESP_LOGI( TAG, "Mensagem Recebida = %s", Msg_para_Enviar );
		}	
		
		if( xQueueReceive(HandlerFilaCountBotaoBoot, &Contador, portMAX_DELAY ) == pdPASS )
		{
			ESP_LOGI( TAG, "Contador recebido = %d\n", Contador);
		} 

		vTaskDelay( 10/portTICK_PERIOD_MS );
	}

	/* Este comando não deve ser executado, será executado se der ruim no laço for */
    vTaskDelete(NULL);
}
/*****************************************************************************/


/*****************************************************************************/
void Tarefa_LED_BuiltIn(void *pvParameter)
{
	uint32_t statusBotao = 0;
	
	/*Configura a GPIO2 do ESP32 como GPIO-OUTPUT - Led BuiltIn do ESP32 */
    gpio_pad_select_gpio( LED_BUILT_IN );
    gpio_set_direction( LED_BUILT_IN, GPIO_MODE_OUTPUT );

    for(;;)
	{
		xQueueReceive( HandlerFilaEstadoBotaoBoot, &statusBotao, portMAX_DELAY ); 

		while(statusBotao == 1)
		{
	        gpio_set_level( LED_BUILT_IN, 1 );
	        vTaskDelay( 1000 / portTICK_PERIOD_MS );			

	        gpio_set_level( LED_BUILT_IN, 0 );
	        vTaskDelay( 1000 / portTICK_PERIOD_MS ); 

			if( xQueueReceive( HandlerFilaEstadoBotaoBoot, &statusBotao, (1/portTICK_PERIOD_MS)) == pdPASS )
			{
				if(statusBotao == 0)
				{		        	
					gpio_set_level( LED_BUILT_IN, 0 );	
				}
			}
		}
    }
    /* Este comando não deve ser executado, será executado se der ruim no laço for */
    vTaskDelete(NULL);
}
/*****************************************************************************/

