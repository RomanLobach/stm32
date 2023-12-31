/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>
#include <stdio.h>

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
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x2004c000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x2004c0a0
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x2004c000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x2004c0a0))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __GNUC__ ) /* GNU Compiler */
ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */

#endif

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM14_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_USB_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t userMode = 1;
uint8_t protocol = 1;
uint8_t BTN_DEBOUNCE_TIMER = 20;

uint8_t uartRxBuffer = 0;
uint8_t uartTxBuffer = 0;
uint8_t spiRxBuffer = 0;
uint8_t spiTxBuffer = 0;

uint16_t BTN_RED_initState = GPIO_PIN_SET;
uint16_t BTN_RED_currentState;
uint16_t BTN_RED_pressSlowCount = 0;
uint16_t BTN_RED_releaseSlowCount = 0;
bool BTN_RED_isPressed = false;

uint16_t BTN_BLUE_initState = GPIO_PIN_SET;
uint16_t BTN_BLUE_currentState;
uint16_t BTN_BLUE_pressSlowCount = 0;
uint16_t BTN_BLUE_releaseSlowCount = 0;
bool BTN_BLUE_isPressed = false;

uint16_t BTN_SET_initState = GPIO_PIN_SET;
uint16_t BTN_SET_currentState;
uint16_t BTN_SET_pressSlowCount = 0;
uint16_t BTN_SET_releaseSlowCount = 0;
bool BTN_SET_isPressed = false;

uint16_t BTN_PROTOCOL_initState = GPIO_PIN_SET;
uint16_t BTN_PROTOCOL_currentState;
uint16_t BTN_PROTOCOL_pressSlowCount = 0;
uint16_t BTN_PROTOCOL_releaseSlowCount = 0;
bool BTN_PROTOCOL_isPressed = false;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  ;
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
  MX_ETH_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM14_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_USB_Init();
  /* USER CODE BEGIN 2 */
//

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  setModeLed();
  setProtocolLed();


  while (1)
  {
	  int delayTime = (6 - userMode) * 100;

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(GPIOB, LD1_G_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, LD3_R_Pin, GPIO_PIN_SET);
	  HAL_Delay(delayTime);
	  HAL_GPIO_WritePin(GPIOB, LD3_R_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, LD2_B_Pin, GPIO_PIN_SET);
	  HAL_Delay(delayTime);
	  HAL_GPIO_WritePin(GPIOB, LD2_B_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, LD1_G_Pin, GPIO_PIN_SET);
	  HAL_Delay(delayTime);

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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
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
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

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
  hi2c1.Init.Timing = 0x00808CD2;
  hi2c1.Init.OwnAddress1 = 34;
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
	hspi1.Init.TIMode = SPI_IT_RXNE;
  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;

  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  HAL_SPI_Receive_IT(&hspi1, &spiRxBuffer, 1);
  HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_SET);
  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 0;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 65535;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */
  HAL_TIM_Base_Start_IT(&htim14);
  /* USER CODE END TIM14_Init 2 */

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
  HAL_UART_Receive_IT(&huart2, &uartRxBuffer, 1);
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_USB_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_R_1_Pin|LED_R_5_Pin|LED_R_2_Pin|LED_R_3_Pin
                          |LED_R_4_Pin|LED_UART_Pin|LED_SPI_Pin|LED_I2C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_G_Pin|LD3_R_Pin|LD2_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LED_ERR_Pin|USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_NSS_Out_GPIO_Port, SPI1_NSS_Out_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_R_1_Pin LED_R_5_Pin LED_R_2_Pin LED_R_3_Pin
                           LED_R_4_Pin LED_UART_Pin LED_SPI_Pin LED_I2C_Pin */
  GPIO_InitStruct.Pin = LED_R_1_Pin|LED_R_5_Pin|LED_R_2_Pin|LED_R_3_Pin
                          |LED_R_4_Pin|LED_UART_Pin|LED_SPI_Pin|LED_I2C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_USER_Pin */
  GPIO_InitStruct.Pin = BTN_USER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN_USER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_G_Pin LD3_R_Pin LD2_B_Pin */
  GPIO_InitStruct.Pin = LD1_G_Pin|LD3_R_Pin|LD2_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_B_Pin BTN_R_Pin BTN_SET_Pin BTN_PROTOCOL_Pin */
  GPIO_InitStruct.Pin = BTN_B_Pin|BTN_R_Pin|BTN_SET_Pin|BTN_PROTOCOL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_ERR_Pin USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = LED_ERR_Pin|USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_NSS_Out_Pin */
  GPIO_InitStruct.Pin = SPI1_NSS_Out_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI1_NSS_Out_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void resetModeLed(void)
{

  HAL_GPIO_WritePin(
					GPIOE,
					LED_R_1_Pin|LED_R_2_Pin|LED_R_3_Pin|LED_R_4_Pin|LED_R_5_Pin,
					GPIO_PIN_RESET
				   );
}

