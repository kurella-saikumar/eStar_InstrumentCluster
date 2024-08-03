/* 
 * File:   Speedometer_App.h
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
#include "../../../../Core/PlatformConfig/speedometer_App_cfg.h"
#include "../../Service/IO_HAL/ICU_middleware/ICU_driver.h"
#include "../../Service/IO_HAL/Switch_Handler/SwitchHandler_App.h"
#include "../Indicator_App/Indicator_App.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define SPEEDO_TEST_MACRO 0U
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/
typedef enum {
    SPEED_IN_KMPH,
    SPEED_IN_MPH,
} speedDisplayMetrics_t;

extern IndicationStatus_t speedStatus;
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
void vValidateSpeed(void);

bool xSafeSpeedCheck(void);
void vCustomizeSpeedUnits(void);
void prvSpeedDampOut(void);


#ifdef __cplusplus
extern "C"
{
#endif

uint32_t xGetSpeedValue(void);

uint32_t GetSpeedValueInKM(void);


#ifdef __cplusplus
}
#endif

#endif	/* SPEEDOMETER_H */
