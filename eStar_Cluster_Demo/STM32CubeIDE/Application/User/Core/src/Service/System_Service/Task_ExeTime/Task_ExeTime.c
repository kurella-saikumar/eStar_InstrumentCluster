/** \addtogroup  MULTIPLE_TASKS_EXECUTION_TIME
 * @{
 * @Task_ExeTime.c
 *
 * @brief This file calculates Execution time for multiple task
 *
 * File Short Name:ExeTime
 *
 * Author:Vasavi Bashetti
 *
 * Create Date:28-11-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***********************************************************************************************/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stdio.h"

#include "Task_ExeTime.h"

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

static void prvReset_Counters(TaskRunTimeStat_t *p_measurement_var_ptr);

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
/***************************************************************************//**
 * @brief  reset_ulexecutionTimeStats_func resets the members of a struct TaskRunTimeStat_t to their initial values
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure
 * @param [out] none
 * @return none
 ******************************************************************************/
void vReset_executionTimeStats(TaskRunTimeStat_t *p_measurement_var_ptr)
{
   p_measurement_var_ptr->ucReset_flag = 1;
}
/***************************************************************************//**
 * @brief Resets counters and flags in the TaskRunTimeStat_t structure.
 * @param [in] p_measurement_var_ptr Pointer to the TaskRunTimeStat_t structure.
 * @param [out] none
 * @return none
 ******************************************************************************/
static void prvReset_Counters(TaskRunTimeStat_t *p_measurement_var_ptr)
{
    p_measurement_var_ptr->ucReset_flag = 0U; /**Reset the reset flag*/
	#ifdef COLLECT_ALL_EXECUTION_INFO
		p_measurement_var_ptr->ulAvg = 0U;  /**Reset average execution time*/
		p_measurement_var_ptr->ulmaxTime = 0U;   /**Reset maximum execution time*/
		p_measurement_var_ptr->ulminTime = 0xFFFFFFFFU;  /**Reset minimum execution time */
		p_measurement_var_ptr->ustask_Counter = 0U;  /**Reset task counter*/
	#endif
}

/***************************************************************************//**
 * @brief  beginExecMeas_func begins the execution time measurement by reading the timer count
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure
 * @param [out] none
 * @return none
 ******************************************************************************/
void vBeginExecMeas(TaskRunTimeStat_t *p_measurement_var_ptr)
{
    /** @startuml *//** start */
    /**if(P_measurement_var_ptr->resetflag is non_zero) then(true)*/
    if(p_measurement_var_ptr->ucReset_flag != 0U)
    {
        /**:function calls the reset_ulexecutionTimeStats function to reset the execution time statistics ;*/
    	prvReset_Counters(p_measurement_var_ptr);
    }/**endif*/
    p_measurement_var_ptr->ulstart_Count = portGET_RUN_TIME_COUNTER_VALUE();
    /** stop *//** @enduml */
 }

/***************************************************************************//**
 * @brief  endExecMeas_func ends the execution time measurement by reading the timer count and calculates the average
 * @param [in] p_measurement_var_ptr Pointer to the execution time measurement structure
 * @param [out] none
 * @return none
 ******************************************************************************/

void vEndExecMeas(TaskRunTimeStat_t *p_measurement_var_ptr,uint32_t ulmaxAllowedTime, execMetricMaxLimit_cb execTimeErrorHook_cb)
{
	uint32_t ul_execution_time;
	/**@startuml*//**start*/
	p_measurement_var_ptr->ulEnd_Count = portGET_RUN_TIME_COUNTER_VALUE();

	/**:Execution time calculated by subtracting ulstart_Count from ulEnd_Count and multiplied with Timer_Resolution in Nanoseconds;*/
	ul_execution_time = (p_measurement_var_ptr->ulEnd_Count - p_measurement_var_ptr->ulstart_Count);

	p_measurement_var_ptr->ulexecutionTime = ul_execution_time;
	//printf("FuelExe_Time: %ld\n",p_measurement_var_ptr->ulexecutionTime);

	#ifdef COLLECT_ALL_EXECUTION_INFO
		/**if(P_measurement_var_ptr->ustask_Counter does not match to current ustask_Counter) then(true)*/
		 if(p_measurement_var_ptr->ustask_Counter != MAX_CYCLE_Avg_EXEC)
		 {
			/**:increments the task counter in the structure by one;*/
			p_measurement_var_ptr->ustask_Counter++;
		 }
		/**endif*/
		/**if(ul_execution_time greater than max_time) then(true)*/
		if(ul_execution_time > p_measurement_var_ptr->ulmaxTime)
		{
			/**:ul_execution_time is assigned to ulmaxTime;*/
			p_measurement_var_ptr->ulmaxTime = ul_execution_time;
		}
		else
		{
			/**nothing to do*/
		}
		/**if(ul_execution_time less than ulminTime) then (true)*/
		if(ul_execution_time < p_measurement_var_ptr->ulminTime)
		{
			/**:ul_execution_time is assigned to ulminTime;*/
			p_measurement_var_ptr->ulminTime = ul_execution_time;
		}/**endif*/
		else
		{
			/**nothing to do*/
		}
		p_measurement_var_ptr->ulAvg = ((p_measurement_var_ptr->ulAvg * (p_measurement_var_ptr->ustask_Counter -1U))+(ul_execution_time))/p_measurement_var_ptr->ustask_Counter;
	#endif

	if (p_measurement_var_ptr->ulexecutionTime > ulmaxAllowedTime)
	{
		/**If the measurement is out of range, trigger the out-of-range callback*/
		if(execTimeErrorHook_cb != NULL)
		{
			execTimeErrorHook_cb(p_measurement_var_ptr);
	     }
		 else
		{
			/*nothing to do**/
		}
	}
	else
	{
	 /*nothing to do**/
	}

/** end*/ /** @enduml */
}


/** @} MULTIPLE_TASKS_EXECUTION_TIME*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/








