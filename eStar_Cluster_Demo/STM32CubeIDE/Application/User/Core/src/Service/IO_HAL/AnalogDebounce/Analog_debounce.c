/** \addtogroup ANALOG_INPUT_DEBOUNCER
 *  @{
 * @file adcm.c
 *
 * @brief This file performs either multiple inputs analog de-bouncing
 * or single input de-bouncing based on the user's configuration
 *
 * @image html analogDebounce_thresholds.png
 * @image rtf analogDebounce_thresholds.png
 * File Short Name: adcm
 *
 * @author:Sandhya
 *
 * @date: 14-12-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ****************************************************************************************/
#ifndef ANALOG_DEBOUNCE_C
#define ANALOG_DEBOUNCE_C
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stddef.h>

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "Analog_debounce.h"
#include "Analog_debounce_cfg.h"
//#include "../../platform_includes.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
#define STATE_INVALID 0XFF
#define AD_MAX_NUM_INPUTS (sizeof(inp_array)/sizeof(inp_array[0]))
#define ANALOG_DEBOUNCE_STATE_0 0

// static AD_State_T Ramp_Up_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state);
static AD_State_T Ramp_Up_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state_index);

// static AD_State_T Ramp_Down_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state);
static AD_State_T Ramp_Down_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state_index);


/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/*List of pointers that point to the input values being checked in each task schedule*/
static uint32_t* inp_array[] = {INPUT_DATA_POINTERS};
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/*Structure that holds the ramp-up and ramp-down thresholds of each state*/
typedef struct{
	uint16_t ramp_up_entry_value;
	uint16_t ramp_down_entry_value;
	uint16_t ramp_up_debounce_counter;
	uint16_t ramp_down_debounce_counter;
}State_Parameters_T;
/*Structure that holds the all the state thresholds for each input type*/
typedef struct
{ 
	State_Parameters_T state_parameters[MAXIMUM_NUMBER_OF_STATES];     
} Input_Thresholds_T;

/*Array of All RampUp and RampDown Thresholds of all the Inputs*/

/**
 * @var Input_Thresholds_T inp_thresholds 
 * @brief constant array of thresholds for each input
 ***************************************************************************************************/

static const Input_Thresholds_T inp_thresholds[AD_MAX_NUM_INPUTS] = {ANALOG_DEBOUNCE_CONFIGURATION}};

/*To hold the final stable state of each of the input type*/
static AD_State_T current_state[AD_MAX_NUM_INPUTS] = {DEFAULT_STATE_CONFIGURATION};

/**
 * @brief  Does the debouncing for all the defined analog inputs and finalizes their states
 * 
 * @param void none
 *
 * @return void 
 ***************************************************************************************************/

