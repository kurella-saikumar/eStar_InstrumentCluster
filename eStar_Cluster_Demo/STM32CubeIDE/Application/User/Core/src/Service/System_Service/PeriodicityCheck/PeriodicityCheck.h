/** \addtogroup  MONITOR_PERIODICITY
 *  @{
 * @file PeriodicityCheck.h
 *
 * @brief PeridoicityCheck file is to monitor the periodicity of each task
 *
 * File Short Name: PeriodicityCheck
 *
 * Author: Rakesh Vangaveti
 *
 * Create Date: 21-11-2023
 *
  * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/

#ifndef INC_PERIODICITYCHECK_H_
#define INC_PERIODICITYCHECK_H_
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stdint.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**
 * @brief Structure to store task Periodicity check information
 *
 * This structure defines the information stored
 * FirstLoopFlag, minimum periodicity, maximum periodicity,
 * current switch time, and previous switch time.
 */

typedef struct
{
	uint8_t  ucFistLoopFlag; 	 /**< To skip the very first loop of the task(Record time of first loop) */
	uint32_t ulMinPeriodicity;   /**< Minimum periodicity(micro seconds) for the task */
    uint32_t ulMaxPeriodicity;   /**< Maximum periodicity(micro seconds) for the task */
    uint32_t ulCurrSwitchTime;   /**< Current switch time for the task */
    uint32_t ulPrevSwitchTime;   /**< Previous switch time for the task */

} TaskPeriodicityCheck_t;
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
/**
 * @brief Task Periodicity Check Implementation Guide
 *
 * This guide explains the steps to implement periodicity checks for tasks.
 *
 * USAGE:
 *
 * *****************************STEP 1:**********************************
 * Define a structure TaskPeriodicityCheck_t to hold the minimum and maximum periodicity of tasks.
 * Initialize xPeriodicityCheckTaskInfo_T01 as follows:
 * - ucFistLoopFlag: To skip the very first loop of the vTask_demo1 Record time of first loop
 * - uxCurrSwitchTime: Current switch time for vTask_demo1
 * - ulPrevSwitchTime: Previous switch time for vTask_demo1
 * - ulMinPeriodicity: Minimum periodicity(micro seconds) for vTask_demo1
 * - ulMaxPeriodicity: Maximum periodicity(micro seconds) for vTask_demo1
 *
 *
 * Example:
 * This structure holds the periodicity check information for vTask_demo1.
 * TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T01 =
 * {
 *   .ucFistLoopFlag = 0 		   *< To skip the very first loop of the vTask_demo1(Record time of first loop)
 *   .uxCurrSwitchTime = 0,        *< Current switch time for vTask_demo1
 *   .ulPrevSwitchTime = 0,        *< Previous switch time for vTask_demo1
 *   .ulMinPeriodicity = 450000,   *< Minimum periodicity (micro seconds)for vTask_demo1
 *   .ulMaxPeriodicity = 550000,   *< Maximum periodicity (micro seconds)for vTask_demo1
 * };
 *
 * *****************************STEP 2:**********************************
 * Create vTask_demo1PeriodicityCheckErrorHook function.
 * This function handles actions when periodicity check fails for vTask_demo1.
 * It takes xPeriodicityCheckTaskInfo as a parameter to manage periodicity failure actions.
 *
 * Example:
 * void vTask_demo1PeriodicityCheckErrorHook (TaskPeriodicityCheck_t* xPeriodicityCheckTaskInfo)
 * {
 * 		//indicates the periodicity check failure, Implement the periodicity failure action here
 * }
 *
 * *****************************STEP 3:**********************************
 * Invoke vCheckPeriodicity function in the task to be monitored (e.g., vTask_demo1).
 * Use it to check the periodicity of the task by passing:
 * - xPeriodicityCheckTaskInfo: Pointer to task periodicity information structure.
 * - vTask_demo1PeriodicityCheckErrorHook: Function pointer for error handling.
 *
 * Example Usage:
 *
 * void vTask_demo1(void) {
 *     while(1) {
 *         // Ensure task periodicity by calling vCheckPeriodicity.
 *         // Follow STEP 1, STEP 2, and then STEP 3.
 *         vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T01, vTask_demo1PeriodicityCheckErrorHook);
 *
 *         // Toggle the pin for task functionality.
 *         HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
 *
 *         // Maintain task periodicity.
 *         osDelay(1000);
 *     }
 * }
 */


extern void vCheckPeriodicity(TaskPeriodicityCheck_t* xPeriodicityCheckTaskInfo, void (*vErrHook)(TaskPeriodicityCheck_t*));

#endif /* INC_PERIODICITYCHECK_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
