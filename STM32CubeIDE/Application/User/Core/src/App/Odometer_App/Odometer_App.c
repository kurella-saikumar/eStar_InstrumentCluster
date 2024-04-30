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
uint32_t mts_to_km_dist_conv_factor = 1000;
uint32_t pulse_multi_factor = 100;
uint32_t pulsesPer100Meters = 1;
uint32_t Km_to_Miles_dist_conv_factor =0.621*100;
vehicleDisplayMetrics_t defaultOdoUnits = 0;
vehicleDisplayMetrics_t OdometerUnits = 0;
vehicleDisplayMetrics_t TripA_Units=0;
vehicleDisplayMetrics_t TripB_Units=0;
bool ignitionStatus = 0;
uint32_t g_receivedPulses_u32= 0;
/**km variables*/
uint32_t g_distanceInMts_u32 = 0;
uint32_t g_pulse100mCountRatio_u32 = 0;
uint32_t g_Pulsesreceived_u32 = 0;
uint32_t g_distanceInKm_u32 = 0;
uint32_t g_presentPulses_u32 =0;
uint32_t g_previousPulses_u32=0;
int64_t g_deltaPulses_u32= 0;
uint32_t g_Total_odo_u32=0;
uint16_t g_TripA_u16=0;
uint16_t g_TripB_u16=0;
//uint16_t l_TripB_u16=0;
uint16_t g_OdoValBeforeTripA_Reset_u32 = 0;
uint16_t g_OdoValBeforeTripB_Reset_u32 = 0;
uint32_t OdoInEeprom=0;
uint32_t updatedOdoValue=0;



/**miles variables*/
uint32_t  g_distanceInMiles_u32 = 0;

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

/**
 * @brief Speed calculation algorithm
 *
 * This API is designed to take count of generated pulses as input within periodic intervals, calculate the speed, and update it with the latest values
 *
 *@return Void.
 */ 
void vOdoAlgorithm(void)
{   
	 uint8_t ignitionStatus=0;
	 ignitionStatus = usIgnitionGetCurrentState();

	if(ignitionStatus == IgnOFF_mode)
    {
		printf("Odometer Ignition: OFF\n");
        g_distanceInKm_u32 = 0;
    }
    else
    {        
        vCalculateOdo();
    }
}

/**
 * @brief Distance calculation
 *
 * The API is designed to calculate the distance travelled by the vehicle, upon processing the no. of pulse count received as Input in between the periodic intervals
 *
 *@return Void.
 */
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
	g_presentPulses_u32= xGetRollingPulseCount(ODO_SPEEDO_CHANNEL);

	g_deltaPulses_u32 = g_presentPulses_u32 - g_previousPulses_u32;

	if(g_deltaPulses_u32 < 0 )
	{
		g_deltaPulses_u32 = UINT32_MAX + g_deltaPulses_u32 ;
	}

	g_previousPulses_u32 = g_presentPulses_u32;
	return g_deltaPulses_u32;
}

void vCalculateOdoInKm(void)
{
	g_receivedPulses_u32 = vPulseCount();
    g_pulse100mCountRatio_u32 = ( g_receivedPulses_u32 / pulsesPer100Meters );
    g_distanceInMts_u32 = g_pulse100mCountRatio_u32 * pulse_multi_factor;

    g_distanceInKm_u32 = (g_distanceInMts_u32 / mts_to_km_dist_conv_factor);
    g_Total_odo_u32 = g_Total_odo_u32 + g_distanceInKm_u32;
    printf("odo: %ld\n", g_Total_odo_u32);

    updatedOdoValue = OdoInEeprom + g_pulse100mCountRatio_u32;// Update OdoInEeprom with the new value
    OdoInEeprom = updatedOdoValue;
    xWrite_OdoVal_to_EEPROM();

}

void vCalculateOdoInMiles(void)
{
    vCalculateOdoInKm();   
    g_distanceInMiles_u32 =(g_distanceInKm_u32 * Km_to_Miles_dist_conv_factor);
    //printf(" distanceInMiles:%d\r\n: " ,g_distanceInMiles_u32);
     
}