void setModeLed(void)
{
	resetModeLed();

	if(userMode == 1)
	{
		HAL_GPIO_WritePin(GPIOE, LED_R_1_Pin, GPIO_PIN_SET);
	}
	if(userMode == 2)
	{
		HAL_GPIO_WritePin(GPIOE, LED_R_2_Pin, GPIO_PIN_SET);
	}
	if(userMode == 3)
	{
		HAL_GPIO_WritePin(GPIOE, LED_R_3_Pin, GPIO_PIN_SET);
	}
	if(userMode == 4)
	{
		HAL_GPIO_WritePin(GPIOE, LED_R_4_Pin, GPIO_PIN_SET);
	}
	if(userMode == 5)
	{
		HAL_GPIO_WritePin(GPIOE, LED_R_5_Pin, GPIO_PIN_SET);
	}
}

void resetProtocolLed(void)
{

	HAL_GPIO_WritePin(GPIOE, LED_UART_Pin|LED_SPI_Pin|LED_I2C_Pin, GPIO_PIN_RESET);

}

void setProtocolLed(void)
{
	resetProtocolLed();
	if(protocol == 1)
	{
		HAL_GPIO_WritePin(GPIOE, LED_UART_Pin, GPIO_PIN_SET);
	}
	if(protocol == 2)
	{
		HAL_GPIO_WritePin(GPIOE, LED_SPI_Pin, GPIO_PIN_SET);
	}
	if(protocol == 3)
	{
		HAL_GPIO_WritePin(GPIOE, LED_I2C_Pin, GPIO_PIN_SET);
	}
}

void UART_Transmit(uint8_t data) {
    HAL_StatusTypeDef status;

    // Transmit a single byte using HAL_UART_Transmit
    status = HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);

    // Check the status
    if (status != HAL_OK) {
    		Error_Handler();
    }
}

