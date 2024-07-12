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

#if 0
void Screen1View::SpeedUpdate(uint32_t newSpeedValue,uint8_t newSpeedMetrics,uint8_t newSpeedStatus)
{
	if(newSpeedStatus == 0)
	{
		Unicode::snprintf(Speed_TaBuffer, SPEED_TA_SIZE, "%d",newSpeedValue);
		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		Speed_Ta.invalidate();
	}
	else
	{
		Unicode::snprintf(Speed_TaBuffer, SPEED_TA_SIZE, "%d",newSpeedValue);
		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		Speed_Ta.invalidate();
	}

	if(newSpeedMetrics == 0)
	{
		Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "KMPH");
		KMPH_MPH.invalidate();
	}
	else
	{
		Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "MPH");
		KMPH_MPH.invalidate();
	}
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
#endif

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

void Screen1View::DriverInforMenu(void)
{
	InfoMenu= xGetDriverInforMenu();
	switch(InfoMenu)
	{
	case 0 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "RANGE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewRANGE1);
				//DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewRANGE2);
//				if(Units == 1)
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
//				DriverInfo_Units.invalidate();
//				}
//				else
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
//				DriverInfo_Units.invalidate();
//				}
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 1 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AVS");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAVS1);
				//DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAVS2);
//				if(Units == 1)
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
//				DriverInfo_Units.invalidate();
//				}
//				else
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
//				DriverInfo_Units.invalidate();
//				}
				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 2 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "AFE");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storednewAFE1);
				//DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storednewAFE2);
//				if(Units == 1)
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MPL");
//				DriverInfo_Units.invalidate();
//				}
//				else
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KMPL");
//				DriverInfo_Units.invalidate();
//				}

				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 3 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""A");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_A1);
				//DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_A2);
//				if(Units == 1)
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
//				DriverInfo_Units.invalidate();
//				}
//				else
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
//				DriverInfo_Units.invalidate();
//				}

				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;
	case 4 :
				Unicode::snprintf(DriverInfoMenuBuffer, DRIVERINFOMENU_SIZE, "TRIP"" ""B");
				Unicode::snprintf(DriverInfoBuffer1, DRIVERINFOBUFFER1_SIZE, "%d",storedTRIP_B1);
				//DriverInfo.invalidate();
				Unicode::snprintf(DriverInfoBuffer2, DRIVERINFOBUFFER2_SIZE, "%d",storedTRIP_B2);
//				if(Units == 1)
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
//				DriverInfo_Units.invalidate();
//				}
//				else
//				{
//				Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
//				DriverInfo_Units.invalidate();
//				}

				DriverInfo.invalidate();
				DriverInfoMenu.invalidate();
				break;

	default:
				/* Nothing to do */
				break;
	}
}

void Screen1View:: MetricsToggle(uint8_t newMetrics)
{
	Units = newMetrics;
	if(Units == 0)
	{
		Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "KMPH");
		Unicode::snprintf(KMPH_MPH_ODOBuffer, KMPH_MPH_ODO_SIZE, "KM");
		KMPH_MPH.invalidate();
		KMPH_MPH_ODO.invalidate();

		switch(InfoMenu)
		{
			case 0 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
						DriverInfo_Units.invalidate();
					}
					break;
			case 1 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
						DriverInfo_Units.invalidate();
					}
					break;
			case 2 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KMPL");
						DriverInfo_Units.invalidate();
					}
					break;
			case 3 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
						DriverInfo_Units.invalidate();
					}
					break;
			case 4 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "KM");
						DriverInfo_Units.invalidate();
					}
					break;

			default:
							/* Nothing to do */
					break;
		}
	}
	else
	{
		Unicode::snprintf(KMPH_MPHBuffer, KMPH_MPH_SIZE, "MPH");
		Unicode::snprintf(KMPH_MPH_ODOBuffer, KMPH_MPH_ODO_SIZE, "MILES");
		KMPH_MPH.invalidate();
		KMPH_MPH_ODO.invalidate();

		switch(InfoMenu)
		{
			case 0 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
						DriverInfo_Units.invalidate();
					}
					break;
			case 1 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
						DriverInfo_Units.invalidate();
					}
					break;
			case 2 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MPL");
						DriverInfo_Units.invalidate();
					}
					break;
			case 3 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
						DriverInfo_Units.invalidate();
					}
					break;
			case 4 :
					{
						Unicode::snprintf(DriverInfo_UnitsBuffer, DRIVERINFO_UNITS_SIZE, "MILES");
						DriverInfo_Units.invalidate();
					}
					break;
			default:
							/* Nothing to do */
					break;
		}
	}
}







