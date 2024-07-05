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

    virtual void notifySpeedDataChanged(uint32_t SpeedValue,uint8_t SpeedMetrics,uint8_t SpeedStatus){};
    virtual void notifyOdoDataChanged(uint32_t Odometer,uint8_t OdoUnits){};
    virtual void notifyFuelCounter(uint16_t Fuelcount){};
    virtual void notifyRPMDataChanged(uint16_t RPMData){};
    virtual void notifyTrip_ADataChanged(uint16_t TripA){};
    virtual void notifyTrip_BDataChanged(uint16_t TripB){};
    virtual void notifyAVSDataChanged(uint32_t AVS){};
    virtual void notifyAFEDataChanged(uint32_t AFE){};
    virtual void notifyRANGEDataChanged(uint16_t RANGE){};
    virtual void notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat){};
    virtual void notifySwitchHandlerDataChanged(uint8_t SwitchStatus){};
    virtual void notifyDriverInforMenuDataChanged(uint8_t newMenu){};
    virtual void notifyIndicatorStatusDataChanged(IndicationStatus_t Status){};


protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
