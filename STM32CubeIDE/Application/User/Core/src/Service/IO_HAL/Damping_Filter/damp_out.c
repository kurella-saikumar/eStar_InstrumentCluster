/** \addtogroup  
 *  @{
 * @file damp_out.c
 *
 * @brief This file contains the following functions and process to apply changes in the multiple inputs in the form of arrays for getting damped output array
 *
 * File Short Name: damp_out 
 *
 * Author: ADITHYA POTU
 *
 * Date: 27-Nov-2021
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 *******************************************************************************@}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "stdio.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "damp_out.h"
#include "damp_out_cfg.h"
#include "FuelGuage_App.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
//#define MAX_INPUTS (sizeof(inp_list)/sizeof(inp_list[0]))

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**
 * Static pointer array that holds input pointer .
 */
static  uint16_t *inp_list[] = {INPUT_POINTERS_LIST};  /*input pointers array*/
/**
 * Structure that holds input thresholds .
 */
#if 0
typedef struct
{
    uint16_t Min_time;
    uint16_t Max_Step_Size;    
}Input_Thresholds_T;
#endif
/*Array of all the Inputs Thresholds*/
//const Input_Thresholds_T inp_thresholds[MAX_INPUTS] = {INPUT_CONFIG};
Input_Thresholds_T inp_thresholds[MAX_INPUTS] = {0};
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/*To hold the final damped state of each of the input type*/
static uint16_t p_Damp_Out_u16[MAX_INPUTS]={DEFAULT_DAMPED_OUTPUT_CONFIG};
/*Counter to count the Min_time for  each of the input type*/
//static uint16_t l_count_u16[MAX_INPUTS] = {0};
uint16_t l_count_u16[MAX_INPUTS] = {0};
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief This function checks the difference between given raw input and the damped output and updates the damped output instantaneously for every Minimum time  if required .  
 * 
 * @param[in] p_raw_input : -> Analog input that can change from 0 to 65535;
 * @param[in] p_Damp_Out_u16 :-> Damped output of the raw_input;
 * 
 * @return None
 *
 */
static const uint16_t *p_raw_input_u16;
static uint8_t p_index_u8;
void DAMP_OUT (void)
{ 
    //uint8_t buffer[50]={0};
    p_index_u8 = MAX_INPUTS;
    while(  p_index_u8> 0)
    {
       
        
        p_index_u8--;/*reading inputs from MAX_INPUTS to 0 */
         printf("counter %d\t",l_count_u16[p_index_u8]);
        /* Read from the input pointer table*/
        if(inp_list[p_index_u8] != NULL)
        {
            p_raw_input_u16 = inp_list[p_index_u8];		
		}
        if(*p_raw_input_u16 != p_Damp_Out_u16[p_index_u8] ) /*Checking if the Output matches the given input value*/
        {
            if(l_count_u16[p_index_u8]== inp_thresholds[p_index_u8].Min_time)/*Checking if Min Time is elapsed after the applying the previous change*/
            {
                /*apply change to implement dampOutput*/
                if(*p_raw_input_u16  > p_Damp_Out_u16[p_index_u8] )/*checking the greater value in input and damped output*/
                {
                    if((*p_raw_input_u16  -  p_Damp_Out_u16[p_index_u8] )>= (inp_thresholds[p_index_u8].Max_Step_Size))
                    {
                        p_Damp_Out_u16[p_index_u8] = (p_Damp_Out_u16[p_index_u8]  +  inp_thresholds[p_index_u8].Max_Step_Size );//increasing the output by the defined Max step size
                    }
                    else 
                    {
                        p_Damp_Out_u16[p_index_u8]  = (p_Damp_Out_u16[p_index_u8] + (*p_raw_input_u16 - p_Damp_Out_u16[p_index_u8])); //increasing the output to the given raw input.
                    }
                }
                else if(*p_raw_input_u16  < p_Damp_Out_u16[p_index_u8]) /*checking the greater value in input and damped output*/
                {
                    if((p_Damp_Out_u16[p_index_u8] - *p_raw_input_u16)>= inp_thresholds[p_index_u8].Max_Step_Size )
                    {
                        p_Damp_Out_u16[p_index_u8] = (p_Damp_Out_u16[p_index_u8] - inp_thresholds[p_index_u8].Max_Step_Size);//changing and decreasing the output.
                    }
                   else
                   {
                        p_Damp_Out_u16[p_index_u8]  = (p_Damp_Out_u16[p_index_u8] -(p_Damp_Out_u16[p_index_u8]- *p_raw_input_u16 ));//decreasing the output to the given raw input.
                   }
               }
                l_count_u16[p_index_u8]=0; //restart the timer after applying the change
            }
            else
            {
            /*waiting for Min time to elapse*/
                l_count_u16[p_index_u8]+=1;
            }
        }
        else
        {
                l_count_u16[p_index_u8]=0; //to make sure that counter always starts from 0 when the input is different from output.
        }
    }
          //sprintf((char *)l_buffer_u8A,"\nInput values : %d\t%d\t%d ; Counter values:%d\t%d\t%d ; OUTPUT_STATES:%d\t%d\t%d", *(inp_list[0]),*(inp_list[1]),*(inp_list[2]), l_count_u16[0],l_count_u16[1],l_count_u16[2], p_Damp_Out_u16[0], p_Damp_Out_u16[1], p_Damp_Out_u16[2]);
          //DEBUG_FORCE_PRINT(l_buffer_u8A);
}

/********************************************************************************
 * @brief This function is used to return damped output value.
 *  
 *
 * @return p_Damp_Out_u16;
 */
uint16_t Get_DAMP_OUT(uint8_t input_type)/*getting  the returned damped output value */

{
     uint16_t p_Damp_Out = 0 ;
	if(MAX_INPUTS > input_type)
	{
		p_Damp_Out = p_Damp_Out_u16[input_type];
	}
	return p_Damp_Out;/*getting  the returned damped output value */
}
/*******************************************************************************
 End of File
 */
