#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
//#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Indicator_App/Indicator_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/Clock_App/clock_App.h"
#include "../../../../STM32CubeIDE/Application/User/Core/src/App/DriverInfoMenu_App/DriverInfoMenu_App.h"
#include "../../../../../STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler/SwitchHandler_App.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void SpeedUpdate(uint32_t newSpeedValue);
    //virtual void KMPHtoMPH(int newCounter);
    virtual void FuelGauageAnimation(uint16_t newFuelCount);
    virtual void OdoDataUpdate(uint32_t newOdoData);
    virtual void RPMDataAnimation(uint16_t newRPMData);
    virtual void TRIP_A(uint16_t newTripA_Value);
    virtual void TRIP_B(uint16_t newTripB_Value);
    virtual void AVSValue(uint32_t newAVS);
    virtual void AFEValue(uint32_t newAFE);
    virtual void RANGEValue(uint16_t newRANGE);
    virtual void ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t Seconds,uint8_t TimeFormat);
    //virtual void ClockValueChangingMode(uint8_t ClockEditingMode);
    virtual void SwitchingModes(uint8_t SwitchStatus);
    virtual void IndicatorsStatus(IndicationStatus_t newIndicators);
    virtual void MetricsToggle(uint8_t newMetrics);



private:
    uint32_t tickCounterRightIndicator;
    uint32_t tickCounterLeftIndicator;
    uint32_t tickCounterParking;
    uint32_t tickCounterHighBeam;
    uint32_t tickCounterLowBeam;
    uint32_t tickCounterEngineOilTemp;
    uint32_t tickCounterSeatBelt;
    uint32_t tickCounterEngineMalfunction;
    uint32_t tickCounterDoorOpen;
    uint32_t tickCounterABSWarning;
    uint32_t tickCounterFaultyRightIndicator;
    uint32_t tickCounterFaultyLeftIndicator;
    uint32_t tickCounterEngineOil;
    uint32_t tickCounterLowBattery;
    uint32_t tickCounterServiceReminder;
    uint32_t tickCounterTachometer;
    uint32_t tickCounterFuelWarning;


    uint8_t Current_Hours;
    uint8_t Current_Minutes;


    void BlinkIndicator(bool state, uint32_t& tickCounters, Image& icon, uint32_t frequency);

protected:
    touchgfx::BitmapId FuelbarImageIds[10];
    touchgfx::BitmapId RPMBarImageIds[10];

    uint8_t Units;
    uint16_t newCounter;
    uint16_t storedTRIP_A1;
    uint16_t storedTRIP_A2;

    uint16_t storedTRIP_B1;
    uint16_t storedTRIP_B2;

    uint32_t storednewAVS1;
    uint32_t storednewAVS2;
    uint32_t storednewAFE1;
    uint32_t storednewAFE2;
    uint16_t storednewRANGE1;
    uint16_t storednewRANGE2;
    uint8_t currentMenu;

    uint8_t Current_Seconds;
    uint8_t Previous_Seconds;
  //  uint8_t currentClockEditingMode;
    uint8_t Hour;
	uint8_t Minute;
	uint8_t TimeFormats;
	//ClockEditActions_t ClockEditing;
	//bool ulClockShiftingPosition;
	//en_clockShiftingPositionType_t ulShiftingPosition;

	uint8_t InfoMenu;
    int tickCounter;
    //bool isBlinkingOn = 0;


    //void updateClockVisibility(void);
//    void updateClock_HoursVisibility(void);
//    void updateClock_MinutesVisibility(void);
    void startBlinkingHours(void);
    void startBlinkingMinutes(void);
    void stopBlinking(void);
//    void StopHoursBlinking(void);
//    void StopMinutesBlinking(void);

    //virtual void ClockValueChangingMode(uint8_t ClockEditingMode);
    void ClockValueChangingMode(void);
    void DriverInforMenu(void);

};


#endif // SCREEN1VIEW_HPP
