/** \addtogroup  
 *  @{
 * @file Odometer.c
 * @file Odometer.h
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
#include "../Odometer_App_test/Odometer_App_Test.h"
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
//uint32_t mts_to_km_dist_conv_factor = 1000;
uint32_t fl_pulse_multi_factor_u32 = 100;
uint32_t fl_pulsesPer100Meters_u32 = 1;
uint32_t gl_Km_to_Miles_dist_conv_factor_u32 =0.621*100;
vehicleDisplayMetrics_t defaultOdoUnits = 0;
vehicleDisplayMetrics_t OdometerUnits = 0;
vehicleDisplayMetrics_t TripA_Units=0;
vehicleDisplayMetrics_t TripB_Units=0;
bool ignitionStatus = 0;
uint32_t gl_receivedPulses_u32= 0;
/**km variables*/
uint32_t fl_distanceInMts_u32 = 0;
uint32_t fl_pulse100mCountRatioOdo_u32 = 0;
//uint32_t g_Pulsesreceived_u32 = 0;
uint32_t gl_distanceInKm_u32 = 0;
uint32_t fl_presentPulses_u32 =0;
uint32_t fl_previousPulses_u32=0;
int64_t fl_pulsesDelta_i32= 0;
uint32_t gl_Total_odo_u32=0;
uint16_t gl_TripA_u16=0;
uint16_t gl_TripB_u16=0;
//uint16_t l_TripB_u16=0;
uint16_t gl_OdoValBeforeTripA_Reset_u32 = 0;
uint16_t gl_OdoValBeforeTripB_Reset_u32 = 0;
uint32_t gl_OdoInEeprom_u32=0;
uint32_t fl_updatedOdoValue_u32=0;

/**Testing Purpose*/
vehicleDisplayMetrics_t DisplayTripA_Units = 0;
vehicleDisplayMetrics_t DisplayTripB_Units = 0;

/**miles variables*/
uint32_t  fl_distanceInMiles_u32 = 0;

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
	 uint8_t l_ignitionStatus_u8=0;
	 l_ignitionStatus_u8 = usIgnitionGetCurrentState();

	if(l_ignitionStatus_u8 == IgnOFF_mode)
    {
#if(OdoTestMacro == 1)
		printf("Odometer Ignition: OFF\n\r");
#endif
		gl_distanceInKm_u32 = 0;
    }
    else
    {        
        vCalculateOdo();
#if(OdoTestMacro == 1)
        printf("A: %d\t", ( xGetTripA_OdoReading(&DisplayTripA_Units) ) );
        printf("B: %d\t", ( xGetTripB_OdoReading(&DisplayTripB_Units)));
#endif
        vResetTripA_OdoReadings();
        vResetTripB_OdoReadings();
#if(OdoTestMacro == 1)
        printf("AR:%d\t",  gl_OdoValBeforeTripA_Reset_u32);
        printf("BR:%d\t",  gl_OdoValBeforeTripB_Reset_u32);
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
	fl_presentPulses_u32= xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	fl_pulsesDelta_i32 = fl_presentPulses_u32 - fl_previousPulses_u32;

	if(fl_pulsesDelta_i32 < 0 )
	{
		fl_pulsesDelta_i32 = UINT32_MAX + fl_pulsesDelta_i32 ;
	}

	fl_previousPulses_u32 = fl_presentPulses_u32;
	return fl_pulsesDelta_i32;
}
void vCalculateOdoInKm(void)
{
	gl_receivedPulses_u32 = vPulseCount();
	fl_pulse100mCountRatioOdo_u32 = ( gl_receivedPulses_u32 / fl_pulsesPer100Meters_u32 );
#if(OdoTestMacro == 1)
    printf("p:%ld\t",fl_pulse100mCountRatioOdo_u32 );
#endif
    fl_distanceInMts_u32 = fl_pulse100mCountRatioOdo_u32 * fl_pulse_multi_factor_u32;
    //gl_distanceInKm_u32 = (fl_distanceInMts_u32 / mts_to_km_dist_conv_factor);
    //gl_Total_odo_u32 = gl_Total_odo_u32 + gl_distanceInKm_u32;
    //printf("odo: %ld\n", gl_Total_odo_u32);
    fl_updatedOdoValue_u32 = gl_OdoInEeprom_u32 + fl_pulse100mCountRatioOdo_u32;// Update OdoInEeprom with the new value
     gl_OdoInEeprom_u32 = fl_updatedOdoValue_u32;
     gl_Total_odo_u32 = (gl_OdoInEeprom_u32/10);
#if(OdoTestMacro == 1)
     printf("odo: %ld\t", gl_Total_odo_u32);
     printf("EEodo:%ld\t", gl_OdoInEeprom_u32);
#endif
}
void vCalculateOdoInMiles(void)
{
    vCalculateOdoInKm();   
    fl_distanceInMiles_u32 =(gl_distanceInKm_u32 * gl_Km_to_Miles_dist_conv_factor_u32);
#if(OdoTestMacro == 1)
   // printf(" distanceInMiles:%ld\t\n\r: " ,fl_distanceInMiles_u32);
#endif
}
void vResetTripA_OdoReadings(void)
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
	gl_OdoValBeforeTripA_Reset_u32 =gl_OdoInEeprom_u32;
     //printf("AR:%d\t\n",  gl_OdoValBeforeTripA_Reset_u32);
}
uint16_t xGetTripA_OdoReading(vehicleDisplayMetrics_t *TripA_Units)
{
    // Calculate the total odometer reading after the reset
	gl_TripA_u16 = gl_OdoInEeprom_u32 -  gl_OdoValBeforeTripA_Reset_u32 ;
    if ( gl_TripA_u16 >= 1000)
    {
    	gl_OdoValBeforeTripA_Reset_u32  =gl_OdoInEeprom_u32;
    }
    else
    {
        // No need to reset Trip A value
        //printf("Trip A value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
    	gl_TripA_u16 =gl_OdoInEeprom_u32 -  gl_OdoValBeforeTripA_Reset_u32 ;
        *TripA_Units = ODO_IN_KM;
        //printf("Trip A: %u kilometers\n",  gl_TripA_u16);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-A reading in miles (1 km = 0.621371 miles)
    	gl_TripA_u16 =   gl_TripA_u16/10 * 0.621371*100;
        *TripA_Units=ODO_IN_MILES;
       // printf("Trip A: %u miles\n",  gl_TripA_u16);
    }
     
    //printf("A: %d\t\n", gl_TripA_u16);
    // Return the Trip-A reading
    return gl_TripA_u16; // You might need to change the return type if necessary
}
void vResetTripB_OdoReadings(void) 
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
	gl_OdoValBeforeTripB_Reset_u32 =gl_OdoInEeprom_u32;
     //printf("BR:%d\t\n ",  gl_OdoValBeforeTripB_Reset_u32);
}
void xWrite_OdoVal_to_EEPROM(void)
{
	//Write EEPROM API here
	//mprintf("gl_OdoInEeprom_u32: %ld\n", gl_OdoInEeprom_u32);
}

