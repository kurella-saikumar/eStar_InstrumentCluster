#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
//#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Indicator_App/Indicator_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Clock_App/clock_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/DriverInfoMenu_App/DriverInfoMenu_App.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void SpeedUpdate(uint32_t newSpeedValue,uint8_t newSpeedMetrics);
    //virtual void KMPHtoMPH(int newCounter);
    virtual void FuelGauageAnimation(uint16_t newFuelCount);
    virtual void OdoDataUpdate(uint32_t newOdoData,uint8_t newOdoUnits);
    virtual void RPMDataAnimation(uint16_t newRPMData);
    virtual void TRIP_A(uint16_t newTripA_Value,uint8_t newTripA_Units);
    virtual void TRIP_B(uint16_t newTripB_Value, uint8_t newTripB_Units);
    virtual void AVSValue(uint32_t newAVS);
    virtual void AFEValue(uint32_t newAFE);
    virtual void RANGEValue(uint16_t newRANGE);
    virtual void ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat);
    //virtual void ClockValueChangingMode(uint8_t ClockEditingMode);
    virtual void SwitchingModes(uint8_t SwitchStatus);
    virtual void IndicatorsStatus(IndicationStatus_t newIndicators);

protected:
    touchgfx::BitmapId FuelbarImageIds[10];
    touchgfx::BitmapId RPMBarImageIds[10];

    uint16_t newCounter;
    uint16_t storedTRIP_A1;
    uint16_t storedTRIP_A2;
    uint8_t stroredTripA_Units;
    uint16_t storedTRIP_B1;
    uint16_t storedTRIP_B2;
    uint8_t stroredTripB_Units;
    uint32_t storednewAVS1;
    uint32_t storednewAVS2;
    uint32_t storednewAFE1;
    uint32_t storednewAFE2;
    uint16_t storednewRANGE1;
    uint16_t storednewRANGE2;
    uint8_t currentMenu;
    uint8_t Current_Hours;
    uint8_t Current_Minutes;
  //  uint8_t currentClockEditingMode;
    uint8_t Hour;
	uint8_t Minute;
	uint8_t TimeFormats;
	ClockEditActions_t ClockEditingMode;

    uint8_t ulShiftingPosition;
    int tickCounter;
    bool isBlinkingOn = 0;
    void updateClockVisibility(void);
    void updateClock_Hours_Buffer1Visibility(bool visible);
    void updateClock_Minutes_Buffer2Visibility(bool visible);
    //virtual void ClockValueChangingMode(uint8_t ClockEditingMode);
    void ClockValueChangingMode(void);
    void DriverInforMenu(void);
};


#endif // SCREEN1VIEW_HPP
