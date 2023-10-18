/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_R_Pin GPIO_PIN_0
#define BTN_R_GPIO_Port GPIOF
#define BTN_B_Pin GPIO_PIN_1
#define BTN_B_GPIO_Port GPIOF
#define LED_R_1_Pin GPIO_PIN_0
#define LED_R_1_GPIO_Port GPIOB
#define LED_R_2_Pin GPIO_PIN_1
#define LED_R_2_GPIO_Port GPIOB
#define LED_R_3_Pin GPIO_PIN_8
#define LED_R_3_GPIO_Port GPIOA
#define LED_R_4_Pin GPIO_PIN_9
#define LED_R_4_GPIO_Port GPIOA
#define LED_R_5_Pin GPIO_PIN_10
#define LED_R_5_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_3
#define LED_G_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */