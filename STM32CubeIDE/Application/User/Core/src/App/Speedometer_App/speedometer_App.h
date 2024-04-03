/* 
 * File:   Speedometer.h
 * Author: ravit
 *
 * Created on February 22, 2024, 4:09 PM
 */

#ifndef SPEEDOMETER_H
#define	SPEEDOMETER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "speedometer_App_cfg.h"
#include "../ICU_middleware/ICU_driver.h"
#include "Tachometer_App.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define SpeedoTestMacro 1
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/
void vSpeedoInit(void);
void vInitializeSpeedometer(void);
void xLoadToEEPROM(void);
//uint32_t xGetSpeedValue(speedDisplayMetrics_t*, IndicationStatus_t*);
void vSpeedoAlgorithm(void);
uint32_t vPulseDeltaCounter(void);

void vCalculateSpeed(void);
void vCalculateSpeedInKm(void);
void vCalculateSpeedInMiles(void);

bool xSafeSpeedCheck(void);
void vCustomizeSpeedUnits(void);

#endif	/* SPEEDOMETER_H */

