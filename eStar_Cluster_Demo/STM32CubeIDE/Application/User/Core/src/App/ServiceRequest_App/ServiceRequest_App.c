/******************************************************************************************
 * Feature Name: ServiceRequest_App.c
 *
 * Feature Short Name: ServiceRequest_App
 *
 * Description:
 *
 * Author: Kurella Saikumar
 *
 * Create Date: 8th-April-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 *****************************************************************************************/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdint.h"
#include "Stdio.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
//#include "stm32h7xx_hal_rtc.h"
//#include "stm32h7xx_hal_def.h"
#include "main.h"
//#include "ServiceRequest_App.h"
#include "Odometer_App.h"
#include "ServiceRequest_App_Cfg.h"
#include "Odometer_App.h"
#include "Indicator_App.h"


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/**************************************************************************************************
 * Purpose: the purpose of ulOdoReading variable is to store the odo_meter reading.
 *
 * Unit: 32 bit
 *
 * Resolution: 1 Bit
 *
 * Range:  0 to 4,294,967,295
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
 uint32_t ulOdoReading;
 uint32_t ulInitialReading = 0;
 uint8_t  ucSrvcRequestFlag=0;
 uint32_t ulServiceRequestValue;
 uint8_t timeServiceFlag;
 uint8_t distanceServiceFlag;
 uint32_t lastServicePoint;
 uint32_t lastTimeReset;
 uint8_t InitialDay;
 uint8_t InitialMonth;
 uint32_t DistancePassed;
 uint8_t CurrentDay;
 uint8_t CurrentMonth;
 uint8_t Monthcount;
 uint8_t FlagSetDay;
 uint8_t Daypassed;
 uint8_t OdoVar;

 extern RTC_HandleTypeDef hrtc;
 HAL_StatusTypeDef monthsElapsed;
 RTC_DateTypeDef xvar;
/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * Purpose: A flag to that is used to mark if a request to change
 * availability has been received or not
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
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
 /**************************************************************************************************
  * Function Name: prvServiceRequestTask
  *
  * Input Parameter: void
  *
  * Return Value: void
  *
  * Description:
  *
  ***************************************************************************************************/
 void prvServiceRequestTask_Init(void)
 {
	 // Read months elapsed from the RTC

	  monthsElapsed = HAL_RTC_GetDate(&hrtc, &xvar, RTC_FORMAT_BIN);

	   if(monthsElapsed != HAL_OK)
	   {
		printf("HAL_RTC_GetDate failed: %d\r\n", monthsElapsed);
	   }
	   InitialDay = xvar.Date;
	   InitialMonth = xvar.Month;

 }
/**************************************************************************************************
 * Function Name: prvServiceRequestTask
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description:
 *
 ***************************************************************************************************/

void prvServiceRequestTask(void)
{
    // Read distance from the odometer
    uint32_t totalDistance = xGetOdoReadings(&OdoVar);
    printf("totalDistance-%ld\t, lastServicePoint-%ld\n",totalDistance,lastServicePoint);

    if(totalDistance - lastServicePoint >= DISTANCE_THRESHOLD)
        {
            distanceServiceFlag = 1; // Set distance service flag
            lastServicePoint = totalDistance;
            DistancePassed = totalDistance;
            printf("totalDistance-%ld\t, lastServicePoint-%ld\n",totalDistance,lastServicePoint);
            printf("distanceServiceFlag is set\n");
        }
	else
	{
		CurrentDay = xvar.Date;
		CurrentMonth = xvar.Month;

		if (InitialDay == CurrentDay)
		{
			if(InitialMonth != CurrentMonth)
			{
				InitialMonth = CurrentMonth;
				Monthcount+=1;
				FlagSetDay = CurrentDay;
			}
		}
		if(Monthcount==TIME_THRESHOLD)
		{
			timeServiceFlag=1;
		}
	}

    // Example usage: Check service flags and take appropriate action
    if (distanceServiceFlag)
    {
    	if (totalDistance - DistancePassed >= DISTANCE_RESET_VALUE)
		{
			 distanceServiceFlag = false;
			 lastServicePoint = totalDistance; // Update last service point
			 printf("distanceServiceFlag reset is done \n");
		}
    }

    if (timeServiceFlag)
    {
    	if(CurrentDay < FlagSetDay)
		{
			Daypassed = FlagSetDay - CurrentDay;
		}
		else
		{
			Daypassed = CurrentDay - FlagSetDay;

		}

		if(Daypassed == WAIT_TIME)
		{
			timeServiceFlag = 0;
			Monthcount=0;
			InitialDay = CurrentDay;
			InitialMonth = CurrentMonth;
		}
    }
}

//void checkServiceRequest(uint32_t totalDistance, RTC_DateTypeDef xTime)
//{
//    // Check if distance threshold is reached or exceeded
//    if (totalDistance - lastServicePoint >= DISTANCE_THRESHOLD)
//    {
//        distanceServiceFlag = true; // Set distance service flag
//        lastServicePoint = totalDistance;
//        DistancePassed = totalDistance;
//
//    }
//    else
//    {
//		CurrentDay = xTime.Date;
//		CurrentMonth = xTime.Month;
//
//		if (InitialDay == CurrentDay)
//		{
//			if(InitialMonth != CurrentMonth)
//			{
//				InitialMonth = CurrentMonth;
//				Monthcount+=1;
//				FlagSetDay = CurrentDay;
//			}
//		}
//		if(Monthcount==TIME_THRESHOLD)
//		{
//			timeServiceFlag=1;
//		}
//    }
//
//
//}

void vGetSrvcReqStatus(IndicationStatus_t* pucSrvcReq_Indictr, bool* p_Warning_status_bool)
{
    /**:Initialize warning status to false;*/
    *p_Warning_status_bool=false;
	if(ucSrvcRequestFlag == 1)
	{
		ucSrvcRequestFlag=0;
		/**:Set warning status to true;*/
		*p_Warning_status_bool=true;
		/**:Update fuel warning indicator;*/
		pucSrvcReq_Indictr->indicators.service_reminder_indicator=1;
		printf("indicattor:%d\n",pucSrvcReq_Indictr->indicators.service_reminder_indicator);

	}

}


