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
#include "stdio.h"
#include "stdint.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "DriverInfoMenu_App.h"


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
   // ignition_status = xGetIgnitionStatus();
    //if (ignition_status) 
        //current_task = TASK_RANGE;
        vSetDriverInforMenu(TASK_RANGE);
    
}
		
//void vDriverInfoRegisterHandles(uint8_t *DriverInfoArray) 
//{	
//    *DriverInfoArray[TASK_RANGE] =	//&xGetDriverInfo(TASK_RANGE);
//    *DriverInfoArray[TASK_AVS]   =	//&xGetDriverInfo(TASK_AVS);
//    *DriverInfoArray[TASK_AFE]   =	//&xGetDriverInfo(TASK_AFE);
//    *DriverInfoArray[TASK_TRIP_ODO_A] =	//&xGetTripOdoAData();
//    *DriverInfoArray[TASK_TRIP_ODO_B] =	//&xGetTripOdoBData();
//}	

#define GET_DRIV_INFO_Range xGetDriverInfo(TASK_RANGE)
#define GET_DRIV_INFO_AVS xGetDriverInfo(TASK_AVS)
#define GET_DRIV_INFO_AFE xGetDriverInfo(TASK_AFE)
#define GET_DRIV_INFO_TripA xGetTripOdoAData()
#define GET_DRIV_INFO_TripB xGetTripOdoBData()

/**
 * @brief Switches to the next mode
 *
 * This function switches to the next mode based on the mode switch status.
 * It increments the current task and handles task wrapping around if it exceeds TASK_TRIP_ODO_B.
 *
 * @return None
 *
 */
char mode_press5[] = "mode press 5 = Range\r\n";
char mode_press1[] = "mode press 1 = AVS\r\n";
char mode_press2[] = "mode press 2 = AFE\r\n";
char mode_press3[] = "mode press 3 = Trip A\r\n";
char mode_press4[] = "mode press 4 = Trip B\r\n";

void vModeSwitchToNext(void)
{
        // Increment the current task
	eButtonPressCount++;
        // Check if the current task exceeds TASK_TRIP_ODO_B, and wrap around if necessary
//        if (current_task1 > TASK_TRIP_ODO_B) 
//        {
//            current_task1 = TASK_RANGE;
//        }
        if(eButtonPressCount >= TASK_NONE)
        {
        	eButtonPressCount = TASK_RANGE;
        }

        // Handle each task case
        switch (eButtonPressCount)
        {
            case TASK_RANGE: // Add a case for TASK_RANGE
                vSetDriverInforMenu(TASK_RANGE); // Set current task to TASK_RANGE
                printf("mode press 5 = Range\r\n");
               // while(SERCOM4_USART_Write(mode_press5,sizeof(mode_press5))==false);
                break;
            case TASK_AVS:
                //current_task = TASK_AVS; // Set current task to TASK_AVS
                vSetDriverInforMenu(TASK_AVS);
                printf("mode press 1 = AVS\r\n");
              //  while(SERCOM4_USART_Write(mode_press1,sizeof(mode_press1))==false);
                break;
            case TASK_AFE:
                vSetDriverInforMenu(TASK_AFE); // Set current task to TASK_AFE
                printf("mode press 2 = AFE\r\n");
              //  while(SERCOM4_USART_Write(mode_press2,sizeof(mode_press2))==false);
                break;                
            case TASK_TRIP_ODO_A:
                vSetDriverInforMenu(TASK_TRIP_ODO_A); // Set current task to TASK_TRIP_ODO_A
                printf("mode press 3 = Trip A\r\n");
              //  while(SERCOM4_USART_Write(mode_press3,sizeof(mode_press3))==false);
                
                break;
            case TASK_TRIP_ODO_B:
                vSetDriverInforMenu(TASK_TRIP_ODO_B); // Set current task to TASK_TRIP_ODO_B
                printf("mode press 4 = Trip B\r\n");
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