void SPI_Transmit(uint8_t data) {
    HAL_StatusTypeDef status;

    // Transmit a single byte using HAL_UART_Transmit
    HAL_GPIO_WritePin(SPI1_NSS_Out_GPIO_Port, SPI1_NSS_Out_Pin, GPIO_PIN_RESET);
    status = HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SPI1_NSS_Out_GPIO_Port, SPI1_NSS_Out_Pin, GPIO_PIN_SET);

    // Check the status
    if (status != HAL_OK) {
    		Error_Handler();
    }
}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{

	if(htim == &htim14)
	{
		BTN_RED_currentState = HAL_GPIO_ReadPin(GPIOG, BTN_R_Pin);
		BTN_SET_currentState = HAL_GPIO_ReadPin(GPIOG, BTN_SET_Pin);
		BTN_BLUE_currentState = HAL_GPIO_ReadPin(GPIOG, BTN_B_Pin);
		BTN_PROTOCOL_currentState = HAL_GPIO_ReadPin(GPIOG, BTN_PROTOCOL_Pin);
		//turning on RED btn
		if(BTN_RED_currentState != BTN_RED_initState)
		{

			++BTN_RED_pressSlowCount;

			if(BTN_RED_pressSlowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_RED_pressSlowCount = 0;

				//onClick RED BTN code
				if(BTN_RED_isPressed == false)
				{
					userMode = userMode + 1;

					if(userMode == 6)
					{

						userMode = 1;

					}


					setModeLed();
					BTN_RED_isPressed = true;
				}
			}

		}
		//turning on BLUE btn
		if(BTN_BLUE_currentState != BTN_BLUE_initState)
		{

			++BTN_BLUE_pressSlowCount;

			if(BTN_BLUE_pressSlowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_BLUE_pressSlowCount = 0;

				//onClick RED BTN code
				if(BTN_BLUE_isPressed == false)
				{
					userMode = userMode - 1;

					if(userMode == 0)
					{

						userMode = 5;

					}

					setModeLed();
					BTN_BLUE_isPressed = true;
				}
			}

		}
		//turning on SET btn
		if(BTN_SET_currentState != BTN_SET_initState)
		{

			++BTN_SET_pressSlowCount;

			if(BTN_SET_pressSlowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_SET_pressSlowCount = 0;

				//onClick RED BTN code
				if(BTN_SET_isPressed == false)
				{

					if(protocol == 1)
					{
						UART_Transmit(userMode);
					}
					if(protocol == 2)
					{
						SPI_Transmit(userMode);
					}
					if(protocol == 3)
					{

					}

					BTN_SET_isPressed = true;
				}
			}

		}
		//turning on PROTOCOL btn
		if(BTN_PROTOCOL_currentState != BTN_PROTOCOL_initState)
		{

			++BTN_PROTOCOL_pressSlowCount;

			if(BTN_PROTOCOL_pressSlowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than RED BTN is pressed
				BTN_PROTOCOL_pressSlowCount = 0;

				//onClick RED BTN code
				if(BTN_PROTOCOL_isPressed == false)
				{

					protocol = protocol + 1;

					if(protocol == 4)
					{

						protocol = 1;

					}

					setProtocolLed();

					BTN_PROTOCOL_isPressed = true;
				}
			}

		}
		//turning off RED btn
		if(BTN_RED_currentState == BTN_RED_initState && BTN_RED_isPressed == true)
		{

			++BTN_RED_releaseSlowCount;

			if(BTN_RED_releaseSlowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_RED_isPressed = false;
				BTN_RED_releaseSlowCount = 0;
				//onRelease RED BTN code

			}
		}
		//turning off RED btn
		if(BTN_BLUE_currentState == BTN_BLUE_initState && BTN_BLUE_isPressed == true)
		{

			++BTN_BLUE_releaseSlowCount;

			if(BTN_BLUE_releaseSlowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_BLUE_isPressed = false;
				BTN_BLUE_releaseSlowCount = 0;
				//onRelease RED BTN code

			}
		}
		//turning off SET btn
		if(BTN_SET_currentState == BTN_SET_initState && BTN_SET_isPressed == true)
		{

			++BTN_SET_releaseSlowCount;

			if(BTN_SET_releaseSlowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_SET_isPressed = false;
				BTN_SET_releaseSlowCount = 0;
				//onRelease RED BTN code

			}
		}

		//turning off PROTOCOL btn
		if(BTN_PROTOCOL_currentState == BTN_PROTOCOL_initState && BTN_PROTOCOL_isPressed == true)
		{

			++BTN_PROTOCOL_releaseSlowCount;

			if(BTN_PROTOCOL_releaseSlowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_PROTOCOL_isPressed = false;
				BTN_PROTOCOL_releaseSlowCount = 0;
				//onRelease RED BTN code

			}
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2 && &uartRxBuffer)
  {
	//userCode
    userMode = uartRxBuffer;
    if(userMode > 5 || userMode < 1) Error_Handler();
    setModeLed();

    //init listening to UART
    HAL_UART_Receive_IT(&huart2, &uartRxBuffer, 1);
  }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    // Handle received data
    // You can access the received data from the 'receivedData' variable
	HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_SET);
	if (hspi->Instance == SPI1 && &spiRxBuffer)
	{
		userMode = spiRxBuffer;
		if(userMode > 5 || userMode < 1) Error_Handler();
		setModeLed();

		HAL_SPI_Receive_IT(&hspi1, &spiRxBuffer, 1);
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
