#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void notifySpeedDataChanged(uint16_t newSpeed);
    virtual void notifyOdoDataChanged(uint32_t newodoData);
    virtual void notifyFuelCounter(uint16_t newFuelCount);
    virtual void notifyRPMDataChanged(uint16_t newRPMData);
    virtual void notifyTrip_ADataChanged(uint16_t newTripA);
    virtual void notifyTrip_BDataChanged(uint16_t newTripB);
    virtual void notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat);
    virtual void notifySwitchHandlerDataChanged(uint8_t SwitchStatus);
    virtual void notifyDriverInforMenuDataChanged( uint8_t newMenu);
    virtual ~Screen1Presenter() {}



private:
    Screen1Presenter();
    bool driverInfoMenuShown;
    uint8_t newMenu;
    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
