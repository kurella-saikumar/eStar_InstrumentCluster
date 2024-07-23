/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file Indicator_App.c
 *
 * @brief Indicator_App file
 *
 * File Short Name: IndicatorApp
 *
 * @author: Roja Ramani
 *
 * @date: 15 Apr 2024
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
#include "CAN_NIM.h"
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
CanRxStatus_t* l_IndicatorSignalStatus;
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

     /**:Get current ignition state;*/
	 usIgnition_State = usIgnitionGetCurrentState();
	 /**check if the IGN status is ON mode*/
    if(usIgnition_State  == IgnON_mode)
	{
    	/**:Update indicator statuses based on received CAN signals;*/
		Status.indicators.right_indicator             = vNim_get_indicator_status_right_indicator(l_IndicatorSignalStatus);
		Status.indicators.left_indicator              = vNim_get_indicator_status_left_indicator(l_IndicatorSignalStatus);
		Status.indicators.parking_indicator           = vNim_get_indicator_status_parking_indicator(l_IndicatorSignalStatus);
		Status.indicators.HighBeam_indicator          = vNim_get_indicator_status_highbeam_indicator(l_IndicatorSignalStatus);
		Status.indicators.LowBeam_indicator           = vNim_get_indicator_status_lowbeam_indicator(l_IndicatorSignalStatus);
		Status.indicators.engine_oil_temp_indicator   = vNim_get_indicator_status_engineoiltemperature_indicator(l_IndicatorSignalStatus);
		Status.indicators.seat_belt_indicator         = vNim_get_indicator_status_seatbelt_indicator(l_IndicatorSignalStatus);
		Status.indicators.engine_malfunction_indicator= vNim_get_indicator_status_enginemalfunction_indicator(l_IndicatorSignalStatus);
		Status.indicators.door_open_indicator         = vNim_get_indicator_status_doorsopen_indicator(l_IndicatorSignalStatus);
		Status.indicators.abs_warning_indicator       = vNim_get_indicator_status_abswarning_indicator(l_IndicatorSignalStatus);
	    Status.indicators.FaultyRight_indicator       = vNim_get_indicator_status_faultyright_indicator(l_IndicatorSignalStatus);
	    Status.indicators.FaultyLeft_indicator	      =	vNim_get_indicator_status_faultyleft_indicator(l_IndicatorSignalStatus);
	    Status.indicators.Engine_Oil_indicator	      =	vNim_get_indicator_status_engineoil_indicator(l_IndicatorSignalStatus);

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
