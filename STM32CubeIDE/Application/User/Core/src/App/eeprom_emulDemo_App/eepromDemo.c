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
#include "../../Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.h"
#include "eeprom_emul.h"
#include "eeprom_emul_cfg.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

eepromData_t eep_Variables_t, eep_shadowRAM_t;

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

#if 1
	&eep_Variables_t.eep_Tacho_MaximumEngineRPM,
    &eep_Variables_t.eep_Tacho_ErrorThresholdRPM,
    &eep_Variables_t.eep_Tacho_Fixed_PPR_Value,
    &eep_Variables_t.eep_Fuel_TankCapacity,
    &eep_Variables_t.eep_Fuel_WarningThresholdValue,
    &eep_Variables_t.eep_ServiceRequest_ThresholdDistance,
    &eep_Variables_t.eep_ServiceRequest_ThresholdTime,
    &eep_Variables_t.eep_LastServiced_TimeStamp,
    &eep_Variables_t.eep_LastServiced_Distance
#endif
};

uint32_t *eepromShadowVars[] = {
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

#if 1
	&eep_shadowRAM_t.eep_Tacho_MaximumEngineRPM,
    &eep_shadowRAM_t.eep_Tacho_ErrorThresholdRPM,
    &eep_shadowRAM_t.eep_Tacho_Fixed_PPR_Value,
    &eep_shadowRAM_t.eep_Fuel_TankCapacity,
    &eep_shadowRAM_t.eep_Fuel_WarningThresholdValue,
    &eep_shadowRAM_t.eep_ServiceRequest_ThresholdDistance,
    &eep_shadowRAM_t.eep_ServiceRequest_ThresholdTime,
    &eep_shadowRAM_t.eep_LastServiced_TimeStamp,
    &eep_shadowRAM_t.eep_LastServiced_Distance
#endif
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

#if 1
	.eep_Tacho_MaximumEngineRPM				= TACHO_MAXIMUM_ENGINE_RPM,
	.eep_Tacho_ErrorThresholdRPM	 		= TACHO_ERROR_THRESHOLD_RPM,
	.eep_Tacho_Fixed_PPR_Value				= TACHO_FIXED_PPR_VALUE,
	.eep_Fuel_TankCapacity 					= FUEL_TANK_CAPACITY,
	.eep_Fuel_WarningThresholdValue 		= FUEL_WARNING_THRESHOLD_VALUE,
	.eep_ServiceRequest_ThresholdDistance 	= SERVICE_REQUEST_THRESHOLD_DISTANCE,
	.eep_ServiceRequest_ThresholdTime 		= SERVICE_REQUEST_THRESHOLD_TIME,
	.eep_LastServiced_TimeStamp 			= LAST_SERVICED_TIMESTAMP,
	.eep_LastServiced_Distance 				= LAST_SERVICED_DISTANCE,
#endif
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
uint16_t vShadowRAM_Init(void);
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
		printf("BSP_OSPI_NOR_Init:Fail \n\r");
	}

	/* Read the current status of the OSPI memory */
	while ( BSP_ERROR_NONE != BSP_OSPI_NOR_GetStatus(0))
	{
		printf("BSP_OSPI_NOR_GetStatus:Fail \n\r");
	}

	/* Init Sequence */
	if ( 0U != xEE_Init(EE_FORCED_ERASE))
	{
		printf("xEE_Init:Fail \n\r");
	}
	else
	{
		printf("xEE_Init:Success \n\r");
	}

	/* ShadowRAM initialization*/
	vShadowRAM_Init();
	/* Loop through each variable and perform the write check */
	for (int i =10; i <90; i++)
	{
		for (int j = 0; j < sizeof(eepromVariables) / sizeof(eepromVariables[0]); j++)
		{
			uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[j],(uint32_t)(i),eepromVariables[j]);
			if (BSP_ERROR_NONE == FlashStatus)
			{
				printf("ESWrite Success:at %p, eepromVariables[%d]:%ld \n\r",eepromVariables[j],j,*eepromVariables[j]);
			}
			else
			{
				printf("ESWrite Fail:eepromVariables\n\r");
				break;
				//return FlashStatus;
			}
		}

	}
	/* Loop through each variable and perform the Read check */
	for (int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
	{
		uint16_t FlashStatus = xEE_ReadVariable32bits((uint32_t)eepromVariables[i], eepromVariables[i]);
		if (BSP_ERROR_NONE != FlashStatus)
		{
			printf("Read Fail:eepromVariables\n\r");
			break;
			//return FlashStatus;
		}
		else
		{
			printf("Read Success:eepromVariables[%d] at :%p data :%ld\n\r",i,eepromVariables[i],*eepromVariables[i]);
		}
//		osDelay(10);
	}
	/* De-initialize OSPI NOR Flash */
//	BSP_OSPI_NOR_DeInit(0);

}




