/*
 * DriverInfoApp.c
 *
 *  Created on: Apr 4, 2024
 *      Author: dhana
 */


#include <stdio.h>
#include "stdint.h"
#include "DriverInfoApp.h"
#include "DriverInfoApp_cfg.h"
#include "Odometer_App.h"
#include "IGN_SmHandler.h"
#include "FuelGuage_App.h"
#include "Indicator_App.h"

uint8_t Distance1 = 0;
uint8_t Distance2 = 0;
uint8_t InitialValue = 0;
uint8_t FinalValue = 0;
uint16_t FInalOdoinKm = 0;
uint16_t FOdo = 0;
uint8_t DeltaTime = 0;
uint16_t var1 = 0;
uint32_t g_InitOdoVal = 0;
uint8_t Fuel_ConsumedinPer = 0;
uint16_t var2 = 0;
uint16_t AverageFuelEconomy1 = 0;
uint16_t Time = 0;
vehicleDisplayMetrics_t units = 0;
uint16_t DTE = 0;
IndicationStatus_t warningindicator;
bool warningstatus = 0;

//driverInfoModeStatus_t status;


#if 1
uint8_t IntialFuelValue = 0;
uint8_t InitialDistance = 0;
uint8_t FinalFuelValue = 0;
uint32_t FinalDistance = 0;
uint8_t DeltaDistance = 0;
//uint8_t count = 0;
uint8_t FuelValinLitres = 0;
#endif

uint8_t displayed_fuellevel = 0;
uint16_t actual_DTE = 0;
uint16_t displayed_DTE = 0;
uint16_t Total_DTE = 0;
uint16_t MaxThresholdDTE = 0;
uint8_t Fuellevel = 0;
uint16_t DistancefromOdo = 0;
//bool flag = false;

typedef struct{
	uint16_t AverageVehicleSpeed;
	uint16_t AverageFuelEconomy;
	uint16_t DistanceToEmpty;
}driverInfoModeStatus_t;

//driverInfoModeStatus_t Infostatus;
driverInfoModeStatus_t ModeStatus;



void vCalculateAvsAfeRange(void)
{
    uint8_t ignitionstatus = 0;
    ignitionstatus = usIgnitionGetCurrentState();
    if(ignitionstatus == IgnOFF_mode)
    {
        printf("Ignition is OFF\r\n");
        Time = 0;
        Distance2 = 0;
    }
    else
    {
        vCalculateAVSInKmperhour();
        vCalculateAFEKmperLitre();
        vCalculateDTE();
    }

}

uint16_t TotalVehicleSpeed = 0;
uint16_t VehicleSpeed = 0;
uint16_t vCalculateAVSInKmperhour(void)
{

   ModeStatus.AverageVehicleSpeed = 0;
   static uint16_t Distance = 0;
   static uint16_t Distance1 = 0;
   static uint16_t Distance2 = 0;
   static uint16_t DeltaTime = 0;
   static uint8_t counter = 0;

   Distance2 = xGetOdoReadings(&units);
   printf("D2:%d\t",Distance2);
   Distance  = Distance2 - Distance1;
   printf("DD:%d\t",Distance);
   Distance1 = Distance2;
   //DeltaTime = 30;
   DeltaTime = 5;
   //printf("DT:%d\r\n",DeltaTime);
   VehicleSpeed = ( Distance * SecondsToHoursFactor ) / DeltaTime;
   printf("VS:%d\t",VehicleSpeed);
   TotalVehicleSpeed = TotalVehicleSpeed + VehicleSpeed;
   //printf("TVS:%d\r\n",TotalVehicleSpeed);

   counter++;
   if(counter == 5)
   {
	   ModeStatus.AverageVehicleSpeed = TotalVehicleSpeed / NoOfSpeedSamples;
	   var1 = ModeStatus.AverageVehicleSpeed;
	   //printf("AVS:%d\r\n",AverageVehicleSpeed);
	   counter = 0;
	   TotalVehicleSpeed = 0;
   }
   printf("var1:%d\n\r",var1);
   return var1;
}

//uint8_t OdoArray[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//uint8_t OdoArray[5] = {1, 3, 6, 7, 10};
//uint8_t xGetOdoReadings(void)
//{
//	static uint8_t Odo = 0;
//	uint8_t Final = 0;
//	Final = OdoArray[Odo];
//	if(Odo == 5)
//	{
//		Odo=0;
//	}
//	else
//	{
//		Odo++;
//	}
//	return Final;
//}
//
////uint8_t FuelArray[10] = {5,10,15,20,25,30,35,40,45,50};
//uint8_t FuelArray[5] = {10, 9, 7, 5, 3};
//uint8_t xGet_FuelLevel(void)
//{
//	static uint8_t Fuel = 0;
//	uint8_t FinalFuel = 0;
//	FinalFuel = FuelArray[Fuel];
//	if(Fuel == 5)
//	{
//		Fuel=0;
//	}
//	else
//	{
//		Fuel++;
//	}
//	return FinalFuel;
//}
uint16_t vCalculateAFEKmperLitre(void)
{

	static uint8_t count = 0;
	static uint8_t FuelValinLitres = 0;
	FinalFuelValue = xGet_FuelLevel(&warningindicator, &warningstatus);
	printf("FFV:%d\t",FinalFuelValue);
	FinalDistance = xGetOdoReadings(&units);
	printf("FD:%u\t",FinalDistance);
	DeltaDistance = FinalDistance - InitialDistance;
	printf("Distance-%d\t",DeltaDistance);
	//printf("DD:%d\n\r",DeltaDistance);
	if(IntialFuelValue >= FinalFuelValue)
	{
		Fuel_ConsumedinPer = IntialFuelValue - FinalFuelValue;
	}
	else
	{
		Fuel_ConsumedinPer = FinalFuelValue - IntialFuelValue;
	}
	//printf("FC:%d\n\r",Fuel_ConsumedinPer);
	if(count >= 1)
	{
		if(Fuel_ConsumedinPer <=100)
		{
			if((Fuel_ConsumedinPer >0))
			{
				FuelValinLitres = Convertintolitres(Fuel_ConsumedinPer);
				printf("FuelValinLitres-%d\t",FuelValinLitres);
				ModeStatus.AverageFuelEconomy = (uint16_t)((DeltaDistance *10) / (FuelValinLitres));
				var2 = ModeStatus.AverageFuelEconomy;
			}
		}
		else
		{
			printf("Invalid Fuelper\r\n");
		}

	}

	IntialFuelValue = FinalFuelValue;
	InitialDistance = FinalDistance;
	count++;
	//printf("AFE:%d\n\r",AverageFuelEconomy);
	//var2 =0;
	printf("var2:%d\n\r",var2);
	//var2 =0;
	return var2;
}

