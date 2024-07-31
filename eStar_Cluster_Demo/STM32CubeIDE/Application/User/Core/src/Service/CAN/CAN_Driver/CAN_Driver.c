/** \addtogroup
 *  @{
 * @file CAN_App.c
 * @file CAN_App.h
 * @brief Template Source File
 *
 * File Short Name: CAN_APP.c
 *
 * Author: Madhavi Manthri
 *
 * Create Date: 17-Apr-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include "CAN_Driver.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "CAN_NIM.h"
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
//FDCAN_HandleTypeDef xhfdcan;
FDCAN_FilterTypeDef sFilterConfig;
FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef RxHeader;
FDCAN_ProtocolStatusTypeDef xCAN_ProtocolStatus;
uint8_t TxData0[] = {0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA};
uint8_t RxData[8] = {0};

extern FDCAN_HandleTypeDef hfdcan3;
uint8_t Rxbuffer[8] = {0};
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
 ***************************************************************************************************/
extern void Error_Handler(void);
/**************************************************************************************************
 * FUNCTION DEFINITIONS
 ***************************************************************************************************/
/**
* @brief  Initializes FDCAN communication by configuring transmission and reception parameters.
* @param  None
* @retval None
*/
void VCAN_Init(void)
{
	  /* Configure Tx buffer message */
	  TxHeader.Identifier = 0x111;
	  TxHeader.IdType = FDCAN_STANDARD_ID;
	  TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	  TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	  TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	  TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
	  TxHeader.MessageMarker = 0x52;

	  /* Configure standard ID reception filter to Rx buffer 0 */
	  sFilterConfig.IdType = FDCAN_STANDARD_ID;
	  sFilterConfig.FilterIndex = 1;
	  sFilterConfig.FilterType = FDCAN_FILTER_DUAL;
	  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	  sFilterConfig.FilterID1 = 0x1FF;
	  sFilterConfig.FilterID2 = 0x7FF;
	  HAL_FDCAN_ConfigFilter(&hfdcan3, &sFilterConfig);

	  HAL_FDCAN_AddMessageToTxBuffer(&hfdcan3, &TxHeader, TxData0, FDCAN_TX_BUFFER0);

	  /* Send Tx buffer message */
	  HAL_FDCAN_EnableTxBufferRequest(&hfdcan3, FDCAN_TX_BUFFER0);

	  /* Activate Rx FIFO 0 watermark notification */
	  HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

	  HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_TIMEOUT_OCCURRED, 0);

	  /* Start the FDCAN module */
	  HAL_FDCAN_Start(&hfdcan3);

}

/**
* @brief  Receives CAN messages from Rx Fifo 0.
* @param  None
* @retval None
*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
	{
		if(HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			Error_Handler();
		}
		else
		{
			  memcpy(Rxbuffer,RxData,sizeof(Rxbuffer));
			  vUpdateRxBuffer_Callback(RxHeader.Identifier, Rxbuffer);
		}
		if(HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			Error_Handler();
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{
		/* Do Nothing */
	}
}

/**
* @brief  Transmits a CAN message using the Tx FIFO queue.
* @param  None
* @retval None
*/
void vCANTransmit(void)
{
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &TxHeader, TxData0);
}

