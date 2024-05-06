/** \addtogroup  DemoApp
 *  @{
 * @file DemoApplication.c
 *
 * @brief Demo Applocation file is to test QueueSend and QueueRecieve with checksum verification
 *
 * File Short Name: DemoApplication
 *
 * Author: Vasavi Bashetti
 *
 * Create Date: 21-11-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/

#ifndef SRC_DEMOAPPLICATION_H_
#define SRC_DEMOAPPLICATION_H_

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
//#include "PeriodicityCheck.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/

void vTask_Execution_Time(void);
void execTimeFault_cb1(TaskRunTimeStat_t *p_measurement_var_ptr);
void execTimeFault_cb2(TaskRunTimeStat_t *p_measurement_var_ptr);
//extern void vTask_demo1PeriodicityCheckErrorHook(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
extern void ExecutionMetricdebug(char *Taskname,TaskRunTimeStat_t *p_measurement_var_ptr);
void SwitchErrorHook1(uint8_t reason);
void SwitchErrorHook2(uint8_t reason);
void SwitchErrorHook3(uint8_t reason);
void vTask_DeadLock_Test(void);
void vLooper(uint32_t ulmilliseconds);
#endif /* SRC_DEMOAPPLICATION_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
