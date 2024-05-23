/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file DriverInfoApp.c

 *
 * @brief Template C file
 *
 * File Short Name:  DriverInfoApp.c
 *
 * @author: Sivadhanalakshmi T
 *
 * Created on: Apr 4, 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

#include "DriverInfoApp.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "DriverInfoApp_cfg.h"
#include "Odometer_App.h"
#include "IGN_SmHandler.h"
#include "FuelGuage_App.h"
#include "Indicator_App.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

uint32_t ucDistance1 = 0;
uint32_t ucDistance2 = 0;
uint8_t ucInitialValue = 0;
uint8_t ucFinalValue = 0;
uint16_t usFInalOdoinKm = 0;
uint16_t usFOdo = 0;
uint32_t usDistance2 = 0;
uint8_t ucDeltaTime = 0;
uint16_t usvar1 = 0;
uint32_t ulg_InitOdoVal = 0;
uint8_t ucFuel_ConsumedinPer = 0;
uint16_t usvar2 = 0;
uint16_t usAverageFuelEconomy1 = 0;
uint16_t usTime = 0;
vehicleDisplayMetrics_t units = 0;
uint16_t usDTE = 0;
IndicationStatus_t warningindicator;
bool warningstatus = 0;
uint32_t usTotalVehicleSpeed = 0;
uint32_t usVehicleSpeed = 0;
uint16_t CurrentAVS = 0;

//driverInfoModeStatus_t status;


#if 1
uint8_t ucIntialFuelValue = 0;
uint32_t ucInitialDistance = 0;
uint8_t ucFinalFuelValue = 0;
uint32_t ulFinalDistance = 0;
uint16_t ucDeltaDistance = 0;
//uint8_t count = 0;
uint8_t ucFuelValinLitres = 0;
#endif

uint8_t ucdisplayed_fuellevel = 0;
uint16_t usactual_DTE = 0;
uint16_t usdisplayed_DTE = 0;
uint16_t usTotal_DTE = 0;
//uint16_t usMaxThresholdDTE = 0;
uint8_t ucFuellevel = 0;
uint16_t usDistancefromOdo = 0;
//bool flag = false;

//typedef struct{
//	uint16_t AverageVehicleSpeed;
//	uint16_t AverageFuelEconomy;
//	uint16_t DistanceToEmpty;
//}driverInfoModeStatus_t;

//driverInfoModeStatus_t Infostatus;
driverInfoModeStatus_t ModeStatus;

/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/*Testing Purpose*/
#if 0
uint8_t prvFuelSimulation(void);
uint8_t simulatedFuel = 100;
#endif

/*This task function is responsible for periodically retrieving and processing driver information.*/

void vDriver_InfoTask(void)
{
    uint8_t ucignitionstatus = 0;
    ucignitionstatus = usIgnitionGetCurrentState();
    if(ucignitionstatus == IgnOFF_mode)
    {
        printf("Ignition is OFF\r\n");
        ucDeltaTime = 0;
        usDistance2 = 0;
    }
    else
    {
        vCalculateAVSInKmperhour();
        vCalculateAFEKmperLitre();
        vCalculateDTE();
    }

}
/**
 * @brief AverageVehicleSpeed Calculation
 *
 * This API is designed to calculates the Average Vehicle Speed (AVS) in kilometers per hour using odometer readings
   and a fixed time interval.
 * The calculated speed is averaged over a set number of samples and then displayed.
 * @param None
 *
 * @return Void.
 */


void vCalculateAVSInKmperhour(void)
{

   //ModeStatus.AverageVehicleSpeed;
   static uint32_t usDistance = 0;
   static uint32_t usDistance1 = 0;
//   static uint16_t usDistance2 = 0;
//   static uint16_t usDeltaTime = 0;
   static uint8_t uccounter = 0;

   usDistance2 = xGetOdoReadings(&units);
//   printf("D2:%ld\t",usDistance2);
   usDistance  = usDistance2 - usDistance1;
   usDistance1 = usDistance2;
   ucDeltaTime = 5;
   usVehicleSpeed = ( usDistance * SecondsToHoursFactor ) / ucDeltaTime;
#if(DRIVERINFO_TEST_MACRO == 1)
   //printf("DD:%d\t",usDistance);
   //printf("DT:%d\r\n",DeltaTime);
   //printf("VS:%d\t",usVehicleSpeed);
#endif
   usTotalVehicleSpeed = usTotalVehicleSpeed + usVehicleSpeed;
   uccounter++;
   if(uccounter == 5)
   {
	   CurrentAVS = usTotalVehicleSpeed / NoOfSpeedSamples;
	   //ModeStatus.AverageVehicleSpeed = CurrentAVS;
	   usvar1 = ModeStatus.AverageVehicleSpeed;
#if(DRIVERINFO_TEST_MACRO == 1)
//	   printf("AVS:%d\t",usvar1);
#endif
	   ModeStatus.AverageVehicleSpeed = CurrentAVS;
	   uccounter = 0;
	   usTotalVehicleSpeed = 0;
   }
}
/**
 * @brief AverageVehicleSpeed Calculation
 *
 * @brief Calculate and display the Average Fuel Economy (AFE) in kilometers per litre
 *
 * This function calculates the Average Fuel Economy (AFE) in kilometers per litre based on the fuel level
 * and odometer readings.
 * It simulates the fuel consumption for testing purposes and updates the AFE value for display after converting the consumed fuel into litres.
 *
 * @param None
 *
 * @return Void.
 */
