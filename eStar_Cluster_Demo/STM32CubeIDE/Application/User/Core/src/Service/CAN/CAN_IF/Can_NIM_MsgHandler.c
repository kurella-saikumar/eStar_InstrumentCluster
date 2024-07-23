/** \addtogroup CAN_INTERFACE
 *  @{
 * @file CAN_Interface.c
 *
 * @brief CAN_Interface C file
 *
 * File Short Name: CAN_NIM
 *
 * @author: Madhavi Manthri
 *
 * @date: Apr 10, 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <string.h>
#include "stdio.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "CAN_NIM.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
#define RX_MESSAGE_MISSING_COUNT 10

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
FDCAN_TxHeaderTypeDef TxMsgHeader[]={
		TX_MSG_LIST
};

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

uint8_t Nim_Can_TxCount[NUM_TX_MESSAGES];
/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/
const uint32_t Nim_CAN_CH0_msgTimeoutLimit[NUM_RX_MESSAGES] =
{
	((RX_MESSAGE_MISSING_COUNT * INDICATORS_INDICATOR_STATUS_CYCLE_TIME_MS) / CAN_NIM_TASK_RATE)
};

const uint32_t Nim_CAN_CH0_msgTxPeriodicity[NUM_TX_MESSAGES] = { };
/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
static void vNim_ProcessSignalTimeout(uint8_t MessageIndex, uint8_t CH_id);
extern FDCAN_HandleTypeDef hfdcan3;
/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief Update the signal timeout for a CAN message
 *
 * This function updates the signal timeout for a CAN message. If the missing counter
 * for the message is not zero, it decrements the counter. If the counter reaches zero,
 * it sets the message status to missing confirmed.
 *
 * @param[in] MessageIndex Index of the CAN message in the buffer
 *
 * @param[out] None
 *
 * @return None
 */
static void vNim_ProcessSignalTimeout(uint8_t MessageIndex, uint8_t CH_id)
{
	if(CH_id == INDICATOR_STATUS_INDEX)
	{
		if (Nim_CAN_CH0_RxBuffer[MessageIndex].l_missingCounter_U8 != 0)
		{
			Nim_CAN_CH0_RxBuffer[MessageIndex].l_missingCounter_U8--;
		}
		else
		{
			Nim_CAN_CH0_RxBuffer[MessageIndex].l_rxStatus_U8 = MSG_MISSING_CONFIRMED;
			//printf("Message missing confirmed from index: %d\r\n",MessageIndex);
		}
	}
	else
	{
		/**Process for 2nd CAN Channel*/
	}
}

/**
 * @brief Initialize the Nim module
 *
 * This function initializes the Nim module by setting up the CAN buffer,
 * initializing missing counters, setting message receive statuses, and
 * performing message-specific initialization.
 *
 * @param[in] None
 *
 * @param[out] None
 *
 * @return None
 */
void vNim_Sig_Init(void)
{
	uint16_t fl_msgLoopCounter_u16;
	for(fl_msgLoopCounter_u16=0; fl_msgLoopCounter_u16 < NUM_RX_MESSAGES; fl_msgLoopCounter_u16++)
	{
		Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_missingCounter_U8 = Nim_CAN_CH0_msgTimeoutLimit[fl_msgLoopCounter_u16];
		Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_rxStatus_U8 = MSG_NEVER_RECEIVED;
		vNim_RxmsgInit(fl_msgLoopCounter_u16, INDICATOR_STATUS_INDEX);
	}

	/**Perform Process for each channel*/
}

/**
 * @brief Process the Nim module task
 *
 * This function processes the task of the Nim module, which includes handling
 * received messages, updating missing counters, and unpacking received data.
 *
 * @param[in] None
 *
 * @param[out] None
 *
 * @return None
 */

void vNim_ProcessRxTask(void)
{
	static uint8_t tmpDataBuffer[8];
	uint16_t fl_msgLoopCounter_u16;
	for(fl_msgLoopCounter_u16=0; fl_msgLoopCounter_u16 < sizeof(Nim_CAN_CH0_RxBuffer)/sizeof(Nim_RxMsg_t); fl_msgLoopCounter_u16++)
	{
		if(Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_rxStatus_U8 == NEW_MSG_RECEIVED)
		{
			/** Enter Critical Section*/
			//CAN_NIM_ENTER_CRITICAL_SECTION;
			Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_rxStatus_U8 = MSG_PROCESSED;
			memcpy(tmpDataBuffer, Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_rxBuffer, sizeof(tmpDataBuffer));
			/** Exit Critical Section*/
			//CAN_NIM_EXIT_CRITICAL_SECTION;
			Nim_CAN_CH0_RxBuffer[fl_msgLoopCounter_u16].l_missingCounter_U8 = Nim_CAN_CH0_msgTimeoutLimit[fl_msgLoopCounter_u16];
			vNim_unPack(fl_msgLoopCounter_u16, tmpDataBuffer);
		}
		else
		{
			vNim_ProcessSignalTimeout(fl_msgLoopCounter_u16, INDICATOR_STATUS_INDEX);
		}
	}

	/**Perform Process for each channel*/
}

/**
 * @brief Processes the transmit task for the Nim module
 *
 * This function processes the transmit task for the Nim module. It packs each
 * transmit message and adds it to the transmit FIFO queue of the FDCAN peripheral.
 *
 * @param None
 * @return None
 * @todo: Need to update Event and Event Periodic message handling.
 */

void vNim_Process_TxTask(void)
{
	static uint8_t tmpDataBuffer[8];
	uint16_t fl_msgLoopCounter_u16 = 0;

	for(fl_msgLoopCounter_u16=0; fl_msgLoopCounter_u16 < NUM_TX_MESSAGES; fl_msgLoopCounter_u16++)
	{
		if(Nim_CAN_CH0_msgTxPeriodicity[fl_msgLoopCounter_u16] != 0)
		{
			if(Nim_Can_TxCount[fl_msgLoopCounter_u16] == 0)
			{
				vNim_Pack(fl_msgLoopCounter_u16, tmpDataBuffer);
				HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &TxMsgHeader[fl_msgLoopCounter_u16], tmpDataBuffer);
				Nim_Can_TxCount[fl_msgLoopCounter_u16] = Nim_CAN_CH0_msgTxPeriodicity[fl_msgLoopCounter_u16];
			}
			else
			{
				Nim_Can_TxCount[fl_msgLoopCounter_u16]--;
			}
		}
	}
}

/**
 * @brief Update receive status and buffer based on message ID.
 *
 * @param Msg_Id The message ID.
 * @param data Pointer to the data to be copied into the receive buffer.
 */
void vUpdateRxBuffer_Callback(uint32_t Msg_Id, uint8_t* data)
{
	uint32_t fl_RxMessageIndex_U32 = 0;
	for (fl_RxMessageIndex_U32 = 0; fl_RxMessageIndex_U32 < NUM_RX_MESSAGES; fl_RxMessageIndex_U32++)
	{
		if (Msg_Id == rx_message_ids[fl_RxMessageIndex_U32])
		{
			Nim_CAN_CH0_RxBuffer[fl_RxMessageIndex_U32].l_rxStatus_U8 = NEW_MSG_RECEIVED;
			memcpy(Nim_CAN_CH0_RxBuffer[fl_RxMessageIndex_U32].l_rxBuffer, data, sizeof(Nim_CAN_CH0_RxBuffer[fl_RxMessageIndex_U32].l_rxBuffer));
			break;
		}
	}
}
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
