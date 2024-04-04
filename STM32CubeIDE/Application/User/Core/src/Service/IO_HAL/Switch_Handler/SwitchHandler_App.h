/** \addtogroup SWITCH_HANDLER
 *  @{
 * @file SwitchHandler_App.h
 *
 * @brief Implementation file for handling switch events.
 *
 * File Short Name: SwitchHandler
 *
 * @author :Govindraj
 *
 * @date Date
 *
 * @copyright  
 * All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 * ********************************************************************************************** @}*/

#ifndef SWITCH_HANDLER_APP_H
#define SWITCH_HANDLER_APP_H

#include "../Switch/switch.h"
// Include necessary libraries or headers if needed

// Define macro for reading mode button input
#define MODE_BUTTON_INPUT IO_RA6_GetValue()

// Define macro for reading reset button input
#define RESET_BUTTON_INPUT IO_RA7_GetValue()


typedef enum {
    CLOCK_MODE_INACTIVE,  // Clock setting mode is off
    CLOCK_MODE_ACTIVE    // Clock setting mode is on
} ClockMode;

typedef enum
{
    CLOCK_ENTRY,
    MODE_LONGPRESS,
    MODE_SHORTPRESS,
    RESET_LONGPRESS,
	RESET_LONGPRESS_RELEASE,
    RESET_SHORTPRESS
}Clock_Edit_Actions;



// Function to get the current clock mode
ClockMode xGetClockMode(void);

extern Button_Push_Event_T getModeButtonStatus(void);
extern Button_Push_Event_T getResetButtonStatus(void);

//extern Clock_Edit_Actions clockSettingGetSetMode(void);
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
// Function prototype for the switch handler task
extern void vSwitchHandlerTask(void);

// Function prototype for handling mode reset actions
extern void vHandleModeResetActions(void);
Clock_Edit_Actions clockSettingGetSetMode(void);
#endif /* SWITCH_HANDLER_APP_H */

