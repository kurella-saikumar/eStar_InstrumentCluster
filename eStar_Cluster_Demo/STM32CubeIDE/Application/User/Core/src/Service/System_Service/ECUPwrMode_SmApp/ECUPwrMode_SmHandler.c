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

uint8_t ECUPwrModeStandBy_To_Off_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_Off_TransCheck_func(void);
uint8_t ECUPwrModeOff_To_StandBy_TransCheck_func(void);
uint8_t ECUPwrModeStatic_To_StandBy_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_StandBy_TransCheck_func(void);
uint8_t ECUPwrModeStandBy_To_Static_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_Static_TransCheck_func(void);
uint8_t ECUPwrModeStandBy_To_Crank_TransCheck_func(void);
uint8_t ECUPwrModeStatic_To_Crank_TransCheck_func(void);
uint8_t ECUPwrModeActive_To_Crank_TransCheck_func(void);
uint8_t ECUPwrModeStandBy_To_Active_TransCheck_func(void);
uint8_t ECUPwrModeStatic_To_Active_TransCheck_func(void);
uint8_t ECUPwrModeCrank_To_Active_TransCheck_func(void);
uint8_t ECUPwrModeOff_To_Active_TransCheck_func(void);
uint8_t ECUPwrModeInitial_To_Off_TransCheck_func(void);


void ECUPwrModeStandBy_To_Off_EntryAction_func(void);
void PwrModeActive_To_Off_EntryAction_func(void);
void ECUPwrModeOff_To_StandBy_EntryAction_func(void);
void ECUPwrModeStatic_To_StandBy_EntryAction_func(void);
void ECUPwrModeActive_To_StandBy_EntryAction_func(void);
void ECUPwrModeStandBy_To_Static_EntryAction_func(void);
void ECUPwrModeActive_To_Static_EntryAction_func(void);
void ECUPwrModeStandBy_To_Crank_EntryAction_func(void);
void ECUPwrModeStatic_To_Crank_EntryAction_func(void);
void ECUPwrModeActive_To_Crank_EntryAction_func(void);
void ECUPwrModeStandBy_To_Active_EntryAction_func(void);
void ECUPwrModeStatic_To_Active_EntryAction_func(void);
void ECUPwrModeCrank_To_Active_EntryAction_func(void);
void ECUPwrModeOff_Action_func(void);
void ECUPwrModeStandBy_Action_func(void);
void ECUPwrModeStatic_Action_func(void);
void ECUPwrModeCrank_Action_func(void);
void ECUPwrModeActive_Action_func(void);
void ECUPwrModeOff_To_Active_EntryAction_func(void);
void ECUPwrModeInitial_To_Off_EntryAction_func(void);
void ECUPwrModeInitial_Action_func(void);

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

const transition_T gl_ECUPwrMode_SM_t[] =
{/*Current State, Next State, CurrentState to NextStateTransitionCheckFunction, NextStateTransitionActionFunction*/
    {ECU_POWER_MODE_INITIAL, ECU_POWER_MODE_OFF, ECUPwrModeInitial_To_Off_TransCheck_func, ECUPwrModeInitial_To_Off_EntryAction_func},\
    {ECU_POWER_MODE_INITIAL, ECU_POWER_MODE_INITIAL, NULL, ECUPwrModeInitial_Action_func },\
    {ECU_POWER_MODE_OFF, ECU_POWER_MODE_ACTIVE, ECUPwrModeOff_To_Active_TransCheck_func, ECUPwrModeOff_To_Active_EntryAction_func},\
    {ECU_POWER_MODE_OFF, ECU_POWER_MODE_OFF, NULL, ECUPwrModeOff_Action_func },\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_OFF, ECUPwrModeActive_To_Off_TransCheck_func, PwrModeActive_To_Off_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_ACTIVE, NULL, ECUPwrModeActive_Action_func },\
    {SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL }

