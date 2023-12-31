/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>

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


/* USER CODE BEGIN PV */
TIM_HandleTypeDef htim16;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int mode = 0;

int BTN_DEBOUNCE_TIMER = 20;
int LED_GREEN_INTERRUPT_COUNTER = 0;

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
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    /* USER CODE END WHILE */
	  HAL_GPIO_WritePin(GPIOB, LED_Green_I_Pin, GPIO_PIN_SET);
	  HAL_Delay(300);
	  HAL_GPIO_WritePin(GPIOB, LED_Green_I_Pin, GPIO_PIN_RESET);
	  HAL_Delay(300);


	  if(mode == 0)
	  {
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
		                            |LED_Mode_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin, GPIO_PIN_SET);
	  }
	  if(mode == 1)
	  {
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
		                            |LED_Mode_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_1_Pin, GPIO_PIN_SET);
	  }
	  if(mode == 2)
	  {
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
		                            |LED_Mode_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_2_Pin, GPIO_PIN_SET);
	  }
	  if(mode == 3)
	  {
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
		                            |LED_Mode_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, LED_Mode_3_Pin, GPIO_PIN_SET);
	  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Red_Pin|LED_Blue_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
                          |LED_Mode_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Red_Pin LED_Blue_Pin */
  GPIO_InitStruct.Pin = LED_Red_Pin|LED_Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Mode_0_Pin LED_Mode_3_Pin LED_Green_I_Pin LED_Mode_2_Pin
                           LED_Mode_1_Pin */
  GPIO_InitStruct.Pin = LED_Mode_0_Pin|LED_Mode_3_Pin|LED_Green_I_Pin|LED_Mode_2_Pin
                          |LED_Mode_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_Red_Pin BTN_Blue_Pin */
  GPIO_InitStruct.Pin = BTN_Red_Pin|BTN_Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  BtnInterrupt(GPIO_Pin);
//}
//typedef void (*VoidFunction)();
//
//void buttonSwitchOnHandler(
//		uint16_t btn_initState,
//		uint16_t btn_currentState,
//		uint16_t btn_pressCounter,
//		bool btn_isPressed,
//		int debounceTimer,
//		VoidFunction userCallback
//		)
//{
//
//	++btn_pressCounter;
//
//	if(btn_pressCounter > debounceTimer)
//	{
//		btn_pressCounter = 0;
//
//		if(!btn_isPressed)
//		{
//			if(userCallback) userCallback();
//			btn_isPressed = true;
//		}
//	}
//}
//
//void buttonSwitchOffHandler(
//		uint16_t btn_initState,
//		uint16_t btn_currentState,
//		uint16_t btn_releaseCounter,
//		bool btn_isPressed,
//		int debounceTimer,
//		VoidFunction userCallback
//		)
//{
//
//	++btn_releaseCounter;
//
//	if(btn_releaseCounter > debounceTimer)
//	{
//
//		btn_isPressed = false;
//		btn_releaseCounter = 0;
//		if(userCallback) userCallback();
//
//	}
//
//}
//
//void increaseMode(void)
//{
//	mode++;
//
//	if(mode > 3)
//	{
//		mode = 0;
//	}
//}
//
//void decreaseMode(void)
//{
//	mode--;
//
//	if(mode < 0)
//	{
//		mode = 3;
//	}
//}
//
//void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
//{
//
//	if(htim == &htim16)
//	{
//		BTN_RED_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_Red_Pin);
//		BTN_BLUE_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_Blue_Pin);
//		//turning on RED btn
//		if(BTN_RED_currentState != BTN_RED_initState) buttonSwitchOnHandler(
//																			BTN_RED_initState,
//																			BTN_RED_currentState,
//																			BTN_RED_press_slowCount,
//																			BTN_RED_isPressed,
//																			BTN_DEBOUNCE_TIMER,
//																			increaseMode
//																			);
//
//		//turning on BLUE btn
//		if(BTN_BLUE_currentState != BTN_BLUE_initState) buttonSwitchOnHandler(
//																			  BTN_BLUE_initState,
//																			  BTN_BLUE_currentState,
//																			  BTN_BLUE_press_slowCount,
//																			  BTN_BLUE_isPressed,
//																			  BTN_DEBOUNCE_TIMER,
//																			  decreaseMode
//																			  );
//		//turning off RED btn
//		if(BTN_RED_currentState == BTN_RED_initState && BTN_RED_isPressed == true) buttonSwitchOffHandler(
//																										  BTN_RED_initState,
//																										  BTN_RED_currentState,
//																										  BTN_RED_release_slowCount,
//																										  BTN_RED_isPressed,
//																										  BTN_DEBOUNCE_TIMER,
//																										  0
//																										  );
//		//turning off RED btn
//		if(BTN_BLUE_currentState == BTN_BLUE_initState && BTN_BLUE_isPressed == true) buttonSwitchOffHandler(
//																											  BTN_BLUE_initState,
//																											  BTN_BLUE_currentState,
//																											  BTN_BLUE_release_slowCount,
//																											  BTN_BLUE_isPressed,
//																											  BTN_DEBOUNCE_TIMER,
//																											  0
//																											  );
//	}
//}


void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{

	if(htim == &htim16)
	{
		BTN_RED_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_Red_Pin);
		BTN_BLUE_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_Blue_Pin);
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
					mode = mode + 1;

					if(mode > 3)
					{

						mode = 0;

					}

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
					mode = mode - 1;

					if(mode < 0)
					{

						mode = 3;

					}

					BTN_BLUE_isPressed = true;
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
