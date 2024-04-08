
/** \addtogroup  
 *  @{

 * @file Speedometer_App_cfg.h
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
 * File:   Speedometer_cfg.h
 * Author: ravit
 *
 * Created on February 22, 2024, 4:09 PM
 */

#ifndef SPEEDOMETER_CFG_H
#define	SPEEDOMETER_CFG_H

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
/**Vehicle specific configurations*/
#define configPULSES_PER_100_METERS               1
#define configMAX_VEH_SPEED_IN_KM                 200
#define configMAX_VEH_SPEED_IN_MILES              125

/**Industry standard configurations*/
#define configMTS_TO_KM_DIST_CONV_FACTOR          1000
#define configSEC_TO_HR_TIME_CONV_FACTOR          3600

/**Speedometer configurations*/
#define configSPEEDO_ALGO_CALL_FREQ_IN_MS			5000

/**Km configuration parameters*/
#define configPULSE_MULTI_FACTOR                  100
#define configTIME_IN_SECS                        (configSPEEDO_ALGO_CALL_FREQ_IN_MS/1000)
#define configSAFE_THRESHOLD_VEH_SPEED_IN_KM      60

/**Miles configuration parameters*/
#define configKM_TO_MILES_DIV_FACTOR                 50
#define configKM_TO_MILES_MULTI_FACTOR               16
#define configSAFE_THRESHOLD_VEH_SPEED_IN_MILES      40

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






#endif	/* SPEEDOMETER_CFG_H */

