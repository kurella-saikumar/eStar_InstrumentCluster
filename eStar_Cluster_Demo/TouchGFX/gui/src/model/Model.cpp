#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App/speedometer_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App/Odometer_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage/FuelGuage_App.h"
#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App/Tachometer_App.h"


bool isButtonPressed = false;
static uint32_t ulOdoCounter = 0;

uint8_t odoUnits[4]; // Assuming the function returns an array of 4 uint8_t
uint8_t Fuel_Readings[4];


speedDisplayMetrics_t speedMetrics;
IndicationStatus_t speedStatus;

IndicationStatus_t FuelWarning;
IndicationStatus_t RPMWarning;

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
		TickCount =0;
	}
}
#endif




void Model::SpeedData()
{
	if(modelListener !=0)
	{
		modelListener->notifyCounterChanged(xGetSpeedValue(&speedMetrics, &speedStatus));
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