void vCalculateAFEKmperLitre(void)
{

	static uint8_t uccount = 0;
	static uint8_t ucFuelValinLitres = 0;
	ucFinalFuelValue = xGetFuelLevel(&warningindicator, &warningstatus);
#if 0
	ucFinalFuelValue = prvFuelSimulation(); /*Testing purpose*/
#endif
	ulFinalDistance = xGetOdoReadings(&units);
	ucDeltaDistance = ulFinalDistance - ucInitialDistance;
	if(ucIntialFuelValue >= ucFinalFuelValue)
	{
		ucFuel_ConsumedinPer = ucIntialFuelValue - ucFinalFuelValue;
	}
	else
	{
		ucFuel_ConsumedinPer = ucFinalFuelValue - ucIntialFuelValue;
	}
	if(uccount >= 1)
	{
		uccount = 0;
		if(ucFuel_ConsumedinPer <=100)
		{
			if((ucFuel_ConsumedinPer >0))
			{
				ucFuelValinLitres = Convertintolitres(ucFuel_ConsumedinPer);
				//printf("FLLitres:%d\t",ucFuelValinLitres);

				//To provide the AFE value for display, they need to place the decimal point before the last digit.
				ModeStatus.AverageFuelEconomy = (uint16_t)((ucDeltaDistance *10) / (ucFuelValinLitres));
				usvar2 = ModeStatus.AverageFuelEconomy;
				printf("AFE_d:%d\t",usvar2);
			}
		}
		else
		{
			printf("Invalid Fuelper\r\n");
		}
	}
	ucIntialFuelValue = ucFinalFuelValue;
	ucInitialDistance = ulFinalDistance;
	uccount++;
}
/**
 * @brief Fuellevel conversion from percentage into Litres
 *
 * This API is designed to take the Fuellevel as input within periodic intervals, Convert the Fuellevel from Percentage into Litres, and update it with the latest values
 *
 *@return Void.
 */

uint8_t Convertintolitres(uint8_t ucFuel_ConsumedinPer)
{
    uint8_t ucFinalFuelVal = 0xFF;

    if (ucFuel_ConsumedinPer == 0)
    {
        printf("Invalid Fuel_ConsumedPer\n\r");
        ucFinalFuelVal = 0;
    }
    else
    {
        // Perform integer arithmetic to avoid floating-point
        uint16_t usfuelLiters = (ucFuel_ConsumedinPer * 40 * 10) / 100;
        ucFinalFuelVal = (uint8_t)usfuelLiters;
    }

    return ucFinalFuelVal;
}

uint16_t dte;
/**
 * @brief Calculate and display the Distance to Empty (DTE) value
 *
 * This function calculates the Distance to Empty (DTE) based on the current fuel level and average fuel economy.
 * It uses the odometer readings and a simulated fuel level for testing purposes to determine the actual and displayed DTE values.
 * The function ensures the displayed DTE is within acceptable thresholds and updates the ModeStatus with the calculated DTE value.
 *
 * @param None
 *
 * @return Void.
 */
