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
uint32_t mts_to_km_dist_conv_factor_speed = 0;
uint32_t sec_to_hr_time_conv_factor = 0;
uint32_t pulse_multi_factor_speed = 0;
uint32_t pulsesPer100Meters_speed = 0;
uint32_t timeInSecs = 0;
uint8_t safeThresholdSpeedInKm = 0;
uint32_t maxVehicleSpeedInKm = 0; 

/**Miles configuration parameters*/
uint8_t safeThresholdSpeedInMiles = 0;
uint32_t maxVehicleSpeedInMiles = 0;
uint8_t kmToMilesDivisionFactor = 0;
uint8_t km_to_miles_speed_multi_factor = 0;

/**Speedometer variables*/
bool ignitionStatus_speed = 0;
int32_t delta = 0;
uint32_t currentReceivedPulses = 0;
uint32_t previousReceivedPulses = 0;

/**km variables*/
uint32_t distanceInMts = 0;
uint32_t pulse100mCountRatio = 0;
uint32_t receivedPulses = 0;
uint32_t distanceInKm = 0;
uint32_t timeInHr = 0;
uint32_t speedInkm = 0;

/**miles variables*/
uint32_t speedInMiles = 0;

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
    printf("Speedometer initialization...\r\n");
    xLoadToEEPROM();
}

void vInitializeSpeedometer(void)
{
    /**Km configuration parameters*/
	mts_to_km_dist_conv_factor_speed = MTS_TO_KM_DIST_CONV_FACTOR;
    sec_to_hr_time_conv_factor = SEC_TO_HR_TIME_CONV_FACTOR;
    pulse_multi_factor_speed = PULSE_MULTI_FACTOR;
    pulsesPer100Meters_speed = PULSES_PER_100_METERS;
    timeInSecs = TIME_IN_SECS;
    safeThresholdSpeedInKm = SAFE_THRESHOLD_VEH_SPEED_IN_KM;
    maxVehicleSpeedInKm = MAX_VEH_SPEED_IN_KM; 

/**Miles configuration parameters*/
    kmToMilesDivisionFactor = KM_TO_MILES_DIV_FACTOR;
    km_to_miles_speed_multi_factor = KM_TO_MILES_MULTI_FACTOR;
    safeThresholdSpeedInMiles = SAFE_THRESHOLD_VEH_SPEED_IN_MILES;
    maxVehicleSpeedInMiles = MAX_VEH_SPEED_IN_MILES;

}
void xLoadToEEPROM(void)
{
   printf("Config parameters loaded to EEPROM...\r\n");
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
		printf("Speedometer Ignition: OFF\n");
        speedInkm = 0;
        speedInMiles = 0;
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
	receivedPulses = vPulseDeltaCounter();
    
    pulse100mCountRatio = (receivedPulses / pulsesPer100Meters_speed);
    distanceInMts = pulse100mCountRatio * pulse_multi_factor_speed;
    
    distanceInKm = ( distanceInMts * mts_to_km_dist_conv_factor_speed );
    timeInHr = timeInSecs * sec_to_hr_time_conv_factor;
            
    speedInkm = ( distanceInKm / timeInHr);
    
    //printf("Sd: %ld\t",receivedPulses);
    //printf("dm: %ld\tdK: %ld\ttH: %lu\t", distanceInMts, distanceInKm, timeInHr);   //Debug purpose
    printf("sK: %ld\n", speedInkm);   //Debug purpose
    //printf("dU: %d\t\r", speedoUnits);   //Debug purpose
   // printf("dI: %d\t\r\n", xSafeSpeedCheck());   //Debug purpose
}

void vCalculateSpeedInMiles(void)
{
    vCalculateSpeedInKm();
    speedInMiles = ( (speedInkm * km_to_miles_speed_multi_factor) / kmToMilesDivisionFactor );
    //printf("sM: %d\t", speedInMiles);   //Debug purpose
}

uint32_t vPulseDeltaCounter(void)
{
	currentReceivedPulses = xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	delta = currentReceivedPulses - previousReceivedPulses;

	if(delta < 0 )
	{
		delta = UINT32_MAX + delta;
	}

	previousReceivedPulses = currentReceivedPulses;
	return delta;
}

bool xSafeSpeedCheck(void)
{
    if(speedoUnits == SPEED_IN_KMPH)
    {
        if(speedInkm > safeThresholdSpeedInKm)
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
        if(speedInkm > safeThresholdSpeedInMiles)
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

		if(speedoUnits == SPEED_IN_KMPH)
		{
			return speedInkm;
		}
		else if(speedoUnits == SPEED_IN_MPH)
		{
			return speedInMiles;
		}
    }
}

#endif	/* SPEEDOMETER_C */

