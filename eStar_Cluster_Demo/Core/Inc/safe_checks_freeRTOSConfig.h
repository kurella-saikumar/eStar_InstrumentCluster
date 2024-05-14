/** \addtogroup  MONITOR_PERIODICITY
 *  @{
 * @file safe_checks_freeRTOSConfig.h
 *
 * @brief SAFE_CHECKS_freeRTOSConfig file contains freeRTOS configuration settings required
 * for safer_checks plug-ins
 *
 * File Short Name: safe_checks_freeRTOSConfig
 *
 * Author: Rakesh Vangaveti
 *
 * Create Date: 28-11-2023
 *
  * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/
#ifndef SAFE_CHECKS_FREERTOSCONFIG_H
#define SAFE_CHECKS_FREERTOSCONFIG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "main.h"
#include "../../STM32CubeIDE/Application/User/Core/src/Service/System_Service/StackUsage_SafeChecks/Stack_Usage.h"
//#include "Task_OverLoad_DeadLock.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * freeRTOS Configurations required for SAFECHECKS Plugins
***************************************************************************************************/
/**
 * @brief Get the current run-time counter value.
 *
 * This macro retrieves the current value of the run-time counter, typically implemented using a hardware timer (e.g., TIM2).
 * It uses the __HAL_TIM_GET_COUNTER() function provided by the HAL library to obtain the counter value.
 *
 * @note Ensure that the hardware timer (e.g., TIM2) is initialized and running properly before using this macro.
 *
 * @return The current value of the run-time counter.
 */
#define portGET_RUN_TIME_COUNTER_VALUE() (__HAL_TIM_GET_COUNTER(&htim2))


#define configRECORD_STACK_HIGH_ADDRESS 1
#define traceTASK_CREATE( pxNewTCB ) SafeRTOS_ntveStack_TraceTASK_CREATE(pxNewTCB)
#define traceTASK_DELETE(pxNewTCB) SafeRTOS_TraceTASK_DELETE(pxNewTCB)
//
//#define traceMOVED_TASK_TO_READY_STATE(pxNewTCB) vSafeChecksMovedTaskToReadyState(pxNewTCB)
//#define traceTASK_SWITCHED_OUT vSafeChecksTaskSwitchedOut

#endif /* SAFE_CHECKS_FREERTOSCONFIG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/







