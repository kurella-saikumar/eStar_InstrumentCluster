/** \addtogroup  
 *  @{
 * @file Odometer_App.c
 * @file Odometer_App.h
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
 * File:   Odometer.c
 * Author: Monika
 *
 * Created on February 28, 2024, 4:10 PM
 */

#ifndef ODOMETER_C
#define	ODOMETER_C

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "Odometer_App.h"
#include "IGN_SmHandler.h"
#include "eeprom_emul.h"
#include "eeprom_emul_cfg.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
/**Configuration Constants variables*/
uint32_t ulMtsToKmDistConvFactor = 1000;
uint32_t ulPulseMultiFactor = 100;
uint8_t defaultOdoUnits = 0;

uint8_t OdometerUnits = 0;
bool ignitionStatus = 0;
uint32_t ulPulsesReceived = 0;

/**Pulse related variables*/
uint32_t ulPresentPulses = 0;
uint32_t ulPreviousPulses = 0;
int64_t sllPulsesDelta = 0;
uint32_t ulPulse100mCountRatioOdo = 0;

/*Units variables*/
uint32_t ulDistanceInMtsOdo = 0;
uint32_t ulOdoInKm = 0;
uint32_t ulOdoInMiles = 0;

/*Trip related variables*/
uint16_t usTripA = 0;
uint16_t usTripB = 0;
uint32_t ulOdoValBeforeTripAReset = 0;
uint32_t ulOdoValBeforeTripBReset = 0;

uint32_t ulOdoInEeprom = 0;
uint32_t ulUpdatedOdoValue = 0;

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
 * @brief Initialize the Odometer 
 *
 * This function initializes the Odometer, setting up any necessary configurations or resources required for its operation
 *
 * @param void
 *
 * @return void
 *
 */
void vOdoInit(void)
{
    defaultOdoUnits = ODO_IN_KM;
    OdometerUnits = defaultOdoUnits;
}

void vOdoAlgorithm(void)
{   
	 uint8_t ucIgnitionStatus=0;
	 ucIgnitionStatus = usIgnitionGetCurrentState();

	if(ucIgnitionStatus == IgnOFF_mode)
    {
#if(ODO_TEST_MACRO == 1)
		printf("Odometer Ignition: OFF\n\r");
#endif
    }
    else
    {        
        vCalculateOdo();
        vWrite_OdoVal_to_EEPROM();
    }
}

void vCalculateOdo(void)
{  
    if(OdometerUnits == ODO_IN_KM)
    {
        vCalculateOdoInKm();
    }
    else if(OdometerUnits == ODO_IN_MILES)
    {
        vCalculateOdoInMiles();   
    }
}

uint32_t vPulseCount(void)
{
	ulPresentPulses= xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	sllPulsesDelta = ulPresentPulses - ulPreviousPulses;

	if(sllPulsesDelta < 0 )
	{
		sllPulsesDelta = UINT32_MAX + sllPulsesDelta ;
	}

	ulPreviousPulses = ulPresentPulses;
	return sllPulsesDelta;
}

void vCalculateOdoInKm(void)
{
	ulPulsesReceived = vPulseCount();
	ulPulse100mCountRatioOdo = ( ulPulsesReceived / PULSES_PER_100_METERS );

    ulDistanceInMtsOdo = ulPulse100mCountRatioOdo * ulPulseMultiFactor;

    ulUpdatedOdoValue = ulOdoInEeprom + ulPulse100mCountRatioOdo;// Update OdoInEeprom with the new value
    ulOdoInEeprom = ulUpdatedOdoValue;
    ulOdoInKm = (ulOdoInEeprom/10);

#if(ODO_TEST_MACRO == 1)
    printf("P: %ld\t", ulPulsesReceived);
    printf("R:%ld\t",ulPulse100mCountRatioOdo );
    printf("EE:%ld\t", ulOdoInEeprom);
    printf("Km: %ld\n\r", ulOdoInKm);
//    if(OdometerUnits == ODO_IN_KM)
//    {
//    	printf("\n");
//    }
//    else
//    {
//    	printf("\t");
//    }
#endif
}

void vCalculateOdoInMiles(void)
{
    vCalculateOdoInKm();   
    ulOdoInMiles =(ulOdoInKm * KM_TO_MILES_CONV_FACTOR) / 1000;
#if(ODO_TEST_MACRO == 1)
    printf("Mile: %ld\n" ,ulOdoInMiles);
#endif
}

