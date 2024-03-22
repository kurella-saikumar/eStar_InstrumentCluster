/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file batterVoltage_SmHandler.c
 *
 * @brief Template Source File
 *
 * File Short Name:
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
 #include "stdint.h"
 #include "stdbool.h"
#include "stdio.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "ECUPwrMode_SmHandler_cfg.h"
#include "IGN_SmHandler.h"
#include "smHandler.h"


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
/**
 * Function Pointer Data Type
 */
typedef  void (*pwrmode_ptr_t)(void);

/**
 * Data Type holding a pointer to the init function
 */
typedef struct pwrmodeStruct {
    pwrmode_ptr_t  pwrmodePtr;     /**<This is a pointer to the task handler*/
} pwrmodeStruct_t;

uint8_t ECUPwrModeSleep_To_Off_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_Off_TransCheck_func(void);
uint8_t ECUPwrModeOff_To_Sleep_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_Sleep_TransCheck_func(void);
uint8_t ECUPwrModeSleep_To_Active_TransCheck_func(void);
uint8_t ECUPwrModeOff_To_Active_TransCheck_func(void);


void ECUPwrModeSleep_To_Off_EntryAction_func(void);
void ECUPwrModeActive_To_Off_EntryAction_func(void);
void ECUPwrModeOff_To_Sleep_EntryAction_func(void);
void ECUPwrModeActive_To_Sleep_EntryAction_func(void);
void ECUPwrModeSleep_To_Active_EntryAction_func(void);
void ECUPwrModeOff_Action_func(void);
void ECUPwrModeSleep_Action_func(void);
void ECUPwrModeActive_Action_func(void);
void ECUPwrModeOff_To_Active_EntryAction_func(void);

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

const transition_T gl_ECUPwrMode_SM_t[] =
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
	{ECU_POWER_MODE_OFF, ECU_POWER_MODE_ACTIVE, ECUPwrModeOff_To_Active_TransCheck_func, ECUPwrModeOff_To_Active_EntryAction_func},\
	{ECU_POWER_MODE_OFF, ECU_POWER_MODE_SLEEP, ECUPwrModeOff_To_Sleep_TransCheck_func, ECUPwrModeOff_To_Sleep_EntryAction_func},\
	{ECU_POWER_MODE_SLEEP, ECU_POWER_MODE_OFF, ECUPwrModeSleep_To_Off_TransCheck_func, ECUPwrModeSleep_To_Off_EntryAction_func},\
	{ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_OFF, ECUPwrModeActive_To_Off_TransCheck_func, ECUPwrModeActive_To_Off_EntryAction_func},\
	{ECU_POWER_MODE_OFF, ECU_POWER_MODE_OFF, NULL, ECUPwrModeOff_Action_func },\
	{ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_ACTIVE, NULL, ECUPwrModeActive_Action_func },\
	{ECU_POWER_MODE_SLEEP, ECU_POWER_MODE_SLEEP, NULL, ECUPwrModeSleep_Action_func },\
	{SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL }


	/*
	{ECU_POWER_MODE_OFF, ECU_POWER_MODE_SLEEP, ECUPwrModeOff_To_Sleep_TransCheck_func, ECUPwrModeOff_To_Sleep_EntryAction_func},\
	{ECU_POWER_MODE_OFF, ECU_POWER_MODE_ACTIVE, ECUPwrModeOff_To_Active_TransCheck_func, ECUPwrModeOff_To_Active_EntryAction_func},\
    {ECU_POWER_MODE_OFF, ECU_POWER_MODE_OFF, NULL, ECUPwrModeOff_Action_func },\
	{ECU_POWER_MODE_SLEEP, ECU_POWER_MODE_OFF, ECUPwrModeSleep_To_Off_TransCheck_func, ECUPwrModeSleep_To_Off_EntryAction_func},\
	{ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_OFF, ECUPwrModeActive_To_Off_TransCheck_func, ECUPwrModeActive_To_Off_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_ACTIVE, NULL, ECUPwrModeActive_Action_func },\
	{ECU_POWER_MODE_SLEEP, ECU_POWER_MODE_SLEEP, NULL, ECUPwrModeSleep_Action_func },\
    {SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL }
    */

};

/**
 * Purpose: Variable To Hold the current state of A53 ecupowermode.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 bit
 *
 * Range:ECU_POWER_MODE_OFF,ECU_POWER_MODE_ACTIVE
 *
 * Power On Init Value\Action: Initialized to the default input state
 *
 * Wakeup Value\Action: Initialized to the next state of R5 ecupowermode
 *
 * Shutdown Value\Action: Don't Care
 *
 */
states_SM l_current_ecuPwrMode_SM = PM_MANAGER_DEFAULT_STATE;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/


/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
states_SM pm_GetSyncStatus(void);

states_SM pm_GetSyncStatus(void)
{
	return l_current_ecuPwrMode_SM;
}

