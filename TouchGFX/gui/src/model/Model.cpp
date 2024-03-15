#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"

Model::Model() : modelListener(0), Button_State(false)
{

}

void Model::tick()
{
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13))
	{
		Button_State = true;
	}
	else Button_State = false;

	modelListener->setLight (Button_State);
}
