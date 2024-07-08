/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file eeprom_emul_cfg.h
 *
 * @brief This file contains all emulation configurations.
 *
 * File Short Name: eeprom_emul_cfg
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
***************************************************************************************************/
#ifndef INC_EEPROM_EMUL_CFG_H_   /* Guard against multiple inclusion */
#define INC_EEPROM_EMUL_CFG_H_

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "STM32H735xx.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
/* Flash base address and end addresses */
#define FLASH_BASE_ADDR      		    (uint32_t)(0x90000000U)		  	/* Ospi NOR FLash Base Address */
#define FLASH_END_ADDR       		    (uint32_t)(0x93FFFFFFU) 	  	/* 64 MegaBytes */

/*define user requirements*/
#define EE_FLASH_BASE_ADDR      		FLASH_BASE_ADDR
#define EE_EMULATION_START_ADDR			(uint32_t)(0x93FF0000U - EE_FLASH_BASE_ADDR)
#define EE_FLASH_SECTOR_SIZE 		  	4096U 							/* 4096Bytes //BSP_OSPI_NOR_BLOCK_4K */
#define CYCLES_NUMBER           		100000U  				 		/*!< Number of Erase/Write cycles given by manufacturer*/
#define NB_OF_VARIABLES         		20U//100U  							/*!< Number of variables to handle in eeprom */
#define NB_OF_WRITES				    1600000U 	//320000U					/* Number of writes required by each variable */

/* Page Header status*/
#define EE_ELEMENT_SIZE         	  	10U                         	 /*!< Size of element in Bytes */
#define EE_HEADER_ELEMENT_SIZE      	8U                          	 /*!< Size of element in Bytes */
#define PAGE_HEADER_SIZE       			EE_HEADER_ELEMENT_SIZE * 4U   	 /*!< Page Header is 4 elements to save page state */ //32Bytes//
#define BSP_INSTANCE					0								 /* BSP instance value */

/*Default values of elements*/
#define TOTAL_ODOMETER							(uint32_t)(0x000A)
#define MAX_ODOMETER_IN_KM						(uint32_t)(0x000A)
#define MAX_ODOMETER_IN_MILES					(uint32_t)(0x000A)
#define PPM										(uint32_t)(0x000A)
#define TRIPA_ODO								(uint32_t)(0x000A)
#define TRIPB_ODO								(uint32_t)(0x000A)
#define SPEEDO_UNITS							(uint32_t)(0x000A)
#define SPEEDO_MAX_SPEED_PULSE_COUNT			(uint32_t)(0x000A)
#define SPEEDO_THRESHOLD						(uint32_t)(0x000A)
#define TACHO_IDLE_ENGINE_RPM 					(uint32_t)(0x000A)
#define TACHO_WARNING_ENGINE_RPM				(uint32_t)(0x000A)
#define TACHO_MAXIMUM_ENGINE_RPM				(uint32_t)(0x000A)
#define TACHO_ERROR_THRESHOLD_RPM				(uint32_t)(0x000A)
#define TACHO_FIXED_PPR_VALUE					(uint32_t)(0x000A)
#define FUEL_TANK_CAPACITY						(uint32_t)(0x000A)
#define FUEL_WARNING_THRESHOLD_VALUE			(uint32_t)(0x000A)
#define SERVICE_REQUEST_THRESHOLD_DISTANCE		(uint32_t)(0x000A)
#define SERVICE_REQUEST_THRESHOLD_TIME			(uint32_t)(0x000A)
#define LAST_SERVICED_TIMESTAMP					(uint32_t)(0x000A)
#define LAST_SERVICED_DISTANCE					(uint32_t)(0x000A)

#define EMUL_DEBUG_ENABLE  (1U)

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

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

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
extern eepromData_t eep_Variables_t;
extern const eepromData_t eep_default_t;
extern uint32_t *eepromVariables[];

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
#endif /* INC_EEPROM_EMUL_CFG_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
