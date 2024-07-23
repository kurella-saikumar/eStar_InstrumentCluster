
/** \addtogroup  FILE_TEMPLATE
 *  @{
 * @file CAN_NIMSignal.c
 *
 * @brief Template Source File
 *
 * File Short Name: Can NIM signal
 *
 * Author: Madhavi Manthri
 *
 * Create Date: Apr 10,2024
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

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "CAN_NIM.h"
#include "Indicators_CANSignal.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
Nim_RxMsg_t Nim_CAN_CH0_RxBuffer[NUM_RX_MESSAGES];
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/*------------------------------------------RX_STRUCT_VARIABLES-------------------------------------------------------------------------*/

static struct indicators_indicator_status_t l_msg_Indicator_Status_unpacked;

/*------------------------------------------TX_STRUCT_VARIABLES-------------------------------------------------------------------------*/


/*------------------------------------------RX_MESSAGE_TIMEOUT_LIST-------------------------------------------------------------------------*/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/


/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
// Functions for message: Indicator_Status

void vNim_unPack(uint16_t msg_index, uint8_t *srcPtr)
{
	if(msg_index == 0)
	{
		indicators_indicator_status_unpack(&l_msg_Indicator_Status_unpacked, srcPtr, INDICATORS_INDICATOR_STATUS_LENGTH);
	}
}

void vNim_Pack(uint8_t msg_index, uint8_t *dstPtr)
{

}

