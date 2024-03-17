/** \addtogroup 
 *  @{
 * @file Switch.h
 *
 * @brief 
 *
 * File Short Name: Switch
 *
 * @author 
 *
 * @date: 
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/
#ifndef SWITCH_H
#define	SWITCH_H

/*Global Type Definitions*/
typedef enum
{
	SHORT_PRESS_HELD,
	SHORT_PRESS_RELEASED,
	LONG_PRESS_HELD,
	LONG_PRESS_RELEASED,
	BUTTON_STUCK
}Button_Push_Event_T;

typedef enum
{
	BUTTON_RELEASED,
	BUTTON_PUSHED
	/* DO NOT ADD any other type... Both Analog and Digital switch states shall be supported */	
}Switch_PushRelease_State_T;



void Switch_Task(void);

#endif	/* SWITCH_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
