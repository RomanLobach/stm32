
/* USER CODE BEGIN Includes */
#include "stm32f3xx_hal.h" 	// usually it's already included in main.h
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
char tx_buffer[20];  //defining transfer buffer. this example is for 20 char long phrase
/* USER CODE END PV */

void UART_Transmit(void* data)
{
	sprintf(tx_buffer, "%d", data);
	HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 0xFFFF);

}

/*
 * USART/UART init fuction on UART2 example
 *
 * MX_USART2_UART_Init(); - launch this in main before while(1)
 *
static void MX_USART2_UART_Init(void)
{
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
}

 */
