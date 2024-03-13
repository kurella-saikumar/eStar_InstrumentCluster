/** \addtogroup STATE_MACHINE_CONFIGURATION
 *  @{
 * @file smHandler_cfg.h
 *
 * @brief Template Header File
 *
 * File Short Name: 
 *
 * Author: 
 *
 * Create Date: 
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef SM_HANDLER_CFG_H
#define	SM_HANDLER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
//#include "batterVoltage_SmHandler.h"
//#include "TempSensor_SmHandler.h"
//#include "ACC_SmHandler.h"
#include "IGN_SmHandler.h"
#include "IGN_SmHandler_cfg.h"
//#include "ACC_SmHandler.h"
//#include "ACC_SmHandler_cfg.h"
//#include "IgnitionManager/ACC_SmHandler.h"
//#include "smHandler_cfg.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
#define STATE_MACHINES_CONFIG \
/*Default State of the state machine, Array of Transitions of the state machine*/\
/*Make sure to have {SM_STATE_INVALID, SM_STATE_INVALID, NULL, NULL } always as the last transition in each state machine's transition array*/\
/*State Machine 0 Configuration*/{IGN_MANAGER_DEFAULT_STATE, gl_IGNMode_SM_t}

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

#endif	/* SM_HANDLER_CFG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

