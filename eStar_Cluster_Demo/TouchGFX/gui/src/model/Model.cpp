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


IndicationStatus_t   Status;


#if 1
//clock variables//
extern RTC_TimeTypeDef xTime;
uint8_t Hours;
uint8_t Minutes;
uint8_t Seconds;
uint8_t TimeFormat;
#endif



Model::Model() : modelListener(0),TickCount(0)
{

}

void Model::tick()
{
	TickCount++;

	if (TickCount >50)
	{
		MetricsToggle();
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
		SwitchHandler();
		IndicatorStatus();

		TickCount =0;
	}
}


void Model::SpeedData()
{
	uint32_t SpeedValue = xGetSpeedValue();

	// Notify listener about SpeedData data change
	if(modelListener !=0)
	{
		modelListener->notifySpeedDataChanged(SpeedValue);
	}
}


void Model::OdoData()
{
	uint32_t Odometer = xGetOdoReadings();

   // Notify listener about OdoData data change
   if (modelListener != 0)
   {
       modelListener->notifyOdoDataChanged(Odometer);
   }
}


void Model::FuelData()
{
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
	uint16_t TripA_Value = xGetTripA_OdoReading();

	// Notify listener about Trip_A data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_ADataChanged(TripA_Value);
	}
}


void Model::Trip_B()
{
	uint16_t TripB_Value = xGetTripB_OdoReading();

	// Notify listener about Trip_B data change
	if(modelListener !=0)
	{
		modelListener->notifyTrip_BDataChanged(TripB_Value);
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
	Seconds = xTime.Seconds;
	TimeFormat = xTime.TimeFormat;

	// Notify listener about Clock data change
	if(modelListener !=0)
	{
		modelListener->notifyClockDataChanged(Hours,Minutes,Seconds,TimeFormat);
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

void Model::IndicatorStatus()
{
	Status= xGetIndicatorstatus();

	if(modelListener !=0)
	{
		modelListener->notifyIndicatorStatusDataChanged(Status);
	}
}

void Model::MetricsToggle()
{
	uint8_t Metrics= xGetToggleMetrics();

	if(modelListener !=0)
	{
		modelListener->notifyMetricsToggleDataChanged(Metrics);
	}
}









