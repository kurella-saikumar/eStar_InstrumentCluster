/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file batterVoltage_SmHandler.h
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
#ifndef ECUPWRMODE_SMHANDLER_H
#define	ECUPWRMODE_SMHANDLER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "smHandler.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

#define ECU_POWER_MODE_OFF SM_STATE_3
#define ECU_POWER_MODE_ACTIVE SM_STATE_4
#define ECU_POWER_MODE_SLEEP SM_STATE_5


#define ECUPWR_MODE_SM_INDEX 2

#define TRANSITION_NOT_ALLOWED 0
#define ALLOW_TRANSITION       1

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

extern void vEcuPwrModeSleepToOffEntryAction(void);
extern void vEcuPwrModeActiveToOffEntryAction(void);
extern void vEcuPwrModeOffToSleepEntryAction(void);
extern void vEcuPwrModeActiveToSleepEntryAction(void);
extern void vEcuPwrModeSleepToActiveEntryAction(void);
extern void vEcuPwrModeOffAction(void);
extern void vEcuPwrModeSleepAction(void);
extern void vEcuPwrModeActiveAction(void);
extern void vEcuPwrModeOffActiveEntryAction(void);

extern void pm_ReqNewState(states_SM p_requested_status_sm);
extern states_SM pm_GetSyncStatus(void);
extern const transition_T gl_ECUPwrMode_SM_t[];
#endif	/* ECUPWRMODE_SMHANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