void Screen1View:: ClockUpdate (uint8_t Hours,uint8_t Minutes,uint8_t TimeFormat)
{
	Current_Hours = Hours;
	Current_Minutes = Minutes;
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

void Screen1View::updateClockVisibility(void)
{
	tickCounter++;
	if (tickCounter <=3)  // Adjust this value to control blink frequency
	{
		Clock.setVisible(!Clock.isVisible());
		Clock.invalidate();
		tickCounter = 0;
	}
}


#if 1
void Screen1View::ClockValueChangingMode(void)
{
	clockSettingRunMode(ClockEditingMode);
	switch (ClockEditingMode)
	{
		case 0:
				{
					updateClock_Hours_Buffer1Visibility(isBlinkingOn);
//					ClockUpdate(Hour,Minute,TimeFormats);
				}

				break;

		case 1:
				{
					ClockUpdate(Hour,Minute,TimeFormats);
				}
				break;

		case 3:
				{
					ulShiftingPosition++;
					if (ulShiftingPosition == 1)
					{
						updateClock_Hours_Buffer1Visibility(isBlinkingOn);
						ClockUpdate(Hour,Minute,TimeFormats);
					}
					else
					{
						updateClock_Minutes_Buffer2Visibility(isBlinkingOn);
						ClockUpdate(Hour,Minute,TimeFormats);
						ulShiftingPosition = 0;
					}
				}
				break;

		case 4:
				{
					ClockUpdate(Hour,Minute,TimeFormats);
				}
				break;

		case 5:
				{
					ClockUpdate(Hour,Minute,TimeFormats);
				}
				break;

		case 6:
				{
					if (ulShiftingPosition == 1)
					{
						ClockUpdate(Hour,Minute,TimeFormats);
					}
					else if (ulShiftingPosition == 2)
					{
						ClockUpdate(Hour,Minute,TimeFormats);
					}
				}
				break;
		default:
				// Handle unknown mode
				break;
	}

}
#endif


void Screen1View::updateClock_Hours_Buffer1Visibility(bool visible)
{
	tickCounter++;
	if (tickCounter >=1)
	{
		tickCounter = 0;
		isBlinkingOn = !isBlinkingOn;
		if (visible)
		{
			Unicode::snprintf(ClockBuffer1, CLOCKBUFFER1_SIZE, "%d",Current_Hours); // Preserve the hour value
		}
		else
		{
			Unicode::snprintf(ClockBuffer1, CLOCKBUFFER1_SIZE, ""); // Clear the text to make it invisible
		}
	Clock.invalidate(); // Refresh the widget to apply changes
	}
}

void Screen1View::updateClock_Minutes_Buffer2Visibility(bool visible)
{
	tickCounter++;
	if (tickCounter >=1)
	{
		tickCounter = 0;
		isBlinkingOn = !isBlinkingOn;
		if (visible)
		{
			Unicode::snprintf(ClockBuffer2, CLOCKBUFFER1_SIZE, "%d",Current_Minutes); // Preserve the Minutes value
		}
		else
		{
			Unicode::snprintf(ClockBuffer2, CLOCKBUFFER1_SIZE, ""); // Clear the text to make it invisible
		}
	Clock.invalidate(); // Refresh the widget to apply changes
	}
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

void Screen1View::IndicatorsStatus(IndicationStatus_t newIndicators)
{
	if(newIndicators.indicators.right_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			RightIndicator_r.setVisible(!RightIndicator_r.isVisible());
			RightIndicator_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		RightIndicator_r.setVisible(false);
		RightIndicator_r.invalidate();
	}


	if(newIndicators.indicators.right_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			LeftIndicator_r.setVisible(!LeftIndicator_r.isVisible());
			LeftIndicator_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		LeftIndicator_r.setVisible(false);
		LeftIndicator_r.invalidate();
	}


	if(newIndicators.indicators.parking_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			Parking_r.setVisible(!Parking_r.isVisible());
			Parking_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		Parking_r.setVisible(false);
		Parking_r.invalidate();
	}


	if(newIndicators.indicators.HighBeam_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			HighBeam_r.setVisible(!HighBeam_r.isVisible());
			HighBeam_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		HighBeam_r.setVisible(false);
		HighBeam_r.invalidate();
	}

	if(newIndicators.indicators.LowBeam_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			LowBeam_r.setVisible(!LowBeam_r.isVisible());
			LowBeam_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		LowBeam_r.setVisible(false);
		LowBeam_r.invalidate();
	}

	if(newIndicators.indicators.engine_oil_temp_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			Temperature_r.setVisible(!Temperature_r.isVisible());
			Temperature_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		EngineOIl_r.setVisible(false);
		EngineOIl_r.invalidate();
	}

	if(newIndicators.indicators.seat_belt_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			SeatBelt_r.setVisible(!SeatBelt_r.isVisible());
			SeatBelt_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		SeatBelt_r.setVisible(false);
		SeatBelt_r.invalidate();
	}


	if(newIndicators.indicators.engine_malfunction_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			EngineWarning_y.setVisible(!EngineWarning_y.isVisible());
			EngineWarning_y.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		EngineWarning_y.setVisible(false);
		EngineWarning_y.invalidate();
	}


	if(newIndicators.indicators.door_open_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			DoorsIcon_r.setVisible(!DoorsIcon_r.isVisible());
			DoorsIcon_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		DoorsIcon_r.setVisible(false);
		DoorsIcon_r.invalidate();
	}

	if(newIndicators.indicators.abs_warning_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			ABS_Detection_r.setVisible(!ABS_Detection_r.isVisible());
			ABS_Detection_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		ABS_Detection_r.setVisible(false);
		ABS_Detection_r.invalidate();
	}


//	if(newIndicators.indicators.FaultyRight_indicator == 1)
//	{
//		tickCounter++;
//		if (tickCounter >=2)  // Adjust this value to control blink frequency
//		{
//			RightIndicator_r.setVisible(!RightIndicator_r.isVisible());
//			RightIndicator_r.invalidate();
//			tickCounter = 0;
//		}
//	}
//	else
//	{
//		RightIndicator_r.setVisible(false);
//		RightIndicator_r.invalidate();
//	}

//	if(newIndicators.indicators.FaultyLeft_indicator == 1)
//	{
//		tickCounter++;
//		if (tickCounter >=2)  // Adjust this value to control blink frequency
//		{
//			LeftIndicator_r.setVisible(!LeftIndicator_r.isVisible());
//			LeftIndicator_r.invalidate();
//			tickCounter = 0;
//		}
//	}
//	else
//	{
//		LeftIndicator_r.setVisible(false);
//		LeftIndicator_r.invalidate();
//	}

	if(newIndicators.indicators.low_battery_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			LowBatteryIcon_r.setVisible(!LowBatteryIcon_r.isVisible());
			LowBatteryIcon_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		LowBatteryIcon_r.setVisible(false);
		LowBatteryIcon_r.invalidate();
	}


	if(newIndicators.indicators.service_reminder_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			ServiceReminder_y.setVisible(!ServiceReminder_y.isVisible());
			ServiceReminder_y.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		ServiceReminder_y.setVisible(false);
		ServiceReminder_y.invalidate();
	}

	if(newIndicators.indicators.tachometer_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			RPMIcon_r.setVisible(!RPMIcon_r.isVisible());
			RPMIcon_r.invalidate();
			tickCounter = 0;
		}
	}
	else
	{
		RPMIcon_r.setVisible(false);
		RPMIcon_r.invalidate();
	}


	if(newIndicators.indicators.over_speed_indicator == 1)
	{

		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		Speed_Ta.invalidate();
	}
	else
	{
		Speed_Ta.setColor(touchgfx::Color::getColorFromRGB(255,255,255));
		Speed_Ta.invalidate();
	}

	if(newIndicators.indicators.Fuel_warning_indicator == 1)
	{
		tickCounter++;
		if (tickCounter >=1)  // Adjust this value to control blink frequency
		{
			FuelIcon_r.setVisible(!FuelIcon_r.isVisible());
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




