/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "libjpeg.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "Sys_WakeUp_Reason.h"
#include "stm32h735g_discovery_ospi.h"
#include "stm32h7xx_hal_ospi.h"
#include "smHandler.h"
#include "digital_debounce.h"
#include "Analog_debounce.h"
#include "FuelGuage_App.h"
#include "Odometer_App.h"
#include "speedometer_App.h"
#include "Tachometer_App.h"
#include "batterVoltage_SmHandler.h"
#include "SwitchHandler_App.h"
#include "SwitchInf.h"
#include "clock_App.h"
#include "CAN_App.h"
#include "Indicator_App.h"
#include "stm32h7xx_hal_tim.h"
#include "ServiceRequest_App.h"
#include "../../STM32CubeIDE/Application/User/Core/src/App/DriverInfo_App/DriverInfoApp.h"



#include <touchgfx/hal/Config.hpp>
#include "eeprom_emul.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint16_t usADCValue;
uint32_t gl_BAT_MON_u32;
IndicationStatus_t indicator;
uint32_t execTimeFault;


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

FDCAN_HandleTypeDef hfdcan3;

IWDG_HandleTypeDef hiwdg1;

LTDC_HandleTypeDef hltdc;

OSPI_HandleTypeDef hospi1;
OSPI_HandleTypeDef hospi2;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

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
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for videoTask */
osThreadId_t videoTaskHandle;
uint32_t videoTaskBuffer[ 1024 ];
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
uint32_t WatchdogServiceBuffer[ 128 ];
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
uint32_t DigitalDebounceBuffer[ 128 ];
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
uint32_t Analog_DebounceBuffer[ 128 ];
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
uint32_t FuelGuageBuffer[ 128 ];
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
uint32_t OdoBuffer[ 128 ];
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
uint32_t SpeedoBuffer[ 128 ];
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
uint32_t SwitchHandlerBuffer[ 128 ];
osStaticThreadDef_t SwitchHandlerControlBlock;
const osThreadAttr_t SwitchHandler_attributes = {
  .name = "SwitchHandler",
  .cb_mem = &SwitchHandlerControlBlock,
  .cb_size = sizeof(SwitchHandlerControlBlock),
  .stack_mem = &SwitchHandlerBuffer[0],
  .stack_size = sizeof(SwitchHandlerBuffer),
  .priority = (osPriority_t) osPriorityLow,
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
uint32_t CAN_AppTaskBuffer[ 128 ];
osStaticThreadDef_t CAN_AppTaskControlBlock;
const osThreadAttr_t CAN_AppTask_attributes = {
  .name = "CAN_AppTask",
  .cb_mem = &CAN_AppTaskControlBlock,
  .cb_size = sizeof(CAN_AppTaskControlBlock),
  .stack_mem = &CAN_AppTaskBuffer[0],
  .stack_size = sizeof(CAN_AppTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
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
  .priority = (osPriority_t) osPriorityLow,
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
  .priority = (osPriority_t) osPriorityLow,
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

static void SYSCLKConfig_STOP(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_LTDC_Init(void);
static void MX_OCTOSPI1_Init(void);
static void MX_OCTOSPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_IWDG1_Init(void);
static void MX_ADC3_Init(void);
static void MX_FDCAN3_Init(void);
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

/* USER CODE BEGIN PFP */
void vBacklightBrightness(void);
void Disp_imgDataHyperRAM_Init(void);
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
HAL_StatusTypeDef res;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
KEEP extern const unsigned char image_abs_detection1_const[];
KEEP extern const unsigned char image_abs_detection2_const[];
KEEP extern const unsigned char image_background_const[];
KEEP extern const unsigned char image_clustericons1_const[];
KEEP extern const unsigned char image_clustericons2_const[];
KEEP extern const unsigned char image_doorswarning1_const[];
KEEP extern const unsigned char image_doorswarning2_const[];
KEEP extern const unsigned char image_engineoil1_const[];
KEEP extern const unsigned char image_engineoil2_const[];
KEEP extern const unsigned char image_fuelbar01_const[];
KEEP extern const unsigned char image_fuelbar02_const[];
KEEP extern const unsigned char image_fuelbar03_const[];
KEEP extern const unsigned char image_fuelbar04_const[];
KEEP extern const unsigned char image_fuelbar05_const[];
KEEP extern const unsigned char image_fuelbar06_const[];
KEEP extern const unsigned char image_fuelbar07_const[];
KEEP extern const unsigned char image_fuelbar08_const[];
KEEP extern const unsigned char image_fuelbar09_const[];
KEEP extern const unsigned char image_fuelbar10_const[];
KEEP extern const unsigned char image_high_beam_const[];
KEEP extern const unsigned char image_high_beam_1_const[];
KEEP extern const unsigned char image_highbeam1_const[];
KEEP extern const unsigned char image_highbeam2_const[];
KEEP extern const unsigned char image_leftindicator1_const[];
KEEP extern const unsigned char image_leftindicator2_const[];
KEEP extern const unsigned char image_lowbattery1_const[];
KEEP extern const unsigned char image_lowbattery2_const[];
KEEP extern const unsigned char image_lowbeam1_const[];
KEEP extern const unsigned char image_lowbeam2_const[];
KEEP extern const unsigned char image_rightindicator1_const[];
KEEP extern const unsigned char image_rightindicator2_const[];
KEEP extern const unsigned char image_rpmbar01_const[];
KEEP extern const unsigned char image_rpmbar02_const[];
KEEP extern const unsigned char image_rpmbar03_const[];
KEEP extern const unsigned char image_rpmbar04_const[];
KEEP extern const unsigned char image_rpmbar05_const[];
KEEP extern const unsigned char image_rpmbar06_const[];
KEEP extern const unsigned char image_rpmbar07_const[];
KEEP extern const unsigned char image_rpmbar08_const[];
KEEP extern const unsigned char image_rpmbar09_const[];
KEEP extern const unsigned char image_rpmbar10_const[];
KEEP extern const unsigned char image_rpmicon1_const[];
KEEP extern const unsigned char image_rpmicon2_const[];
KEEP extern const unsigned char image_tempicon1_const[];
KEEP extern const unsigned char image_tempicon2_const[];

#if 1
extern unsigned char ucImage_abs_detection1_HypRAM[24*20];
extern unsigned char ucImage_abs_detection2_HypRAM[24*20];
extern unsigned char ucImage_background_HypRAM[480*272];
extern unsigned char ucImage_clustericons1_HypRAM[24*20];
extern unsigned char ucImage_clustericons2_HypRAM[24*20];
extern unsigned char ucImage_doorswarning1_HypRAM[24*20];
extern unsigned char ucImage_doorswarning2_HypRAM[24*20];
extern unsigned char ucImage_engineoil1_HypRAM[24*20];
extern unsigned char ucImage_engineoil2_HypRAM[24*20];
extern unsigned char ucImage_fuelbar01_HypRAM[128*128];
extern unsigned char ucImage_fuelbar02_HypRAM[128*128];
extern unsigned char ucImage_fuelbar03_HypRAM[128*128];
extern unsigned char ucImage_fuelbar04_HypRAM[128*128];
extern unsigned char ucImage_fuelbar05_HypRAM[128*128];
extern unsigned char ucImage_fuelbar06_HypRAM[128*128];
extern unsigned char ucImage_fuelbar07_HypRAM[128*128];
extern unsigned char ucImage_fuelbar08_HypRAM[128*128];
extern unsigned char ucImage_fuelbar09_HypRAM[128*128];
extern unsigned char ucImage_fuelbar10_HypRAM[128*128];
extern unsigned char ucImage_high_beam_HypRAM[64*64];
extern unsigned char ucImage_high_beam_1_HypRAM[50*50];
extern unsigned char ucImage_highbeam1_HypRAM[24*20];
extern unsigned char ucImage_highbeam2_HypRAM[24*20];
extern unsigned char ucImage_leftindicator1_HypRAM[24*20];
extern unsigned char ucImage_leftindicator2_HypRAM[24*20];
extern unsigned char ucImage_lowbattery1_HypRAM[24*20];
extern unsigned char ucImage_lowbattery2_HypRAM[24*20];
extern unsigned char ucImage_lowbeam1_HypRAM[24*20];
extern unsigned char ucImage_lowbeam2_HypRAM[24*20];
extern unsigned char ucImage_rightindicator1_HypRAM[24*20];
extern unsigned char ucImage_rightindicator2_HypRAM[24*20];
extern unsigned char ucImage_rpmbar01_HypRAM[128*128];
extern unsigned char ucImage_rpmbar02_HypRAM[128*128];
extern unsigned char ucImage_rpmbar03_HypRAM[128*128];
extern unsigned char ucImage_rpmbar04_HypRAM[128*128];
extern unsigned char ucImage_rpmbar05_HypRAM[128*128];
extern unsigned char ucImage_rpmbar06_HypRAM[128*128];
extern unsigned char ucImage_rpmbar07_HypRAM[128*128];
extern unsigned char ucImage_rpmbar08_HypRAM[128*128];
extern unsigned char ucImage_rpmbar09_HypRAM[128*128];
extern unsigned char ucImage_rpmbar10_HypRAM[128*128];
extern unsigned char ucImage_rpmicon1_HypRAM[24*20];
extern unsigned char ucImage_rpmicon2_HypRAM[24*20];
extern unsigned char ucImage_tempicon1_HypRAM[24*20];
extern unsigned char ucImage_tempicon2_HypRAM[24*20];

#endif
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_LTDC_Init();
  MX_OCTOSPI1_Init();
  MX_OCTOSPI2_Init();
  MX_LIBJPEG_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_USART3_UART_Init();
 // MX_IWDG1_Init();
  MX_ADC3_Init();
  MX_FDCAN3_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  vEmul_Init();
  (void)Mcu_GetResetReason();
  State_Manager_init();
  vOdoInit();
  vSpeedoInit();
  vTacho_Init();
  clock_Init();
  vFuelGuageTaskInit();
  VCAN_Init();
  vIndicatorsInit();
  vServiceRequestTask_Init();

  if(HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_4)!=HAL_OK)
  {
	  Error_Handler();
  }
  if(HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4)!=HAL_OK)
  {
	  Error_Handler();
  }
  vBacklightBrightness();


  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

  /* creation of videoTask */
  videoTaskHandle = osThreadNew(videoTaskFunc, NULL, &videoTask_attributes);

  /* creation of WatchdogService */
 // WatchdogServiceHandle = osThreadNew(WDG_SRVC_Task, NULL, &WatchdogService_attributes);

  /* creation of DigitalDebounce */
  DigitalDebounceHandle = osThreadNew(DigitalDebounce_Task, NULL, &DigitalDebounce_attributes);

  /* creation of State_Manager */
  State_ManagerHandle = osThreadNew(State_Machine_Task, NULL, &State_Manager_attributes);

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

  /* creation of GetClock */
  GetClockHandle = osThreadNew(GetClockTask, NULL, &GetClock_attributes);

  /* creation of CAN_AppTask */
  CAN_AppTaskHandle = osThreadNew(CAN_Task, NULL, &CAN_AppTask_attributes);

  /* creation of Indicators_App */
  Indicators_AppHandle = osThreadNew(IndicatorsApp_Task, NULL, &Indicators_App_attributes);

  /* creation of ServiceIndicato */
  ServiceIndicatoHandle = osThreadNew(ServiceIndicatorApp_Task, NULL, &ServiceIndicato_attributes);

  /* creation of DriverInfoApp */
  DriverInfoAppHandle = osThreadNew(DriverInfoApp_Task, NULL, &DriverInfoApp_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 44;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 68;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLL2.PLL2M = 5;
  PeriphClkInitStruct.PLL2.PLL2N = 80;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.PLL3.PLL3M = 25;
  PeriphClkInitStruct.PLL3.PLL3N = 288;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 2;
  PeriphClkInitStruct.PLL3.PLL3R = 30;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOMEDIUM;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_PLL2;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.DataAlign = ADC3_DATAALIGN_RIGHT;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.SamplingMode = ADC_SAMPLING_MODE_NORMAL;
  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc3.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc3.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC3_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSign = ADC3_OFFSET_SIGN_NEGATIVE;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
  hdma2d.Init.OutputOffset = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief FDCAN3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN3_Init(void)
{

  /* USER CODE BEGIN FDCAN3_Init 0 */

  /* USER CODE END FDCAN3_Init 0 */

  /* USER CODE BEGIN FDCAN3_Init 1 */

  /* USER CODE END FDCAN3_Init 1 */
  hfdcan3.Instance = FDCAN3;
  hfdcan3.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan3.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan3.Init.AutoRetransmission = ENABLE;
  hfdcan3.Init.TransmitPause = DISABLE;
  hfdcan3.Init.ProtocolException = DISABLE;
  hfdcan3.Init.NominalPrescaler = 2;
  hfdcan3.Init.NominalSyncJumpWidth = 0x8;
  hfdcan3.Init.NominalTimeSeg1 = 13;
  hfdcan3.Init.NominalTimeSeg2 = 2;
  hfdcan3.Init.DataPrescaler = 1;
  hfdcan3.Init.DataSyncJumpWidth = 1;
  hfdcan3.Init.DataTimeSeg1 = 0x1F;
  hfdcan3.Init.DataTimeSeg2 = 0x8;
  hfdcan3.Init.MessageRAMOffset = 0;
  hfdcan3.Init.StdFiltersNbr = 1;
  hfdcan3.Init.ExtFiltersNbr = 1;
  hfdcan3.Init.RxFifo0ElmtsNbr = 1;
  hfdcan3.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan3.Init.RxFifo1ElmtsNbr = 1;
  hfdcan3.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan3.Init.RxBuffersNbr = 1;
  hfdcan3.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan3.Init.TxEventsNbr = 1;
  hfdcan3.Init.TxBuffersNbr = 1;
  hfdcan3.Init.TxFifoQueueElmtsNbr = 2;
  hfdcan3.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan3.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN3_Init 2 */

  /* USER CODE END FDCAN3_Init 2 */

}

/**
  * @brief IWDG1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG1_Init(void)
{

  /* USER CODE BEGIN IWDG1_Init 0 */

  /* USER CODE END IWDG1_Init 0 */

  /* USER CODE BEGIN IWDG1_Init 1 */

  /* USER CODE END IWDG1_Init 1 */
  hiwdg1.Instance = IWDG1;
  hiwdg1.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg1.Init.Window = 4095;
  hiwdg1.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG1_Init 2 */

  /* USER CODE END IWDG1_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 40;
  hltdc.Init.VerticalSync = 9;
  hltdc.Init.AccumulatedHBP = 53;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveW = 533;
  hltdc.Init.AccumulatedActiveH = 283;
  hltdc.Init.TotalWidth = 565;
  hltdc.Init.TotalHeigh = 285;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0x70000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief OCTOSPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */
  BSP_OSPI_NOR_Init_t ospi_nor_int;
  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  /* OCTOSPI1 parameter configuration*/
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 4;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_MACRONIX;
  hospi1.Init.DeviceSize = 32;
  hospi1.Init.ChipSelectHighTime = 2;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 2;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.DQSPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  sOspiManagerCfg.IOHighPort = HAL_OSPIM_IOPORT_1_HIGH;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */
  HAL_OSPI_DeInit(&hospi1);
  ospi_nor_int.InterfaceMode = BSP_OSPI_NOR_OPI_MODE;
  ospi_nor_int.TransferRate  = BSP_OSPI_NOR_DTR_TRANSFER;
  BSP_OSPI_NOR_DeInit(0);
  if(BSP_OSPI_NOR_Init(0, &ospi_nor_int) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
  if(BSP_OSPI_NOR_EnableMemoryMappedMode(0) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
  /* USER CODE END OCTOSPI1_Init 2 */

}

/**
  * @brief OCTOSPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OCTOSPI2_Init(void)
{

  /* USER CODE BEGIN OCTOSPI2_Init 0 */
//  BSP_OSPI_RAM_Init_t ospi_ram_init;
  /* USER CODE END OCTOSPI2_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};
  OSPI_HyperbusCfgTypeDef sHyperBusCfg = {0};

  /* USER CODE BEGIN OCTOSPI2_Init 1 */
  OSPI_HyperbusCmdTypeDef sCommand = {0};
  OSPI_MemoryMappedTypeDef sMemMappedCfg = {0};
  /* USER CODE END OCTOSPI2_Init 1 */
  /* OCTOSPI2 parameter configuration*/
  hospi2.Instance = OCTOSPI2;
  hospi2.Init.FifoThreshold = 4;
  hospi2.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi2.Init.MemoryType = HAL_OSPI_MEMTYPE_HYPERBUS;
  hospi2.Init.DeviceSize = 24;
  hospi2.Init.ChipSelectHighTime = 4;
  hospi2.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi2.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi2.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi2.Init.ClockPrescaler = 2;
  hospi2.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi2.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
  hospi2.Init.ChipSelectBoundary = 23;
  hospi2.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_USED;
  hospi2.Init.MaxTran = 0;
  hospi2.Init.Refresh = 400;
  if (HAL_OSPI_Init(&hospi2) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 2;
  sOspiManagerCfg.DQSPort = 2;
  sOspiManagerCfg.NCSPort = 2;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_2_LOW;
  sOspiManagerCfg.IOHighPort = HAL_OSPIM_IOPORT_2_HIGH;
  if (HAL_OSPIM_Config(&hospi2, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  sHyperBusCfg.RWRecoveryTime = 3;
  sHyperBusCfg.AccessTime = 6;
  sHyperBusCfg.WriteZeroLatency = HAL_OSPI_LATENCY_ON_WRITE;
  sHyperBusCfg.LatencyMode = HAL_OSPI_FIXED_LATENCY;
  if (HAL_OSPI_HyperbusCfg(&hospi2, &sHyperBusCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI2_Init 2 */
  sCommand.AddressSpace = HAL_OSPI_MEMORY_ADDRESS_SPACE;
  sCommand.AddressSize  = HAL_OSPI_ADDRESS_32_BITS;
  sCommand.DQSMode      = HAL_OSPI_DQS_ENABLE;
  sCommand.Address      = 0;
  sCommand.NbData       = 1;

  if (HAL_OSPI_HyperbusCmd(&hospi2, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

  if (HAL_OSPI_MemoryMapped(&hospi2, &sMemMappedCfg) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE END OCTOSPI2_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x12;
  sTime.Minutes = 0x30;
  sTime.Seconds = 0x20;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_THURSDAY;
  sDate.Month = RTC_MONTH_APRIL;
  sDate.Date = 0x10;
  sDate.Year = 0x24;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
//  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN RTC_Init 2 */
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != 0x32F2)
  {
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
		{
		  Error_Handler();
		}

		if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
		{
		  Error_Handler();
		}

    HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0x32F2);
  }
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LCD_BL_CTRL_Pin|RENDER_TIME_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MCU_ACTIVE_Pin|FRAME_RATE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VSYNC_FREQ_GPIO_Port, VSYNC_FREQ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Mode_switch_Pin */
  GPIO_InitStruct.Pin = Mode_switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Mode_switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Switch_Fuel_Pin */
  GPIO_InitStruct.Pin = Switch_Fuel_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Switch_Fuel_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Reset_switch_Pin */
  GPIO_InitStruct.Pin = Reset_switch_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Reset_switch_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EXTI_Pin */
  GPIO_InitStruct.Pin = EXTI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EXTI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RENDER_TIME_Pin */
  GPIO_InitStruct.Pin = RENDER_TIME_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(RENDER_TIME_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Ignition_Pin */
  GPIO_InitStruct.Pin = Ignition_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Ignition_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PF9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : MCU_ACTIVE_Pin FRAME_RATE_Pin */
  GPIO_InitStruct.Pin = MCU_ACTIVE_Pin|FRAME_RATE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_DISP_Pin */
  GPIO_InitStruct.Pin = LCD_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_DISP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : VSYNC_FREQ_Pin */
  GPIO_InitStruct.Pin = VSYNC_FREQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(VSYNC_FREQ_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void SYSCLKConfig_STOP(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  uint32_t pFLatency = 0;


   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);
   while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Get the Oscillators configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* After wake-up from STOP reconfigure the system clock: Enable HSE and PLL */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Get the Clocks configuration according to the internal RCC registers */
  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &pFLatency);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType     = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource  = RCC_SYSCLKSOURCE_PLLCLK;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, pFLatency) != HAL_OK)
  {
    Error_Handler();
  }
}


void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	HAL_IWDG_Refresh(&hiwdg1);
	//SystemClock_Config ();
	SYSCLKConfig_STOP();
	HAL_ResumeTick();
	HAL_LTDC_MspInit(&hltdc);
	printf("WAKEUP FROM RTC\r\n");
	//HAL_PWR_DisableSleepOnExit();
    /* Reset all RSR(Reset) flags */
    SET_BIT(RCC->RSR, RCC_RSR_RMVF);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Prevent unused argument(s) compilation warning */
	  UNUSED(GPIO_Pin);
	  res = HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	  if(res == HAL_OK)
	  {
		  printf("%02d:%02d:%02d \n", sTime.Hours, sTime.Minutes, sTime.Seconds);
	  }
	  SystemClock_Config ();
	  HAL_ResumeTick();
	  printf("WAKEUP FROM EXTII\r\n");
 // HAL_PWR_DisableSleepOnExit();
}





void Disp_imgDataHyperRAM_Init(void)
{


	memset(ucImage_abs_detection1_HypRAM, 0 ,(24*20));
	memset(ucImage_abs_detection2_HypRAM, 0 ,(24*20));
	memset(ucImage_background_HypRAM, 0 ,(480*272));
	memset(ucImage_clustericons1_HypRAM, 0 ,(24*20));
	memset(ucImage_clustericons2_HypRAM, 0 ,(24*20));
	memset(ucImage_doorswarning1_HypRAM, 0 ,(24*20));
	memset(ucImage_doorswarning2_HypRAM, 0 ,(24*20));
	memset(ucImage_engineoil1_HypRAM, 0 ,(24*20));
	memset(ucImage_engineoil2_HypRAM, 0 ,(24*20));
	memset(ucImage_fuelbar01_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar02_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar03_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar04_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar05_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar06_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar07_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar08_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar09_HypRAM, 0 ,(128*128));
	memset(ucImage_fuelbar10_HypRAM, 0 ,(128*128));
	memset(ucImage_high_beam_HypRAM, 0 ,(64*64));
	memset(ucImage_high_beam_1_HypRAM, 0 ,(50*50));
	memset(ucImage_highbeam1_HypRAM, 0 ,(24*20));
	memset(ucImage_highbeam2_HypRAM, 0 ,(24*20));
	memset(ucImage_leftindicator1_HypRAM, 0 ,(24*20));
	memset(ucImage_leftindicator2_HypRAM, 0 ,(24*20));
	memset(ucImage_lowbattery1_HypRAM, 0 ,(24*20));
	memset(ucImage_lowbattery2_HypRAM, 0 ,(24*20));
	memset(ucImage_lowbeam1_HypRAM, 0 ,(24*20));
	memset(ucImage_lowbeam2_HypRAM, 0 ,(24*20));
	memset(ucImage_rightindicator1_HypRAM, 0 ,(24*20));
	memset(ucImage_rightindicator2_HypRAM, 0 ,(24*20));
	memset(ucImage_rpmbar01_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar02_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar03_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar04_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar05_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar06_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar07_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar08_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar09_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmbar10_HypRAM, 0 ,(128*128));
	memset(ucImage_rpmicon1_HypRAM, 0 ,(24*20));
	memset(ucImage_rpmicon2_HypRAM, 0 ,(24*20));
	memset(ucImage_tempicon1_HypRAM, 0 ,(24*20));
	memset(ucImage_tempicon2_HypRAM, 0 ,(24*20));

#if 1
	uint32_t Address1= (uint32_t )(&image_abs_detection1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_abs_detection1_HypRAM,Address1,(24*20*4)))
	{
		printf("Copy Fail-1\n\r");
	}
	else
	{
		printf("Copy Success1\n\r");
	}

	uint32_t Address2= (uint32_t )(&image_abs_detection2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_abs_detection2_HypRAM,Address2,(24*20*4)))
	{
		printf("Copy Fail-2\n\r");
	}
	else
	{
		printf("Copy Success2\n\r");
	}

	uint32_t Address3= (uint32_t )(&image_background_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_background_HypRAM,Address3,(480*272*4)))
	{
		printf("Copy Fail-3\n\r");
	}
	else
	{
		printf("Copy Success3\n\r");
	}

	uint32_t Address4= (uint32_t )(&image_clustericons1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_clustericons1_HypRAM,Address4,(24*20*4)))
	{
		printf("Copy Fail-4\n\r");
	}
	else
	{
		printf("Copy Success4\n\r");
	}

	uint32_t Address5= (uint32_t )(&image_clustericons2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_clustericons2_HypRAM,Address5,(24*20*4)))
	{
		printf("Copy Fail-5\n\r");
	}
	else
	{
		printf("Copy Success5\n\r");
	}

	uint32_t Address6= (uint32_t )(&image_doorswarning1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_doorswarning1_HypRAM,Address6,(24*20*4)))
	{
		printf("Copy Fail-6\n\r");
	}
	else
	{
		printf("Copy Success6\n\r");
	}

	uint32_t Address7= (uint32_t )(&image_doorswarning2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_doorswarning2_HypRAM,Address7,(24*20*4)))
	{
		printf("Copy Fail-7\n\r");
	}
	else
	{
		printf("Copy Success7\n\r");
	}

	uint32_t Address8= (uint32_t )(&image_engineoil1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_engineoil1_HypRAM,Address8,(24*20*4)))
	{
		printf("Copy Fail-8\n\r");
	}
	else
	{
		printf("Copy Success8\n\r");
	}

	uint32_t Address9= (uint32_t )(&image_engineoil2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_engineoil2_HypRAM,Address9,(24*20*4)))
	{
		printf("Copy Fail-9\n\r");
	}
	else
	{
		printf("Copy Success9\n\r");
	}

	uint32_t Address10= (uint32_t )(&image_fuelbar01_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar01_HypRAM,Address10,(128*128*4)))
	{
		printf("Copy Fail-10\n\r");
	}
	else
	{
		printf("Copy Success10\n\r");
	}
	uint32_t Address11= (uint32_t )(&image_fuelbar02_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar02_HypRAM,Address11,(128*128*4)))
	{
		printf("Copy Fail-11\n\r");
	}
	else
	{
		printf("Copy Success11\n\r");
	}
	uint32_t Address12= (uint32_t )(&image_fuelbar03_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar03_HypRAM,Address12,(128*128*4)))
	{
		printf("Copy Fail-12\n\r");
	}
	else
	{
		printf("Copy Success12\n\r");
	}

	uint32_t Address13= (uint32_t )(&image_fuelbar04_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar04_HypRAM,Address13,(128*128*4)))
	{
		printf("Copy Fail-13\n\r");
	}
	else
	{
		printf("Copy Success13\n\r");
	}

	uint32_t Address14= (uint32_t )(&image_fuelbar05_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar05_HypRAM,Address14,(128*128*4)))
	{
		printf("Copy Fail-14\n\r");
	}
	else
	{
		printf("Copy Success14\n\r");
	}

	uint32_t Address15= (uint32_t )(&image_fuelbar06_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar06_HypRAM,Address15,(128*128*4)))
	{
		printf("Copy Fail-15\n\r");
	}
	else
	{
		printf("Copy Success15\n\r");
	}

	uint32_t Address16= (uint32_t )(&image_fuelbar07_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar07_HypRAM,Address16,(128*128*4)))
	{
		printf("Copy Fail-16\n\r");
	}
	else
	{
		printf("Copy Success16\n\r");
	}

	uint32_t Address17= (uint32_t )(&image_fuelbar08_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar08_HypRAM,Address17,(128*128*4)))
	{
		printf("Copy Fail-17\n\r");
	}
	else
	{
		printf("Copy Success17\n\r");
	}

	uint32_t Address18= (uint32_t )(&image_fuelbar09_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar09_HypRAM,Address18,(128*128*4)))
	{
		printf("Copy Fail-18\n\r");
	}
	else
	{
		printf("Copy Success18\n\r");
	}

	uint32_t Address19= (uint32_t )(&image_fuelbar10_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar10_HypRAM,Address19,(128*128*4)))
	{
		printf("Copy Fail-19\n\r");
	}
	else
	{
		printf("Copy Success19\n\r");
	}

	uint32_t Address20= (uint32_t )(&image_high_beam_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_high_beam_HypRAM,Address20,(64*64*4)))
	{
		printf("Copy Fail-20\n\r");
	}
	else
	{
		printf("Copy Success20\n\r");
	}

	uint32_t Address21= (uint32_t )(&image_high_beam_1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_high_beam_1_HypRAM,Address21,(50*50*4)))
	{
		printf("Copy Fail-20\n\r");
	}
	else
	{
		printf("Copy Success20\n\r");
	}

	uint32_t Address22= (uint32_t )(&image_highbeam1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_highbeam1_HypRAM,Address22,(24*20*4)))
	{
		printf("Copy Fail-21\n\r");
	}
	else
	{
		printf("Copy Success21\n\r");
	}

	uint32_t Address23= (uint32_t )(&image_highbeam2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_highbeam2_HypRAM,Address23,(24*20*4)))
	{
		printf("Copy Fail-21\n\r");
	}
	else
	{
		printf("Copy Success21\n\r");
	}


	uint32_t Address24= (uint32_t )(&image_leftindicator1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_leftindicator1_HypRAM,Address24,(24*20*4)))
	{
		printf("Copy Fail-23\n\r");
	}
	else
	{
		printf("Copy Success23\n\r");
	}

	uint32_t Address25= (uint32_t )(&image_leftindicator2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_leftindicator2_HypRAM,Address25,(24*20*4)))
	{
		printf("Copy Fail-24\n\r");
	}
	else
	{
		printf("Copy Success24\n\r");
	}

	uint32_t Address26= (uint32_t )(&image_lowbattery1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbattery1_HypRAM,Address26,(24*20*4)))
	{
		printf("Copy Fail-25\n\r");
	}
	else
	{
		printf("Copy Success25\n\r");
	}

	uint32_t Address27= (uint32_t )(&image_lowbattery2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbattery2_HypRAM,Address27,(24*20*4)))
	{
		printf("Copy Fail-26\n\r");
	}
	else
	{
		printf("Copy Success26\n\r");
	}

	uint32_t Address28= (uint32_t )(&image_lowbeam1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbeam1_HypRAM,Address28,(24*20*4)))
	{
		printf("Copy Fail-27\n\r");
	}
	else
	{
		printf("Copy Success27\n\r");
	}

	uint32_t Address29= (uint32_t )(&image_lowbeam2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbeam2_HypRAM,Address29,(24*20*4)))
	{
		printf("Copy Fail-28\n\r");
	}
	else
	{
		printf("Copy Success28\n\r");
	}

	uint32_t Address30= (uint32_t )(&image_rightindicator1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rightindicator1_HypRAM,Address30,(24*20*4)))
	{
		printf("Copy Fail-29\n\r");
	}
	else
	{
		printf("Copy Success29\n\r");
	}

	uint32_t Address31= (uint32_t )(&image_rightindicator2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rightindicator2_HypRAM,Address31,(24*20*4)))
	{
		printf("Copy Fail-30\n\r");
	}
	else
	{
		printf("Copy Success30\n\r");
	}


	uint32_t Address32= (uint32_t )(&image_rpmbar01_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar01_HypRAM,Address32,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address33= (uint32_t )(&image_rpmbar02_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar02_HypRAM,Address33,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address34= (uint32_t )(&image_rpmbar03_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar03_HypRAM,Address34,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address35= (uint32_t )(&image_rpmbar04_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar04_HypRAM,Address35,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address36= (uint32_t )(&image_rpmbar05_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar05_HypRAM,Address36,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address37= (uint32_t )(&image_rpmbar06_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar06_HypRAM,Address37,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address38= (uint32_t )(&image_rpmbar07_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar07_HypRAM,Address38,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address39= (uint32_t )(&image_rpmbar08_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar08_HypRAM,Address39,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address40= (uint32_t )(&image_rpmbar09_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar09_HypRAM,Address40,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}


	uint32_t Address41= (uint32_t )(&image_rpmbar10_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar10_HypRAM,Address41,(128*128*4)))
	{
		printf("Copy Fail-31\n\r");
	}
	else
	{
		printf("Copy Success31\n\r");
	}

	uint32_t Address42= (uint32_t )(&image_rpmicon1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmicon1_HypRAM,Address42,(24*20*4)))
	{
		printf("Copy Fail-32\n\r");
	}
	else
	{
		printf("Copy Success32\n\r");
	}

	uint32_t Address43= (uint32_t )(&image_rpmicon2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmicon2_HypRAM,Address43,(24*20*4)))
	{
		printf("Copy Fail-33\n\r");
	}
	else
	{
		printf("Copy Success33\n\r");
	}

	uint32_t Address44= (uint32_t )(&image_tempicon1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_tempicon1_HypRAM,Address44,(24*20*4)))
	{
		printf("Copy Fail-34\n\r");
	}
	else
	{
		printf("Copy Success34\n\r");
	}

	uint32_t Address45= (uint32_t )(&image_tempicon2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_tempicon2_HypRAM,Address45,(24*20*4)))
	{
		printf("Copy Fail-35\n\r");
	}
	else
	{
		printf("Copy Success35\n\r");
	}
#endif



}
/* USER CODE END 4 */

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

  /* Infinite loop */
  for(;;)
  {
//	  res = HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//	  if(res == HAL_OK)
//	  {
//		  printf("%02d:%02d:%02d \n", sTime.Hours, sTime.Minutes, sTime.Seconds);
//	  }
//
//	  res = HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//	  if(res == HAL_OK)
//	  {
//		  printf("Current date: %02d-%02d-%04d\n", sDate.Date, sDate.Month, sDate.Year);
//	  }
    osDelay(10000);
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
	    osDelay(30000); //watchdog period
	    //service or refresh or reload the watchdog here
	    printf("WDG_SRVC_Task\r\n");
	    if (HAL_IWDG_Refresh(&hiwdg1) != HAL_OK)
	    {
	          Error_Handler();
	    }

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
//  static TaskRunTimeStat_t p_measurement_var_ptr;
//  vReset_executionTimeStats(&p_measurement_var_ptr);
  /* Infinite loop */
  for(;;)
  {

	DebounceTask();
	vGet_Switch_DebouncedStatus();
     osDelay(4);


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
  /* Infinite loop */
  for(;;)
  {

	//HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x4E20, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
	  State_Manager_task();
	      osDelay(10);

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
  /* Infinite loop */
  for(;;)
  {
	  HAL_ADC_Start(&hadc3); // start the adc
	  HAL_ADC_PollForConversion(&hadc3, 100); // poll for conversion
	  gl_BAT_MON_u32 = HAL_ADC_GetValue(&hadc3); // get the adc value
	 // printf("gl_BAT_MON_u32:%ld\r\n",gl_BAT_MON_u32);
	//  HAL_ADC_Stop(&hadc1); // stop adc
	  analog_debounce_task();

#if(BATMON_TEST_MACRO == 1)
	  Batt_state = get_analog_debounce_state(0);
	  printf("Batt_state:%d\r\n",Batt_state);
#endif
    osDelay(100);
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
  /* Infinite loop */
  for(;;)
  {
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1);
	  usADCValue=(uint16_t)HAL_ADC_GetValue(&hadc1);
	  //printf("ADC-%d\r\n",usADCValue);
	  vFuelGuageTask();
    osDelay(100);
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
  /* Infinite loop */
  for(;;)
  {
	vOdoAlgorithm();
	osDelay(5000);
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
  /* Infinite loop */
  for(;;)
  {
	  vSpeedoAlgorithm();
    osDelay(configSPEEDO_ALGO_CALL_FREQ_IN_MS);
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
  /* Infinite loop */
  for(;;)
  {
	  vTacho_App();
    osDelay(1000);
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
  /* Infinite loop */
  for(;;)
  {
	  vSwitchHandlerTask();
	  Switch_Task();
	  vHandleModeResetActions();
	  osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
	  vGet_Clock();
	  vClockIncreament();
	  osDelay(500);
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
  /* Infinite loop */
  for(;;)
  {
//	vCANTransmit();
//	vCANReceive();
    osDelay(100);
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
  /* Infinite loop */
	for(;;)
	  {
		vIndicator_App_Task();
		indicator = xGetIndicatorstatus();
		//printf("indicator=%lu\r\n",indicator);
		//printf("Indicator_status: %x\r\n", indicator.Indicator_status); // Example: Print ReceivedData member

		//printf("Right indicator: %x\r\n", indicator.Indicator_status);
		// or
		//printf("Indicator_status: %x\r\n",  xGetIndicatorstatus());
	    osDelay(50);

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
  /* Infinite loop */
  for(;;)
  {
	  vServiceRequestTask();
    osDelay(1000);
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
  /* Infinite loop */
  for(;;)
  {
	vDriver_InfoTask();
    osDelay(1000);
  }
  /* USER CODE END DriverInfoApp_Task */
}

 /* MPU Configuration */

void MPU_Config(void)
{
 MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();
#if 0


  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as WT for OCTOSPI1 */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = OCTOSPI1_BASE;
  MPU_InitStruct.Size = MPU_REGION_SIZE_64MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
#endif
  /* Configure the MPU attributes as WT for OCTOSPI2 */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = OCTOSPI2_BASE;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
#endif /* USE_FULL_ASSERT */
