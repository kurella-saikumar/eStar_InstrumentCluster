/** \addtogroup DAMPING_ALGORITHM_USER_CONFIGURATION
 *  @{
 * @file damp_out_cfg.h
 *
 * @brief This following file contains the configuration parameters and input parameters of the damping algorithm.  
 *
 * File Short Name:  damp_out_cfg
 *
 * Author: ADITHYA POTU
 *
 * Create Date: 27-NOV-2021
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************@}*/

#ifndef _DAMP_OUT_CFG_H    /* Guard against multiple inclusion */
#define _DAMP_OUT_CFG_H 

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "FuelGuage_App.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**/
#define DEFAULT_DAMPED_OUTPUT_CONFIG \
0,\
/*0,\
0*/


/**
 * The base counter for the MIN_TIME is the periodicity and Max_Step_Size is the change in steps at which
 * the "Damp_Out" is called by the application */
/*{ Min_Time , Max_Step_Size}*/
#define INPUT_CONFIG \
{MinTimeValue, MaxStepSizeValue},
/*{10, 15},\
 {10, 20}, \
 {10, 10} */
 /**
 *  Declaration of  the three input levels
 */
#define INPUT_POINTERS_LIST \
&gl_Current_FuelLevel_u16,      /** Pointer to 16-bit value of the Input 1*/\
/*&temp_inp_level,*/        /** Pointer to 16-bit value of the Input 2*/\
/*&obstacle_inp_level,*/  /** Pointer to 16-bit value of the Input 3*/\

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
extern uint16_t gl_Current_FuelLevel_u16;        /**extern variable to 16-bit value of the Input 1*/
/*extern uint16_t temp_inp_level;*/              /** extern variable to 16-bit value of the Input 2*/
/*extern uint16_t obstacle_inp_level;*/          /** extern variable to 16-bit value of the Input 3*/



 
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/


#endif /* _DAMP_OUT_CFG_H  */

/* *****************************************************************************
 End of File
 */
