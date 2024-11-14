/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler_Demo.c
 *
 * @brief Template Source File
 *
 * File Short Name:
 *
 * Author:k.saikumar
 *
 * Create Date: 08/07/2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "Sys_WakeUp_Reason.h"
#include "stm32h735g_discovery_ospi.h"
#include "stm32h7xx_hal_ospi.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
 * Purpose: Variable To Hold the request status of ecupowermode.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 bit
 *
 * Range:NoRequestPending,l_next_ecuPwrMode_SM
 *
 * Power On Init Value\Action: Initialized to the default input state
 *
 * Wakeup Value\Action: Initialized to the next state of ecupowermode
 *
 * Shutdown Value\Action: Don't Care
 *
 */
pmReqStatus_t pmReqStatus;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

PM_PWRDN_TYPE checkBootReason(void);
uint8_t Mcu_GetResetReason(void);

extern int32_t BSP_LCD_DisplayOn(uint32_t Instance);
extern int32_t BSP_LCD_DisplayOff(uint32_t Instance);

PM_PWRDN_TYPE checkBootReason(void)
{
    PM_PWRDN_TYPE ret = PM_PWRDN_RESET;

    // Check if RCC flag Window Watchdog 1 reset is set
    if ((READ_BIT(RCC->RSR, RCC_RSR_WWDG1RSTF) != 0))
    {
        ret = PM_PWRDN_WDT;
    }
    // Check if RCC flag Independent Watchdog 1 reset is set
    else if ((READ_BIT(RCC->RSR, RCC_RSR_IWDG1RSTF) != 0))
    {
        ret = PM_PWRDN_WDT;
    }
    // Check if Wakeup pin EXTI line interrupt detected
    else if (READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) != 0)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3); // Example: Toggle an LED to indicate wake-up
        ret = PM_PWR_WakeUp_RESET;
    }
    // Check if RCC flag BOR reset is set
    else if ((READ_BIT(RCC->RSR, RCC_RSR_BORRSTF) != 0))
    {
        ret = PM_BOR;
    }
    // Check if RCC flag Pin reset is set
    else if ((READ_BIT(RCC->RSR, RCC_RSR_PINRSTF) != 0))
    {
        ret = PM_PIN_RESET;
    }
    // Check if RCC flag POR/PDR reset is set
    else if ((READ_BIT(RCC->RSR, RCC_RSR_PORRSTF) != 0))
    {
        ret = PM_POR_PDR;
    }

    return ret;
}

uint8_t Mcu_GetResetReason(void)
{
    uint8_t boot_reason = 0;

    // Check boot reason
    boot_reason = checkBootReason();

    // Print boot reason
    switch (boot_reason)
    {
        case PM_PWRDN_RESET:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is reset\n");
#endif
            break;
        case PM_PWRDN_WDT:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is watchdog\n");
#endif
            break;
        case PM_BOR:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is brown-out reset\n");
#endif
            break;
        case PM_POR_PDR:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is power-on reset or power-down reset\n");
#endif
            break;
        case PM_PIN_RESET:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is pin reset\n");
#endif
            break;
        case PM_PWR_WakeUp_RESET:
#if(SysWakeup_TestMacro == 1)
            printf("Boot reason is power wake-up reset\n");
#endif
            break;
        default:
#if(SysWakeup_TestMacro == 1)
            printf("Unknown boot reason\n");
#endif
            break;
    }
    /* Reset all RSR flags */
    SET_BIT(RCC->RSR, RCC_RSR_RMVF);
    return boot_reason;
}

void vSys_EnterSTOP_Mode(void)
{
	/* Disable Wakeup Counter */
    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    /* Enable Wakeup Counter and set to  20s -0x9C40 periodic wakeup is system sleep*/
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x9C40, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
	BSP_LCD_DisplayOff(0);
	/*Invoke HAL API to enter stop mode with LOW_PWR_REG ON & Wait for Interrupt */
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
}
void vSys_WakeUpFromSTOP(void)
{
	SystemClock_Config();
	PeriphCommonClock_Config();
	BSP_LCD_DisplayOn(0);
}
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