void analog_debounce_task(void)
{
	uint8_t fl_loop_counter_u8 = 0;
	
	/* specifies the state from which the ramp-up or ramp-down check should happen for the input being checked... debouncing state OR the stable state*/
	AD_State_T base_state; 
	
	/* Temporary variable to store if the new identified state is different from the current state, for the input being checked...*/
	AD_State_T new_state_identified = STATE_INVALID; 
	
	/* To read the input value for the input type being checked */
	// static const uint16_t *p_input_analog_data_u16p; 
	static const uint32_t *p_input_analog_data_u32p;
	
	/* To store the state value that is currently under debounce, for each input type */
	static AD_State_T debouncing_state[AD_MAX_NUM_INPUTS];	

	/* To read the ramp-up/ramp-down counter constant of the current debouncing state, for later comparison with the debounce counter , for each of the input types */ 
	static uint16_t state_rampUp_Down_counter[AD_MAX_NUM_INPUTS];

	/* to hold the current state of the ramp-up/ramp-down debounce counter for each of the input types  */
	static uint16_t db_counter[AD_MAX_NUM_INPUTS];
		
	
	fl_loop_counter_u8 = AD_MAX_NUM_INPUTS;
	while(fl_loop_counter_u8 > 0)
	{
		fl_loop_counter_u8--;
		
		/** @startuml */ /** start */
		/** :Read the input signal value; */
		
		/* Read from the input pointer table*/
		if(NULL != inp_array[fl_loop_counter_u8])
		{
			// p_input_analog_data_u16p = inp_array[fl_loop_counter_u8];	
			p_input_analog_data_u32p = inp_array[fl_loop_counter_u8];	
		}
		
		/*New ramp-up or ramp-down detection should happen even while debouncing is in progress for any previously identified state... 
		Based on the stable 'current_state' - If debouncing is not in progress
		Based on the debouncing state - if debouncing is in progress...
		Debounce counter gets restarted in either case and counts till the new state's timer value.
		
		The possible cases are
		If there is a ramp-up debouncing in progress for a state, and a ramp-down is detected to a lower state OR a ramp-up is detected to another higher state....
		If there is a ramp-down debouncing in progress for a state, and a ramp-up is detected to an upper state OR a ramp-down is detected to another lower state... */
		
		/** if (debouncing in progress for the input) then (true)*/
        /** :base state = debouncing state; */
		/** else (false) */
		/** :base state = current stable state; */
		/** endif */
		base_state = ((STATE_INVALID != debouncing_state[fl_loop_counter_u8])? debouncing_state[fl_loop_counter_u8]: current_state[fl_loop_counter_u8]);
		 
		/*Check if there is any ramp-up for the given input from the base_state */
		/** :Ramp_Up_Check(input value, base state); */
		
		// new_state_identified = Ramp_Up_Check((*p_input_analog_data_u16p), fl_loop_counter_u8, base_state);	
		new_state_identified = Ramp_Up_Check((*p_input_analog_data_u32p), fl_loop_counter_u8, base_state);				
		if(MAXIMUM_NUMBER_OF_STATES > new_state_identified) /*If there is a ramp-up detected */
		{
			/** if (valid ramp-up state is identified) then (true)*/
			/** :debouncing state = new ramp_up state; */
			/** :debounce counter threshold = ramp-UP debounce counter value of the new state; */
			/** :Reset the debounce counter; */
			
			debouncing_state[fl_loop_counter_u8] = new_state_identified;
			/*Read the ramp-up counter value of the new state */		
			state_rampUp_Down_counter[fl_loop_counter_u8] = inp_thresholds[fl_loop_counter_u8].state_parameters[new_state_identified].ramp_up_debounce_counter;	
			/* debounce Counter restarted */
			db_counter[fl_loop_counter_u8] = 0; 			
		}
		else /* No ramp-up is detected */
		{
			/** else (false) */
			/** :Ramp_Down_Check(input value, base state); */
			
			/*Check if there is any ramp-down for the given input from the base_state */
			// new_state_identified = Ramp_Down_Check((*p_input_analog_data_u16p), fl_loop_counter_u8, base_state);
			new_state_identified = Ramp_Down_Check((*p_input_analog_data_u32p), fl_loop_counter_u8, base_state);
			if(MAXIMUM_NUMBER_OF_STATES > new_state_identified) /*If there is a ramp-down detected */	
			{
				/** if (valid ramp-down state is identified) then (true)*/
				/** :debouncing state = new ramp_down state; */
				/** :debounce counter threshold = ramp-DOWN debounce counter value of the new state; */
				/** :Reset the debounce counter; */
				debouncing_state[fl_loop_counter_u8] = new_state_identified;
				/*Read the ramp-down counter value of the new state */
				state_rampUp_Down_counter[fl_loop_counter_u8] = inp_thresholds[fl_loop_counter_u8].state_parameters[new_state_identified].ramp_down_debounce_counter;
				/* debounce Counter restarted */
				db_counter[fl_loop_counter_u8] = 0; 				
			}
			/** else (false) */
			/** endif */			
		}/*End of ramp-up or ramp-down detection */
		/** endif */
		
		/* If debouncing is already in progress or any new-ramp-up or ramp-down is detected for the input */
		if(STATE_INVALID != debouncing_state[fl_loop_counter_u8])
		{
			/** if (debouncing is already in progress or new ramp-up or ramp-down debouncing to be done) then (true)*/
			if(db_counter[fl_loop_counter_u8] >= state_rampUp_Down_counter[fl_loop_counter_u8] ) /*Counter reached the limit*/
			{
				/** if (debouncing counter reached the limit) then (true)*/
				/** :current stable state = debouncing state; */
				/** :debouncing state = STATE_INVALID; */
				/** :Stop Debounce counter; */
				current_state[fl_loop_counter_u8] = debouncing_state[fl_loop_counter_u8];

				/* Reset*/
				debouncing_state[fl_loop_counter_u8] = STATE_INVALID;   
				db_counter[fl_loop_counter_u8] = 0; /* Stop debounce timer */
			}
			else
			{
				/** else (false) */
				/** :Increment Debounce timer; */
				db_counter[fl_loop_counter_u8]++;
			}
			/** endif */
		}
		/** else (false) */
		/** :Stay in the current stable state; */
		/** endif */
			
	} /* End of While */
	
/** end*/ /** @enduml */
}

