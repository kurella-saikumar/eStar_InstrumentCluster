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

#include "eeprom_emul.h"
#include "Odometer_App.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "IGN_SmHandler.h"
#include "IGN_SmHandler_cfg.h"
#include "ICU_driver.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

void vIgnitionONFunc(void);
void vIgnitionOffFunc(void);
void vInIgnitionONFunc(void);
void vInIgnitionOffFunc(void);



/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
                                                                                                       
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/
extern void Disp_imgDataHyperRAM_Init(void);
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

void vIgnitionONFunc(void)
{
	printf("IGNON_STATE_OFF_TO_ON_ENTRY_Action\r\n");
	vEnable_OdoSpeedo_Channel_Interrupts();
	vEE_Demo();
	xRetrive_LastStored_OdoVal_from_EEPROM();
	Disp_imgDataHyperRAM_Init();
}

/**
 * @brief  IGNOFF_func function is to perform some action when the state changed to IGN_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vIgnitionOffFunc(void)
{
	 printf("IGNOFF_STATE_ON_TO_OFF_ENTRY_Action\r\n");
	 vDisable_OdoSpeedo_Channel_Interrupts();
}  

/**
 * @brief  in_IGNON_func function is to perform some action when the state remain in IGN_ON
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void vInIgnitionONFunc(void)
{
    //printf("IGN_STATE_in_IGNON_Action\r\n");
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

void vInIgnitionOffFunc(void)
{
    //printf("IGN_STATE_in_IGNOFF_Action\r\n");
    //printf("\nIGNOFF_To_IGNOFF_STATE\n");
} 

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
