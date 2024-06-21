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

    //void FuelData();
protected:
    ModelListener* modelListener;
    uint16_t counter;
    //uint16_t FuelCounter;
    uint16_t TickCount;
    uint16_t speedcounter;
    uint32_t odometer ;
};

#endif // MODEL_HPP
