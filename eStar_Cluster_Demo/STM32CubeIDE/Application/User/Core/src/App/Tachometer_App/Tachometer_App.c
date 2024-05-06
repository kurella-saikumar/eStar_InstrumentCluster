/** \addtogroup  
 *  @{
 * @file Tachometer.c
 * @file Tachometer.h
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
#include "IGN_SmHandler.h"
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
	uint32_t gl_rpm_u32 = 0;
	uint32_t fl_previousCapture_u32 = 0;
	uint32_t fl_presentCapture_u32 = 0;
	int32_t fl_deltaPulses_i32 = 0;
	uint32_t fl_frequency_u32 = 0;





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

void vTacho_Init(void)
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

	fl_presentCapture_u32 = xGetRollingPulseCount(1);
	fl_deltaPulses_i32 = fl_presentCapture_u32 - fl_previousCapture_u32;

    if(fl_deltaPulses_i32 < 0)
    {

    	fl_deltaPulses_i32 = UINT32_MAX + fl_deltaPulses_i32;
    }
    fl_frequency_u32 = (fl_deltaPulses_i32) / TIME; // Assuming TIME is in seconds

    if(fl_frequency_u32 >= (UINT32_MAX / 60))
    {
    	gl_rpm_u32= UINT32_MAX;
    }
    else
    {
    	gl_rpm_u32 = ((fl_frequency_u32 * 60) / FIXED_PPR_VALUE);
    }
#if(TachoTestMacro == 1)
    //printf("Ap: %ld\r\t",fl_presentCapture_u32);
      printf("Td: %ld\t",fl_deltaPulses_i32);
//    printf("pv:%ld\r\t",fl_previousCapture_u32);
//    gl_rpm_u32 = ( fl_presentCapture_u32 / 16)* 1000;
//    printf("rpm %lu\r\n", gl_rpm_u32);
      printf("RPM:%ld\n\r",gl_rpm_u32);
#endif
      fl_previousCapture_u32 = fl_presentCapture_u32;

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
     
    if( gl_rpm_u32 >= MAXIMUM_ENGINE_RPM || gl_rpm_u32 <= IDLE_ENGINE_RPM)
    {

        Indication->indicators.tachometer_indicator = 1;
        *status = true;
        gl_rpm_u32 = 0;
#if(TachoTestMacro == 1)
        printf("warning\t");
#endif

    }
#if(TachoTestMacro == 1)
    printf("RPM: %ld\n\r", gl_rpm_u32);
#endif

    	return gl_rpm_u32;
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
void vTacho_App(void)
{   

    uint8_t l_ignitionStatus_u8=0;
    l_ignitionStatus_u8 = usIgnitionGetCurrentState();
//   // printf("IgnitionStatus: %i\r\n", ignitionStatus);  debug purpose
    if(l_ignitionStatus_u8 == IgnOFF_mode)
    {
    	gl_rpm_u32 = 0;

#if(TachoTestMacro == 1)
        printf("Tachometer Ignition: OFF\n\r");
#endif
    }
    else
    {
   	 IndicationStatus_t Indication;
	 bool status = false;
    	 vMeasureRPM();
 	 xGet_TachometerData(&Indication,&status);
    }
    
   
}
#endif	/* TACHOMETER_C */

