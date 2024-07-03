#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void notifySpeedDataChanged (uint16_t Speed){};
    virtual void notifyOdoDataChanged(uint32_t odometer){};
    virtual void notifyFuelCounter(uint16_t Fuelcount){};
    virtual void notifyRPMDataChanged(uint16_t RPMData){};
    virtual void notifyTrip_ADataChanged(uint16_t TripA){};
    virtual void notifyTrip_BDataChanged(uint16_t TripB){};
    virtual void notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat){};
    virtual void notifySwitchHandlerDataChanged(uint8_t SwitchStatus){};
    virtual void notifyDriverInforMenuDataChanged(uint8_t newMenu){};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
