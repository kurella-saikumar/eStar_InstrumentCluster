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
IndicationStatus_t   Status;


/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

/**
 * Purpose: Describe the purpose of the variable
 *
 * Unit: Boolean
 *
 * Resolution: 1 Bit
 *
 * Range: TRUE/FALSE
 *
 * Power On Init Value\Action: FALSE
 *
 * Wakeup Value\Action: FALSE
 *
 * Shutdown Value\Action: Don't Care
 *
 */



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

  if(usIgnitionGetCurrentState() == IgnON_mode)
	{

		Status.indicators.right_indicator    = RIGHTTURNINDICATOR_STATUS;
		Status.indicators.left_indicator     = LEFTTURNINDICATOR_STATUS;
		Status.indicators.parking_indicator  = PARKINGINDICATORS_STATUS;
		Status.indicators.HighBeam_indicator = HIGHBEAMINDICATOR_STATUS;
		Status.indicators.LowBeam_indicator  = LOWBEAMINDICATOR_STATUS;
		Status.indicators.engine_oil_temp_indicator   = ENGTEMPINDICATOR_STATUS ;
		Status.indicators.seat_belt_indicator        =  SEATBELTWARINDICATOR_STATUS ;
		Status.indicators.engine_malfunction_indicator  = ENGINEMALFUNCTION_STATUS;
		Status.indicators.door_open_indicator       = DOOROPENWARINDICATOR_STATUS;
		Status.indicators.abs_warning_indicator  =    ABSINDICATOR_STATUS;
	    Status.indicators.FaultyRight_indicator    =  FAULTYRIGHT_STATUS;
	    Status.indicators.FaultyLeft_indicator	  =	FAULTYLEFT_STATUS;

     }
}




/**
 * @brief This function is used to get the indicator status.
 *
 * @param[in] None
 *
 * @param[out] This function returns the indicator status.
 *
 * @return None
 *
 */
uint32_t  xGetIndicatorstatus(void)
{
	uint32_t  l_Indicator_Status=0;

	   l_Indicator_Status = Status.Indicator_status;

    return l_Indicator_Status;
}



#endif






























/**************************************************************************************************
 * End Of File
***************************************************************************************************/
