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
#include "main.h"
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

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
extern void VCAN_Init(void);
extern void vCANTransmit(void);
extern void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);

#endif /* APPLICATION_USER_CORE_SRC_APP_CAN_APP_CAN_APP_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/


