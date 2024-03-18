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

uint8_t ucIGNONTransCheckFunc(void);
uint8_t ucIGNOFFTransCheckFunc(void);

void vIgnitionOnEntryActionFunc(void);
void vIgnitionOffEntryActionFunc(void);
void vInIgnitionOnStateActionFunc(void);
void vInIgnitionOffStateActionFunc(void);


//uint16_t IGN_get_current_state(void);




/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
* @brief gl_IGNMode_SM_t is an constant array of structures, where each element of the array is of type transition_T.
*/
const transition_T gl_IGNMode_SM_t[] = 
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
    {IgnOFF_mode, IgnON_mode, ucIGNONTransCheckFunc, vIgnitionOnEntryActionFunc},\
    {IgnON_mode, IgnOFF_mode, ucIGNOFFTransCheckFunc, vIgnitionOffEntryActionFunc},\
    {IgnON_mode, IgnON_mode, NULL, vInIgnitionOnStateActionFunc },\
    {IgnOFF_mode, IgnOFF_mode, NULL, vInIgnitionOffStateActionFunc },\
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
uint8_t ucIGNONTransCheckFunc(void)
{
    uint8_t ucReturnValueBool = 0;
    uint8_t ucIGNStatusCheck =0;
    ucIGNStatusCheck = get_debounce_status();
    ucIGNStatusCheck = (ucIGNStatusCheck>>2);
    uint8_t ucDebounceStatus = (ucIGNStatusCheck & 0x01);/**Checking IGN Status*/
    if(ucDebounceStatus==0)
    {
    	ucReturnValueBool = 1;
    }
    return ucReturnValueBool;
}
/**
 * @brief  IGNOFFTransCheck_func function is to check the entry condition for  IGN_OFF
 *
 * @param[in] void type
 *
 * @return true if IGN is OFF otherwise return false
 *
 */
uint8_t ucIGNOFFTransCheckFunc(void)
{
    uint8_t ucReturnValueBool = 0;
    uint8_t ucIGNStatusCheck =0;
    ucIGNStatusCheck = get_debounce_status();
    ucIGNStatusCheck = (ucIGNStatusCheck>>2);
    uint8_t ucDebounceStatus = (ucIGNStatusCheck & 0x01);/**Checking IGN Status*/
    if(ucDebounceStatus==1)
    {
    	ucReturnValueBool = 1;
    }
    return ucReturnValueBool;
}
/**
 * @brief  IGNONEntryAction_func function is to perform some action when the state changed to IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vIgnitionOnEntryActionFunc(void)
{
    uint8_t ucIgnitionOffToOnCounter = 0;
    static const Ign_ptr_t IgnitionOffToOnList[]=
    {
        IGNON_ACTION_FUNC\
        NULL       
    };

    while (IgnitionOffToOnList[ucIgnitionOffToOnCounter] != NULL)
    {
    	IgnitionOffToOnList[ucIgnitionOffToOnCounter]();
    	ucIgnitionOffToOnCounter++;
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
void vIgnitionOffEntryActionFunc(void)
{
    uint8_t ucIgnitionOnToOffCounter = 0;
    static const Ign_ptr_t IgnitionOnToOffList[]=
    {
        IGNOFF_ACTION_FUNC\
        NULL
    };

    while (IgnitionOnToOffList[ucIgnitionOnToOffCounter] != NULL)
    {
    	IgnitionOnToOffList[ucIgnitionOnToOffCounter]();
        ucIgnitionOnToOffCounter++;
    }
} 
/**
 * @brief  in_IGNONstateAction_func function is to perform some action when the state remain in IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInIgnitionOnStateActionFunc(void)
{
    uint8_t ucIgnitionOnStateCounter = 0;
    static const Ign_ptr_t IgnitionOnStateList[]=
    {
        IN_IGNON_ACTION_FUNC\
        NULL
    };

    while (IgnitionOnStateList[ucIgnitionOnStateCounter] != NULL)
    {
    	IgnitionOnStateList[ucIgnitionOnStateCounter]();
        ucIgnitionOnStateCounter++;
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

void vInIgnitionOffStateActionFunc(void)
{
    uint8_t uc_IGNOffstate_counter_u8 = 0;
    static const Ign_ptr_t IGNOffState_List[]=
    {
        IN_IGNOFF_ACTION_FUNC\
        NULL
    };

    while (IGNOffState_List[uc_IGNOffstate_counter_u8] != NULL)
    {
        IGNOffState_List[uc_IGNOffstate_counter_u8]();
        uc_IGNOffstate_counter_u8++;
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
uint16_t usIgnitionGetCurrentState(void)
{
    return((uint16_t)SM_get_current_state(IGN_SM_INDEX));

}

   
 

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
