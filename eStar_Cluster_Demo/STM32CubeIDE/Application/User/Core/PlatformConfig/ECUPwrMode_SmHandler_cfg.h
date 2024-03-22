/** \addtogroup STATE_MACHINE_CONFIGURATION
 *  @{
 * @file IGN_SmHandler_cfg.h
 *
 * @brief Template Header File
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
***************************************************************************************************/
#ifndef ECUPWRMODE_SM_HANDLER_CFG_H
#define	ECUPWRMODE_SM_HANDLER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
// #include "IGN_SmHandler.h"
#include "ECUPwrMode_SmHandler.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

#define PM_MANAGER_DEFAULT_STATE ECU_POWER_MODE_OFF

#define POWER_MODE_TASK_PERIOD_MS       10 /*10 milli seconds*/
#define ECUPWRMODE_INITIAL_TIMEOUT_MS 3000 /*3 seconds*/

#define ECUPWRMODE_INITIAL_TIMEOUT (ECUPWRMODE_INITIAL_TIMEOUT_MS/POWER_MODE_TASK_PERIOD_MS)

/*
*the defined macro "IGNON_ACTION_FUNC" that expands to IGNON_func().
* It is likely used to invoke or execute a function called IGNON_func()
*/

#define ECUPWRMODESLEEP_TO_OFF_LIST \
ECUPwrModeSleep_To_Off_EntryAction,\

#define ECUPWRMODEACTIVE_TO_OFF_LIST \
ECUPwrModeActive_To_Off_EntryAction,\

#define ECUPWRMODEOFF_TO_SLEEP_LIST \
ECUPwrModeOff_To_Sleep_EntryAction,\

#define ECUPWRMODEACTIVE_TO_SLEEP_LIST \
ECUPwrModeActive_To_Sleep_EntryAction,\

#define ECUPWRMODESLEEP_TO_ACTIVE_LIST \
ECUPwrModeSleep_To_Active_EntryAction,\

#define ECUPWRMODEOFF_LIST \
ECUPwrModeOff_Action,\

#define ECUPWRMODESLEEP_LIST \
ECUPwrModeSleep_Action,\

#define ECUPWRMODEACTIVE_LIST \
ECUPwrModeActive_Action,\

#define ECUPWRMODEOFF_To_ACTIVE_LIST \
ECUPwrModeOff_Active_ENtryAction,\



/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

#endif	/* ECUPWRMODE_SM_HANDLER_CFG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

