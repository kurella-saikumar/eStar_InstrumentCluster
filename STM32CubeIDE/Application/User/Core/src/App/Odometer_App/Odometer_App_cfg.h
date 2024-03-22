
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
 * File:   Odometer_cfg.h
 * Author: Monika
 *
 * Created on February 28, 2024, 4:09 PM
 */

#ifndef ODOMETER_CFG_H
#define	ODOMETER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdbool.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
//#define PULSES_PER_100_METERS 1
//#define PULSE_MULTI_FACTOR 100
//#define MTS_TO_KM_DIST_CONV_FACTOR 1000
//#define KM_TO_MILES_DIST_CONV_FACTOR 0.621

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/
typedef enum {
    DEFAULT_ODO_UNITS,
    ODO_IN_KM,
    ODO_IN_MILES,
} vehicleDisplayMetrics_t;        


//typedef bool IndicationStatus_t;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
extern uint32_t mts_to_km_dist_conv_factor;
extern uint32_t pulse_multi_factor;
extern uint32_t pulsesPer100Meters;
extern  uint32_t Km_to_Miles_dist_conv_factor;

extern vehicleDisplayMetrics_t defaultOdoUnits;
extern vehicleDisplayMetrics_t OdometerUnits;
extern vehicleDisplayMetrics_t TripA_Units;
extern vehicleDisplayMetrics_t TripB_Units;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/






#endif	/* ODOMETER_CFG_H */

