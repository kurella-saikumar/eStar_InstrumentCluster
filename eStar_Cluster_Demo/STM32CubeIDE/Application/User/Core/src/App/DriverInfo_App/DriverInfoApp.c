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



//uint32_t ucDistance2 = 0;
uint8_t ucInitialValue = 0;
uint8_t ucFinalValue = 0;
uint16_t usFInalOdoinKm = 0;
uint16_t usFOdo = 0;

uint32_t usDistance = 0;
uint32_t ucDistance1 = 0;
uint32_t usDistance2 = 0;
uint8_t ucDeltaTime = 0;
uint32_t usTotalVehicleSpeed = 0;
uint32_t usVehicleSpeed = 0;
uint16_t CurrentAVS = 0;

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


/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/


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


//vehicleDisplayMetrics_t units = 0;
//bool warningstatus = 0;
IndicationStatus_t warningindicator;
driverInfoModeStatus_t ModeStatus;
//uint8_t fuelTankCapacity = 40;
uint16_t initialDistance = 0;
uint16_t finalDistance = 0;
//uint32_t deltaDistance = 0;
uint32_t DeltaDistance = 0;


//uint16_t defaultAFE = 0;
int8_t initialFuelPercentage = 0;
int8_t finalFuelPercentage = 0;
//uint8_t deltaFuelInPercentage = 0;
int8_t deltaFuelInPercentage = 0;
//int8_t previousdeltaFuelInPercentage = 0;
uint16_t deltaFuelInLitres = 0;
//uint32_t deltaFuelInLitres = 0;
uint16_t fuelInLitres = 0;
uint64_t In_AFE = 0 ;
uint64_t AFE = 0;
uint64_t previousAFE = 0;

uint8_t fuelRemainingInPercentage = 0;
uint16_t fuelRemainingInLitres = 0;
uint16_t FinalFuelLevel = 0;


uint16_t usCalculated_DTE = 0;
uint16_t uspresent_DTE = 0;
uint16_t usprevious_DTE = 0;
uint16_t usDelta_DTE = 0;

static uint16_t DeltaOdoValues1[WINDOW_SIZE];
static uint16_t DeltaFuelValues2[WINDOW_SIZE];
static uint16_t odoSamplecount = 0;
static uint16_t Fuelsamplecount = 0;
static uint32_t TotalSum1 = 0;
//static uint32_t TotalSum2 = 0;
static uint16_t TotalSum2 = 0;
//static uint16_t usSampleCount = 0;


//uint64_t AFE_D = 0;
//uint64_t AFE_C = 0;
//int DTE = 0;
uint16_t usactual_DTE = 0;
uint16_t usdisplayed_DTE = 0;
uint16_t usTotal_DTE = 0;



uint16_t calculatedDTE = 0;


