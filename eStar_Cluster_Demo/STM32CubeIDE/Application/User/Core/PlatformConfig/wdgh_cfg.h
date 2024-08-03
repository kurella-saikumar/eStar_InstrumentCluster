/** \addtogroup WATCHDOG
 *  @{
 * @file wdgh_cfg.h
 *
 * @brief This file have user configurations
 * 
 * File Short Name: wdgh_cfg
 *
 * @author Rakesh Vangaveti
 *
 * @date: 31st-Mar-2023
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 **/


#ifndef WDT_CFG_H
#define WDT_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
// #include "tcc_wdt.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**
 *          |<-------------Window Period------------>| 
 *  
 *          |                    |-------------------|
 *          |--------------------|                   |
 * 
 *          |<--Window Closed -->||<--Window Open -->|
 * 
 * Watchdog Should be Kicked/Serviced/Petted only during the Window Open Period
 * 
 * */

/**
 *  Define the clock frequency for the Watchdog timer Pripheral 
 *  Watchdog clock frequency in MHz
 * */
#define WDT_CLOCK_IN_MHz 12

/**
 *  Define the Watchdog window period/reset time for the Watchdog timer Pripheral 
 *  WTD time: second
 * */
#define WDT_WINDOW_PERIOD_IN_SEC 24

/**
 *  Define the Watchdog open window for the Watchdog timer Pripheral 
 *  No.of seconds after which the watchdog should be serviced
 *  WTD time: second
 * */
#define WDT_WINDOW_OPEN_IN_SEC 1

/**
 *  Define the Watchdog open window for the Watchdog timer Pripheral 
 *  Number of Tasks to be moniterd with watchdog service
 * */
#define MAX_WDT_TASK_MONITOR 14

/**
 *  Define the Watchdog KICK limit percent to validate the minimum task watchdog kicks 
 *  eg: 10% -1  , 20% - 2, .... , 30% - 3  
 * */
#define WDT_KICK_LIMIT_PERCENT 3

#endif /*WDT_CFG_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
