/** \addtogroup
 *  @{
 * @file SafetyCheckPluginDemo.c
 * @file SafetyCheckPluginDemo.h
 * @brief Template Source File
 *
 * File Short Name:
 *
 * Author:
 *
 * Create Date:
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/


/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

#include "SafetyCheckPluginDemo.h"
#include "InstrumentClusterInit.h"
#include "main.h"
#include "cmsis_os.h"
#include "Sys_WakeUp_Reason.h"
#include "digital_debounce.h"
#include "Analog_debounce.h"
#include "FuelGuage_App.h"
#include "Odometer_App.h"
#include "speedometer_App.h"
#include "Tachometer_App.h"
#include "SwitchHandler_App.h"
#include "SwitchInf.h"
#include "clock_App.h"
#include "CAN_NIM.h"
#include "ServiceRequest_App.h"
#include "DriverInfoApp.h"
#include "safe_checks_freeRTOSConfig.h"
#include "safe_checks_Config.h"
#include "Task_ExeTime.h"
#include "PeriodicityCheck.h"
#include "Stack_Usage.h"
#include "Task_OverLoad_DeadLock.h"
#include "wdgh.h"

/* Private function prototypes -----------------------------------------------*/
uint32_t ulFail1Counter;
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T01 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(3600),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(4400)   /**< Maximum periodicity for vTask_demo1 */
};

TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T02 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(9000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(11000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T03 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(90000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(110000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T04 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(90000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(110000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T05 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(225000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(275000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T06 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(225000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(275000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T07 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(90000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(110000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T08 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(45000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(55000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T09 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(450000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(550000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T10 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(7000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(13000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T11 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(45000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(55000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T12 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(450000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(550000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T13 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(450000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(550000)   /**< Maximum periodicity for vTask_demo1 */
};
TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T14 = {
	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
	.ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
	.ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
	.ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(450000),   /**< Minimum periodicity for vTask_demo1 */
	.ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(550000)   /**< Maximum periodicity for vTask_demo1 */
};
/* end of prototypes -----------------------------------------------*/


void vApplicationStackUsageLimit(TaskHandle2_t xTask, const char *pcTaskName)
{
#if(SafeChecks_TestMacro == 1)
	printf("Task handle: %p, Task name: %s, exceeded stack usage limit\n",xTask,pcTaskName);
#endif
#if(UART_DEBUG == 1)

	/** @startuml */ /** start */
	/**: Buffer to hold vApplicationStackUsageLimit stats;*/
	char ucBuffer[50];
	/**: Transmit the vApplicationStackUsageLimit stats message via UART;*/
	snprintf(ucBuffer, sizeof(ucBuffer), "Task handle: %p, Task name: %s, exceeded stack usage limit\n",xTask,pcTaskName);

	while ((HAL_UART_Transmit(&huart1, (uint8_t *)ucBuffer, strlen(ucBuffer), 30)) != HAL_OK)
	{
		/**:You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}


void vMaxTaskRegisteredCallback(uint8_t registered_task_index)
{
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold callbackHookMaxTaskRegistered index;*/
	char ucBuffer[50];
	/**: Transmit the callbackHookMaxTaskRegistered index message via UART;*/
	snprintf(ucBuffer, sizeof(ucBuffer), "callbackHookMaxTaskRegistered: %d\n",registered_task_index);
	while ((HAL_UART_Transmit(&huart1, (uint8_t *)ucBuffer, strlen(ucBuffer), 30)) != HAL_OK)
	{
		/**:You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}


void execTimeFault_cb1(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("DigitalDebounce_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook01(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("DigitalDebounce_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook1(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task1 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task1 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb2(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("State_Machine_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook02(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("State_Machine_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook2(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task2 state mc hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task2 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb3(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("Analog_Debounce_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook03(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("Analog_Debounce_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook3(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task3 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task3 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

/* USER CODE BEGIN Header_FuelGuageTask */
/**
* @brief Function implementing the FuelGuage thread.
* @param argument: Not used
* @retval None
*/
void execTimeFault_cb4(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("FuelGuageTask_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook04(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("FuelGuageTask periodicity Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook4(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task4 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task4 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb5(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 0)
	printf("Odo_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook05(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 0)
	printf("Odo_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook5(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task5 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task5 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb6(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("Speedo_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook06(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("Speedo_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook6(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task6 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task6 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}


void execTimeFault_cb7(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("Tacho_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook07(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("Tacho_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook7(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task7 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task7 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}


void execTimeFault_cb8(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("SwitchHandlerTask_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook08(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("SwitchHandlerTask periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook8(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task8 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task8 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb9(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("GetClockTask Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook09(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("GetClockTask periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook9(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task9 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task9 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb10(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("CAN_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook10(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("CAN_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook10(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task10 CAN hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task10 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}
void execTimeFault_cb11(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("IndicatorsApp_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook11(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("IndicatorsApp_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook11(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task11 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task11 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}


void execTimeFault_cb12(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("ServiceIndicatorApp_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook12(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("ServiceIndicatorApp_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook12(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task12 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task12 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}

void execTimeFault_cb13(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("DriverInfoApp_Task_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook13(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("DriverInfoApp_Task periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}

void SwitchErrorHook13(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task13 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task12 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}


void execTimeFault_cb14(TaskRunTimeStat_t *p_measurement_var_ptr)
{
#if(SafeChecks_TestMacro == 1)
	printf("adLockTask_ExeTime Failed\n");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold cExecutionTime ;*/
	char cExecutionTime[50];
	sprintf(cExecutionTime,"Execution time: %lu\r\n",CONVERT_TIMER_COUNTS_TO_US(p_measurement_var_ptr->ulexecutionTime));

	/**: Transmit the execTimeFault_cb status message via UART ;*/
	while (HAL_UART_Transmit(&huart1, cExecutionTime, strlen(cExecutionTime), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed ;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
}

void vTask_demo1PeriodicityCheckErrorHook14(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
{
#if(SafeChecks_TestMacro == 1)
	printf("DeadLockTask_periodicity Failed");
#endif
#if(UART_DEBUG == 1)
	/** @startuml */ /** start */
	/**: Buffer to hold FailStatus;*/
	char ucBuffer[50];

	/**: Periodicity Check status ;*/
	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");

	/**: Transmit the Periodicity Check status message via UART;*/
	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
	{
		/**: You can add some error handling here if needed;*/
		break;
	}
	/** end*/ /** @enduml */
#endif
	ulFail1Counter++;
}
void SwitchErrorHook14(uint8_t reason)
{
#if(SafeChecks_TestMacro == 1)
	printf("task14 hook- reason:%d \r\n",reason);
#endif
#if(UART_DEBUG == 1)
	/* Buffer to hold checksum status */
	char cStatusBuffer[50];
	/* Construct the checksum status message */
	sprintf(cStatusBuffer,"task13 hook, reason:%d \r\n",reason);
	/* Transmit the checksum status message via UART */
	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
	{
		/* You can add some error handling here if needed */
		break;
	}
#endif
}
/* USER CODE END Header_DeadLockTask */
void DeadLockTask(void *argument)
{
  /* USER CODE BEGIN DeadLockTask */
	int32_t fl_wdt_task_kick_id_i32 = -1;
	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,1000,SwitchErrorHook14 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(DEADLOCK_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(DEADLOCK_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckTaskDeadlock();
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
    osDelay(DEADLOCK_TASK_DELAY_IN_MS);
  }
  /* USER CODE END DeadLockTask */
}




