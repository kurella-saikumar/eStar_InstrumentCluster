/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define Mode_switch_Pin GPIO_PIN_3
#define Mode_switch_GPIO_Port GPIOE
#define Switch_Fuel_Pin GPIO_PIN_13
#define Switch_Fuel_GPIO_Port GPIOC
#define LCD_BL_CTRL_Pin GPIO_PIN_15
#define LCD_BL_CTRL_GPIO_Port GPIOG
#define Reset_switch_Pin GPIO_PIN_5
#define Reset_switch_GPIO_Port GPIOG
#define EXTI_Pin GPIO_PIN_4
#define EXTI_GPIO_Port GPIOG
#define EXTI_EXTI_IRQn EXTI4_IRQn
#define RENDER_TIME_Pin GPIO_PIN_3
#define RENDER_TIME_GPIO_Port GPIOG
#define Ignition_Pin GPIO_PIN_8
#define Ignition_GPIO_Port GPIOF
#define Ignition_EXTI_IRQn EXTI9_5_IRQn
#define Tacho_Pin GPIO_PIN_15
#define Tacho_GPIO_Port GPIOD
#define MCU_ACTIVE_Pin GPIO_PIN_15
#define MCU_ACTIVE_GPIO_Port GPIOB
#define FRAME_RATE_Pin GPIO_PIN_14
#define FRAME_RATE_GPIO_Port GPIOB
#define LCD_DISP_Pin GPIO_PIN_10
#define LCD_DISP_GPIO_Port GPIOD
#define VSYNC_FREQ_Pin GPIO_PIN_0
#define VSYNC_FREQ_GPIO_Port GPIOA
#define FuelGuage_Pin GPIO_PIN_0
#define FuelGuage_GPIO_Port GPIOA
#define gpio_test_Pin GPIO_PIN_14
#define gpio_test_GPIO_Port GPIOF

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