#if 0
uint8_t xGetOdoReadings(void)
{
	uint8_t OdoArray[30] = {20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
	static uint8_t Odo = 0;
	uint8_t Final = 0;
		Final = OdoArray[Odo];
		Odo++;
	return Final;
}
#endif


void vDriver_InfoTask(void)
{
    uint16_t ucignitionstatus = 0;
    ucignitionstatus = usIgnitionGetCurrentState();
    if(ucignitionstatus == IgnOFF_mode)
    {
        printf("Ignition is OFF\r\n");
        //ucDeltaTime = 0;
        //usDistance2 = 0;
        finalDistance = 0;
        initialDistance = 0;
    }
    else
    {
    	vCalculateAVSInKmperhour();
    	vCalculateAFEKmperLitre();
    	vCalculateDTE();
    }

}

void vCalculateAVSInKmperhour(void)
{

   //ModeStatus.AverageVehicleSpeed;

   //static uint32_t usDistance1 = 0;
//   static uint16_t usDistance2 = 0;
//   static uint16_t usDeltaTime = 0;
   static uint8_t uccounter = 0;

   usDistance2 = xGetOdoReadings(&units);
   usDistance = usDistance2 - ucDistance1;
   ucDistance1 = usDistance2;
   ucDeltaTime = 5;
   usVehicleSpeed = ( usDistance * SECONDS_TO_HOURS_FACTOR ) / ucDeltaTime;
#if(DRIVERINFO_TEST_MACRO == 1)
#endif
   usTotalVehicleSpeed = usTotalVehicleSpeed + usVehicleSpeed;
   uccounter++;
   if(uccounter == 5)
   {
	   CurrentAVS = usTotalVehicleSpeed / NO_OF_SAMPLES;
	   printf("CurrentAVS:%d\t",CurrentAVS);
	  // usvar1 = ModeStatus.AverageVehicleSpeed;
#if (DRIVERINFO_TEST_MACRO == 1)
	   ModeStatus.AverageVehicleSpeed = CurrentAVS;
	   uccounter = 0;
	   usTotalVehicleSpeed = 0;
   }
}



uint8_t prvFuelSimulation(void)
{
	static uint8_t simulatedFuel = 100;
//	simulatedFuel = simulatedFuel-20;

	if(simulatedFuel <= 0)
		simulatedFuel = 100;

	simulatedFuel = simulatedFuel-20;
	return simulatedFuel;
}

uint16_t convert_FuelPercentageToLitres(uint8_t fuelPercentage)
{
	uint16_t fuelInLitres = 0;
	//uint8_t FinalFuelLevel = 0xFF;

    /*In the below expression 10 is multiplied intentionally in the numerator for calculating fuel in milliliters*/
    fuelInLitres = (FUEL_TANK_CAPACITY * fuelPercentage * 10) / 100;
    //FinalFuelLevel  = (uint8_t) fuelInLitres;
    FinalFuelLevel  =  fuelInLitres;

    return FinalFuelLevel;
}


void vCalculateAFEKmperLitre(void)
{
	static uint8_t uccount = 0;
	static uint32_t AverageDitsance = 0;
	static uint16_t AverageFuel = 0;
	//static uint32_t AverageFuel = 0;

	uccount++;
	finalDistance = xGetOdoReadings(&units);
	DeltaDistance = finalDistance - initialDistance;

	AverageDitsance = prvCalculateMovingAverage_Odo(DeltaDistance);

	printf("D_odo:%ld\t",DeltaDistance);
	printf("MA_Odo:%ld\t",AverageDitsance);
	finalFuelPercentage = prvFuelSimulation();

	if((DeltaDistance == 0) ||( DeltaDistance == finalDistance ))
	{
		initialDistance = finalDistance;
		initialFuelPercentage = finalFuelPercentage;
		AFE = DEFAULT_AFE;
		printf("AFE_D:%ld\n\r",AFE);
		return AFE;
	}

	deltaFuelInPercentage = initialFuelPercentage - finalFuelPercentage;

	if(deltaFuelInPercentage <= 0)
	{
		initialFuelPercentage = finalFuelPercentage;
		printf("I_Per:%d\t",initialFuelPercentage);
		//deltaFuelInPercentage = previousdeltaFuelInPercentage;
		return previousAFE;
	}

	deltaFuelInLitres = (uint16_t)(convert_FuelPercentageToLitres(deltaFuelInPercentage));
	AverageFuel = prvCalculateMovingAverage_Fuel(deltaFuelInLitres);
	printf("Fuel_MA:%u\t", AverageFuel);

	if (AverageFuel == 0)
	{
		// Handle the division by zero case
		AFE = DEFAULT_AFE;
	}
	else
	{
		In_AFE = (AverageDitsance * 10);
		AFE = (In_AFE /( (uint64_t)AverageFuel) );
		//AFE = (AverageDitsance * 10) /(uint32_t)(AverageFuel);
		printf("AFE_C:%d\n\r", AFE);
	}
    initialDistance = finalDistance;

    initialFuelPercentage = finalFuelPercentage;
    previousAFE = AFE;
    ModeStatus.AverageFuelEconomy = AFE;
   // return AFE;
}

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

#if 1
void vCalculateDTE(void)
{
	static uint8_t uccount1 = 0;
	uccount1++;
    fuelRemainingInPercentage = xGetFuelLevel(&warningindicator, &warningstatus);
    fuelRemainingInPercentage = finalFuelPercentage; /*Testing */
    fuelRemainingInLitres = convert_FuelPercentageToLitres(fuelRemainingInPercentage);


    //printf("Fuel: %d\n\r", fuelRemainingInLitres);
	if(uccount1 == 1)
	{
		printf("inside_If\r\n");
		fuelRemainingInLitres = FINAL_FUEL_LEVEL;
		//usCalculated_DTE = (int)(FINAL_FUEL_LEVEL * defaultAFE);
		usCalculated_DTE = (uint16_t)(FINAL_FUEL_LEVEL * DEFAULT_AFE);
		printf("C_DTE:%d\t",usCalculated_DTE);
		uspresent_DTE= usCalculated_DTE;
		printf("PIN_DTE:%d\t",uspresent_DTE);
	}
	else
	{
		printf("inside_else\r\n");
		usCalculated_DTE = fuelRemainingInLitres * AFE;
		uspresent_DTE = usCalculated_DTE;
		printf("POUT_DTE:%d\t",uspresent_DTE);
		/*Here, if DTE = 28 then it's actual value is 2.8*/
	}

	if(uspresent_DTE <= usprevious_DTE)
	{
		usDelta_DTE = usprevious_DTE - uspresent_DTE;
	}
	else
	{
		usDelta_DTE = uspresent_DTE - usprevious_DTE;
	}

		if(uspresent_DTE >= usMaxThresholdDTE)
		{
			uspresent_DTE = usMaxThresholdDTE;
			printf("P_DTE:%d\t",uspresent_DTE);
			printf("1\t");
		}
		if(usDelta_DTE < MIN_DISPLAYED_DTE)
		{
			uspresent_DTE = usprevious_DTE - 1;
		}
		else if (usDelta_DTE > MAX_DISPLAYED_DTE)
		{
			uspresent_DTE = usCalculated_DTE;
		}
		else if (usDelta_DTE >= MIN_DISPLAYED_DTE && usDelta_DTE <= MAX_DISPLAYED_DTE)
		{
			uspresent_DTE = usprevious_DTE - 2;
		}
		else
		{
		}

	usprevious_DTE = uspresent_DTE;
	//usdisplayed_DTE = usactual_DTE;
	printf("DTE:%d\r\n",uspresent_DTE);
	ModeStatus.DistanceToEmpty = uspresent_DTE;
   // return uspresent_DTE;
}

//void DisplayDTE(bool flag,uint16_t usdisplayed_DTE )
//{
//	if(flag)
//	{
//#if(DRIVERINFO_TEST_MACRO == 1)
//		printf("---\n");
//#endif
//	}
//	else
//	{
//#if(DRIVERINFO_TEST_MACRO == 1)
////		printf("DTE1: %u\n",usdisplayed_DTE);
//#endif
//	}
//}
//driverInfoModeStatus_t Modestate;

driverInfoModeStatus_t xGetInfostatus(void)
{
//	if (Modestate.DistanceToEmpty < BLINK_THRESHOLD_LOW || Modestate.DistanceToEmpty > usMaxThresholdDTE)
//	{
//		//flag = true;
//		//DisplayDTE(true,Modestate.DistanceToEmpty);
//		Modestate.DistanceToEmpty =1;
//	}
//	else
//	{
//		DisplayDTE(false,Modestate.DistanceToEmpty);
//	}
	printf("AVS:%d\n\r",ModeStatus.AverageVehicleSpeed);
	return ModeStatus;
}


#endif
uint32_t prvCalculateMovingAverage_Odo(uint32_t DeltaDistance)
{
	//printf("IF_D_MAVR:%ld\r\n",finalDelta);
	uint32_t Odo_Raw_value;
//	uint8_t Result = 0;
	uint32_t Odo_Result = 0;
	static uint8_t CurrentIndex = 0;
	Odo_Raw_value = DeltaDistance;
	//printf("ROdo_MAVR:%ld\r\n",Odo_Raw_value);
	DeltaOdoValues1[CurrentIndex] = Odo_Raw_value;
	CurrentIndex = (CurrentIndex + 1) % WINDOW_SIZE;
	TotalSum1 += Odo_Raw_value;
	//TotalSum = TotalSum1;
	odoSamplecount++;
	printf("oS: %d\t", odoSamplecount);
	if(odoSamplecount >= WINDOW_SIZE)
	{
		Odo_Result = prvCalculateAverage1();
		//printf("Result:%ld\t",Result);
		TotalSum1 -= DeltaOdoValues1[CurrentIndex];
	}
	return Odo_Result;
}
uint16_t prvCalculateMovingAverage_Fuel(uint16_t deltaFuelInLitres)
{
	//printf("IF_F_MAVR:%d\t",deltaFuelInLitres);
	uint16_t Fuel_Raw_value;
//	uint8_t Result = 0;
	uint16_t FuelResult = 0;
	static uint8_t CurrentIndex = 0;
	Fuel_Raw_value = deltaFuelInLitres;
	//Fuel_Raw_value = deltaFuelInPercentage;
	//printf("D_Fuel:%ld\t",Fuel_Raw_value);
	DeltaFuelValues2[CurrentIndex] = Fuel_Raw_value;
	CurrentIndex = (CurrentIndex + 1) % WINDOW_SIZE;
	TotalSum2 += Fuel_Raw_value;
	//TotalSum = TotalSum2;
	Fuelsamplecount++;
	if(Fuelsamplecount >= WINDOW_SIZE)
	{
		FuelResult = prvCalculateAverage2();
		//printf("Result:%ld\t",Result);
		TotalSum2 -= DeltaFuelValues2[CurrentIndex];
	}
	return FuelResult;
}



uint32_t prvCalculateAverage1(void)
{
//	printf("cOA\n");
	static uint32_t average;
	average = TotalSum1 / WINDOW_SIZE;
	//printf("MAVGd-%d\n",average);
	return average;
}
uint16_t prvCalculateAverage2(void)
{
	static uint16_t average;
	average = TotalSum2 / WINDOW_SIZE;
	//printf("MAVGd-%d\n",average);
	return average;
}




/**************************************************************************************************
 * End Of File
***************************************************************************************************/
