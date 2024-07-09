#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>

#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Indicator_App/Indicator_App.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();
    void SpeedData();
    void OdoData();
    void FuelData();
    void RPMData();
    void Trip_A();
    void Trip_B();
    void Clock();
    void SwitchHandler();
    void DriverInforMenu();
    void AVSValue();
    void AFEValue();
    void RANGEValue();
    void IndicatorStatus();

protected:
    ModelListener* modelListener;
    uint16_t counter;
    uint16_t FuelPercentage;
    uint16_t TickCount;
};

#endif // MODEL_HPP
