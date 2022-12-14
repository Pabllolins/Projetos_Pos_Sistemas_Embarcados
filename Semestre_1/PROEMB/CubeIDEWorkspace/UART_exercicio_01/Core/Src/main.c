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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char RX = '0';
uint8_t u8_LastValue = '0';
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void USART2_Init(void);
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
  MX_GPIO_Init();
  //MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  USART2_Init();
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	//Se o registrador RTR n??o est?? vazio
	if(USART2->SR & USART_SR_RXNE)
	{
		if((0x30 <= USART2->DR) && (0x39 >= USART2->DR))
		{
			RX = USART2->DR;
			u8_LastValue = RX;
		}
	}
	else
	{
		RX = u8_LastValue;
	}


	while((48 <= RX) && (57 >= RX))
	{
		switch(RX)
		{
			case '0':
				//while(0x30 == USART2->DR)
				while('0' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('0' != USART2->DR)
						{
							if(('0' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '1':
				while('1' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(26);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('1' != USART2->DR)
						{
							if(('1' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '2':
				while('2' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(2);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(23);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('2' != USART2->DR)
						{
							if(('2' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '3':
				while('3' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(3);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(20);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('3' != USART2->DR)
						{
							if(('3' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '4':
				while('4' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(4);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(17);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('4' != USART2->DR)
						{
							if(('4' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '5':
				while('5' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(5);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(14);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('5' != USART2->DR)
						{
							if(('5' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '6':
				while('6' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(6);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(11);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('6' != USART2->DR)
						{
							if(('6' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '7':
				while('7' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(7);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(8);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('7' != USART2->DR)
						{
							if(('7' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '8':
				while('8' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(8);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(5);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('8' != USART2->DR)
						{
							if(('8' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			case '9':
				while('9' == RX)
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(9);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(2);

					if(USART2->SR & USART_SR_RXNE)
					{
						if('9' != USART2->DR)
						{
							if(('9' != USART2->DR) && ('\r' != USART2->DR) && ('\n' != USART2->DR) && ((48 <= USART2->DR) && (57 >= USART2->DR)))
							{
								RX = USART2->DR;
								break;
							}
						}
					}
				}
			break;

			default:
	//						if((0x00 != USART2->DR) && (0x0d != USART2->DR) && (0x0a != USART2->DR))
	//						{
	//							USART2->DR = u8_LastValue;
	//						}
			break;
		}
	}

  }
//  }
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
//Fun????o de inicializa????o da USART2 (PA2-TX, PA3-RX)
//modo ass??ncrono, 9.600 bps, 8N1, APB1 = 42 MHz
void USART2_Init(void)
{
	uint32_t tmpreg = 0;
	//Configurar os GPIOs

	//Ativar o clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Aguardar o clock estabilizar
	tmpreg = RCC->AHB1ENR;

	//Definir o modo de funcionamento alternativo (10)
	GPIOA->MODER &= ~(GPIO_MODER_MODE3_Msk | GPIO_MODER_MODE2_Msk);
	GPIOA->MODER |= GPIO_MODER_MODE3_1;
	GPIOA->MODER |= GPIO_MODER_MODE2_1;

	//Ajustar a velocidade de comuta????o para High Speed (opcional)
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR2);

	//Definir a fun????o alternativa (7)
	GPIOA->AFR[0] |= (GPIO_AFRH_AFRH3_2 | GPIO_AFRH_AFRH3_1 | GPIO_AFRH_AFRH3_0);

	GPIOA->AFR[0] |= (GPIO_AFRH_AFRH2_2 | GPIO_AFRH_AFRH2_1 | GPIO_AFRH_AFRH2_0);

	//Ativar o clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	//Aguardar o clock estabilizar
	tmpreg = RCC->APB1ENR;

	//Desabilitar a USART
	USART2->CR1 &= ~USART_CR1_UE;

	//Programar o word lenght (M bit) = 0 (1 Start bit, 8 Data bits, n Stop bit)
	USART2->CR1 &= ~USART_CR1_M;

	//Programar o n??mero de stop bits = 00 (1)
	USART2->CR2 &= ~USART_CR2_STOP_Msk;

	//Ajustar o baud rate = 9.600 bps
	USART2->BRR = 0x1117;

	//Habilitar a transmiss??o e recep????o
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);

	//Habilitar a USART
	USART2->CR1 |= USART_CR1_UE;
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
