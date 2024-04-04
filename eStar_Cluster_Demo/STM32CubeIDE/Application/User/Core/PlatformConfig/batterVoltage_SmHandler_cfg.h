/** \addtogroup STATE_MACHINE_CONFIGURATION
 *  @{
 * @file batterVolatge_SmHandler_cfg.h
 *
 * @brief config file for batterVolatge_SmHandler_cfg
 *
 * File Short Name:batterVolatge_SmHandler_cfg 
 *
 * Author:k.saikumar
 *
 * Create Date: 08/07/2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef BATTERVOLTAGE_SM_HANDLER_CFG_H
#define	BATTERVOLTAGE_SM_HANDLER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "batterVoltage_SmHandler.h"


/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

#define BATTERVOLTAGE_MANAGER_DEFAULT_STATE  LOW_VOLTAGE_STATE


/*
*the defined macro "LV_ACTION_FUNC" that expands to LV_func().
* It is likely used to invoke or execute a function called LV_func()
*/
#define LV_ACTION_FUNC \
LV_func, \

/*
*the defined macro "IN_IGNCRANK_ACTION_FUNC" that expands to in_IGNCRANK_func().
* It is likely used to invoke or execute a function called in_IGNCRANK_func()
*/
#define NV_ACTION_FUNC \
NV_func, \

/*
*the defined macro "NV_ACTION_FUNC" that expands to HV_func().
* It is likely used to invoke or execute a function called HV_func()
*/
#define HV_ACTION_FUNC \
HV_func, \

/*
*the defined macro "ULV_ACTION_FUNC" that expands to ULV_func().
* It is likely used to invoke or execute a function called ULV_func()
*/
#define ULV_ACTION_FUNC \
ULV_func, \


/*
*the defined macro "IN_LV_ACTION_FUNC" that expands to in_LV_func().
* It is likely used to invoke or execute a function called in_LV_func()
*/
#define IN_LV_ACTION_FUNC \
in_LV_func, \

/*
*the defined macro "IN_NV_ACTION_FUNC" that expands to in_NV_func().
* It is likely used to invoke or execute a function called in_NV_func()
*/
#define IN_NV_ACTION_FUNC \
in_NV_func, \

/*
*the defined macro "IN_HV_ACTION_FUNC" that expands to in_HV_func().
* It is likely used to invoke or execute a function called in_HV_func()
*/
#define IN_HV_ACTION_FUNC \
in_HV_func, \

/*
*the defined macro "IN_UL_ACTION_FUNC" that expands to in_ULV_func().
* It is likely used to invoke or execute a function called in_ULV_func()
*/
#define IN_UL_ACTION_FUNC \
in_ULV_func, \


/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

#endif	/* BATTERVOLTAGE_SM_HANDLER_CFG_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