/*    {ECU_POWER_MODE_OFF, ECU_POWER_MODE_STANDBY, ECUPwrModeOff_To_StandBy_TransCheck_func, ECUPwrModeOff_To_StandBy_EntryAction_func},\
    {ECU_POWER_MODE_OFF, ECU_POWER_MODE_OFF, NULL, ECUPwrModeOff_Action_func },\
    {ECU_POWER_MODE_STANDBY, ECU_POWER_MODE_OFF, ECUPwrModeStandBy_To_Off_TransCheck_func, ECUPwrModeStandBy_To_Off_EntryAction_func},\
    {ECU_POWER_MODE_STANDBY, ECU_POWER_MODE_STATIC, ECUPwrModeStandBy_To_Static_TransCheck_func,  ECUPwrModeStandBy_To_Static_EntryAction_func},\
    {ECU_POWER_MODE_STANDBY, ECU_POWER_MODE_CRANK, ECUPwrModeStandBy_To_Crank_TransCheck_func, ECUPwrModeStandBy_To_Crank_EntryAction_func},\
    {ECU_POWER_MODE_STANDBY, ECU_POWER_MODE_ACTIVE, ECUPwrModeStandBy_To_Active_TransCheck_func, ECUPwrModeStandBy_To_Active_EntryAction_func},\
    {ECU_POWER_MODE_STANDBY, ECU_POWER_MODE_STANDBY, NULL, ECUPwrModeStandBy_Action_func },\
    {ECU_POWER_MODE_STATIC, ECU_POWER_MODE_STANDBY, ECUPwrModeStatic_To_StandBy_TransCheck_func, ECUPwrModeStatic_To_StandBy_EntryAction_func},\
    {ECU_POWER_MODE_STATIC, ECU_POWER_MODE_CRANK, ECUPwrModeStatic_To_Crank_TransCheck_func, ECUPwrModeStatic_To_Crank_EntryAction_func},\
    {ECU_POWER_MODE_STATIC, ECU_POWER_MODE_ACTIVE, ECUPwrModeStatic_To_Active_TransCheck_func, ECUPwrModeStatic_To_Active_EntryAction_func},\
    {ECU_POWER_MODE_STATIC, ECU_POWER_MODE_STATIC, NULL, ECUPwrModeStatic_Action_func },\
    {ECU_POWER_MODE_CRANK, ECU_POWER_MODE_ACTIVE, ECUPwrModeCrank_To_Active_TransCheck_func, ECUPwrModeCrank_To_Active_EntryAction_func},\
    {ECU_POWER_MODE_CRANK, ECU_POWER_MODE_CRANK, NULL, ECUPwrModeCrank_Action_func },\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_OFF, ECUPwrModeActive_To_Off_TransCheck_func, PwrModeActive_To_Off_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_STANDBY, ECUPwrModeActive_To_StandBy_TransCheck_func, ECUPwrModeActive_To_StandBy_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_STATIC, ECUPwrModeActive_To_Static_TransCheck_func, ECUPwrModeActive_To_Static_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_CRANK, ECUPwrModeActive_To_Crank_TransCheck_func, ECUPwrModeActive_To_Crank_EntryAction_func},\
    {ECU_POWER_MODE_ACTIVE, ECU_POWER_MODE_ACTIVE, NULL, ECUPwrModeActive_Action_func },\
    {SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL }*/
};

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
static uint16_t l_PwrModeInitial_Timer_u16 = 0;

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/


/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
static uint8_t pm_GetSyncStatus(void);

static uint8_t pm_GetSyncStatus(void)
{
	return 1;
}
static void pm_ReqNewSyncState(states_SM p_requested_status_sm)
{

}

