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
#include "i2c.h"
#include "spi.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RAL_main.h"
#include "ssd1306.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "BME.h"
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
char tMessage[16];
char hMessage[16];
char pMessagePa[16];
char pMessageHg[16];
char aMessage[16];
char dMessage[16];
//char adrMessage[] = 	 "Addr:";
char result;
//
//uint16_t xOffset = 2;
//uint16_t yOffset = 2;

float Temperature, Pressure, Humidity;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* USER CODE BEGIN PFP */
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ssd1306_Init();

  BME280_Config(OSRS_2, OSRS_16, OSRS_1, MODE_NORMAL, T_SB_0p5, IIR_16);
//  ssd1306_Fill(White);
//  ssd1306_UpdateScreen();


//  result = ssd1306_WriteString(temperature, Font_7x10, White);
//  ssd1306_SetCursor(3, 16);
//  result = ssd1306_WriteString(humidity, Font_7x10, White);
//  ssd1306_SetCursor(3, 26);
//  result = ssd1306_WriteString(pressure, Font_7x10, White);
//  ssd1306_SetCursor(3, 40);
//  result = ssd1306_WriteString(adrMessage, Font_7x10, White);
//  ssd1306_SetCursor(53, 40);
//  result = ssd1306_WriteString(addressesString, Font_7x10, White);
//  ssd1306_UpdateScreen();

//  void I2C_Scan(I2C_HandleTypeDef *hi2c) {
//      HAL_StatusTypeDef res;
//      char str[] = "00";
//      printf("Scanning I2C bus...\n");
//
//      for (uint8_t address = 1; address <= 127; address++) {
//          // The HAL_I2C_IsDeviceReady function checks if a device responds at a given address
//          res = HAL_I2C_IsDeviceReady(hi2c, address << 1, 1, 10);
//
//          if (res == HAL_OK) {
//        	      sprintf(str, "0x%01X", address);
//        	  	  ssd1306_SetCursor(xOffset, yOffset);
//        	  	  result = ssd1306_WriteString(str, Font_7x10, White);
//		  	  ssd1306_UpdateScreen();
//
//		  	  xOffset = xOffset + 30;
//		  	  if(xOffset > 112) {
//		  		  xOffset = 3;
//		  		  yOffset = yOffset + 12;
//		  	  }
//
//          }
//      }
//  }
//  I2C_Scan(&hi2c1);

