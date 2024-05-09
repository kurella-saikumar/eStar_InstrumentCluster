/** \addtogroup  STACK_USAGE_MONITORING
 *  @{
 * @file Stack_Usage.c
 *
 * @brief Stack_Usage Source File
 *
 * File Short Name: Stack_Usage
 *
 * Author: ANIL
 *
 * Create Date: 07-11-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
/*"Stack_Usage.h" file gets included via FreeRTOS.h*/
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
StackMonitorInfo_t prvTCB_Info[MAX_TASK_MONITOR];
uint8_t ucregistered_task_index;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief Monitors the stack usage of registered tasks and notifies if the stack usage exceeds the limit.
 *
 * This function goes through the list of registered tasks, checks their stack usage, and notifies if
 * the stack usage exceeds the specified limit for each task.
 *
 * @param[in] void
 * @return None
 *
 ***************************************************************************************************/
void vStackMonitorDemonTask_Handler(void)
{/** @startuml */ /** start */

    UBaseType_t uxHighWaterMark;
	/**: Variable to store the minimum amount of unused stack space in the task; */

	for(uint8_t ucTaskMonitoringIndex = 0; ucTaskMonitoringIndex < ucregistered_task_index; ucTaskMonitoringIndex++)
	{/**: Iterate through the registered tasks ;*/

		if(prvTCB_Info[ucTaskMonitoringIndex].handle != NULL)
		{/** if (task handle is valid) */

			uxHighWaterMark = uxTaskGetStackHighWaterMark(prvTCB_Info[ucTaskMonitoringIndex].handle);
			/**: Get the minimum amount of unused stack space since the task started running; */
			if(uxHighWaterMark < prvTCB_Info[ucTaskMonitoringIndex].ulStackMinFreeSize)
			{/** if (uxHighWaterMark stack space is below the specified limit) then (yes) */

				/**: Send a notification about exceeded stack usage limit; */
				vApplicationStackUsageLimit(prvTCB_Info[ucTaskMonitoringIndex].handle, prvTCB_Info[ucTaskMonitoringIndex].pcTaskName);

			}/** endif */
		}/** endif */
	}
}/** end*/ /** @enduml */

__WEAK void vApplicationStackUsageLimit(TaskHandle2_t xTask, const char *pcTaskName)
{
	/**:Application defined functionality;*/
	(void)xTask;
	(void)pcTaskName;
}

__WEAK void vMaxTaskRegisteredCallback(uint8_t registered_task_index)
{
	/**:Application defined functionality;*/
	(void)registered_task_index;
}
/**************************************************************************************************
 * End Of File
***************************************************************************************************/