void pm_ReqNewState(states_SM p_requested_status_sm)
{/** @startuml */ /** start */

	if(p_requested_status_sm == ECU_POWER_MODE_SLEEP)
	{
		/**:return true;*/
		l_current_ecuPwrMode_SM= ECU_POWER_MODE_SLEEP;
	}
	else if(p_requested_status_sm == ECU_POWER_MODE_ACTIVE)
	{
		l_current_ecuPwrMode_SM= ECU_POWER_MODE_ACTIVE;
	}
	else if(p_requested_status_sm == ECU_POWER_MODE_OFF)
	{
		l_current_ecuPwrMode_SM= ECU_POWER_MODE_OFF;
	}
	else
	{

	}

}/** end*/ /** @enduml */

/**
 * @brief  ECUPwrModeSleep_To_Off_TransCheck_func function is to check the entry condition for sleep to off state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeSleep_To_Off_TransCheck_func(void)
{
    uint8_t fl_allow_sleep_off_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into OFF state if Sleep Timer elapsed and IGN is OFF;*/
    /**if (IGN_STATUS) then (OFF)*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
    states_SM pmReq_Status_Check = pm_GetSyncStatus();

    if((IGN_STATUS==IgnOFF_mode) && (pmReq_Status_Check == ECU_POWER_MODE_OFF ))
    {
         fl_allow_sleep_off_state_u8 = ALLOW_TRANSITION; /*1*/
    }

    return (fl_allow_sleep_off_state_u8);
}
/**
 * @brief  ECUPwrModeActive_To_Off_TransCheck_func function is to check the entry condition for Active to off state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeActive_To_Off_TransCheck_func(void)
{
    uint8_t fl_allow_active_off_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into OFF state if IGN is OFF;*/
    /**if (IGN_STATUS) then (OFF)*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
    states_SM pmReq_Status_Check = pm_GetSyncStatus();

    if((IGN_STATUS==IgnOFF_mode) && (pmReq_Status_Check == ECU_POWER_MODE_ACTIVE))
    {
        //printf("powermodeActive_to_off\n");
         fl_allow_active_off_state_u8 = ALLOW_TRANSITION; /*1*/
    }
    /**:Also, A53 and A7 cores should have already been in OFF State;*/

    return (fl_allow_active_off_state_u8);

}
/**
 * @brief  ECUPwrModeOff_To_Sleep_TransCheck_func function is to check the entry condition for off to sleep state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeOff_To_Sleep_TransCheck_func(void)
{
    uint8_t fl_allow_off_sleep_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into Sleep state if HW_Acc is ON;*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
    states_SM pmReq_Status_Check = pm_GetSyncStatus();
   // printf("usIgnitionGetCurrentState:%d",IGN_STATUS);
    if((IGN_STATUS==IgnOFF_mode) && (pmReq_Status_Check == ECU_POWER_MODE_SLEEP))
    {
       fl_allow_off_sleep_state_u8 = ALLOW_TRANSITION; /*1*/
    }

    return (fl_allow_off_sleep_state_u8);

}

/**
 * @brief  ECUPwrModeActive_To_Sleep_TransCheck_func function is to check the entry condition for Active to sleep state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeActive_To_Sleep_TransCheck_func(void)
{
    uint8_t fl_allow_active_sleep_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into Sleep state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
    states_SM pmReq_Status_Check = pm_GetSyncStatus();

    if(IGN_STATUS==IgnON_mode || pmReq_Status_Check == ECU_POWER_MODE_SLEEP)
    {
         fl_allow_active_sleep_state_u8 = ALLOW_TRANSITION; /*1*/
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_SLEEP State;*/

    return (fl_allow_active_sleep_state_u8);

}

/**
 * @brief  ECUPwrModeSleep_To_Active_TransCheck_func function is to check the entry condition for Standby to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeSleep_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_sleep_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into Sleep state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
    states_SM pmReq_Status_Check = pm_GetSyncStatus();
    if(IGN_STATUS==IgnOFF_mode || pmReq_Status_Check == ECU_POWER_MODE_ACTIVE )
    {
        fl_allow_sleep_active_state_u8 = ALLOW_TRANSITION; /*1*/
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_ACTIVE State;*/

    return (fl_allow_sleep_active_state_u8);

}

/**
 * @brief  ECUPwrModeOff_To_Active_TransCheck_func function is to check the entry condition for off to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeOff_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_off_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    /**:Enter into Sleep state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = usIgnitionGetCurrentState();
   // states_SM pmReq_Status_Check = pm_GetSyncStatus();
    if(IGN_STATUS==IgnON_mode)// && (pmReq_Status_Check == ECU_POWER_MODE_ACTIVE ))
    {
        //printf("powermodeoff_to_Active_state\n");
            fl_allow_off_active_state_u8 = ALLOW_TRANSITION; /*1*/
    }

    return (fl_allow_off_active_state_u8);

}

