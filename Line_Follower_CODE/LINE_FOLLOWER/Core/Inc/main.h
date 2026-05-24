/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Start_Pin GPIO_PIN_14
#define Start_GPIO_Port GPIOC
#define nSleep_Pin GPIO_PIN_0
#define nSleep_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_1
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_8
#define AIN2_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_6
#define BIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_11
#define BIN1_GPIO_Port GPIOA
#define Sensor_1_Pin GPIO_PIN_4
#define Sensor_1_GPIO_Port GPIOB
#define Sensor_2_Pin GPIO_PIN_5
#define Sensor_2_GPIO_Port GPIOB
#define Sensor_3_Pin GPIO_PIN_6
#define Sensor_3_GPIO_Port GPIOB
#define Sensor_4_Pin GPIO_PIN_7
#define Sensor_4_GPIO_Port GPIOB
#define Sensor_5_Pin GPIO_PIN_8
#define Sensor_5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
