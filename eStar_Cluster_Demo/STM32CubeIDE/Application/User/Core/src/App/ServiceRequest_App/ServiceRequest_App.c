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
#include "string.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "main.h"
#include "ServiceRequest_App.h"
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
char *montharray[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
extern RTC_HandleTypeDef hrtc;
HAL_StatusTypeDef xMonthsElapsed;
RTC_DateTypeDef xvar;

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
 struct Service
 {
	 uint8_t month;
	 uint8_t date;
 };
 struct Service xservice;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/**************************************************************************************************
* Purpose: the purpose of ucTimeServiceFlag variable is to set or reset the flag.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucTimeServiceFlag;
/**************************************************************************************************
* Purpose: the purpose of ucDistanceServiceFlag variable is to set or reset the flag.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucDistanceServiceFlag;
/**************************************************************************************************
* Purpose: the purpose of ucInitialDay variable is to assign InitialDay.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucInitialDay;
/**************************************************************************************************
* Purpose: the purpose of ucInitialMonth variable is to assign the InitialMonth.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucInitialMonth;
/**************************************************************************************************
* Purpose: the purpose of ucCurrentDay variable is to assign the currentDay.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucCurrentDay;
/**************************************************************************************************
* Purpose: the purpose of ucCurrentMonth variable is to assign the currentMonth.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucCurrentMonth;
/**************************************************************************************************
* Purpose: the purpose of ucMonthcount variable is for counting the months.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucMonthcount;
/**************************************************************************************************
* Purpose: the purpose of ucFlagSetDay variable is to store the date when flag is reset.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucFlagSetDay;
/**************************************************************************************************
* Purpose: the purpose of ucDaypassed variable is to store the number of days passed after flag is set.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucDaypassed;
/**************************************************************************************************
* Purpose: the purpose of ucOdoVar variable is output parameter for xGetOdoReadings function. .
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucOdoVar;
/**************************************************************************************************
* Purpose: the purpose of ulLastServicePoint variable is to store the odo readings when reset the time service flag.
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
static uint32_t ulLastServicePoint;
/**************************************************************************************************
* Purpose: the purpose of ulDistancePassed variable is to store the distance passed after reset the distance flag.
*
* Unit: 32 bit
*
* Resolution: 1 Bit
*
* Range:  0 to  4,294,967,295
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint32_t ulDistancePassed;

/**************************************************************************************************
* Purpose: the purpose of ucMonthvar variable is to update the month.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucMonthvar = 0;
/**************************************************************************************************
* Purpose: the purpose of ulTotalDistance variable is to capture the odometer readings.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint32_t ulTotalDistance;
/**************************************************************************************************
* Purpose: the purpose of ucDaycount variable is to count the number of days.
*
* Unit: 8 bit
*
* Resolution: 1 Bit
*
* Range:  0 to 255
*
* Power On Init Value\Action: 0
*
* Wakeup Value\Action: 0
*
* Shutdown Value\Action: Don't Care
*
***************************************************************************************************/
static uint8_t ucDaycount = 1;

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
 /**************************************************************************************************
  * Function Name: vServiceRequestTask_Init
  *
  * Input Parameter: void
  *
  * Return Value: void
  *
  * Description:the vServiceRequestTask_Init function is to initialize the month and date.
  *
  ***************************************************************************************************/
 void vServiceRequestTask_Init(void)
 {
#if TimeBasedServiceDemo
	 /**:Run RTC demo application;*/
	 vRTCDemoApp();
	 memcpy(&xvar.Month,&xservice,sizeof(xservice));
	 /**:set the InitialDay;*/
	 ucInitialDay = 10 /*xvar.Date*/;
	 /**:set the InitialMonth;*/
	 ucInitialMonth = xvar.Month;

#else
	 /**:Read months elapsed from the RTC;*/
	 xMonthsElapsed = HAL_RTC_GetDate(&hrtc, &xvar, RTC_FORMAT_BIN);
	 if(xMonthsElapsed != HAL_OK)
	 {
		printf("HAL_RTC_GetDate failed: %d\r\n", xMonthsElapsed);
	 }
	 /**: Set initial day from RTC data;*/
	 ucInitialDay = xvar.Date;
	 /**: Set initial month from RTC data;*/
	 ucInitialMonth = xvar.Month;

#endif
 }

/**************************************************************************************************
 * Function Name: vServiceRequestTask
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description:the vServiceRequestTask function is to set or reset distance/time based service request indicator.
 *
 ***************************************************************************************************/

void vServiceRequestTask(void)
{
	/**:Get odometer readings;*/
	ulTotalDistance = xGetOdoReadings(&ucOdoVar);

#if (TimeBasedServiceDemo == 1)
	/**:Run RTC demo application and copy service data to month variable;*/
	vRTCDemoApp();
	memcpy(&xvar.Month,&xservice,sizeof(xservice));
#endif

#if(ServiceRequest_TestMacro == 1)
    //printf("TotalDistance-%ld\t, LastServicePoint-%ld\n",ulTotalDistance,ulLastServicePoint);
#endif

    /**Check if the distance traveled since last service exceeds the threshold*/
    if(ulTotalDistance - ulLastServicePoint >= configDISTANCE_THRESHOLD)
	{
    	/**Set distance service flag;*/
		ucDistanceServiceFlag = 1;
		/**:Update last service point;*/
		ulLastServicePoint = ulTotalDistance;
		/**:Update distance passed;*/
		ulDistancePassed = ulTotalDistance;

#if(ServiceRequest_TestMacro == 1)
            printf("DistanceServiceFlag is set\n");
#endif
     }
	else
	{
		/**:Update current day and month from RTC data;*/
		ucCurrentDay = xvar.Date;
		ucCurrentMonth = xvar.Month;
		/**Check if the day has changed since the initial day*/
		if (ucInitialDay == ucCurrentDay)
		{
			/**Check if the month has changed since the initial month*/
			if(ucInitialMonth != ucCurrentMonth)
			{
				/**Update initial month;*/
				ucInitialMonth = ucCurrentMonth;
				/**:Increment month count;*/
				ucMonthcount+=1;
				/**:Set flag for day change;*/
				ucFlagSetDay = ucCurrentDay;
			}
		}
		/**Check if the month count has reached the configured threshold*/
		if(ucMonthcount==configTIME_THRESHOLD)
		{
			/**:Set time service flag;*/
			ucTimeServiceFlag=1;

#if(ServiceRequest_TestMacro == 1)
			printf("TimeServiceFlag is set\n");
#endif
		}
	}

    if (ucDistanceServiceFlag)
    {
    	/**Check if distance traveled since last service exceeds the reset value*/
    	if (ulTotalDistance - ulDistancePassed >= configDISTANCE_RESET_VALUE)
		{
    		/**:Reset distance service flag;*/
			ucDistanceServiceFlag = false;
			/**:Update last service point;*/
			ulLastServicePoint = ulTotalDistance;

			/**:Reset month count;*/
			ucMonthcount=0;
			/**:Update initial day;*/
			ucInitialDay = ucCurrentDay;
			/**:Update initial month;*/
			ucInitialMonth = ucCurrentMonth;

#if(ServiceRequest_TestMacro == 1)
			 printf("DistanceServiceFlag reset is done \n");
#endif
		}
    }

    if (ucTimeServiceFlag)
    {
    	/**Calculate days passed since the flag was set*/
    	if(ucCurrentDay < ucFlagSetDay)
		{
			ucDaypassed = ucFlagSetDay - ucCurrentDay;
		}
		else
		{
			ucDaypassed = ucCurrentDay - ucFlagSetDay;
		}
    	/**Check if the configured wait time has elapsed*/
		if(ucDaypassed == configWAIT_TIME)
		{
			/**:Reset time service flag;*/
			ucTimeServiceFlag = 0;
			/**:Reset month count;*/
			ucMonthcount=0;
			/**:Update initial day;*/
			ucInitialDay = ucCurrentDay;
			/**:Update initial month;*/
			ucInitialMonth = ucCurrentMonth;

			/**:Update last service point;*/
			ulLastServicePoint = ulTotalDistance;


#if(ServiceRequest_TestMacro == 1)
			printf("TimeServiceFlag reset is done \n");
#endif
		}
    }
}

/**************************************************************************************************
 * Function Name: vGetSrvcReqStatus
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: the vGetSrvcReqStatus function is to provide the status of service_reminder_indicator to enable the service indicator
 *
 ***************************************************************************************************/

void vGetSrvcReqStatus(IndicationStatus_t* pucSrvcReq_Indictr, bool* p_Warning_status_bool)
{
    /**:Initialize warning status to false;*/
    *p_Warning_status_bool=false;
	if((ucTimeServiceFlag == 1)  || (ucTimeServiceFlag == 1) )
	{
		/**:Set warning status to true;*/
		*p_Warning_status_bool=true;
		/**:Update fuel warning indicator;*/
		pucSrvcReq_Indictr->indicators.service_reminder_indicator=1;
#if(ServiceRequest_TestMacro == 1)
		printf("indicattor:%d\n",pucSrvcReq_Indictr->indicators.service_reminder_indicator);
#endif

	}
}

/**************************************************************************************************
 * Function Name: vRTCDemoApp
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description:the vRTCDemoApp function is for update the dates and months for demo testing purpose.
 *
 ***************************************************************************************************/
void vRTCDemoApp(void)
{
    /**:Update the date in the service structure;*/
    xservice.date = ucDaycount;
    /**Check if the current day is the first day of the month*/
    if (ucDaycount == 1) {
        /**:Update the month in the service structure and increment the month variable;*/
        xservice.month = ucMonthvar;
        ucMonthvar++;
    }
    /**Check if the current day is the last day of the month*/
    if (ucDaycount == configLimitdays) {
        /**:Reset the day count to 0 to start a new month:*/
        ucDaycount = 0;
    }
    /**Check if the month count has reached 12 (December)*/
    if (ucMonthvar == 12) {
        /**:Reset the month count to 0 to start a new year;*/
        ucMonthvar = 0;
    }
    /**:Increment the day count for the next iteration;*/
    ucDaycount++;

#if (ServiceRequest_TestMacro == 1)
    //printf("Month: %s\t Day: %d\n", montharray[xservice.month], xservice.date);
#endif
}

