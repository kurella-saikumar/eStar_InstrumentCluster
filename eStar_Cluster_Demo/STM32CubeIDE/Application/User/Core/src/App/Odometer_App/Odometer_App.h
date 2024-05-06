
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
 * File:   Odometer.h
 * Author: Monika
 *
 * Created on February 28, 2024, 4:09 PM
 */

#ifndef ODOMETER_H
#define	ODOMETER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "Odometer_App_cfg.h"
#include "../ICU_middleware/ICU_driver.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define OdoTestMacro 1

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/
void vOdoAlgorithm(void);
void vOdoInit(void);
void vCalculateOdo(void);
void vCalculateOdoInKm(void);
void vCalculateOdoInMiles(void);
uint32_t xGetOdoReadings(vehicleDisplayMetrics_t* OdoUnits);
uint32_t vPulseCount(void);

void vToggleOdoUnits(void);
uint16_t xGetTripA_OdoReading(vehicleDisplayMetrics_t *TripA_Units);
void vResetTripA_OdoReadings(void);
uint16_t xGetTripB_OdoReading(vehicleDisplayMetrics_t *TripB_Units);
void vResetTripB_OdoReadings(void);

void xWrite_OdoVal_to_EEPROM(void);
void xRetrive_LastStored_OdoVal_from_EEPROM(void);


#endif	/* ODOMETER_H */

