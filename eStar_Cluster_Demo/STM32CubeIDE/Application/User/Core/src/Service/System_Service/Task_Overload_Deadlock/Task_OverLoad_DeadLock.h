/** \addtogroup  STACK_USAGE_MONITORING
 *  @{
 * @file Task_OverLoad_DeadLock.h
 *
 * @brief Task_OverLoad_DeadLock Header File
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

#ifndef TASK_OVERLOAD_DEADLOCK_H
#define TASK_OVERLOAD_DEADLOCK_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
//#include "safe_checks_Config.h"
//#include "../../../PlatformConfig/safe_checks_Config"
#include "../../../../../Core/PlatformConfig/safe_checks_Config.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

 /**************************************************************************************************
   * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define OVER_LOAD 0U

#define DEAD_LOCK 1U

 /**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

/***************************************************************************//**
 * @brief Error hook function type for handling context switch errors.
 * This function type defines the signature for an error hook that handles context switch errors.
 * It takes a reason as input and does not return any value.
 * @param[in] reason Reason code indicating the context switch error.
 ********************************************************************************/
typedef void (* ContextSwitchErrorHook)(uint8_t reason);

/** Forward declaration of a task control block. */
//struct tskTaskControlBlock;
///** Type definition for a TaskHandle3_t as a pointer to a task control block. */
//typedef struct tskTaskControlBlock* TaskHandle3_t;

struct tskTaskControlBlock;
typedef struct tskTaskControlBlock* TaskHandle3_t;
/*****************************************************************************
 * @brief Structure to hold information for monitoring tasks.
 * This structure contains information for monitoring tasks, including task handles, error hooks,
 * context switch counters, maximum context switch limits, start values for deadlock detection,
 * task active status flags, and deadlock timeout limits.
 ********************************************************************************/
typedef struct
{
    TaskHandle3_t handle; /**< Task handle of the monitored task. */
    ContextSwitchErrorHook errorHook; /**< Error hook for handling context switch errors. */
    uint32_t ulContextSwitchCounter; /**< Counter for context switches. */
    uint32_t ulMaxContextSwitchLimit; /**< Maximum context switch limit for the task. */
    uint32_t ulDeadLockTimeStartValue; /**< Start value for deadlock detection. */
    uint32_t ulDeadLockTimeoutLimit; /**< Timeout limit for detecting task deadlock. */
    uint8_t ucTaskActiveStatusFlag; /**< Flag indicating task activity status. */
} TaskMonitorInfo;


/***********************************************************************
 * @brief Registers a task for overload and deadlock checks.
 *
 * This function registers a task for monitoring context switches, overload conditions, and deadlock situations.
 *
 * @param xTaskHandle - Task handle of the registered task.
 * @param ulSwitchLimitCounter - Maximum allowed context switch limit for the task.
 * @param ulTimeoutLimit - Timeout limit(in Scheduler Ticks)for detecting a potential deadlock.
 * @param switchErrorHook - Function pointer to the error hook to be called in case of an issue.
 *
 * @return None
 *
 * @note The registered task information is stored in an array for monitoring.
 * @note Ensure that 'prvContextCount_Info' and 'ucRegTaskIndex' are declared and available in the scope where this function is used.
 * @note The error hook is invoked when the maximum number of tasks for context switch monitoring is reached.
 *************************************************************************/
void vRegisterTaskForOverloadDeadLockCheck(TaskHandle3_t xTask,
                                           uint32_t ulSwitchLimitCounter,
                                           uint32_t ulTimeoutLimit,
                                           ContextSwitchErrorHook switchErrorHook);

/*****************************************************************************
 * @brief Checks for task deadlocks based on task activity status and elapsed time.
 * @param [in] none
 * @param [out] none
 * @return none
 ******************************************************************************/
void vCheckTaskDeadlock(void);

/***********************************************************************
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
 **************************************************************************/
void vSafeChecksMovedTaskToReadyState(TaskHandle3_t pxTCB);

/*****************************************************************************
 * @brief This function performs safety checks when a task is switched out.
 * It updates context-related information and checks for context switch counts.
 * If the context switch count exceeds a specified limit, it triggers an error hook.
 * @param [in] none
 * @param [out] none
 * @return none
 ******************************************************************************/
void vSafeChecksTaskSwitchedOut(void);

#endif /* TASK_OVERLOAD_DEADLOCK_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

