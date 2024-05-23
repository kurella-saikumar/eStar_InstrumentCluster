/** \addtogroup  
 *  @{
 * @file Tachometer_App.c
 * @file Tachometer_App.h
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
 * File:   Tachometer.c
 * Author: 
 *
 */

#ifndef TACHOMETER_C
#define	TACHOMETER_C


/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

#include"Tachometer_App.h"
#include"stdio.h"
#include "inttypes.h"
#include "IGN_SmHandler.h"
#include "Task_ExeTime.h"
#include "DemoApplication.h"
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

	uint32_t ulRpm = 0;
	uint32_t ulPreviousCapture = 0;
	uint32_t ulPresentCapture = 0;
	int32_t slDeltaPulse = 0;
	uint32_t ulFrequency = 0;







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
* @brief This function returns the current state of the Ignition switch
*
* @param[in] void
*
* @return current state of Ignition switch
*
*/

/**
 * @brief Initialize the tachometer.
 *
 * This function initializes the tachometer, setting up any necessary
 * configurations or resources required for its operation.
 *
 * @return void
*/

void vTachoInit(void)
{

}
/** 
* @brief Measures the revolutions per minute (RPM) of a static unit.
 *
* This function calculates and returns the RPM of a static unit.
* The actual implementation details may vary based on the specific requirements.
 *
 * @return uint32_t  The measured RPM of the static unit. 
*/
//gl_pulses_u32

void vMeasureRPM(void)
{

	ulPresentCapture = xGetRollingPulseCount(1);
	slDeltaPulse = ulPresentCapture - ulPreviousCapture;

    if(slDeltaPulse < 0)
    {

    	slDeltaPulse = UINT32_MAX + slDeltaPulse;
    }
    ulFrequency = (slDeltaPulse) / configTIME; // Assuming TIME is in seconds

    if(ulFrequency >= (UINT32_MAX / 60))
    {
    	ulRpm= UINT32_MAX;
    }
    else
    {
    	ulRpm = ((ulFrequency * 60) / configFIXED_PPR_VALUE);
    }
#if(TACHO_TEST_MACRO == 1)
    //printf("Ap: %ld\r\t",ulPresentCapture);
    printf("Td: %ld\t", slDeltaPulse);
//    printf("pv:%ld\r\t",ulPreviousCapture);
//    ulRpm = ( ulPresentCapture / 16)* 1000;
//    printf("rpm %lu\r\n", ulRpm);
      printf("RPM:%ld\n\r",ulRpm);
#endif
      ulPreviousCapture = ulPresentCapture;

}

/**
 * @brief Get tachometer data.
 *
 * This function retrieves tachometer data and stores it in the provided
 * IndicationStatus_t structure.
 *
 * @param[out] Indication - Pointer to the structure to store tachometer data.
 *
 * @return uint16_t - The tachometer data.
 */

uint16_t xGet_TachometerData(IndicationStatus_t* Indication, bool *status)
{
	 Indication->indicators.tachometer_indicator = 0;
	 *status = false;
     
    if( ulRpm >= configMAXIMUM_ENGINE_RPM || ulRpm <= configIDLE_ENGINE_RPM)
    {

        Indication->indicators.tachometer_indicator = 1;
        *status = true;
        ulRpm = 0;
#if(TACHO_TEST_MACRO == 1)
        printf("warning\t");
#endif

    }
#if(TACHO_TEST_MACRO == 1)
    printf("RPM: %ld\n\r", ulRpm);
#endif

    	return ulRpm;
}
/**
 * @brief Tachometer Application.
 *
 * This function represents the task responsible for handling tachometer-related
 * operations within the application.
* @note This task should be scheduled to run periodically at a frequency of * 100ms in the 
* application's
 *
 * @return void
 */
//int var;
void vTacho_App(void)
{   

    uint8_t ucIgnitionStatus=0;
    ucIgnitionStatus = usIgnitionGetCurrentState();
//   // printf("IgnitionStatus: %i\r\n", ignitionStatus);  debug purpose
   //
#if 1
    if(ucIgnitionStatus == IgnOFF_mode)
      {
    	ulRpm = 0;

#if(TACHO_TEST_MACRO == 1)
        printf("Tachometer Ignition: OFF\n\r");
#endif
    }
    else
    {
//    	 IndicationStatus_t Indication;
//    	 bool status = false;
    	 vMeasureRPM();
//    	 xGet_TachometerData(&Indication,&status);
    }
#endif
  //  osDelay(50);

    

   // var=0;
}
#endif	/* TACHOMETER_C */

