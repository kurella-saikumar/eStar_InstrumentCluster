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
#define Fuel_Fast_Fill_Loss_Filter_StepSize 273 /*6.66% Fuel*/       /*341 33.33% Fuel*/
#define Fuel_Fast_Fill_Loss_Filter_UpdateRate 2 /*200ms*/            /*10 1sec*/

#define Fuel_slow_Fill_Loss_Filter_StepSize 136.5 /*3.33% Fuel*/     /*102 9.92% Fuel*/
#define Fuel_slow_Fill_Loss_Filter_UpdateRate 100 /*10sec */         /*300 30 sec*/

#define Fuel_Normal_Fill_Loss_Filter_StepSize 136.5 /*3.33% Fuel*/   /*51 4.97% Fuel*/
#define Fuel_Normal_Fill_Loss_Filter_UpdateRate 300 /*30 sec*/       /*450 45sec*/

#define Instantaneous_Filter_StepSize 4096 /*100% Fuel*/             /*1023 100%*/
#define Instantaneous_Filter_UpdateRate 0 /*100ms*/                  /*1 100ms */


#define Maximum_ADC_Range 4095

#define WINDOW_SIZE 30

#define FastFillRange 819       /*205 20% of ADC range*/
#define SlowFillRange 409       /*102 10% of ADC range*/
#define WARNING_FUELLEVEL 341    /*85*/



#define TASK_PERIOD_MS           100 /*100 milli seconds*/

#define FastFill_UpdateTime_ms   30000 /*3 sec*/
#define FastFill_TimeOut_ms      (FastFill_UpdateTime_ms/TASK_PERIOD_MS)

#define SlowFill_UpdateTime_ms   300000 /*5 Min*/
#define SlowFill_TimeOut_ms      (SlowFill_UpdateTime_ms/TASK_PERIOD_MS)

#define NormalFill_UpdateTime_ms 900000 /*15 Min*/
#define NormalFill_TimeOut_ms    (NormalFill_UpdateTime_ms/TASK_PERIOD_MS)



#endif/*FUELGUAGE_APP_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
