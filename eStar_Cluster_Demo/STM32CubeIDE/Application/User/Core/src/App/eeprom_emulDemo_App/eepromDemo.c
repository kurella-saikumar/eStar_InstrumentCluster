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
	BSP_OSPI_NOR_Init_t ospiInit;

	/*Initialize OSPI NOR Flash*/
	ospiInit.InterfaceMode = BSP_OSPI_NOR_OPI_MODE;  // or BSP_OSPI_NOR_OPI_MODE for Octal SPI
	ospiInit.TransferRate = BSP_OSPI_NOR_DTR_TRANSFER;  // or BSP_OSPI_NOR_DTR_TRANSFER for Double Transfer Rate

	/* De-initialize OSPI NOR Flash */
	BSP_OSPI_NOR_DeInit(0);

	/* Initialize OSPI NOR Flash */
	while ( BSP_ERROR_NONE != BSP_OSPI_NOR_Init(0, &ospiInit))
	{
#if(EMUL_DEBUG_ENABLE == 1)
		printf("BSP_OSPI_NOR_Init:Fail \n\r");
#endif
	}

	/* Read the current status of the OSPI memory */
	while ( BSP_ERROR_NONE != BSP_OSPI_NOR_GetStatus(0))
	{
#if(EMUL_DEBUG_ENABLE == 1)
		printf("BSP_OSPI_NOR_GetStatus:Fail \n\r");
#endif
	}

//	prvEE_Format(EE_FORCED_ERASE); // EE_CONDITIONAL_ERASE
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

	/* ShadowRAM initialization*/
	vShadowRAM_Init();
	/********** Read Back the shadow 20 variable's latest values *******/
	/* Loop through each variable and perform the Read check */
	for (int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
	{
#if(EMUL_DEBUG_ENABLE == 1)
//		printf("ShadowRam Read: eepromVariables[%d] at :%p data :0x%lx\n\r",i,eepromVariables[i],*eepromVariables[i]);
#endif
	}
//	xRetrive_LastStored_OdoVal_from_EEPROM();
	/* Loop through each variable and perform the write check */
	for (uint32_t i = 0 ; i <= 0xFFFFFFFF; i = i+2)
	{
//		for (int j = 0; j < sizeof(eepromVariables) / sizeof(eepromVariables[0]); j++)
		for (int j = 0; j < 2; j++)
		{
			uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[j],(uint32_t)(i),eepromVariables[j]);
			if (BSP_ERROR_NONE == FlashStatus)
			{
#if(EMUL_DEBUG_ENABLE == 1)
//				printf("ESW_S:at %p,[%d]:%ld \n\r",eepromVariables[j],j,*eepromVariables[j]);
#endif
			}
			else
			{
#if(EMUL_DEBUG_ENABLE == 1)
				printf("ESW_F:\n\r");
#endif
			}
		}
	}
	xShadowUpdate(1);
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
