#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::notifyCounterChanged(uint16_t newCounter)
{
	//view.FuelbarWarningIcon(newCounter);
	view.UpdateCount(newCounter);
	view.KMPHtoMPH(newCounter);
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
