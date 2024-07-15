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
#include "../../../App/Indicator_App/Indicator_App.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/


void vHVFunc(void);
void vNVFunc(void);
void vLVFunc(void);
void vULVFunc(void);


void vInLVFunc(void); 
void vInNVFunc(void);
void vInHVFunc(void);
void vInULVFunc(void);



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
 * @brief  vULVFunc function is to perform some action when the state changed to ULTRA_Low_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vULVFunc(void)
{
	Status.indicators.low_battery_indicator = 1;
#if(BATMON_TEST_MACRO == 1)
    printf("\nULTRA_LOW_VOLTAGE_STATE_ENTRY_Action\n");

#endif
}
/**
 * @brief  vLVFunc function is to perform some action when the state changed to LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vLVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
    printf("\nLOW_VOLTAGE_STATE_ENTRY_Action\n");
#endif
} 

/**
 * @brief  vNVFunc function is to perform some action when the state changed to NORMAL_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vNVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
    printf("\nNORMAL_VOLTAGE_STATE_ENTRY_Action\n");
#endif
} 

/**
 * @brief  vHVFunc function is to perform some action when the state changed to HIGH_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vHVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
    printf("\nHIGH_VOLTAGE_STATE_ENTRY_Action\n");
#endif
} 

/**
 * @brief  vInULVFunc function is to perform some action when the state remain in ULTRA_LOW_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void vInULVFunc(void)
{
	Status.indicators.low_battery_indicator = 1;
#if(BATMON_TEST_MACRO == 1)
    printf("\nUL_UL_voltage\n");
#endif
}

/**
 * @brief  vInLVFunc function is to perform some action when the state state remain in LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInLVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
    printf("\nLOW_LOW_voltage\n");
#endif
} 

/**
 * @brief  vInNVFunc function is to perform some action when the state remain in NORMAL_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInNVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
   printf("\nNORMAL_NORMAL_voltage\n");
#endif
} 

/**
 * @brief  vInHVFunc function is to perform some action when the state state remain in HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInHVFunc(void)
{
	Status.indicators.low_battery_indicator = 0;
#if(BATMON_TEST_MACRO == 1)
  printf("\nHIGH_HIGH_voltage\n");
#endif
} 




/**************************************************************************************************
 * End Of File
***************************************************************************************************/