void vResetTripA_OdoReadings(void)
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
     g_OdoValBeforeTripA_Reset_u32 = g_Total_odo_u32;
    //printf("AR:%d\t\n",  g_OdoValBeforeTripA_Reset_u32);

    // Assuming reset involves setting the odometer to zero
    // Reset the value of l_Total_odo_u32
}


uint16_t xGetTripA_OdoReading(vehicleDisplayMetrics_t *TripA_Units)
{
    uint16_t g_TripA_u16;

    // Calculate the total odometer reading after the reset
     g_TripA_u16 = g_Total_odo_u32 -  g_OdoValBeforeTripA_Reset_u32 ;
    if ( g_TripA_u16 >= 1000)
    {
        // Reset Trip A value
         g_OdoValBeforeTripA_Reset_u32  = g_Total_odo_u32;
    }
    else
    {
        // No need to reset Trip A value
        //printf("Trip A value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
        // Calculate Trip-A reading in kilometers
         //g_TripA_u16 =  g_TripA_u16 ;
        g_TripA_u16 = g_Total_odo_u32 -  g_OdoValBeforeTripA_Reset_u32 ;
        //printf("Trip A: %u kilometers\n",  g_TripA_u16);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-A reading in miles (1 km = 0.621371 miles)
        g_TripA_u16 =   g_TripA_u16/10 * 0.621371*100;
       // printf("Trip A: %u miles\n",  g_TripA_u16);
    }
     
     //printf("A: %d\t\n", g_TripA_u16);
    // Return the Trip-A reading
    return g_TripA_u16; // You might need to change the return type if necessary
}

void vResetTripB_OdoReadings(void) 
{
    // Store the current value of l_Total_odo_u32 into l_Total_odo_u32_Before_TripA_u32_Reset
     g_OdoValBeforeTripB_Reset_u32 = g_Total_odo_u32;
    //printf("BR:%d\t\n ",  g_OdoValBeforeTripB_Reset_u32);
}
void xWrite_OdoVal_to_EEPROM(void)
{
	//Write EEPROM API here
	printf("OdoInEeprom: %ld\n", OdoInEeprom);
}

void xRetrive_LastStored_OdoVal_from_EEPROM(void)
{
	//Write EEPROM API here
	// g_Total_odo_u32 = ActualAPI();
	printf("Reading last stored Odo value from EEPROM\n");
}

uint16_t xGetTripB_OdoReading(vehicleDisplayMetrics_t *TripB_Units)
{
    uint16_t g_TripB_u16;

    // Calculate the total odometer reading after the reset
     g_TripB_u16 = g_Total_odo_u32 -  g_OdoValBeforeTripB_Reset_u32 ;
    if ( g_TripB_u16 >= 999)
    {
        // Reset Trip A value
         g_OdoValBeforeTripB_Reset_u32  = g_Total_odo_u32;
         //g_TripB_u16 = 0;
        //printf("Trip B value reset to 0\n");
    }
    else
    {
        // No need to reset Trip A value
        //printf("Trip B value is within the limit\n");
    }
    if (OdometerUnits == ODO_IN_KM)
    {
        // Calculate Trip-B reading in kilometers
         //g_TripB_u16 =  g_TripB_u16 ;
        g_TripB_u16 = g_Total_odo_u32 -  g_OdoValBeforeTripB_Reset_u32 ;
        //printf("Trip B: %u kilometers\n",  g_TripA_u16);
    }
    else if (OdometerUnits == ODO_IN_MILES)
    {
        // Calculate Trip-B reading in miles (1 km = 0.621371 miles)
        g_TripB_u16 =   g_TripB_u16/10 * 0.621371*100;
       // printf("Trip B: %u miles\n",  g_TripA_u16);
    }
     
     //printf("B: %d\t\r\n", g_TripB_u16);
    // Return the Trip-A reading
    return g_TripB_u16; 
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
        return g_Total_odo_u32;
    }
    else
    {

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
//    //printf("odo:%d\n",g_Total_odo_u32);
//    //l_previousPulses_u32 = l_presentPulses_u32;
//}
#endif	/* ODOMETER_C */

