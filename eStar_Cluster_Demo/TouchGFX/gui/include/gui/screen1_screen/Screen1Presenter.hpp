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

    virtual void notifyCounterChanged(uint16_t newCounter);
    virtual void notifyOdoDataChanged(uint32_t newodoData);
    virtual void notifyFuelCounter(uint16_t newFuelCount);
    virtual void notifyRPMDataChanged(uint16_t newRPMData);
    virtual void notifyDriverInforMenuDataChanged( uint8_t newMenu);

    virtual ~Screen1Presenter() {}

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
