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

void Screen1Presenter::notifySpeedDataChanged(uint16_t newSpeed)
{
	//view.FuelbarWarningIcon(newCounter);
	view.SpeedUpdate(newSpeed);
	view.KMPHtoMPH(newSpeed);
	//view.FuelGauageAnimation(newCounter);

}

void Screen1Presenter::notifyOdoDataChanged(uint32_t newodoData)
{
	view.OdoDataUpdate(newodoData);
}

void Screen1Presenter::notifyFuelCounter(uint16_t newFuelCount)
{
	view.FuelGauageAnimation(newFuelCount);
}

void Screen1Presenter::notifyRPMDataChanged(uint16_t newRPMData)
{
	view.RPMDataAnimation(newRPMData);
}

void Screen1Presenter::notifyTrip_ADataChanged(uint16_t newTripA)
{
	view.TRIP_A(newTripA);
}

void Screen1Presenter::notifyTrip_BDataChanged(uint16_t newTripB)
{
	view.TRIP_B(newTripB);
}

void Screen1Presenter::notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat)
{
	view.ClockUpdate(Hours,Minutes,TimeFormat);
}

void Screen1Presenter::notifyDriverInforMenuDataChanged( uint8_t newMenu)
{
	view.DriverInforMenu(newMenu);
}


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




