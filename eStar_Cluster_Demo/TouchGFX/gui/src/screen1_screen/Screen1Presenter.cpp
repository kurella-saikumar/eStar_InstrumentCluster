#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v),driverInfoMenuShown(false)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::notifySpeedDataChanged(uint32_t newSpeedValue)
{
	view.SpeedUpdate(newSpeedValue);
	//view.KMPHtoMPH(newSpeed);
}

void Screen1Presenter::notifyOdoDataChanged(uint32_t newOdoData)
{
	view.OdoDataUpdate(newOdoData);
}

void Screen1Presenter::notifyFuelCounter(uint16_t newFuelCount)
{
	view.FuelGauageAnimation(newFuelCount);
}

void Screen1Presenter::notifyRPMDataChanged(uint16_t newRPMData)
{
	view.RPMDataAnimation(newRPMData);
}

void Screen1Presenter::notifyTrip_ADataChanged(uint16_t newTripA_Value)
{
	view.TRIP_A(newTripA_Value);
}

void Screen1Presenter::notifyTrip_BDataChanged(uint16_t newTripB_Value)
{
	view.TRIP_B(newTripB_Value);
}

void Screen1Presenter::notifyAVSDataChanged(uint32_t newAVS)
{
	view.AVSValue(newAVS);
}

void Screen1Presenter::notifyAFEDataChanged(uint32_t newAFE)
{
	view.AFEValue(newAFE);
}

void Screen1Presenter::notifyRANGEDataChanged(uint16_t newRANGE)
{
	view.RANGEValue(newRANGE);
}

void Screen1Presenter::notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t Seconds, uint8_t TimeFormat,uint8_t l_12_24_Hrs_Flag)
{
	view.ClockUpdate(Hours,Minutes,Seconds,TimeFormat,l_12_24_Hrs_Flag);
}

//void Screen1Presenter::notifyClockEditingDataChanged(uint8_t ClockEditingMode)
//{
//	view.ClockValueChangingMode(ClockEditingMode);
//}

//void Screen1Presenter::notifyDriverInforMenuDataChanged( uint8_t newMenu)
//{
//	view.DriverInforMenu(newMenu);
//}


void Screen1Presenter::notifySwitchHandlerDataChanged(uint8_t SwitchStatus)
{
	view.SwitchingModes(SwitchStatus);

//	// Assuming newMenu is a member variable of Screen1Presenter to track the current menu state
//	if (newMenu == 2)
//	{  // Assuming 2 corresponds to the mode where DriverInforMenu should be shown
//	        if (!driverInfoMenuShown)
//	        {  // driverInfoMenuShown is a boolean member variable
//	            view.DriverInforMenu(newMenu);
//	            driverInfoMenuShown = true;  // Set the flag to true after showing the menu once
//	        }
//	    }
}

void Screen1Presenter:: notifyIndicatorStatusDataChanged(IndicationStatus_t newIndicators)
{
	view. IndicatorsStatus(newIndicators);
}

void Screen1Presenter:: notifyMetricsToggleDataChanged(uint8_t newMetrics)
{
	view.  MetricsToggle(newMetrics);
}


