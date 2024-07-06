/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file Indicator_App.c
 *
 * @brief Indicator_App file
 *
 * File Short Name: IndicatorApp
 *
 * @author: _________
 *
 * @date: ________
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/
/*
 * File:   Indicator_App.c
 * Author: Roja_Ramani
 *
 * Created on April, 2024,
 */
#ifndef INDICATOR_C
#define	INDICATOR_C
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "Indicator_App.h"
#include "IGN_SmHandler.h"
#include "Tachometer_App.h"
#include "CAN_App.h"
#include <stdint.h>

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**
 * Template example MACRO definition.
 * All MACROS should be in CAPITAL LETTERS ONLY
 */

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/


CAN_RxMessage_t  CANRxdata;

/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief Intilaize the indicator.
 *
 * @param[in] None
 *
 * @param[out] None
 *
 * @return None
 *
 */
void vIndicatorsInit(void)
{

	Status.Indicator_status = 0;
}
/**
 * @brief This function is used to update the indicators status for every 50ms.
 *
 * @param[in] None
 *
 * @param[out] None
 *
 * @return None
 *
 */
void vIndicator_App_Task(void)
{
     uint8_t usIgnition_State;
     /**:Get signal status from CAN bus;*/
     CANRxdata = Get_SignalStatus();
     /**:Get current ignition state;*/
	 usIgnition_State = usIgnitionGetCurrentState();
	 /**check if the IGN status is ON mode*/
    if(usIgnition_State  == IgnON_mode)
	{
    	/**:Update indicator statuses based on received CAN signals;*/
		Status.indicators.right_indicator             = CANRxdata.flags.Signal_1;
		Status.indicators.left_indicator              = CANRxdata.flags.Signal_2;
		Status.indicators.parking_indicator           = CANRxdata.flags.Signal_3;
		Status.indicators.HighBeam_indicator          = CANRxdata.flags.Signal_4;
		Status.indicators.LowBeam_indicator           = CANRxdata.flags.Signal_5;
		Status.indicators.engine_oil_temp_indicator   = CANRxdata.flags.Signal_6;
		Status.indicators.seat_belt_indicator         = CANRxdata.flags.Signal_7;
		Status.indicators.engine_malfunction_indicator= CANRxdata.flags.Signal_8;
		Status.indicators.door_open_indicator         = CANRxdata.flags.Signal_9;
		Status.indicators.abs_warning_indicator       = CANRxdata.flags.Signal_10;
	    Status.indicators.FaultyRight_indicator       = CANRxdata.flags.Signal_11;
	    Status.indicators.FaultyLeft_indicator	      =	CANRxdata.flags.Signal_12;

     }
#if(Indicator_Macro == 1)
       printf("Indicator_status: %x\r\n", Status.Indicator_status);
#endif
}




/**
 * @brief This function is used to get the indicator status.
 *
 * @param[in] None
 *
 * @param[out]None
 *
 * @return This function returns the indicator status.
 *
 */
IndicationStatus_t  xGetIndicatorstatus(void)
{
	return  Status;
}



#endif






























/**************************************************************************************************
 * End Of File
***************************************************************************************************/
