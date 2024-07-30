/** \addtogroup CAN_APP
 *  @{
 * @CAN_App.h
 *
 * @brief This file contains an example template of how the .h
 *
 * File Short Name: CAN_App.h
 *
 * @author: Madhavi Manthri
 *
 * @date: 17-Apr-2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef APPLICATION_USER_CORE_SRC_APP_CAN_APP_CAN_APP_H_
#define APPLICATION_USER_CORE_SRC_APP_CAN_APP_CAN_APP_H_

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdio.h>

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stm32h7xx_hal.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define CAN_TEST_DEBUG 0


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
typedef union
{
	uint32_t ReceivedData;
	struct
	{
		uint8_t Signal_1 : 1;
		uint8_t Signal_2 : 1;
		uint8_t Signal_3 : 1;
		uint8_t Signal_4 : 1;
		uint8_t Signal_5 : 1;
		uint8_t Signal_6 : 1;
		uint8_t Signal_7 : 1;
		uint8_t Signal_8 : 1;
		uint8_t Signal_9 : 1;
		uint8_t Signal_10 : 1;
		uint8_t Signal_11 : 1;
		uint8_t Signal_12 : 1;
		uint8_t Signal_13 : 1;
		uint8_t Signal_14 : 1;
		uint8_t Signal_15 : 1;
		uint32_t Reserved :17 ;
	}flags;
}CAN_RxMessage_t;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

void VCAN_Init(void);
void vCANTransmit(void);
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
bool xGet_CANBusOff_Status(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *hfdcan);
CAN_RxMessage_t Get_SignalStatus(void);

#endif /* APPLICATION_USER_CORE_SRC_APP_CAN_APP_CAN_APP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/


