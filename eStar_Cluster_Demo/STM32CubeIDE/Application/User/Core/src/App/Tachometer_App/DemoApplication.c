/** \addtogroup  DemoApp
 *  @{
 * @file DemoApplication.h
 *
 * @brief Demo Applocation file is to test QueueSend and QueueRecieve with checksum verification
 *
 * File Short Name: DemoApplication
 *
 * Author: Vasavi Bashetti
 *
 * Create Date: 21-11-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "Task_ExeTime.h"
#include "DemoApplication.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "SecureQueue.h"
//#include "Stack_Usage.h"
//#include "PeriodicityCheck.h"
#include "string.h"
#include "stdio.h"
//#include "Task_OverLoad_DeadLock.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
#define UART_DEBUG 0
/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
uint32_t ulFail1Counter;

/**: Define a handle of QueueHandle_t type ;*/
//QueueHandle_t xQueue1Handle;

/**: Define a control block for the queue ;*/
StaticQueue_t xQcb_queue1;
volatile uint32_t ulresourceA = 0;
volatile uint32_t ulresourceB = 0;
/* create a queue buffer */
//uint8_t ucQueue1_buffer[GET_BUFFER_SIZE(10, 100)];

/** 
* @brief Secure Message Queue Attributes 
* 
* This structure defines the attributes necessary for initializing a secured FreeRTOS queue. 
* It contains essential configurations such as queue handle, control block memory, 
* message buffer, buffer size, message count, and message size. */

//secureMessageQueueAttr_t xDemoQueue1 =
//{
//	.xQueueHandle = NULL,  /**< Handle to the queue (initialized as NULL). */
//	.pvCb_mem = &xQcb_queue1,  /**< Reference to a memory structure for callback purposes. */
//	.pvMq_mem = ucQueue1_buffer,/**< Pointer to the buffer for the message queue. */
//	.ulBuffer_Size = sizeof(ucQueue1_buffer), /**< Size of the message queue buffer. */
//	.ulMsg_count = 10,		/**< Maximum number of messages in the queue. */
//	.ulMsg_size = GET_SECURED_QUEUE_SIZE(100),  /**< Size of each message in the queue. */
//};


/**: Data Buffer to store send data ;*/
//uint8_t ucQueue1_data[GET_SECURED_QUEUE_SIZE(100)] = " Heavy commercial vehicles - such as trucks and buses mainly use the ladder-type chassis structure.";
///**: Data Buffer to store received data ;*/
//uint8_t ucQueue1_Rxdata[GET_SECURED_QUEUE_SIZE(100)];


/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/
//static void vQueue1_ErrHook(secureMessageQueueAttr_t *xSecAttr, BaseType_t pc_ChecksumStatus);

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/*****************************************************************************
 * 
 * @brief vTask_demo1 Periodicity Check Information
 *
 * This structure holds the periodicity check information for vTask_demo1.
 *
 *
 * This structure contains the periodicity check information for task vTask_demo1.
 * It includes mandatory MinPeriodicity and MaxPeriodicity values in microseconds for periodicity validation.
 * There will be one info structure allocated for each task for periodicity monitoring
 *
 ******************************************************************************/
//TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T01 = {
//	.ucFistLoopFlag = 0,	/**< Flag must be set to zero for vTask_demo1 */
//    .ulCurrSwitchTime = 0,        /**< Current switch time for vTask_demo1 */
//    .ulPrevSwitchTime = 0,        /**< Previous switch time for vTask_demo1 */
//    .ulMinPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(450000),   /**< Minimum periodicity for vTask_demo1 */
//    .ulMaxPeriodicity = CONVERT_USEC_TO_TIMER_COUNTS(550000)   /**< Maximum periodicity for vTask_demo1 */
//};



/***************************************************************************//**
 * @brief Simulates a task that might lead to a deadlock scenario.
 * This function demonstrates a scenario where two resources (Resource A and Resource B)
 * are acquired and released in a specific order, potentially leading to a deadlock if
 * not managed properly.
 * @note This function is for demonstration purposes and does not handle deadlock scenarios.
 *       It's important to handle resource acquisition and release carefully in real scenarios
 *       to avoid deadlocks.
 ******************************************************************************/
void vTask_DeadLock_Test(void)
{
  /*Simulate some computation or processing with Resource A**/
  ulresourceA = 1;
  vLooper(100); // Simulate a delay

  /*Attempt to acquire Resource B**/
  while (ulresourceB != 0)
  {
	  /*Resource B is not available, wait or do other tasks**/
  }
  ulresourceB = 1; /*Acquire Resource B**/

  /*Simulate some computation or processing with Resource B**/
  vLooper(50); /*Simulate a delay**/

  /*Release resources in reverse order**/
  ulresourceB = 0; /*Release Resource B**/
  ulresourceA = 0; /*Release Resource A**/

  /*Simulate a longer delay before repeating the process**/
  vLooper(200);
}
/***************************************************************************//**
 * @brief Loops for a specified number of milliseconds.
 * This function creates a delay loop to wait for the specified number
 * of milliseconds.
 * @param milliseconds The number of milliseconds to loop for.
 * @return void
 ******************************************************************************/
