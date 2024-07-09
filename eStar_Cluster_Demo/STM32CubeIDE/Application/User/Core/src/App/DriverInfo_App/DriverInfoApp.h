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

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define DRIVERINFO_TEST_MACRO 1
#define FUEL_TEST_MACRO 0

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
	uint32_t Range;
}driverInfoModeStatus_t;


void vDriver_InfoTask(void);
void vCalculateAVSInKmperhour(void);
uint32_t vCalculateAFEKmperLitre(void);
uint8_t prvFuelSimulation(void);
//uint16_t convert_FuelPercentageToLitres(uint8_t);
int16_t convert_FuelPercentageToLitres(int8_t);
uint16_t vCalculateDTE(void);
uint32_t prvCalculateMovingAverage_Odo(uint32_t);
uint16_t prvCalculateMovingAverage_Fuel(uint16_t);
uint32_t prvCalculateAverage1(void);
uint16_t prvCalculateAverage2(void);
uint16_t DisplayDTE(bool flag,uint16_t);
uint32_t xGetAVSstatus(void);
uint32_t xGetAFEstatus(void);
uint16_t xGetDTEstatus(void);


#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
