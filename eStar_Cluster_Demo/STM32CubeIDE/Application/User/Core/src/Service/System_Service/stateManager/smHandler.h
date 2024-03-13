/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file smHandler.h
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
#ifndef SM_HANDLER_H
#define	SM_HANDLER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "string.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
typedef enum
{
	SM_STATE_INVALID = 0x0000,
	SM_STATE_1 = 0x0001,
	SM_STATE_2 = 0x0002,
	SM_STATE_3 = 0x0004,
	SM_STATE_4 = 0x0008,
	SM_STATE_5 = 0x0010,
	SM_STATE_6 = 0x0020,
	SM_STATE_7 = 0x0040,
	SM_STATE_8 = 0x0080,
	SM_STATE_9 = 0x0100,
	SM_STATE_10 = 0x0200,
	SM_STATE_11 = 0x0400,
	SM_STATE_12 = 0x0800,
	SM_STATE_13 = 0x1000,
	SM_STATE_14 = 0x2000,
	SM_STATE_15 = 0x4000,
	SM_STATE_16 = 0x8000
}states_SM;

/**
 * @brief typedef for a function pointer taking no arguments and returning a bool for a TransitionCheck function
 *****************************************************************************************************************/
typedef uint8_t (*smTransCheck)(void);
/**
 * @brief typedef for a function pointer taking no arguments and returning void for Transition Action Callback
 *****************************************************************************************************************/
typedef void (*smTransAction)(void);

/**
 * @brief Structure definition of a 'Transition' 
 **************************************************************************************************/
typedef struct
{
    states_SM in_state_u16;
    states_SM next_state_u16;
    smTransCheck TransitionCheck_fp;
    smTransAction TransitionAction_fp;
}transition_T;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
void State_Manager_task(void);
void State_Manager_init(void);
states_SM SM_get_current_state(uint8_t l_Ign_SM_INDEX);
#endif	/* SM_HANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

