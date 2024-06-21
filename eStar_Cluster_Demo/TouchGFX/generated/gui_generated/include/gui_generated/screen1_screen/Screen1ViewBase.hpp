/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image BackGround;
    touchgfx::Image image1;
    touchgfx::Image ABS_Detection_w;
    touchgfx::Image ABS_Detection_r;
    touchgfx::Image LowBatteryIcon_w;
    touchgfx::Image LowBatteryIcon_r;
    touchgfx::Image DoorsIcon_w;
    touchgfx::Image DoorsIcon_r;
    touchgfx::Image EngineOIl_w;
    touchgfx::Image EngineOIl_r;
    touchgfx::Image Temperature_w;
    touchgfx::Image Temperature_r;
    touchgfx::Image FuelICon_w;
    touchgfx::Image FuelIcon_r;
    touchgfx::Image HighBeam_w;
    touchgfx::Image HighBeam_r;
    touchgfx::Image LeftIndicator_w;
    touchgfx::Image LeftIndicator_r;
    touchgfx::Image LowBeam_w;
    touchgfx::Image LowBeam_r;
    touchgfx::Image RightIndicator_w;
    touchgfx::Image RightIndicator_r;
    touchgfx::Image RPMIcon_w;
    touchgfx::Image RPMIcon_r;
    touchgfx::AnimatedImage FuelBarAnimation;
    touchgfx::TextAreaWithOneWildcard Speed_Ta;
    touchgfx::TextAreaWithOneWildcard KMPH_MPH;
    touchgfx::TextAreaWithOneWildcard KMPH_MPH_ODO;
    touchgfx::TextAreaWithOneWildcard KMPH_MPH_DTE;
    touchgfx::TextAreaWithOneWildcard ODOReadings;
    touchgfx::TextAreaWithOneWildcard DriverInfo;
    touchgfx::TextAreaWithOneWildcard DriverInfo_Data;
    touchgfx::TextAreaWithOneWildcard Clock_HR;
    touchgfx::TextAreaWithOneWildcard Clock_MIN;
    touchgfx::TextAreaWithOneWildcard Semicolon;
    touchgfx::TextAreaWithOneWildcard AM_PM;
    touchgfx::Image RPMBars;

    /*
     * Wildcard Buffers
     */
    static const uint16_t SPEED_TA_SIZE = 4;
    touchgfx::Unicode::UnicodeChar Speed_TaBuffer[SPEED_TA_SIZE];
    static const uint16_t KMPH_MPH_SIZE = 5;
    touchgfx::Unicode::UnicodeChar KMPH_MPHBuffer[KMPH_MPH_SIZE];
    static const uint16_t ODOREADINGS_SIZE = 12;
    touchgfx::Unicode::UnicodeChar ODOReadingsBuffer[ODOREADINGS_SIZE];

private:

};

#endif // SCREEN1VIEWBASE_HPP
