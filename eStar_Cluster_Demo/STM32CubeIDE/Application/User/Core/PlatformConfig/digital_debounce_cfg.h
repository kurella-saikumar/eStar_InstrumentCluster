/** \addtogroup DIGITAL_INPUT_DEBOUNCER_CONFIGURATION
 *  @{
 * @file digital_debounce_cfg.h
 *
 * @brief Application specific configuration file
 *
 * File Short Name: debounce_cfg
 *
 * @author: Sashidhar Bhaguluri
 *
 * @date: 1st-Sept-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 */

#ifndef DIGITAL_DEBOUNCE_CFG_H
#define	DIGITAL_DEBOUNCE_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "digital_debounce.h"

#include "main.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
/**
 * Define the number of samples to be compared before confirming a digital input state
 */
#define SAMPLES_TO_CONFIRM_DEBOUNCE_STATUS 12

/**
 * Define the MACRO "PARALLEL_DEBOUNCE" if multiple inputs are required to be de-bounced in parallel
 */
#define PARALLEL_DEBOUNCE

#ifdef PARALLEL_DEBOUNCE

	/**
	 * Define the pairs "DI_0x_RAW_VALUE" and "DI_0x_DEFAULT_VALUE" for all available digital inputs
	 * These macros should return a BIT value of 0 or 1 only.
	 * If any input is not required, then the corresponding MACRO pairs should be commented out
	 */
	/**
	 * Define Input 7 pair values
	 */
	#define DI_07_RAW_VALUE 0
	#define DI_07_DEFAULT_VALUE 0

	/**
	 * Define Input 6 pair values
	 */
	#define DI_06_RAW_VALUE 0
	#define DI_06_DEFAULT_VALUE 0

	/**
	 * Define Input 5 pair values
	 */
	#define DI_05_RAW_VALUE 0
	#define DI_05_DEFAULT_VALUE 0

	/**
	 * Define Input 4 pair values
	 */
	#define DI_04_RAW_VALUE 0
	#define DI_04_DEFAULT_VALUE 0

	/**
	 * Define Input 3 pair values
	 */
	#define DI_03_RAW_VALUE 0
	#define DI_03_DEFAULT_VALUE 0

	/**
	 * Define Input 2 pair values
	 */
	#define DI_02_RAW_VALUE HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_8)
	#define DI_02_DEFAULT_VALUE 0

	/**
	 * Define Input 1 pair values
	 */
	#define DI_01_RAW_VALUE 0//HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_5)
	#define DI_01_DEFAULT_VALUE 0

	/**
	 * Define Input 0 pair values
	 */
	#define DI_00_RAW_VALUE 0//HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)
	#define DI_00_DEFAULT_VALUE 0

#else
	/**
	 * Define the pairs "DI_RAW_VALUE" and "DI_DEFAULT_VALUE" for the single digital input
	 * These macros should return a BIT value of 0 or 1 only.
	 */
	//#define DI_RAW_VALUE HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)
	#define DI_RAW_VALUE HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)
	#define DI_DEFAULT_VALUE 1
#endif /*PARALLEL_DEBOUNCE*/
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
#endif	/* DIGITAL_DEBOUNCE_CFG_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
