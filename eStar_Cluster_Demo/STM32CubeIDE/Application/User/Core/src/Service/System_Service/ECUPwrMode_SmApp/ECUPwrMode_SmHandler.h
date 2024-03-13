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

#define ECU_POWER_MODE_OFF SM_STATE_1
#define ECU_POWER_MODE_STANDBY SM_STATE_2
#define ECU_POWER_MODE_STATIC SM_STATE_3
#define ECU_POWER_MODE_CRANK SM_STATE_4
#define ECU_POWER_MODE_ACTIVE SM_STATE_5
#define ECU_POWER_MODE_INITIAL SM_STATE_6

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

extern void ECUPwrModeStandBy_To_Off_EntryAction(void);
extern void PwrModeActive_To_Off_EntryAction(void);
extern void ECUPwrModeOff_To_StandBy_EntryAction(void);
extern void ECUPwrModeStatic_To_StandBy_EntryAction(void);
extern void ECUPwrModeActive_To_StandBy_EntryAction(void);
extern void ECUPwrModeStandBy_To_Static_EntryAction(void);
extern void ECUPwrModeActive_To_Static_EntryAction(void);
extern void ECUPwrModeStandBy_To_Crank_EntryAction(void);
extern void ECUPwrModeStatic_To_Crank_EntryAction(void);
extern void ECUPwrModeActive_To_Crank_EntryAction(void);
extern void ECUPwrModeStandBy_To_Active_EntryAction(void);
extern void ECUPwrModeStatic_To_Active_EntryAction(void);
extern void ECUPwrModeCrank_To_Active_EntryAction(void);
extern void ECUPwrModeOff_Action(void);
extern void ECUPwrModeStandBy_Action(void);
extern void ECUPwrModeStatic_Action(void) ;
extern void ECUPwrModeCrank_Action(void);
extern void ECUPwrModeActive_Action(void);

extern void ECUPwrModeOff_Active_ENtryAction(void);
extern void ECUPerModeInitial_Off_EntryAction(void);
extern void ECUPwrModeInitial_Action(void);

extern const transition_T gl_ECUPwrMode_SM_t[];
#endif	/* ECUPWRMODE_SMHANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

