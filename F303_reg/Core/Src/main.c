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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct PinConfig PinConfig;

typedef enum {
	RAL_OK,
	RAL_ERROR
} RAL_Status;

typedef enum {
	INPUT  = 0b00U,
	OUTPUT = 0b01U,
	ALT_F  = 0b10U,
	ANALOG = 0b11U
} RAL_PinMode;

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
	NO_PUPD   = 0b00U,
	PULL_UP   = 0b01U,
	PULL_DOWN = 0b10U,
	RESERVED  = 0b11U
} RAL_PinPullUpPullDownResistor;

typedef enum {
	PIN_LOW = 0,
	PIN_HI  = 1
} RAL_PinLevel;

//typedef RAL_Status configurePin(PinConfig *pin);
//typedef RAL_PinLevel readPin(PinConfig *pin);
//typedef RAL_Status writePin(PinConfig *pin, RAL_PinLevel level);

struct PinConfig {
	GPIO_TypeDef* port;
    int pin_number;
    RAL_PinMode mode;
    RAL_PinOutputType type;
    RAL_PinPullUpPullDownResistor pullResistor;
    RAL_PinOutputSpeed speed;
    RAL_PinLevel initLevel;

    // Function pointers
    RAL_Status (*configure)(struct PinConfig *pin);
    RAL_PinLevel (*read)(struct PinConfig *pin);
    RAL_Status (*write)(struct PinConfig *pin, RAL_PinLevel level);

    // Add more configuration parameters as needed
};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

char errorMessage[128] = 'no errors, bro';

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

RAL_PinLevel RAL_readPin(PinConfig *pin);
RAL_Status RAL_writePin(PinConfig *pin, RAL_PinLevel level);
RAL_Status RAL_pinRegister(PinConfig *pin);

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
//  if(RAL_pinRegister(GPIOB, 3, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
//  if(RAL_pinRegister(GPIOA, 0, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
//  if(RAL_pinRegister(GPIOA, 1, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
//  if(RAL_pinRegister(GPIOA, 3, OUTPUT, PUSH_PULL, LOW, NO_PUPD) != RAL_OK) Error_Handler();
//
//  if(RAL_pinRegister(GPIOB, 4, INPUT, PUSH_PULL, LOW, PUD) != RAL_OK) Error_Handler();
//  PinConfig myButton = {0};
//  PinConfig myDiode = {0};
//
//  myButton.port = GPIOB;
//  myButton.pin_number = 4;
//  myButton.mode = INPUT;
//  myButton.type = PUSH_PULL;
//  myButton.pullResistor = NO_PUPD;
//  myButton.speed = LOW;
//  myButton.configure(&myButton);
//
//  myDiode.port = GPIOA;
//  myDiode.pin_number = 0;
//  myDiode.mode = OUTPUT;
//  myDiode.type = PUSH_PULL;
//  myDiode.pullResistor = NO_PUPD;
//  myDiode.speed = LOW;
//  myDiode.configure(&myDiode);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  PinConfig myButton = {0};
  PinConfig myDiode = {0};

  myButton.port = GPIOB;
  myButton.pin_number = 4;
  myButton.mode = INPUT;
  myButton.type = PUSH_PULL;
  myButton.pullResistor = NO_PUPD;
  myButton.speed = LOW;
  myButton.initLevel = PIN_LOW;
  myButton.configure = RAL_pinRegister;
  myButton.read = RAL_readPin;
  myButton.write = RAL_writePin;
  if(myButton.configure(&myButton) != RAL_OK) Error_Handler();
  if(myButton.write(&myButton, myButton.initLevel) != RAL_OK) Error_Handler();
  if(myButton.read(&myButton) != myButton.initLevel) Error_Handler();

  myDiode.port = GPIOA;
  myDiode.pin_number = 0;
  myDiode.mode = OUTPUT;
  myDiode.type = PUSH_PULL;
  myDiode.pullResistor = NO_PUPD;
  myDiode.speed = LOW;
  myDiode.initLevel = PIN_LOW;
  myDiode.configure = RAL_pinRegister;
  myDiode.read = RAL_readPin;
  myDiode.write = RAL_writePin;
  if(myDiode.configure(&myDiode) != RAL_OK) Error_Handler();
  if(myDiode.write(&myDiode, myDiode.initLevel) != RAL_OK) Error_Handler();
  if(myDiode.read(&myDiode) != myDiode.initLevel) Error_Handler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  if (myButton.read(&myButton) == PIN_HI) {
		  myDiode.write(&myDiode, PIN_HI);
	  } else {
		  myDiode.write(&myDiode, PIN_LOW);
	  }

