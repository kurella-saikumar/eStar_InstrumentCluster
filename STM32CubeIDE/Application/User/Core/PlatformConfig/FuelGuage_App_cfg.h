/**\addtogroup  FUELGUAGE_CONFIGURATION
 * @{
 * @file FuelGuage_App_cfg.h 
 *
 * @brief Critical_var_check_cfg Application specific configuration file
 * 
 * File Short Name: FuelGuage_App_Cfg
 *
 * Author: Saikumar kurella.
 *
 * Create Date: 22-Feb-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/

#ifndef FUELGUAGE_APP_CFG_H
#define FUELGUAGE_APP_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/


#define FAST_FILL_LOSS_FILTER_STEPSIZE   273 /*6.66% Fuel*/
#define FAST_FILL_LOSS_FILTER_UPDATERATE 2  /*200ms*/

#define SLOW_FILL_LOSS_FILTER_STEPSIZE  136.5 /*3.33% Fuel*/
#define SLOW_FILL_LOSS_FILTER_UPDATERATE 100 /*10sec */

#define NORMAL_FILL_LOSS_FILTER_STEPSIZE 136.5 /*3.33% Fuel*/
#define NORMAL_FILL_LOSS_FILTER_UPDATERATE 300 /*30 sec*/

#define INSTANTANEOUS_FILTER_STEPSIZE 4096 /*100% Fuel*/
#define INSTANTANEOUS_FILTER_UPDATERATE 0 /*100ms*/


#define MAXIMUM_ADC_RANGE 4095

#define WINDOW_SIZE 30

#define FAST_FILL_RANGE 819       /*20% of ADC range*/
#define SLOW_FILL_RANGE 409       /*10% of ADC range*/
#define WARNING_FUELLEVEL 341    /*8% of ADC range*/



#define TASK_PERIOD_MS             100 /*100 milli seconds*/

#define FASTFILL_UPDATETIME_MS     30000 /*3 sec*/
#define FASTFILL_TIMEOUT_MS       (FASTFILL_UPDATETIME_MS/TASK_PERIOD_MS)

#define SLOWFILL_UPDATETIME_MS     300000 /*5 Min*/
#define SLOWFILL_TIMEOUT_MS       (SLOWFILL_UPDATETIME_MS/TASK_PERIOD_MS)

#define NORMALFILL_UPDATETIME_MS  900000 /*15 Min*/
#define NORMALFILL_TIMEOUT_MS     (NORMALFILL_UPDATETIME_MS/TASK_PERIOD_MS)



#endif/*FUELGUAGE_APP_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
