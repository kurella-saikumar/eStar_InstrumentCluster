#include <gui/screen1_screen/Screen1View.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <cstdio>


Screen1View::Screen1View()
{
	 for (int i = 0; i < 10; i++)
	 {
		 FuelbarImageIds[i] = 0; // Or initialize with the appropriate BitmapId values
		 RPMBarImageIds[i] = 0;
	 }
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    FuelIcon_r.setVisible(false);
    LowBatteryIcon_r.setVisible(false);
    EngineOIl_r.setVisible(false);
    DoorsIcon_r.setVisible(false);
    Temperature_r.setVisible(false);
    HighBeam_r.setVisible(false);
    LeftIndicator_r.setVisible(false);
    RightIndicator_r.setVisible(false);
    RPMIcon_r.setVisible(false);
    ABS_Detection_r.setVisible(false);
    LowBeam_r.setVisible(false);
    SeatBelt_r.setVisible(false);
	Parking_r.setVisible(false);
	EngineWarning_y.setVisible(false);
	ServiceReminder_y.setVisible(false);
}


void Screen1View::SpeedUpdate(uint32_t newSpeedValue)
{
	Unicode::snprintf(Speed_TaBuffer, SPEED_TA_SIZE, "%d",newSpeedValue);
	Speed_Ta.invalidate();

}


void Screen1View::OdoDataUpdate(uint32_t newOdoData)
{
	Unicode::snprintf(ODOReadingsBuffer, ODOREADINGS_SIZE, "%u", newOdoData);
	ODOReadings.invalidate();
}



void Screen1View::FuelGauageAnimation(uint16_t newFuelCount)
{

	 for (int i = 0; i < 10; i++)
	 {
		 FuelbarImageIds[i] = BITMAP_FUELBAR01_ID + i;
	 }

	 FuelBarAnimation.setBitmaps(FuelbarImageIds[0], FuelbarImageIds[9]);

	 if (newFuelCount<100)
	 {
		int imageIndex = 9 -(newFuelCount/10);

		// Set the current image for the animation
		FuelBarAnimation.setBitmaps(FuelbarImageIds[imageIndex], FuelbarImageIds[imageIndex]);
	 }
	 else
	 {
		 FuelBarAnimation.setBitmaps(FuelbarImageIds[0], FuelbarImageIds[0]);
	 }

	 FuelBarAnimation.invalidate();
}

void Screen1View:: RPMDataAnimation(uint16_t newRPMData)
{
	for (int i = 0; i < 10; i++)
	{
		RPMBarImageIds[i] = BITMAP_RPMBAR01_ID + i;
	}
	RPMAnimation.setBitmaps(RPMBarImageIds[0], RPMBarImageIds[9]);

	if(newRPMData<12000)
	{
		uint16_t imageIndex = (newRPMData/1200);
		// Set the current image for the animation
		RPMAnimation.setBitmaps(RPMBarImageIds[imageIndex], RPMBarImageIds[imageIndex]);
		RPMAnimation.invalidate();
	}
	else
	{
		RPMAnimation.setBitmaps(RPMBarImageIds[9], RPMBarImageIds[9]);
		RPMAnimation.invalidate();
	}
}

void Screen1View::TRIP_A(uint16_t newTripA_Value)
{
	storedTRIP_A1 = newTripA_Value / 10;
	storedTRIP_A2 = newTripA_Value % 10;
}

void Screen1View::TRIP_B(uint16_t newTripB_Value)
{
	storedTRIP_B1 = newTripB_Value / 10;
	storedTRIP_B2 = newTripB_Value % 10;
}

void Screen1View::AVSValue(uint32_t newAVS)
{
	storednewAVS1 = newAVS;
	storednewAVS2 = 00;
}

void Screen1View::AFEValue(uint32_t newAFE)
{
	storednewAFE1 = newAFE / 10;
	storednewAFE2 = newAFE % 10;
}

void Screen1View::RANGEValue(uint16_t newRANGE)
{
	storednewRANGE1 = newRANGE / 10;
	storednewRANGE2 = newRANGE % 10;
}

