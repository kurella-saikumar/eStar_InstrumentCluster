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
//bool ignitionStatus_speed = 0;
int64_t sllDelta = 0;
uint32_t ulCurrentReceivedPulses = 0;
uint32_t ulPreviousReceivedPulses = 0;
uint32_t ulSpeedValue = 0;

/**km variables*/
uint8_t ucPulsesPerMeter = 0;
uint32_t ulDistanceInMts = 0;
//uint32_t ulPulse100mCountRatio = 0;
uint32_t ulReceivedPulses = 0;
//uint32_t ulDistanceInKm = 0;
//uint32_t ulTimeInHr = 0;
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
/**
 * @brief Initialize the Speedometer
 *
 * This function initializes the Speedometer by configuring the necessary parameters for speed calculation
 * in both kilometers and miles, including conversion factors, pulse factors, and speed thresholds.
 *
 * @param[in] void
 *
 * @return void
 *
 */
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
/**
 * @brief Load Configuration Parameters to EEPROM
 *
 * This function simulates loading configuration parameters to EEPROM.
 * @param[in] void
 *
 * @return void
 *
 */
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
/**
 * @brief Calculate Speed in Kilometers per Hour
 *
 * This function calculates the speed in kilometers per hour (KMPH) based on received pulses.
 * @param[in] void
 *
 * @return void
 *
 */
void vCalculateSpeedInKm(void)
{
    ulReceivedPulses = vPulseDeltaCounter();

    if (ulReceivedPulses < (UINT32_MAX / 10))
    {
        ulDistanceInMts = (ulReceivedPulses * 10) / ucPulsesPerMeter;

        if (ulDistanceInMts < (UINT32_MAX / configMILLI_SEC_TO_SECS_CONV_FACTOR))
        {
            ulSpeedInMtsPerSec = ( (ulDistanceInMts * configMILLI_SEC_TO_SECS_CONV_FACTOR) / configSPEEDO_TASK_PERIODICITY_IN_MS );

            if (ulSpeedInMtsPerSec < (UINT32_MAX / ulSecToHrTimeConvFactor))
            {
                ulSpeedInKm = ((ulSpeedInMtsPerSec * ulSecToHrTimeConvFactor) / ulMtsToKmDistConvFactorSpeed );
                ulSpeedInKm /= 10;

                vValidateSpeed();

                #if (SPEEDO_TEST_MACRO == 1)
                    printf("sU: %ld\t", speedoUnits);
                    printf("dP: %ld\t", ulReceivedPulses);
                    printf("m/s: %ld\t", ulSpeedInMtsPerSec);
                    printf("k/h: %ld", ulSpeedInKm);

                    if (speedoUnits == SPEED_IN_KMPH)
                        printf("\n\n");
                    else
                        printf("\t");
                #endif
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else
    {
    }
}

/**************************************************************************************************/
/**
 * @brief Calculate Speed in Miles
 *
 * This function calculates the speed in miles based on received pulses.
 * @param[in] void
 *
 * @return void
 *
 */
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
/**
 * @brief Validate the Speed Value
 *
 * This function checks if the current speed in kilometers per hour (KMPH) exceeds the maximum allowable
 * vehicle speed. If it does, the speed is set to an error value.
 *
 * @param[in] void
 *
 * @return void
 *
 */
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
/**
 * @brief Calculate the Pulse Delta Counter
 *
 * This function calculates the pulse difference between the current and previous counts, adjusting for rollover if the delta is negative.
 *
 * @param[in] void
 *
 * @return uint32_t The calculated pulse delta.
 *
 */
uint32_t vPulseDeltaCounter(void)
{
	ulCurrentReceivedPulses = xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	sllDelta =(int64_t)ulCurrentReceivedPulses - (int64_t)ulPreviousReceivedPulses;

	if(sllDelta < 0 )
	{
		sllDelta = UINT32_MAX + sllDelta;
	}

	ulPreviousReceivedPulses =  ulCurrentReceivedPulses;
	return (uint32_t)sllDelta;
}

/**************************************************************************************************/
/**
 * @brief Check if the Speed Exceeds the Safe Limit
 *
 * This function checks whether the current speed exceeds the safe threshold based on the selected
 * speed unit (KMPH or MPH) and sets a flag accordingly.
 *
 * @param[in] void
 *
 * @return bool Returns true if the safe speed limit is exceeded, false otherwise.
 *
 */
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
 *@param void
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
/**
 * @brief Get the Current Speed in Kilometers per Hour (KMPH)
 *
 * This function returns the current speed value in kilometers per hour.
 *
 * @param[in] void
 *
 * @return uint32_t The current speed in KMPH.
 *
 */
uint32_t xGetSpeedValueInKM(void)
{
	return ulSpeedInKm;
}
/**************************************************************************************************/
/**
 * @brief Dampen Speed Value Fluctuations
 *
 * This function smooths out speed value fluctuations by comparing the current speed with the previous one.
 * If the speed difference exceeds a threshold, the current speed is updated; otherwise, the previous speed is retained.
 *
 * @param[in] void
 *
 * @return void
 *
 */
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
