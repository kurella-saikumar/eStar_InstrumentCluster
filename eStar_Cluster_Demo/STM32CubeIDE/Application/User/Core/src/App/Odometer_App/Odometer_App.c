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
#include "Odometer_App.h"
#include "eeprom_emul.h"
#include "eeprom_emul_cfg.h"
//#include "Odometer_App_cfg.h"


/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
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

/**km variables*/

/**Testing Purpose*/


/**miles variables*/
uint32_t ulMtsToKmDistConvFactor = 1000;
uint32_t ulPulseMultiFactor = 100;
uint32_t ulPulsesPer100Meters = 1;
uint32_t ulKmToMilesDistConvFactor = 0.621 * 100;
vehicleDisplayMetrics_t defaultOdoUnits = 0;
vehicleDisplayMetrics_t OdometerUnits = 0;
vehicleDisplayMetrics_t TripA_Units=0;
vehicleDisplayMetrics_t TripB_Units=0;
bool ignitionStatus = 0;
uint32_t ulPulsesReceived = 0;
/**km variables*/
uint32_t ulDistanceInMtsOdo = 0;
uint32_t ulPulse100mCountRatioOdo = 0;
//uint32_t ulPulsesReceived = 0;
uint32_t ulDistanceInKmOdo = 0;
uint32_t ulPresentPulses = 0;
uint32_t ulPreviousPulses = 0;
int64_t sllPulsesDelta = 0;
uint32_t ulTotalOdo = 0;
uint16_t usTripA = 0;
uint16_t usTripB = 0;
uint16_t usOdoValBeforeTripAReset = 0;
uint16_t usOdoValBeforeTripBReset = 0;
uint32_t ulOdoInEeprom = 0;
uint32_t ulUpdatedOdoValue = 0;

/**Testing Purpose*/
vehicleDisplayMetrics_t DisplayTripA_Units = 0;
vehicleDisplayMetrics_t DisplayTripB_Units = 0;

/**miles variables*/
uint32_t ulDistanceInMiles = 0;


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
		printf("Odometer Ignition: ON\n\r");
#endif
		ulDistanceInKmOdo = 0;
    }
    else
    {        
        vCalculateOdo();
#if(ODO_TEST_MACRO == 1)
        printf("A: %d\t", ( xGetTripA_OdoReading(&DisplayTripA_Units) ) );
        printf("B: %d\t", ( xGetTripB_OdoReading(&DisplayTripB_Units)));
#endif
        vResetTripA_OdoReadings();
        vResetTripB_OdoReadings();
#if(ODO_TEST_MACRO == 1)
        printf("AR:%d\t",  usOdoValBeforeTripAReset);
        printf("BR:%d\t",  usOdoValBeforeTripBReset);
#endif
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
	ulPulse100mCountRatioOdo = ( ulPulsesReceived / ulPulsesPer100Meters );
#if(ODO_TEST_MACRO == 1)
    printf("p:%ld\t",ulPulse100mCountRatioOdo );
#endif
    ulDistanceInMtsOdo = ulPulse100mCountRatioOdo * ulPulseMultiFactor;
    //ulDistanceInKmOdo = (ulDistanceInMtsOdo / ulMtsToKmDistConvFactor);
    //ulTotalOdo = ulTotalOdo + ulDistanceInKmOdo;
    //printf("odo: %ld\n", ulTotalOdo);
    ulUpdatedOdoValue = ulOdoInEeprom + ulPulse100mCountRatioOdo;// Update OdoInEeprom with the new value
    ulOdoInEeprom = ulUpdatedOdoValue;
     ulTotalOdo = (ulOdoInEeprom/10);
#if(ODO_TEST_MACRO == 1)
     printf("odo: %ld\t", ulTotalOdo);
     printf("EEodo:%ld\t", ulOdoInEeprom);
#endif
}
void vCalculateOdoInMiles(void)
{
    vCalculateOdoInKm();   
    ulDistanceInMiles =(ulDistanceInKmOdo * ulKmToMilesDistConvFactor);
#if(ODO_TEST_MACRO == 1)
   // printf(" distanceInMiles:%ld\t\n\r: " ,ulDistanceInMiles);
#endif
}
void vResetTripA_OdoReadings(void)
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
	usOdoValBeforeTripAReset =ulOdoInEeprom;
     //printf("AR:%d\t\n",  usOdoValBeforeTripAReset);
}
uint16_t xGetTripA_OdoReading(vehicleDisplayMetrics_t *TripA_Units)
{
    // Calculate the total odometer reading after the reset
	usTripA = ulOdoInEeprom -  usOdoValBeforeTripAReset ;
    if ( usTripA >= 1000)
    {
    	usOdoValBeforeTripAReset  =ulOdoInEeprom;
    }
    else
    {
        // No need to reset Trip A value
        //printf("Trip A value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
    	usTripA =ulOdoInEeprom -  usOdoValBeforeTripAReset ;
        *TripA_Units = ODO_IN_KM;
        //printf("Trip A: %u kilometers\n",  usTripA);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-A reading in miles (1 km = 0.621371 miles)
    	usTripA =   usTripA/10 * 0.621371*100;
        *TripA_Units=ODO_IN_MILES;
       // printf("Trip A: %u miles\n",  usTripA);
    }
     
    //printf("A: %d\t\n", usTripA);
    // Return the Trip-A reading
    return usTripA; // You might need to change the return type if necessary
}
void vResetTripB_OdoReadings(void) 
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
	usOdoValBeforeTripBReset =ulOdoInEeprom;
     //printf("BR:%d\t\n ",  usOdoValBeforeTripBReset);
}
void xWrite_OdoVal_to_EEPROM(void)
{
	//Write EEPROM API here
	//mprintf("ulOdoInEeprom: %ld\n", ulOdoInEeprom);
	*eepromVariables[0] = ulOdoInEeprom;

//	*eepromVariables[0] = xGetOdoReadings(&xEE_OdoUnits);
	uint16_t FlashStatus= xES_WriteVariable((uint32_t)eepromVariables[0],*eepromVariables[0],eepromVariables[0]);
	if (0 == FlashStatus)
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("ESWrite Success:at 0x%lx, eepromVariables[0]:0x%lx \n\r",eepromVariables[0],*eepromVariables[0]);
//		printf("eepromVariables[0]: 0x%lx \n\r",*eepromVariables[0]);
#endif
	}
	else
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("ESWrite Fail:eepromVariables\n\r");
#endif
	}
