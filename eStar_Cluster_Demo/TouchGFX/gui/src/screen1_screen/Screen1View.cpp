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
    //InitializeFuelBarAnimation();

}
#if 0
void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
#endif

void Screen1View::UpdateCount(uint16_t newCounter)
{
	Unicode::snprintf(Speed_TaBuffer, SPEED_TA_SIZE, "%d",newCounter);

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

void Screen1View::KMPHtoMPH(int newCounter)
{
	if (newCounter >110)
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








