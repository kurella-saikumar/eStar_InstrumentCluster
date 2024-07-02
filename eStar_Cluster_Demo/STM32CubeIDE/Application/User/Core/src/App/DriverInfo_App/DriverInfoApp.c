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


uint32_t ulDistance = 0;
uint32_t ulDistance1 = 0;
uint32_t ulDistance2 = 0;
uint32_t ulTotalVehicleSpeed = 0;
uint32_t ulVehicleSpeed = 0;
uint32_t usCurrentAVS = 0;

vehicleDisplayMetrics_t units = 0;
IndicationStatus_t warningindicator;
bool warningstatus = 0;


//driverInfoModeStatus_t status;
//vehicleDisplayMetrics_t units = 0;
//bool warningstatus = 0;
bool warningStatus;
IndicationStatus_t warningIndicator;
driverInfoModeStatus_t ModeStatus;
uint16_t usinitialDistance = 0;
uint16_t usfinalDistance = 0;
uint32_t ulDeltaDistance = 0;


int8_t initialFuelPercentage = 0;
int8_t finalFuelPercentage = 0;
int16_t deltaFuelInPercentage = 0;
uint16_t usdeltaFuelInLitres = 0;
uint16_t fuelInLitres = 0;
//uint64_t In_AFE = 0 ;
//uint64_t AFE = 0;
uint32_t Afe = 0;
uint64_t previousAFE = 0;

uint8_t ucfuelRemainingInPercentage = 0;
uint16_t usfuelRemainingInLitres = 0;
uint16_t usFinalFuelLevel = 0;


uint16_t usCalculated_DTE = 0;
uint16_t uspresent_DTE = 0;
uint16_t usprevious_DTE = 0;
uint16_t usDelta_DTE = 0;

static uint16_t DeltaOdoValues1[WINDOW_SIZE];
static uint16_t DeltaFuelValues2[WINDOW_SIZE];
static uint16_t odoSamplecount = 0;
static uint16_t Fuelsamplecount = 0;
static uint32_t TotalSum1 = 0;
static uint16_t TotalSum2 = 0;



