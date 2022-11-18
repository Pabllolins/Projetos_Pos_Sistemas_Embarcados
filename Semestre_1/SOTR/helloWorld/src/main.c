/**
 * Lib C;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * FreeRTOS
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

/**
 * Log
 */
#include "esp_system.h"
#include "esp_log.h"

/**
 * Definições;
 */
#define DEBUG 1

/**
 * Variáveis;
 */
static const char * TAG = "Main: ";

/**
 * Início do Programa;
 */
void app_main( void )
{
    uint32_t count = 0; 

    if( DEBUG )
        ESP_LOGI( TAG, "App main run ... " ); 

    for( ;; )
    {
        if( DEBUG )
            ESP_LOGI( TAG, "Count: %d", count++ );

        vTaskDelay( 100 / portTICK_PERIOD_MS );
    }

    return;
}