/**
 * @brief  ECUPwrModeSleep_To_Off_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_SLEEP to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void ECUPwrModeSleep_To_Off_EntryAction_func(void)
{
    uint8_t fl_sleep_off_counter_u8 = 0;
    static const pwrmode_ptr_t Sleep_To_Off_List[]=
    {
        ECUPWRMODESLEEP_TO_OFF_LIST \
        NULL, \
    };

    while (Sleep_To_Off_List[fl_sleep_off_counter_u8] != NULL)
    {
        Sleep_To_Off_List[fl_sleep_off_counter_u8]();
        fl_sleep_off_counter_u8++;
    }

}
/**
 * @brief  ECUPwrModeActive_To_Off_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Off_EntryAction_func(void)
{
    uint8_t fl_active_off_counter_u8 = 0;
    static const pwrmode_ptr_t Active_To_Off_List[]=
    {
        ECUPWRMODEACTIVE_TO_OFF_LIST \
        NULL, \
    };

    while (Active_To_Off_List[fl_active_off_counter_u8] != NULL)
    {
        Active_To_Off_List[fl_active_off_counter_u8]();
        fl_active_off_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeOff_To_Sleep_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_OFF to ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_To_Sleep_EntryAction_func(void)
{
    uint8_t fl_off_sleep_counter_u8 = 0;
    static const pwrmode_ptr_t Off_To_sleep_List[]=
    {
        ECUPWRMODEOFF_TO_SLEEP_LIST \
        NULL, \
    };

    while (Off_To_sleep_List[fl_off_sleep_counter_u8]!= NULL)
    {
        Off_To_sleep_List[fl_off_sleep_counter_u8]();
        fl_off_sleep_counter_u8++;
    }
}

/**
 * @brief  ECUPwrModeActive_To_Sleep_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Sleep_EntryAction_func(void)
{
    uint8_t fl_active_sleep_counter_u8 = 0;
    static const pwrmode_ptr_t Active_sleep_List[]=
    {
        ECUPWRMODEACTIVE_TO_SLEEP_LIST \
        NULL, \
    };

    while (Active_sleep_List[fl_active_sleep_counter_u8] != NULL)
    {
        Active_sleep_List[fl_active_sleep_counter_u8]();
        fl_active_sleep_counter_u8++;
    }
}

/**
 * @brief  ECUPwrModeSleep_To_Active_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_SLEEP to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeSleep_To_Active_EntryAction_func(void)
{
    uint8_t fl_sleep_active_counter_u8 = 0;
    static const pwrmode_ptr_t Sleep_To_active_List[]=
    {
        ECUPWRMODESLEEP_TO_ACTIVE_LIST \
        NULL, \
    };

    while (Sleep_To_active_List[fl_sleep_active_counter_u8] != NULL)
    {
        Sleep_To_active_List[fl_sleep_active_counter_u8]();
        fl_sleep_active_counter_u8++;
    }
}


/**
 * @brief  ECUPwrModeOff_To_Active_EntryAction_func function is to perform some action when the state  change from ECU_POWER_MODE_OFF to Active
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_To_Active_EntryAction_func(void)
{
       uint8_t fl_off_active_counter_u8 = 0;
    static const pwrmode_ptr_t Off_Active_List[]=
    {
        ECUPWRMODEOFF_To_ACTIVE_LIST \
        NULL, \
    };

    while (Off_Active_List[fl_off_active_counter_u8] != NULL)
    {
        Off_Active_List[fl_off_active_counter_u8]();
        fl_off_active_counter_u8++;
    }
}


/**
 * @brief  ECUPwrModeOff_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_Action_func(void)
{

    uint8_t fl_off_counter_u8 = 0;
    static const pwrmode_ptr_t Off_List[]=
    {
        ECUPWRMODEOFF_LIST \
        NULL, \
    };

    while (Off_List[fl_off_counter_u8]!= NULL)
    {
        Off_List[fl_off_counter_u8]();
        fl_off_counter_u8++;
    }

}
/**
 * @brief  ECUPwrModeSleep_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_SLEEP
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeSleep_Action_func(void)
{
    uint8_t fl_sleep_counter_u8 = 0;
    static const pwrmode_ptr_t Sleep_List[]=
    {
        ECUPWRMODESLEEP_LIST \
        NULL, \
    };

    while (Sleep_List[fl_sleep_counter_u8] != NULL)
    {
        Sleep_List[fl_sleep_counter_u8]();
        fl_sleep_counter_u8++;
    }
}

/**
 * @brief  ECUPwrModeActive_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_Action_func(void)
{
       uint8_t fl_active_counter_u8 = 0;
    static const pwrmode_ptr_t Active_List[]=
    {
        ECUPWRMODEACTIVE_LIST \
        NULL, \
    };

    while (Active_List[fl_active_counter_u8] != NULL)
    {
        Active_List[fl_active_counter_u8]();
        fl_active_counter_u8++;
    }
}

/**
 * @brief  ecupwrmode_get_current_state function is to get the current state of ecupoermode
 *
 * @param[in] void type
 *
 * @return current state of ecupoermode
 *
 */
states_SM ecupwrmode_get_current_state(void)
{
    return(SM_get_current_state(ECUPWR_MODE_SM_INDEX));
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