//	  if(RAL_readPin(GPIOB, 4) == PIN_HI) {
//		  RAL_writePin(GPIOA, 0, PIN_HI);
//	  } else if(RAL_readPin(GPIOB, 4) == PIN_LOW){
//		  RAL_writePin(GPIOA, 0, PIN_LOW);
//	  }

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *------------------------------ RAL -------------------------------------------
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 */

void setBitHandler(volatile uint32_t* reg, uint32_t setBit, uint32_t width, int position) {

	uint32_t resultRegConfig = *reg;
	uint32_t clearMask = ~(width << position);
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

RAL_Status RAL_pinRegister(PinConfig *pin) {

	if (pin == NULL || pin->port == NULL) {
		return RAL_ERROR;  // Add appropriate error handling
	}

	GPIO_TypeDef* GPIO = pin->port;
	uint32_t pinNumber = pin->pin_number;
	uint32_t mode = (uint32_t)pin->mode;
	uint32_t type = (uint32_t)pin->type;
	uint32_t speed = (uint32_t)pin->speed;
	uint32_t pullResistor = (uint32_t)pin->pullResistor;

	//set GPIO port AHB bus clock
	RAL_portClockEnable(GPIO);

	if(mode == OUTPUT) {
		//set GPIO pin mode
		setBitHandler(GPIO->MODER, mode, 0b11U, pinNumber * 2);
		//set type of pin
		setBitHandler(GPIO->OTYPER, type, 0b1U, pinNumber);
		//set the output speed
		setBitHandler(GPIO->OSPEEDR, speed, 0b11U, pinNumber * 2);
		//set pull-up/pull-down
		setBitHandler(GPIO->PUPDR, pullResistor, 0b11U, pinNumber * 2);
	} else if (mode == INPUT){
		setBitHandler(GPIO->MODER, mode, 0b11U, pinNumber * 2);
		setBitHandler(GPIO->PUPDR, pullResistor, 0b11U, pinNumber * 2);
	}


	if(
	   mode == OUTPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == mode &&
	   (GPIO->OTYPER >> pinNumber & 0x1U) == type &&
	   (GPIO->OSPEEDR >> (pinNumber * 2) & 0x3U) == speed &&
	   (GPIO->PUPDR >> (pinNumber * 2) & 0x3U) == pullResistor
	  ) return RAL_OK;

	if(
	   mode == INPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == mode
      ) return RAL_OK;

	return RAL_ERROR;
}

RAL_Status RAL_writePin(PinConfig *pin, RAL_PinLevel level) {

	if (pin == NULL || pin->port == NULL) {
		return PIN_LOW;  // Add appropriate error handling
	}

	GPIO_TypeDef* GPIO = pin->port;
	uint32_t pinNumber = pin->pin_number;
	uint32_t pinSetBit = 1U << pinNumber;
	uint32_t pinResetBit = 1U << (pinNumber + 16);

	if(level) {
		GPIO->BSRR &= ~pinResetBit;
		GPIO->BSRR |= pinSetBit;
	} else {
		GPIO->BSRR &= ~pinSetBit;
		GPIO->BSRR |= pinResetBit;
	}

	if(
		 level == PIN_HI &&
		(GPIO->BSRR & pinSetBit) == 1 &&
		(GPIO->BSRR & pinResetBit) == 0
	  ) return RAL_ERROR;

	if(
		 level != PIN_LOW &&
		(GPIO->BSRR & pinSetBit) == 0 &&
		(GPIO->BSRR & pinResetBit) == 1
	  ) return RAL_ERROR;

	return RAL_OK;
}


RAL_PinLevel RAL_readPin(PinConfig *pin) {

	GPIO_TypeDef* GPIO = pin->port;
	uint32_t pinNumber = pin->pin_number;

	return (GPIO->IDR & (1U << pinNumber)) ? PIN_HI : PIN_LOW;

}

//RAL_Status configurePin(PinConfig *pin) {
//    return RAL_pinRegister(
//        pin->port,
//        pin->pin_number,
//        pin->mode,
//        pin->type,
//        pin->speed,
//        pin->pullResistor
//    );
//}
//
//RAL_PinLevel readPin(PinConfig *pin) {
//    return RAL_readPin(pin->port, pin->pin_number);
//}
//
//RAL_Status writePin(PinConfig *pin, RAL_PinLevel level) {
//    return RAL_writePin(pin->port, pin->pin_number, level);
//}

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
	  errorMessage[128] = copystr();
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
