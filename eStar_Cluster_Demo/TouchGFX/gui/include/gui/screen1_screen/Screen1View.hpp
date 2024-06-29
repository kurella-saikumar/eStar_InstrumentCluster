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
   // virtual void tearDownScreen();
   // uint16_t storedCounter;
    virtual void UpdateCount(uint16_t newCounter);
   // virtual void UpdateSpeed();
    //virtual void FuelbarWarningIcon(int newCounter);
    virtual void KMPHtoMPH(int newCounter);
    virtual void FuelGauageAnimation(uint16_t newFuelCount);
    virtual void OdoDataUpdate(uint32_t newodoData);
    virtual void RPMDataAnimation(uint16_t newRPMData);
    virtual void DriverInforMenu(uint8_t newMenu);


protected:
    touchgfx::BitmapId FuelbarImageIds[10];
    touchgfx::BitmapId RPMBarImageIds[10];
    uint16_t newCounter;
    int tickCounter;
};


#endif // SCREEN1VIEW_HPP
