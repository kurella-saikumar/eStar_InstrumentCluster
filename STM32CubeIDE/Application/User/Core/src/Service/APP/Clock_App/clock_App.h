/** \addtogroup  RKE_1527DECODER
 *  @{
 * @file clock_App.h
 *
 * @brief clock App external API header file 
 *
 * File Short Name: 
 *
 * Author: Sandhya
 *
 * Create Date: 
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef CLOCK_APP_H
#define	CLOCK_APP_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/


/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
//#include "clock_App_cfg.h"
//#include "definitions.h"
#include "../Switch_Handler/SwitchHandler_App.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
//extern struct tm sys_time;
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/


/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern void clock_Init(void);
//extern void vGet_Clock(struct tm CurrentTime);
extern void vGet_Clock(void);
extern void clockSettingRunMode(Clock_Edit_Actions clockSettingMode);
extern void vClock_exit(void);

#endif	/* RKE_HANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