void vNim_RxmsgInit(uint8_t msg_index, uint8_t CH_id)
{
	if(CH_id == NIM_CAN_ID_0)
	{
		if(msg_index == 0)
		{
			indicators_indicator_status_init(&l_msg_Indicator_Status_unpacked);
		}
	}
}
/**
 * @brief Get the status of the Right_Indicator signal
 *
 * This function retrieves the status of the Right_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the Right_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_right_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_right_indicator_is_in_range(l_msg_Indicator_Status_unpacked.right_indicator))
        {
            fl_data_double = indicators_indicator_status_right_indicator_decode(l_msg_Indicator_Status_unpacked.right_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the Left_Indicator signal
 *
 * This function retrieves the status of the Left_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the Left_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_left_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_left_indicator_is_in_range(l_msg_Indicator_Status_unpacked.left_indicator))
        {
            fl_data_double = indicators_indicator_status_left_indicator_decode(l_msg_Indicator_Status_unpacked.left_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the Parking_Indicator signal
 *
 * This function retrieves the status of the Parking_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the Parking_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_parking_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_parking_indicator_is_in_range(l_msg_Indicator_Status_unpacked.parking_indicator))
        {
            fl_data_double = indicators_indicator_status_parking_indicator_decode(l_msg_Indicator_Status_unpacked.parking_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the HighBeam_Indicator signal
 *
 * This function retrieves the status of the HighBeam_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the HighBeam_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_highbeam_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_high_beam_indicator_is_in_range(l_msg_Indicator_Status_unpacked.high_beam_indicator))
        {
            fl_data_double = indicators_indicator_status_high_beam_indicator_decode(l_msg_Indicator_Status_unpacked.high_beam_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the LowBeam_Indicator signal
 *
 * This function retrieves the status of the LowBeam_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the LowBeam_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_lowbeam_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_low_beam_indicator_is_in_range(l_msg_Indicator_Status_unpacked.low_beam_indicator))
        {
            fl_data_double = indicators_indicator_status_low_beam_indicator_decode(l_msg_Indicator_Status_unpacked.low_beam_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the EngineOilTemperature_Indicator signal
 *
 * This function retrieves the status of the EngineOilTemperature_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the EngineOilTemperature_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_engineoiltemperature_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_engine_oil_temperature_indicator_is_in_range(l_msg_Indicator_Status_unpacked.engine_oil_temperature_indicator))
        {
            fl_data_double = indicators_indicator_status_engine_oil_temperature_indicator_decode(l_msg_Indicator_Status_unpacked.engine_oil_temperature_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the SeatBelt_Indicator signal
 *
 * This function retrieves the status of the SeatBelt_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the SeatBelt_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_seatbelt_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_seat_belt_indicator_is_in_range(l_msg_Indicator_Status_unpacked.seat_belt_indicator))
        {
            fl_data_double = indicators_indicator_status_seat_belt_indicator_decode(l_msg_Indicator_Status_unpacked.seat_belt_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the EngineMalfunction_Indicator signal
 *
 * This function retrieves the status of the EngineMalfunction_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the EngineMalfunction_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_enginemalfunction_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_engine_malfunction_indicator_is_in_range(l_msg_Indicator_Status_unpacked.engine_malfunction_indicator))
        {
            fl_data_double = indicators_indicator_status_engine_malfunction_indicator_decode(l_msg_Indicator_Status_unpacked.engine_malfunction_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the DoorsOpen_indicator signal
 *
 * This function retrieves the status of the DoorsOpen_indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the DoorsOpen_indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_doorsopen_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_doors_open_indicator_is_in_range(l_msg_Indicator_Status_unpacked.doors_open_indicator))
        {
            fl_data_double = indicators_indicator_status_doors_open_indicator_decode(l_msg_Indicator_Status_unpacked.doors_open_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the ABSWarning_Indicator signal
 *
 * This function retrieves the status of the ABSWarning_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the ABSWarning_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_abswarning_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_abs_warning_indicator_is_in_range(l_msg_Indicator_Status_unpacked.abs_warning_indicator))
        {
            fl_data_double = indicators_indicator_status_abs_warning_indicator_decode(l_msg_Indicator_Status_unpacked.abs_warning_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the FaultyRight_Indicator signal
 *
 * This function retrieves the status of the FaultyRight_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the FaultyRight_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_faultyright_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_faulty_right_indicator_is_in_range(l_msg_Indicator_Status_unpacked.faulty_right_indicator))
        {
            fl_data_double = indicators_indicator_status_faulty_right_indicator_decode(l_msg_Indicator_Status_unpacked.faulty_right_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the FaultyLeft_Indicator signal
 *
 * This function retrieves the status of the FaultyLeft_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the FaultyLeft_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_faultyleft_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_faulty_left_indicator_is_in_range(l_msg_Indicator_Status_unpacked.faulty_left_indicator))
        {
            fl_data_double = indicators_indicator_status_faulty_left_indicator_decode(l_msg_Indicator_Status_unpacked.faulty_left_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/**
 * @brief Get the status of the EngineOil_Indicator signal
 *
 * This function retrieves the status of the EngineOil_Indicator signal
 * and returns its decoded value if the signal is within range. It also updates the
 * signal status parameter with the status of the CAN message.
 *
 * @param[out] sigStatus Pointer to the status of the CAN message
 *
 * @return Decoded value of the EngineOil_Indicator signal if within range,
 *         otherwise returns 0 and updates sigStatus with SIG_INVALID if the signal is
 *         out of range, or returns 0 and updates sigStatus with MSG_MISSING_CONFIRMED
 *         if the message is missing or never received.
 */
double vNim_get_indicator_status_engineoil_indicator(CanRxStatus_t *sigStatus)
{
    double fl_data_double = 0;

    *sigStatus = Nim_CAN_CH0_RxBuffer[INDICATOR_STATUS_INDEX].l_rxStatus_U8;

    if (*sigStatus == MSG_PROCESSED)
    {
        if (indicators_indicator_status_engine_oil_indicator_is_in_range(l_msg_Indicator_Status_unpacked.engine_oil_indicator))
        {
            fl_data_double = indicators_indicator_status_engine_oil_indicator_decode(l_msg_Indicator_Status_unpacked.engine_oil_indicator);
        }
        else
        {
            *sigStatus = SIG_INVALID;
            /** Signal received is invalid. Return error handling value as per the product spec */
        }
    }
    else
    {
        *sigStatus = MSG_MISSING_CONFIRMED;
        /** The CAN signal is either missing or never received
         * Return error handling value as per the product spec
         */
    }
    return fl_data_double;
}


/*------------------------------------------TX_UPDATE_DEFINATIONS-------------------------------------------------------------------------*/


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