void vLooper(uint32_t ulmilliseconds)
{
    for (uint32_t i = 0; i < ulmilliseconds; i++)
    {
        for (uint32_t j = 0; j < 20000; j++)
        {
            // Delay loop
        }
    }
}

/*****************************************************************************
 * @brief Demo application task to demostrate how to measure the execution time of a section of code
 *			(could be either entire task or a section of code)
 *			And It also checks the periodicity of the task triggers an callback if periodicity check fails
 *			It also sends the data defined in ucQueue1_data associated with (xDemoQueue1) with a specific size to the queue
 * 			and waits for a maximum of 20 ticks for the operation to succeed.
 * @param [in]  none
 * @param [out] none
 * @return None
 ******************************************************************************/
//void vTask_demo1(void *argument)
//{
//	/** @startuml */ /** start */
//	static TaskRunTimeStat_t p_measurement_var_ptr;
//
//	/**: Create the first secured queue using configuration from xDemoQueue1 ;*/
//	BaseType_t xTx_Status;
////    xQueue1Handle = xSecuredQueueCreate(&xDemoQueue1);
////	TaskHandle3_t xTaskHandle;
////
////	xTaskHandle = xTaskGetCurrentTaskHandle();
////
////	vRegisterTaskForOverloadDeadLockCheck(xTaskHandle,5,200,SwitchErrorHook1 );
//	vReset_executionTimeStats(&p_measurement_var_ptr);
//	for(;;)
//	{
//		/**:To ensure periodicity monitoring of this task, vCheckPeriodicity shall be called from here in a loop;*/
//		vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T01,vTask_demo1PeriodicityCheckErrorHook );
//		/**: Begin the execution measurement ;*/
//		vBeginExecMeas(&p_measurement_var_ptr);
//		/**: Send ucQueue1_data data to the queue ;*/
//		xTx_Status = xSecuredQueueSend(&xDemoQueue1,ucQueue1_data,sizeof(ucQueue1_data),20);
//	  	/*to test deadlock**/
//	  	vTask_DeadLock_Test();
//		/**: Perform the task or code segment for which you want to measure the execution time;*/
//
//		if(xTx_Status != pdFAIL)
//		{
//			vTaskDelay(2);
//		}
//		else
//		{
//			vTaskDelay(1);
//		}
//
//		for(uint32_t i = 0; i<0xFFFF;i++)
//		{
//
//		}
//		/**: End the execution measurement,Invoke a callback if it is out of boundaries ;*/
	//	vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(3000), execTimeFault_cb1);
//		vTaskDelay(500);
//
//	}


	/** end*/ /** @enduml */


void SwitchErrorHook1(uint8_t reason)
{
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
/*****************************************************************************
 * @brief Demo application task to demostrate how to measure the execution time of a section of code
 *			(could be either entire task or a section of code)
 *          This application also attempts to receive data from the secured queue
 * 			associated with (xDemoQueue1) using the xSecured_Queue_Receive function.
 * 			It receives the data into the ucQueue1_Rxdata buffer with a specific size from the queue
 * 			and waits for a maximum of 20 ticks for the operation to succeed.
 * @param [in]  none
 * @param [out] none
 * @return None
 ******************************************************************************/
void vTask_demo2(void *argument)
{
	/** @startuml */ /** start */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	BaseType_t xRx_Status;
//    TaskHandle3_t xTaskHandler;
//    xTaskHandler = xTaskGetCurrentTaskHandle();
  //  vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,400,SwitchErrorHook2 );
    vReset_executionTimeStats(&p_measurement_var_ptr);
	for(;;)
	{
		/**: Receive data associated with xDemoQueue1 ;*/
		//xRx_Status = xSecuredQueueRecieve(&xDemoQueue1, ucQueue1_Rxdata, sizeof(ucQueue1_Rxdata), 0, vQueue1_ErrHook);
		/**: Begin the execution measurement ;*/
		vBeginExecMeas(&p_measurement_var_ptr);

	   /*to test deadlock**/
		vTask_DeadLock_Test();
		/**: Perform the task or code segment for which you want to measure the execution time;*/

		if(xRx_Status != pdFAIL)
		{
			vTaskDelay(1);
		}
		else
		{
			vTaskDelay(2);
		}

		for(uint32_t i = 0; i<0xFFF;i++)
		{

		}
		/**: End the execution measurement,Invoke a callback if it is out of boundaries ;*/
		vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(3000), execTimeFault_cb2);

		vTaskDelay(500);

  	}
   /** end*/ /** @enduml */
}

