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
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/DriverInfo_App/DriverInfoApp.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Indicator_App/Indicator_App.h"

bool isButtonPressed = false;
//static uint32_t ulOdoCounter = 0;

//uint8_t odoUnits[4]; // Assuming the function returns an array of 4 uint8_t
uint8_t Fuel_Readings[4];

DriverInfoModeStatus_t DIM_Value;
IndicationStatus_t RPMWarning;
IndicationStatus_t   Status;
//ClockEditActions_t ClockEditingMode;

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

Model::Model() : modelListener(0),counter(0),TickCount(0),speedcounter(0)
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
		AVSValue();
		AFEValue();
		RANGEValue();
		Clock();
		//ClockEdit();
		SwitchHandler();
		//DriverInforMenu();
		IndicatorStatus();

		TickCount =0;
	}
}
#endif




void Model::SpeedData()
{
	speedDisplayMetrics_t SpeedMetrics;
	uint32_t SpeedValue = xGetSpeedValue(&SpeedMetrics);

	// Notify listener about SpeedData data change
	if(modelListener !=0)
	{
		modelListener->notifySpeedDataChanged(SpeedValue,SpeedMetrics);
	}
}


void Model::OdoData()
{
	uint8_t OdoUnits;
	uint32_t Odometer = xGetOdoReadings(&OdoUnits);

   // Notify listener about OdoData data change
   if (modelListener != 0)
   {
       modelListener->notifyOdoDataChanged(Odometer,OdoUnits);
   }
}


void Model::FuelData()
{
	//IndicationStatus_t FuelWarningIndication;
	uint8_t Fuelcount= xGetFuelLevel();
	// Notify listener about fuelData data change
	if(modelListener !=0)
	{
		modelListener->notifyFuelCounter(Fuelcount);
	}
}

void Model::RPMData()
{
	uint16_t RPMData = xGet_TachometerData();
	// Notify listener about RPMData data change
	if(modelListener !=0)
	{
		modelListener->notifyRPMDataChanged(RPMData);
	}
}

void Model::Trip_A()
{
	uint8_t TripA_Units;
	uint16_t TripA_Value = xGetTripA_OdoReading(&TripA_Units);

	// Notify listener about Trip_A data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_ADataChanged(TripA_Value,TripA_Units);
	}
}


void Model::Trip_B()
{
	uint8_t TripB_Units;
	uint16_t TripB_Value = xGetTripB_OdoReading(&TripB_Units);

	// Notify listener about Trip_B data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_BDataChanged(TripB_Value,TripB_Units);
	}
}


void Model::AVSValue()
{
	uint32_t AVS = xGetAVSstatus();
	// Notify listener about AVSValue data change
	if(modelListener !=0)
	{
		modelListener->notifyAVSDataChanged(AVS);
	}
}

void Model::AFEValue()
{
	uint32_t AFE = xGetAFEstatus();
	// Notify listener about AFEValue data change
	if(modelListener !=0)
	{
		modelListener->notifyAFEDataChanged(AFE);
	}
}


void Model::RANGEValue()
{
	uint16_t RANGE = xGetRANGEstatus();
	// Notify listener about RANGEValue data change
	if(modelListener !=0)
	{
		modelListener->notifyRANGEDataChanged(RANGE);
	}
}


void Model::Clock()
{
	vGet_Clock();
	Hours = xTime.Hours;
	Minutes = xTime.Minutes;
	TimeFormat = xTime.TimeFormat;

	// Notify listener about Clock data change
	if(modelListener !=0)
	{
		modelListener->notifyClockDataChanged(Hours,Minutes,TimeFormat);
	}
}

//void Model::ClockEdit()
//{
//	clockSettingRunMode(ClockEditingMode);
//
//	// Notify listener about Clock data change
//	if(modelListener !=0)
//	{
//		modelListener->notifyClockEditingDataChanged(ClockEditingMode);
//	}
//}

void Model::SwitchHandler()
{
	uint8_t SwitchStatus = xGetSwitchStatus();
	// Notify listener about SwitchHandler data change
	if(modelListener !=0)
	{
		modelListener->notifySwitchHandlerDataChanged(SwitchStatus);
	}

}

//void Model::DriverInforMenu()
//{
//
//	DIM_Value = xGetDriverInforMenu();
//
//	// Notify listener about DriverInforMenudata change
//	if(modelListener !=0)
//	{
//		modelListener->notifyDriverInforMenuDataChanged(DIM_Value);
//	}
//}

void Model::IndicatorStatus()
{
	Status= xGetIndicatorstatus();

	if(modelListener !=0)
		{
			modelListener->notifyIndicatorStatusDataChanged(Status);
		}
}












