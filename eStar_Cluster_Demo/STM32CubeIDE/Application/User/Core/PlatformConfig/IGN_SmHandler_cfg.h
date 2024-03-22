/** \addtogroup VDIO-STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler_cfg.h
 *
 * @brief config file for IGN_SmHandler
 *
 * File Short Name:IGN_SmHandler_cfg
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
***************************************************************************************************/
#ifndef IGN_SM_HANDLER_CFG_H
#define	IGN_SM_HANDLER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "IGN_SmHandler.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

#define IGN_MANAGER_DEFAULT_STATE IgnON_mode

/*
*the defined macro "IGNON_ACTION_FUNC" that expands to IGNON_func().
* It is likely used to invoke or execute a function called IGNON_func()
*/
#define IGNON_ACTION_FUNC \
vIgnitionONFunc, \


/*
*the defined macro "IGNOFF_ACTION_FUNC" that expands to IGNOFF_func().
* It is likely used to invoke or execute a function called IGNOFF_func()
*/
#define IGNOFF_ACTION_FUNC \
vIgnitionOffFunc, \



/*
*the defined macro "IN_IGNON_ACTION_FUNC" that expands to in_IGNON_func().
* It is likely used to invoke or execute a function called in_IGNON_func()
*/
#define IN_IGNON_ACTION_FUNC \
vInIgnitionONFunc, \

        
/*
*the defined macro "IN_IGNOFF_ACTION_FUNC" that expands to in_IGNOFF_func().
* It is likely used to invoke or execute a function called in_IGNOFF_func()
*/
#define IN_IGNOFF_ACTION_FUNC \
vInIgnitionOffFunc, \

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

#endif	/* IGN_SM_HANDLER_CFG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

