/** \addtogroup ANALOG_INPUT_DEBOUNCER_CONFIGURATION
 *  @{
 * @file adcm_cfg.h
 *
 * @brief Application specific configuration file
 *
 * File Short Name: adcm_cfg
 *
 * @author:Sandhya
 *
 * @date: 14-12-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/

#ifndef _ANALOG_DEBOUNCE_CFG_H    /* Guard against multiple inclusion */
#define _ANALOG_DEBOUNCE_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "Analog_debounce_cfg.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**
* Macro to define the MAXIMUM_NUMBER_OF_STATES for each input
*/
#define MAXIMUM_NUMBER_OF_STATES 4

//extern uint16_t *l_adc_value_ptr;
extern uint32_t gl_BAT_MON_u32;

/*If ADCFG_STRICT_RANGE is enabled (!= 0), the out-of-range values shall be ignored and current state would not be updated for such input values received...
If ADCFG_STRICT_RANGE is disabled (== 0), the out-of-range values would result in either a ramp-up to the Last state or ramp-down to the First state depending on the input value received*/
#define ADCFG_STRICT_RANGE 0

#define INPUT_DATA_POINTERS \
    &gl_BAT_MON_u32, /** Pointer to 32-bit value of the Input 0*/   \


#define DEFAULT_STATE_CONFIGURATION \
    0,/** Default State for Input 0 is State_0*/ \


#define AD_INDEX_BATTERY_VOLTAGE 0


/**
 * Define an array of threshold values for each of the input. Please note that
 * all inputs should have same number of States. Define the thresholds for each State
 * as below. Note: The base counter for the DEBOUNCE_COUNTER is the periodicity at which
 * the "analog_debounce_task" is called by the application
 * {"RAMP_UP_ENTRY_THRESHOLD, RAMP_DOWN_ENTRY_THRESHOLD, RAMP_UP_DEBOUNCE_COUNTER, RAMP_DOWN_DEBOUNCE_COUNTER"}
 *
 * For a stable operation, configure the thresholds in such a way that 
 * the RAMP_UP_ENTRY_THRESHOLD of a state is ALWAYS ABOVE the RAMP_DOWN_ENTRY_THRESHOLD of its previous state.
 * Otherwise, for input values falling between the two thresholds, there will be constant jump between the two states
*/

/**VBATT STATE INDEX For Application To USE*/
#define VBATT_LELVEL_0	0
#define VBATT_LELVEL_1	1
#define VBATT_LELVEL_2	2
#define VBATT_LELVEL_3	3

#define INPUT_1_THRESHOLDS {\
	/*Thresholds For State 0 VBATT_LELVEL_0*/{0/*RAMP_UP_ENTRY_THRESHOLD*/, 1700/*RAMP_DOWN_ENTRY_THRESHOLD*/, 10/*RAMP_UP_DEBOUNCE_COUNTER*/, 10/*RAMP_DOWN_DEBOUNCE_COUNTER*/}, \
	/*Thresholds For State 1 VBATT_LELVEL_1*/{1800, 2200, 10, 10}, \
	/*Thresholds For State 2 VBATT_LELVEL_2*/{2300, 3400, 10, 10}, \
    /*Thresholds For State 3 VBATT_LELVEL_3*/{3500, 4096, 10, 10}

/**
* Macro to define the ANALOG_DEBOUNCE_CONFIGURATION to hold the input threshold values for each input
*/
#define ANALOG_DEBOUNCE_CONFIGURATION \
	{INPUT_1_THRESHOLDS} \



/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
#endif	/* ANALOG_DEBOUNCE_CFG_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

