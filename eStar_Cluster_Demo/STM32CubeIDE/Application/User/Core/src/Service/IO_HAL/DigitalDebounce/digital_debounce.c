/** \addtogroup DIGITAL_INPUT_DEBOUNCER
 *  @{
 * @file digital_debounce.c
 *
 * @brief This file performs either multiple input parallel de-bouncing
 * or single input de-bouncing based on the user's configuration
 *
 * File Short Name: debounce
 *
 * @author Sashidhar Bhaguluri
 *
 * @date: 29th-June-2021
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/

#ifndef DIGITAL_DEBOUNCE_C
#define DIGITAL_DEBOUNCE_C

/*Include Platform or Standard Headers*/
#include <stdint.h>
#include <stddef.h>
#include "stdio.h"

/*Include Project Specific Headers*/

#include "digital_debounce.h"
#include "digital_debounce_cfg.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
extern osMessageQueueId_t myQueue01Handle;
extern osEventFlagsId_t myEvent01Handle;

/*DEFINE FILE SCOPE MACROS*/

/*DEFINE FILE SCOPE TYPES*/

#ifdef PARALLEL_DEBOUNCE
#ifndef DI_07_RAW_VALUE
#define DI_07_RAW_VALUE 0
#endif
#ifndef DI_07_DEFAULT_VALUE
#define DI_07_DEFAULT_VALUE 0
#endif
#ifndef DI_06_RAW_VALUE
#define DI_06_RAW_VALUE 0
#endif
#ifndef DI_06_DEFAULT_VALUE
#define DI_06_DEFAULT_VALUE 0
#endif
#ifndef DI_05_RAW_VALUE
#define DI_05_RAW_VALUE 0
#endif
#ifndef DI_05_DEFAULT_VALUE
#define DI_05_DEFAULT_VALUE 0
#endif
#ifndef DI_04_RAW_VALUE
#define DI_04_RAW_VALUE 0
#endif
#ifndef DI_04_DEFAULT_VALUE
#define DI_04_DEFAULT_VALUE 0
#endif
#ifndef DI_03_RAW_VALUE
#define DI_03_RAW_VALUE 0
#endif
#ifndef DI_03_DEFAULT_VALUE
#define DI_03_DEFAULT_VALUE 0
#endif
#ifndef DI_02_RAW_VALUE
#define DI_02_RAW_VALUE 0
#endif
#ifndef DI_02_DEFAULT_VALUE
#define DI_02_DEFAULT_VALUE 0
#endif
#ifndef DI_01_RAW_VALUE
#define DI_01_RAW_VALUE 0
#endif
#ifndef DI_01_DEFAULT_VALUE
#define DI_01_DEFAULT_VALUE 0
#endif
#ifndef DI_00_RAW_VALUE
#define DI_00_RAW_VALUE 0
#endif
#ifndef DI_00_DEFAULT_VALUE
#define DI_00_DEFAULT_VALUE 0
#endif
/**
 * Define upto 8 inputs one per bit that should be de-bounced
 */
#define RawKeyPressed() (uint8_t)(((DI_07_RAW_VALUE<<7)|(DI_06_RAW_VALUE<<6)|(DI_05_RAW_VALUE<<5)|(DI_04_RAW_VALUE<<4)|(DI_03_RAW_VALUE<<3)|(DI_02_RAW_VALUE<<2)|(DI_01_RAW_VALUE<<1)|DI_00_RAW_VALUE))

/**
 * Define the default values of upto 8 inputs one per bit that should be de-bounced
 */
#define DefaultKeyValues() (uint8_t)(((DI_07_DEFAULT_VALUE<<7)|(DI_06_DEFAULT_VALUE<<6)|(DI_05_DEFAULT_VALUE<<5)|(DI_04_DEFAULT_VALUE<<4)|(DI_03_DEFAULT_VALUE<<3)|(DI_02_DEFAULT_VALUE<<2)|(DI_01_DEFAULT_VALUE<<1)|DI_00_DEFAULT_VALUE))

/**
 * Macro to define the number of samples to be compared before confirming a switch state
 */
#define MAX_CHECKS SAMPLES_TO_CONFIRM_DEBOUNCE_STATUS
uint8_t l_State_u8A[MAX_CHECKS]; // Array that maintains bounce status
uint8_t l_Index_u8; // Pointer into State
#else
/**
 * Define 1 input at Bit_0 that should be de-bounced
 */
#define RawKeyPressed() (uint8_t)DI_RAW_VALUE

/**
 * Define the default values of 1 input at Bit_0 that should be de-bounced
 */
#define DefaultKeyValues() (uint8_t)DI_DEFAULT_VALUE
/**
 * Macro to define the stable state mask value to determine if the input is HI
 */
#define STABLE_STATE_LOW_MASK_VALUE (uint16_t)(0xFFFF)
/**
 * Macro to define the stable state mask value to determine if the input is HI
 */
#define STABLE_STATE_HI_MASK_VALUE (uint16_t)(STABLE_STATE_LOW_MASK_VALUE << SAMPLES_TO_CONFIRM_DEBOUNCE_STATUS) //0xf000
/**
 * Macro to define the number of samples to be compared before confirming a switch state
 * The Number of bit Cleared in the MASK is equal to the number of samples to be collected
 */
