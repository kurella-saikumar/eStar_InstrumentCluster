#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "../../../eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App/speedometer_App.h"
//#include <../Core/src/App/Speedometer_App/speedometer_App.h>
//#include "../Application/User/Core/src/App/Speedometer_App/speedometer_App.h"
//#include <../Core/src/App/Speedometer_App/speedometer_App.h>
//#include <../Core/src/App/Indicator_App/Indicator_App.h>
//#include "../User/Core/src/App/Speedometer_App/speedometer_App.h"


bool isButtonPressed = false;
static uint32_t ulOdoCounter = 0;

speedDisplayMetrics_t speedMetrics;

IndicationStatus_t speedStatus;

//extern uint32_t xGetSpeedValue(speedDisplayMetrics_t *speedDisplayUnits, IndicationStatus_t *speedStatus);

// Function to simulate button press
void simulateButtonPress() {
    isButtonPressed = true;
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
//	counter = xGetSpeedValue(speedMetrics, speedStatus);

	//counter =xGetSpeedValue(speedDisplayMetrics_t *speedDisplayUnits, IndicationStatus_t *speedStatus);

	if(modelListener !=0)
	{
		modelListener->notifyCounterChanged(xGetSpeedValue(&speedMetrics, &speedStatus));
	}
}

#if 0
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

#endif




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



//void SpeedData()
//{
//    speedDisplayMetrics_t speedMetrics; // Example initialization
//    IndicationStatus_t speedStatus;     // Example initialization
//
//    uint32_t speedValue = xGetSpeedValue(&speedMetrics, &speedStatus);
//}







//void xGetSpeedValue()
//{
//	uint32_t xGetSpeedValue(speedDisplayMetrics_t *speedDisplayUnits, IndicationStatus_t *speedStatus);
//}
#if 0
uint32_t xGetSpeedValue(speedDisplayMetrics_t *speedDisplayUnits, IndicationStatus_t *speedStatus)
{
    *speedDisplayUnits = speedoUnits;

    if(xSafeSpeedCheck())
    {
    	speedStatus->indicators.over_speed_indicator = 1;

//    printf("dU: %d\t", speedDisplayUnits);   //Debug purpose
//    printf("dI: %d\t", speedStatus);   //Debug purpose
    }

		if(speedoUnits == SPEED_IN_KMPH)
		{
			return ulSpeedInKm;
		}
		else if(speedoUnits == SPEED_IN_MPH)
		{
			return ulspeedInMiles;
		}
 return 0;
}
#endif


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
