/** \addtogroup MONITOR_PERIODICITY
 *  @{
 * @file PeriodicityCheck.c
 *
 * @brief PeriodicityCheck Source File
 *
 * File Short Name: PeridoicityCheck
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
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "PeriodicityCheck.h"
#include "safe_checks_freeRTOSConfig.h"
#include "stdio.h"
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
 * @brief Checks the periodicity of a task based on given parameters.
 *
 * This function checks the periodicity of a task by comparing the time difference
 * between the current and previous switch times against specified minimum and maximum
 * periodicity values.
 *
 * @param[in,out] xPeriodicityCheckTaskInfo
 * 		Pointer to a structure containing task periodicity information.
 * 		This parameter is both an input and output as it gets modified within the function.
 * @param[in] vErrHook
 * 		Pointer to a function to handle errors when periodicity criteria aren't met.
 * 		This parameter is an input as it is used to call the error handling function.
 */
void vCheckPeriodicity(TaskPeriodicityCheck_t* xPeriodicityCheckTaskInfo,void (*vErrHook)(TaskPeriodicityCheck_t*))
{
	/** @startuml */ /** start */
	/**: Check if the ucFistLoopFlag is invalid;*/
	if (xPeriodicityCheckTaskInfo->ucFistLoopFlag == 0U)
	{
		/**: Validate the FirstLoopFlag,indicates first loop is done;*/
		xPeriodicityCheckTaskInfo->ucFistLoopFlag = 1U;
		/**:Record the FirstLoop's switched time;*/
		xPeriodicityCheckTaskInfo->ulCurrSwitchTime = portGET_RUN_TIME_COUNTER_VALUE();
	}
	else
	{
		/**: Record the previous switch time;*/
		xPeriodicityCheckTaskInfo->ulPrevSwitchTime = xPeriodicityCheckTaskInfo->ulCurrSwitchTime;

		/**:Record the current switch time;*/
		xPeriodicityCheckTaskInfo->ulCurrSwitchTime = portGET_RUN_TIME_COUNTER_VALUE();

		/**: Calculate the time difference between current and previous switch times;*/
		uint32_t ulPeriodicityDiff = xPeriodicityCheckTaskInfo->ulCurrSwitchTime - xPeriodicityCheckTaskInfo->ulPrevSwitchTime;
		//printf("ulPeriodicityDiff: %ld\n", (unsigned long)ulPeriodicityDiff);

		/**: Check if the periodicity difference lies within specified bounds;*/

		if ((ulPeriodicityDiff < xPeriodicityCheckTaskInfo->ulMinPeriodicity) || \
			 (ulPeriodicityDiff > xPeriodicityCheckTaskInfo->ulMaxPeriodicity ))  \
			{
				if(vErrHook !=NULL)
				{
					/**: Failed periodicity check: Call the error handling function;*/
					(*vErrHook) (xPeriodicityCheckTaskInfo);
				}
			}
			else
			{
				/**: Success condition, Updated xPeriodicityCheckTaskInfo and call success hook; */
			}
	}
    /** end*/ /** @enduml */
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
