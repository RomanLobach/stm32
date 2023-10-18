/*
 * interrupt_test.h
 *
 *  Created on: Oct 15, 2023
 *      Author: romanlobach
 */

#ifndef INC_INTERRUPT_TEST_H_
#define INC_INTERRUPT_TEST_H_



int ModeChange(char action[1])
{
	if(action == "+")
	{
	  mode++;
	  if(mode == 4)
	  {
		  mode = 0;
	  }
	}
	if(action == "-")
	{
	  mode--;
	  if(mode == 0)
	  {
		  mode = 3;
	  }
	}
}

void BtnInterrupt(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BTN_Red_Pin)
	{
	  HAL_GPIO_WritePin(GPIOA, LED_Blue_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, LED_Red_Pin, GPIO_PIN_SET);
	  ModeChange("+");
	}
	if(GPIO_Pin == BTN_Blue_Pin)
	{
	  HAL_GPIO_WritePin(GPIOA, LED_Red_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, LED_Blue_Pin, GPIO_PIN_SET);
	  ModeChange("-");
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  UNUSED(GPIO_Pin);

  BtnInterrupt(GPIO_Pin);
}

#endif /* INC_INTERRUPT_TEST_H_ */
