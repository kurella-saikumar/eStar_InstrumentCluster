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
*the defined macro "LV_ACTION_FUNC" that expands to vLVFunc().
* It is likely used to invoke or execute a function called vLVFunc()
*/
#define LV_ACTION_FUNC \
vLVFunc, \

/*
*the defined macro "IN_IGNCRANK_ACTION_FUNC" that expands to in_IGNCRANK_func().
* It is likely used to invoke or execute a function called in_IGNCRANK_func()
*/
#define NV_ACTION_FUNC \
vNVFunc, \

/*
*the defined macro "NV_ACTION_FUNC" that expands to vHVFunc().
* It is likely used to invoke or execute a function called vHVFunc()
*/
#define HV_ACTION_FUNC \
vHVFunc, \

/*
*the defined macro "ULV_ACTION_FUNC" that expands to vULVFunc().
* It is likely used to invoke or execute a function called vULVFunc()
*/
#define ULV_ACTION_FUNC \
vULVFunc, \


/*
*the defined macro "IN_LV_ACTION_FUNC" that expands to vInLVFunc().
* It is likely used to invoke or execute a function called vInLVFunc()
*/
#define IN_LV_ACTION_FUNC \
vInLVFunc, \

/*
*the defined macro "IN_NV_ACTION_FUNC" that expands to vInNVFunc().
* It is likely used to invoke or execute a function called vInNVFunc()
*/
#define IN_NV_ACTION_FUNC \
vInNVFunc, \

/*
*the defined macro "IN_HV_ACTION_FUNC" that expands to vInHVFunc().
* It is likely used to invoke or execute a function called vInHVFunc()
*/
#define IN_HV_ACTION_FUNC \
vInHVFunc, \

/*
*the defined macro "IN_UL_ACTION_FUNC" that expands to vInULVFunc().
* It is likely used to invoke or execute a function called vInULVFunc()
*/
#define IN_UL_ACTION_FUNC \
vInULVFunc, \


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