#define DEBOUNCE_SAMPLING_MASK (uint16_t)(STABLE_STATE_HI_MASK_VALUE << 1) //0xe000  12 samples to be evaluated for determining stable state

/**
 * Purpose: Variable To Hold the stable state counter.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: Initialized to the default input state of the input to be de-bounced
 *
 * Wakeup Value\Action: Initialized to the default input state of the input to be de-bounced
 *
 * Shutdown Value\Action: Don't Care
 *
 */
static uint16_t l_State_U16;

#endif

/**
 * Purpose: Variable To Hold the de-bounced state of the input.
 *
 * Unit: 8 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 255
 *
 * Power On Init Value\Action: Initialized to the default input state of the input to be de-bounced
 *
 * Wakeup Value\Action: Initialized to the default input state of the input to be de-bounced
 *
 * Shutdown Value\Action: Don't Care
 *
 */
static uint8_t l_Debounced_State_u8 = 0;
uint8_t ucDebounced_State = 0;

//uint8_t *debounced_value = &debounced_state;

// Service routine called every CHECK_MSEC to
// debounce both edges
#ifdef PARALLEL_DEBOUNCE
/**
 * @brief Periodic task function that shall take one sample of the input
 * to be de-bounced on every execution
 *
 * @param[in] void
 *
 * @return void
 *
 */
#ifdef RawKeyPressed
void DebounceTask(void)
{

    uint8_t i,j;
    l_State_u8A[l_Index_u8]=RawKeyPressed();
    ++l_Index_u8;
    j=0xff;
    for(i=0; i<MAX_CHECKS;i++)
    {
        j=j & l_State_u8A[i];
    }
    l_Debounced_State_u8= j;
    ucDebounced_State = j;
    if(l_Index_u8>=MAX_CHECKS)l_Index_u8=0;

#if 0
    uint32_t event = osEventFlagsSet(myEvent01Handle,EVENT_FLAG_0);
    printf("DebounceTask: Event flag set, %ld \n",event);
	uint32_t flags = osEventFlagsGet(myEvent01Handle);
	printf("flags:%ld\t",flags);
	if(flags & EVENT_FLAG_0)
	{
		osMessageQueuePut(myQueue01Handle,&l_Debounced_State_u8, NULL, 0);
		printf("put:%d\n\r\t",l_Debounced_State_u8);

	}
	else
	{
		printf("event not set\n\r");
	}
#endif


}

#else
/**
 * @brief De-bounce initialization function to set the state and debounce
 * status to the initial value of the input
 *
 * @param[in] void
 *
 * @return void
 *
 */
void debounce_init(void)
{
    uint8_t i,j;
    j=DefaultKeyValues();
    for(i=0; i<MAX_CHECKS;i++)
    {
        l_State_u8A[i] = j;
    }
    l_Debounced_State_u8= j;
    l_Index_u8=0;
}

#endif
#else

/**
 * @brief Periodic task function that shall take one sample of the input
 * to be de-bounced on every execution
 *
 * @param[in] void
 *
 * @return void
 *
 */
void DebounceTask(void)
{
    uint8_t KeyStatus = RawKeyPressed();
    l_State_U16=(l_State_U16<<1) | !KeyStatus | DEBOUNCE_SAMPLING_MASK;
    if((l_State_U16==STABLE_STATE_HI_MASK_VALUE) || (l_State_U16==STABLE_STATE_LOW_MASK_VALUE))
    {
        l_Debounced_State_u8 = KeyStatus;
    }
    else
    {
    }
}

/**
 * @brief De-bounce initialization function to set the state and debounce
 * status to the initial value of the input
 *
 * @param[in] void
 *
 * @return void
 *
 */
void debounce_init(void)
{
    l_Debounced_State_u8 = DefaultKeyValues();
    
    if(l_Debounced_State_u8)
    {
        l_State_U16 = STABLE_STATE_HI_MASK_VALUE;
    }
    else
    {
        l_State_U16 = STABLE_STATE_LOW_MASK_VALUE;
    }
}
#endif

/**
 * @brief This function returns the stable state of the input
 *
 * @param[in] void
 *
 * @return l_Debounced_State_u8
 *
 */

uint8_t get_debounce_status(void)
{
	//static uint8_t state = 0;
//		osEventFlagsSet(myEvent01Handle,EVENT_FLAG_1);
//		uint32_t flags = osEventFlagsGet(myEvent01Handle);
//		printf("flags:%ld\t",flags);
//		if(flags & EVENT_FLAG_1)
//		{
			//if(osMessageQueuePut(myQueue01Handle,&l_Debounced_State_u8, NULL, 10)==osOK)
#if 0
	osStatus_t status = 0;
	status = osMessageQueuePut(myQueue01Handle,&ucDebounced_State, NULL, 4);
			if(status == 0)
			{
				printf("QPut Pass:%d\n\r",ucDebounced_State);

			}
			else
			{
				printf("QPut Fail,%ld\n\r",status);
			}
#endif
//		}
//		else
//		{
//			printf("Event not set\n\r");
//		}
	//static uint8_t Deb_State = 0;
//	osMessageQueueGet (myQueue01Handle, &l_Debounced_State_u8, NULL, 0);
//
//	//printf("get:%d",Deb_State);
    return l_Debounced_State_u8;
}


#undef DIGITAL_DEBOUNCE_C
#endif /*DIGITAL_DEBOUNCE_C*/
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
