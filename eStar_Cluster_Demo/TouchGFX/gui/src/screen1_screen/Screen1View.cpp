#include <gui/screen1_screen/Screen1View.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>


Screen1View::Screen1View()
{
	 for (int i = 0; i < 10; ++i)
	 {
			barImageIds[i] = 0; // Or initialize with the appropriate BitmapId values
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
void Screen1View::OdoDataUpdate(uint16_t newodoData)
{
	Unicode::snprintf(ODOReadingsBuffer, ODOREADINGS_SIZE, "%u", newodoData);

	// Set the text of the ODOReadings widget to display the updated odometer value
	ODOReadings.invalidate();
}

void Screen1View::FuelGauageAnimation(int newCounter)
{

	 for (int i = 0; i < 10; ++i)
	 {
		barImageIds[i] = BITMAP_FUELBAR01_ID + i;
	 }
	 FuelBarAnimation.setBitmaps(barImageIds[0], barImageIds[9]);

	 int percentage = (newCounter * 100)/220;
	 int imageIndex = (percentage/10)%10;


	// Set the current image for the animation
	FuelBarAnimation.setBitmaps(barImageIds[imageIndex], barImageIds[9]);

	FuelBarAnimation.invalidate();
}
