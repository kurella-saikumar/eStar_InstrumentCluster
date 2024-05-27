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

#ifndef APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_
#define APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_

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
typedef struct{
	uint16_t AverageVehicleSpeed;
	uint16_t AverageFuelEconomy;
	uint16_t DistanceToEmpty;
}driverInfoModeStatus_t;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
#if 1
void vDriver_InfoTask(void);
void vCalculateAVSInKmperhour(void);
void vCalculateAFEKmperLitre(void);
uint8_t prvFuelSimulation(void);
void vCalculateDTE(void);
uint8_t Convertintolitres(uint8_t ucFuel_ConsumedinPer);
driverInfoModeStatus_t xGetInfostatus(void);
#endif

#if 0
uint8_t prvFuelSimulation(void);
int convert_FuelPercentageToLitres(int);
int calculateAFE(void);
int calculateDTE(void);
#endif

#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
