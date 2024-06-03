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
vEcuPwrModeSleepToOffEntryAction,\

#define ECUPWRMODEACTIVE_TO_OFF_LIST \
vEcuPwrModeActiveToOffEntryAction,\

#define ECUPWRMODEOFF_TO_SLEEP_LIST \
vEcuPwrModeOffToSleepEntryAction,\

#define ECUPWRMODEACTIVE_TO_SLEEP_LIST \
vEcuPwrModeActiveToSleepEntryAction,\

#define ECUPWRMODESLEEP_TO_ACTIVE_LIST \
vEcuPwrModeSleepToActiveEntryAction,\

#define ECUPWRMODEOFF_LIST \
vEcuPwrModeOffAction,\

#define ECUPWRMODESLEEP_LIST \
vEcuPwrModeSleepAction,\

#define ECUPWRMODEACTIVE_LIST \
vEcuPwrModeActiveAction,\

#define ECUPWRMODEOFF_To_ACTIVE_LIST \
vEcuPwrModeOffActiveEntryAction,\



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

