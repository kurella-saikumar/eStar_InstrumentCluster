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


uint8_t LVTransCheck_func(void);
uint8_t NVTransCheck_func(void);
uint8_t HVTransCheck_func(void);
uint8_t UHVTransCheck_func(void);

void HVEntryAction_func(void);
void NVEntryAction_func(void);
void LVEntryAction_func(void);
void UHVEntryAction_func(void);

void in_LVstateAction_func(void);
void in_NVstateAction_func(void);
void in_HVstateAction_func(void);
void in_UHVstateAction_func(void);




/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
* @brief gl_batteryMode_SM_t is an constant array of structures, where each element of the array is of type transition_T. 
*/
const transition_T gl_batteryMode_SM_t[] = 
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
    {NORMAL_VOLTAGE_STATE|HIGH_VOLTAGE_STATE|ULTRA_HIGH_VOLTAGE_STATE, LOW_VOLTAGE_STATE, LVTransCheck_func, LVEntryAction_func},\
    {LOW_VOLTAGE_STATE|HIGH_VOLTAGE_STATE|ULTRA_HIGH_VOLTAGE_STATE, NORMAL_VOLTAGE_STATE, NVTransCheck_func, NVEntryAction_func},\
    {LOW_VOLTAGE_STATE|NORMAL_VOLTAGE_STATE|ULTRA_HIGH_VOLTAGE_STATE, HIGH_VOLTAGE_STATE, HVTransCheck_func, HVEntryAction_func},\
    {LOW_VOLTAGE_STATE|NORMAL_VOLTAGE_STATE|HIGH_VOLTAGE_STATE, ULTRA_HIGH_VOLTAGE_STATE, UHVTransCheck_func, UHVEntryAction_func},\
    {LOW_VOLTAGE_STATE, LOW_VOLTAGE_STATE, NULL, in_LVstateAction_func },\
    {NORMAL_VOLTAGE_STATE, NORMAL_VOLTAGE_STATE, NULL, in_NVstateAction_func },\
    {HIGH_VOLTAGE_STATE, HIGH_VOLTAGE_STATE, NULL, in_HVstateAction_func },\
    {ULTRA_HIGH_VOLTAGE_STATE, ULTRA_HIGH_VOLTAGE_STATE, NULL, in_UHVstateAction_func },\
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
 * @brief  LVTransCheck_func function is to check the entry condition for LV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 1 otherwisee return false
 *
 */

uint8_t LVTransCheck_func(void)
{
   // printf("LVTransCheck_%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_ret_val_bool = 0;
    if( 1 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE))
    {
        fl_ret_val_bool = 1;     
    }
    return fl_ret_val_bool; 
}

/**
 * @brief  NVTransCheck_func function is to check the entry condition for NV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 2 otherwisee return false
 *
 */
uint8_t NVTransCheck_func(void)
{
    //printf_R5("NVTransCheck_func condition%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_ret_val_bool = 0;
    if( (2 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)))
    {
        fl_ret_val_bool = 1;      
    }
    return fl_ret_val_bool; 
}
/**
 * @brief  HVTransCheck_func function is to check the entry condition for HV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 3 otherwisee return false
 *
 */
uint8_t HVTransCheck_func(void)
{
    //printf_R5("HVTransCheck_func condition%d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_ret_val_bool = 0;
    if( (3 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)))
    {
        fl_ret_val_bool = 1;      
    }
    return fl_ret_val_bool; 
}
/**
 * @brief  UHVTransCheck_func function is to check the entry condition for UHV state
 *
 * @param[in] void type
 *
 * @return true if get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE)) is 0 otherwisee return false
 *
 */
uint8_t UHVTransCheck_func(void)
{
   // printf("UHVTransCheck_func %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_ret_val_bool = 0;
    if(0 == get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE))
    {
        fl_ret_val_bool = 1;
    }
    return fl_ret_val_bool;
}


/**
 * @brief  HVEntryAction_func function is to perform some action when the state changed to HIGH_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 */
void LVEntryAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_LV_entry_counter_u8 = 0;
    static const BatterVolage_ptr_t LV_EntryState_List[]=
    {
        LV_ACTION_FUNC\
        NULL
    };

    while (LV_EntryState_List[fl_LV_entry_counter_u8] != NULL)
    {
        LV_EntryState_List[fl_LV_entry_counter_u8]();
        fl_LV_entry_counter_u8++;
    }
    
} 
/**
 * @brief  NVEntryAction_func function is to perform some action when the state changed to NORMAL_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void NVEntryAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_NV_entry_counter_u8 = 0;
    static const BatterVolage_ptr_t NV_EntryState_List[]=
    {
        NV_ACTION_FUNC\
        NULL
    };

    while (NV_EntryState_List[fl_NV_entry_counter_u8] != NULL)
    {
        NV_EntryState_List[fl_NV_entry_counter_u8]();
        fl_NV_entry_counter_u8++;
    }
    
} 
/**
 * @brief  LVEntryAction_func function is to perform some action when the state changed to LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void HVEntryAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_HV_entry_counter_u8 = 0;
    static const BatterVolage_ptr_t HV_EntryState_List[]=
    {
        HV_ACTION_FUNC\
        NULL
    };

    while (HV_EntryState_List[fl_HV_entry_counter_u8] != NULL)
    {
        HV_EntryState_List[fl_HV_entry_counter_u8]();
        fl_HV_entry_counter_u8++;
    }
    
}
/**
 * @brief  UHVEntryAction_func function is to perform some action when the state changed to ULTRA_HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void UHVEntryAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_UHV_entry_counter_u8 = 0;
    static const BatterVolage_ptr_t UHV_EntryState_List[]=
    {
        UHV_ACTION_FUNC\
        NULL
    };

    while (UHV_EntryState_List[fl_UHV_entry_counter_u8] != NULL)
    {
        UHV_EntryState_List[fl_UHV_entry_counter_u8]();
        fl_UHV_entry_counter_u8++;
    }

}


/**
 * @brief  in_LVstateAction_func function is to perform some action when the state state remain in LOW_VOLTAGE_STATE 
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_LVstateAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_HVState_counter_u8 = 0;
    static const BatterVolage_ptr_t HVState_List[]=
    {
        IN_LV_ACTION_FUNC\
        NULL
    };

    while (HVState_List[fl_HVState_counter_u8] != NULL)
    {
        HVState_List[fl_HVState_counter_u8]();
        fl_HVState_counter_u8++;
    }
    
} 
/**
 * @brief  in_NVstateAction_func function is to perform some action when the state remain in NORMAL_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 */
void in_NVstateAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_NVState_counter_u8 = 0;
    static const BatterVolage_ptr_t NVState_List[]=
    {
        IN_NV_ACTION_FUNC\
        NULL
    };

    while (NVState_List[fl_NVState_counter_u8] != NULL)
    {
        NVState_List[fl_NVState_counter_u8]();
        fl_NVState_counter_u8++;
    }
    
} 
/**
 * @brief  in_HVstateAction_func function is to perform some action when the state state remain in HIGH_VOLTAGE_STATE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_HVstateAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_HVState_counter_u8 = 0;
    static const BatterVolage_ptr_t HVState_List[]=
    {
        IN_HV_ACTION_FUNC\
        NULL
    };

    while (HVState_List[fl_HVState_counter_u8] != NULL)
    {
        HVState_List[fl_HVState_counter_u8]();
        fl_HVState_counter_u8++;
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
void in_UHVstateAction_func(void)
{
	printf("STATE- %d\n",get_analog_debounce_state(AD_INDEX_BATTERY_VOLTAGE));
    uint8_t fl_UHVState_counter_u8 = 0;
    static const BatterVolage_ptr_t UHVState_List[]=
    {
        IN_UH_ACTION_FUNC\
        NULL
    };

    while (UHVState_List[fl_UHVState_counter_u8] != NULL)
    {
        UHVState_List[fl_UHVState_counter_u8]();
        fl_UHVState_counter_u8++;
    }

}



/**
 * @brief  batteryvoltage_get_current_state function is to get the current state of batteryvoltage
 *
 * @param[in] void type
 *
 * @return current state of battery voltage
 *
 */
states_SM batteryvoltage_get_current_state(void)
{
    return(SM_get_current_state(BATTERVOLTAGE_MODE_SM_INDEX));
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