void vResetTripA_OdoReadings(void)
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
	ulOdoValBeforeTripAReset = ulOdoInEeprom;

	/*Write Odo value before Trip-A reset into the EEPROM*/
	*eepromVariables[4] = ulOdoValBeforeTripAReset;
	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[4],*eepromVariables[4],eepromVariables[4]);
	if (0 == FlashStatus)
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESWrite Success: EEVar[4]:%ld\n" ,*eepromVariables[4]);
#endif
	}
	else
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESWrite Fail:TripAReset\n");
#endif
	}

#if(ODO_TEST_MACRO == 1)
    printf("AVR: %ld\t" ,ulOdoValBeforeTripAReset);
#endif
}

uint16_t xGetTripA_OdoReading(uint8_t *TripA_Units)
{
    // Calculate the total odometer reading after the reset
	usTripA = ulOdoInEeprom -  ulOdoValBeforeTripAReset ;
    if( usTripA >= TRIP_A_MAX)
    {
    	uint16_t usDifference = 0;

    	usDifference = usTripA - TRIP_A_MAX;
    	ulOdoValBeforeTripAReset = ulOdoInEeprom - usDifference;

    	/*Write Odo value value into the EEPROM after Trip-A value reaching to it's max value*/
    	*eepromVariables[4]=ulOdoValBeforeTripAReset;
    	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[4],*eepromVariables[4],eepromVariables[4]);
    	if (0 == FlashStatus)
    	{
#if(ODO_TEST_MACRO == 1)
    		printf("ESWrite Success: EEVar[4]:%ld\n\r",*eepromVariables[4]);
#endif
    	}
    	else
    	{
#if(ODO_TEST_MACRO == 1)
    		printf("ESWrite Fail:TripAGet\n\r");
#endif
    	}

    }
    else
    {
    	/*Do nothing*/
    }

    /*Trip A value calculation*/
	usTripA = ulOdoInEeprom -  ulOdoValBeforeTripAReset;

    if (OdometerUnits == ODO_IN_KM)
    {
        *TripA_Units = ODO_IN_KM;
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-A reading in miles (1 km = 0.621371 miles)
    	usTripA = (usTripA * KM_TO_MILES_CONV_FACTOR) / 1000;
        *TripA_Units = ODO_IN_MILES;
    }

#if(ODO_TEST_MACRO == 1)
    printf("tripA: %d\t" ,usTripA);
#endif
    return usTripA; // You might need to change the return type if necessary
}

void vResetTripB_OdoReadings(void)
{
    // Store the current value of total odometer value into variable (Total odo value before Trip B reset)
	ulOdoValBeforeTripBReset = ulOdoInEeprom;

	/*Write Odo value before Trip-B reset into the EEPROM*/
	*eepromVariables[5] = ulOdoValBeforeTripBReset;
	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[5],*eepromVariables[5],eepromVariables[5]);
	if (0 == FlashStatus)
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESW_S: EE[5]:%ld\n\r",*eepromVariables[5]);
#endif
	}
	else
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESW_F\n\r");
#endif
	}
#if(ODO_TEST_MACRO == 1)
    printf("BVR: %ld\n" ,ulOdoValBeforeTripBReset);
#endif
}
uint16_t xGetTripB_OdoReading(uint8_t *TripB_Units)
{
    // Calculate the total odometer reading after the reset
	usTripB = ulOdoInEeprom -  ulOdoValBeforeTripBReset ;
    if( usTripB >= TRIP_B_MAX)
    {
    	uint16_t usDifferenceB = 0;

    	usDifferenceB = usTripB - TRIP_B_MAX;
    	ulOdoValBeforeTripBReset = ulOdoInEeprom - usDifferenceB;

    	/*Write Odo value value into the EEPROM after Trip-B value reaching to it's max value*/
    	*eepromVariables[5] = ulOdoValBeforeTripBReset;
    	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[5],*eepromVariables[5],eepromVariables[5]);
    	if (0 == FlashStatus)
    	{
#if(ODO_TEST_MACRO == 1)
    		printf("ESW_S EE[5]:%ld\n\r",*eepromVariables[5]);
#endif
    	}
    	else
    	{
#if(ODO_TEST_MACRO == 1)
    		printf("ESW_F:tripBGet\n\r");
#endif
    	}

    }
    else
    {
    	/*Do nothing*/
    }

