#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

bool isButtonPressed = false;
static uint32_t ulOdoCounter = 0;
// Function to simulate button press
void simulateButtonPress() {
    //isButtonPressed = true;
}

// Function to simulate button release
void simulateButtonRelease() {
    isButtonPressed = false;
}

Model::Model() : modelListener(0),counter(0),TickCount(0),speedcounter(0),odometer(0)
{

}
#if 1

void Model::tick()
{
	TickCount++;

	if (TickCount > 100)
	{
		speedcounter++;
		if (speedcounter < 120)
		{
			simulateButtonPress(); // Simulate button press when speed counter is less than 100
		}
		else
		{
			simulateButtonRelease(); // Simulate button release when speed counter is 100 or more
		}

		SpeedData();
		OdoData();
		//FuelData();
		TickCount =0;
	}
}
#endif
void Model::SpeedData()
{
	if(counter < 220)
	{
		//counter =0;
		 if (isButtonPressed)
		 {
		        counter++;  // Increment counter when button is pressed
		 }
		 else
		 {
			 //counter--;
		 }
	}
	else
	{

	}

	if(modelListener !=0)
	{
		modelListener->notifyCounterChanged(counter);
	}
}

void Model::OdoData()
{
    // Define a constant value representing the distance covered per tick
    const int distancePerTick = 1; // For example, 10 units per tick

    // Update odometer data based on the button state
    ulOdoCounter++;
    if(ulOdoCounter > 10)
    {
    	ulOdoCounter=0;
        if (isButtonPressed)
        {
            // Increment odometer value when button is pressed
            odometer += distancePerTick;
        }
        else
        {
            // Do any other operation when button is released
        }

    }
    else
    {
    	// Do Nothing
    }


    // Notify listener about odometer data change
    if (modelListener != nullptr)
    {
        modelListener->notifyOdoDataChanged(odometer);
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