void vDriver_InfoTask(void)
{
    uint8_t ucignitionstatus = 0;
    ucignitionstatus = usIgnitionGetCurrentState();
    if(ucignitionstatus == IgnOFF_mode)
    {
        printf("Ignition is OFF\r\n");
        //ucDeltaTime = 0;
        //usDistance2 = 0;
        ulDistance2 = 0;
        ulDistance1 = 0;
    }
    else
    {
    	vCalculateAVSInKmperhour();
    	vCalculateAFEKmperLitre();
    	vCalculateDTE();
    	xGetAVSstatus();
    	xGetAFEstatus();
    	xGetDTEstatus();
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
   static uint8_t uccounter = 0;

   ulDistance2 = xGetOdoReadings(&units);
   ulDistance = ulDistance2 - ulDistance1;
   ulDistance1 = ulDistance2;
   ulVehicleSpeed = ( ulDistance * SECONDS_TO_HOURS_FACTOR ) / DELTA_TIME;
#if(DRIVERINFO_TEST_MACRO == 1)
#endif
   ulTotalVehicleSpeed = ulTotalVehicleSpeed + ulVehicleSpeed;
   uccounter++;
   if(uccounter == 5)
   {
	   usCurrentAVS = ulTotalVehicleSpeed / NO_OF_SAMPLES;
#if (DRIVERINFO_TEST_MACRO == 1)
	   printf("CurrentAVS:%ld\t",usCurrentAVS);
#endif
	   ModeStatus.AverageVehicleSpeed = usCurrentAVS;
	   uccounter = 0;
	   ulTotalVehicleSpeed = 0;
   }
}


/*This API is used for simulation (Testing Purpose)*/

#if(FUEL_TEST_MACRO == 0)
uint8_t prvFuelSimulation(void)
{
	static uint8_t ucsimulatedFuel = 100;
//	simulatedFuel = simulatedFuel-20;

	if(ucsimulatedFuel <= 0)
		ucsimulatedFuel = 100;

	ucsimulatedFuel = ucsimulatedFuel-20;
	return ucsimulatedFuel;
}
#endif

int16_t convert_FuelPercentageToLitres(int8_t fuelPercentage)
{
	int16_t usfuelInLitres = 0;
	//uint8_t FinalFuelLevel = 0xFF;

    /*In the below expression 10 is multiplied intentionally in the numerator for calculating fuel in milliliters*/
	usfuelInLitres = (FUEL_TANK_CAPACITY * fuelPercentage * 10) / 100;
    //FinalFuelLevel  = (uint8_t) fuelInLitres;
   // usFinalFuelLevel  =  fuelInLitres;

    return usfuelInLitres;
}


uint64_t vCalculateAFEKmperLitre(void)
{
	static uint8_t uccount = 0;
	static uint32_t ulAverageDitsance = 0;
	static uint16_t usAverageFuel = 0;
	//static uint32_t AverageFuel = 0;

	uccount++;
	usfinalDistance = xGetOdoReadings(&units);
	ulDeltaDistance = usfinalDistance - usinitialDistance;

	ulAverageDitsance = prvCalculateMovingAverage_Odo(ulDeltaDistance);

	printf("D_odo:%ld\t",ulDeltaDistance);
	printf("MA_Odo:%ld\t",ulAverageDitsance);
#if(FUEL_TEST_MACRO == 1)
	finalFuelPercentage = xGetFuelLevel(&warningIndicator,warningStatus);
#endif

#if(FUEL_TEST_MACRO == 0)
	finalFuelPercentage = prvFuelSimulation();
#endif

	if((ulDeltaDistance == 0) ||( ulDeltaDistance == usfinalDistance ))
	{
		usinitialDistance = usfinalDistance;
		initialFuelPercentage = finalFuelPercentage;
		Afe = DEFAULT_AFE;
		ModeStatus.AverageFuelEconomy = previousAFE;
		printf("AFE_D:%ld\n\r",Afe);
		return Afe;
	}

	deltaFuelInPercentage = initialFuelPercentage - finalFuelPercentage;

	if(deltaFuelInPercentage <= 0)
	{
		initialFuelPercentage = finalFuelPercentage;
		printf("I_Per:%d\t",initialFuelPercentage);
		ModeStatus.AverageFuelEconomy = previousAFE;
		return previousAFE;
	}

	usdeltaFuelInLitres = (uint16_t)(convert_FuelPercentageToLitres(deltaFuelInPercentage));
	usAverageFuel = prvCalculateMovingAverage_Fuel(usdeltaFuelInLitres);
	printf("Fuel_MA:%u\t", usAverageFuel);

	if (usAverageFuel == 0)
	{
		// Handle the division by zero case
		Afe = DEFAULT_AFE;
	}
	else
	{
//		In_AFE = (ulAverageDitsance * 10);
//		AFE = (In_AFE /((uint64_t)usAverageFuel));
		Afe = (ulAverageDitsance * 10) /(uint32_t)(usAverageFuel);
		printf("AFE_C:%ld\n\r", Afe);
	}
	usinitialDistance = usfinalDistance;

    initialFuelPercentage = finalFuelPercentage;
    previousAFE = Afe;
    ModeStatus.AverageFuelEconomy = Afe;
    return Afe;
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


void vCalculateDTE(void)
{
	static uint8_t uccount1 = 0;
	uccount1++;
#if(FUEL_TEST_MACRO == 1)
	ucfuelRemainingInPercentage = xGetFuelLevel(&warningIndicator, &warningStatus);
#endif

#if(FUEL_TEST_MACRO == 0)
	ucfuelRemainingInPercentage = prvFuelSimulation();
#endif

	//ucfuelRemainingInPercentage = finalFuelPercentage; /*Testing */
	usfuelRemainingInLitres = convert_FuelPercentageToLitres(ucfuelRemainingInPercentage);


    //printf("Fuel: %d\n\r", usfuelRemainingInLitres);
	if(uccount1 == 1)
	{
		printf("inside_If\r\n");
		usfuelRemainingInLitres = FINAL_FUEL_LEVEL;
		//usCalculated_DTE = (int)(FINAL_FUEL_LEVEL * defaultAFE);
		usCalculated_DTE = (uint16_t)(FINAL_FUEL_LEVEL * DEFAULT_AFE );
		printf("C_DTE:%d\t",usCalculated_DTE);
		uspresent_DTE= usCalculated_DTE;
		printf("PIN_DTE:%d\t",uspresent_DTE);
	}
	else
	{
		printf("inside_else\r\n");
		usCalculated_DTE = usfuelRemainingInLitres * Afe;
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
			ModeStatus.Range = uspresent_DTE;
			return uspresent_DTE;
		}
		else
		{
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
		}
	ModeStatus.Range = uspresent_DTE;
	usprevious_DTE = uspresent_DTE;
	printf("DTE:%d\r\n",uspresent_DTE);
	printf("DTE1:%d\n\r",ModeStatus.Range);
    return uspresent_DTE;
}
#if 1
uint16_t DisplayDTE(bool flag,uint16_t uspresent_DTE )
{
	static uint16_t Error_Value = 0;
	Error_Value = 9999;
	if(flag)
	{
#if(DRIVERINFO_TEST_MACRO == 1)
		//printf("---\n");
#endif
		printf("E_V:%hu\n\r",Error_Value);
		return Error_Value;


	}
	else
	{
#if(DRIVERINFO_TEST_MACRO == 1)
		//printf("DTE1: %u\n",usdisplayed_DTE);
#endif
		printf("E_V:%ld\n\r",uspresent_DTE);
		return uspresent_DTE;
	}
}


uint32_t xGetAVSstatus(void)
{
	uint32_t FinalAvs = (uint32_t)ModeStatus.AverageVehicleSpeed;
	printf("FAVS:%d\n\r",FinalAvs);
	return FinalAvs;
}


uint32_t xGetAFEstatus(void)
{
	uint32_t FinalAfe = (uint32_t)ModeStatus.AverageFuelEconomy;
	printf("FAFE:%d\n\r",FinalAfe);
	return FinalAfe;
}


uint16_t xGetDTEstatus(void)
{
	if((ModeStatus.Range < BLINK_THRESHOLD_LOW) || (ModeStatus.Range > usMaxThresholdDTE))
	{
		//flag = true;
		DisplayDTE(true,ModeStatus.Range);
		//ModeStatus.Range =1;
	}
	else
	{
		DisplayDTE(false,ModeStatus.Range);
	}

	//printf("DTE:%d\n\r",ModeStatus.Range);
	uint16_t FinalDte = (uint16_t)ModeStatus.Range;
	printf("FDTE:%d\n\r",FinalDte);

	return FinalDte;
}
#endif



uint32_t prvCalculateMovingAverage_Odo(uint32_t ulDeltaDistance)
{
	//printf("IF_D_MAVR:%ld\r\n",finalDelta);
	uint32_t ulOdo_Raw_value;
//	uint8_t Result = 0;
	uint32_t ulOdo_Result = 0;
	static uint8_t ucCurrentIndex = 0;
	ulOdo_Raw_value = ulDeltaDistance;
	//printf("ROdo_MAVR:%ld\r\n",ulOdo_Raw_value);
	DeltaOdoValues1[ucCurrentIndex] = ulOdo_Raw_value;
	ucCurrentIndex = (ucCurrentIndex + 1) % WINDOW_SIZE;
	TotalSum1 += ulOdo_Raw_value;
	odoSamplecount++;
	printf("oS: %d\t", odoSamplecount);
	if(odoSamplecount >= WINDOW_SIZE)
	{
		ulOdo_Result = prvCalculateAverage1();
		//printf("Result:%ld\t",Result);
		TotalSum1 -= DeltaOdoValues1[ucCurrentIndex];
	}
	return ulOdo_Result;
}
uint16_t prvCalculateMovingAverage_Fuel(uint16_t usdeltaFuelInLitres)
{
	//printf("IF_F_MAVR:%d\t",usdeltaFuelInLitres);
	uint16_t usFuel_Raw_value;
	uint16_t usFuelResult = 0;
	static uint8_t ucCurrentIndex = 0;
	usFuel_Raw_value = usdeltaFuelInLitres;
	//printf("D_Fuel:%ld\t",usFuel_Raw_value);
	DeltaFuelValues2[ucCurrentIndex] = usFuel_Raw_value;
	ucCurrentIndex = (ucCurrentIndex + 1) % WINDOW_SIZE;
	TotalSum2 += usFuel_Raw_value;
	Fuelsamplecount++;
	if(Fuelsamplecount >= WINDOW_SIZE)
	{
		usFuelResult = prvCalculateAverage2();
		//printf("Result:%ld\t",Result);
		TotalSum2 -= DeltaFuelValues2[ucCurrentIndex];
	}
	return usFuelResult;
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
