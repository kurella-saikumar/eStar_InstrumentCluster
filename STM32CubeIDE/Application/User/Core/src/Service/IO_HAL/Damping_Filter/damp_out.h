/** \addtogroup  DAMPING_ALGORITHM
 *  @{
 * @file damp_out.h
 *
 * @brief This file performs either multiple raw input  damping
 * or single input damping based on the user's configuration.
 *
 * File Short Name: damp_out
 *
 * Author: ADITHYA POTU
 *
 * Date: 27-NOV-2021
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************@}*/

#ifndef _DAMP_OUT_H
#define _DAMP_OUT_H
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "damp_out_cfg.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define MAX_INPUTS (sizeof(inp_list)/sizeof(inp_list[0]))

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
typedef struct
{
    uint16_t Min_time;
    uint16_t Max_Step_Size;    
}Input_Thresholds_T;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
/**
 * @brief DAMP_OUT task function that shall Raw input
 * to be damped checks the difference between the raw input and damped Output on every execution for minimum time allowed.
 *
 * @param[in] p_raw_input_u16 -> Analog input that can change from 0 to 65535;
 *
 * @return void
 *
 */
extern void DAMP_OUT( void );
/**
 * @brief This function returns the damped output of the Raw input
 *
 * @param[in] void
 *
 * @return p_raw_input_u16
 *
 */
extern uint16_t Get_DAMP_OUT(uint8_t );


#endif /* _DAMP_OUT_H */

/*******************************************************************************
 End of File
 */

