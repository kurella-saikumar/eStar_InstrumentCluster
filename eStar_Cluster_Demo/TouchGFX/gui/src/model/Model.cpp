#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


Model::Model() : modelListener(0),counter(0),TickCount(0)
{

}
#if 0

void Model::tick()
{
	TickCount++;
	if (TickCount > 10)
	{
		SpeedData();
		//FuelData();
		TickCount =0;
	}
}
#endif
void Model::tick()
{

	counter++;
	if(counter >220)
	{
		counter =0;
	}
	if(modelListener !=0)
	{
		modelListener->notifyCounterChanged(counter);
	}
}
#if 0
void Model::FuelData()
{
	FuelCounter++;
	if(modelListener !=0)
	{
		modelListener->notifyFuelCounter(FuelCounter);
	}
}
#endif
