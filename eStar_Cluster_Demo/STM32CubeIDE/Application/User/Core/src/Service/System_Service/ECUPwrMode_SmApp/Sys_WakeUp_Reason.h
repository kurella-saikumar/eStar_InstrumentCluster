/*
 * Sys_WakeUp_Reason.h
 *
 *  Created on: Mar 14, 2024
 *      Author: 91970
 */

#ifndef SYS_WAKEUP_REASON_H_
#define SYS_WAKEUP_REASON_H_

#include "stdint.h"
#include "stdio.h"
#include "ECUPwrMode_SmHandler.h"
typedef enum {
    PM_PWRDN_RESET = 0,
    PM_BOR,
    PM_PWRDN_ACC_OFF,
    PM_PWRDN_WDT,
    PM_POR_PDR,
    PM_PIN_RESET,
    PM_PWR_WakeUp_RESET,
    PM_PWRDN_EXT_SRC
} PM_PWRDN_TYPE;

typedef enum
{
    RequestedMode_OFF = ECU_POWER_MODE_OFF,
    RequestedMode_SLEEP = ECU_POWER_MODE_SLEEP,
    RequestedMode_ACTIVE = ECU_POWER_MODE_ACTIVE,
    NoRequestPending
}pmReqStatus_t;

#define SysWakeup_TestMacro 1
PM_PWRDN_TYPE checkBootReason(void);
extern uint8_t Mcu_GetResetReason(void);

extern void vSys_EnterSTOP_Mode(void);
extern void vSys_WakeUpFromSTOP(void);
#endif /* SYS_WAKEUP_REASON_H_ */
