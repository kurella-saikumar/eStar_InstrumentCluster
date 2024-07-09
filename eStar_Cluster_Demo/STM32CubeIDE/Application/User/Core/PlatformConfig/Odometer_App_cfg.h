
/** \addtogroup  
 *  @{
 * @file  Odometer_App_cfg.h
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
 * File:   Odometer_App_cfg.h
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
#define MAX_ODO_VALUE_IN_KM 	(16093439UL)    /* 16,09,343.9 Km */
#define MAX_ODO_VALUE_IN_MILES 	(99999999UL)    /* 9,99,999.9 Miles */
#define PULSES_PER_100_METERS 	(1U)
#define PULSES_PER_1_METER 		(5U)
#define TRIP_A_MAX 				(10000U)
#define TRIP_B_MAX 				(10000U)
#define KM_TO_MILES_CONV_FACTOR (621U)    		/* (0.621*1000) */
#define DEFAULT_ODO_UNITS 		(ODO_IN_KM)
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/

//typedef bool IndicationStatus_t;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/






#endif	/* ODOMETER_CFG_H */