void SwitchErrorHook2(uint8_t reason)
{
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
/*****************************************************************************
 * @brief Measures the execution time of a task.
 * 
 * @param [in]  none
 * 
 * @param [out] none
 * 
 * @return None
 ******************************************************************************/
//void vTask_StackMonitor_Demo(void *argument)
//{
//	/** @startuml */ /** start */
//  TaskHandle3_t xTaskHandler;
//
//  xTaskHandler = xTaskGetCurrentTaskHandle();
//
//  vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,1000,SwitchErrorHook3 );
//	for(;;)
//	{
//		/**: vStackMonitorDemonTask_Handler ;*/
//		vStackMonitorDemonTask_Handler();
//		vCheckTaskDeadlock();
//		for(uint32_t i = 0; i<0xFFFF;i++)
//		{
//
//		}
//		vTaskDelay(1000);
//	}
//	/** end*/ /** @enduml */
//}

void SwitchErrorHook3(uint8_t reason)
{
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
/****************************************************************************
 * @brief Executes a function while managing the maximum execution time.
 * 
 * @param [in]  maxExecutionTime
 * 
 * @param [out] none
 * 
 * @return None
 ******************************************************************************/
void execTimeFault_cb1(TaskRunTimeStat_t *p_measurement_var_ptr)
{
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

void execTimeFault_cb2(TaskRunTimeStat_t *p_measurement_var_ptr)
{

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


/*******************************************************************************
 * @brief Validates and transmits checksum status via UART (if UART_DEBUG is enabled)
 *
 * This function validates the checksum status and, if UART_DEBUG is enabled, transmits
 * the checksum status message via UART. It constructs a message indicating the checksum
 * status and transmits it via UART using HAL_UART_Transmit.
 *
 * @param[in] xQueue Handle to the FreeRTOS queue for checksum validation
 * @param[in] pc_ChecksumStatus Pointer to the checksum status message to be transmitted
 *
 * @return void
 *******************************************************************************/

//void vQueue1_ErrHook(secureMessageQueueAttr_t *xSecAttr, BaseType_t pc_ChecksumStatus)
//{
//#if(UART_DEBUG == 1)
//	/** @startuml */ /** start */
//	/**: Buffer to hold checksum status ;*/
//	char cStatusBuffer[50];
//
//	/**: Construct the checksum status message ;*/
//	sprintf(cStatusBuffer,"Checksum Status :%d\r\n",pc_ChecksumStatus);
//
//	/**: Transmit the checksum status message via UART ;*/
//	while (HAL_UART_Transmit(&huart1, (uint8_t*)cStatusBuffer, strlen(cStatusBuffer), 30) != HAL_OK)
//	{
//		/**: You can add some error handling here if needed ;*/
//		break;
//	}
//	/** end*/ /** @enduml */
//#endif
//}


/*******************************************************************************
 * @brief Performs actions when periodicity check fails for Task T01.
 *
 * This function is called when the periodicity check for Task T01 fails.
 *
 * @param[in] xPeriodicityCheckTaskInfo Pointer to TaskPeriodicityCheck_t structure holding task periodicity information.
 *
 * @return void
  *******************************************************************************/
//void vTask_demo1PeriodicityCheckErrorHook(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo)
//{
//#if(UART_DEBUG == 1)
//	/** @startuml */ /** start */
//	/**: Buffer to hold FailStatus;*/
//	char ucBuffer[50];
//
//	/**: Periodicity Check status ;*/
//	snprintf(ucBuffer,sizeof(ucBuffer),"vTask_demo1PeriodicityCheckErrorHook\r\n");
//
//	/**: Transmit the Periodicity Check status message via UART;*/
//	while (HAL_UART_Transmit(&huart1, (uint8_t*)ucBuffer, strlen(ucBuffer), 30) != HAL_OK)
//	{
//		/**: You can add some error handling here if needed;*/
//		break;
//	}
//	/** end*/ /** @enduml */
//#endif
//	ulFail1Counter++;
//}


/*******************************************************************************
 * @brief Application-defined hook for stack usage limit notification.
 *
 * This function is called when a task's stack usage exceeds the configured limit.
 *
 * @param xTask - Task handle.
 * @param pcTaskName - Task name as a string.
 *
 *******************************************************************************/
//void vApplicationStackUsageLimit(TaskHandle2_t xTask, const char *pcTaskName)
//{
//#if(UART_DEBUG == 1)
//
//	/** @startuml */ /** start */
//	/**: Buffer to hold vApplicationStackUsageLimit stats;*/
//	char ucBuffer[50];
//	/**: Transmit the vApplicationStackUsageLimit stats message via UART;*/
//	snprintf(ucBuffer, sizeof(ucBuffer), "Task handle: %p, Task name: %s, exceeded stack usage limit\n",xTask,pcTaskName);
//
//	while ((HAL_UART_Transmit(&huart1, (uint8_t *)ucBuffer, strlen(ucBuffer), 30)) != HAL_OK)
//	{
//		/**:You can add some error handling here if needed;*/
//		break;
//	}
//	/** end*/ /** @enduml */
//#endif
//}

/*******************************************************************************
 * @brief Callback function triggered when the maximum number of tasks is registered.
 *
 * This function is called when the number of registered tasks reaches the configured maximum limit.
 *
 * @param registered_task_index - Number of tasks currently registered.
*******************************************************************************/
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

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/



