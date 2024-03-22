/*
 * SwitchInf.h
 *
 *  Created on: Mar 4, 2024
 *      Author: dhana
 */

#ifndef APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_H_
#define APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_H_

#define MODE_SWITCH_POS 0
#define RESET_SWITCH_POS 1
#define IGN_SWITCH_POS 2

#include "main.h"

typedef enum PRESSED{
	PRESSED ,
	RELEASED
} STATE_t;
extern void vGet_Switch_DebouncedStatus(void);
extern STATE_t xGetModeSwitch(void);
extern STATE_t xGetResetSwitch(void);
extern STATE_t xGetIgnSwitch(void);

#endif /* APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_H_ */
