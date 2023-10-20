
/* USER CODE BEGIN Includes */
#include "stm32f3xx_hal.h" 	// usually it's already included in main.h
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */

//defining BTN states
uint16_t BTN_initState = GPIO_PIN_SET; //in case if GPIO default level HI (use pull-up resistor)
uint16_t BTN_currentState;
uint16_t BTN_press_slowCount = 0;
uint16_t BTN_release_slowCount = 0;
bool BTN_isPressed = false;

//defining debounce time window
int BTN_DEBOUNCE_TIMER = 20;

//defining handler for your timer (this example for exmpl TIM16)
TIM_HandleTypeDef htim16;

/*
 * TIM initital funcrion
 *
static void MX_TIM16_Init(void)
{
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 8000-1;									//init TIM prescaler to set TIM interrupt interval
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 1;											//init TIM prescaler to set TIM interrupt interval
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_Base_Start_IT(&htim16); 									//don't forget to include iterrupt starting function

}
 */

/* USER CODE END PV */


/* USER CODE BEGIN 4 */
//TIM interrupt processing
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{

	if(htim == &htim16) //cheking if interrupt came from our TIM
	{
		BTN_currentState = HAL_GPIO_ReadPin(GPIOB, BTN_Pin);

		//onCLICK code
		if(BTN_currentState != BTN_initState)
		{
			++BTN_press_slowCount;

			if(BTN_press_slowCount > BTN_DEBOUNCE_TIMER)
			{
				//if you are here than BTN is pressed
				BTN_press_slowCount = 0;

				if(BTN_isPressed == false)
				{

					/* ONCLICK YOUR CODE HERE */

					BTN_isPressed = true;
				}
			}

		}
		//onRELEASE code
		if(BTN_currentState == BTN_initState && BTN_isPressed == true)
		{

			++BTN_release_slowCount;

			if(BTN_release_slowCount > BTN_DEBOUNCE_TIMER)
			{

				BTN_isPressed = false;
				BTN_release_slowCount = 0;

				/* ONRELEASE YOUR CODE HERE */

			}
		}

	}
}
/* USER CODE BEGIN 4 */