/**
 * @brief  ECUPwrModeStandBy_To_Off_TransCheck_func function is to check the entry condition for standby to off state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStandBy_To_Off_TransCheck_func(void)
{
    uint8_t fl_allow_standby_off_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into OFF state if Standby Timer elapsed and IGN is OFF;*/
    /**if (IGN_STATUS) then (OFF)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnOFF_mode)
    {

        /**:Request for A53 and A7 Core to enter into OFF State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_OFF);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_standby_off_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in OFF State;*/

    return (fl_allow_standby_off_state_u8);
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
    bool fl_sync_status_bool = false;

    /**:Enter into OFF state if IGN is OFF;*/
    /**if (IGN_STATUS) then (OFF)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnOFF_mode)
    {
        //printf("powermodeActive_to_off\n");

        /**:Request for A53 and A7 Core to enter into OFF State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_OFF);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_active_off_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    /**:Also, A53 and A7 cores should have already been in OFF State;*/

    return (fl_allow_active_off_state_u8);

}
/**
 * @brief  ECUPwrModeOff_To_StandBy_TransCheck_func function is to check the entry condition for off to standby state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeOff_To_StandBy_TransCheck_func(void)
{
    uint8_t fl_allow_off_standby_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if HW_Acc is ON;*/
    /**if (HW_Acc) then (ON)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_STANDBY State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_STANDBY);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_off_standby_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_STANDBY State;*/

    return (fl_allow_off_standby_state_u8);

}
/**
 * @brief  ECUPwrModeStatic_To_StandBy_TransCheck_func function is to check the entry condition for static to standby state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStatic_To_StandBy_TransCheck_func(void)
{
    uint8_t fl_allow_off_standby_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if power is OFF;*/
    /**if (power) then (OFF)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_STANDBY State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_STANDBY);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_off_standby_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_STANDBY State;*/

    return (fl_allow_off_standby_state_u8);

}
/**
 * @brief  ECUPwrModeActive_To_StandBy_TransCheck_func function is to check the entry condition for Active to standby state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeActive_To_StandBy_TransCheck_func(void)
{
    uint8_t fl_allow_active_standby_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnON_mode)
    {
        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_STANDBY State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_STANDBY);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_active_standby_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_STANDBY State;*/

    return (fl_allow_active_standby_state_u8);

}
/**
 * @brief  ECUPwrModeStandBy_To_Static_TransCheck_func function is to check the entry condition for Standby to static state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStandBy_To_Static_TransCheck_func(void)
{
    uint8_t fl_allow_standby_static_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into Static state if power is ON;*/
    /**if (power) then (ON)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_STATIC State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_STATIC);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_standby_static_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_STATIC State;*/

    return (fl_allow_standby_static_state_u8);

}
/**
 * @brief  ECUPwrModeActive_To_Static_TransCheck_func function is to check the entry condition for Active to static state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeActive_To_Static_TransCheck_func(void)
{
    uint8_t fl_allow_active_static_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into static state if Ign is Off & EntryToActiveDueToRemoteFlag  is False and IsNewConfigurationDetectedFlag is False;*/
    /**if (IGN_STATUS) then (OFF)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnOFF_mode)
    {
        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_STATIC State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_STATIC);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_active_static_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_STATIC State;*/

    return (fl_allow_active_static_state_u8);

}
/**
 * @brief  ECUPwrModeStandBy_To_Crank_TransCheck_func function is to check the entry condition for Standby to Crank state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStandBy_To_Crank_TransCheck_func(void)
{
    uint8_t fl_allow_standby_crank_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into Crank state if Crank is ON;*/
    /**if (Crank) then (ON)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_CRANK State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_CRANK);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_standby_crank_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_CRANK State;*/

    return (fl_allow_standby_crank_state_u8);

}
/**
 * @brief  ECUPwrModeStatic_To_Crank_TransCheck_func function is to check the entry condition for Static to Crank state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStatic_To_Crank_TransCheck_func(void)
{
        uint8_t fl_allow_static_crank_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into Crank state if Crank is ON;*/
    /**if (Crank) then (ON)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_CRANK State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_CRANK);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_static_crank_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_CRANK State;*/

    return (fl_allow_static_crank_state_u8);

}
/**
 * @brief  ECUPwrModeActive_To_Crank_TransCheck_func function is to check the entry condition for active to Crank state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeActive_To_Crank_TransCheck_func(void)
{
    uint8_t fl_allow_active_crank_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into Crank state if Crank is ON;*/
    /**if (Crank) then (ON)*/
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_CRANK State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_CRANK);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_active_crank_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_CRANK State;*/

    return (fl_allow_active_crank_state_u8);

}
/**
 * @brief  ECUPwrModeStandBy_To_Active_TransCheck_func function is to check the entry condition for Standby to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStandBy_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_standby_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnOFF_mode)
    {
        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_ACTIVE State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_ACTIVE);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_standby_active_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_ACTIVE State;*/

    return (fl_allow_standby_active_state_u8);

}
/**
 * @brief  ECUPwrModeStatic_To_Active_TransCheck_func function is to check the entry condition for Static to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeStatic_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_static_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnON_mode)
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_ACTIVE State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_ACTIVE);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_static_active_state_u8 = ALLOW_TRANSITION; /*1*/
        }
    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_ACTIVE State;*/

    return (fl_allow_static_active_state_u8);

}
/**
 * @brief  ECUPwrModeCrank_To_Active_TransCheck_func function is to check the entry condition for Crank to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeCrank_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_crank_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnON_mode)
    {

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_ACTIVE State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_ACTIVE);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_crank_active_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_ACTIVE State;*/

    return (fl_allow_crank_active_state_u8);

}
/**
 * @brief  ECUPwrModeCrank_To_Active_TransCheck_func function is to check the entry condition for off to active state
 *
 * @param[in] void type
 *
 * @return true if A53,A7,R5 are in same state otherwisee return false
 *
 */
