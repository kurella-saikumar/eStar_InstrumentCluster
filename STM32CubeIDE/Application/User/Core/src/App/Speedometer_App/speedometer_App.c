/** \addtogroup  
 *  @{
 * @file Speedometer.c
 * @file Speedometer.h
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
 * File:   Speedometer.c
 * Author: ravit
 *
 * Created on February 22, 2024, 4:10 PM
 */

#ifndef SPEEDOMETER_C
#define	SPEEDOMETER_C


/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "speedometer_App.h"
//#include "../Speedometer_App_test/speedometer_App_Test.h"
#include "IGN_SmHandler.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
/**Speedometer configuration parameters*/
speedDisplayMetrics_t defaultSpeedoUnits = 0;
speedDisplayMetrics_t speedoUnits = 0;
bool safeSpeedLimitExceededFlag = 0;

/**Km configuration parameters*/
uint32_t gl_mts_to_km_dist_conv_factor_speed_u32 = 0;
uint32_t gl_sec_to_hr_time_conv_factor_u32 = 0;
uint32_t gl_pulse_multi_factor_speed_u32 = 0;
uint32_t gl_pulsesPer100MetersSpeed_u32 = 0;
uint32_t gl_timeInSecs_u32 = 0;
uint8_t gl_safeThresholdSpeedInKm_u8 = 0;
uint32_t fl_maxVehicleSpeedInKm_u32 = 0;

/**Miles configuration parameters*/
uint8_t gl_safeThresholdSpeedInMiles_u8 = 0;
uint32_t fl_maxVehicleSpeedInMiles_u32 = 0;
uint8_t gl_kmToMilesDivisionFactor_u8 = 0;
uint8_t gl_km_to_miles_speed_multi_factor_u32 = 0;

/**Speedometer variables*/
bool ignitionStatus_speed = 0;
int32_t fl_delta_i32 = 0;
uint32_t fl_currentReceivedPulses_u32 = 0;
uint32_t fl_previousReceivedPulses_u32 = 0;

/**km variables*/
uint32_t fl_distanceInMts_32 = 0;
uint32_t fl_pulse100mCountRatio_u32 = 0;
uint32_t fl_receivedPulses_u32 = 0;
uint32_t fl_distanceInKm_u32 = 0;
uint32_t fl_timeInHr_u32 = 0;
uint32_t gl_speedInkm_u32 = 0;

/**miles variables*/
uint32_t gl_speedInMiles_u32 = 0;

IndicationStatus_t IndicationStatus;
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
 * @brief Initialize the Speedometer 
 *
 * This function initializes the Speedometer, setting up any necessary configurations or resources required for its operation
 *
 * @param void
 *
 * @return void
 *
 */
void vSpeedoInit(void)
{
    defaultSpeedoUnits = SPEED_IN_KMPH;
    speedoUnits = defaultSpeedoUnits;
    vInitializeSpeedometer();
    //printf("Speedometer initialization...\r\n");
    xLoadToEEPROM();
}

void vInitializeSpeedometer(void)
{
    /**Km configuration parameters*/
	gl_mts_to_km_dist_conv_factor_speed_u32 = MTS_TO_KM_DIST_CONV_FACTOR;
	gl_sec_to_hr_time_conv_factor_u32 = SEC_TO_HR_TIME_CONV_FACTOR;
	gl_pulse_multi_factor_speed_u32 = PULSE_MULTI_FACTOR;
    gl_pulsesPer100MetersSpeed_u32 = PULSES_PER_100_METERS;
    gl_timeInSecs_u32 = TIME_IN_SECS;
    gl_safeThresholdSpeedInKm_u8 = SAFE_THRESHOLD_VEH_SPEED_IN_KM;
    fl_maxVehicleSpeedInKm_u32 = MAX_VEH_SPEED_IN_KM;

/**Miles configuration parameters*/
    gl_kmToMilesDivisionFactor_u8 = KM_TO_MILES_DIV_FACTOR;
    gl_km_to_miles_speed_multi_factor_u32 = KM_TO_MILES_MULTI_FACTOR;
    gl_safeThresholdSpeedInMiles_u8 = SAFE_THRESHOLD_VEH_SPEED_IN_MILES;
    fl_maxVehicleSpeedInMiles_u32 = MAX_VEH_SPEED_IN_MILES;

}
void xLoadToEEPROM(void)
{
#if(SpeedoTestMacro == 1)
   printf("Config parameters loaded to EEPROM...\r\n");
#endif
}
 /**
 * @brief Speed calculation algorithm
 *
 * This API is designed to take count of generated pulses as input within periodic intervals, calculate the speed, and update it with the latest values
 *
 *@return Void.
 */ 
void vSpeedoAlgorithm(void)
{   
	 uint8_t ignitionStatus=0;
	 ignitionStatus = usIgnitionGetCurrentState();
	 if(ignitionStatus == IgnOFF_mode)
    {
#if(SpeedoTestMacro == 1)
		printf("Speedometer Ignition: OFF\n");
#endif
		gl_speedInkm_u32 = 0;
		gl_speedInMiles_u32 = 0;
    }
    else    
    {        
        vCalculateSpeed();
    }
}
/**
 * @brief Distance calculation
 *
 * The API is designed to calculate the distance travelled by the vehicle, upon processing the no. of pulse count received as Input in between the periodic intervals
 *
 *@return Void.
 */
