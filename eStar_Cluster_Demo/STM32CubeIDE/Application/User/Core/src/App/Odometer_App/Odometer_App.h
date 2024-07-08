
/** \addtogroup  
 *  @{
 * @file Odometer_App.h
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
 * File:   Odometer_App.h
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
//#include "Odometer_App_cfg.h"
//#include "../ICU_middleware/ICU_driver.h"
#include "../../Service/IO_HAL/ICU_middleware/ICU_driver.h"
#include "../../../PlatformConfig/Odometer_App_cfg.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define ODO_IN_KM 0U
#define ODO_IN_MILES 1U

#define ODO_TEST_MACRO 0U
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
//uint32_t xGetOdoReadings(uint8_t* OdoUnits);
uint32_t vPulseCount(void);

void vToggleOdoUnits(void);
//uint16_t xGetTripA_OdoReading(uint8_t *TripA_Units);
void vResetTripA_OdoReadings(void);
//uint16_t xGetTripB_OdoReading(uint8_t *TripB_Units);
void vResetTripB_OdoReadings(void);

void xWrite_OdoVal_to_EEPROM(void);
void xRetrive_LastStored_OdoVal_from_EEPROM(void);


#ifdef __cplusplus
extern "C" {
#endif

uint32_t xGetOdoReadings(uint8_t* OdoUnits);
uint16_t xGetTripA_OdoReading(uint8_t *TripA_Units);
uint16_t xGetTripB_OdoReading(uint8_t *TripB_Units);
#ifdef __cplusplus
}
#endif

#endif	/* ODOMETER_H */