uint8_t Convertintolitres(uint8_t Fuel_ConsumedinPer)
{
    uint8_t FinalFuelVal = 0xFF;

    if (Fuel_ConsumedinPer == 0)
    {
        printf("Invalid Fuel_ConsumedPer\n\r");
        FinalFuelVal = 0;
    }
    else
    {
        // Perform integer arithmetic to avoid floating-point
        uint16_t fuelLiters = (Fuel_ConsumedinPer * 40 * 10) / 100;
        FinalFuelVal = (uint8_t)fuelLiters;
        //printf("FinalFuelVal=%d\n\r", FinalFuelVal);
    }

    return FinalFuelVal;
}


uint16_t vCalculateDTE(void)
{
    static uint8_t count1 = 0;
    static uint16_t MaxThresholdDTE = 0;
    printf("AFE1:%d\t", AverageFuelEconomy1);
    Fuellevel = xGet_FuelLevel(&warningindicator, &warningstatus);
    printf("FL:%d\t",Fuellevel);
    actual_DTE = (Fuellevel * 40  * DeltaDistance * 100 )/ (100 *  40);
    MaxThresholdDTE = fueltankcapacity * AverageFuelEconomy1;
    printf("ADTE:%d\t", actual_DTE);

    if(count1 == 1 )
    {

    	if(actual_DTE <= displayed_DTE)
    	{
    		Total_DTE = displayed_DTE - actual_DTE;
    		printf("a:%d,d:%d\t",actual_DTE,displayed_DTE);

    	}
    	else
    	{
    		Total_DTE = actual_DTE - displayed_DTE;
    		printf("a1:%d,d1:%d\t",actual_DTE,displayed_DTE);

    	}
    	displayed_DTE = actual_DTE;
    	//previous_DTE = actual_DTE;

		//Total_DTE = displayed_DTE - actual_DTE;
		printf("DDTE:%d\t", displayed_DTE);
		printf("TDTE:%d\t",Total_DTE);
		if(actual_DTE >= MaxThresholdDTE)
		{
			actual_DTE = MaxThresholdDTE;
			printf("displayed_DTE:%d\t",displayed_DTE);
		}
		//displayed_DTE = actual_DTE;

		if(Total_DTE < MIN_DISPLAYED_DTE)
		{
			displayed_DTE = displayed_DTE - 1;
			printf("displayed_DTE0:%d\t",displayed_DTE);
		}
		else if (Total_DTE > MAX_DISPLAYED_DTE)
		{
			displayed_DTE = actual_DTE;
			printf("displayed_DTE1:%d\t",displayed_DTE);
		}
		else if (Total_DTE >= MIN_DISPLAYED_DTE && Total_DTE <= MAX_DISPLAYED_DTE)
		{
			displayed_DTE = displayed_DTE - 2;
			printf("displayed_DTE2:%d\t",displayed_DTE);
		}
		else
		{

		}

    }
    else
    {
    	count1++;
    }
    ModeStatus.DistanceToEmpty = displayed_DTE;

    return displayed_DTE;
}

void DisplayDTE(bool flag,uint16_t displayed_DTE )
{
	if(flag)
	{
		printf("displayed_DTE: ---\n");
	}
	else
	{
		//printf("DTE: %.2f km" ,displayed_DTE);
		printf("DTE1: %u\n",displayed_DTE);
	}
}
//	return displayed_DTE
void xGetInfostatus(uint16_t *avgVehicleSpeed, uint16_t *avgFuelEconomy, uint16_t *displayedDTE)
{
	    // Assign values to the output parameters
	*avgVehicleSpeed = ModeStatus.AverageVehicleSpeed;
	*avgFuelEconomy = ModeStatus.AverageFuelEconomy;
	*displayedDTE = ModeStatus.DistanceToEmpty;
	if (*displayedDTE < BLINK_THRESHOLD_LOW || *displayedDTE > MaxThresholdDTE)
	{
		//flag = true;
		DisplayDTE(true,*displayedDTE);
	}
	else
	{
		DisplayDTE(false,*displayedDTE);
	}
}

//driverInfoModeStatus_t xGetInfostatus(void)
//{
//	    // Assign values to the output parameters
//	return ModeStatus;
//}
//driverInfoModeStatus_t status;


