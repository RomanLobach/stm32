#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

typedef enum {
	RAL_OK,
	RAL_ERROR
} RAL_Status;

typedef enum {
	INPUT  = 0b00U,
	OUTPUT = 0b01U,
	ALT_F  = 0b10U,
	ANALOG = 0b11U
} RAL_PinOutputMode;

typedef enum {
	PUSH_PULL  = 0b0U,
	OPEN_DRAIN = 0b1U,
} RAL_PinOutputType;

typedef enum {
	LOW = 0b00U,
	MED = 0b01U,
	HI 	= 0b11U
} RAL_PinOutputSpeed;

typedef enum {
	NO_PUPD  = 0b00U,
	PUP      = 0b01U,
	PUD      = 0b10U,
	RESERVED = 0b11U
} RAL_PinPullUpPullDownResistor;

typedef enum {
	PIN_LOW = 0,
	PIN_HI  = 1
} RAL_PinLevel;

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  RAL_PinLevel RAL_readPin(GPIO_TypeDef* GPIO, int pinNumber);
  RAL_Status RAL_writePin(GPIO_TypeDef* GPIO, int, RAL_PinLevel pinOutputLevel);
  RAL_Status RAL_pinRegister(
  					GPIO_TypeDef* GPIO,
  					int pinNumber,
					RAL_PinOutputMode mode,
					RAL_PinOutputType type,
					RAL_PinOutputSpeed speed,
					RAL_PinPullUpPullDownResistor pupd
  					);

  //register     portB, pin3
  if(RAL_pinRegister(GPIOB, 3, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
  if(RAL_pinRegister(GPIOA, 0, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
  if(RAL_pinRegister(GPIOA, 1, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
  if(RAL_pinRegister(GPIOA, 3, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();

  if(RAL_pinRegister(GPIOB, 4, INPUT, PUSH_PULL, LOW, PUD) != RAL_OK) Error_Handler();

  while (1)
  {
	  if(RAL_readPin(GPIOB, 4) == PIN_HI) {
		  RAL_writePin(GPIOA, 0, PIN_HI);
	  } else if(RAL_readPin(GPIOB, 4) == PIN_LOW){
		  RAL_writePin(GPIOA, 0, PIN_LOW);
	  }



  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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

/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *------------------------------ RAL -------------------------------------------
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 */


void setTWOBitsHandler(volatile uint32_t* reg, uint32_t setBit, int position) {

	uint32_t resultRegConfig = *reg;
	uint32_t clearMask = ~(0b11u << position);
	resultRegConfig &= clearMask;
	uint32_t setBits = ((uint32_t)setBit) << position;
	resultRegConfig |= setBits;

	*reg = resultRegConfig;
}

RAL_Status RAL_portClockEnable(GPIO_TypeDef* GPIO) {
	int portOffset = (GPIO == GPIOA) ? 17 :
	             (GPIO == GPIOB) ? 18 :
	             (GPIO == GPIOC) ? 19 :
	             (GPIO == GPIOD) ? 20 :
//	             (GPIO == GPIOE) ? 21 :
	             (GPIO == GPIOF) ? 22 : -1;
//	             (GPIO == GPIOG) ? 23 :
//	             (GPIO == GPIOH) ? 16 : -1;

	if (portOffset != -1) {
		if ((RCC->AHBENR & (1U << portOffset)) == 0) {
			RCC->AHBENR |= 1U << portOffset;
		}

		if ((RCC->AHBENR & (1U << portOffset)) != 0) {
			return RAL_OK;
		}
	}

	return RAL_ERROR;
}

RAL_Status RAL_writePin(
				 GPIO_TypeDef* GPIO,
				 int pinNumber,
				 RAL_PinLevel PinOutputLevel
				 ) {
	uint32_t pinSetBit = 1U << pinNumber;
	uint32_t pinResetBit = 1U << (pinNumber + 16);

	if(PinOutputLevel) {
		GPIO->BSRR &= ~pinResetBit;
		GPIO->BSRR |= pinSetBit;
	} else {
		GPIO->BSRR &= ~pinSetBit;
		GPIO->BSRR |= pinResetBit;
	}

	if(
		PinOutputLevel == PIN_HI &&
		(GPIO->BSRR & pinSetBit) == 1 &&
		(GPIO->BSRR & pinResetBit) == 0
	  ) return RAL_ERROR;

	if(
		PinOutputLevel != PIN_LOW &&
		(GPIO->BSRR & pinSetBit) == 0 &&
		(GPIO->BSRR & pinResetBit) == 1
	  ) return RAL_ERROR;

	return RAL_OK;
}


RAL_PinLevel RAL_readPin(GPIO_TypeDef* GPIO, int pinNumber) {

	return (GPIO->IDR & (1U << pinNumber)) ? PIN_HI : PIN_LOW;

}

RAL_Status RAL_pinRegister(
					GPIO_TypeDef* GPIO,
					int pinNumber,
					RAL_PinOutputMode mode,
					RAL_PinOutputType type,
					RAL_PinOutputSpeed speed,
					RAL_PinPullUpPullDownResistor pupd
					) {
	//set GPIO port AHB bus clock
	RAL_portClockEnable(GPIO);

	if(mode == OUTPUT) {
		//set GPIO pin mode
		setTWOBitsHandler(&GPIO->MODER, (uint32_t)mode, pinNumber * 2);
		//set type of pin
		setTWOBitsHandler(&GPIO->OTYPER, (uint32_t)type, pinNumber);
		//set the output speed
		setTWOBitsHandler(&GPIO->OSPEEDR, (uint32_t)speed, pinNumber * 2);
		//set pull-up/pull-down
		setTWOBitsHandler(&GPIO->PUPDR, (uint32_t)pupd, pinNumber * 2);
	} else if (mode == INPUT){
		setTWOBitsHandler(&GPIO->MODER, (uint32_t)mode, pinNumber * 2);
		setTWOBitsHandler(&GPIO->PUPDR, (uint32_t)pupd, pinNumber * 2);
	}


	if(
	   mode == OUTPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == (uint32_t)mode &&
	   (GPIO->OTYPER >> pinNumber & 0x1U) == (uint32_t)type &&
	   (GPIO->OSPEEDR >> (pinNumber * 2) & 0x3U) == (uint32_t)speed &&
	   (GPIO->PUPDR >> (pinNumber * 2) & 0x3U) == (uint32_t)pupd
	  ) return RAL_OK;

	if(
	   mode == INPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == (uint32_t)mode
      ) return RAL_OK;

	return RAL_ERROR;
}

static void MX_GPIO_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();

}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
	  if(RAL_writePin(GPIOB, 3, PIN_HI)) Error_Handler();
  }
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