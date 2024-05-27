/** \addtogroup  STACK_USAGE_MONITORING
 *  @{
 * @file Task_OverLoad_DeadLock.c
 *
 * @brief Task_OverLoad_DeadLock Source File
 *
 * File Short Name: Task_OverLoad_DeadLock
 *
 * Author: Vasavi Bashetti
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
#include "Task_OverLoad_DeadLock.h"
#include "FreeRTOS.h"
#include "task.h"
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
/** Index for the number of registered tasks for monitoring. */
static uint8_t prvReguctaskIndex = 0;
/** Array to store information for monitoring tasks. */
static TaskMonitorInfo prvContextCount_Info[MAX_TASK_MONITOR];
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/***************************************************************************************************
 * @brief Registers a task for overload and deadlock checks.
 *
 * This function registers a task for monitoring context switches, overload conditions, and deadlock situations.
 *
 * @param xTaskHandle - Task handle of the registered task.
 * @param ulSwitchLimitCounter - Maximum allowed context switch limit for the task.
 * @param ulTimeoutLimit -  Timeout limit(in Scheduler Ticks)for detecting a potential deadlock.
 * @param switchErrorHook - Function pointer to the error hook to be called in case of an issue.
 *
 * @return None
 *
 * @note The registered task information is stored in an array for monitoring.
 * @note Ensure that 'prvContextCount_Info' and 'ucRegTaskIndex' are declared and available in the scope where this function is used.
 * @note The error hook is invoked when the maximum number of tasks for context switch monitoring is reached.
 ***************************************************************************************************/
void vRegisterTaskForOverloadDeadLockCheck(TaskHandle3_t xTask,
                                           uint32_t ulSwitchLimitCounter,
                                           uint32_t ulTimeoutLimit,
                                           ContextSwitchErrorHook switchErrorHook)
{
	/**@startuml*//**start*/
	/**if(prvReguctaskIndex is lesser than max task switch monitor) then (yes)*/
    if (prvReguctaskIndex < MAX_TASK_MONITOR)
    {
    	/**:Record the User Provided Task Deadlock & OverLoad information into registered index*/
        prvContextCount_Info[prvReguctaskIndex].handle = xTask;
        prvContextCount_Info[prvReguctaskIndex].ulMaxContextSwitchLimit = ulSwitchLimitCounter;
        prvContextCount_Info[prvReguctaskIndex].ulContextSwitchCounter = 0;
        prvContextCount_Info[prvReguctaskIndex].ulDeadLockTimeoutLimit = ulTimeoutLimit;
        prvContextCount_Info[prvReguctaskIndex].ucTaskActiveStatusFlag = 0;
        prvContextCount_Info[prvReguctaskIndex].ulDeadLockTimeStartValue = xTaskGetTickCount();
        prvContextCount_Info[prvReguctaskIndex].errorHook = switchErrorHook;
        /**:Increment registered index for next task registration;*/
        prvReguctaskIndex++;
    }
    /**else*/
    else
    {
        /**:Invoke the error hook if the maximum number of tasks is reached ;*/
    	vMaxTaskRegisteredCallback(prvReguctaskIndex);
    }
    /**endif*/
    /**end*//**@enduml*/
}

/*****************************************************************************
 * @brief This function performs safety checks when a task is switched out.
 * It updates context-related information and checks for context switch counts.
 * If the context switch count exceeds a specified limit, it triggers an error hook.
 * @param [in] none
 * @param [out] none
 * @return none
 ******************************************************************************/