void Screen1View::DriverInforMenu(void)
{
	InfoMenu = xGetDriverInforMenu();
	switch(InfoMenu)
	{
	case 0 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "RANGE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewRANGE1);
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewRANGE2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 1 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AVS");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAVS1);
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAVS2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 2 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AFE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAFE1);
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAFE2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 3 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""A");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_A1);
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_A2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 4 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""B");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_B1);
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_B2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;

	default:
				/* Nothing to do */
				break;
	}
}


void Screen1View::MetricsToggle(uint8_t newMetrics)
{
    Units = newMetrics;

    const char* SpeedUnits = (Units == 0) ? "KMPH" : "MPH";
    const char* OdoUnits = (Units == 0) ? "KM" : "MILES";
    const char* AFEUnits = (Units == 0) ? "KMPL" : "MPL";

    Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, SpeedUnits);
    Unicode::snprintf(KMPH_MPH_ODOBuffer, KMPH_MPH_ODO_SIZE, OdoUnits);
    KMPH_MPH.invalidate();
    KMPH_MPH_ODO.invalidate();

    switch (InfoMenu)
    {
		case 0:
		case 1:
		case 3:
		case 4:
				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, OdoUnits);
				DriverInfo_Units.invalidate();
				break;
		case 2:
				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, AFEUnits);
				DriverInfo_Units.invalidate();
				break;
		default:
				/* Nothing to do */
				break;
    }
}


void Screen1View:: ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t Seconds, uint8_t TimeFormat)
{

	Current_Hours = Hours;
	Current_Minutes = Minutes;
	Current_Seconds = Seconds;

	Unicode::snprintf(Clock_HRBuffer, CLOCK_HR_SIZE, "%d", Hours);
	Unicode::snprintf(Clock_MNBuffer, CLOCK_MN_SIZE, "%d", Minutes);
	//const char* amPmText = (TimeFormat == 0) ? "AM" : "PM";
	const char* amPmText = (TimeFormat == 0) ? "" : "";
	Unicode::snprintf(AM_PMBuffer, AM_PM_SIZE, amPmText);

	if (Previous_Seconds != Current_Seconds)  // Adjust this value to control blink frequency
	{
		Clock_SEC.setVisible(!Clock_SEC.isVisible());
		Clock_SEC.invalidate();
		Previous_Seconds = Current_Seconds;
	}
	Clock_HR.invalidate();
	Clock_MN.invalidate();
	AM_PM.invalidate();
}



void Screen1View::updateClock_HoursVisibility(void)
{
	Clock_HR.setVisible(!Clock_HR.isVisible());
	Clock_HR.invalidate();
}

void Screen1View::updateClock_MinutesVisibility(void)
{
	Clock_MN.setVisible(!Clock_MN.isVisible());
	Clock_MN.invalidate();
}



void Screen1View::ClockValueChangingMode(void)
{
    switch (ClockEditing)
    {
        case CLOCK_ENTRY:
            {
            	startBlinkingHours();
            }
            break;

        case MODE_LONGPRESS:
            {
                stopBlinking();
            }
            break;

        case MODE_SHORTPRESS:
            {
        		if (ulShiftingPosition == E_CLOCK_HOURS_POS)
				{
        			startBlinkingHours();
				}
        		else if(ulShiftingPosition == E_CLOCK_MINS_POS)
				{
        			startBlinkingMinutes();
				}
        		else
        		{

        		}
            }
            break;

        case RESET_LONGPRESS_RELEASE:
            {
            	stopBlinking();
            }
            break;

        case RESET_LONGPRESS_HELD:
            {
            	stopBlinking();
            }
            break;

        case RESET_SHORTPRESS:
            {
				if (ulShiftingPosition == E_CLOCK_HOURS_POS)
				{
					startBlinkingHours();
				}
				else if(ulShiftingPosition == E_CLOCK_MINS_POS)
				{
					startBlinkingMinutes();
				}
				else
				{
				}
            }
            break;

        default:
            // Handle unknown mode
            break;
    }
}

void Screen1View::startBlinkingHours(void)
{
	Clock_HR.setVisible(!Clock_HR.isVisible());
    Clock_HR.invalidate();
}