uint8_t ECUPwrModeOff_To_Active_TransCheck_func(void)
{
    uint8_t fl_allow_off_active_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/
    bool fl_sync_status_bool = false;

    /**:Enter into StandBy state if IGN is ON;*/
    /**if (IGN_STATUS) then (ON)*/
    states_SM IGN_STATUS = IGN_get_current_state();
    if(IGN_STATUS==IgnON_mode)
    {
        //printf("powermodeoff_to_Active_state\n");

        /**:Request for A53 and A7 Core to enter into ECU_POWER_MODE_ACTIVE State;*/
        pm_ReqNewSyncState(ECU_POWER_MODE_ACTIVE);
        fl_sync_status_bool = pm_GetSyncStatus();

        if(fl_sync_status_bool != false)
        {
            fl_allow_off_active_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    /**:Also, A53 and A7 cores should have already been in ECU_POWER_MODE_ACTIVE State;*/

    return (fl_allow_off_active_state_u8);

}
/**
 * @brief  ECUPwrModeInitial_To_Off_TransCheck_func function is to check the entry condition for ecupowermodeInitial to Off state
 *
 * @param[in] void type
 *
 * @return true if same state otherwise return false
 *
 */
uint8_t ECUPwrModeInitial_To_Off_TransCheck_func(void)
{
    uint8_t fl_allow_initial_off_state_u8 = TRANSITION_NOT_ALLOWED; /*0*/

    if(l_PwrModeInitial_Timer_u16<=100)//ECUPWRMODE_INITIAL_TIMEOUT)
    {
        printf("l_PwrModeInitial_Timer_u16 %d\n",l_PwrModeInitial_Timer_u16);
        l_PwrModeInitial_Timer_u16++;
    }
    else
    {
        l_PwrModeInitial_Timer_u16=0;
        /**:Enter into OFF state if IGN is OFF;*/
        /**if (IGN_STATUS) then (OFF)*/
        states_SM IGN_STATUS = IGN_get_current_state();
        if(IGN_STATUS==IgnOFF_mode)
        {
            //printf("powermodeActive_to_off\n");
             fl_allow_initial_off_state_u8 = ALLOW_TRANSITION; /*1*/
        }

    }
    return (fl_allow_initial_off_state_u8);
}

/**
 * @brief  ECUPwrModeStandBy_To_Off_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void ECUPwrModeStandBy_To_Off_EntryAction_func(void)
{
    uint8_t fl_standby_off_counter_u8 = 0;
    static const pwrmode_ptr_t StandBy_To_Off_List[]=
    {
        ECUPWRMODESTANDBY_TO_OFF_LIST \
        NULL, \
    };

    while (StandBy_To_Off_List[fl_standby_off_counter_u8] != NULL)
    {
        StandBy_To_Off_List[fl_standby_off_counter_u8]();
        fl_standby_off_counter_u8++;
    }

}
/**
 * @brief  PwrModeActive_To_Off_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void PwrModeActive_To_Off_EntryAction_func(void)
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
 * @brief  ECUPwrModeOff_To_StandBy_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_OFF to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_To_StandBy_EntryAction_func(void)
{
    uint8_t fl_off_standby_counter_u8 = 0;
    static const pwrmode_ptr_t Off_To_standby_List[]=
    {
        ECUPWRMODEOFF_TO_STANDBY_LIST \
        NULL, \
    };

    while (Off_To_standby_List[fl_off_standby_counter_u8]!= NULL)
    {
        Off_To_standby_List[fl_off_standby_counter_u8]();
        fl_off_standby_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStatic_To_StandBy_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_StandBy_EntryAction_func(void)
{
    uint8_t fl_static_standby_counter_u8 = 0;
    static const pwrmode_ptr_t Static_standby_List[]=
    {
        ECUPWRMODESTATIC_TO_STANDBY_LIST \
        NULL, \
    };

    while (Static_standby_List[fl_static_standby_counter_u8]!= NULL)
    {
        Static_standby_List[fl_static_standby_counter_u8]();
        fl_static_standby_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeActive_To_StandBy_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_StandBy_EntryAction_func(void)
{
    uint8_t fl_active_standby_counter_u8 = 0;
    static const pwrmode_ptr_t Active_standby_List[]=
    {
        ECUPWRMODEACTIVE_TO_STANDBY_LIST \
        NULL, \
    };

    while (Active_standby_List[fl_active_standby_counter_u8] != NULL)
    {
        Active_standby_List[fl_active_standby_counter_u8]();
        fl_active_standby_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStandBy_To_Static_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Static_EntryAction_func(void)
{
    uint8_t fl_standby_static_counter_u8 = 0;
    static const pwrmode_ptr_t StandBy_To_static_List[]=
    {
        ECUPWRMODESTANDBY_TO_STATIC_LIST \
        NULL, \
    };

    while (StandBy_To_static_List[fl_standby_static_counter_u8]!= NULL)
    {
        StandBy_To_static_List[fl_standby_static_counter_u8]();
        fl_standby_static_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeActive_To_Static_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Static_EntryAction_func(void)
{
    uint8_t fl_active_static_counter_u8 = 0;
    static const pwrmode_ptr_t Active_To_static_List[]=
    {
        ECUPWRMODEACTIVE_TO_STATIC_LIST \
        NULL, \
    };

    while (Active_To_static_List[fl_active_static_counter_u8] != NULL)
    {
        Active_To_static_List[fl_active_static_counter_u8]();
        fl_active_static_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStandBy_To_Crank_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Crank_EntryAction_func(void)
{
    uint8_t fl_standby_crank_counter_u8 = 0;
    static const pwrmode_ptr_t StandBy_To_crank_List[]=
    {
        ECUPWRMODESTANDBY_TO_CRANK_LIST \
        NULL, \
    };

    while (StandBy_To_crank_List[fl_standby_crank_counter_u8] != NULL)
    {
        StandBy_To_crank_List[fl_standby_crank_counter_u8]();
        fl_standby_crank_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStatic_To_Crank_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_Crank_EntryAction_func(void)
{
    uint8_t fl_static_crank_counter_u8 = 0;
    static const pwrmode_ptr_t Static_To_crank_List[]=
    {
        ECUPWRMODESTATIC_TO_CRANK_LIST \
        NULL, \
    };

    while (Static_To_crank_List[fl_static_crank_counter_u8] != NULL)
    {
        Static_To_crank_List[fl_static_crank_counter_u8]();
        fl_static_crank_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeActive_To_Crank_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Crank_EntryAction_func(void)
{
    uint8_t fl_active_crank_counter_u8 = 0;
    static const pwrmode_ptr_t Active_To_crank_List[]=
    {
        ECUPWRMODEACTIVE_TO_CRANK_LIST \
        NULL, \
    };

    while (Active_To_crank_List[fl_active_crank_counter_u8]!= NULL)
    {
        Active_To_crank_List[fl_active_crank_counter_u8]();
        fl_active_crank_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStandBy_To_Active_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Active_EntryAction_func(void)
{
    uint8_t fl_standby_active_counter_u8 = 0;
    static const pwrmode_ptr_t StandBy_To_active_List[]=
    {
        ECUPWRMODESTANDBY_TO_ACTIVE_LIST \
        NULL, \
    };

    while (StandBy_To_active_List[fl_standby_active_counter_u8] != NULL)
    {
        StandBy_To_active_List[fl_standby_active_counter_u8]();
        fl_standby_active_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStatic_To_Active_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_Active_EntryAction_func(void)
{
    uint8_t fl_static_active_counter_u8 = 0;
    static const pwrmode_ptr_t Static_To_active_List[]=
    {
        ECUPWRMODESTATIC_TO_ACTIVE_LIST \
        NULL, \
    };

    while (Static_To_active_List[fl_static_active_counter_u8] != NULL)
    {
        Static_To_active_List[fl_static_active_counter_u8]();
        fl_static_active_counter_u8++;
    }

}
/**
 * @brief  ECUPwrModeCrank_To_Active_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_CRANK to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeCrank_To_Active_EntryAction_func(void)
{
    uint8_t fl_crank_active_counter_u8 = 0;
    static const pwrmode_ptr_t Crank_To_active_List[]=
    {
        ECUPWRMODECRANK_TO_ACTIVE_LIST \
        NULL, \
    };

    while (Crank_To_active_List[fl_crank_active_counter_u8]!= NULL)
    {
        Crank_To_active_List[fl_crank_active_counter_u8]();
        fl_crank_active_counter_u8++;
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
 * @brief  ECUPwrModeInitial_To_Off_EntryAction_func function is to perform some action when the state changed from ECU_POWER_MODE_Initial to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeInitial_To_Off_EntryAction_func(void)
{
    uint8_t fl_Initial_off_counter_u8 = 0;
    static const pwrmode_ptr_t Initial_Off_List[]=
    {
        ECUPERMODEINITIAL_TO_OFF_LIST \
        NULL, \
    };

    while (Initial_Off_List[fl_Initial_off_counter_u8] != NULL)
    {
        Initial_Off_List[fl_Initial_off_counter_u8]();
        fl_Initial_off_counter_u8++;
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
 * @brief  ECUPwrModeStandBy_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_Action_func(void)
{
    uint8_t fl_standby_counter_u8 = 0;
    static const pwrmode_ptr_t StandBy_List[]=
    {
        ECUPWRMODESTANDBY_LIST \
        NULL, \
    };

    while (StandBy_List[fl_standby_counter_u8] != NULL)
    {
        StandBy_List[fl_standby_counter_u8]();
        fl_standby_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeStatic_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_Action_func(void)
{
    uint8_t fl_standby_counter_u8 = 0;
    static const pwrmode_ptr_t Static_List[]=
    {
        ECUPWRMODESTATIC_LIST \
        NULL, \
    };

    while (Static_List[fl_standby_counter_u8] != NULL)
    {
        Static_List[fl_standby_counter_u8]();
        fl_standby_counter_u8++;
    }
}
/**
 * @brief  ECUPwrModeCrank_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeCrank_Action_func(void)
{
    uint8_t fl_crank_counter_u8 = 0;
    static const pwrmode_ptr_t Crank_List[]=
    {
        ECUPWRMODECRANK_LIST \
        NULL, \
    };

    while (Crank_List[fl_crank_counter_u8] != NULL)
    {
        Crank_List[fl_crank_counter_u8]();
        fl_crank_counter_u8++;
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
 * @brief  ECUPwrModeInitial_Action_func function is to perform some action when the state remain in ECU_POWER_MODE_INITIAL
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeInitial_Action_func(void)
{
    uint8_t fl_Initial_counter_u8 = 0;
    static const pwrmode_ptr_t Initial_List[]=
    {
        ECUPERMODEINITIAL_LIST \
        NULL, \
    };

    while (Initial_List[fl_Initial_counter_u8] != NULL)
    {
        Initial_List[fl_Initial_counter_u8]();
        fl_Initial_counter_u8++;
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
