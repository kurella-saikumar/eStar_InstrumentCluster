/** \addtogroup ANALOG_INPUT_DEBOUNCER
 *  @{
 * @file adcm.h
 *
 * @brief This file performs  multiple analog de-bouncing
 * or single input analog de-bouncing based on the user's configuration
 *
 * File Short Name: adcm
 *
 * @author: Sandhya
 *
 * @date: 14-12-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/
#ifndef ANALOG_DEBOUNCE_H
#define	ANALOG_DEBOUNCE_H


/*Global Type Definitions*/
typedef uint8_t AD_State_T;

/*returns the current state for the input type being requested...
 returns STATE_INVALID(0xFF) if the inp_type is not supported OR above the MAX no.of inputs*/
extern /*__reentrant*/ AD_State_T get_analog_debounce_state(uint8_t inp_type);

extern void analog_debounce_task(void);

#endif	/* ANALOG_DEBOUNCE_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
