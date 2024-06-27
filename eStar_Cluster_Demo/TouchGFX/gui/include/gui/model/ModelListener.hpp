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

    virtual void notifyCounterChanged (uint16_t counter) {};
    virtual void notifyOdoDataChanged(uint32_t odometer){};
    virtual void notifyFuelCounter(uint16_t Fuelcount){};

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
