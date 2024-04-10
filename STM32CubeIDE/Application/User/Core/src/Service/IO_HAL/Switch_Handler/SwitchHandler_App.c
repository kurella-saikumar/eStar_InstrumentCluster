/** \addtogroup SWITCH_HANDLER
 *  @{
 * @file SwitchHandler_App.c
 *
 * @brief Implementation file for handling switch events.
 *
 * File Short Name: SwitchHandler
 *
 * @author: Govindraj
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

#ifndef SWITCH_HANDLER_APP_C
#define SWITCH_HANDLER_APP_C    /* Guard against multiple inclusion */


/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdio.h"
#include "stdint.h"
#include <stdio.h>

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "DriverInfoMenu_App.h"
#include "Switch.h"
#include "Switch_cfg.h"
#include "SwitchHandler_App.h"
#include "SwitchInf.h"
#include "stm32h7xx_hal.h"

//#include "../Clock_App/clock_App.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
#define BUTTON_TIMEOUT_THRESHOLD 15000 // Timeout duration in seconds

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
uint8_t l_Mode_ButtonEvent_Status_u8 = 0xFF;
uint8_t l_Reset_ButtonEvent_Status_u8 = 0xFF;


uint8_t l_mode_button_status_u8 = 0;
uint8_t l_reset_button_status_u8 = 0;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
Switch_PushRelease_State_T gl_mode_button_Push_Release_state_t = BUTTON_RELEASED;
Switch_PushRelease_State_T gl_reset_button_Push_Release_state_t = BUTTON_RELEASED;

ClockMode eclockMode = CLOCK_MODE_INACTIVE;
// Define a timer variable to track the count since the last button press
uint32_t l_button_Timeout = 0,l_button_Timeout_Start=0,l_button_Timeout_End=0;


//extern STATE_t ModeSwitchState = RELEASED;


/**
 * @brief In this function updating the control switch state
 *
 * @param[in] None
 *
 * @return None
 *
 ***************************************************************************************************/
void vMode_Button_Press_Hdlr(Button_Push_Event_T eModeButtonStatus)
{

    l_Mode_ButtonEvent_Status_u8 = eModeButtonStatus;
}

void vReset_Button_Press_Hdlr(Button_Push_Event_T eResetButtonStatus)
{

	l_Reset_ButtonEvent_Status_u8 = eResetButtonStatus;
}



/**
 * @brief Task to handle switch button inputs and update their states.
 * 
 * This function reads the status of mode and reset buttons, updates their
 * push/release states accordingly, and stores the states in global variables.
 */
void vSwitchHandlerTask(void)
{
    // Read the status of mode and reset buttons
    l_mode_button_status_u8 = xGetModeSwitch();
    l_reset_button_status_u8 = xGetResetSwitch();
    

    // Check if mode button is pressed
    if (l_mode_button_status_u8 == PRESSED)
    {
        // Update global mode button state to pushed
        gl_mode_button_Push_Release_state_t = BUTTON_PUSHED;
    }
    else
    {
        // Update global mode button state to released
        gl_mode_button_Push_Release_state_t = BUTTON_RELEASED;
    }
    
    // Check if reset button is pressed
    if (l_reset_button_status_u8 == PRESSED)
    {
        // Update global reset button state to pushed
        gl_reset_button_Push_Release_state_t = BUTTON_PUSHED;
    }
    else
    {
        // Update global reset button state to released
        gl_reset_button_Push_Release_state_t = BUTTON_RELEASED;
    }
    //printf("l_Mode_button_status_u8:%d\r\n",l_mode_button_status_u8);
    //printf("l_Reset_button_status_u8:%d\r\n",l_reset_button_status_u8);
}

/**
 * @brief Retrieves the current clock mode.
 * 
 * This function returns the current clock mode stored in a local variable.
 * The clock mode indicates whether the clock setting mode is active or inactive.
 * 
 * @return The current clock mode.
 */
ClockMode xGetClockMode(void) 
{
    // Return the current clock mode stored in a local variable
    return eclockMode;
}


