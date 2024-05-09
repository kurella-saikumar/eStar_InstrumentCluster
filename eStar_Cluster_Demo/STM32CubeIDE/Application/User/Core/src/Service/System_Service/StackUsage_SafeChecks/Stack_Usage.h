/** \addtogroup  STACK_USAGE_MONITORING
 *  @{
 * @file Stack_Usage.h
 *
 * @brief STACK_USAGE_H Header File
 *
 * File Short Name:
 *
 * Author: ANIL
 *
 * Create Date:
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/

#ifndef STACK_USAGE_H
#define STACK_USAGE_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdint.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
//#include "safe_checks_Config.h"
//#include "D:\Govind_WorkSpace\Github_Workspace\eSTAR_InstrumentCluster\eStar_Cluster_Demo\STM32CubeIDE\Application\User\Core\PlatformConfig\safe_checks_Config.h"
#include "../../../../PlatformConfig/safe_checks_Config.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
struct tskTaskControlBlock;
typedef struct tskTaskControlBlock* TaskHandle2_t;


/**
 * @struct StackMonitorInfo_t
 * @brief Structure to hold information about a monitored task.
 */
  typedef struct
  {
	  TaskHandle2_t handle; /** Task handle of the monitored task. */
      uint32_t ulStackMinFreeSize; /** Minimum free stack size of the monitored task. */
      char* pcTaskName;   /** Task name as a string. */
  } StackMonitorInfo_t;


 /**************************************************************************************************
   * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/

 /**
 * @brief Trace macro for task register.
 *
 * This macro records information about a newly created task for monitoring purposes.
 *
 * @param pxNewTCB Pointer to the task control block of the newly created task.
 */

#define SafeRTOS_ntveStack_TraceTASK_CREATE(pxNewTCB) \
      	if (ucregistered_task_index < MAX_TASK_MONITOR)\
  		{\
			prvTCB_Info[ucregistered_task_index].ulStackMinFreeSize = (((((StackType_t)(pxNewTCB->pxEndOfStack) - (StackType_t)(pxNewTCB->pxStack))+1U) * (100U - MAX_STACK_THRESHOLD_PCNT)) / 100U);/*lint !e9078 MISRA exception.  Avoiding casts between pointers and integers is not practical.  Need to calculate the size of stack. */\
			prvTCB_Info[ucregistered_task_index].handle = pxNewTCB;\
			prvTCB_Info[ucregistered_task_index].pcTaskName =  pxNewTCB->pcTaskName;\
			ucregistered_task_index++;\
		}else\
		{\
			vMaxTaskRegisteredCallback(ucregistered_task_index);\
		}

#define SafeRTOS_ptveStack_TraceTASK_CREATE(pxNewTCB) \
    	if (ucregistered_task_index < MAX_TASK_MONITOR) \
		{\
			prvTCB_Info[ucregistered_task_index].ulStackMinFreeSize = (((pxNewTCB->pxStack - pxNewTCB->pxEndOfStack) * (100 - MAX_STACK_THRESHOLD_PCNT)) / 100);/*lint !e9078 MISRA exception.  Avoiding casts between pointers and integers is not practical.  Need to calculate the size of stack. */\
            prvTCB_Info[ucregistered_task_index].handle = pxNewTCB; \
            prvTCB_Info[ucregistered_task_index].pcTaskName =  pxNewTCB->pcTaskName;\
            ucregistered_task_index++; \
        }else\
		{\
        	vMaxTaskRegisteredCallback(ucregistered_task_index);\
		}

/**
 * @brief Trace macro for registered task deletion.
 *
 * This macro removes information about a deleted task from the monitoring data.
 *
 * @param pxNewTCB Pointer to the task control block of the deleted task.
 */
#define SafeRTOS_TraceTASK_DELETE(pxNewTCB) \
	for(uint8_t uctask_index = 0; uctask_index < ucregistered_task_index; uctask_index++) \
	{ \
		if(prvTCB_Info[uctask_index].handle == pxNewTCB) \
		{ \
			for (uint8_t i = uctask_index; i < ucregistered_task_index; i++)  \
  	  	  	  { \
			     prvTCB_Info[i] = prvTCB_Info[i + 1U]; \
			  } \
			prvTCB_Info[ucregistered_task_index].handle = NULL; \
			ucregistered_task_index--; \
		} \
	}

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
  extern StackMonitorInfo_t prvTCB_Info[MAX_TASK_MONITOR];
  extern uint8_t ucregistered_task_index;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
  /**
  * @brief Stack usage Implementation Guide
  *
  * This guide explains the steps to implement stack usage for tasks.
  *
  * USAGE:
  *
  * *****************************STEP 1:**********************************
  * Invoke vStackMonitorDemonTask_Handler() function in a task to check whether the stack usage is exceeded or not
  *
  * Example:
  *	void vTask_StackMonitor_Demo(void *argument)
  *	{
  *		for(;;)
  *		{
  *			vStackMonitorDemonTask_Handler();
  *			vTaskDelay(1000);
  *		}
  *	}
  *
  * *****************************STEP 2:**********************************
  * Define vApplicationStackUsageLimit function with TaskHandle2_t and Task name as parameters.
  * This function handles actions when stack usage exceeds the user defined threshold.
  *
  * Example:
  * void vApplicationStackUsageLimit(TaskHandle2_t xTask, char *pcTaskName)
  * {
  * 	 // Stack usage is exceeded the specified limit,do the actions that needs to be performed
  * }
  **/



  /**
   * @brief Monitors the stack usage of registered tasks and notifies if the stack usage exceeds the limit.
   *
   * This function goes through the list of registered tasks, checks their stack usage, and notifies if
   * the stack usage exceeds the specified limit for each task.
   *
   * @param void - No input parameters.
   * @return None
   */
  void vStackMonitorDemonTask_Handler(void);

  /**
   * @brief Application-defined hook for stack usage limit notification.
   *
   * This function is called when a task's stack usage exceeds the configured limit.
   *
   * @param xTask - Task handle.
   * @param pcTaskName - Task name as a string.
   */
  void vApplicationStackUsageLimit(TaskHandle2_t xTask, const char *pcTaskName);

  /**
   * @brief Callback function triggered when the maximum number of tasks is registered.
   *
   * This function is called when the number of registered tasks reaches the configured maximum limit.
   *
   * @param ucregistered_task_index - Number of tasks currently registered.
   */
  void vMaxTaskRegisteredCallback(uint8_t registered_task_index);


#endif /* STACK_USAGE_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

