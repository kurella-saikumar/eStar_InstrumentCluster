/**\addtogroup  FUELGUAGE_CONFIGURATION
 * @{
 * @file FuelGuage_App_cfg.h
 *
 * @brief Critical_var_check_cfg Application specific configuration file
 *
 * File Short Name: FuelGuage_App_Cfg
 *
 * Author: Kuella Saikumar
 *
 * Create Date: 8th-April-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/

#ifndef SERVICEREQUEST_APP_CFG_H
#define SERVICEREQUEST_APP_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define configServiceRequestThreshold_Distance 5000
#define configServiceRequestThreshold_Time     3 /*3 months*/
#define DISTANCE_RESET_VALUE  100
#define WAIT_TIME  15
#define TIME_THRESHOLD  6
#define  DISTANCE_THRESHOLD 5000


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

#endif/*SERVICEREQUEST_APP_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
