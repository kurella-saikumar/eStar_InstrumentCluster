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

    virtual void notifySpeedDataChanged(uint32_t SpeedValue){};
    virtual void notifyOdoDataChanged(uint32_t Odometer){};
    virtual void notifyFuelCounter(uint16_t Fuelcount){};
    virtual void notifyRPMDataChanged(uint16_t RPMData){};
    virtual void notifyTrip_ADataChanged(uint16_t TripA_Value){};
    virtual void notifyTrip_BDataChanged(uint16_t TripB_Value){};
    virtual void notifyAVSDataChanged(uint32_t AVS){};
    virtual void notifyAFEDataChanged(uint32_t AFE){};
    virtual void notifyRANGEDataChanged(uint16_t RANGE){};
    virtual void notifyClockDataChanged(uint8_t Hours,uint8_t Minutes,uint8_t Seconds, uint8_t TimeFormat,uint8_t l_12_24_Hrs_Flag){};
    //virtual void notifyClockEditingDataChanged(uint8_t ClockEditingMode){};
    virtual void notifySwitchHandlerDataChanged(uint8_t SwitchStatus){};
   // virtual void notifyDriverInforMenuDataChanged(uint8_t newMenu){};
    virtual void notifyIndicatorStatusDataChanged(IndicationStatus_t Status){};
    virtual void notifyMetricsToggleDataChanged(uint8_t Metrics){};




protected:
    Model* model;
   // virtual void notifyClockEditingDataChanged(uint8_t ClockEditingMode){};
};

#endif // MODELLISTENER_HPP
