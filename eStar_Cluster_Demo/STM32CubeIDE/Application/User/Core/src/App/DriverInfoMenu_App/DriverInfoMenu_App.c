/** \addtogroup DRIVER_INFO_MENU
 *  @{
 * @file DriverInfoMenu.c
 *
 * @brief 
 *
 * File Short Name: DriverInfoMenu
 *
 * @author: Govindraj
 *
 * @date: 
 *
 * @copyright  
 * All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 * ********************************************************************************************** @}*/
#ifndef DRIVER_INFO_MENU_C
#define DRIVER_INFO_MENU_C  /* Guard against multiple inclusion */


/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "../DriverInfoMenu_App/DriverInfoMenu_App.h"

#include "stdio.h"
#include "stdint.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
DriverInfoModeStatus_t eCurrentTask = TASK_RANGE; //eCurrentTask
DriverInfoModeStatus_t eButtonPressCount = TASK_RANGE; //eButtonPressCount


/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief Initializes the Driver Information Menu
 *
 * @param[in] None
 *
 * @param[out] None
 *
 * @return None
 *
 */
void vDriverInfoMenu_Init(void) 
{
	vSetDriverInforMenu(TASK_RANGE);
    
}
		


/**
 * @brief Switches to the next mode
 *
 * This function switches to the next mode based on the mode switch status.
 * It increments the current task and handles task wrapping around if it exceeds TASK_TRIP_ODO_B.
 *
 * @return None
 *
 */


void vModeSwitchToNext(void)
{
        // Increment the current task
	eButtonPressCount++;

        if(eButtonPressCount >= TASK_NONE)
        {
        	eButtonPressCount = TASK_RANGE;
        }

        // Handle each task case
        switch (eButtonPressCount)
        {
            case TASK_RANGE: // Add a case for TASK_RANGE
                vSetDriverInforMenu(TASK_RANGE); // Set current task to TASK_RANGE
#if(DriverInfoMenuApp_TestMacro == 1)
                printf("mode press 5 = Range\r\n");
#endif
               // while(SERCOM4_USART_Write(mode_press5,sizeof(mode_press5))==false);
                break;
            case TASK_AVS:
                //current_task = TASK_AVS; // Set current task to TASK_AVS
                vSetDriverInforMenu(TASK_AVS);
#if(DriverInfoMenuApp_TestMacro == 1)
                printf("mode press 1 = AVS\r\n");
#endif
              //  while(SERCOM4_USART_Write(mode_press1,sizeof(mode_press1))==false);
                break;
            case TASK_AFE:
                vSetDriverInforMenu(TASK_AFE); // Set current task to TASK_AFE
#if(DriverInfoMenuApp_TestMacro == 1)
                printf("mode press 2 = AFE\r\n");
#endif
              //  while(SERCOM4_USART_Write(mode_press2,sizeof(mode_press2))==false);
                break;                
            case TASK_TRIP_ODO_A:
                vSetDriverInforMenu(TASK_TRIP_ODO_A); // Set current task to TASK_TRIP_ODO_A
#if(DriverInfoMenuApp_TestMacro == 1)
                printf("mode press 3 = Trip A\r\n");
#endif
              //  while(SERCOM4_USART_Write(mode_press3,sizeof(mode_press3))==false);
                
                break;
            case TASK_TRIP_ODO_B:
                vSetDriverInforMenu(TASK_TRIP_ODO_B); // Set current task to TASK_TRIP_ODO_B
#if(DriverInfoMenuApp_TestMacro == 1)
                printf("mode press 4 = Trip B\r\n");
#endif
               // while(SERCOM4_USART_Write(mode_press4,sizeof(mode_press4))==false);
                break;
            default:
                // Handle unexpected cases
                break;
        }
}


/**
 * @brief Retrieves the current driver information menu status.
 *
 * @return The current driver information menu status.
 */
DriverInfoModeStatus_t xGetDriverInforMenu(void)
{
#if(DriverInfoMenuApp_TestMacro == 1)
	printf("DriverInfoMode=%d\n",eCurrentTask);
#endif
    return eCurrentTask;
    
}

/**
 * @brief Sets the driver information menu status to the specified value.
 *
 * @param MenuSetItem The value to set the driver information menu status to.
 */
void vSetDriverInforMenu(DriverInfoModeStatus_t MenuSetItem)
{
	eCurrentTask = MenuSetItem;
}

#endif /* DRIVER_INFO_MENU_C */
