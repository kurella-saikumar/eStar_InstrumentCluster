/** \addtogroup SWITCH
 *  @{
 * @file Switch.c
 *
 * @brief 
 *
 * File Short Name: Switch
 *
 * @author 
 *
 * @date: 
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/
#ifndef SWITCH_C
#define SWITCH_C
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

#include "Switch_cfg.h"
#include "switch.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

#define BUTTON_MAX (sizeof(inp_switch_array)/sizeof(inp_switch_array[0]))

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/*Structure that holds the minimum duration needed for a Short Press, Long Press, and Button Stuck detection on a button*/
typedef struct{
	uint16_t short_push_min_time_msec;   
	uint16_t long_push_min_time_msec;
	uint16_t stuck_button_min_time_msec;
}Button_Push_Durations_T;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/*List of pointers that point to the input values being checked in each task schedule*/
static Switch_PushRelease_State_T* inp_switch_array[] = {INPUT_SWITCH_POINTERS};

/*Array of All Button_state_Durations of all the Input switches*/
static const Button_Push_Durations_T inp_button_durations[BUTTON_MAX] = {SWITCH_PRESS_DURATION_CONFIGURATION};

#if SEPARATE_CALLBACK_FUNCTIONS
typedef void (*action_fptr)();
static action_fptr ShortPushHeld_Clbks[] = {SHORT_PUSH_HELD_CALLBACKS};
static action_fptr ShortPushReleased_Clbks[] = {SHORT_PUSH_RELEASED_CALLBACKS};
static action_fptr LongPushHeld_Clbks[] = {LONG_PUSH_HELD_CALLBACKS};
static action_fptr LongPushReleased_Clbks[] = {LONG_PUSH_RELEASED_CALLBACKS};
static action_fptr StuckBtn_Clbks[] = {BUTTON_STUCK_CALLBACKS};
#else

typedef void (*action_fptr)(Button_Push_Event_T);
static action_fptr ButtonPush_Clbks[] = {BUTTON_PUSH_NOTIFY_CALLBACKS};

#endif

/*
 * Declare the Variable For Status of the previous button state
 */
static Switch_PushRelease_State_T previous_button_state[BUTTON_MAX] = {BUTTON_RELEASED};
/*
 * Initialize the default input push counter 
 */
static uint32_t button_push_time[BUTTON_MAX] = {0};

/***************************************************************************/
/** @brief  Handling switch events */
/** @param  void none*/
/** @return none*/
/*******************************************************************************/

