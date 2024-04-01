
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @author  		: DEVIDRAJ.K
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "../../Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.h"
#include "eeprom.h"
#include "eeprom_cfg.h"

/* USER CODE END Includes */

/*Default values of elements*/
#define TOTAL_ODOMETER							0000
#define MAX_ODOMETER_IN_KM						0000
#define MAX_ODOMETER_IN_MILES					0000
#define PPM										0000
#define TRIPA_ODO								0000
#define TRIPB_ODO								0000
#define SPEEDO_UNITS							0000
#define SPEEDO_MAX_SPEED_PULSE_COUNT			0000
#define SPEEDO_THRESHOLD						0000
#define TACHO_IDLE_ENGINE_RPM 					0000
#define TACHO_WARNING_ENGINE_RPM				0000
#define TACHO_MAXIMUM_ENGINE_RPM				0000
#define TACHO_ERROR_THRESHOLD_RPM				0000
#define TACHO_FIXED_PPR_VALUE					0000
#define FUEL_TANK_CAPACITY						0000
#define FUEL_WARNING_THRESHOLD_VALUE			0000
#define SERVICE_REQUEST_THRESHOLD_DISTANCE		0000
#define SERVICE_REQUEST_THRESHOLD_TIME			0000
#define LAST_SERVICED_TIMESTAMP					0000
#define LAST_SERVICED_DISTANCE					0000

/* Type of page erasing:
       EE_FORCED_ERASE     --> pages to erase are erased unconditionally
       EE_CONDITONAL_ERASE --> pages to erase are erased only if not fully erased
*/
typedef enum {
   EE_FORCED_ERASE,
   EE_CONDITIONAL_ERASE
} EE_Erase_type;

typedef struct
{
	uint32_t eep_Total_Odometer;
	uint32_t eep_MaxOdometerInKM;
	uint32_t eep_MaxOdometerInMiles;
	uint32_t eep_PPM;
	uint32_t eep_TripA_Odo;
	uint32_t eep_TripB_Odo;
	uint32_t eep_Speedo_Units;
	uint32_t eep_Speedo_MaxSpeedPulseCount;
	uint32_t eep_Speedo_Threshold;
	uint32_t eep_Tacho_IdleEngineRPM ;
	uint32_t eep_Tacho_WarningEngineRPM;
	uint32_t eep_Tacho_MaximumEngineRPM;
	uint32_t eep_Tacho_ErrorThresholdRPM;
	uint32_t eep_Tacho_Fixed_PPR_Value;
	uint32_t eep_Fuel_TankCapacity;
	uint32_t eep_Fuel_WarningThresholdValue;
	uint32_t eep_ServiceRequest_ThresholdDistance;
	uint32_t eep_ServiceRequest_ThresholdTime;
	uint32_t eep_LastServiced_TimeStamp;
	uint32_t eep_LastServiced_Distance;

}eepromData_t;


eepromData_t eep_shadowRAM_t;

const eepromData_t eep_default_t ={
		.eep_Total_Odometer 					= TOTAL_ODOMETER,
		.eep_MaxOdometerInKM 					= MAX_ODOMETER_IN_KM,
		.eep_MaxOdometerInMiles 				= MAX_ODOMETER_IN_MILES,
		.eep_PPM 								= PPM,
		.eep_TripA_Odo							= TRIPA_ODO,
		.eep_TripB_Odo 							= TRIPB_ODO,
		.eep_Speedo_Units 						= SPEEDO_UNITS,
		.eep_Speedo_MaxSpeedPulseCount			= SPEEDO_MAX_SPEED_PULSE_COUNT,
		.eep_Speedo_Threshold 		   			= SPEEDO_THRESHOLD,
		.eep_Tacho_IdleEngineRPM 				= TACHO_IDLE_ENGINE_RPM,
		.eep_Tacho_WarningEngineRPM 			= TACHO_WARNING_ENGINE_RPM,
		.eep_Tacho_MaximumEngineRPM				= TACHO_MAXIMUM_ENGINE_RPM,
		.eep_Tacho_ErrorThresholdRPM	 		= TACHO_ERROR_THRESHOLD_RPM,
		.eep_Tacho_Fixed_PPR_Value				= TACHO_FIXED_PPR_VALUE,
		.eep_Fuel_TankCapacity 					= FUEL_TANK_CAPACITY,
		.eep_Fuel_WarningThresholdValue 		= FUEL_WARNING_THRESHOLD_VALUE,
		.eep_ServiceRequest_ThresholdDistance 	= SERVICE_REQUEST_THRESHOLD_DISTANCE,
		.eep_ServiceRequest_ThresholdTime 		= SERVICE_REQUEST_THRESHOLD_TIME,
		.eep_LastServiced_TimeStamp 			= LAST_SERVICED_TIMESTAMP,
		.eep_LastServiced_Distance 				= LAST_SERVICED_DISTANCE,
};


/* Define an array of pointers to the members of the structure */

