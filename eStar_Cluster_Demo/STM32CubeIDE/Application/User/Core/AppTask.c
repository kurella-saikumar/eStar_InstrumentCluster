/** \addtogroup
 *  @{
 * @file AppTask.c
 * @file AppTask.h
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
#include "AppTask.h"
#include "InstrumentClusterInit.h"
#include "SafetyCheckPluginDemo.h"
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




#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */





uint16_t usADCValue;
uint32_t gl_BAT_MON_u32;
IndicationStatus_t indicator;
uint32_t execTimeFault;
//uint32_t ulFail1Counter;



typedef StaticTask_t osStaticThreadDef_t;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for videoTask */
osThreadId_t videoTaskHandle;
uint32_t videoTaskBuffer[ 2048 ];
osStaticThreadDef_t videoTaskControlBlock;
const osThreadAttr_t videoTask_attributes = {
  .name = "videoTask",
  .cb_mem = &videoTaskControlBlock,
  .cb_size = sizeof(videoTaskControlBlock),
  .stack_mem = &videoTaskBuffer[0],
  .stack_size = sizeof(videoTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for WatchdogService */
osThreadId_t WatchdogServiceHandle;
uint32_t WatchdogServiceBuffer[ 512 ];
osStaticThreadDef_t WatchdogServiceControlBlock;
const osThreadAttr_t WatchdogService_attributes = {
  .name = "WatchdogService",
  .cb_mem = &WatchdogServiceControlBlock,
  .cb_size = sizeof(WatchdogServiceControlBlock),
  .stack_mem = &WatchdogServiceBuffer[0],
  .stack_size = sizeof(WatchdogServiceBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DigitalDebounce */
osThreadId_t DigitalDebounceHandle;
uint32_t DigitalDebounceBuffer[ 512 ];
osStaticThreadDef_t DigitalDebounceControlBlock;
const osThreadAttr_t DigitalDebounce_attributes = {
  .name = "DigitalDebounce",
  .cb_mem = &DigitalDebounceControlBlock,
  .cb_size = sizeof(DigitalDebounceControlBlock),
  .stack_mem = &DigitalDebounceBuffer[0],
  .stack_size = sizeof(DigitalDebounceBuffer),
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for State_Manager */
osThreadId_t State_ManagerHandle;
uint32_t State_ManagerBuffer[ 1024 ];
osStaticThreadDef_t State_ManagerControlBlock;
const osThreadAttr_t State_Manager_attributes = {
  .name = "State_Manager",
  .cb_mem = &State_ManagerControlBlock,
  .cb_size = sizeof(State_ManagerControlBlock),
  .stack_mem = &State_ManagerBuffer[0],
  .stack_size = sizeof(State_ManagerBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Analog_Debounce */
osThreadId_t Analog_DebounceHandle;
uint32_t Analog_DebounceBuffer[ 512 ];
osStaticThreadDef_t Analog_DebounceControlBlock;
const osThreadAttr_t Analog_Debounce_attributes = {
  .name = "Analog_Debounce",
  .cb_mem = &Analog_DebounceControlBlock,
  .cb_size = sizeof(Analog_DebounceControlBlock),
  .stack_mem = &Analog_DebounceBuffer[0],
  .stack_size = sizeof(Analog_DebounceBuffer),
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for FuelGuage */
osThreadId_t FuelGuageHandle;
uint32_t FuelGuageBuffer[ 256 ];
osStaticThreadDef_t FuelGuageControlBlock;
const osThreadAttr_t FuelGuage_attributes = {
  .name = "FuelGuage",
  .cb_mem = &FuelGuageControlBlock,
  .cb_size = sizeof(FuelGuageControlBlock),
  .stack_mem = &FuelGuageBuffer[0],
  .stack_size = sizeof(FuelGuageBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OdoMeter */
osThreadId_t OdoMeterHandle;
uint32_t OdoBuffer[ 1024 ];
osStaticThreadDef_t OdoControlBlock;
const osThreadAttr_t OdoMeter_attributes = {
  .name = "OdoMeter",
  .cb_mem = &OdoControlBlock,
  .cb_size = sizeof(OdoControlBlock),
  .stack_mem = &OdoBuffer[0],
  .stack_size = sizeof(OdoBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for SpeedoMeter */
osThreadId_t SpeedoMeterHandle;
uint32_t SpeedoBuffer[ 256 ];
osStaticThreadDef_t SpeedoControlBlock;
const osThreadAttr_t SpeedoMeter_attributes = {
  .name = "SpeedoMeter",
  .cb_mem = &SpeedoControlBlock,
  .cb_size = sizeof(SpeedoControlBlock),
  .stack_mem = &SpeedoBuffer[0],
  .stack_size = sizeof(SpeedoBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for TachoMeter */
osThreadId_t TachoMeterHandle;
uint32_t TachoMeterBuffer[ 128 ];
osStaticThreadDef_t TachoMeterControlBlock;
const osThreadAttr_t TachoMeter_attributes = {
  .name = "TachoMeter",
  .cb_mem = &TachoMeterControlBlock,
  .cb_size = sizeof(TachoMeterControlBlock),
  .stack_mem = &TachoMeterBuffer[0],
  .stack_size = sizeof(TachoMeterBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for SwitchHandler */
osThreadId_t SwitchHandlerHandle;
uint32_t SwitchHandlerBuffer[ 512 ];
osStaticThreadDef_t SwitchHandlerControlBlock;
const osThreadAttr_t SwitchHandler_attributes = {
  .name = "SwitchHandler",
  .cb_mem = &SwitchHandlerControlBlock,
  .cb_size = sizeof(SwitchHandlerControlBlock),
  .stack_mem = &SwitchHandlerBuffer[0],
  .stack_size = sizeof(SwitchHandlerBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for GetClock */
osThreadId_t GetClockHandle;
uint32_t GetClockBuffer[ 128 ];
osStaticThreadDef_t GetClockControlBlock;
const osThreadAttr_t GetClock_attributes = {
  .name = "GetClock",
  .cb_mem = &GetClockControlBlock,
  .cb_size = sizeof(GetClockControlBlock),
  .stack_mem = &GetClockBuffer[0],
  .stack_size = sizeof(GetClockBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CAN_AppTask */
osThreadId_t CAN_AppTaskHandle;
uint32_t CAN_AppTaskBuffer[ 256 ];
osStaticThreadDef_t CAN_AppTaskControlBlock;
const osThreadAttr_t CAN_AppTask_attributes = {
  .name = "CAN_AppTask",
  .cb_mem = &CAN_AppTaskControlBlock,
  .cb_size = sizeof(CAN_AppTaskControlBlock),
  .stack_mem = &CAN_AppTaskBuffer[0],
  .stack_size = sizeof(CAN_AppTaskBuffer),
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for Indicators_App */
osThreadId_t Indicators_AppHandle;
uint32_t Indicators_AppBuffer[ 128 ];
osStaticThreadDef_t Indicators_AppControlBlock;
const osThreadAttr_t Indicators_App_attributes = {
  .name = "Indicators_App",
  .cb_mem = &Indicators_AppControlBlock,
  .cb_size = sizeof(Indicators_AppControlBlock),
  .stack_mem = &Indicators_AppBuffer[0],
  .stack_size = sizeof(Indicators_AppBuffer),
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for ServiceIndicato */
osThreadId_t ServiceIndicatoHandle;
uint32_t ServiceIndicatoBuffer[ 128 ];
osStaticThreadDef_t ServiceIndicatoControlBlock;
const osThreadAttr_t ServiceIndicato_attributes = {
  .name = "ServiceIndicato",
  .cb_mem = &ServiceIndicatoControlBlock,
  .cb_size = sizeof(ServiceIndicatoControlBlock),
  .stack_mem = &ServiceIndicatoBuffer[0],
  .stack_size = sizeof(ServiceIndicatoBuffer),
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for DriverInfoApp */
osThreadId_t DriverInfoAppHandle;
uint32_t DriverInfoAppBuffer[ 128 ];
osStaticThreadDef_t DriverInfoAppControlBlock;
const osThreadAttr_t DriverInfoApp_attributes = {
  .name = "DriverInfoApp",
  .cb_mem = &DriverInfoAppControlBlock,
  .cb_size = sizeof(DriverInfoAppControlBlock),
  .stack_mem = &DriverInfoAppBuffer[0],
  .stack_size = sizeof(DriverInfoAppBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for DeadLock */
osThreadId_t DeadLockHandle;
uint32_t DeadLockBuffer[ 128 ];
osStaticThreadDef_t DeadLockControlBlock;
const osThreadAttr_t DeadLock_attributes = {
  .name = "DeadLock",
  .cb_mem = &DeadLockControlBlock,
  .cb_size = sizeof(DeadLockControlBlock),
  .stack_mem = &DeadLockBuffer[0],
  .stack_size = sizeof(DeadLockBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* USER CODE BEGIN PV */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}


/* Private function prototypes -----------------------------------------------*/

void StartDefaultTask(void *argument);
extern void TouchGFX_Task(void *argument);
extern void videoTaskFunc(void *argument);
void WDG_SRVC_Task(void *argument);
void DigitalDebounce_Task(void *argument);
void State_Machine_Task(void *argument);
void Analog_Debounce_Task(void *argument);
void FuelGuageTask(void *argument);
void Odo_Task(void *argument);
void Speedo_Task(void *argument);
void Tacho_Task(void *argument);
void SwitchHandlerTask(void *argument);
void GetClockTask(void *argument);
void CAN_Task(void *argument);
void IndicatorsApp_Task(void *argument);
void ServiceIndicatorApp_Task(void *argument);
void DriverInfoApp_Task(void *argument);
void vCreate_LowPowerMode_Tasks(void);
void vCreate_ActiveMode_Tasks(void);
void vDelete_ActiveMode_Tasks(void);
/* end of prototypes -----------------------------------------------*/

/**
 * @brief Create all system tasks required for both active and low-power modes.
 *
 * This function creates all necessary tasks by calling:
 * - `vCreate_LowPowerMode_Tasks()`: for tasks running in both low-power and active modes.
 * - `vCreate_ActiveMode_Tasks()`: for tasks specific to active (normal) mode.
 */

void vCreate_AllTasks(void)
{
	/* Create the thread(s) */
	  vCreate_LowPowerMode_Tasks();
	  vCreate_ActiveMode_Tasks();
}

/**
 * @brief Create tasks that operate during both low-power and active modes.
 * @note Use this function to create tasks specifically required in low-power mode.
 */

void vCreate_LowPowerMode_Tasks(void)
{
	/* Create the thread(s) */
	  /* creation of defaultTask */
	  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	  /* creation of TouchGFXTask */
	  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

	  /* creation of videoTask */
	  videoTaskHandle = osThreadNew(videoTaskFunc, NULL, &videoTask_attributes);

	  /* creation of WatchdogService */
	  WatchdogServiceHandle = osThreadNew(WDG_SRVC_Task, NULL, &WatchdogService_attributes);

	  /* creation of DigitalDebounce */
	  DigitalDebounceHandle = osThreadNew(DigitalDebounce_Task, NULL, &DigitalDebounce_attributes);

	  /* creation of State_Manager */
	  State_ManagerHandle = osThreadNew(State_Machine_Task, NULL, &State_Manager_attributes);

	  /* creation of CAN_AppTask */
	  CAN_AppTaskHandle = osThreadNew(CAN_Task, NULL, &CAN_AppTask_attributes);

	  /* creation of DeadLock */
	  DeadLockHandle = osThreadNew(DeadLockTask, NULL, &DeadLock_attributes);

	  /* creation of GetClock */
	  GetClockHandle = osThreadNew(GetClockTask, NULL, &GetClock_attributes);
}

/**
 * @brief Create tasks that operate during active mode only.
 * @note Use this function to create tasks specific to normal or active mode operation.
 */
void vCreate_ActiveMode_Tasks(void)
{
	/* Create the thread(s) */
	  /* creation of Analog_Debounce */
	  Analog_DebounceHandle = osThreadNew(Analog_Debounce_Task, NULL, &Analog_Debounce_attributes);

	  /* creation of FuelGuage */
	  FuelGuageHandle = osThreadNew(FuelGuageTask, NULL, &FuelGuage_attributes);

	  /* creation of OdoMeter */
	  OdoMeterHandle = osThreadNew(Odo_Task, NULL, &OdoMeter_attributes);

	  /* creation of SpeedoMeter */
	  SpeedoMeterHandle = osThreadNew(Speedo_Task, NULL, &SpeedoMeter_attributes);

	  /* creation of TachoMeter */
	  TachoMeterHandle = osThreadNew(Tacho_Task, NULL, &TachoMeter_attributes);

	  /* creation of SwitchHandler */
	  SwitchHandlerHandle = osThreadNew(SwitchHandlerTask, NULL, &SwitchHandler_attributes);

	  /* creation of Indicators_App */
	  Indicators_AppHandle = osThreadNew(IndicatorsApp_Task, NULL, &Indicators_App_attributes);

	  /* creation of ServiceIndicato */
	  ServiceIndicatoHandle = osThreadNew(ServiceIndicatorApp_Task, NULL, &ServiceIndicato_attributes);

	  /* creation of DriverInfoApp */
	  DriverInfoAppHandle = osThreadNew(DriverInfoApp_Task, NULL, &DriverInfoApp_attributes);
}

void vDelete_ActiveMode_Tasks(void)
{
	osThreadId_t ActiveModeTaskHandles[] =
	{
			Analog_DebounceHandle,
			FuelGuageHandle,
			OdoMeterHandle,
			SpeedoMeterHandle,
			TachoMeterHandle,
			SwitchHandlerHandle,
			Indicators_AppHandle,
			ServiceIndicatoHandle,
			DriverInfoAppHandle
	};
	for(uint8_t ucLoopCounter = 0;ucLoopCounter<(sizeof(ActiveModeTaskHandles) / sizeof(ActiveModeTaskHandles[0]));ucLoopCounter++)
	{
		vTaskDelete(ActiveModeTaskHandles[ucLoopCounter]);
		if(ActiveModeTaskHandles[ucLoopCounter] != NULL)
		{
			Error_Handler();
		}
		else
		{
			printf("ActiveTask:%d Deleted\n",ucLoopCounter);
		}
	}
}
/* USER CODE BEGIN 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	uint8_t Ecu_Status = 0;
  /* Infinite loop */
  for(;;)
  {
	  vStackMonitorDemonTask_Handler();
	  Ecu_Status = pm_GetSyncStatus();
	switch (Ecu_Status)
	{
	case ECU_POWER_MODE_ACTIVE:
		/* Disable Wakeup Counter */
	    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	  break;
	case ECU_POWER_MODE_SLEEP:
	     /* Enter Stop Mode */
	  	 vSys_EnterSTOP_Mode();
	  	 vSys_WakeUpFromSTOP();
//	  	(void)Mcu_GetResetReason();
	     pm_ReqNewState(ECU_POWER_MODE_OFF);
	  break;
	case ECU_POWER_MODE_OFF:
	  // Handle ignition off state
	  break;
	default :
		break;
	}
    osDelay(100);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_WDG_SRVC_Task */
/**
* @brief Function implementing the WatchdogService thread.
* @param argument: Not used
* @retval None
*/



/* USER CODE END Header_WDG_SRVC_Task */
void WDG_SRVC_Task(void *argument)
{
  /* USER CODE BEGIN WDG_SRVC_Task */
  /* Infinite loop */
  for(;;)
  {
	    osDelay(WDT_WINDOW_OPEN_IN_SEC*1000); //watchdog period
	    //service or refresh or reload the watchdog here

	    //if(validate_tsk_wdt_kick())
	    {
			if (HAL_IWDG_Refresh(&hiwdg1) != HAL_OK)
			{
#if(DBGPrints_TestMacro == 0)
				printf("Watchdog Refresh Filure\r\n");
#endif
			}
			else
			{
#if(DBGPrints_TestMacro == 0)
//				printf("WS\r\n");
#endif
			}
	    }
//	    else
//	    {
//
//#if(DBGPrints_TestMacro == 0)
//			printf("Watchdog Service validation Filure\r\n");
//#endif
//			while(1);
//	    }

  }
  /* USER CODE END WDG_SRVC_Task */
}

/* USER CODE BEGIN Header_DigitalDebounce_Task */
/**
* @brief Function implementing the DigitalDebounce thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DigitalDebounce_Task */
void DigitalDebounce_Task(void *argument)
{
  /* USER CODE BEGIN DigitalDebounce_Task */
  static TaskRunTimeStat_t p_measurement_var_ptr;
  int32_t fl_wdt_task_kick_id_i32 = -1;
  vReset_executionTimeStats(&p_measurement_var_ptr);

  TaskHandle3_t xTaskHandler;
  xTaskHandler = xTaskGetCurrentTaskHandle();
  char *taskName = pcTaskGetName(xTaskHandler);
  vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,4000,SwitchErrorHook1 );
  fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(DIGITALDEBOUNCE_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(DIGITALDEBOUNCE_TASK_DELAY_IN_MS),taskName);
  /* Infinite loop */
  for(;;)
  {
	 // HAL_GPIO_TogglePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin);
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T01,vTask_demo1PeriodicityCheckErrorHook01 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  DebounceTask();
	  vGet_Switch_DebouncedStatus();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb1);
	  /* Kicking watchdog timer */
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
     osDelay(DIGITALDEBOUNCE_TASK_DELAY_IN_MS);



  }
  /* USER CODE END DigitalDebounce_Task */
}

/* USER CODE BEGIN Header_State_Machine_Task */
/**
* @brief Function implementing the State_Manager thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_State_Machine_Task */
void State_Machine_Task(void *argument)
{
  /* USER CODE BEGIN State_Machine_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,500,SwitchErrorHook2 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(STATE_MACHINE_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(STATE_MACHINE_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {

	 vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T02,vTask_demo1PeriodicityCheckErrorHook02 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  State_Manager_task();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(3000000), execTimeFault_cb2);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
	  osDelay(STATE_MACHINE_TASK_DELAY_IN_MS);
  }
  /* USER CODE END State_Machine_Task */
}

/* USER CODE BEGIN Header_Analog_Debounce_Task */
/**
* @brief Function implementing the Analog_Debounce thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Analog_Debounce_Task */
void Analog_Debounce_Task(void *argument)
{
  /* USER CODE BEGIN Analog_Debounce_Task */
// uint8_t Batt_state = 0 ;
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,500,SwitchErrorHook3 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(ANALOG_DEBOUNCE_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(ANALOG_DEBOUNCE_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  //HAL_GPIO_TogglePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin);
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T03,vTask_demo1PeriodicityCheckErrorHook03 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  HAL_ADC_Start(&hadc3); // start the adc
	  HAL_ADC_PollForConversion(&hadc3, 100); // poll for conversion
	  gl_BAT_MON_u32 = HAL_ADC_GetValue(&hadc3); // get the adc value
	  analog_debounce_task();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb3);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);

#if(BATMON_TEST_MACRO == 1)
	  Batt_state = get_analog_debounce_state(0);
#if(DBGPrints_TestMacro == 1)
	  printf("Batt_state:%d\r\n",Batt_state);
#endif
#endif
    osDelay(ANALOG_DEBOUNCE_TASK_DELAY_IN_MS);
  }
  /* USER CODE END Analog_Debounce_Task */
}

/* USER CODE BEGIN Header_FuelGuageTask */
/**
* @brief Function implementing the FuelGuage thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FuelGuageTask */
void FuelGuageTask(void *argument)
{
  /* USER CODE BEGIN FuelGuageTask */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,100,SwitchErrorHook4 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(FUELGUAGE_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(FUELGUAGE_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {

	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T04,vTask_demo1PeriodicityCheckErrorHook04 );
	  //HAL_GPIO_TogglePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin);
	  vBeginExecMeas(&p_measurement_var_ptr);
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1);
	  usADCValue=(uint16_t)HAL_ADC_GetValue(&hadc1);
	  vFuelGuageTask();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_TIMER_COUNTS_TO_US(1000), execTimeFault_cb4);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
      osDelay(FUELGUAGE_TASK_DELAY_IN_MS);
  }
  /* USER CODE END FuelGuageTask */
}

/* USER CODE BEGIN Header_Odo_Task */
/**
* @brief Function implementing the OdoMeter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Odo_Task */
void Odo_Task(void *argument)
{
  /* USER CODE BEGIN Odo_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,500,SwitchErrorHook5 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(ODO_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(ODO_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T05,vTask_demo1PeriodicityCheckErrorHook05 );
	  //HAL_GPIO_TogglePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin);
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vOdoAlgorithm();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb5);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
	osDelay(ODO_TASK_DELAY_IN_MS);
  }
  /* USER CODE END Odo_Task */
}

/* USER CODE BEGIN Header_Speedo_Task */
/**
* @brief Function implementing the SpeedoMeter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Speedo_Task */
void Speedo_Task(void *argument)
{
  /* USER CODE BEGIN Speedo_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,500,SwitchErrorHook6 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(SPEEDO_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(SPEEDO_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T06,vTask_demo1PeriodicityCheckErrorHook06 );
	  HAL_GPIO_TogglePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin);
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vSpeedoAlgorithm();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb6);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
	  osDelay(SPEEDO_TASK_DELAY_IN_MS);
  }
  /* USER CODE END Speedo_Task */
}

/* USER CODE BEGIN Header_Tacho_Task */
/**
* @brief Function implementing the TachoMeter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Tacho_Task */
void Tacho_Task(void *argument)
{
  /* USER CODE BEGIN Tacho_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,500,SwitchErrorHook7 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(TACHO_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(TACHO_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T07,vTask_demo1PeriodicityCheckErrorHook07 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vTacho_App();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb7);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
    osDelay(TACHO_TASK_DELAY_IN_MS);
  }
  /* USER CODE END Tacho_Task */
}

/* USER CODE BEGIN Header_SwitchHandlerTask */
/**
* @brief Function implementing the SwitchHandler thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SwitchHandlerTask */
void SwitchHandlerTask(void *argument)
{
  /* USER CODE BEGIN SwitchHandlerTask */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,100,SwitchErrorHook8 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(SWITCHHANDLER_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(SWITCHHANDLER_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T08,vTask_demo1PeriodicityCheckErrorHook08 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vSwitchHandlerTask();
	  Switch_Task();
	  vHandleModeResetActions();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(3000), execTimeFault_cb8);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
	  //printf("SwitchHandle = %d\n",p_measurement_var_ptr.ulexecutionTime);
	  osDelay(SWITCHHANDLER_TASK_DELAY_IN_MS);
  }
  /* USER CODE END SwitchHandlerTask */
}

/* USER CODE BEGIN Header_GetClockTask */
/**
* @brief Function implementing the GetClock thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetClockTask */
void GetClockTask(void *argument)
{
  /* USER CODE BEGIN GetClockTask */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,1000,SwitchErrorHook9 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(GETCLOCK_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(GETCLOCK_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T09,vTask_demo1PeriodicityCheckErrorHook09 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vGet_Clock();
	  //vClockIncreament();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb9);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
	  osDelay(GETCLOCK_TASK_DELAY_IN_MS);
  }
  /* USER CODE END GetClockTask */
}

/* USER CODE BEGIN Header_CAN_Task */
/**
* @brief Function implementing the CAN_AppTask thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_CAN_Task */
void CAN_Task(void *argument)
{
  /* USER CODE BEGIN CAN_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,10,100,SwitchErrorHook10 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(CAN_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(CAN_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T10,vTask_demo1PeriodicityCheckErrorHook10 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vNim_ProcessRxTask();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb10);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
      osDelay(CAN_TASK_DELAY_IN_MS);
  }
  /* USER CODE END CAN_Task */
}

/* USER CODE BEGIN Header_IndicatorsApp_Task */
/**
* @brief Function implementing the Indicators_App thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_IndicatorsApp_Task */
void IndicatorsApp_Task(void *argument)
{
  /* USER CODE BEGIN IndicatorsApp_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,100,SwitchErrorHook11 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(INDICATORSAPP_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(INDICATORSAPP_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
	for(;;)
	  {
		vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T11,vTask_demo1PeriodicityCheckErrorHook11 );
		vBeginExecMeas(&p_measurement_var_ptr);
		vIndicator_App_Task();
		indicator = xGetIndicatorstatus();
		vEndExecMeas(&p_measurement_var_ptr, CONVERT_USEC_TO_TIMER_COUNTS(1000), execTimeFault_cb11);
		wdt_kick_task(fl_wdt_task_kick_id_i32);
	    osDelay(INDICATORSAPP_TASK_DELAY_IN_MS);

	  }
  /* USER CODE END IndicatorsApp_Task */
}

/* USER CODE BEGIN Header_ServiceIndicatorApp_Task */
/**
* @brief Function implementing the ServiceIndicato thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ServiceIndicatorApp_Task */
void ServiceIndicatorApp_Task(void *argument)
{
  /* USER CODE BEGIN ServiceIndicatorApp_Task */
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,1000,SwitchErrorHook12 );
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(SERVICEINDICATOR_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(SERVICEINDICATOR_TASK_DELAY_IN_MS),taskName);

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T12,vTask_demo1PeriodicityCheckErrorHook12 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vServiceRequestTask();
	  vEndExecMeas(&p_measurement_var_ptr, CONVERT_TIMER_COUNTS_TO_US(1000), execTimeFault_cb12);
	  wdt_kick_task(fl_wdt_task_kick_id_i32);
    osDelay(SERVICEINDICATOR_TASK_DELAY_IN_MS);
  }
  /* USER CODE END ServiceIndicatorApp_Task */
}

/* USER CODE BEGIN Header_DriverInfoApp_Task */
/**
* @brief Function implementing the DriverInfoApp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DriverInfoApp_Task */
void DriverInfoApp_Task(void *argument)
{
  /* USER CODE BEGIN DriverInfoApp_Task */
	AVSreset_IO_LM_BV_FA_data();
	Odoreset_IO_LM_BV_FA_data();
	Fuelreset_IO_LM_BV_FA_data();
	static TaskRunTimeStat_t p_measurement_var_ptr;
	int32_t fl_wdt_task_kick_id_i32 = -1;
	vReset_executionTimeStats(&p_measurement_var_ptr);

	TaskHandle3_t xTaskHandler;
	xTaskHandler = xTaskGetCurrentTaskHandle();
	char *taskName = pcTaskGetName(xTaskHandler);
	fl_wdt_task_kick_id_i32 = register_for_watchdog_monitoring(WDT_TASK_MIN_COUNT(DRIVERINFOAPP_TASK_DELAY_IN_MS), WDT_TASK_MAX_COUNT(DRIVERINFOAPP_TASK_DELAY_IN_MS),taskName);

	vRegisterTaskForOverloadDeadLockCheck(xTaskHandler,5,1000,SwitchErrorHook13 );

  /* Infinite loop */
  for(;;)
  {
	  vCheckPeriodicity(&xPeriodicityCheckTaskInfo_T13,vTask_demo1PeriodicityCheckErrorHook13 );
	  vBeginExecMeas(&p_measurement_var_ptr);
	  vDriver_InfoTask();
	 vEndExecMeas(&p_measurement_var_ptr, CONVERT_TIMER_COUNTS_TO_US(1000), execTimeFault_cb13);
	 wdt_kick_task(fl_wdt_task_kick_id_i32);
    osDelay(DRIVERINFOAPP_TASK_DELAY_IN_MS);
  }
  /* USER CODE END DriverInfoApp_Task */
}

/* USER CODE BEGIN Header_DeadLockTask */
/**
* @brief Function implementing the DeadLock thread.
* @param argument: Not used
* @retval None
*/
/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	uint8_t counter = 0;
	counter++;
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif


