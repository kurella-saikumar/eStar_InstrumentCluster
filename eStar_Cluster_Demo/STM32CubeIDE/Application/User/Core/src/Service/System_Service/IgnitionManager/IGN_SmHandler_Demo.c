/** \addtogroup  VDIO-STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler_Demo.c
 *
 * @brief IGN_StateManager Handler demo file perform action functions when transition occured
 *
 * File Short Name:IGN_SmHandler_Demo
 *
 * Author:T.Sivadhanalakshmi
 *
 * Create Date: 11/03/2024
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
#include "stdint.h"
#include "stdio.h"
// #include "stdbool.h"
//#include "types.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "IGN_SmHandler.h"
//#include "debug.h"
//#include "ACC_SmHandler_cfg.h"
#include "IGN_SmHandler_cfg.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

void IGNON_func(void);
void IGNOFF_func(void);
void in_IGNON_func(void);
void in_IGNOFF_func(void);



/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
                                                                                                       
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief  IGNON_func function is to perform some action when the state changed to IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void IGNON_func(void)
{
    printf("IGNON_STATE_ON_ENTRY_Action\r\n");
}

/**
 * @brief  IGNOFF_func function is to perform some action when the state changed to IGN_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void IGNOFF_func(void)
{
   printf("IGNOFF_STATE_OFF_ENTRY_Action\r\n");
}  

/**
 * @brief  in_IGNON_func function is to perform some action when the state remain in IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void in_IGNON_func(void)
{
    printf("IGN_STATE_in_IGNON_Action\r\n");
    //printf("\nIGNON_To_IGNON_STATE\n");
} 

/**
 * @brief  in_IGNOFF_func function is to perform some action when the state remain in IGN_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void in_IGNOFF_func(void)
{
    printf("IGN_STATE_in_IGNOFF_Action\r\n");
    //printf("\nIGNOFF_To_IGNOFF_STATE\n");
} 


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