void Switch_Task(void)
{
	uint8_t fl_loop_counter_u8 = 0; 
	Switch_PushRelease_State_T p_button_input = BUTTON_RELEASED;
	
	fl_loop_counter_u8 = BUTTON_MAX;
	while(fl_loop_counter_u8 > 0)
	{
		fl_loop_counter_u8--;

//		current_debounced_state = get_analog_debounce_state(fl_loop_counter_u8);	
		
		/* Read from the input pointer table*/
		if(NULL != inp_switch_array[fl_loop_counter_u8])
		{
			p_button_input = *(inp_switch_array[fl_loop_counter_u8]);		
		}		
		
		if((BUTTON_PUSHED == p_button_input) && (UINT32_MAX != button_push_time[fl_loop_counter_u8]))
		{
			button_push_time[fl_loop_counter_u8]++;
			
			if(inp_button_durations[fl_loop_counter_u8].stuck_button_min_time_msec == button_push_time[fl_loop_counter_u8])
			{
                /**@startuml*/
                /**start*/
                /**:button pushed is button input;*/
                /**:button push time increments;*/
                
                /**if(button pressed for more than stuck_button_min_time_msec) then*/
                /**:Notify button STUCK;*/
                /**endif*/
                /**if(button released is current button state) then (button input)*/
                /**if(button is pressed for more than long_push_min_time_msec ) then*/
                /**:Notify LONG_Press;*/
                /**elseif(button is press for more than short_push_min_time_msec) then*/ 
                /**:Notify SHORT Press;*/
                /**endif*/
                /**else*/
                /**:No Button Press;*/
                /**endif*/
                /**stop*/
                /**@enduml*/            
				
				/* Callback for the STUCK Button Handler of the input switch */				
				#if SEPARATE_CALLBACK_FUNCTIONS
				if(NULL != StuckBtn_Clbks[fl_loop_counter_u8])
				{
					StuckBtn_Clbks[fl_loop_counter_u8]();
				}
				#else
				if(NULL != ButtonPush_Clbks[fl_loop_counter_u8])
				{
					ButtonPush_Clbks[fl_loop_counter_u8](BUTTON_STUCK);
				}
				#endif
			}
			else if(inp_button_durations[fl_loop_counter_u8].long_push_min_time_msec == button_push_time[fl_loop_counter_u8])
			{
				/*
				 * Long push is a one time notification, and is sent while the button is still pushed.
				 * This is not a continuous notification from the time the counter limit is reached.
				 * Even after notifying a Long Push event, counter should keep incrementing in order to successfully detect a Button stuck case
				 */
				
				/* Issue Callback for the LONG PUSH Handler of the input switch */
				#if SEPARATE_CALLBACK_FUNCTIONS
				if(NULL != LongPushHeld_Clbks[fl_loop_counter_u8])
				{
					LongPushHeld_Clbks[fl_loop_counter_u8]();
				}
				#else
				if(NULL != ButtonPush_Clbks[fl_loop_counter_u8])
				{
					ButtonPush_Clbks[fl_loop_counter_u8](LONG_PRESS_HELD);
				}
				#endif
			}
			else if(inp_button_durations[fl_loop_counter_u8].short_push_min_time_msec == button_push_time[fl_loop_counter_u8])
			{
				/*
				 * Short push is a one time notification, and is sent while the button is still pushed.
				 * This is not a continuous notification from the time the counter limit is reached.
				 * Even after notifying a Short Push event, counter should keep incrementing in order to successfully detect a long push or Button stuck case
				 */
					
				/* Issue Callback for the SHORT PUSH Handler of the input switch */
				#if SEPARATE_CALLBACK_FUNCTIONS
				if(NULL != ShortPushHeld_Clbks[fl_loop_counter_u8])
				{
					ShortPushHeld_Clbks[fl_loop_counter_u8]();
				}
				#else
				if(NULL != ButtonPush_Clbks[fl_loop_counter_u8])
				{
					ButtonPush_Clbks[fl_loop_counter_u8](SHORT_PRESS_HELD);
				}
				#endif
			}
			else
			{
				
			}
		}
		else if(BUTTON_RELEASED == p_button_input)
		{
			if(BUTTON_PUSHED == previous_button_state[fl_loop_counter_u8])
			{	
				if((button_push_time[fl_loop_counter_u8] >= inp_button_durations[fl_loop_counter_u8].long_push_min_time_msec) &&
				(button_push_time[fl_loop_counter_u8] < inp_button_durations[fl_loop_counter_u8].stuck_button_min_time_msec))
				{
					/*
					 * Long push is a one time notification based on the counter value, after the button is released.
					 * This is not a continuous notification from the time the counter limit is reached.
					 */
					
					/* Issue Callback for the LONG PUSH Handler of the input switch */
					#if SEPARATE_CALLBACK_FUNCTIONS
					if(NULL != LongPushReleased_Clbks[fl_loop_counter_u8])
					{
						LongPushReleased_Clbks[fl_loop_counter_u8]();
					}
					#else
					if(NULL != ButtonPush_Clbks[fl_loop_counter_u8])
					{
						ButtonPush_Clbks[fl_loop_counter_u8](LONG_PRESS_RELEASED);
					}
					#endif					
						
				}
				else if((button_push_time[fl_loop_counter_u8] >= inp_button_durations[fl_loop_counter_u8].short_push_min_time_msec) &&
				(button_push_time[fl_loop_counter_u8] < inp_button_durations[fl_loop_counter_u8].long_push_min_time_msec))
				{
					/*
					 * Short push is a one time notification based on the counter value, after the button is released.
					 * This is not a continuous notification from the time the counter limit is reached.
					 */
					
					/* Issue Callback for the SHORT PUSH Handler of the input switch */
					#if SEPARATE_CALLBACK_FUNCTIONS
					if(NULL != ShortPushReleased_Clbks[fl_loop_counter_u8])
					{
						ShortPushReleased_Clbks[fl_loop_counter_u8]();
					}
					#else
					if(NULL != ButtonPush_Clbks[fl_loop_counter_u8])
					{
						ButtonPush_Clbks[fl_loop_counter_u8](SHORT_PRESS_RELEASED);
					}
					#endif	
				}				
			}
			else
			{

			}
			/*
			 * Reset the Count after the notification
			 */
			button_push_time[fl_loop_counter_u8] = 0;
		}
		
	    previous_button_state[fl_loop_counter_u8] = p_button_input; 
			
	} /*End of While */		
}

#undef SWITCH_C
#endif /*SWITCH_C*/
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