void vCalculateSpeed(void)
{    
    if(speedoUnits == SPEED_IN_KMPH)
        vCalculateSpeedInKm();
    else
        vCalculateSpeedInMiles();   
}

void vCalculateSpeedInKm(void)
{
	fl_receivedPulses_u32 = vPulseDeltaCounter();
    
	fl_pulse100mCountRatio_u32 = (fl_receivedPulses_u32 / gl_pulsesPer100MetersSpeed_u32);
    fl_distanceInMts_32 = fl_pulse100mCountRatio_u32 * gl_pulse_multi_factor_speed_u32;
    
    fl_distanceInKm_u32 = ( fl_distanceInMts_32 * gl_mts_to_km_dist_conv_factor_speed_u32 );
    fl_timeInHr_u32 = gl_timeInSecs_u32 * gl_sec_to_hr_time_conv_factor_u32;
            
    gl_speedInkm_u32 = ( fl_distanceInKm_u32 / fl_timeInHr_u32);
#if(SpeedoTestMacro == 1)
    /**Debug purpose*/
    printf("Sd: %ld\t",fl_receivedPulses_u32);
    printf("dm: %ld\tdK: %ld\ttH: %lu\t", fl_distanceInMts_32, fl_distanceInKm_u32, fl_timeInHr_u32);
    printf("sK: %ld\t", gl_speedInkm_u32);
    printf("dU: %d\t", speedoUnits);
    printf("dI: %d\t\n\n\r", xSafeSpeedCheck());
#endif
}

void vCalculateSpeedInMiles(void)
{
    vCalculateSpeedInKm();
    gl_speedInMiles_u32 = ( (gl_speedInkm_u32 * gl_km_to_miles_speed_multi_factor_u32) / gl_kmToMilesDivisionFactor_u8 );
    //printf("sM: %d\t", gl_speedInMiles_u32);   //Debug purpose
}

uint32_t vPulseDeltaCounter(void)
{
	fl_currentReceivedPulses_u32 = xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	fl_delta_i32 = fl_currentReceivedPulses_u32 - fl_previousReceivedPulses_u32;

	if(fl_delta_i32 < 0 )
	{
		fl_delta_i32 = UINT32_MAX + fl_delta_i32;
	}

	fl_previousReceivedPulses_u32 =  fl_currentReceivedPulses_u32;
	return fl_delta_i32;
}

bool xSafeSpeedCheck(void)
{
    if(speedoUnits == SPEED_IN_KMPH)
    {
        if(gl_speedInkm_u32 > gl_safeThresholdSpeedInKm_u8)
        {
            safeSpeedLimitExceededFlag = 1;
        }
        else
        {
            safeSpeedLimitExceededFlag = 0;
        }
    }
    else if(speedoUnits == SPEED_IN_MPH)
    {
        if(gl_speedInkm_u32 > gl_safeThresholdSpeedInMiles_u8)
        {
            safeSpeedLimitExceededFlag = 1;
        }
        else
        {
            safeSpeedLimitExceededFlag = 0;
        }
    }
    else
    {
        //do nothing
    }
    //printf("hSF: %d\n", safeSpeedLimitExceededFlag);   //Debug purpose
    return safeSpeedLimitExceededFlag;
}

/**
 * @brief Customize Odo units
 *
 * This function is designed to configure vehicle Speed units, in between kilometers and miles
 *
 * @param void
 *
 * @return void
 */
void vCustomizeSpeedUnits(void)
{
    if(speedoUnits == SPEED_IN_KMPH)
    {
        speedoUnits = SPEED_IN_MPH;
    }
    else
    {
        speedoUnits = SPEED_IN_KMPH;
    //printf("u: %d\t", speedoUnits);   //Debug purpose
    }
}

/**
 * @brief Provides Speed value
 * 
 * This function is designed to provide the latest updated Speed readings at the same time it need to update the out parameters namely SpeedoUnits and speedStatus
 *
 *@param SpeedoUnits  It provides the vehicle's Speedo Units information
 *
 * @param speedStatus It provides the information indicating that the speed value has exceeded the safe threshold limit.
 * 
 * @return uint16_t  This return parameter provides the latest updated Speed value
 */
uint32_t xGetSpeedValue(speedDisplayMetrics_t *speedDisplayUnits, IndicationStatus_t *speedStatus)
{
    *speedDisplayUnits = speedoUnits;

    if(xSafeSpeedCheck())
    {
    	speedStatus->indicators.over_speed_indicator = 1;

//    printf("dU: %d\t", speedDisplayUnits);   //Debug purpose
//    printf("dI: %d\t", speedStatus);   //Debug purpose
    }

		if(speedoUnits == SPEED_IN_KMPH)
		{
			return gl_speedInkm_u32;
		}
		else if(speedoUnits == SPEED_IN_MPH)
		{
			return gl_speedInMiles_u32;
		}
 return 0;
}

#endif	/* SPEEDOMETER_C */

