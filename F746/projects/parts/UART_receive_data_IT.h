
/* USER CODE BEGIN Includes */
#include "stm32f3xx_hal.h" 	// usually it's already included in main.h
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
UART_HandleTypeDef huart2;  //defining handler for uart2 interrupt

char rx_buffer[20];  //defining receive buffer. this example is for 20 char long phrase
volatile data;
/* USER CODE END PV */

/*
 * USART/UART init fuction and interruption listener on UART2 example
 *
 * launch UART init:
 * MX_USART2_UART_Init(); - launch this in main before while(1)
 *
 * starting listening to UART receive interruption:
 * HAL_UART_Receive_IT(&huart2, (uint8_t*)rx_buffer, 1); - launch this in main before while(1)
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  if (huart->Instance == USART2)
  {
	// onRECEIVE user code here
	data = atoi(rx_buffer);

    //init listening to UART_IT again
    HAL_UART_Receive_IT(&huart2, (uint8_t*)rx_buffer, 1);
  }
}