void Screen1View::startBlinkingMinutes(void)
{
	Clock_MN.setVisible(!Clock_MN.isVisible());
    Clock_MN.invalidate();
}

void Screen1View::stopBlinking(void)
{
    Clock_HR.setVisible(true);
    Clock_HR.invalidate();
    Clock_MN.setVisible(true);
    Clock_MN.invalidate();
}

void Screen1View::StopHoursBlinking(void)
{
    Clock_HR.setVisible(true);
    Clock_HR.invalidate();
}

void Screen1View::StopMinutesBlinking(void)
{
    Clock_MN.setVisible(true);
    Clock_MN.invalidate();
}

void Screen1View:: SwitchingModes(uint8_t SwitchStatus)
{
	switch(SwitchStatus)
	{
	case 0:
			//odo meTER tOGGLE//
			break;
	case 1:
			{
				ClockValueChangingMode();
			}


			break;
	case 2:
				DriverInforMenu();
			break;

	default:
			break;
	}
}



void Screen1View::BlinkIndicator(bool state, uint32_t& tickCounters, Image& icon, uint32_t frequency)
{
    if (state)
    {
        tickCounters++;
        if (tickCounters >= frequency)
        {
            icon.setVisible(!icon.isVisible());
            icon.invalidate();
            tickCounters = 0;
        }
    }
    else
    {
        icon.setVisible(false);
        icon.invalidate();
        tickCounters = 0; // Reset tickCounter when state is false
    }
}


void Screen1View::IndicatorsStatus(IndicationStatus_t newIndicators)
{
    BlinkIndicator(newIndicators.indicators.right_indicator, tickCounterRightIndicator, RightIndicator_r, 7);
    BlinkIndicator(newIndicators.indicators.left_indicator, tickCounterLeftIndicator, LeftIndicator_r, 7);
    BlinkIndicator(newIndicators.indicators.parking_indicator, tickCounterParking, Parking_r, 7);
    BlinkIndicator(newIndicators.indicators.HighBeam_indicator, tickCounterHighBeam, HighBeam_r, 7);
    BlinkIndicator(newIndicators.indicators.LowBeam_indicator, tickCounterLowBeam, LowBeam_r, 7);
    BlinkIndicator(newIndicators.indicators.engine_oil_temp_indicator, tickCounterEngineOilTemp, Temperature_r, 7);
    BlinkIndicator(newIndicators.indicators.seat_belt_indicator, tickCounterSeatBelt, SeatBelt_r, 7);
    BlinkIndicator(newIndicators.indicators.engine_malfunction_indicator, tickCounterEngineMalfunction, EngineWarning_y, 7);
    BlinkIndicator(newIndicators.indicators.door_open_indicator, tickCounterDoorOpen, DoorsIcon_r, 7);
    BlinkIndicator(newIndicators.indicators.abs_warning_indicator, tickCounterABSWarning, ABS_Detection_r, 7);
    //BlinkIndicator(newIndicators.indicators.FaultyRight_indicator, tickCounterFaultyRightIndicator, RightIndicator_r, 1);
    //BlinkIndicator(newIndicators.indicators.FaultyLeft_indicator, tickCounterFaultyLeftIndicator, LeftIndicator_r, 1);
    BlinkIndicator(newIndicators.indicators.Engine_Oil_indicator, tickCounterEngineOil, EngineOIl_r, 7);
    BlinkIndicator(newIndicators.indicators.low_battery_indicator, tickCounterLowBattery, LowBatteryIcon_r, 7);
    BlinkIndicator(newIndicators.indicators.service_reminder_indicator, tickCounterServiceReminder, ServiceReminder_y, 7);
    BlinkIndicator(newIndicators.indicators.tachometer_indicator, tickCounterTachometer, RPMIcon_r,7);
    BlinkIndicator(newIndicators.indicators.Fuel_warning_indicator, tickCounterFuelWarning, FuelIcon_r, 7);

    // Color handling for over_speed_indicator (no blinking, just color change)
    if (newIndicators.indicators.over_speed_indicator == 1)
    {
        Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
        Speed_Ta.invalidate();
    }
    else
    {
        Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        Speed_Ta.invalidate();
    }
}



