#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void SpeedUpdate(uint16_t newSpeed);
    virtual void KMPHtoMPH(int newCounter);
    virtual void FuelGauageAnimation(uint16_t newFuelCount);
    virtual void OdoDataUpdate(uint32_t newodoData);
    virtual void RPMDataAnimation(uint16_t newRPMData);
    virtual void TRIP_A(uint16_t newTripA);
    virtual void TRIP_B(uint16_t newTripB);
    virtual void ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat);
    virtual void SwitchingModes(uint8_t SwitchStatus);
    virtual void DriverInforMenu(uint8_t newMenu);

protected:
    touchgfx::BitmapId FuelbarImageIds[10];
    touchgfx::BitmapId RPMBarImageIds[10];

    uint16_t newCounter;
    uint16_t storedTRIP_A1;
    uint16_t storedTRIP_A2;
    uint16_t storedTRIP_B1;
    uint16_t storedTRIP_B2;
    uint8_t currentMenu;
    int tickCounter;


};


#endif // SCREEN1VIEW_HPP
