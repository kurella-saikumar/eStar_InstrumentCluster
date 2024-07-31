
/** \addtogroup WATCHDOG
 *  @{
 * @file wdgh.c
 *
 * @brief This file defines the FREERTOS task Bodies and and stack declarations
 *
 * @author: Rakesh Vangaveti
 *
 * @date: 31-Mar-2023
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "wdgh_cfg.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"
//#include "types.h"
//#include "debug.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
#define WDT_ERR -1
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/


/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

typedef struct
{
    uint32_t min_count;
    uint32_t max_count;
    const char *taskName;
    uint32_t kick_counter;
}wdt_task_kick_t;

wdt_task_kick_t l_task_kick_data[MAX_WDT_TASK_MONITOR] = {0};

static uint32_t l_wdt_kick_task_counter_u32 = 0;

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**
 * @brief intialize the shared watchdog task info array to -1
 *
 * @param[in] None
 *
 * @return None
 *
 ***************************************************************************************************/
void wdt_handler_init(void)
{
    memset(l_task_kick_data, /*WDT_ERR*/-1, sizeof(l_task_kick_data));
}

/**
 * @brief register_for_watchdog_monitoring
 *
 * @param[in] p_min_count_u32 : minimum no.of counts based on task periodicity to kick the watchdog
 * 
 * @param[in] p_max_count_u32 : maximum no.of counts based on task periodicity to kick the watchdog
 *
 * @return fl_return_value_i32
 *
 ***************************************************************************************************/
int32_t register_for_watchdog_monitoring(uint32_t p_min_count_u32,uint32_t p_max_count_u32, const char *p_taskName_ptr)
{
	int32_t fl_return_value_i32 = -1;
    if(p_min_count_u32 !=0 && p_max_count_u32 > 1)
    {
        if(l_wdt_kick_task_counter_u32 < MAX_WDT_TASK_MONITOR)
        {
            if(p_min_count_u32 == p_max_count_u32)
            {
                // p_min_count_u32--;
                p_max_count_u32++;
            }

            l_task_kick_data[l_wdt_kick_task_counter_u32].min_count = p_min_count_u32;
            l_task_kick_data[l_wdt_kick_task_counter_u32].max_count = p_max_count_u32;
            l_task_kick_data[l_wdt_kick_task_counter_u32].taskName = p_taskName_ptr;
            l_task_kick_data[l_wdt_kick_task_counter_u32].kick_counter = 0;
            fl_return_value_i32 = (int32_t)l_wdt_kick_task_counter_u32;
            l_wdt_kick_task_counter_u32++;
        }
    }
	return fl_return_value_i32;
}

/**
 * @brief kick/service the watchdog for task id 
 *
 * @param[in] p_wdt_task_kick_id :watchdog_kick_id of the task
 *
 * @return None
 *
 ***************************************************************************************************/
void wdt_kick_task(int32_t p_wdt_task_kick_id)
{
	if((p_wdt_task_kick_id >=0) && (p_wdt_task_kick_id < MAX_WDT_TASK_MONITOR))
	{
		l_task_kick_data[p_wdt_task_kick_id].kick_counter++;
	}
}

/**
 * @brief validate the watchdog kick counts 
 *
 * @param[in] None
 *
 * @return 0 or 1
 *
 ***************************************************************************************************/

uint8_t validate_tsk_wdt_kick(void)
{
    uint8_t fl_return_status_u8 = 1;

	for(uint32_t fl_loop_index_u32 = 0; fl_loop_index_u32 < l_wdt_kick_task_counter_u32; fl_loop_index_u32++)
	{
		if( (l_task_kick_data[fl_loop_index_u32].kick_counter > l_task_kick_data[fl_loop_index_u32].max_count) || \
			(l_task_kick_data[fl_loop_index_u32].kick_counter < l_task_kick_data[fl_loop_index_u32].min_count) ) 
		{
			fl_return_status_u8 = 0;
                        printf("\n %s: MIN:=%ld, MAX=%ld, ACTUAL=%ld \n", l_task_kick_data[fl_loop_index_u32].taskName, l_task_kick_data[fl_loop_index_u32].min_count, l_task_kick_data[fl_loop_index_u32].max_count, l_task_kick_data[fl_loop_index_u32].kick_counter);
		}
        //printf_R5("\n %s: MIN:=%d, MAX=%d, ACTUAL=%d \n", l_task_kick_data[fl_loop_index_u32].taskName, l_task_kick_data[fl_loop_index_u32].min_count, l_task_kick_data[fl_loop_index_u32].max_count, l_task_kick_data[fl_loop_index_u32].kick_counter);
        l_task_kick_data[fl_loop_index_u32].kick_counter = 0;
	}
	return(fl_return_status_u8);
}

void tsk_wdt_kick_data(void)
{
    for(uint32_t fl_loop_index_u32 = 0; fl_loop_index_u32 < l_wdt_kick_task_counter_u32; fl_loop_index_u32++)
    {
        printf("\n %s: MIN:=%ld, MAX=%ld, ACTUAL=%ld \n", l_task_kick_data[fl_loop_index_u32].taskName, l_task_kick_data[fl_loop_index_u32].min_count, l_task_kick_data[fl_loop_index_u32].max_count, l_task_kick_data[fl_loop_index_u32].kick_counter);
    }
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/




















