/** \addtogroup DIGITAL_INPUT_DEBOUNCER
 *  @{
 * @file digital_debounce.h
 *
 * @brief This file performs either multiple input parallel de-bouncing
 * or single input de-bouncing based on the user's configuration
 *
 * File Short Name: debounce
 *
 * @author: Sashidhar Bhaguluri
 *
 * @date: 29th-June-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 */
#ifndef DIGITAL_DEBOUNCE_H
#define	DIGITAL_DEBOUNCE_H


/**
 * @brief Periodic task function that shall take one sample of the input
 * to be de-bounced on every execution
 *
 * @param[in] void
 *
 * @return void
 *
 */
extern void DebounceTask(void);

/**
 * @brief This function returns the stable state of the input
 *
 * @param[in] void
 *
 * @return l_Debounced_State_u8
 *
 */
extern uint8_t get_debounce_status(void);

/**
 * @brief De-bounce initialization function to set the state and debounce
 * status to the initial value of the input
 *
 * @param[in] void
 *
 * @return void
 *
 */
extern void debounce_init(void);

#endif	/* DIGITAL_DEBOUNCE_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