//  void ssd1306_SetCursor(uint8_t x, uint8_t y);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//  PinConfig BTN_green = {0};
//  PinConfig LED_green1 = {0};
//  PinConfig LED_green2 = {0};
//  PinConfig LED_green3 = {0};
//  PinConfig LED_greenInternal = {0};
//
//  RAL_pinRegister(&BTN_green,
//				  GPIOB,
//				  4,
//				  INPUT,
//				  PUSH_PULL,
//				  LOW,
//				  PULL_DOWN,
//				  PIN_LOW);
//  RAL_pinRegister(&LED_green1,
//				  GPIOA,
//				  0,
//				  OUTPUT,
//				  PUSH_PULL,
//				  LOW,
//				  NO_PUPD,
//				  PIN_LOW);
//  RAL_pinRegister(&LED_green2,
//				  GPIOA,
//				  1,
//				  OUTPUT,
//				  PUSH_PULL,
//				  LOW,
//				  NO_PUPD,
//				  PIN_LOW);
//  RAL_pinRegister(&LED_green3,
//				  GPIOA,
//				  3,
//				  OUTPUT,
//				  PUSH_PULL,
//				  LOW,
//				  NO_PUPD,
//				  PIN_LOW);
//  RAL_pinRegister(&LED_greenInternal,
//				  GPIOB,
//				  3,
//				  OUTPUT,
//				  PUSH_PULL,
//				  LOW,
//				  NO_PUPD,
//				  PIN_LOW);

  while (1)
  {

	BME280_Measure();
//	if(Temperature>10) {
//		Temperature *= 100;
//		Pressure *=100;
//		Humidity *=100;
//		sprintf(tMessage, "T: %u.%02u C", ((unsigned int)Temperature /100),((unsigned int)Temperature %100));
//		sprintf(hMessage, "P: %u.%02u Pa", ((unsigned int)Pressure /100),((unsigned int)Pressure % 100));
//		sprintf(pMessage, "T: %u.%02u %%", ((unsigned int)Humidity /100),((unsigned int)Humidity %100));
////		sprintf((char *)buff, "%u.%02u C - %u.%02u Pa - %u.%02u %% \r\n",((unsigned int)Temperature /100),((unsigned int)Temperature %100),((unsigned int)Pressure /100),((unsigned int)Pressure % 100),((unsigned int)Humidity /100),((unsigned int)Humidity %100));
//	}
//	else {
//		sprintf(tMessage, "T: error");
//		sprintf(hMessage, "P: error");
//		sprintf(pMessage, "T: error");
//	}
	const double PA_TO_MMHG = 0.00750062;

	int tIntPart = (int)Temperature;
	int tDecimalPart = (int)((Temperature - tIntPart) * 100);
	int hIntPart = (int)Humidity;
	int hDecimalPart = (int)((Humidity - hIntPart) * 100);
//	int pIntPartPa = (int)Pressure;
//	int pDecimalPartPa = (int)((Pressure - pIntPartPa) * 100);
//	int pIntPartKpa = (int)(Pressure / 100);
//	int pDecimalPartKpa = (int)((Pressure / 100 - pIntPartKpa) * 100);

//	const double standardPressurePa = 101325.0;
//	const double mmHgConversionFactor = 760.0;

	double PressureMmHg = Pressure * PA_TO_MMHG;

	int pIntPartMmHg = (int)PressureMmHg;
	int pDecimalPartMmHg = (int)((PressureMmHg - pIntPartMmHg) * 100);

	const double T0 = 288.15;
	const double L = 0.0065;
	const double P0 = 101325.0;
	const double R = 287.05;
	const double g = 9.81;
	const double M = 0.0289644;

//	double Altitude = (T0 / L) * (1 - pow((Pressure / P0), (R * L) / g));
	double Pressure286 = P0 * pow(1 - (L * 286) / T0, (g * M) / (R * L)) * PA_TO_MMHG;

	double deltaPressure = ( PressureMmHg / Pressure286 ) * 100;



//	int aIntPart = (int)Altitude;
//	int aDecimalPart = (int)((Altitude - aIntPart) * 100);

	int dIntPart = (int)deltaPressure;
	int dDecimalPart = (int)((deltaPressure - dIntPart) * 100);

	sprintf(tMessage, "T  %d.%02d *C", tIntPart, tDecimalPart);
	sprintf(hMessage, "H  %d.%02d %%", hIntPart, hDecimalPart);
//	sprintf(pMessagePa, "P %d.%02dkPa", pIntPartKpa, pDecimalPartKpa);
	sprintf(pMessageHg, "P %d.%02d mmHg", pIntPartMmHg, pDecimalPartMmHg);
//	sprintf(aMessage, "A %d.%02dm", aIntPart, aDecimalPart);
	sprintf(dMessage, "P  %d.%02d %%", dIntPart, dDecimalPart);

//Sending out data
//	  	  HAL_UART_Transmit(&huart2,buff, strlen((char *)buff),HAL_MAX_DELAY);

	ssd1306_SetCursor(5, 3);
	result = ssd1306_WriteString(tMessage, Font_7x10, White);
	ssd1306_SetCursor(5, 15);
	result = ssd1306_WriteString(hMessage, Font_7x10, White);
	ssd1306_SetCursor(5, 27);
//	result = ssd1306_WriteString(pMessagePa, Font_7x10, White);
	result = ssd1306_WriteString(pMessageHg, Font_7x10, White);
	ssd1306_SetCursor(5, 39);
	result = ssd1306_WriteString(dMessage, Font_7x10, White);
//	ssd1306_SetCursor(5, 51);
//	result = ssd1306_WriteString(aMessage, Font_7x10, White);
	ssd1306_UpdateScreen();
//
//
//	HAL_Delay(750);

	HAL_Delay(500);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
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
