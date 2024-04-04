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

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
uint8_t Hours,Minutes;
uint8_t shiftingPosition = E_CLOCK_HOURS_POS;
RTC_TimeTypeDef time;
RTC_DateTypeDef date;
HAL_StatusTypeDef res;
extern RTC_HandleTypeDef hrtc;

RTC_TimeTypeDef editTime;

uint8_t gl_ContinousIncrement_flag;
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
//    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}



void vGet_Clock(void)
{
    Hours = time.Hours;
    Minutes = time.Minutes;
    res = HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    if(res != HAL_OK)
    {
    	printf("HAL_RTC_GetTime failed: %d\r\n", res);
    }
    else
    {
    	printf("DT: %02d:%02d \n", time.Hours, time.Minutes);
    }
    res = HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
    if(res != HAL_OK)
    {
    	printf("HAL_RTC_GetDate failed: %d\r\n", res);
    }
    else
    {
    	//printf("Current date: %02d-%02d-%04d\n", date.Date, date.Month, date.Year);
    }

}

void clockSettingRunMode(Clock_Edit_Actions clockSettingMode) {

//	gl_SwitchState = clockSettingMode;
    switch (clockSettingMode) {

        case CLOCK_ENTRY:
        {
        	printf("Clock Edit Mode Entry\n");
        	HAL_RTC_GetTime(&hrtc, &editTime, RTC_FORMAT_BIN);
            Hours = editTime.Hours;
            Minutes = editTime.Minutes;
            printf("%02d:%02d \n", Hours, Minutes);
        }
        break;

        case MODE_LONGPRESS:
        	vClock_exit();
            break;

        case MODE_SHORTPRESS:
            
            shiftingPosition++;
            if (shiftingPosition == E_CLOCK_INVALID_POS)
            {
                shiftingPosition = E_CLOCK_HOURS_POS;
            }
            break;
        case RESET_LONGPRESS:

        	gl_ContinousIncrement_flag = 1;
            break;
        case RESET_LONGPRESS_RELEASE:

        	gl_ContinousIncrement_flag = 0;
            break;
        case RESET_SHORTPRESS:
			if (shiftingPosition == E_CLOCK_HOURS_POS) {
				// Increment hours
				editTime.Hours++;
				// Ensure hours wrap around correctly
				editTime.Hours %= 24;
			} else if (shiftingPosition == E_CLOCK_MINS_POS) {
				// Increment minutes
				editTime.Minutes++;
				// Check if minutes reached 60
				if (editTime.Minutes == 60) {
					// Reset minutes to 0
					editTime.Minutes = 0;
					// Increment hours
					editTime.Hours++;
					// Ensure hours wrap around correctly
					editTime.Hours %= 24;
				}
			}
//            Hours = editTime.Hours;
//            Minutes = editTime.Minutes;
//            printf("%02d:%02d \n", Hours, Minutes);
            break;

        default:
            // Handle unknown mode
            break;
    }

}

void vClock_exit(void)
{
	printf("Exit Param: H: %d\tM: %d\n", editTime.Hours, editTime.Minutes);
	HAL_RTC_SetTime(&hrtc, &editTime, RTC_FORMAT_BIN);
	printf("Clock edit mode exit\n");
}

void ContinousIncrement(void)
{
	if (shiftingPosition == E_CLOCK_HOURS_POS)
	{// Increment hours
		editTime.Hours++;
		// Ensure hours wrap around correctly
		editTime.Hours %= 24;
	}
	else if (shiftingPosition == E_CLOCK_MINS_POS)
	{
		// Increment minutes
		editTime.Minutes++;
		// Check if minutes reached 60
		if (editTime.Minutes == 60)
		{
				// Reset minutes to 0
				editTime.Minutes = 0;
				// Increment hours
				editTime.Hours++;
				// Ensure hours wrap around correctly
				editTime.Hours %= 24;
		}
	}
}

void vClockIncreament(void)
{
	if(gl_ContinousIncrement_flag == 1)
	{
		ContinousIncrement();
//		gl_ContinousIncrement_flag =0;

	}
	else
	{
		/*do nothing*/
	}

}
/** end*/ /** @enduml */
/**************************************************************************************************
 * End Of File
***************************************************************************************************/



























	









































