/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file batterVoltage_SmHandler.c
 *
 * @brief BatteryVoltage_StateManager Handler file performs the transition of different states of battery voltage.
 * and perform transition check and transition action functions.
 * 
 * File Short Name:batterVoltage_SmHandler
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
#include "batterVoltage_SmHandler_cfg.h"
#include "batterVoltage_SmHandler.h"
#include "Analog_debounce.h"
#include "Analog_debounce_cfg.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**
 * Function Pointer Data Type
 */
typedef  void (*BatterVolage_ptr_t)(void);

uint8_t ucULVTransCheckFunc(void);
uint8_t ucLVTransCheckFunc(void);
uint8_t ucNVTransCheckFunc(void);
uint8_t ucHVTransCheckFunc(void);


void vHVEntryActionFunc(void);
void vNVEntryActionFunc(void);
void vLVEntryActionFunc(void);
void vULVEntryActionFunc(void);

void vInULVstateActionFunc(void);
void vInLVstateActionFunc(void);
void vInNVstateActionFunc(void);
void vInHVstateActionFunc(void);





/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
* @brief gl_batteryMode_SM_t is an constant array of structures, where each element of the array is of type transition_T. 
*/
const transition_T gl_batteryMode_SM_t[] = 
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
	{LOW_VOLTAGE_STATE|NORMAL_VOLTAGE_STATE|HIGH_VOLTAGE_STATE, ULTRA_LOW_VOLTAGE_STATE, ucULVTransCheckFunc, vULVEntryActionFunc},\
    {ULTRA_LOW_VOLTAGE_STATE|NORMAL_VOLTAGE_STATE|HIGH_VOLTAGE_STATE, LOW_VOLTAGE_STATE, ucLVTransCheckFunc, vLVEntryActionFunc},\
    {ULTRA_LOW_VOLTAGE_STATE|LOW_VOLTAGE_STATE|HIGH_VOLTAGE_STATE, NORMAL_VOLTAGE_STATE, ucNVTransCheckFunc, vNVEntryActionFunc},\
    {ULTRA_LOW_VOLTAGE_STATE|LOW_VOLTAGE_STATE|NORMAL_VOLTAGE_STATE, HIGH_VOLTAGE_STATE, ucHVTransCheckFunc, vHVEntryActionFunc},\
    {LOW_VOLTAGE_STATE, LOW_VOLTAGE_STATE, NULL, vInLVstateActionFunc },\
    {NORMAL_VOLTAGE_STATE, NORMAL_VOLTAGE_STATE, NULL, vInNVstateActionFunc },\
    {HIGH_VOLTAGE_STATE, HIGH_VOLTAGE_STATE, NULL, vInHVstateActionFunc },\
    {ULTRA_LOW_VOLTAGE_STATE, ULTRA_LOW_VOLTAGE_STATE, NULL, vInULVstateActionFunc },\
    {SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL }
};

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
 * @brief  ucLVTransCheckFunc function is to check the entry condition for LV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 1 otherwisee return false
 *
 */

uint8_t ucLVTransCheckFunc(void)
{
   // printf("LVTransCheck_%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucRetVal = 0;
    if( 1 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE))
    {
        ucRetVal = 1;     
    }
    return ucRetVal; 
}

/**
 * @brief  ucNVTransCheckFunc function is to check the entry condition for NV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 2 otherwisee return false
 *
 */
uint8_t ucNVTransCheckFunc(void)
{
    //printf_R5("ucNVTransCheckFunc condition%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucRetVal = 0;
    if( (2 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)))
    {
        ucRetVal = 1;      
    }
    return ucRetVal; 
}
/**
 * @brief  ucHVTransCheckFunc function is to check the entry condition for HV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 3 otherwisee return false
 *
 */
uint8_t ucHVTransCheckFunc(void)
{
    //printf_R5("ucHVTransCheckFunc condition%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucRetVal = 0;
    if( (3 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)))
    {
        ucRetVal = 1;      
    }
    return ucRetVal; 
}
/**
 * @brief  UHVTransCheck_func function is to check the entry condition for UHV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 0 otherwisee return false
 *
 */
uint8_t ucULVTransCheckFunc(void)
{
   // printf("UHVTransCheck_func %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucRetVal = 0;
    if(0 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE))
    {
        ucRetVal = 1;
    }
    return ucRetVal;
}


