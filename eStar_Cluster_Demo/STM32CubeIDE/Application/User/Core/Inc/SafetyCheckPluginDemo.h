/*
 * Feature Name:
 *
 * Feature Short Name:
 *
 * Description: This file contains an example template of how the .h
 * file should be created and maintained. The contents cover the following information
 * 1. Avoid multiple include of the same file hence avoiding recursive includes of any files
 * 2. Usage of EXTERN helps define the global scope functions/variables. Any file using these
 * should include the header file and the prototype definition is there automatically
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
 */

#ifndef SAFETYCHECKPLUGINDEMO_H
#define SAFETYCHECKPLUGINDEMO_H
#include "stdint.h"
#include "safe_checks_freeRTOSConfig.h"
#include "safe_checks_Config.h"
#include "Task_ExeTime.h"
#include "PeriodicityCheck.h"
#include "Stack_Usage.h"
#include "Task_OverLoad_DeadLock.h"
#include "wdgh.h"

/* GLOBAL TYPE DEFINES*/
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T01;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T02;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T03;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T04;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T05;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T06;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T07;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T08;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T09;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T10;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T11;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T12;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T13;
extern TaskPeriodicityCheck_t xPeriodicityCheckTaskInfo_T14;

/* GLOBAL VARIABLES*/

/* GLOBAL FUNCTIONS*/
void execTimeFault_cb1(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook01(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook1(uint8_t reason);
void execTimeFault_cb2(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook02(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook2(uint8_t reason);
void execTimeFault_cb3(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook03(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook3(uint8_t reason);
void execTimeFault_cb4(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook04(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook4(uint8_t reason);
void execTimeFault_cb5(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook05(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook5(uint8_t reason);
void execTimeFault_cb6(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook06(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook6(uint8_t reason);
void execTimeFault_cb7(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook07(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook7(uint8_t reason);
void execTimeFault_cb8(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook08(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook8(uint8_t reason);
void execTimeFault_cb9(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook09(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook9(uint8_t reason);
void execTimeFault_cb10(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook10(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook10(uint8_t reason);
void execTimeFault_cb11(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook11(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook11(uint8_t reason);
void execTimeFault_cb12(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook12(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook12(uint8_t reason);
void execTimeFault_cb13(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook13(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook13(uint8_t reason);
void execTimeFault_cb14(TaskRunTimeStat_t *p_measurement_var_ptr);
void vTask_demo1PeriodicityCheckErrorHook14(TaskPeriodicityCheck_t *xPeriodicityCheckTaskInfo);
void SwitchErrorHook14(uint8_t reason);
void DeadLockTask(void *argument);
#endif /* SAFETYCHECKPLUGINDEMO_H */
