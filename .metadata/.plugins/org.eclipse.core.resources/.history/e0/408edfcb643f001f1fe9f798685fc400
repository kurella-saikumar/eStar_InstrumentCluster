/** \addtogroup DRIVER_INFO_MENU
 *  @{
 * @file DriverInfoMenu_App.h
 *
 * @brief Header file for Driver Information Menu Application
 *
 * File Short Name: DriverInfoMenu
 *
 * @author: Govindraj
 *
 * @date: 23 feb 2024
 *
 * @copyright  
 * All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 * ********************************************************************************************** @}*/
#ifndef DRIVER_INFO_MENU_APP_H
#define DRIVER_INFO_MENU_APP_H

#include <stdbool.h>

// Define the enum for different tasks
typedef enum {
    TASK_RANGE,          /**< Indicates the range task */
    TASK_AVS,            /**< Indicates the AVS task */
    TASK_AFE,            /**< Indicates the AFE task */
    TASK_TRIP_ODO_A,     /**< Indicates the Trip ODO A task */
    TASK_TRIP_ODO_B,      /**< Indicates the Trip ODO B task */
    TASK_NONE
} DriverInfoModeStatus_t;

// Function prototypes
void vDriverInfoMenu_Init(void); /**< Initializes the Driver Information Menu */
void vModeSwitchToNext(void); /**< Switches to the next mode */

#define DriverInfoMenuApp_TestMacro 1

// Global variables
extern DriverInfoModeStatus_t eCurrentTask; /**< Global variable to store the current task */



void vSetDriverInforMenu(DriverInfoModeStatus_t MenuSetItem);


#ifdef __cplusplus
extern "C" {
#endif

DriverInfoModeStatus_t xGetDriverInforMenu(void);

#ifdef __cplusplus
}
#endif


#endif /* DRIVER_INFO_MENU_APP_H */
