/** \addtogroup  
 *  @{
 * @file ICU_driver.c
 * @file ICU_driver.h
 * @brief Template Source File
 *
 * File Short Name: 
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
 ********************************************************************************************** @}*/
/* 
 * File:   ICU_driver.c
 * Author:
 *
 * Created on February 22, 2024, 4:19 PM
 */

#ifndef ICU_DRIVER_C
#define	ICU_DRIVER_C


/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "ICU_driver.h"
#include "main.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
uint16_t edge_Counter[MAX_CHANNELS] = {0};
uint8_t edge_Counter_Rollover_Flag[MAX_CHANNELS] = {0};
uint32_t temp_edgeCounter = 0;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
 ***************************************************************************************************/
/**
 * @brief Routine to be called upon every successful capture of the edge configured for Input Capture Mode of the CCP
 *                                                                                                                                                                                                                                                                                                                                                                                                                              
 * This function is designed to count the number of pulses generated when an Interrupt is triggered. If the count value exceeds the variable limit, it will increment the rollover flag variable by one and restart counting from zero.
 *
 * @param channelNum [in]The channel number for which the interrupt is generated
 *                                
 * @return void
 */

void vTriggeredEdge_Counter(uint8_t channelNum)
{
    if (edge_Counter[channelNum] == USHRT_MAX)
    {
    	edge_Counter_Rollover_Flag[channelNum]++;
    }
    edge_Counter[channelNum]++;
}

/**
 * @brief Count the total no. of pulses generated
 *
 * This function is designed to count the number of pulses generated based on the rollOverCount input. After counting, it will reset the values.
 *
 * @param channelNum [in] The channel number for which the rolling count is requested   
 *                                
 * @param rollOverCount [out] Provides the no. of times that the value has rolled over
 *
 * @return  uint16_t Provides the count of the generated pulses
 */

uint32_t xGetRollingPulseCount(uint8_t channelNum)
{
	if(MAX_CHANNELS > channelNum)
	{
		temp_edgeCounter = edge_Counter_Rollover_Flag[channelNum] * USHRT_MAX + edge_Counter[channelNum];
	}
    return temp_edgeCounter;
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(htim);

	if(htim->Instance == TIM1)
	{
		vTriggeredEdge_Counter(ODO_SPEEDO_CHANNEL);	// Timer 1 capture event
	}
	else if(htim->Instance == TIM4)
	{
		vTriggeredEdge_Counter(TACHO_CHANNEL);	// Timer 4 capture event
	}

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_IC_CaptureCallback could be implemented in the user file
   */
}

void vDisable_OdoSpeedo_Channel_Interrupts(void)
{
	if( HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_4)!= HAL_OK )
	{
		Error_Handler();
	}
}

void vEnable_OdoSpeedo_Channel_Interrupts(void)
{
	if(HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_4)!=HAL_OK)
	{
		Error_Handler();
	}
}
#endif	/* ICU_DRIVER_C */

