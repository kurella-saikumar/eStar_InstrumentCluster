/** \addtogroup  VDIO-STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler_SmHandler.h
 *
 * @brief ECUPowerMode_StateManager Handler file performs the transition of ACC .
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
***************************************************************************************************/
#ifndef IGN_SMHANDLER_H
#define	IGN_SMHANDLER_H

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

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

#define IgnON_mode SM_STATE_1
#define IgnOFF_mode SM_STATE_2

#define IGN_SM_INDEX 0

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

extern void vIgnitionONFunc(void);
extern void vIgnitionOffFunc(void);
extern void vInIgnitionONFunc(void);
extern void vInIgnitionOffFunc(void);
extern uint16_t usIgnitionGetCurrentState(void);

extern const transition_T gl_IGNMode_SM_t[];

#endif	/* IGN_SMHANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

