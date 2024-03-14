/** \addtogroup  VDIO-STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler.c
 *
 * @brief ECUPowerMode_StateManager Handler file performs the transition of IGN .
 * and perform transition check and transition action functions.
 *
 * File Short Name:IGN_SmHandler
 *
 * Author:T.Sivadhanalakshmi
 *
 * Create Date: 11/03/2024
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


/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "IGN_SmHandler.h"
#include "digital_debounce.h"
#include "digital_debounce_cfg.h"

#include "IGN_SmHandler_cfg.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**
 * Function Pointer Data Type
 */
typedef  void (*Ign_ptr_t)(void);

uint8_t IGNONTransCheck_func(void);
uint8_t IGNOFFTransCheck_func(void);

void IGNONEntryAction_func(void);
void IGNOFFEntryAction_func(void);
void in_IGNONstateAction_func(void);
void in_IGNOFFstateAction_func(void);


//uint16_t IGN_get_current_state(void);




/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
* @brief gl_IGNMode_SM_t is an constant array of structures, where each element of the array is of type transition_T.
*/
const transition_T gl_IGNMode_SM_t[] = 
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
    {IgnOFF_mode, IgnON_mode, IGNONTransCheck_func, IGNONEntryAction_func},\
    {IgnON_mode, IgnOFF_mode, IGNOFFTransCheck_func, IGNOFFEntryAction_func},\
    {IgnON_mode, IgnON_mode, NULL, in_IGNONstateAction_func },\
    {IgnOFF_mode, IgnOFF_mode, NULL, in_IGNOFFstateAction_func },\
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
 * @brief  IGNONTransCheck_func function is to check the entry condition for  IGN_ON
 *
 * @param[in] void type
 *
 * @return true if ACC is ON otherwise return false
 *
 */
uint8_t IGNONTransCheck_func(void)
{
    uint8_t fl_ret_val_bool = 0;
    uint8_t fl_IGN_Status_Check_u8 =0;
    fl_IGN_Status_Check_u8 = get_debounce_status();
    fl_IGN_Status_Check_u8 = (fl_IGN_Status_Check_u8>>2);
    uint8_t l_DBNC_Status_u8 = (fl_IGN_Status_Check_u8 & 0x01);/**Checking IGN Status*/
    if(l_DBNC_Status_u8==0)
    {
        fl_ret_val_bool = 1;   
    }
    return fl_ret_val_bool; 
}
/**
 * @brief  IGNOFFTransCheck_func function is to check the entry condition for  IGN_OFF
 *
 * @param[in] void type
 *
 * @return true if IGN is OFF otherwise return false
 *
 */
uint8_t IGNOFFTransCheck_func(void)
{
    uint8_t fl_ret_val_bool = 0;
    uint8_t fl_IGN_Status_Check_u8 =0;
    fl_IGN_Status_Check_u8 = get_debounce_status();
    fl_IGN_Status_Check_u8 = (fl_IGN_Status_Check_u8>>2);
    uint8_t l_DBNC_Status_u8 = (fl_IGN_Status_Check_u8 & 0x01);/**Checking IGN Status*/
    if(l_DBNC_Status_u8==1)
    {
        fl_ret_val_bool = 1;
    }
    return fl_ret_val_bool; 
}
/**
 * @brief  IGNONEntryAction_func function is to perform some action when the state changed to IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void IGNONEntryAction_func(void)
{
    uint8_t fl_IGNOff_ON_counter_u8 = 0;
    static const Ign_ptr_t IGNOff_To_ON_List[]=
    {
        IGNON_ACTION_FUNC\
        NULL       
    };

    while (IGNOff_To_ON_List[fl_IGNOff_ON_counter_u8] != NULL)
    {
        IGNOff_To_ON_List[fl_IGNOff_ON_counter_u8]();
        fl_IGNOff_ON_counter_u8++;
    }
}
/**
 * @brief  IGNOFFEntryAction_func function is to perform some action when the state changed to IGN_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void IGNOFFEntryAction_func(void)
{
    IGNOFF_func();
#if 1
//    printf("IGNOFFEntryAction_func \r\n");
    uint8_t fl_IGNON_Off_counter_u8 = 0;
    static const Ign_ptr_t IGNON_To_Off_List[]=
    {
        IGNOFF_ACTION_FUNC\
        NULL
    };

    while (IGNON_To_Off_List[fl_IGNON_Off_counter_u8] != NULL)
    {
        IGNON_To_Off_List[fl_IGNON_Off_counter_u8]();
        fl_IGNON_Off_counter_u8++;
    }
#endif  
} 
/**
 * @brief  in_IGNONstateAction_func function is to perform some action when the state remain in IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_IGNONstateAction_func(void)
{
    uint8_t fl_IGNONstate_counter_u8 = 0;
    static const Ign_ptr_t IGNONState_List[]=
    {
        IN_IGNON_ACTION_FUNC\
        NULL
    };

    while (IGNONState_List[fl_IGNONstate_counter_u8] != NULL)
    {
        IGNONState_List[fl_IGNONstate_counter_u8]();
        fl_IGNONstate_counter_u8++;
    }
} 
/**
 * @brief  in_IGNOFFstateAction_func function is to perform some action when the state remain in IGN_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void in_IGNOFFstateAction_func(void)
{
    uint8_t fl_IGNOffstate_counter_u8 = 0;
    static const Ign_ptr_t IGNOffState_List[]=
    {
        IN_IGNOFF_ACTION_FUNC\
        NULL
    };

    while (IGNOffState_List[fl_IGNOffstate_counter_u8] != NULL)
    {
        IGNOffState_List[fl_IGNOffstate_counter_u8]();
        fl_IGNOffstate_counter_u8++;
    }
}
/**
 * @brief  ign_get_current_state function is to get the current state of ecupoermode
 *
 * @param[in] void type
 *
 * @return current state of IGN
 *
 */
uint16_t IGN_get_current_state(void)
{
    return(SM_get_current_state(IGN_SM_INDEX));
}

   
 

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
