/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file batterVoltage_SmHandler_Demo.c
 *
 * @brief BatteryVoltage_StateManager Handler demo file perform action functions when transition occured.
 *
 * File Short Name:batterVoltage_SmHandler_Demo
 *
 * Author:k.saikumar
 *
 * Create Date: 08/07/2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
// #include "stdint.h"
// #include "stdbool.h"
#include "stdio.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "batterVoltage_SmHandler.h"
#include "Analog_debounce.h"
#include "Analog_debounce_cfg.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/


void HV_func(void);
void NV_func(void);
void LV_func(void);
void UHV_func(void);


void in_LV_func(void); 
void in_NV_func(void);
void in_HV_func(void);
void in_UHV_func(void);



/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
                                                                                                       
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief  LV_func function is to perform some action when the state changed to LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void LV_func(void)
{
  // printf("\nLOW_VOLTAGE_STATE_ENTRY_Action\n");
} 

/**
 * @brief  NV_func function is to perform some action when the state changed to NORMAL_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void NV_func(void)
{
  //printf("\nNORMAL_VOLTAGE_STATE_ENTRY_Action\n");
} 

/**
 * @brief  HV_func function is to perform some action when the state changed to HIGH_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void HV_func(void)
{
   //printf("\nHIGH_VOLTAGE_STATE_ENTRY_Action\n");
} 

/**
 * @brief  UHV_func function is to perform some action when the state changed to ULTRA_HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void UHV_func(void)
{
    //printf("\nULTRA_LOW_VOLTAGE_STATE_ENTRY_Action\n");
}

/**
 * @brief  in_LV_func function is to perform some action when the state state remain in LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_LV_func(void)
{
   // printf("\nLOW_LOW_voltage\n");
} 

/**
 * @brief  in_NV_func function is to perform some action when the state remain in NORMAL_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_NV_func(void)
{
   //printf("\nNORMAL_NORMAL_voltage\n");
} 

/**
 * @brief  in_HV_func function is to perform some action when the state state remain in HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_HV_func(void)
{
   // printf("\nHIGH_HIGH_voltage\n");
} 
/**
 * @brief  in_UHV_func function is to perform some action when the state remain in ULTRA_HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void in_UHV_func(void)
{
    //printf("\nUL_UL_voltage\n");
}



/**************************************************************************************************
 * End Of File
***************************************************************************************************/