/**
 * @brief  To check if there is any ramp-up from the current stable state of the given input, to its higher states
 * 
 * @param [in] input_value The current input value \n
          Data type: uint16_t \n
          range : 0-65535 \n
		  resolution : 1
 * @param [in] input_index index indicating which input is being processed \n
          Data type: uint8_t \n
          range : 0- (AD_MAX_NUM_INPUTS-1) \n
		  resolution : 1
 * @param [in] input_base_state_index state_index of the base_state \n
          Data type: uint8_t \n
          range : 0- (MAXIMUM_NUMBER_OF_STATES-1) \n
		  resolution : 1
 * @param [out] None
 *
 * @return AD_State_T \n
 * index of the new state if a ramp-up is identified, returns 0xFF otherwise
 **********************************************************************************************************************/

/* returns STATE_INVALID if no ramp-up is detected from the base state, otherwise returns the new state index */
static AD_State_T Ramp_Up_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state_index)
{
	uint8_t state_index; /* index to loop through the state's limits*/
	uint8_t new_ramp_up_state = STATE_INVALID;
	
	/** @startuml */ /** start */
	/** if (input already in the highest possible state or Debouncing already started to the Highest state) then (false)*/
	
		/** :state_index = base state + 1;*/
		/** if(input value >= ramp_UP_entry_threshold of the state next to base state) then (ramp-up) */
		
		   /** repeat */
			
			/** if(input falls between the ramp_UP_entry_thresholds of the state at the state_index and the next higher state) then (TRUE);*/
			/** :new ramp-up state = state_index;*/
			/** else (FALSE) */
			/** :state_index = state_index + 1;*/
			/** endif */		
			
			/** repeat while (ramp-UP state NOT YET finalized) is (yes)*/
			/** ->no; */	
		
		/** :return the new ramp-up state;*/
		
		/** else (no ramp-up) */
		/** :return STATE_INVALID as the new ramp-up state;*/
		/** endif */		
	
	/** else (true)*/
	/** :return STATE_INVALID as the new ramp-up state;*/
	/** endif */
	
	/** end*/ /** @enduml */
	
	/* Check the range & validity of indices... and also there is no need to check for ramp-up if the base state is already the highest possible state */
	if((AD_MAX_NUM_INPUTS > input_index) && ((MAXIMUM_NUMBER_OF_STATES -1) > input_base_state_index))
	{		
		state_index = (input_base_state_index+1); /* Check from the immediate next state's ramp-up entry value */
		
		/* Check for ramp-up, '>=' ramp-up entry limit value included... Loop shoould not continue once the new ramp-up state is finalized */
		while((STATE_INVALID == new_ramp_up_state) && (MAXIMUM_NUMBER_OF_STATES > state_index) && (input_value >= inp_thresholds[input_index].state_parameters[state_index].ramp_up_entry_value))
		{
			if(state_index == (MAXIMUM_NUMBER_OF_STATES -1)) /* If LAST State reached*/
			{
#if ADCFG_STRICT_RANGE
				if(input_value <= inp_thresholds[input_index].state_parameters[state_index].ramp_down_entry_value)
				{
					new_ramp_up_state = state_index;
					/* Last state assigned only if the input value is strictly within the range defined */				
				}
				else
				{
					/*Consider NO Ramp-Up for out-of-range values*/
				}
#else
				new_ramp_up_state = state_index;
				/* Last state assigned for any value above the ramp-up entry value of the Last state, including the out-of-range values */
#endif			
			}
			/* Check if the input value is below the next state's ramp-up entry value */
			else if(input_value < inp_thresholds[input_index].state_parameters[state_index+1].ramp_up_entry_value)
			{
				new_ramp_up_state = state_index;				
			}
			else
			{
				/* ramp-up state not yet finalized... new_ramp_up_state remains as STATE_INVALID  */				
			}			
			state_index++;
		}		
	}	
	return new_ramp_up_state;
}

/**
 * @brief  To check if there is any ramp-down from the current stable state of the given input, to its lower states
 * 
 * @param [in] input_value The current input value \n
          Data type: uint16_t \n
          range : 0-65535 \n
		  resolution : 1
 * @param [in] input_index index indicating which input type is being processed \n
          Data type: uint8_t \n
          range : 0- (AD_MAX_NUM_INPUTS-1) \n
		  resolution : 1
 * @param [in] input_base_state_index index of the base_state \n
          Data type: uint8_t \n
          range : 0- (MAXIMUM_NUMBER_OF_STATES-1) \n
		  resolution : 1
 * @param [out] None
 *
 * @return AD_State_T \n
 * index of the new state if a ramp-down is identified, returns 0xFF otherwise
 ***************************************************************************************************************************/

