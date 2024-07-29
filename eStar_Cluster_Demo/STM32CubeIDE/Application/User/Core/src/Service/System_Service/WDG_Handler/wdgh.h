/** \addtogroup WATCHDOG
 *  @{
 * @file wdgh.h
 *
 * @brief This file have user configurations
 * 
 * File Short Name: wdgh
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


#ifndef WDT_HNDLR_H
#define WDT_HNDLR_H


/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "wdgh_cfg.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stdint.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "../../../../PlatformConfig/safe_checks_Config.h"

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
struct tskTaskControlBlock;
typedef struct tskTaskControlBlock* TaskHandle4_t;

/**
 * @struct StackMonitorInfo_t
 * @brief Structure to hold information about a monitored task.
 */
  typedef struct
  {
	  TaskHandle4_t handle; /** Task handle of the monitored task. */
      char* pcTaskName;   /** Task name as a string. */
  } WdgMonitorInfo_t;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
/**
 *  Define the Watchdog task idle count based on task frequency
 * */
#define WDT_TASK_IDLE_COUNT(x) ( (WDT_WINDOW_OPEN_IN_SEC * 1000 ) / x )

/**
 *  Define the Watchdog task minimum count based on idle count 
 *  minimum no.of times watchdog to be serived based on minimum count
 * */
//#define WDT_TASK_MIN_COUNT(x) (WDT_TASK_IDLE_COUNT(x) - ((WDT_TASK_IDLE_COUNT(x)*WDT_KICK_LIMIT_PERCENT)/100) )
#define WDT_TASK_MIN_COUNT(x) (WDT_TASK_IDLE_COUNT(x) - ((WDT_TASK_IDLE_COUNT(x) * WDT_KICK_LIMIT_PERCENT) / 100) - (((WDT_TASK_IDLE_COUNT(x) * WDT_KICK_LIMIT_PERCENT) % 100) > 0 ? 1 : 0))
//#define WDT_TASK_MIN_COUNT(x) (WDT_TASK_IDLE_COUNT(x) - WDT_KICK_LIMIT_PERCENT) 

/**
 *  Define the Watchdog task maximum count based on idle count 
 *  maximum no.of times watchdog to be serived based on maximum count
 * */
//#define WDT_TASK_MAX_COUNT(x) (WDT_TASK_IDLE_COUNT(x) + ((WDT_TASK_IDLE_COUNT(x)*WDT_KICK_LIMIT_PERCENT)/100) )
#define WDT_TASK_MAX_COUNT(x) (WDT_TASK_IDLE_COUNT(x) + ((WDT_TASK_IDLE_COUNT(x) * WDT_KICK_LIMIT_PERCENT) / 100) + (((WDT_TASK_IDLE_COUNT(x) * WDT_KICK_LIMIT_PERCENT) % 100) > 0 ? 1 : 0))
//#define WDT_TASK_MAX_COUNT(x) (WDT_TASK_IDLE_COUNT(x) + WDT_KICK_LIMIT_PERCENT) 

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
//extern int32_t register_for_watchdog_monitoring(uint32_t p_min_count_u32,uint32_t p_max_count_u32, const char *p_taskName_ptr);
extern int32_t register_for_watchdog_monitoring(uint32_t p_min_count_u32,uint32_t p_max_count_u32, char *p_taskName_ptr);
extern void wdt_kick_task(int32_t p_wdt_task_kick_id);
extern uint8_t validate_tsk_wdt_kick(void);
extern void wdt_handler_init(void);
extern void tsk_wdt_kick_data(void);

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/



#endif /*WDT_HNDLR_H*/
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
