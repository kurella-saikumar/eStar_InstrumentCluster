
/** \addtogroup  FILE_TEMPLATE
 *  @{
 * @file template.h
 *
 * @brief Template Header File
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
***************************************************************************************************/
#ifndef RX_SIGNALS_H
#define	RX_SIGNALS_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "main.h"
#include "Indicators_CANSignal.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define NUM_RX_MESSAGES 1
#define NUM_TX_MESSAGES 0

#define RX_MESSAGE_MISSING_COUNT 10
#define CAN_NIM_TASK_RATE 5

/*-------------------------------------------RX_MESSAGE_INDEX-------------------------------------------------------------------------*/

#define INDICATOR_STATUS_INDEX 0

/*-------------------------------------------RX_TIMEOUT_VALUES-------------------------------------------------------------------------*/


#define INDICATORS_INDICATOR_STATUS_CYCLE_TIME_MS 10

/*-------------------------------------------TX_TIMEOUT_VALUES-------------------------------------------------------------------------*/


/*-------------------------------------------TX_TIMEOUT_VALUES-------------------------------------------------------------------------*/

/*------------------------------------------TX_MESSAGE_CONFIGS-------------------------------------------------------------------------*/

#define TX_MSG_LIST \

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/*-------------------------------------------RX_FRAME_ID's-------------------------------------------------------------------------*/
typedef enum
{
	MSG_NEVER_RECEIVED = 0,
	NEW_MSG_RECEIVED,
	MSG_PROCESSED,
	SIG_INVALID,
	MSG_MISSING_CONFIRMED
}CanRxStatus_t;

typedef struct {
    uint8_t l_missingCounter_U8;
    CanRxStatus_t l_rxStatus_U8;
    uint8_t l_rxBuffer[8];
} Nim_RxMsg_t;

static const uint32_t rx_message_ids[NUM_RX_MESSAGES] = {
	INDICATORS_INDICATOR_STATUS_FRAME_ID,

};

extern Nim_RxMsg_t Nim_CAN_CH0_RxBuffer[NUM_RX_MESSAGES];;
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern double vNim_get_indicator_status_right_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_left_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_parking_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_highbeam_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_lowbeam_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_engineoiltemperature_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_seatbelt_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_enginemalfunction_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_doorsopen_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_abswarning_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_faultyright_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_faultyleft_indicator(CanRxStatus_t *sigStatus);
extern double vNim_get_indicator_status_engineoil_indicator(CanRxStatus_t *sigStatus);


/*------------------------------------------TX_Signal_static_prototypes-------------------------------------------------------------------------*/


#endif	/* RX_SIGNALS_H */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/


