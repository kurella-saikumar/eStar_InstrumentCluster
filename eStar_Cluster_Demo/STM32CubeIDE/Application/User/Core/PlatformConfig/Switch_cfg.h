/** \addtogroup SWITCH_USER_CONFIGURATION
 *  @{
 * @file switch_cfg.h
 *
 * @brief 
 *
 * File Short Name: switch_cfg
 *
 * @author: 
 *
 * @date: 
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef SWITCH_CFG_H   
#define SWITCH_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "../Switch/switch.h"
#include "stdint.h"


/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define SEPARATE_CALLBACK_FUNCTIONS 0

extern Switch_PushRelease_State_T eModeButtonPushReleaseState;
extern Switch_PushRelease_State_T eResetButtonPushReleaseState;

/**
 * Define a structure of button press durations for each of the buttons, in the following format
 * {"SHORT_PUSH_MIN_TIME_MSEC, LONG_PUSH_MIN_TIME_MSEC, STUCK_BUTTON_MIN_TIME_MSEC"}
 * Note: The base counter for the SHORT_PUSH, LONG_PUSH and BUTTON_STUCK Detection is the periodicity at which
 * the "Process_Button_States" function is called by the application
 */

/* Macros for short-push,long-push and stuck functionality of all analog and digital switches */
/*  Stuck functionality is implemented for 5minutes (12000 * 5 = 60000msec) */

#define MODE_BUTTON_DURATIONS_CONFIG {4,60,600}
#define RESET_BUTTON_DURATION_CONFIG {4,60,600}

/**************************************************************************************************************************************************
*** Only the list name gets used in the code, during initializing the respective array... All items in the list are local to this Configuartion ***
***************************************************************************************************************************************************/

/* Both Analog and Digital Switch states can be added... However, the inputs to be fed finally as only two states - PUSHED and RELEASED  */
#define INPUT_SWITCH_POINTERS \
    &eModeButtonPushReleaseState, /** Pointer to the variable giving the button state - PUSHED and RELEASED*/\
    &eResetButtonPushReleaseState /** Pointer to the variable giving the button state - PUSHED and RELEASED*/\


#define SWITCH_PRESS_DURATION_CONFIGURATION \
    MODE_BUTTON_DURATIONS_CONFIG, \
	RESET_BUTTON_DURATION_CONFIG
	
#if SEPARATE_CALLBACK_FUNCTIONS

#else
extern void vModeButtonPressHandler(Button_Push_Event_T);
extern void vResetButtonPressHandler(Button_Push_Event_T);

#define BUTTON_PUSH_NOTIFY_CALLBACKS \
&vModeButtonPressHandler,\
&vResetButtonPressHandler

#endif

/*Global Type Definitions*/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

#endif /*SWITCH_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