uint32_t *eepromVariables[] = {
    &eep_shadowRAM_t.eep_Total_Odometer,
    &eep_shadowRAM_t.eep_MaxOdometerInKM,
    &eep_shadowRAM_t.eep_MaxOdometerInMiles,
    &eep_shadowRAM_t.eep_PPM,
    &eep_shadowRAM_t.eep_TripA_Odo,
    &eep_shadowRAM_t.eep_TripB_Odo,
    &eep_shadowRAM_t.eep_Speedo_Units,
    &eep_shadowRAM_t.eep_Speedo_MaxSpeedPulseCount,
    &eep_shadowRAM_t.eep_Speedo_Threshold,
    &eep_shadowRAM_t.eep_Tacho_IdleEngineRPM,
    &eep_shadowRAM_t.eep_Tacho_WarningEngineRPM,
    &eep_shadowRAM_t.eep_Tacho_MaximumEngineRPM,
    &eep_shadowRAM_t.eep_Tacho_ErrorThresholdRPM,
    &eep_shadowRAM_t.eep_Tacho_Fixed_PPR_Value,
    &eep_shadowRAM_t.eep_Fuel_TankCapacity,
    &eep_shadowRAM_t.eep_Fuel_WarningThresholdValue,
    &eep_shadowRAM_t.eep_ServiceRequest_ThresholdDistance,
    &eep_shadowRAM_t.eep_ServiceRequest_ThresholdTime,
    &eep_shadowRAM_t.eep_LastServiced_TimeStamp,
    &eep_shadowRAM_t.eep_LastServiced_Distance
};


uint16_t ES_WriteVariable(uint32_t *VirtAddress, uint32_t Data)
{
	if (BSP_ERROR_NONE != EE_WriteVariable32bits((uint32_t)VirtAddress, Data)) //Write into EEPROM
	{
		return BSP_ERROR_COMPONENT_FAILURE;
	}
	else
	{
		*VirtAddress = Data; //update shadowRAM
		return BSP_ERROR_NONE;
	}
}

void shadowRAM_Init(void)
{
 uint16_t FlashStatus;
  /* Write default values into eep_shadowRAM_t */
  memcpy(&eep_shadowRAM_t, &eep_default_t, sizeof(eepromData_t));

  // Loop through each variable and perform the check
  for (int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
  {
	  FlashStatus = EE_ReadVariable32bits(eepromVariables[i],eepromVariables[i]);
      if (BSP_ERROR_NONE != FlashStatus)
      {
    	  printf("Read Fail:\n\r");
//          return FlashStatus;
      }
      else
      {
    	  printf("Read Success:eepromVariables[%d]:%ld \n\r",i,*eepromVariables[i]);
      }
  }

  // If EEPROM has valid data, update shadow RAM
  memcpy(&eep_shadowRAM_t, eepromVariables, sizeof(eepromData_t));
  //return FlashStatus;
}
void vEEpromDemoFunc(void)
{
  BSP_OSPI_NOR_Init_t ospiInit;

  printf("vEEpromDemoFunc\n\r");
  /*Initialize OSPI NOR Flash*/
  ospiInit.InterfaceMode = BSP_OSPI_NOR_OPI_MODE;  // or BSP_OSPI_NOR_OPI_MODE for Octal SPI
  ospiInit.TransferRate = BSP_OSPI_NOR_DTR_TRANSFER;  // or BSP_OSPI_NOR_DTR_TRANSFER for Double Transfer Rate

	BSP_OSPI_NOR_DeInit(0);

	/* Initialize OSPI NOR Flash */
	while ( BSP_ERROR_NONE != BSP_OSPI_NOR_Init(0, &ospiInit))
	{
	  printf("BSP_OSPI_NOR_Init:Fail \n\r");
	}

	/* Read the current status of the OSPI memory */
	while ( BSP_ERROR_NONE != BSP_OSPI_NOR_GetStatus(0))
	{
	  printf("BSP_OSPI_NOR_GetStatus:Fail \n\r");
	}

	/* Init Sequence */

#if 0
	if ( 0U != EE_Format(EE_FORCED_ERASE))
	{
		printf("EE_Format:Fail \n\r");
	}
	else
	{
		printf("EE_Format:Success \n\r");
	}
#endif

	if ( 0U != EE_Init(EE_FORCED_ERASE))
	{
		printf("EE_Init:Fail \n\r");
	}
	else
	{
		printf("EE_Init:Success \n\r");
	}

	shadowRAM_Init();


	// Loop through each variable and perform the check
	for (int i =0; i <50; i++)
	{
		for (int j = 0; j < sizeof(eepromVariables) / sizeof(eepromVariables[0]); j++)
		{
		  uint16_t FlashStatus= ES_WriteVariable(eepromVariables[j],(uint32_t)(i));
		  if (BSP_ERROR_NONE == FlashStatus)
		  {
			  printf("Write Success:at %p, eepromVariables[%d]:%ld \n\r",eepromVariables[j],j,*eepromVariables[j]);
		  }
		  else
		  {
			  printf("Write Fail:eepromVariables\n\r");
			  return FlashStatus;
		  }
		}
	}

	// Loop through each variable and perform the check
	for (int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
	{
		uint16_t FlashStatus = EE_ReadVariable32bits(eepromVariables[i], eepromVariables[i]);
		  if (BSP_ERROR_NONE != FlashStatus)
		  {
			  printf("Read Fail:\n\r");
			  return FlashStatus;
		  }
		  else
		  {
			  printf("Read Success:at :%p, eepromVariables[%d]:%ld\n\r",eepromVariables[i],i,*eepromVariables[i]);
		  }
	}

	/* De-initialize OSPI NOR Flash */
	BSP_OSPI_NOR_DeInit(0);
}
