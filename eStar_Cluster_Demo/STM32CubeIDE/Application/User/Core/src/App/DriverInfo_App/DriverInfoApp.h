/** \addtogroup TEMPLATE
 *  @{
 * @file DriverInfoApp.h
 *
 *
 * File Short Name: DriverInfoApp.h

 *
 * @author: Sivadhanalakshmi T
 *
 * Created on: Apr 4, 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/

#ifndef DRIVERINFOAPP_H
#define DRIVERINFOAPP_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "stdbool.h"
#include "stdint.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Speedometer_App/speedometer_App.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define DRIVERINFO_TEST_MACRO 0
#define FUEL_TEST_MACRO 0

#define INFOSTATUS_IN_KM 0U
#define INFOSTATUS_IN_MILES 1U

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
typedef struct{
	uint32_t AverageVehicleSpeed;
	uint32_t AverageFuelEconomy;
	uint16_t Range;
}driverInfoModeStatus_t;

typedef enum
{
	UNITS_IN_KM,
	UINITS_IN_MILES,
}DriverInfo_Units_t;


void vCalculateAVS(void);
void vCalculateAFE(void);
void vCalculateRange(void);
void AVSreset_IO_LM_BV_FA_data(void);
void Odoreset_IO_LM_BV_FA_data(void);
void Fuelreset_IO_LM_BV_FA_data(void);
void vDriver_InfoTask(void);
uint8_t prvFuelSimulation(void);
int16_t prvconvert_FuelPercentageToLitres(int8_t);
uint16_t DisplayDTE(bool flag,uint16_t);



#ifdef __cplusplus
extern "C" {
#endif
uint32_t xGetAVSstatus(void);
uint32_t xGetAFEstatus(void);
uint16_t xGetRANGEstatus(void);
#ifdef __cplusplus
}
#endif
#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
