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


/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "Switch.h"
#include "Switch_cfg.h"
#include "SwitchHandler_App.h"
#include "SwitchInf.h"
#include "stm32h7xx_hal.h"
#include "speedometer_App.h"
#include "Odometer_App.h"
#include "clock_App.h"

#include "../../../App/DriverInfoMenu_App/DriverInfoMenu_App.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
#define BUTTON_TIMEOUT_THRESHOLD 15000 // Timeout duration in seconds

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
uint8_t ucModeButtonEventStatus = 0xFF;
uint8_t ucResetButtonEventStatus = 0xFF;
uint8_t ucModeButtonStatus = 0;
uint8_t ucResetButtonStatus = 0;
uint8_t ToggleMetrics = ODO_IN_KM;








/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
 SwitchModesDisplay_t ToDisplay;
 ClockEditActions_t ClockEditing;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
Switch_PushRelease_State_T eModeButtonPushReleaseState = BUTTON_RELEASED;
Switch_PushRelease_State_T eResetButtonPushReleaseState = BUTTON_RELEASED;




extern ClockEditModeState_t eClockMode = CLOCK_MODE_INACTIVE; //eClockMode
// Define a timer variable to track the count since the last button press

uint32_t ulButtonTimeout = 0, ulButtonTimeoutStart = 0, ulButtonTimeoutEnd = 0;





/**
 * @brief In this function updating the control switch state
 *
 * @param[in] None
 *
 * @return None
 *
 ***************************************************************************************************/
void vModeButtonPressHandler(Button_Push_Event_T eModeButtonStatus) //vModeButtonPressHandler
{

	ucModeButtonEventStatus = eModeButtonStatus;
}