void vSafeChecksTaskSwitchedOut(void)
{
	/**@startuml*//**start*/
	/**:Get the Current Task Handle info;*/
    TaskHandle3_t taskHandle = xTaskGetCurrentTaskHandle();

    for (uint8_t ucloop_Counter = 0; ucloop_Counter < prvReguctaskIndex; ucloop_Counter++)
    {
    	/**if(Current task handle matched with registered task handle index) then (yes)*/
        if (prvContextCount_Info[ucloop_Counter].handle == taskHandle)
        {
        	/**:Increment the Context Switch Counter;*/
            prvContextCount_Info[ucloop_Counter].ulContextSwitchCounter++;
            /**if(Switch Counter is greater than Switch Limit) then (yes)*/
            if((prvContextCount_Info[ucloop_Counter].ulContextSwitchCounter > prvContextCount_Info[ucloop_Counter].ulMaxContextSwitchLimit)&&(prvContextCount_Info[ucloop_Counter].errorHook !=NULL))
            {
            	/**:Invoke the Error Hook with OVERLOAD Reason;*/
                prvContextCount_Info[ucloop_Counter].errorHook(OVER_LOAD);
            }
            /**endif*/
            /**:Break the loop;*/
            ucloop_Counter = prvReguctaskIndex; /*Break the loop without using a break statement*/
        }
        /**endif*/
    }
    /**end*//**@enduml*/
}

/*****************************************************************************
 * @brief Updates context switch and task status when a task is moved to the ready state.
 *
 * This function is called when a task is moved to the ready state, and it updates the context switch counter,
 * task status flag, and deadlock start time for the corresponding task.
 *
 * @param pxTCB - Task handle of the task moved to the ready state.
 *
 * @return None
 *
 * @note The function iterates through the registered tasks to find the matching task handle.
 * @note If a match is found, it resets the context switch counter, sets the task active status flag,
 *       and updates the deadlock start time.
 ******************************************************************************/
void vSafeChecksMovedTaskToReadyState(TaskHandle3_t pxTCB)
{
	/**@startuml*//**start*/
    for (uint8_t ucloop_Counter = 0; ucloop_Counter < prvReguctaskIndex; ucloop_Counter++)
    {
    	/**if(Current task handle matched with registered task handle index) then (yes)*/
        if (prvContextCount_Info[ucloop_Counter].handle == pxTCB)
        {
        	/**: Reset the context switch counter;  */
       		prvContextCount_Info[ucloop_Counter].ulContextSwitchCounter = 0;

        	/**: Set the task active status flag; */            
       		prvContextCount_Info[ucloop_Counter].ucTaskActiveStatusFlag = 1;

			/**: Update the deadlock start time; */
			prvContextCount_Info[ucloop_Counter].ulDeadLockTimeStartValue = xTaskGetTickCount();

			/**:Break the loop without using a break statement;*/
			ucloop_Counter = prvReguctaskIndex; /*Break the loop without using a break statement*/
        }
        /**endif*/
        else
        {
        	/**nothing to do*/
        }
    }
    /**end*//**@enduml*/
}

/*****************************************************************************
 * @brief Checks for task deadlocks based on task activity status and elapsed time.
 * @param [in] none
 * @param [out] none
 * @return none
 ******************************************************************************/
void vCheckTaskDeadlock(void)
{
	/**@startuml*//**start*/
    for (uint8_t uctaskIndex = 0; uctaskIndex < prvReguctaskIndex; uctaskIndex++)
    {
    	/**:if(ucTaskActiveStatusFlag is not set) then (yes);*/
        if (prvContextCount_Info[uctaskIndex].ucTaskActiveStatusFlag == 0U)
        {
			/**:Compute the Elapsed time of Deadlock start and current time;*/
            uint32_t ulElapsedTime = xTaskGetTickCount() - prvContextCount_Info[uctaskIndex].ulDeadLockTimeStartValue;
			/**:if(elapsed time is greater user provided deadlock timeout limit) then (yes);*/
            if ((ulElapsedTime > prvContextCount_Info[uctaskIndex].ulDeadLockTimeoutLimit)&&(prvContextCount_Info[uctaskIndex].errorHook !=NULL))
            {
				/**:Task deadlock detected, Invoke Error Hook with DEAD_LOCK Reason;*/
                prvContextCount_Info[uctaskIndex].errorHook(DEAD_LOCK);
            }
            /**else*/
            else
            {
            	/**:nothing to do;*/
            }
            /**endif*/
        }
        /**else*/
        else
        {
			/**:Reset the context switch count and last check time;*/
            prvContextCount_Info[uctaskIndex].ucTaskActiveStatusFlag = 0;
        }
        /**endif*/
    }
    /**end*//**@enduml*/
}
/**************************************************************************************************
 * End Of File
***************************************************************************************************/


