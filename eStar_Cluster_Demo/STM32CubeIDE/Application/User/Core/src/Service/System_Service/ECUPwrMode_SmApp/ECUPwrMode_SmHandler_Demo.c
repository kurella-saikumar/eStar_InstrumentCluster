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
// #include "stdint.h"
 #include "stdio.h"
//#include "types.h"
#include "main.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "ECUPwrMode_SmHandler.h"
//#include "debug.h"
//#include "tcc_pmgpio.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

void vEcuPwrModeSleepToOffEntryAction(void);
void vEcuPwrModeActiveToOffEntryAction(void);
void vEcuPwrModeOffToSleepEntryAction(void);
void vEcuPwrModeActiveToSleepEntryAction(void);
void vEcuPwrModeSleepToActiveEntryAction(void);
void vEcuPwrModeOffAction(void);
void vEcuPwrModeSleepAction(void);
void vEcuPwrModeActiveAction(void);
void vEcuPwrModeOffActiveEntryAction(void);


/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief  ECUPwrModeSleep_To_Off_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_SLEEP to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeSleepToOffEntryAction(void)
{
  //  printf("ECUPwrModeSleep_To_Off_EntryAction\n");
}

/**
 * @brief  ECUPwrModeActive_To_Off_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeActiveToOffEntryAction(void)
{
   // printf("wrModeActive_To_Off_EntryAction\n");
    //PowerDown(Hw_ACC_DET);
	pm_ReqNewState(ECU_POWER_MODE_OFF);
#if(ECUPwrMode_TestMacro == 1)
	printf("ECUPwrModeAction_off\n");
#endif

}

/**
 * @brief  ECUPwrModeOff_To_Sleep_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_OFF to ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
extern RTC_HandleTypeDef hrtc;
extern LTDC_HandleTypeDef hltdc;
void vEcuPwrModeOffToSleepEntryAction(void)
{
//    printf("ECUPwrModeOff_To_Sleep_EntryAction\n");
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	/*## Configure the Wake up timer ###########################################*/
	  /*  RTC Wake-up Interrupt Generation:
		  Wake-up Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSI))
		  ==> WakeUpCounter = Wake-up Time / Wake-up Time Base

		  To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
			RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16
			Wake-up Time Base = 16 /(32KHz) = 0.0005 seconds
			==> WakeUpCounter = ~10s/0.0005s = 20000 = 0x4E20,20s -0x9C40  */
	  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc,0x9C40, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
		{
		  Error_Handler();
		}
	  /****** Suspend the Ticks before entering the STOP mode or else this can wake the device up **********/
	  HAL_SuspendTick();
	  HAL_PWR_EnableSleepOnExit();
	  HAL_LTDC_DeInit(&hltdc);
	  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	  // The code will continue here upon wake-up
	// Deactivate the Wake-up Timer
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	while(1)
	{

	}
}


/**
 * @brief  ECUPwrModeActive_To_Sleep_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeActiveToSleepEntryAction(void)
{
   // printf("ECUPwrModeActive_To_Sleep_EntryAction\n");
}


/**
 * @brief  ECUPwrModeSleep_To_Active_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_SLEEP to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeSleepToActiveEntryAction(void)
{
  //  printf("ECUPwrModeSleep_To_Active_EntryAction\n");
}


/**
 * @brief  ECUPwrModeOff_Action function is to perform some action when the state remain in ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
uint16_t l_PowerOff_Sleep_u16 = 0;
void vEcuPwrModeOffAction(void)
{
    //Enable Wakeup Settings
    // Enter into sleep mode
	/*No warnings, Display OFF - When Warning Indicators are OFF,Display Shall be in OFF mode, All features non functional
	Any Warnings, Display ON - When Warning Indicators are ON, Display Shall be in ON mode*/
	// if non of the Activity are active for particular period, enter into Sleep mode
	if(pm_GetSyncStatus() == ECU_POWER_MODE_OFF )
	{
		l_PowerOff_Sleep_u16++;
	}
	else
	{
		l_PowerOff_Sleep_u16 = 0;
	}
	if(l_PowerOff_Sleep_u16 == 6500)
	{
		l_PowerOff_Sleep_u16 = 0;
		//printf("ECUPwrModeOff_Action\n");
		pm_ReqNewState(ECU_POWER_MODE_SLEEP);
	}
}

/**
 * @brief  ECUPwrModeSleep_Action function is to perform some action when the state remain in ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeSleepAction(void)
{
   // printf("ECUPwrModeSleep_Action\n");
}


/**
 * @brief  ECUPwrModeActive_Action function is to perform some action when the state remain in ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vEcuPwrModeActiveAction(void)
{
   // printf("ECUPwrModeActive_Action\n");
//	 printf("ECUPwrModeOff_To_Sleep_EntryAction\n");
//		RTC_HandleTypeDef hrtc;
//		/*## Configure the Wake up timer ###########################################*/
//			  /*  RTC Wake-up Interrupt Generation:
//			      Wake-up Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSI))
//			      ==> WakeUpCounter = Wake-up Time / Wake-up Time Base
//
//			      To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
//			        RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16
//			        Wake-up Time Base = 16 /(32KHz) = 0.0005 seconds
//			        ==> WakeUpCounter = ~10s/0.0005s = 20000 = 0x4E20 */
//
//			  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x4E20, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
//
//			  /****** Suspend the Ticks before entering the STOP mode or else this can wake the device up **********/
//			  HAL_SuspendTick();
//
//			//  HAL_PWR_EnableSleepOnExit();
//			  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
			  // The code will continue here upon wake-up

//			  // Deactivate the Wake-up Timer
//			  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
//
//			  // Resume the system tick
//			  HAL_ResumeTick();

//		while(1)
//		{
//
//		}
}

/**
 * @brief  ECUPwrModeOff_Active_ENtryAction function is to perform some action when the state  change from ECU_POWER_MODE_OFF to Active
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void vEcuPwrModeOffActiveEntryAction()
{
    //printf("ECUPwrModeOff_Active_ENtryAction\n");
    //PowerDown(Hw_ACC_DET);
	pm_ReqNewState(ECU_POWER_MODE_ACTIVE);
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
