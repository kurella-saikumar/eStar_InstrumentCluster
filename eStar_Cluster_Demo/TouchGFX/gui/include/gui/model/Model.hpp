#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>

class ModelListener;

void simulateButtonPress();
void simulateButtonRelease();

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

protected:
    ModelListener* modelListener;
    uint16_t counter;
    uint16_t FuelPercentage;
    uint16_t TickCount;
    uint16_t speedcounter;
    uint32_t odometer ;
    uint16_t Trip_A_Value;
    uint16_t Trip_B_Value;
};

#endif // MODEL_HPP
