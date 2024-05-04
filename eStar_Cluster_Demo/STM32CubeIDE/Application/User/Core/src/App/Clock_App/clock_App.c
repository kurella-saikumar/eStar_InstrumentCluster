/** \addtogroup  Clock_App
 *  @{
 * @file Clock_App.c
 *
 * @brief This file contains software logic to edit the time and Date by using RTC module. 
 *
 * File Short Name: Clock
 *
 * Author: 
 *
 * Create Date: 
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/
#include<stdio.h>
#include "stdint.h"
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "clock_App.h"
#include "../Switch_Handler/SwitchHandler_App.h"
#include "main.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
typedef enum
{
	E_CLOCK_HOURS_POS,
	E_CLOCK_MINS_POS,
	E_CLOCK_INVALID_POS

}en_clockShiftingPositionType_t;

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/



/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
extern RTC_HandleTypeDef hrtc;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
uint8_t ulHours,ulMinutes;

uint8_t ulShiftingPosition = E_CLOCK_HOURS_POS;
/*
 * @brief Variable representing the RTC time.
 */
RTC_TimeTypeDef xTime;
/*
 * @brief Variable representing the RTC Date.
 */
RTC_DateTypeDef xDate;
/*
 * @brief To store the HAL function result.
 */
HAL_StatusTypeDef xRes;


RTC_TimeTypeDef xEditTime;

uint8_t ulContinousIncrement_flag;
/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief This function initializes the Time and date and sets the current time and date
 * 
 * @param[in] None
 *
 * @return None
 *
 ***************************************************************************************************/
void clock_Init(void)
{
	ulHours = xTime.Hours;
	ulMinutes = xTime.Minutes;
	HAL_RTC_GetTime(&hrtc, &xTime, RTC_FORMAT_BIN);
}



void vGet_Clock(void)
{
    xRes = HAL_RTC_GetTime(&hrtc, &xTime, RTC_FORMAT_BIN);
    if(xRes != HAL_OK)
    {
    	printf("HAL_RTC_GetTime failed: %d\r\n", xRes);
    }
    else
    {
    	//printf("DT: %02d:%02d \n", xTime.Hours, xTime.Minutes);
    }
    xRes = HAL_RTC_GetDate(&hrtc, &xDate, RTC_FORMAT_BIN);
    if(xRes != HAL_OK)
    {
    	printf("HAL_RTC_GetDate failed: %d\r\n", xRes);
    }
    else
    {
    	//printf("Current date: %02d-%02d-%04d\n", xDate.Date, xDate.Month, xDate.Year);
    }

}

void clockSettingRunMode(ClockEditActions_t clockSettingMode)
{
	switch (clockSettingMode)
	{
	case CLOCK_ENTRY:
	{
		printf("Clock Edit Mode Entry\n");
		HAL_RTC_GetTime(&hrtc, &xEditTime, RTC_FORMAT_BIN);
		ulHours = xEditTime.Hours;
		ulMinutes = xEditTime.Minutes;
		printf("Hours:%02d,Minutes:%02d \n", ulHours, ulMinutes);
	}
	break;
	case MODE_LONGPRESS:
	{
		vClock_exit();
	}
	break;
	case MODE_SHORTPRESS:
	{
		ulShiftingPosition++;
		if (ulShiftingPosition == E_CLOCK_INVALID_POS)
		{
			ulShiftingPosition = E_CLOCK_HOURS_POS;
		}
		else
		{
			/*do nothing*/
		}
	}
	break;
    case RESET_LONGPRESS_RELEASE:
        	ulContinousIncrement_flag = 0;
        	printf("Long Press Release\n\r");
        break;
    case RESET_LONGPRESS_HELD:
    	ulContinousIncrement_flag = 1;
    	printf("Long Press Held\n\r");
    break;
      case RESET_SHORTPRESS:
    	if (ulShiftingPosition == E_CLOCK_HOURS_POS)
    	{
			//Increment hours
			xEditTime.Hours++;
			// Ensure hours wrap around correctly
			xEditTime.Hours %= 24;
		}
        else if (ulShiftingPosition == E_CLOCK_MINS_POS)
        {
			// Increment minutes
			xEditTime.Minutes++;
			// Check if minutes reached 60
			if (xEditTime.Minutes == 60)
			{
				// Reset minutes to 0
				xEditTime.Minutes = 0;
				// Increment hours
//				xEditTime.Hours++;
				// Ensure hours wrap around correctly
//				xEditTime.Hours %= 24;
			}
			else
			{
				/*do nothing*/
			}
		}
       break;
       default:
    	   // Handle unknown mode
       break;
	}

}

void vClock_exit(void)
{
	printf("Exit Param: H: %d\tM: %d\n", xEditTime.Hours, xEditTime.Minutes);
	HAL_RTC_SetTime(&hrtc, &xEditTime, RTC_FORMAT_BIN);
	printf("Clock edit mode exit\n");
}

void ContinousIncrement(void)
{
	if (ulShiftingPosition == E_CLOCK_HOURS_POS)
	{
		// Increment hours
		xEditTime.Hours++;
		// Ensure hours wrap around correctly
		xEditTime.Hours %= 24;
		printf("ContinousIncrement_Hours:%d",xEditTime.Hours);
	}
	else if (ulShiftingPosition == E_CLOCK_MINS_POS)
	{
		// Increment minutes
		xEditTime.Minutes++;
		// Check if minutes reached 60
		if (xEditTime.Minutes == 60)
		{
			// Reset minutes to 0
			xEditTime.Minutes = 0;
				// Increment hours
			xEditTime.Hours++;
				// Ensure hours wrap around correctly
			xEditTime.Hours %= 24;
			printf("ContinousIncrement_Minutes:%d",xEditTime.Minutes);
		}
		else
		{
				/*do nothing*/
		}
	}
	else

	{
		/*do nothing*/
	}
}

void vClockIncreament(void)
{
	if(ulContinousIncrement_flag == 1)
	{
//		if (0 == xGetResetSwitch())
//		{
			ContinousIncrement();
			printf("ContinousIncrement success\n\r");
//		}
//		else
//		{
//			ulContinousIncrement_flag =0;
//			printf("Long press released1\n\r");
//		}
	}
	else
	{
		ulContinousIncrement_flag =0;
//		printf("Long press released2\n\r");
	}

}
/** end*/ /** @enduml */
/**************************************************************************************************
 * End Of File
***************************************************************************************************/



























	









































