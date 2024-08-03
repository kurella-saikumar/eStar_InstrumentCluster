/** \addtogroup  
 *  @{
 * @file Speedometer_App.c
 * @file Speedometer_App.h
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
uint32_t ulMtsToKmDistConvFactorSpeed = 0;
uint32_t ulSecToHrTimeConvFactor = 0;
uint32_t ulPulseMultiFactorSpeed = 0;
uint32_t ulPulsesPer100MetersSpeed = 0;
uint32_t ulTimeInSecs = 0;
uint8_t ucSafeThresholdSpeedInKm = 0;
uint32_t ulMaxVehicleSpeedInKm = 0;

/**Miles configuration parameters*/
uint8_t ucSafeThresholdSpeedInMiles = 0;
uint32_t ulMaxVehicleSpeedInMiles = 0;
uint16_t ucKmToMilesDivisionFactor = 0;
uint16_t ucKmToMilesSpeedMultiFactor = 0;

/**Speedometer variables*/
bool ignitionStatus_speed = 0;
int64_t sllDelta = 0;
uint32_t ulCurrentReceivedPulses = 0;
uint32_t ulPreviousReceivedPulses = 0;
uint32_t ulSpeedValue = 0;

/**km variables*/
uint8_t ucPulsesPerMeter = 0;
uint32_t ulDistanceInMts = 0;
uint32_t ulPulse100mCountRatio = 0;
uint32_t ulReceivedPulses = 0;
uint32_t ulDistanceInKm = 0;
uint32_t ulTimeInHr = 0;
uint32_t ulSpeedInMtsPerSec = 0;
uint32_t ulSpeedInKm = 0;

/**miles variables*/
uint32_t ulspeedInMiles = 0;


uint32_t prevSpeedVal = 0;
uint32_t presSpeedVal = 0;
uint32_t deltaSpeed = 0;
//IndicationStatus_t IndicationStatus;
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
    xLoadToEEPROM();

#if(SPEEDO_TEST_MACRO == 1)
    printf("Speedometer initialization...\r\n");
#endif
}

/**************************************************************************************************/
void vInitializeSpeedometer(void)
{
    /**Km configuration parameters*/
	ulMtsToKmDistConvFactorSpeed 	= configMTS_TO_KM_DIST_CONV_FACTOR;
	ulSecToHrTimeConvFactor 		= configSEC_TO_HR_TIME_CONV_FACTOR;
	ulPulseMultiFactorSpeed 		= configPULSE_MULTI_FACTOR;
	ucPulsesPerMeter 				= configPULSES_PER_1_METER;
	ulPulsesPer100MetersSpeed 		= configPULSES_PER_100_METERS;
	ulTimeInSecs 					= configTIME_IN_SECS;
	ucSafeThresholdSpeedInKm 		= configSAFE_THRESHOLD_VEH_SPEED_IN_KM;
	ulMaxVehicleSpeedInKm 			= configMAX_VEH_SPEED_IN_KM;

/**Miles configuration parameters*/
	ucKmToMilesDivisionFactor 		= configKM_TO_MILES_DIV_FACTOR;
	ucKmToMilesSpeedMultiFactor 	= configKM_TO_MILES_MULTI_FACTOR;
    ucSafeThresholdSpeedInMiles 	= configSAFE_THRESHOLD_VEH_SPEED_IN_MILES;
    ulMaxVehicleSpeedInMiles 		= configMAX_VEH_SPEED_IN_MILES;
}

/**************************************************************************************************/
void xLoadToEEPROM(void)
{
#if(SPEEDO_TEST_MACRO == 1)
   printf("Config parameters loaded to EEPROM...\r\n");
#endif
}

/**************************************************************************************************/
 /**
 * @brief Speed calculation algorithm
 *
 * This API is designed to take count of generated pulses as input within periodic intervals, calculate the speed, and update it with the latest values
 *
 *@return Void.
 */ 
void vSpeedoAlgorithm(void)
{   
	 uint8_t ucIgnitionStatus=0;
	 ucIgnitionStatus = usIgnitionGetCurrentState();
	 if(ucIgnitionStatus == IgnOFF_mode)
    {

		 ulSpeedInKm = 0;
		 ulspeedInMiles = 0;
#if(SPEEDO_TEST_MACRO == 1)
		printf("Speedometer Ignition: OFF\n");
#endif
    }
    else    
    {

        vCalculateSpeed();
    }
}

/**************************************************************************************************/
/**
 * @brief Distance calculation
 *
 * The API is designed to calculate the distance travelled by the vehicle, upon processing the no. of pulse count received as Input in between the periodic intervals
 *
 *@return Void.
 */
