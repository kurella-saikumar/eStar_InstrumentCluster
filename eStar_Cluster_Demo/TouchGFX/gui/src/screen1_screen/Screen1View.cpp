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
}


void Screen1View::SpeedUpdate(uint16_t newSpeed)
{
	Unicode::snprintf(Speed_TaBuffer, SPEED_TA_SIZE, "%d",newSpeed);

	if(newCounter > 80)
	{
		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}
	else
	{
		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	Speed_Ta.invalidate();
}
#if 0
void Screen1View::FuelbarWarningIcon(int newCounter)
{

	if(newCounter > 80 )
	{
		FuelIcon_r.setVisible(true);
	}
	else
	{
		FuelIcon_r.setVisible(false);
	}
	FuelIcon_r.invalidate();
}
#endif

void Screen1View::KMPHtoMPH(int newSpeed)
{
	if (newSpeed >110)
	{
		Unicode::UnicodeChar* currentText = KMPH_MPHBuffer;

		if (Unicode::strncmp(currentText, TypedText(T___SINGLEUSE_ZEGA).getText(), Unicode::strlen("KMPH")) == 0)
		{
			// Change the text buffer to "MPH"
			Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "MPH");

			// Update the text in the TextArea
			KMPH_MPH.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DKL2));

			// Invalidate the text area to trigger a redraw
			KMPH_MPH.invalidate();
		}

	}
	else
	{
		Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "KMPH");

		// Update the text in the TextArea
		KMPH_MPH.setTypedText(TypedText(T___SINGLEUSE_ZEGA));
		KMPH_MPH.invalidate();
	}
}
void Screen1View::OdoDataUpdate(uint32_t newodoData)
{
	Unicode::snprintf(ODOReadingsBuffer, ODOREADINGS_SIZE, "%u", newodoData);

	// Set the text of the ODOReadings widget to display the updated odometer value
	ODOReadings.invalidate();
}
#if 0
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

		if(newFuelCount < 10)
		{
			tickCounter++;
			if (tickCounter >=1)  // Adjust this value to control blink frequency
			{
				FuelIcon_r.setVisible(!FuelIcon_r.isVisible());
				FuelBarAnimation.setVisible(!FuelBarAnimation.isVisible());
				FuelIcon_r.invalidate();
				tickCounter = 0;
			}
		}
		else
		{
			FuelIcon_r.setVisible(false);
			FuelIcon_r.invalidate();
		}
	 }
	 else
	 {
		 FuelBarAnimation.setBitmaps(FuelbarImageIds[0], FuelbarImageIds[0]);
	 }

	 FuelBarAnimation.invalidate();
}
#endif

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

	uint16_t imageIndex = (newRPMData/1200);

	// Set the current image for the animation
	RPMAnimation.setBitmaps(RPMBarImageIds[imageIndex], RPMBarImageIds[imageIndex]);

	RPMAnimation.invalidate();
}

void Screen1View::TRIP_A(uint16_t newTripA)
{
		storedTRIP_A1 = newTripA / 10;
		storedTRIP_A2 = newTripA % 10;
}

void Screen1View::TRIP_B(uint16_t newTripB)
{
		storedTRIP_B1 = newTripB / 10;
		storedTRIP_B2 = newTripB % 10;
}

void Screen1View::AVSValue(uint32_t newAVS)
{
		storednewAVS1 = newAVS / 10;
		storednewAVS2 = newAVS % 10;
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

void Screen1View::DriverInforMenu(uint8_t newMenu)
{
	currentMenu = newMenu;
	switch(newMenu)
	{
	case 0 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "RANGE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewRANGE1);
				DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewRANGE2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 1 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AVS");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAVS1);
				DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAVS2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 2 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AFE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAFE1);
				DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAFE2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 3 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""A");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_A1);
				DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_A2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 4 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""B");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_B1);
				DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_B2);
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;

	default:
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "RANGE");
				DriverInfoMenu.invalidate();
				break;
	}
}

void Screen1View:: ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat)
{
	Unicode::snprintf(ClockBuffer1, CLOCKBUFFER1_SIZE, "%d", Hours);
	Unicode::snprintf(ClockBuffer2, CLOCKBUFFER2_SIZE, "%d", Minutes);
	if (TimeFormat==0)
	{
		Unicode::snprintf(AM_PMBuffer, AM_PM_SIZE,"AM");
	}
	else
	{
		Unicode::snprintf(AM_PMBuffer, AM_PM_SIZE,"PM");
	}
	Clock.invalidate();
	AM_PM.invalidate();
}

void Screen1View:: SwitchingModes(uint8_t SwitchStatus)
{
	switch(SwitchStatus)
	{
	case 0:
			//odo meTER tOGGLE//
			break;
	case 1:
			tickCounter++;
			if (tickCounter >=1)  // Adjust this value to control blink frequency
			{
				Clock.setVisible(!	Clock.isVisible());
				Clock.invalidate();
				tickCounter = 0;
			}
			break;
	case 2:
				DriverInforMenu(currentMenu);
			break;

	default:
			break;
	}
}