/**
  * @brief  Write Variables in EEPROM and ShadowRAM.
  * @param  VirtAddress Variable name to be write
  * @param  Data Data to be write
  * @param  UpdateToShadowRAM update data into shadowRAM
  * @retval Status of the operation of during EEPROM write
  */

uint16_t xES_WriteVariable(uint32_t VirtAddress, uint32_t Data,uint32_t *UpdateToShadowRAM)
{
	if (BSP_ERROR_NONE == xEE_WriteVariable32bits(VirtAddress, Data)) //Write into EEPROM
	{
		*UpdateToShadowRAM = Data;
		return BSP_ERROR_NONE;

	}
	else
	{
		return BSP_ERROR_COMPONENT_FAILURE;
	}
}


/**
  * @brief  Initializes the shadowRAM with default values of variables
  * 		and update with last saved values in eeprom.
  * @param  None.
  * @retval FlashStatus:
  */
extern EE_Status prvEE_Format(EE_Erase_type EraseType);
uint16_t vShadowRAM_Init(void)
{
	uint16_t usFlashStatus;
#if 0
	uint8_t dummyData[8]={0xAA, 0x55,0xAA, 0x55,0xAA, 0x55,0xAA, 0x55};
	prvEE_Format(EE_FORCED_ERASE);
	xFI_WriteDoubleWord(0x3ff03f6, &dummyData[0]);
	xFI_WriteDoubleWord(0x3ff03fA, &dummyData[4]);
	xFI_WriteDoubleWord(0x3ff03fe, &dummyData[0]);
	xFI_WriteDoubleWord(0x3ff0402, &dummyData[4]);
	uint8_t read_array[16];
	BSP_OSPI_NOR_Read(BSP_INSTANCE, read_array, 0x3ff03f6, 16);
	printf("read_array = %x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x \n\r",read_array[0],read_array[1],read_array[2],read_array[3],read_array[4],read_array[5],read_array[6],read_array[7],read_array[8],read_array[9],read_array[10],read_array[11],read_array[12],read_array[13],read_array[14],read_array[15]);
#endif
	/* Write default values into eep_shadowRAM_t */
	memcpy(&eep_shadowRAM_t, &eep_default_t, sizeof(eepromData_t));

	/* Loop through each variable and perform the check*/
	for (int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
	{
		usFlashStatus = xEE_ReadVariable32bits((uint32_t)eepromVariables[i],eepromVariables[i]);
		if (BSP_ERROR_NONE != usFlashStatus)
		{
			printf("EERead Fail:\n\r");
			prvEE_Format(EE_FORCED_ERASE);
			return usFlashStatus;
			break;
		}
		else
		{
			printf("EERead Success:eepromVariables[%d] at :%p data :%ld\n\r",i,eepromVariables[i],*eepromVariables[i]);
		}
	}

	/* If EEPROM has valid data, update shadow RAM */
	memcpy(eepromShadowVars, eepromVariables, sizeof(eepromData_t));
	for(int i = 0; i < sizeof(eepromVariables) / sizeof(eepromVariables[0]); i++)
	{
		printf("Shadow_RAM Copy Success :eepromShadowVars[%d] at :0%p data :%ld\n\r",i,eepromShadowVars[i],*eepromShadowVars[i]);
	}
	return usFlashStatus;
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