void vCalculateSpeed(void)
{
	speedoUnits = xGetToggleMetrics();
    if(speedoUnits == SPEED_IN_KMPH)
        vCalculateSpeedInKm();
    else
        vCalculateSpeedInMiles();   
}

/**************************************************************************************************/
void vCalculateSpeedInKm(void)
{
	ulReceivedPulses = vPulseDeltaCounter();
//	ulReceivedPulses = 42; /*Simulation*/
	ulDistanceInMts = ( (ulReceivedPulses*10) / ucPulsesPerMeter );
	ulSpeedInMtsPerSec = ( (ulDistanceInMts * configMILLI_SEC_TO_SECS_CONV_FACTOR) / configSPEEDO_TASK_PERIODICITY_IN_MS );
	ulSpeedInKm = ((ulSpeedInMtsPerSec * configSEC_TO_HR_TIME_CONV_FACTOR) / configMTS_TO_KM_DIST_CONV_FACTOR );
	ulSpeedInKm = (ulSpeedInKm/10);
	vValidateSpeed();

#if(SPEEDO_TEST_MACRO == 1)
    /**Debug purpose*/
	printf("sU: %ld\t", speedoUnits);
    printf("dP: %ld\t",ulReceivedPulses);
    printf("m/s: %ld\t", ulSpeedInMtsPerSec);
    printf("k/h: %ld", ulSpeedInKm);
    if(speedoUnits == SPEED_IN_KMPH)
        	printf("\n\n");
        else
        	printf("\t");
#endif
}

/**************************************************************************************************/
void vCalculateSpeedInMiles(void)
{
    vCalculateSpeedInKm();
//    ulspeedInMiles = ( (ulSpeedInKm * ucKmToMilesSpeedMultiFactor) / ucKmToMilesDivisionFactor );
    ulspeedInMiles = ( (ulSpeedInKm * 1000) / 1609 );
#if(SPEEDO_TEST_MACRO == 1)
    printf("M/h: %d\n\n", ulspeedInMiles);   //Debug purpose
    printf("Multi: %d\tDiv: %d\n", ucKmToMilesSpeedMultiFactor, configKM_TO_MILES_DIV_FACTOR);
#endif

}

/**************************************************************************************************/
void vValidateSpeed(void)
{
	if(ulSpeedInKm > configMAX_VEH_SPEED_IN_KM)
	{
		ulSpeedInKm = configSPEED_ERROR;
    #if(SPEEDO_TEST_MACRO == 1)
            printf("Error in Speed\n");
    #endif
	}
    else
    {
        /*do nothing*/
    }
}

/**************************************************************************************************/
uint32_t vPulseDeltaCounter(void)
{
	ulCurrentReceivedPulses = xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	sllDelta = ulCurrentReceivedPulses - ulPreviousReceivedPulses;

	if(sllDelta < 0 )
	{
		sllDelta = UINT32_MAX + sllDelta;
	}

	ulPreviousReceivedPulses =  ulCurrentReceivedPulses;
	return sllDelta;
}

/**************************************************************************************************/
bool xSafeSpeedCheck(void)
{
    if(speedoUnits == SPEED_IN_KMPH)
    {
        if(ulSpeedInKm > ucSafeThresholdSpeedInKm)
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
        if(ulspeedInMiles > ucSafeThresholdSpeedInMiles)
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

/**************************************************************************************************/
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
    }
}

/**************************************************************************************************/
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
uint32_t xGetSpeedValue(void)
{
//    *speedDisplayUnits = speedoUnits;

    Status.indicators.over_speed_indicator = 0;

    if(xSafeSpeedCheck())
    {
    	Status.indicators.over_speed_indicator = 1;
    }

	if(speedoUnits == SPEED_IN_KMPH)
	{
		ulSpeedValue = ulSpeedInKm;
	}
	else if(speedoUnits == SPEED_IN_MPH)
	{
		ulSpeedValue = ulspeedInMiles;
	}
	prvSpeedDampOut();
	return ulSpeedValue;
}

/**************************************************************************************************/
uint32_t GetSpeedValueInKM(void)
{
	return ulSpeedInKm;
}
/**************************************************************************************************/
void prvSpeedDampOut(void)
{
	presSpeedVal = ulSpeedValue;
	if(prevSpeedVal > presSpeedVal)
		deltaSpeed = prevSpeedVal - presSpeedVal;
	else
		deltaSpeed = presSpeedVal - prevSpeedVal;

	if(deltaSpeed > 2)
	{
		ulSpeedValue = presSpeedVal;
		prevSpeedVal = presSpeedVal;
	}
	else
	{
		ulSpeedValue = prevSpeedVal;
	}
}
/**************************************************************************************************/
#endif	/* SPEEDOMETER_C */