/**
 * @brief Handles actions based on mode and reset button presses.
 * 
 * This function processes the state of mode and reset buttons and performs
 * actions accordingly, such as toggling odometer units, switching modes,
 * and resetting trip values. It also manages the clock mode and button timeout.
 */

Button_Push_Event_T getModeButtonStatus(void)
{
    Button_Push_Event_T mode_status = 0xFF;
    if(eclockMode == CLOCK_MODE_ACTIVE)
    {
        mode_status = l_Mode_ButtonEvent_Status_u8;
        
    }
    else
    {
        mode_status = 0xFF;
    }
    return mode_status;
    
}

Clock_Edit_Actions clockSettingGetSetMode(void)
{
    Button_Push_Event_T clk_mode_status = getModeButtonStatus();
    Button_Push_Event_T clk_reset_status = getResetButtonStatus();
//    printf("clk_reset_status : %d",clk_reset_status);
//    clockSettingRunMode(CLOCK_ENTRY);

     if(clk_mode_status == SHORT_PRESS_RELEASED )
     {
         printf("Clock mode short press\r\n");
         clockSettingRunMode(MODE_SHORTPRESS);
     }
     else if(clk_mode_status == LONG_PRESS_HELD)
     {
        printf("clock mode long press\r\n");
         clockSettingRunMode(MODE_LONGPRESS);
     }
     else if(clk_reset_status == SHORT_PRESS_RELEASED)
     {
         printf("clock reset short press\r\n");
         clockSettingRunMode(RESET_SHORTPRESS);
     }
     else if(clk_reset_status == LONG_PRESS_RELEASED)
	  {
		  printf("clock reset long press release");
		  clockSettingRunMode(RESET_LONGPRESS_RELEASE);
	  }
     else if(clk_reset_status == LONG_PRESS_HELD)
     {
         printf("clock reset long press held");
         clockSettingRunMode(RESET_LONGPRESS_HELD);
     }
     else
     {

     }

	return 0;

}

Button_Push_Event_T getResetButtonStatus(void)
{
    Button_Push_Event_T reset_status = 0xFF;
    if(eclockMode == CLOCK_MODE_ACTIVE)
    {
        reset_status = l_Reset_ButtonEvent_Status_u8;
        
    }
    else
    {
        reset_status = 0xFF;
    }
    return reset_status;
    
}


