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
	view.FuelbarWarningIcon(newCounter);
	view.UpdateCount(newCounter);
	view.KMPHtoMPH(newCounter);
	view.FuelGauageAnimation(newCounter);
}
#if 0
void Screen1Presenter::notifyFuelCounter(int newFuelCount)
{
	view.FuelGauageAnimation(newFuelCount);
}
#endif
