/** \addtogroup MULTIPLE_TASKS_EXECUTION_TIME
 *  @{
 * @file Task_ExeTime.h
 *
 * @brief This file calculates Execution time for multiple tasks.
 *
 *
 * File Short Name: ExeTime
 *
 * @author: Vasavi Bashetti
 *
 * @date:28-11-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
 ********************************************************************************************** @}*/
#ifndef TASK_EXETIME_H
#define	TASK_EXETIME_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdint.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "safe_checks_freeRTOSConfig.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define RUN_TIME_COUNTS_FOR_1_USEC 2U
/***************************************************************************//**
 * @brief Macro to convert microseconds to timer counts.
 * @param x Value in microseconds to convert.
 * @return The converted value in timer counts.
 *
 * This macro multiplies the given value in microseconds (x) with RUN_TIME_COUNTS_FOR_1_USEC
 * to obtain the equivalent timer counts.
 ******************************************************************************/

#define CONVERT_USEC_TO_TIMER_COUNTS(x)  ((x) * RUN_TIME_COUNTS_FOR_1_USEC)
/***************************************************************************//**
 * @brief Macro to convert timer counts to microseconds.
 * @param x Value in timer counts to convert.
 * @return The converted value in microseconds.
 *
 * This macro divides the given value in timer counts (x) by RUN_TIME_COUNTS_FOR_1_USEC
 * to obtain the equivalent microseconds.
  ******************************************************************************/

#define CONVERT_TIMER_COUNTS_TO_US(x)	((x) / RUN_TIME_COUNTS_FOR_1_USEC)


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
typedef struct TaskRunTimeStat {
	#ifdef COLLECT_ALL_EXECUTION_INFO
    uint32_t ulAvg; /** Average execution time in input timer counts of the measurement*/
    uint32_t ulminTime; /**Minimum execution time in input timer counts*/
    uint32_t ulmaxTime; /**Maximum execution time in input timer counts*/
	#endif
    uint32_t ulexecutionTime;/**Collects the last execution time in input timer counts of the measurement*/
    uint32_t ulstart_Count; /** Start count for the execution measurement*/
    uint32_t ulEnd_Count; /** End count for the execution measurement*/
	#ifdef COLLECT_ALL_EXECUTION_INFO
    uint16_t ustask_Counter;/**Counter indicating the number of times a specific task has been executed. */
	#endif
    uint8_t  ucReset_flag; /**Flag indicating a reset state*/

}TaskRunTimeStat_t;

/***************************************************************************//**
 * @brief Callback function type for executing a metric maximum limit.
 *        This typedef defines a function pointer type that points to a function
 *        responsible for handling maximum metric limit execution.
 * @param p_measurement_var_ptr Pointer to TaskRunTimeStat_t structure.
 *        This structure holds runtime statistics.
 * @param [out] none
 * @return none
  ******************************************************************************/

typedef void (* execMetricMaxLimit_cb)(TaskRunTimeStat_t *p_measurement_var_ptr);
/**
 *
 * @brief Section's Execution metrics Implementation Guide
 *
 * This guide explains the steps to implement execution time for tasks.
 *
 * USAGE:
 *
 * *****************************STEP 1:**********************************
 * Define a static structure variable TaskRunTimeStat_t to hold the Task Runtime statistics
 *
 * Example:
 * static TaskRunTimeStat_t p_measurement_var_ptr;
 * This variable holds the Runtime statistics for vTask_demo1.
 * *****************************STEP 2:**********************************
 * Create execTimeFault_cb function.
 * This function handles actions when execution time fails for vTask_demo1.
 *
 * Example:
 * void execTimeFault_cb(TaskRunTimeStat_t *p_measurement_var_ptr)
 * {
 * 	//indicates the failure(execution is greater than user allowed limit), Implement the execution time failure action here
 * }
 *
 * *****************************STEP 3:**********************************
 * Invoke vBeginExecMeas,vEndExecMeas functions in the section of code to be monitored (e.g., vTask_demo1).
 *
 * Example Usage:
 *
 * void vTask_demo1(void) {
 *     while(1) {
 *		//: Begin the execution measurement ;
 *		vBeginExecMeas(&p_measurement_var_ptr);
 *
 *      // Toggle the pin for task functionality.
 *      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
 *
 *		// :End the execution measurement,Invoke a callback if it is out of boundaries ;
 *		vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(3000), execTimeFault_cb);
 *
 *		// Maintain task periodicity.
 *       osDelay(1000);
 *     }
 * }
 *
 **/

/***************************************************************************//**
 * @brief  vReset_executionTimeStats resets the members of a struct TaskRunTimeStat_t to their initial values.
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure
 * @param [out] none
 * @return none
 ******************************************************************************/
 void vReset_executionTimeStats(TaskRunTimeStat_t *p_measurement_var_ptr);

/***************************************************************************//**
 * @brief  vBeginExecMeas begins the execution time measurement by reading the timer count
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure
 * @param [out] none
 * @return none
 ******************************************************************************/
 void vBeginExecMeas(TaskRunTimeStat_t *p_measurement_var_ptr);

/***************************************************************************//**
 * @brief  vEndExecMeas ends the execution time measurement by reading the timer count and calculates the average
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure.
 * @param [in] ulmaxAllowedTime Maximum allowed execution time threshold.
 * @param [in] execTimeErrorHook_cb Callback function for handling execution time errors.
 * @param [out] none
 * @return none
 ******************************************************************************/
void vEndExecMeas(TaskRunTimeStat_t *p_measurement_var_ptr, uint32_t ulmaxAllowedTime, execMetricMaxLimit_cb execTimeErrorHook_cb);

#endif	/* TASK_EXETIME_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