void vHandleModeResetActions(void)
{

    /***/
    // Check if both mode and reset buttons are short-pressed
    if (l_Mode_ButtonEvent_Status_u8 == SHORT_PRESS_RELEASED && l_Reset_ButtonEvent_Status_u8 == SHORT_PRESS_RELEASED)
    {
        // Odometer Units Toggle
        //ToggleOdometerUnits();
        // Reset Button Status
        
        l_Mode_ButtonEvent_Status_u8 = 0xFF;
        l_Reset_ButtonEvent_Status_u8= 0xFF;
        printf("mode and reset short pressed - Odo Units toggle\r\n");
        
    }
    // Check if mode button is short-pressed 
    else if (l_Mode_ButtonEvent_Status_u8 == SHORT_PRESS_RELEASED)
    {
        // Switch to next mode if clock mode is inactive
        if (eclockMode == CLOCK_MODE_INACTIVE) 
        {
            vModeSwitchToNext();
            printf("mode short press\r\n");
            
        }
        if(eclockMode == CLOCK_MODE_ACTIVE)
        {
           Button_Push_Event_T mode_status = getModeButtonStatus();
           clockSettingGetSetMode();

              
        }
        // Reset Mode Button Status
        l_Mode_ButtonEvent_Status_u8 = 0xFF;
    }
    // Check if reset button is short-pressed
    else if (l_Reset_ButtonEvent_Status_u8 == SHORT_PRESS_RELEASED)
    {
         if (eclockMode == CLOCK_MODE_INACTIVE)
         {
                    // Reset trip values based on current mode
               if (xGetDriverInforMenu() == TASK_TRIP_ODO_A ) 
               {
                   printf("Reset short press - Trip A Reset\r\n");

                   l_Reset_ButtonEvent_Status_u8= 0xFF;
               }
               if( xGetDriverInforMenu() == TASK_TRIP_ODO_B)
               {
                   l_Reset_ButtonEvent_Status_u8= 0xFF;
                   printf("Reset short press - Trip B Reset\r\n");

               }
             
         }
         if(eclockMode == CLOCK_MODE_ACTIVE)
         {
             clockSettingGetSetMode();
             Button_Push_Event_T reset_status = getResetButtonStatus();
             //printf("reset short press\r\n");
             l_Reset_ButtonEvent_Status_u8 = 0xFF;
         }
        
    }
    // Check if both mode and reset buttons are long-pressed
    else if (l_Mode_ButtonEvent_Status_u8 == LONG_PRESS_HELD && l_Reset_ButtonEvent_Status_u8 == LONG_PRESS_HELD)
    {

//    	printf("clock:%d\r\n",eclockMode);
        clockSettingRunMode(CLOCK_ENTRY);
        
        if (eclockMode == CLOCK_MODE_INACTIVE) 
        {
            clockSettingGetSetMode();      //Deciding clk action based on buttons inputs

            printf("mode and Reset Long press - Clock Setting mode\r\n");
            
            eclockMode = CLOCK_MODE_ACTIVE;
            l_button_Timeout_Start = HAL_GetTick(); // Reset the button timeout counter
            l_Mode_ButtonEvent_Status_u8 = 0xFF;
            l_Reset_ButtonEvent_Status_u8 = 0xFF;
            
        }
    }
    // Check if clock mode is active
    else if (eclockMode == CLOCK_MODE_ACTIVE)
    {
        // Increment button timeout counter if no button is pressed
        if (gl_mode_button_Push_Release_state_t == BUTTON_RELEASED && gl_reset_button_Push_Release_state_t == BUTTON_RELEASED)
        {
            l_button_Timeout_End= HAL_GetTick();
            l_button_Timeout = l_button_Timeout_End - l_button_Timeout_Start;
            // Check if the timeout threshold has been reached
            if (l_button_Timeout >= BUTTON_TIMEOUT_THRESHOLD)
            {
                printf("Clock Exit after time out\r\n");
                vClock_exit();
                // Exit clock setting mode due to timeout
                eclockMode = CLOCK_MODE_INACTIVE;
                l_button_Timeout = 0; // Reset the button timeout counter
            }
        }
    }
    if(l_Mode_ButtonEvent_Status_u8 == LONG_PRESS_HELD)
    {
        if(eclockMode == CLOCK_MODE_ACTIVE)
        {
            clockSettingGetSetMode();
            Button_Push_Event_T mode_status = getModeButtonStatus();

            l_Mode_ButtonEvent_Status_u8 = 0xFF;
        }
        
    }
    if(l_Reset_ButtonEvent_Status_u8 == LONG_PRESS_HELD)
    {
        if(eclockMode == CLOCK_MODE_ACTIVE)
        {
            clockSettingGetSetMode();
            Button_Push_Event_T reset_status = getResetButtonStatus();

            l_Reset_ButtonEvent_Status_u8 = 0xFF;
        }
        
    }
    if(l_Reset_ButtonEvent_Status_u8 == LONG_PRESS_RELEASED)
    {
    	if(eclockMode == CLOCK_MODE_ACTIVE)
		{
			clockSettingGetSetMode();
			Button_Push_Event_T reset_status = getResetButtonStatus();

			l_Reset_ButtonEvent_Status_u8 = 0xFF;
		}
    }
    // Reset button timeout and statuses if clock mode is active and any button is short-pressed
    if ((eclockMode == CLOCK_MODE_ACTIVE) && (l_Mode_ButtonEvent_Status_u8 == SHORT_PRESS_HELD || l_Reset_ButtonEvent_Status_u8 == SHORT_PRESS_HELD))
    {
         l_button_Timeout = 0;
		 l_button_Timeout_End = HAL_GetTick();
         l_button_Timeout_Start = HAL_GetTick();
         l_Mode_ButtonEvent_Status_u8 = 0xFF;
         l_Reset_ButtonEvent_Status_u8 = 0xFF;
    }
}





#endif /* SWITCH_HANDLER_C */
