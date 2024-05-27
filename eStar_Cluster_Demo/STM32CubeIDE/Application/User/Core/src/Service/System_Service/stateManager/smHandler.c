/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file smHandler.c
 *
 * @brief Template Source File
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
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "smHandler.h"
#include "smHandler_cfg.h"
#include "stm32h7xx_hal.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

#define NUM_STATE_MACHINES (sizeof(l_stateMachine_List_a)/sizeof(State_Machine_T))

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**
 * @brief Structure definition of a 'State Machine'
 **************************************************************************************************/
typedef struct
{
    states_SM sm_default_state_u16;
    const transition_T * st_transition_list_a;
} State_Machine_T;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/**
 * @brief List of State machines being executed, each one with its Default state information and a constant list of supported transitions
 **********************************************************************************************************************************/
static const State_Machine_T l_stateMachine_List_a[] = 
{
	STATE_MACHINES_CONFIG,
};

/**
 * @brief Stores the Active state information of each state machine
 ********************************************************************/
static states_SM l_sm_active_state_u16[NUM_STATE_MACHINES];

states_SM SM_get_current_state(uint8_t l_Ign_SM_INDEX)
{
    return (l_sm_active_state_u16[l_Ign_SM_INDEX]);
}
                                                                                                       
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/ 

void State_Manager_init(void)
{
	uint8_t fl_num_of_SMs_u8;
	/** @startuml */ /** start */
    /** :Set the State machine's active state to the default state provided in the State machine configuration; */
	for(fl_num_of_SMs_u8 = 0; fl_num_of_SMs_u8 < NUM_STATE_MACHINES; fl_num_of_SMs_u8++)
	{
		l_sm_active_state_u16[fl_num_of_SMs_u8] = l_stateMachine_List_a[fl_num_of_SMs_u8].sm_default_state_u16;
	}
	/** end*/ /** @enduml */
}
/**
 * @brief Checks if any of the State Transitions configured for the StateMachin'e active state need to be executed \n
 * If the transition check return true, it calls the configured callback function (transition action) for the transition \n
 * 
 * @param void none
 *
 * @return void 
 ***************************************************************************************************/
void State_Manager_task(void)
{   
   uint8_t fl_sm_index_u8;
   states_SM fl_active_state_u16;
   
   uint8_t fl_trans_index_u8 = 0;   
   const transition_T *fl_trans_list_sm;

   for(fl_sm_index_u8 = 0; fl_sm_index_u8 < NUM_STATE_MACHINES; fl_sm_index_u8++)
   {       
       /** @startuml */ /** start */
       /** :Get the Active state of the state machine; */
       fl_active_state_u16 = l_sm_active_state_u16[fl_sm_index_u8];
	   
	   /** :Get the pointer to the transitions list of the state machine; */
	   fl_trans_list_sm = l_stateMachine_List_a[fl_sm_index_u8].st_transition_list_a;

       /** if(Transitions list pointer provided for the state machine != NULL?) then (TRUE);*/
       if(fl_trans_list_sm != NULL)
	   {
		   /** :Start from the first transition listed (Highest priority) i.e. transition_index = 0; */
		   fl_trans_index_u8 = 0;
		   /** while('in_state' of the transition != SM_STATE_INVALID ) is (Yes / Not the End of the Transitions list) */
		   while(SM_STATE_INVALID != fl_trans_list_sm[fl_trans_index_u8].in_state_u16)
		   {
				  HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_2);
			   /** if(state machine's active state is listed in the 'in_states' of the transition ?) then (TRUE/);*/
			   if((fl_active_state_u16 & fl_trans_list_sm[fl_trans_index_u8].in_state_u16) != 0)
			   {
				   /** if(state machine's active state != next_state of the transition) then (TRUE/ Not Same);*/
				   if(fl_active_state_u16 != fl_trans_list_sm[fl_trans_index_u8].next_state_u16)
				   {
					   /** if(transitionCheck function ptr != NULL?) then (TRUE);*/
					   if(NULL != fl_trans_list_sm[fl_trans_index_u8].TransitionCheck_fp)
					   {
						   /** if(transitionCheck function of the transition returned True?) then (TRUE);*/
						   if(fl_trans_list_sm[fl_trans_index_u8].TransitionCheck_fp())
						   {
							   /** :Execute the transition Action;*/
							   if(NULL != fl_trans_list_sm[fl_trans_index_u8].TransitionAction_fp)
							   {
								   fl_trans_list_sm[fl_trans_index_u8].TransitionAction_fp();
							   }
							   /** :Assign 'next_state' listed in the transition to SM_Active_State;*/
							   l_sm_active_state_u16[fl_sm_index_u8] = fl_trans_list_sm[fl_trans_index_u8].next_state_u16;
							   /** break */
							   break;                       
						   }
						   /** else (FALSE) */
						   /** endif */						   
					   }
					   /** else (FALSE) */
				       /** endif */					   
				   }
				   else
				   {
					   /**else (FALSE/Same)*/
					   /** :Execute In State Action; */
					   if(NULL != fl_trans_list_sm[fl_trans_index_u8].TransitionAction_fp)
					   {
						   fl_trans_list_sm[fl_trans_index_u8].TransitionAction_fp();
					   }
					   /** break */
					   break;    
				   }/** endif */           
			   }
			   /** else (FALSE/active state is not found in the 'in_states' of the transition) */
			   /** :Ignore the Transition;*/			   
			   /** :Go to the next transition listed for the state machine(Increment transition_index);*/
			   fl_trans_index_u8++;
			   /** endif */
		   }
		   /** endwhile (No)*/
	   }	   
	   /** else (FALSE) */
	   /** :Ignore the State machine;*/
	   /** endif */  
	   
       /** end*/ /** @enduml */
   }

}   
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