void vCalculateDTE(void)
{
    static uint8_t uccount1 = 0;
    usAverageFuelEconomy1 = usvar2;
    ucFuellevel = xGetFuelLevel(&warningindicator, &warningstatus);
    //ucFuellevel = simulatedFuel; /*Testing Pupose*/
#if(DRIVERINFO_TEST_MACRO == 1)
//    printf("AFE_in:%d\t", usAverageFuelEconomy1);
//    printf("FL:%d\t",ucFuellevel);
#endif
    usactual_DTE = (ucFuellevel * 40  * ucDeltaDistance * 100 )/ (100 *  40);
	//usMaxThresholdDTE = fueltankcapacity * usAverageFuelEconomy1;
    if(uccount1 == 1 )
    {

    	if(usactual_DTE <= usdisplayed_DTE)
    	{
    		usTotal_DTE = usdisplayed_DTE - usactual_DTE;
#if(DRIVERINFO_TEST_MACRO == 1)
    		//printf("a:%d,d:%d\t",usactual_DTE,usdisplayed_DTE);
#endif

    	}
    	else
    	{
    		usTotal_DTE = usactual_DTE - usdisplayed_DTE;
#if(DRIVERINFO_TEST_MACRO == 1)
    		//printf("a1:%d,d1:%d\t",usactual_DTE,usdisplayed_DTE);
#endif

    	}
    	usdisplayed_DTE = usactual_DTE;
#if(DRIVERINFO_TEST_MACRO == 1)
//		printf("DDTE:%d\t", usdisplayed_DTE);
//		printf("TDTE:%d\t",usTotal_DTE);
#endif
		if(usactual_DTE >= usMaxThresholdDTE)
		{
			usactual_DTE = usMaxThresholdDTE;
#if(DRIVERINFO_TEST_MACRO == 1)
//			printf("displayed_DTE:%d\t",usdisplayed_DTE);
#endif
		}

		if(usTotal_DTE < MIN_DISPLAYED_DTE)
		{
			usdisplayed_DTE = usdisplayed_DTE - 1;
#if(DRIVERINFO_TEST_MACRO == 1)
//			printf("displayed_DTE0:%d\t",usdisplayed_DTE);
#endif
		}
		else if (usTotal_DTE > MAX_DISPLAYED_DTE)
		{
			usdisplayed_DTE = usactual_DTE;
#if(DRIVERINFO_TEST_MACRO == 1)
			//printf("displayed_DTE1:%d\t",usdisplayed_DTE);
#endif
		}
		else if (usTotal_DTE >= MIN_DISPLAYED_DTE && usTotal_DTE <= MAX_DISPLAYED_DTE)
		{
			usdisplayed_DTE = usdisplayed_DTE - 2;
			//printf("displayed_DTE2:%d\t",usdisplayed_DTE);
		}
		else
		{

		}

    }
    else
    {
    	uccount1++;
    }
    ModeStatus.DistanceToEmpty = usdisplayed_DTE;
#if(DRIVERINFO_TEST_MACRO == 1)
    dte = ModeStatus.DistanceToEmpty;
//    printf("DTE:%d\n\r",dte);
#endif
}
/**
 * @brief Speed calculation algorithm
 *
 * This function displays the Distance to Empty (DTE) value based on the provided flag.
 *@return Void.
 */

void DisplayDTE(bool flag,uint16_t usdisplayed_DTE )
{
	if(flag)
	{
#if(DRIVERINFO_TEST_MACRO == 1)
		printf("---\n");
#endif
	}
	else
	{
#if(DRIVERINFO_TEST_MACRO == 1)
//		printf("DTE1: %u\n",usdisplayed_DTE);
#endif
	}
}
/**
 * @brief Retrieve and display vehicle information status
 *
 * This function retrieves the average vehicle speed, average fuel economy, and displayed Distance to Empty (DTE) from the ModeStatus structure and assigns these values to the provided output parameters.
 * It also checks if  the displayed DTE is within an acceptable range and calls the DisplayDTE function to update the display accordingly.
 *
 // @param AVS AFE DTE values  It provides the vehicle's AVS AFE DTE information
 * @param[out] pusavgVehicleSpeed Pointer to a variable where the average vehicle speed will be stored.
 * @param[out] pusavgFuelEconomy Pointer to a variable where the average fuel economy will be stored.
 * @param[out] pusdisplayedDTE Pointer to a variable where the displayed DTE will be stored.
 *
 * @return Void.
 */

driverInfoModeStatus_t xGetInfostatus(void)
{
	if (ModeStatus.DistanceToEmpty < BLINK_THRESHOLD_LOW || ModeStatus.DistanceToEmpty > usMaxThresholdDTE)
	{
		//flag = true;
		DisplayDTE(true,ModeStatus.DistanceToEmpty);
	}
	else
	{
		DisplayDTE(false,ModeStatus.DistanceToEmpty);
	}
	return ModeStatus;
}
/*For testing purpose ,we can vary the fuellevel through this API*/
#if 0
uint8_t prvFuelSimulation(void)
{
	simulatedFuel--;

	if(simulatedFuel <= 0)
		simulatedFuel = 100;

	return simulatedFuel;
}
#endif


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
