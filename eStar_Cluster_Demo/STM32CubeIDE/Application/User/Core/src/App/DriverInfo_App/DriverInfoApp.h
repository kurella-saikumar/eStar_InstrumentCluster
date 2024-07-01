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
	uint16_t AverageVehicleSpeed;
	uint16_t AverageFuelEconomy;
	uint16_t DistanceToEmpty;
}driverInfoModeStatus_t;


void vDriver_InfoTask(void);
void vCalculateAVSInKmperhour(void);
void vCalculateAFEKmperLitre(void);
uint8_t prvFuelSimulation(void);
uint16_t convert_FuelPercentageToLitres(uint8_t);
void vCalculateDTE(void);
uint32_t prvCalculateMovingAverage_Odo(uint32_t);
uint16_t prvCalculateMovingAverage_Fuel(uint16_t);
uint32_t prvCalculateAverage1(void);
uint16_t prvCalculateAverage2(void);
driverInfoModeStatus_t xGetInfostatus(void);


#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
