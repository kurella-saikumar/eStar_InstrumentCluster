/*
 * SwitchInf.c
 *
 *  Created on: Mar 4, 2024
 *      Author: dhana
 */

#ifndef APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_C_
#define APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_C_

#include "stdio.h"
#include "SwitchInf.h"
#include "digital_debounce.h"
#include "digital_debounce_cfg.h"
//#include "Application/User/Core/DigitalDebounce/digital_debounce.h"
uint8_t AllSwitchStatus;
static uint8_t switchDebouncedState = 0;
void vGet_Switch_DebouncedStatus(void)
{
	switchDebouncedState = get_debounce_status();
	printf("switchDebouncedState;%d\r\n",switchDebouncedState);
}

STATE_t xGetModeSwitch(void)
{
	STATE_t ModeSwitchState; // = RELEASED;
	if (switchDebouncedState & (1 << MODE_SWITCH_POS))
	{
		ModeSwitchState = RELEASED;
	}
	else
	{
		ModeSwitchState = PRESSED;
	}
	//printf("ModeSwitchState;%d\r\n",ModeSwitchState);
	return ModeSwitchState;
}

STATE_t xGetResetSwitch(void)
{
	STATE_t ResetSwitchState;
	if (switchDebouncedState & (1 << RESET_SWITCH_POS))
	{
		ResetSwitchState = RELEASED;
	}
	else
	{
		ResetSwitchState = PRESSED;
	}
	return ResetSwitchState;
}

STATE_t xGetIgnSwitch(void)
{
	STATE_t IgnitionSwitchState;
	if (switchDebouncedState & (1 << IGN_SWITCH_POS))
	{
		IgnitionSwitchState = RELEASED;
	}
	else
	{
		IgnitionSwitchState = PRESSED;
	}
	return IgnitionSwitchState;
}

#undef APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_C_
#endif /*APPLICATION_USER_CORE_SWITCHINTERFACE_SWITCHINF_C_*/

