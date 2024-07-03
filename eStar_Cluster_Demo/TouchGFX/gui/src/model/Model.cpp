#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "main.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/DriverInfoMenu_App/DriverInfoMenu_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App/speedometer_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App/Odometer_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage/FuelGuage_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App/Tachometer_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Clock_App/clock_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler/SwitchHandler_App.h"


bool isButtonPressed = false;
static uint32_t ulOdoCounter = 0;

uint8_t odoUnits[4]; // Assuming the function returns an array of 4 uint8_t
uint8_t Fuel_Readings[4];
uint8_t Trip_A_Units;
uint8_t Trip_B_Units;

speedDisplayMetrics_t speedMetrics;
IndicationStatus_t speedStatus;
DriverInfoModeStatus_t DIM_Value;

IndicationStatus_t FuelWarning;
IndicationStatus_t RPMWarning;

#if 1
//clock variables//
extern RTC_TimeTypeDef xTime;
uint8_t Hours;
uint8_t Minutes;
uint8_t TimeFormat;
#endif

bool RPMWarning_Status;
bool FuelWarning_Status;

// Function to simulate button press
void simulateButtonPress() {
    isButtonPressed = true;
}

// Function to simulate button release
void simulateButtonRelease() {
    isButtonPressed = false;
}

Model::Model() : modelListener(0),counter(0),TickCount(0),speedcounter(0),odometer(0)
{

}
#if 1

void Model::tick()
{
	TickCount++;

	if (TickCount > 100)
	{
		speedcounter++;
		if (speedcounter < 120)
		{
			simulateButtonPress(); // Simulate button press when speed counter is less than 100
		}
		else
		{
			simulateButtonRelease(); // Simulate button release when speed counter is 100 or more
		}

		SpeedData();
		OdoData();
		FuelData();
		RPMData();
		Trip_A();
		Trip_B();
		Clock();
		SwitchHandler();
		DriverInforMenu();

		TickCount =0;
	}
}
#endif




void Model::SpeedData()
{
	if(modelListener !=0)
	{
		modelListener->notifySpeedDataChanged(xGetSpeedValue(&speedMetrics, &speedStatus));
	}
}


void Model::OdoData()
{
	odometer = xGetOdoReadings(odoUnits);

   // Notify listener about Odometer data change
   if (modelListener != nullptr)
   {
       modelListener->notifyOdoDataChanged(odometer);
   }
}


void Model::FuelData()
{
	// Notify listener about fuelData data change
	if(modelListener !=0)
	{
		modelListener->notifyFuelCounter(xGetFuelLevel(&FuelWarning,&FuelWarning_Status));
	}
}

void Model::RPMData()
{
	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyRPMDataChanged(xGet_TachometerData(&RPMWarning,&RPMWarning_Status));
	}
}

void Model::Trip_A()
{

	Trip_A_Value = xGetTripA_OdoReading(&Trip_A_Units);

	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_ADataChanged(Trip_A_Value);
	}
}

void Model::Trip_B()
{

	Trip_B_Value = xGetTripB_OdoReading(&Trip_B_Units);

	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_BDataChanged(Trip_B_Value);
	}
}

#if 1
void Model::Clock()
{
	vGet_Clock();
	Hours = xTime.Hours;
	Minutes = xTime.Minutes;
	TimeFormat = xTime.TimeFormat;

	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyClockDataChanged(Hours,Minutes,TimeFormat);
	}
}

#endif

void Model::SwitchHandler()
{
	uint8_t SwitchStatus = xGetSwitchStatus();
	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifySwitchHandlerDataChanged(SwitchStatus);
	}

}

void Model::DriverInforMenu()
{

	DIM_Value = xGetDriverInforMenu();

	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyDriverInforMenuDataChanged(DIM_Value);
	}
}