/*Trip A value calculation*/
usTripB = ulOdoInEeprom -  ulOdoValBeforeTripBReset;

    if (OdometerUnits == ODO_IN_KM)
    {
        *TripB_Units = ODO_IN_KM;
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-A reading in miles (1 km = 0.621371 miles)
    	usTripB = (usTripB * KM_TO_MILES_CONV_FACTOR) / 1000;
        *TripB_Units = ODO_IN_MILES;
    }

#if(ODO_TEST_MACRO == 1)
    printf("tripB: %d\n\r" ,usTripB);
#endif
    return usTripB; // You might need to change the return type if necessary
}

void vWrite_OdoVal_to_EEPROM(void)
{
	/*Write odo value to EEPROM*/
	//printf("ulOdoInEeprom: %ld\n", ulOdoInEeprom);

	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[0],ulOdoInEeprom,eepromVariables[0]);
	if (0 == FlashStatus)
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESW_S EE[0]:%ld\n\r",*eepromVariables[0]);
#endif
	}
	else
	{
#if(ODO_TEST_MACRO == 1)
		printf("ESW_F:odoEEP\n\r");
#endif
	}
#if 1
	uint16_t FlashStatus2= xEE_ReadVariable32bits((uint32_t)eepromVariables[0],(uint32_t*)eepromVariables[0]);
	if (0 == FlashStatus2)
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("ESR_S:at %p:0x%lx \n\r",eepromVariables[0],*eepromVariables[0]);
#endif
	}
	else
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("ESR_F:0x%lx\n\r",FlashStatus2);
#endif
	}
#endif
}

void vRetrive_LastStored_OdoVal_from_EEPROM(void)
{
	/*Read odo value from EEPROM variable*/
	ulOdoInEeprom = *eepromVariables[0];
	ulOdoValBeforeTripAReset = *eepromVariables[4];
	ulOdoValBeforeTripBReset = *eepromVariables[5];
	ulOdoInKm = (ulOdoInEeprom/10);

#if(ODO_TEST_MACRO == 1)
	printf("Retrived Odo data from EEPROM\t");
	printf("ER_Odo: %ld\t", ulOdoInEeprom);
	printf("ER_AVR: %ld\t",ulOdoValBeforeTripAReset);
	printf("ER_BVR: %ld\n",ulOdoValBeforeTripBReset);
#endif
}

/**
 * @brief Provides Odo value
 * 
 * This function is designed to provide the latest updated Odometer readings at the same time it need to update the out parameters namely OdoUnits
 *
 *@param OdoUnits[out]  It provides the vehicle's odometer units information 
 * 
 * @return uint32_t  This return parameter provides the latest updated Odo value
 */

uint32_t xGetOdoReadings(uint8_t* OdoUnits)
{
	uint32_t xOdoValue = 0;

    if(OdometerUnits == ODO_IN_KM)
    {
       *OdoUnits = ODO_IN_KM;

       if(ulOdoInKm >= MAX_ODO_VALUE_IN_KM)
       {
    	   xOdoValue = MAX_ODO_VALUE_IN_KM;
       }
       else
       {
    	   xOdoValue = ulOdoInKm;
       }
#if(ODO_TEST_MACRO == 1)
       printf("Odo value=%ld\n", xOdoValue);
#endif
    }
    else
    {
    	*OdoUnits = ODO_IN_MILES;
    	if(ulOdoInMiles >= MAX_ODO_VALUE_IN_KM)
    	{
    		ulOdoInMiles = MAX_ODO_VALUE_IN_KM;
    	}
    	else
    	{
    		xOdoValue = ulOdoInMiles;
    	}
    }
 return xOdoValue;
}

/**
 * @brief Toggle Odo units
 *
 * This function is designed to configure vehicle odometer units, in between kilometers and miles
 *
 * @param[in] void
 *
 * @return void
 */

void vToggleOdoUnits(void)
{
    if(OdometerUnits == ODO_IN_KM)
    {
        OdometerUnits = ODO_IN_MILES;
    }
    else
    {
        OdometerUnits = ODO_IN_KM;
    }
#if(ODO_TEST_MACRO == 1)
    if(OdometerUnits == ODO_IN_KM)
    {
    	printf("Units: KM\n");
    }
    else
    {
    	printf("Units: MILE\n");
    }
#endif
}

#endif	/* ODOMETER_C */

