/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

Screen1ViewBase::Screen1ViewBase()
{
    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_IMAGE_ID));
    add(image1);

    Low_Fuel.setXY(54, 241);
    Low_Fuel.setBitmap(touchgfx::Bitmap(BITMAP_FUEL_RED_ID));
    add(Low_Fuel);
}

Screen1ViewBase::~Screen1ViewBase()
{

}

void Screen1ViewBase::setupScreen()
{

}