#if 0
	uint16_t FlashStatus2 = xEE_ReadVariable32bits((uint32_t)eepromVariables[0], eepromVariables[0]);
	if (0 != FlashStatus2)
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("Read Fail:eepromVariables:%d\n\r",FlashStatus2);
		printf("eepromVariables[0] at :0x%lx data :0x%lx\n\r",eepromVariables[0],*eepromVariables[0]);
#endif
	}
	else
	{
#if(EMUL_DEBUG_ENABLE == 0)
		printf("Read Success:eepromVariables[0] at :0x%lx data :0x%lx\n\r",eepromVariables[0],*eepromVariables[0]);
#endif
	}
#endif
}

void xRetrive_LastStored_OdoVal_from_EEPROM(void)
{
	//Write EEPROM API here
	// ulTotalOdo = ActualAPI();

	ulOdoInEeprom = *eepromVariables[0];
	printf("ulOdoInEeprom:0x%lx,eepromVariables[0]:0x%lx\n\r",ulOdoInEeprom,*eepromVariables[0]);
	ulTotalOdo = (ulOdoInEeprom/10);

#if(ODO_TEST_MACRO == 1)
	//printf("Reading last stored Odo value from EEPROM\n");
#endif
}

uint16_t xGetTripB_OdoReading(vehicleDisplayMetrics_t *TripB_Units)
{
    //uint16_t usTripB;

    // Calculate the total odometer reading after the reset
	usTripB =ulOdoInEeprom -  usOdoValBeforeTripBReset ;
    if ( usTripB >= 999)
    {
        // Reset Trip A value
    	usOdoValBeforeTripBReset  =ulOdoInEeprom;
         //usTripB = 0;
        //printf("Trip B value reset to 0\n");
     }
    else
    {
        // No need to reset Trip A value
        //printf("Trip B value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
    	usTripB =ulOdoInEeprom -  usOdoValBeforeTripBReset ;
        *TripB_Units=ODO_IN_KM;
       // printf("Trip B: %u kilometers\n",  usTripA);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-B reading in miles (1 km = 0.621371 miles)
    	usTripB =   usTripB/10 * 0.621371*100;
        *TripB_Units=ODO_IN_MILES;
       // printf("Trip B: %u miles\n",  usTripA);
    }
     
     //("B: %d\t\r\n", usTripB);
    // Return the Trip-A reading
    return usTripB;
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

uint32_t xGetOdoReadings(vehicleDisplayMetrics_t* OdoUnits)
{
    if(OdometerUnits == ODO_IN_KM)
    {
       *OdoUnits = OdometerUnits;
        return ulTotalOdo;
    }
 return 0;

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
}

//uint32_t xGetOdoReadings(vehicleDisplayMetrics_t*OdoUnits)
//{
//    vCalculateOdoInKm();
//    //printf("odo:%d\n",ulTotalOdo);
//    //l_previousPulses_u32 = l_presentPulses_u32;
//}
#endif	/* ODOMETER_C */