/**
 * @brief  vHVEntryActionFunc function is to perform some action when the state changed to HIGH_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 */
void vLVEntryActionFunc(void)
{
#if(BATMON_TEST_MACRO == 1)
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
#endif
    uint8_t ucLVEntryCounter = 0;
    static const BatterVolage_ptr_t LV_EntryState_List[]=
    {
        LV_ACTION_FUNC\
        NULL
    };

    while (LV_EntryState_List[ucLVEntryCounter] != NULL)
    {
        LV_EntryState_List[ucLVEntryCounter]();
        ucLVEntryCounter++;
    }
    
} 
/**
 * @brief  vNVEntryActionFunc function is to perform some action when the state changed to NORMAL_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vNVEntryActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucNVEntryCounter = 0;
    static const BatterVolage_ptr_t NV_EntryState_List[]=
    {
        NV_ACTION_FUNC\
        NULL
    };

    while (NV_EntryState_List[ucNVEntryCounter] != NULL)
    {
        NV_EntryState_List[ucNVEntryCounter]();
        ucNVEntryCounter++;
    }
    
} 
/**
 * @brief  vLVEntryActionFunc function is to perform some action when the state changed to LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vHVEntryActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucHVEntryCounter = 0;
    static const BatterVolage_ptr_t HV_EntryState_List[]=
    {
        HV_ACTION_FUNC\
        NULL
    };

    while (HV_EntryState_List[ucHVEntryCounter] != NULL)
    {
        HV_EntryState_List[ucHVEntryCounter]();
        ucHVEntryCounter++;
    }
    
}
/**
 * @brief  UHVEntryAction_func function is to perform some action when the state changed to ULTRA_LOW_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vULVEntryActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucULVEntryCounter = 0;
    static const BatterVolage_ptr_t ULV_EntryState_List[]=
    {
        ULV_ACTION_FUNC\
        NULL
    };

    while (ULV_EntryState_List[ucULVEntryCounter] != NULL)
    {
        ULV_EntryState_List[ucULVEntryCounter]();
        ucULVEntryCounter++;
    }

}


/**
 * @brief  vInLVstateActionFunc function is to perform some action when the state state remain in LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInLVstateActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucLVStateCounter = 0;
    static const BatterVolage_ptr_t HVState_List[]=
    {
        IN_LV_ACTION_FUNC\
        NULL
    };

    while (HVState_List[ucLVStateCounter] != NULL)
    {
        HVState_List[ucLVStateCounter]();
        ucLVStateCounter++;
    }
    
} 
/**
 * @brief  vInNVstateActionFunc function is to perform some action when the state remain in NORMAL_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 */
void vInNVstateActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucNVStateCounter = 0;
    static const BatterVolage_ptr_t NVState_List[]=
    {
        IN_NV_ACTION_FUNC\
        NULL
    };

    while (NVState_List[ucNVStateCounter] != NULL)
    {
        NVState_List[ucNVStateCounter]();
        ucNVStateCounter++;
    }
    
} 
/**
 * @brief  vInHVstateActionFunc function is to perform some action when the state state remain in HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInHVstateActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucHVStateCounter = 0;
    static const BatterVolage_ptr_t HVState_List[]=
    {
        IN_HV_ACTION_FUNC\
        NULL
    };

    while (HVState_List[ucHVStateCounter] != NULL)
    {
        HVState_List[ucHVStateCounter]();
        ucHVStateCounter++;
    }
   
} 

/**
 * @brief  in_UHVstateAction_func function is to perform some action when the state remain in ULTRA_LOW_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInULVstateActionFunc(void)
{
	//printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t ucULVStateCounter = 0;
    static const BatterVolage_ptr_t ULVState_List[]=
    {
        IN_UL_ACTION_FUNC\
        NULL
    };

    while (ULVState_List[ucULVStateCounter] != NULL)
    {
        ULVState_List[ucULVStateCounter]();
        ucULVStateCounter++;
    }

}



/**
 * @brief  xbatteryvoltage_get_current_state function is to get the current state of batteryvoltage
 *
 * @param[in] void type
 *
 * @return current state of battery voltage
 *
 */
states_SM xbatteryvoltage_get_current_state(void)
{
    return(SM_get_current_state(configBATTERVOLTAGE_MODE_SM_INDEX));
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
