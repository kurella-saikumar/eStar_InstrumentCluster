/*
 * DisplayService.c
 *
 *  Created on: Apr 25, 2024
 *      Author: 91810
 */

#include "main.h"
#include "stm32h735g_discovery_errno.h"
#include "stm32h7xx_hal_ltdc.h"

extern LTDC_HandleTypeDef hltdc;
void vBacklightBrightness(void);
/* LCD Display control pin */
#define LCD_DISP_CTRL_PIN                     GPIO_PIN_10
#define LCD_DISP_CTRL_PULL                    GPIO_NOPULL
#define LCD_DISP_CTRL_GPIO_PORT               GPIOD

/* Back-light control pin */
#define LCD_BL_CTRL_PIN                       GPIO_PIN_15
#define LCD_BL_CTRL_GPIO_PORT                 GPIOG
#define LCD_INSTANCES_NBR      			      1U

/**
  * @brief  Switch On the display.
  * @param  Instance    LCD Instance
  * @retval BSP status
  */
int32_t BSP_LCD_DisplayOn(uint32_t Instance)
{
  int32_t ret;

  if(Instance >= LCD_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_LTDC_ENABLE(&hltdc);
	/* Assert LCD_DISP_CTRL_EN pin */
    HAL_GPIO_WritePin(LCD_DISP_CTRL_GPIO_PORT, LCD_DISP_CTRL_PIN, GPIO_PIN_SET);
	/* Assert LCD_BL_CTRL pin */
    HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_SET);

    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Switch Off the display.
  * @param  Instance    LCD Instance
  * @retval BSP status
  */
int32_t BSP_LCD_DisplayOff(uint32_t Instance)
{
  int32_t ret;

  if(Instance >= LCD_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_LTDC_DISABLE(&hltdc);
	/* Assert LCD_DISP_CTRL_EN pin */
    HAL_GPIO_WritePin(LCD_DISP_CTRL_GPIO_PORT, LCD_DISP_CTRL_PIN, GPIO_PIN_RESET);
	/* Assert LCD_BL_CTRL pin */
    HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_RESET);

    ret = BSP_ERROR_NONE;
  }

  return ret;
}
void vBacklightBrightness(void)
{
	BSP_LCD_DisplayOff(0);
	HAL_Delay(1000);
	BSP_LCD_DisplayOn(0);
	HAL_Delay(1000);

}
