#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>

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
    //void FuelData();
protected:
    ModelListener* modelListener;
    uint16_t counter;
    //uint16_t FuelCounter;
    uint16_t TickCount;
};

#endif // MODEL_HPP
