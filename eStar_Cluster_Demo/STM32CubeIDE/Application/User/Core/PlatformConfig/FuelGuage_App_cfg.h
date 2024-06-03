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

/*FAST_FILL_LOSS_FILTER parameters which takes the 3sec time to update from 0 to 4096*/
#define configFAST_FILL_LOSS_FILTER_STEPSIZE   273 /*6.66% Fuel*/
#define configFAST_FILL_LOSS_FILTER_UPDATERATE 2  /*200ms*/

/*SLOW_FILL_LOSS_FILTER parameters which takes the 5min time to update from 0 to 4096*/
#define configSLOW_FILL_LOSS_FILTER_STEPSIZE  136 /*3.33% Fuel*/
#define configSLOW_FILL_LOSS_FILTER_UPDATERATE 100 /*10sec */

/*NORMAL_FILL_LOSS_FILTER parameters which takes the 15min time to update from 0 to 4096*/
#define configNORMAL_FILL_LOSS_FILTER_STEPSIZE 136 /*3.33% Fuel*/
#define configNORMAL_FILL_LOSS_FILTER_UPDATERATE 300 /*30 sec*/

/*INSTANTANEOUS_FILTER parameters which takes the 100ms time to update from 0 to 4096*/
#define configINSTANTANEOUS_FILTER_STEPSIZE 4096 /*100% Fuel*/
#define configINSTANTANEOUS_FILTER_UPDATERATE 0 /*100ms*/


#define configMAXIMUM_ADC_RANGE 4095

#define configWINDOW_SIZE 30

#define configFAST_FILL_RANGE 819      /*20% of ADC range*/
#define configSLOW_FILL_RANGE 409      /*10% of ADC range*/
#define configWARNING_FUELLEVEL 341    /*8% of ADC range*/



#define configTASK_PERIOD_MS             100 /*100 milli seconds*/

#define configFASTFILL_UPDATETIME_MS     30000 /*3 sec*/
#define configFASTFILL_TIMEOUT_MS       (configFASTFILL_UPDATETIME_MS/configTASK_PERIOD_MS)

#define configSLOWFILL_UPDATETIME_MS     300000 /*5 Min*/
#define configSLOWFILL_TIMEOUT_MS       (configSLOWFILL_UPDATETIME_MS/configTASK_PERIOD_MS)

#define configNORMALFILL_UPDATETIME_MS  900000 /*15 Min*/
#define configNORMALFILL_TIMEOUT_MS     (configNORMALFILL_UPDATETIME_MS/configTASK_PERIOD_MS)



#endif/*FUELGUAGE_APP_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