/* returns STATE_INVALID if no ramp-down is detected from the base state, otherwise returns the new state index */
static AD_State_T Ramp_Down_Check(uint16_t input_value, uint8_t input_index, uint8_t input_base_state_index)
{	
	uint8_t state_index;	/* index to loop through the state's limits... */
	uint8_t new_ramp_down_state = STATE_INVALID;
		
	/** @startuml */ /** start */
	/** if (input already in the lowest possible state OR Debouncing already started to the Lowest state) then (false)*/
	
		/** :state_index = base state - 1;*/
		/** if(input value <= ramp_DOWN_entry_threshold of the state before the base state) then (ramp-down) */
		
			/** repeat */
			
			/** if(input falls between the ramp_DOWN_entry_thresholds of the state at the state_index and its immediate previous state) then (TRUE);*/
			/** :new ramp-DOWN state = state_index;*/
			/** else (FALSE) */
			/** :state_index = state_index - 1;*/
			/** endif */			
			
			/** repeat while (ramp-down state NOT YET finalized) is (yes)*/
			/** ->no; */			
			
		
		/** :return the new ramp-down state;*/
		
		/** else (no ramp-down) */
		/** :return STATE_INVALID as the new ramp-down state;*/
		/** endif */		
	
	/** else (true)*/
	/** :return STATE_INVALID as the new ramp-down state;*/
	/** endif */
	
	/** end*/ /** @enduml */
	
	/* Check the range & validity of indices... and also there is no need to check for ramp-down if the base state is already the lowest state */
	if((AD_MAX_NUM_INPUTS > input_index) && ( (MAXIMUM_NUMBER_OF_STATES > input_base_state_index) && (ANALOG_DEBOUNCE_STATE_0 < input_base_state_index)))
	{
		/* The state_index may need to be defined as signed int if the lowest state check is not made above */
		state_index = (input_base_state_index-1); /* check from the immediate previous state's ramp-down entry value...*/
		
		/* Check for ramp-down, '<=' ramp-down entry limit value included... Loop should not continue once the new ramp-down state is finalized...  */
		while( (STATE_INVALID == new_ramp_down_state)  && (MAXIMUM_NUMBER_OF_STATES > state_index) && (input_value <= inp_thresholds[input_index].state_parameters[state_index].ramp_down_entry_value))
		{ 
            if(ANALOG_DEBOUNCE_STATE_0 == state_index) /* If FIRST state reached */
			{
#if ADCFG_STRICT_RANGE
				if(input_value >= inp_thresholds[input_index].state_parameters[state_index].ramp_up_entry_value)
				{
					new_ramp_down_state = state_index;
					/* First state assigned only if the input value is strictly within the range defined */
				}
				else
				{
					/*Consider NO Ramp-down for out-of-range values */
				}
#else
				new_ramp_down_state = state_index; //1st state assigned i.e., ANALOG_DEBOUNCE_STATE_0
			    /* First state assigned for any value below the ramp-down entry value of the First state, including the out-of-range values */
#endif			
			}
			/* Check if the input value is above the previous state's ramp-down entry value */
			else if(input_value > inp_thresholds[input_index].state_parameters[state_index-1].ramp_down_entry_value)
			{
				new_ramp_down_state = state_index;				
			}
			else
			{
				/* ramp-down state not yet finalized... new_ramp_down_state remains as STATE_INVALID  */
			}	
			state_index--;
		}		
	}		
	return new_ramp_down_state;
}

/**
 * @brief  To read the current stable state of the given input
 * 
 * @param [in] inp_type index of the given input \n
          Data type : uint8_t \n
          range : 0- (AD_MAX_NUM_INPUTS-1) \n
		  resolution : 1
 * @param [out] None
 *
 * @return AD_State_T \n
 * state_index of the given input's stable state, returns 0xFF if the given input is not valid
 ***************************************************************************************************/

/*__reentrant*/ AD_State_T get_analog_debounce_state(uint8_t inp_type)
{
	AD_State_T out_state = STATE_INVALID;
	if(AD_MAX_NUM_INPUTS > inp_type)
	{
		out_state = current_state[inp_type];
	}
	return out_state;
}

#undef ANALOG_DEBOUNCE_C
#endif /*ANALOG_DEBOUNCE_C*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/






