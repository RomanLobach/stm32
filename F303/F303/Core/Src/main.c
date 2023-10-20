/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
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
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM16_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM17_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int USER_MODE = 1;
char rx_buffer[20];

int BTN_DEBOUNCE_TIMER = 20;

uint16_t BTN_RED_initState = GPIO_PIN_SET;
uint16_t BTN_RED_currentState;
uint16_t BTN_RED_press_slowCount = 0;
uint16_t BTN_RED_release_slowCount = 0;
bool BTN_RED_isPressed = false;

uint16_t BTN_BLUE_initState = GPIO_PIN_SET;
uint16_t BTN_BLUE_currentState;
uint16_t BTN_BLUE_press_slowCount = 0;
uint16_t BTN_BLUE_release_slowCount = 0;
bool BTN_BLUE_isPressed = false;

uint16_t BTN_SET_initState = GPIO_PIN_SET;
uint16_t BTN_SET_currentState;
uint16_t BTN_SET_press_slowCount = 0;
uint16_t BTN_SET_release_slowCount = 0;
bool BTN_SET_isPressed = false;


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
  MX_TIM16_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM17_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  //init listening to UART
  HAL_UART_Receive_IT(&huart2, (uint8_t*)rx_buffer, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setModeLed();
  while(1)
  {
	  int delayTime = (6 - USER_MODE) * 100;

	  HAL_GPIO_WritePin(GPIOB, LED_G_Pin, GPIO_PIN_SET);
	  HAL_Delay(delayTime);
	  HAL_GPIO_WritePin(GPIOB, LED_G_Pin, GPIO_PIN_RESET);
	  HAL_Delay(delayTime);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 8000-1;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 1;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */
  HAL_TIM_Base_Start_IT(&htim16);
  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 0;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 65535;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */
  HAL_TIM_MspPostInit(&htim17);

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_R_1_Pin|LED_R_2_Pin|LED_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_R_3_Pin|LED_R_4_Pin|LED_R_5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_ERR_Pin */
  GPIO_InitStruct.Pin = LED_ERR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_ERR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_R_1_Pin LED_R_2_Pin LED_G_Pin */
  GPIO_InitStruct.Pin = LED_R_1_Pin|LED_R_2_Pin|LED_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_R_3_Pin LED_R_4_Pin LED_R_5_Pin */
  GPIO_InitStruct.Pin = LED_R_3_Pin|LED_R_4_Pin|LED_R_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_B_Pin BTN_SET_Pin */
  GPIO_InitStruct.Pin = BTN_B_Pin|BTN_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_R_Pin */
  GPIO_InitStruct.Pin = BTN_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_R_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

//INTERRUP PROCESSING
void resetModeLed(void)
{

  HAL_GPIO_WritePin(
					GPIOB,
					LED_R_1_Pin|LED_R_2_Pin,
					GPIO_PIN_RESET
				   );
  HAL_GPIO_WritePin(
					GPIOA,
					LED_R_3_Pin|LED_R_4_Pin|LED_R_5_Pin,
					GPIO_PIN_RESET
				   );
}

void setModeLed(void)
{
	if(USER_MODE == 1)
	{
	  resetModeLed();
	  HAL_GPIO_WritePin(GPIOB, LED_R_1_Pin, GPIO_PIN_SET);
	}
	if(USER_MODE == 2)
	{
	  resetModeLed();
	  HAL_GPIO_WritePin(GPIOB, LED_R_2_Pin, GPIO_PIN_SET);
	}
	if(USER_MODE == 3)
	{
	  resetModeLed();
	  HAL_GPIO_WritePin(GPIOA, LED_R_3_Pin, GPIO_PIN_SET);
	}
	if(USER_MODE == 4)
	{
	  resetModeLed();
	  HAL_GPIO_WritePin(GPIOA, LED_R_4_Pin, GPIO_PIN_SET);
	}
	if(USER_MODE == 5)
	{
	  resetModeLed();
	  HAL_GPIO_WritePin(GPIOA, LED_R_5_Pin, GPIO_PIN_SET);
	}
}

void UART_Transmit(void* data)
{
	char tx_buffer[20];
	sprintf(tx_buffer, "%d", data);
	HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 0xFFFF);

}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)				//TIM16 interrupt processing
{

	if(htim == &htim16)
	{
		BTN_RED_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_R_Pin);
		BTN_SET_currentState = HAL_GPIO_ReadPin(GPIOA, BTN_SET_Pin);
		BTN_BLUE_currentState = HAL_GPIO_ReadPin(GPIOA, BTN_B_Pin);
		//turning on RED btn
		if(BTN_RED_currentState != BTN_RED_initState)
		{

			++BTN_RED_press_slowCount;

			if(BTN_RED_press_slowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_RED_press_slowCount = 0;

				//onClick RED BTN code
				if(BTN_RED_isPressed == false)
				{
					USER_MODE = USER_MODE + 1;

					if(USER_MODE == 6)
					{

						USER_MODE = 1;

					}


					setModeLed();
					BTN_RED_isPressed = true;
				}
			}

		}
		//turning on BLUE btn
		if(BTN_BLUE_currentState != BTN_BLUE_initState)
		{

			++BTN_BLUE_press_slowCount;

			if(BTN_BLUE_press_slowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_BLUE_press_slowCount = 0;

				//onClick RED BTN code
				if(BTN_BLUE_isPressed == false)
				{
					USER_MODE = USER_MODE - 1;

					if(USER_MODE == 0)
					{

						USER_MODE = 5;

					}

					setModeLed();
					BTN_BLUE_isPressed = true;
				}
			}

		}
		//turning on SET btn
		if(BTN_SET_currentState != BTN_SET_initState)
		{

			++BTN_SET_press_slowCount;

			if(BTN_SET_press_slowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_SET_press_slowCount = 0;

				//onClick RED BTN code
				if(BTN_SET_isPressed == false)
				{

					UART_Transmit(USER_MODE);

					BTN_SET_isPressed = true;
				}
			}

		}
		//turning off RED btn
		if(BTN_RED_currentState == BTN_RED_initState && BTN_RED_isPressed == true)
		{

			++BTN_RED_release_slowCount;

			if(BTN_RED_release_slowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_RED_isPressed = false;
				BTN_RED_release_slowCount = 0;
				//onRelease RED BTN code

			}
		}
		//turning off RED btn
		if(BTN_BLUE_currentState == BTN_BLUE_initState && BTN_BLUE_isPressed == true)
		{

			++BTN_BLUE_release_slowCount;

			if(BTN_BLUE_release_slowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_BLUE_isPressed = false;
				BTN_BLUE_release_slowCount = 0;
				//onRelease RED BTN code

			}
		}
		//turning off SET btn
		if(BTN_SET_currentState == BTN_SET_initState && BTN_SET_isPressed == true)
		{

			++BTN_SET_release_slowCount;

			if(BTN_SET_release_slowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_SET_isPressed = false;
				BTN_SET_release_slowCount = 0;
				//onRelease RED BTN code

			}
		}
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
	//userCode
    USER_MODE = atoi(rx_buffer);
    setModeLed();

    //init listening to UART
    HAL_UART_Receive_IT(&huart2, (uint8_t*)rx_buffer, 1);
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_SET);
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  return;
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