void vResetButtonPressHandler(Button_Push_Event_T eResetButtonStatus) //vResetButtonPressHandler
{

	ucResetButtonEventStatus = eResetButtonStatus;
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
	ucModeButtonStatus = xGetModeSwitch();
	ucResetButtonStatus = xGetResetSwitch();
    

    // Check if mode button is pressed
    if (ucModeButtonStatus == PRESSED)
    {
        // Update global mode button state to pushed
    	eModeButtonPushReleaseState = BUTTON_PUSHED;
    }
    else
    {
        // Update global mode button state to released
    	eModeButtonPushReleaseState = BUTTON_RELEASED;
    }
    
    // Check if reset button is pressed
    if (ucResetButtonStatus == PRESSED)
    {
        // Update global reset button state to pushed
    	eResetButtonPushReleaseState = BUTTON_PUSHED;
    }
    else
    {
        // Update global reset button state to released
    	eResetButtonPushReleaseState = BUTTON_RELEASED;
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
ClockEditModeState_t xGetClockMode(void)
{
    // Return the current clock mode stored in a local variable
    return eClockMode;
}


/**
 * @brief Handles actions based on mode and reset button presses.
 * 
 * This function processes the state of mode and reset buttons and performs
 * actions accordingly, such as toggling odometer units, switching modes,
 * and resetting trip values. It also manages the clock mode and button timeout.
 */

Button_Push_Event_T xGetModeButtonStatus(void)//xGetModeButtonStatus
{
    Button_Push_Event_T mode_status = 0xFF;
    if(eClockMode == CLOCK_MODE_ACTIVE)
    {
        mode_status = ucModeButtonEventStatus;
        
    }
    else
    {
        mode_status = 0xFF;
    }
    return mode_status;
    
}

ClockEditActions_t xClockSettingGetSetMode(void)
{
    Button_Push_Event_T eClkModeStatus = xGetModeButtonStatus(); //eClkModeStatus
    Button_Push_Event_T eClkResetStatus = xGetResetButtonStatus(); //eClkResetStatus
//    clockSettingRunMode(CLOCK_ENTRY);

     if(eClkModeStatus == SHORT_PRESS_RELEASED )
     {
#if (SWITCH_HANDLER_MACRO == 1)
         printf("Clock mode short press\r\n");
#endif
         clockSettingRunMode(MODE_SHORTPRESS);
         ClockEditing = MODE_SHORTPRESS;
     }
     else if(eClkModeStatus == LONG_PRESS_HELD)
     {
#if (SWITCH_HANDLER_MACRO == 1)
    	 printf("clock mode long press\r\n");
#endif

         clockSettingRunMode(MODE_LONGPRESS);
         ClockEditing = MODE_LONGPRESS;

     }
     else if(eClkResetStatus == SHORT_PRESS_RELEASED)
     {
#if (SWITCH_HANDLER_MACRO == 1)
         printf("clock reset short press\r\n");
#endif
         clockSettingRunMode(RESET_SHORTPRESS);

         ClockEditing = RESET_SHORTPRESS;
     }
     else if(eClkResetStatus == LONG_PRESS_RELEASED)
	  {
#if (SWITCH_HANDLER_MACRO == 1)
		  printf("clock reset long press release");
#endif
		  clockSettingRunMode(RESET_LONGPRESS_RELEASE);
		  ClockEditing = RESET_LONGPRESS_RELEASE;
	  }
     else if(eClkResetStatus == LONG_PRESS_HELD)
     {
#if (SWITCH_HANDLER_MACRO == 1)
         printf("clock reset long press held");
#endif
         clockSettingRunMode(RESET_LONGPRESS_HELD);
         ClockEditing = RESET_LONGPRESS_HELD;
     }
     else
     {

     }

	return 0;

}

Button_Push_Event_T xGetResetButtonStatus(void)//xGetResetButtonStatus
{
    Button_Push_Event_T reset_status = 0xFF;
    if(eClockMode == CLOCK_MODE_ACTIVE)
    {
        reset_status = ucResetButtonEventStatus;
        
    }
    else
    {
        reset_status = 0xFF;
    }
    return reset_status;
    
}


void vHandleModeResetActions(void)
{

    //printf("before pressing the switches : %d\n", ToggleMetrics );
    /***/

    // Check if both mode and reset buttons are short-pressed
    if (ucModeButtonEventStatus == SHORT_PRESS_RELEASED && ucResetButtonEventStatus == SHORT_PRESS_RELEASED)
    {
    	ucModeButtonEventStatus = 0xFF;
    	ucResetButtonEventStatus= 0xFF;
    	ToDisplay =ODO_METER_TOGGLE;
    	ToggleMetrics = xToggleUnits();

    	//vCustomizeSpeedUnits();


#if (SWITCH_HANDLER_MACRO == 1)
        printf("mode and reset short pressed - Odo Units toggle\r\n");
#endif
    }
    // Check if mode button is short-pressed 
    else if (ucModeButtonEventStatus == SHORT_PRESS_RELEASED)
    {
        // Switch to next mode if clock mode is inactive
        if (eClockMode == CLOCK_MODE_INACTIVE)
        {
            vModeSwitchToNext();
            ToDisplay =MENU_MODES;

#if (SWITCH_HANDLER_MACRO == 1)
            //printf("mode short press\r\n");
#endif
            
        }
        if(eClockMode == CLOCK_MODE_ACTIVE)
        {
           //Button_Push_Event_T mode_status = getModeButtonStatus();
        	xClockSettingGetSetMode();
        }
        // Reset Mode Button Status
        ucModeButtonEventStatus = 0xFF;
    }
    // Check if reset button is short-pressed
    else if (ucResetButtonEventStatus == SHORT_PRESS_RELEASED)
    {
         if (eClockMode == CLOCK_MODE_INACTIVE)
         {
                    // Reset trip values based on current mode
               if (xGetDriverInforMenu() == TASK_TRIP_ODO_A ) 
               {
            	   ucResetButtonEventStatus= 0xFF;
            	   vResetTripA_OdoReadings();
#if (SWITCH_HANDLER_MACRO == 1)
                   printf("Reset short press - Trip A Reset\r\n");
#endif
               }
               if( xGetDriverInforMenu() == TASK_TRIP_ODO_B)
               {
            	   ucResetButtonEventStatus= 0xFF;
            	   vResetTripB_OdoReadings();
#if (SWITCH_HANDLER_MACRO == 1)
                   printf("Reset short press - Trip B Reset\r\n");
#endif
               }
             
         }
         if(eClockMode == CLOCK_MODE_ACTIVE)
         {
        	 xClockSettingGetSetMode();
//             Button_Push_Event_T reset_status = getResetButtonStatus();
             //printf("reset short press\r\n");
             ucResetButtonEventStatus = 0xFF;
         }
        
    }
    // Check if both mode and reset buttons are long-pressed
    else if (ucModeButtonEventStatus == LONG_PRESS_HELD && ucResetButtonEventStatus == LONG_PRESS_HELD)
    {

//    	printf("clock:%d\r\n",eclockMode);
        clockSettingRunMode(CLOCK_ENTRY);
        ClockEditing = CLOCK_ENTRY;
        ToDisplay =CLOCK_EDITING;
        
        if (eClockMode == CLOCK_MODE_INACTIVE)
        {
        	xClockSettingGetSetMode();      //Deciding clk action based on buttons inputs
#if (SWITCH_HANDLER_MACRO == 1)
            printf("mode and Reset Long press - Clock Setting mode\r\n");
#endif
            
            eClockMode = CLOCK_MODE_ACTIVE;
            ulButtonTimeoutStart = HAL_GetTick(); // Reset the button timeout counter
            ucModeButtonEventStatus = 0xFF;
            ucResetButtonEventStatus = 0xFF;
            
        }
    }
    // Check if clock mode is active
    else if (eClockMode == CLOCK_MODE_ACTIVE)
    {
        // Increment button timeout counter if no button is pressed
        if (eModeButtonPushReleaseState == BUTTON_RELEASED && eResetButtonPushReleaseState == BUTTON_RELEASED)
        {
        	ulButtonTimeoutEnd= HAL_GetTick();
            ulButtonTimeout = ulButtonTimeoutEnd - ulButtonTimeoutStart;
            // Check if the timeout threshold has been reached
            if (ulButtonTimeout >= BUTTON_TIMEOUT_THRESHOLD)
            {
#if (SWITCH_HANDLER_MACRO == 1)
                printf("Clock Exit after time out\r\n");
#endif
                vClock_exit();
                // Exit clock setting mode due to timeout
                eClockMode = CLOCK_MODE_INACTIVE;
                ulButtonTimeout = 0; // Reset the button timeout counter
            }
        }
    }
    if(ucModeButtonEventStatus == LONG_PRESS_HELD)
    {
        if(eClockMode == CLOCK_MODE_ACTIVE)
        {
        	xClockSettingGetSetMode();
            //Button_Push_Event_T mode_status = getModeButtonStatus();

            ucModeButtonEventStatus = 0xFF;
        }
        
    }
    if(ucResetButtonEventStatus == LONG_PRESS_HELD)
    {
        if(eClockMode == CLOCK_MODE_ACTIVE)
        {
        	xClockSettingGetSetMode();
            //Button_Push_Event_T reset_status = getResetButtonStatus();

            ucResetButtonEventStatus = 0xFF;
        }
        
    }
    if(ucResetButtonEventStatus == LONG_PRESS_RELEASED)
    {
    	if(eClockMode == CLOCK_MODE_ACTIVE)
		{
    		xClockSettingGetSetMode();
			//Button_Push_Event_T reset_status = getResetButtonStatus();
			ucResetButtonEventStatus = 0xFF;
		}
    }
    // Reset button timeout and statuses if clock mode is active and any button is short-pressed
    if ((eClockMode == CLOCK_MODE_ACTIVE) && (ucModeButtonEventStatus == SHORT_PRESS_HELD || ucResetButtonEventStatus == SHORT_PRESS_HELD))
    {
    	ulButtonTimeout = 0;
    	ulButtonTimeoutEnd = HAL_GetTick();
		 ulButtonTimeoutStart = HAL_GetTick();
         ucModeButtonEventStatus = 0xFF;
         ucResetButtonEventStatus = 0xFF;
    }
}


SwitchModesDisplay_t xGetSwitchStatus(void)
{
#if (SWITCH_HANDLER_MACRO == 1)
	printf("todisplay=%d\n",ToDisplay);
#endif
	return ToDisplay;

}

uint8_t xGetToggleMetrics(void)
{
#if (SWITCH_HANDLER_MACRO == 1)
	printf("after pressing the switches : %d\n", ToggleMetrics );
#endif
	return ToggleMetrics;
}

uint8_t UserDriverUnits = 0;
uint8_t xToggleUnits(void)
{

    if(UserDriverUnits == ODO_IN_KM)
    {
    	UserDriverUnits = ODO_IN_MILES;
    }
    else
    {
    	UserDriverUnits = ODO_IN_KM;
    }
    return UserDriverUnits;
}



#endif /* SWITCH_HANDLER_C */
