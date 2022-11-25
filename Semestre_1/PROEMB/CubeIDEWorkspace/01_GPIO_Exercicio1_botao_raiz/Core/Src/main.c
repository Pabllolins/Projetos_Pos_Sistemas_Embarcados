/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************

	/*
	 * Autor: Pabllo Lins
	 * Versão: v.1.0
	 * Descrição: Firmware para entrega do capitulo de IOs
	 * Licença: N/A
	 * Data: 18/11/2022
	*/

	/*  Informações adicionais
	* PLACA: NUCLEO-F446RE
	* MCU: STM32F446RE
	* IDE: STM32CubeIDE Version: 1.10.1
	* Extension:
	* Framework:
	* Periferico: GPIO - PortC Pin 13 - B1 - Push Button User da placa
	* Periferico: GPIO - PortA Pin 05 - LD2 - LED 2 verde da placa
	*/

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define true 1
#define false 0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void vGPIOC_13_InitButtonB1();
void vPiscaPiscaLED2();
void vGPIOA_5_InitLED2();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  vGPIOA_5_InitLED2();
  vGPIOC_13_InitButtonB1();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  while((GPIOC->IDR & (0x1<<13)) == 0 )
	  {
		  vPiscaPiscaLED2();
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void vGPIOC_13_InitButtonB1()
{
	//Botão B1 = PORT C pino 13
	uint32_t tmpreg = 0;

	/* Habilita o clock do PORTC */
	RCC->AHB1ENR |= 0x00000004;

	 /* Aguarda estabilizar */
	tmpreg = RCC->AHB1ENR;

	/* C13 Modo entrada (00) */
	GPIOC->MODER = (GPIOB->MODER & ~(0x3<<((2*13)+1)));
	//	(0x3<<((2*13)+1))	= xxxxx110000000000000000000000000
	//	~(0x3<<((2*13)+1))	= xxxxx001111111111111111111111111
	//	(AND)
	//	MODER				= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//	MODER				= xxxxx00xxxxxxxxxxxxxxxxxxxxxxxxx


	/* Tipo push-pull (0) */
	GPIOC->OTYPER = (GPIOC->OTYPER & ~(0x1<<13));

	/* Velocidade: High Speed (11) */
	GPIOC->OSPEEDR = (GPIOC->OSPEEDR | (0x3<<((2*13)+1)));
	//	(0x3<<((2*13)+1))	= xxxxx110000000000000000000000000
	//	(OR)
	//	OSPEEDR				= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//	OSPEEDR				= xxxxx11xxxxxxxxxxxxxxxxxxxxxxxxx


	/* Pull-Up (01) */
	GPIOC->PUPDR = (GPIOC->PUPDR & ~(0x3<<((2*13)+1))) | (0x1<<(2*13));
	//	(0x3<<27))		= xxxxx110000000000000000000000000
	//	~(0x3<<25))		= xxxxx001111111111111111111111111
	//	(AND)
	//	PUPDR			= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	//	PUPDR			= xxxxx00xxxxxxxxxxxxxxxxxxxxxxxxx

	//	(0x1<<(2*13))	= xxxxx010000000000000000000000000
	//	(OR)
	//	PUPDR			= xxxxx00xxxxxxxxxxxxxxxxxxxxxxxxx
	//	PUPDR			= xxxxx01xxxxxxxxxxxxxxxxxxxxxxxxx

	/* Estado inicial resetado '0’ */
	//GPIOA->ODR = (GPIOA->ODR & ~0x1<<5);
	GPIOC->BSRR = 0x1<<(13+16);
}

void vPiscaPiscaLED2(void)
{
	GPIOA->ODR = 0xFFFF;
	HAL_Delay(500);
	GPIOA->ODR = 0x0000;
	HAL_Delay(500);
}

void vGPIOA_5_InitLED2(void)
{
	uint32_t tmpreg = 0;

	/* Habilita o clock do PORTA */
	RCC->AHB1ENR |= 0x01;

	/* Aguarda estabilizar */
	tmpreg = RCC->AHB1ENR;

	/* Modo saída (01) */
	GPIOA->MODER = (GPIOA->MODER & ~(0x3<<(2*5))) | (0x1<<(2*5));

	/* Tipo push-pull (0) */
	GPIOA->OTYPER = (GPIOA->OTYPER & ~0x1<<5);

	/* Velocidade fast (10) */
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~(0x3<<(2*5))) | (0x2<<(2*5));

	/* Sem resistores internos (00) */
	GPIOA->PUPDR = (GPIOA->PUPDR & ~(0x3<<(2*5)));

	/* Estado inicial resetado '0’*/
	//GPIOA->ODR = (GPIOA->ODR & ~0x1<<5);
	GPIOA->BSRR = 0x1<<(5+16);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
