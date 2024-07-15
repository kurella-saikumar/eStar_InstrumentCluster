/** \addtogroup  MONITOR_PERIODICITY
 *  @{
 * @file SAFE_CHECKS_Config.h
 *
 * @brief User Configuration file to adjust the parameters of SafeChecks plug-ins
 *
 * File Short Name: SAFE_CHECKS_Config
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
#ifndef SAFE_CHECKS_CONFIG_H
#define SAFE_CHECKS_CONFIG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "main.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * STACK MONITORING CONFIGURATION PARAMETERS
***************************************************************************************************/
/**
 * @brief Maximum number of tasks that can be monitored.
 */
#define MAX_TASK_MONITOR 12U

/**
 * @brief Maximum stack usage threshold percentage.
 *
 * When monitoring tasks, this threshold is used to trigger a warning if the stack usage exceeds this percentage.
 */
#define MAX_STACK_THRESHOLD_PCNT 80U

/**************************************************************************************************
 * EXECUTION METRICS COLLECTION CONFIGURATION PARAMETERS
***************************************************************************************************/
/***************************************************************************//**
 * @def COLLECT_ALL_EXECUTION_INFO
 * @brief Defines whether to collect additional execution information.
 *
 * This macro, when defined, enables the collection of additional execution
 * information including average, minimum, and maximum execution times.
 * Commenting it out or leaving it undefined will disable the collection of
 * these additional statistics.
 ******************************************************************************/
#define COLLECT_ALL_EXECUTION_INFO
/**
 * @def MAX_CYCLE_Avg_EXEC
 * @brief Maximum number of cycles for calculating average execution time.
 *
 * Defines the maximum number of cycles considered when calculating the average
 * execution time. Adjust this value based on memory constraints and desired
 * statistical significance for accurate averaging.
 */
#define MAX_CYCLE_Avg_EXEC 100U
/**
 * @brief Number of timer counts equivalent to 1 microsecond.
 *
 * This constant defines the conversion factor between timer counts and microseconds.
 * It represents the number of timer counts that correspond to a single microsecond.
 * Other conversion macros rely on this value for accurate conversion calculations.
 *
 * The prescaler calculation formula helps determine the division factor used in a system, often in microcontrollers or devices where a clock signal needs to be divided down to a specific frequency. To calculate the prescaler value, you'll need to know the input clock frequency, desired output frequency, and the range of prescaler values supported by your device.

 * Here's a general formula for calculating the prescaler value:

 * Prescaler value=(Input clock frequency/Desired output frequency)-1


 * This formula assumes that the prescaler value is an integer and the prescaler itself starts counting from 0.

 * Let's break it down further with an example:

 * Suppose you have an input clock frequency of 8 MHz (8,000,000 Hz) and you want to generate an output frequency of 1 kHz (1,000 Hz) using a prescaler in a microcontroller.

 * Prescaler value=(8,000,000/1,000)-1 = 7999

 * In this case, if the prescaler values supported by your device include an exact integer division to achieve the desired output frequency, a prescaler value of 7999 would be used.
 */
#define RUN_TIME_COUNTS_FOR_1_USEC 1U




#endif /* SAFE_CHECKS_CONFIG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/