void xRetrive_LastStored_OdoVal_from_EEPROM(void)
{
	//Write EEPROM API here
	// gl_Total_odo_u32 = ActualAPI();
#if(OdoTestMacro == 1)
	//printf("Reading last stored Odo value from EEPROM\n");
#endif
}

uint16_t xGetTripB_OdoReading(vehicleDisplayMetrics_t *TripB_Units)
{
    //uint16_t gl_TripB_u16;

    // Calculate the total odometer reading after the reset
	gl_TripB_u16 =gl_OdoInEeprom_u32 -  gl_OdoValBeforeTripB_Reset_u32 ;
    if ( gl_TripB_u16 >= 999)
    {
        // Reset Trip A value
    	gl_OdoValBeforeTripB_Reset_u32  =gl_OdoInEeprom_u32;
         //gl_TripB_u16 = 0;
        //printf("Trip B value reset to 0\n");
     }
    else
    {
        // No need to reset Trip A value
        //printf("Trip B value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
    	gl_TripB_u16 =gl_OdoInEeprom_u32 -  gl_OdoValBeforeTripB_Reset_u32 ;
        *TripB_Units=ODO_IN_KM;
       // printf("Trip B: %u kilometers\n",  gl_TripA_u16);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-B reading in miles (1 km = 0.621371 miles)
    	gl_TripB_u16 =   gl_TripB_u16/10 * 0.621371*100;
        *TripB_Units=ODO_IN_MILES;
       // printf("Trip B: %u miles\n",  gl_TripA_u16);
    }
     
     //("B: %d\t\r\n", gl_TripB_u16);
    // Return the Trip-A reading
    return gl_TripB_u16;
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
        return gl_Total_odo_u32;
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
//    //printf("odo:%d\n",gl_Total_odo_u32);
//    //l_previousPulses_u32 = l_presentPulses_u32;
//}
#endif	/* ODOMETER_C */

