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
    uint16_t storedCounter;
    virtual void UpdateCount(uint16_t newCounter);
   // virtual void UpdateSpeed();
    virtual void FuelbarWarningIcon(int newCounter);
    virtual void KMPHtoMPH(int newCounter);
    virtual void FuelGauageAnimation(int newCounter);
protected:
    touchgfx::BitmapId barImageIds[10];
    uint16_t newCounter;
};


#endif // SCREEN1VIEW_HPP
