
/** \addtogroup  
 *  @{
 * @file template.c
 *
 * @brief Template Source File
 *
 * File Short Name: 
 *
 * Author: 
 *
 * Create Date: 
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/

/* 
 * File:   Odometer_app_test.h
 * Author: Monika
 *
 * Created on February 24, 2024, 12:38 PM
 */

#ifndef ODOMETER_APP_TEST_H
#define	ODOMETER_APP_TEST_H

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdbool.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

//#include "../Odometer_App/../Odometer_App_test/Odometer_App_Test.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/
//vehicleDisplayMetrics_t displayOdoUnits;
//IndicationStatus_t displayOdoStatus;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/
//extern uint32_t xGetOdoReadings(vehicleDisplayMetrics_t* OdoUnits);
extern void vToggleOdoUnits(void);
bool xGetIgnitionStatus(void);
void vReadOdoUnitsTogglePin(void);
bool isResetSwitchPressed(void);





#endif	/* ODOMETER_APP_TEST_H */

