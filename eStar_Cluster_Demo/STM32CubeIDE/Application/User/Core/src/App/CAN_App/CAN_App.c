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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "CAN_App.h"
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/
#define NUMBER_OF_TIMEOUTCYCLES 30
#define FDCAN_TIMEOUT_PRESCALER  FDCAN_TIMESTAMP_PRESC_16
#define TIMEOUT_PRESCALER_VALUE	16
#define FDCAN_BAUDRATE	253000
#define TIMEOUT_VALUE	0.2
#define TIMEOUT_PERIOD_VALUE	((FDCAN_BAUDRATE * TIMEOUT_VALUE)/TIMEOUT_PRESCALER_VALUE)

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
uint8_t RxTimeoutCounter = 0;
bool BusOffStatus_bool = false;
bool TimeoutStatus_bool = false;
static CAN_RxMessage_t CAN_RxData;
extern FDCAN_HandleTypeDef hfdcan3;

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

	  HAL_FDCAN_ConfigTimestampCounter(&hfdcan3,FDCAN_TIMEOUT_PRESCALER);
	  HAL_FDCAN_EnableTimestampCounter(&hfdcan3,FDCAN_TIMESTAMP_INTERNAL);

	  while(HAL_FDCAN_ConfigTimeoutCounter(&hfdcan3, FDCAN_TIMEOUT_CONTINUOUS, TIMEOUT_PERIOD_VALUE) !=0 );

	  while(HAL_FDCAN_EnableTimeoutCounter(&hfdcan3) != 0);

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
	RxTimeoutCounter = 0;
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
	{
		if(HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			Error_Handler();
		}
		else
		{
			  HAL_FDCAN_ResetTimeoutCounter(hfdcan);
			  if(RxHeader.Identifier == 0x1FF)
			  {
				  CAN_RxData.flags.Signal_1 = (RxData[0] >> 0) & 0x01;
				  CAN_RxData.flags.Signal_2 = (RxData[0] >> 1) & 0x01;
				  CAN_RxData.flags.Signal_3 = (RxData[0] >> 2) & 0x01;
				  CAN_RxData.flags.Signal_4 = (RxData[0] >> 3) & 0x01;
				  CAN_RxData.flags.Signal_5 = (RxData[0] >> 4) & 0x01;
				  CAN_RxData.flags.Signal_6 = (RxData[0] >> 5) & 0x01;
				  CAN_RxData.flags.Signal_7 = (RxData[0] >> 6) & 0x01;
				  CAN_RxData.flags.Signal_8 = (RxData[0] >> 7) & 0x01;
				  CAN_RxData.flags.Signal_9 = (RxData[1] >> 0) & 0x01;
				  CAN_RxData.flags.Signal_10 = (RxData[1] >> 1) & 0x01;
				  CAN_RxData.flags.Signal_11 = (RxData[1] >> 2) & 0x01;
				  CAN_RxData.flags.Signal_12 = (RxData[1] >> 3) & 0x01;
				  CAN_RxData.flags.Signal_13 = (RxData[1] >> 4) & 0x01;
			  }
			  else
			  {
				  /* Received Invalid Message */
			  }

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
 * @brief Callback function for FDCAN timeout occurrence
 *
 * @param xhfdcan Pointer to the FDCAN handle structure
 */
void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *xhfdcan)
{
	if(FDCAN_IT_TIMEOUT_OCCURRED != 0)
	{
		RxTimeoutCounter++;
		//printf("%s", "Time out occurred\r\n");
		if(HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_TIMEOUT_OCCURRED, 0) != HAL_OK)
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
		/* Do Nothing*/
	}

	if(RxTimeoutCounter > NUMBER_OF_TIMEOUTCYCLES)
	{
		TimeoutStatus_bool = true;
	}
	else
	{
		TimeoutStatus_bool = false;
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

/**
 * @brief Check CAN Bus Off status
 *
 * @param xhfdcan Pointer to the FDCAN handle structure
 * @return true if CAN bus is OFF, false otherwise
 */
bool xGet_CANBusOff_Status(FDCAN_HandleTypeDef *xhfdcan)
{
	HAL_FDCAN_GetProtocolStatus(xhfdcan,&xCAN_ProtocolStatus);
	BusOffStatus_bool= xCAN_ProtocolStatus.BusOff;
	//printf("%s", "Entered BUS Off\r\n");
	return BusOffStatus_bool;
}

CAN_RxMessage_t Get_SignalStatus(void)
{
	return CAN_RxData;
}

bool Get_TimeoutStatus(void)
{
	return TimeoutStatus_bool;
}
