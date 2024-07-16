/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file eepromDemo.c
 *
 * @brief This file provides the demo functions and shadowRAM mechanism.
 *
 * File Short Name: eepromDemo
 *
 * @author: DEVIDRAJ.K
 *
 * @date: 4th April 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/


/* Define to prevent recursive inclusion -------------------------------------*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stm32h735g_discovery_ospi.h"
#include "eeprom_emul.h"
#include "eeprom_emul_cfg.h"
#include "Odometer_App.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

eepromData_t eep_Variables_t;
/* Define an array of pointers to the members of the structure */
uint32_t *eepromVariables[] = {
    &eep_Variables_t.eep_Total_Odometer,
    &eep_Variables_t.eep_MaxOdometerInKM,
    &eep_Variables_t.eep_MaxOdometerInMiles,
    &eep_Variables_t.eep_PPM,
    &eep_Variables_t.eep_TripA_Odo,
    &eep_Variables_t.eep_TripB_Odo,
    &eep_Variables_t.eep_Speedo_Units,
    &eep_Variables_t.eep_Speedo_MaxSpeedPulseCount,
    &eep_Variables_t.eep_Speedo_Threshold,
    &eep_Variables_t.eep_Tacho_IdleEngineRPM,
    &eep_Variables_t.eep_Tacho_WarningEngineRPM,
	&eep_Variables_t.eep_Tacho_MaximumEngineRPM,
    &eep_Variables_t.eep_Tacho_ErrorThresholdRPM,
    &eep_Variables_t.eep_Tacho_Fixed_PPR_Value,
    &eep_Variables_t.eep_Fuel_TankCapacity,
    &eep_Variables_t.eep_Fuel_WarningThresholdValue,
    &eep_Variables_t.eep_ServiceRequest_ThresholdDistance,
    &eep_Variables_t.eep_ServiceRequest_ThresholdTime,
    &eep_Variables_t.eep_LastServiced_TimeStamp,
    &eep_Variables_t.eep_LastServiced_Distance
};

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

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

uint16_t xES_WriteVariable(uint32_t VirtAddress, uint32_t Data,uint32_t *UpdateToShadowRAM);
/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
/**
  * @brief  Provides the Demo function to write/read the data
  *         to/from external eeprom and shadowRAM using emulation technique.
  * @param   void
  * @retval  No
  */

void vEE_Demo(void)
{

	/* Loop through each variable and perform the write check */
#if 1
	for (uint32_t i = 0x0 ; i <= 0x0000FFFF; i = i+6553)
//	for (uint32_t i = 0 ; i < 100; i++)
	{
		for (int j = 0; j < sizeof(eepromVariables) / sizeof(eepromVariables[0]); j++) //for (int j = 0; j < 20; j++)
		{

			uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[j],(uint32_t)(i),eepromVariables[j]);
			if (BSP_ERROR_NONE == FlashStatus)
			{
#if(EMUL_DEBUG_ENABLE == 1)
				printf("ESW_S:at %p,[%d]:0x%lx \n\r",eepromVariables[j],j,*eepromVariables[j]);
#endif
			}
			else
			{
#if(EMUL_DEBUG_ENABLE == 1)
				printf("ESW_F:0x%x\n\r",FlashStatus);
#endif
			}
		}
	}

	for (int jj = 0; jj < sizeof(eepromVariables) / sizeof(eepromVariables[0]); jj++)
	{
		uint16_t FlashStatus2= xEE_ReadVariable32bits((uint32_t)eepromVariables[jj],(uint32_t*)eepromVariables[jj]);
		if (BSP_ERROR_NONE == FlashStatus2)
		{
#if(EMUL_DEBUG_ENABLE == 0)
			//printf("ESR_S:at %p,[%d]:0x%lx \n\r",eepromVariables[jj],jj,*eepromVariables[jj]);
#endif
		}
		else
		{
#if(EMUL_DEBUG_ENABLE == 0)
			//printf("ESR_F:0x%x\n\r",FlashStatus2);
#endif
		}
	}
#endif
}

void vEmul_Init(void)
{
	/* Init Sequence */
	if ( 0U != xEE_Init(EE_FORCED_ERASE))
	{
#if(EMUL_DEBUG_ENABLE == 1)
		printf("xEE_Init:Fail \n\r");
#endif
	}
	else
	{
#if(EMUL_DEBUG_ENABLE == 1)
//		printf("xEE_Init:Success \n\r");
#endif
	}
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
