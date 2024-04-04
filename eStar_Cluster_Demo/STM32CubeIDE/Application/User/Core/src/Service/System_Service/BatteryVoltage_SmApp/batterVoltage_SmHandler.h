/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file batterVoltage_SmHandler.h
 *
 * @brief BatteryVoltage_StateManager Handler file performs the transition of different states of battery voltage.
 * and perform transition check and transition action functions.
 *
 * File Short Name:batterVoltage_SmHandler 
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
#ifndef BATTERY_VOLTAGE_SMHANDLER_H
#define	BATTERY_VOLTAGE_SMHANDLER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "smHandler.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define ULTRA_LOW_VOLTAGE_STATE SM_STATE_1
#define LOW_VOLTAGE_STATE       SM_STATE_2
#define NORMAL_VOLTAGE_STATE    SM_STATE_3
#define HIGH_VOLTAGE_STATE      SM_STATE_4


#define BATTERVOLTAGE_MODE_SM_INDEX 1
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

extern void HV_func(void);
extern void NV_func(void);
extern void LV_func(void);
extern void ULV_func(void);

extern void in_LV_func(void); 
extern void in_NV_func(void);
extern void in_HV_func(void);
extern void in_ULV_func(void);

extern const transition_T gl_batteryMode_SM_t[];

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

#endif	/* BATTERY_VOLTAGE_SMHANDLER_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

