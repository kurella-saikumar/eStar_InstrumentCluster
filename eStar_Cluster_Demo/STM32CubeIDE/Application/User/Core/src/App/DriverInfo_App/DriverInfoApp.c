/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file DriverInfoApp.c

 *
 * @brief Template C file
 *
 * File Short Name:  DriverInfoApp.c
 *
 * @author: Sivadhanalakshmi T
 *
 * Created on: Apr 4, 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "DriverInfoApp.h"
#include "../../Service/IO_HAL/Moving_Average_Algorithm/moving_avg.h"
#include "../../Service/IO_HAL/Switch_Handler/SwitchHandler_App.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "DriverInfoApp_cfg.h"
#include "Odometer_App.h"
#include "IGN_SmHandler.h"
#include "FuelGuage_App.h"
#include "Indicator_App.h"
#include "speedometer_App.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
MV_data_t l_AVS_MA_t;
MV_data_t l_Odo_MA_t;
MV_data_t l_Fuel_MA_t;

uint32_t ulFinal_AVS = 0;

driverInfoModeStatus_t ModeStatus;

int8_t ucinitialFuelPercentage = 0;
int8_t ucfinalFuelPercentage = 0;
int16_t usdeltaFuelInPercentage = 0;
uint32_t ulAfeinKmperLitre = 0;

extern uint32_t ulOdoInKm;

void vDriver_InfoTask(void)
{
    uint8_t ucignitionstatus = 0;
    ucignitionstatus = usIgnitionGetCurrentState();
    if(ucignitionstatus == IgnOFF_mode)
    {
       // printf("Ignition is OFF\r\n");
        //ucDeltaTime = 0;
        //usDistance2 = 0;
        //ulDistance2 = 0;
        //ulDistance1 = 0;
    }
    else
    {
    	vCalculateAVS();
    	vCalculateAFE();
    	vCalculateRange();
    }

}

#define MA_AVS_DATA_BUFFER_SIZE 10
uint32_t l_AVS_DataBuffer_1_u16A[MA_AVS_DATA_BUFFER_SIZE];
#define MA_AVS_WINDOW_SIZE 6

#define MA_Odo_DATA_BUFFER_SIZE 10
uint32_t l_Odo_DataBuffer_1_u16A[MA_Odo_DATA_BUFFER_SIZE];
#define MA_Odo_WINDOW_SIZE 6

#define MA_Fuel_DATA_BUFFER_SIZE 10
uint32_t l_Fuel_DataBuffer_1_u16A[MA_Fuel_DATA_BUFFER_SIZE];
#define MA_Fuel_WINDOW_SIZE 6


void AVSreset_IO_LM_BV_FA_data(void)	//IGNON lower Mean Battery Voltage
{
	// Reset the data buffer to all zeros
	memset(l_AVS_DataBuffer_1_u16A, 0, sizeof(l_AVS_DataBuffer_1_u16A));
	// Set the configuration for the IOBV_MA calculation
	l_AVS_MA_t.dataInp_ptr = l_AVS_DataBuffer_1_u16A;
	l_AVS_MA_t.raw_data_size= MA_AVS_DATA_BUFFER_SIZE;
	l_AVS_MA_t.min_raw_data_counter = 0;
	l_AVS_MA_t.raw_ip_index = 0;
	l_AVS_MA_t.window_index =0;
	l_AVS_MA_t.window_size = MA_AVS_WINDOW_SIZE;
}

void Odoreset_IO_LM_BV_FA_data(void)	//IGNON lower Mean Battery Voltage
{
	// Reset the data buffer to all zeros
	memset(l_Odo_DataBuffer_1_u16A, 0, sizeof(l_Odo_DataBuffer_1_u16A));
	// Set the configuration for the IOBV_MA calculation
	l_Odo_MA_t.dataInp_ptr = l_Odo_DataBuffer_1_u16A;
	l_Odo_MA_t.raw_data_size= MA_Odo_DATA_BUFFER_SIZE;
	l_Odo_MA_t.min_raw_data_counter = 0;
	l_Odo_MA_t.raw_ip_index = 0;
	l_Odo_MA_t.window_index =0;
	l_Odo_MA_t.window_size = MA_Odo_WINDOW_SIZE;
}

void Fuelreset_IO_LM_BV_FA_data(void)	//IGNON lower Mean Battery Voltage
{
	// Reset the data buffer to all zeros
	memset(l_Fuel_DataBuffer_1_u16A, 0, sizeof(l_Fuel_DataBuffer_1_u16A));
	// Set the configuration for the IOBV_MA calculation
	l_Fuel_MA_t.dataInp_ptr = l_Fuel_DataBuffer_1_u16A;
	l_Fuel_MA_t.raw_data_size= MA_Fuel_DATA_BUFFER_SIZE;
	l_Fuel_MA_t.min_raw_data_counter = 0;
	l_Fuel_MA_t.raw_ip_index = 0;
	l_Fuel_MA_t.window_index =0;
	l_Fuel_MA_t.window_size = MA_Fuel_WINDOW_SIZE;
}

/**
 * @brief AverageVehicleSpeed Calculation
 *
 * This API is designed to calculate the Average Vehicle Speed (AVS) in kilometers per hour and Miles per hour using odometer readings
   and a fixed time interval.
 * The calculated speed is averaged over a set number of samples and then displayed.
 * @param None
 *
 * @return Void.
 */




void vCalculateAVS(void)
{
	static uint32_t ulSpeedValue = 0;
	static uint32_t ulSpeedMovAvg = 0;
	DriverInfo_Units_t SpeedUnits = 0;

	SpeedUnits = xGetToggleMetrics();
	ulSpeedValue = GetSpeedValueInKM();
	ulSpeedMovAvg = calculateMovingAverage(ulSpeedValue,&l_AVS_MA_t);


	if(SpeedUnits == UNITS_IN_KM)
	{
		ulFinal_AVS = ulSpeedMovAvg;
		//printf("AVS1:%d",ulFinal_AVS);
	}
	else
	{
		ulFinal_AVS = (ulSpeedMovAvg * KM_TO_MILES_CONVERSION_MULTIPLICATION_FACTOR)/ KM_TO_MILES_CONVERSION_DIVISION_FACTOR ;
		//printf("AVS2:%d",ulFinal_AVS);
	}

	ModeStatus.AverageVehicleSpeed = ulFinal_AVS;
//	printf("AVS:%d",ModeStatus.AverageVehicleSpeed);
}


/*This API is used for simulation (Testing Purpose)*/

#if(FUEL_TEST_MACRO == 0)
uint8_t prvFuelSimulation(void)
{
	static uint8_t ucsimulatedFuel = 100;

	if(ucsimulatedFuel <= 0)
		ucsimulatedFuel = 100;

	ucsimulatedFuel = ucsimulatedFuel-20;
	//printf("S:%ld\r\n",ucfinalFuelPercentage);
	return ucsimulatedFuel;
}
#endif

/*  This API is designed to calculate the fuel level in liters by converting percentage values.  */

int16_t prvconvert_FuelPercentageToLitres(int8_t ucfuelPercentage)
{
	int16_t usfuelInLitres = 0;

    /*In the below expression 10 is multiplied intentionally in the numerator for calculating fuel in milliliters*/
	usfuelInLitres = (FUEL_TANK_CAPACITY * ucfuelPercentage * 10) / 100;

    return usfuelInLitres;
}


/**
 * @brief Calculate Average Fuel Economy in Kilometers per Litre and Miles per Litre
 *
 * This function calculates the Average Fuel Economy (AFE) in kilometers per litre and Miles per Litre.
 * It uses odometer readings and fuel level readings to compute the distance traveled and the fuel consumed, respectively.
 * The AFE is calculated as the ratio of the moving average of the distance traveled to the moving average of the fuel consumed.
 *
 * @param None
 *
 * @return uint32_t - The calculated AFE in kilometers per litre.
 */


void vCalculateAFE(void)
{
    static uint32_t ulinitialDistanceinKm = 0;
    static uint32_t ulfinalDistanceinKm = 0;
    static uint32_t ulDeltaDistanceinKm = 0;
    static uint16_t usdeltaFuelInLitres = 0;
    static uint32_t ulAfe = 0;
    static uint32_t ulpreviousAFEinKmperLitre = 0;
    static uint16_t usAverageFuel = 0;

	static uint32_t ulAverageDitsance = 0;
	DriverInfo_Units_t OdoUnits = 0;

	ulfinalDistanceinKm = ulOdoInKm;
	ulDeltaDistanceinKm = ulfinalDistanceinKm - ulinitialDistanceinKm;
//	printf("DD:%ld\r\n",ulDeltaDistanceinKm);


#if(FUEL_TEST_MACRO == 1)
	ucfinalFuelPercentage = xGetFuelLevel();
#endif

#if(FUEL_TEST_MACRO == 0)
	ucfinalFuelPercentage = prvFuelSimulation();
	//printf("A:%ld\r\n",ucfinalFuelPercentage);
#endif


	if((ulDeltaDistanceinKm == 0) && (ulpreviousAFEinKmperLitre == 0))
	{
		ulinitialDistanceinKm = ulfinalDistanceinKm;
		ucinitialFuelPercentage = ucfinalFuelPercentage;
		ulAfeinKmperLitre = DEFAULT_AFE;
//		printf("afe1:%ld\r\n",ulAfeinKmperLitre);
	}
	else if((ulDeltaDistanceinKm == 0) && (ulpreviousAFEinKmperLitre != 0))
	{
		ulinitialDistanceinKm = ulfinalDistanceinKm;
		ucinitialFuelPercentage = ucfinalFuelPercentage;
		ulAfeinKmperLitre = ulpreviousAFEinKmperLitre;
//		printf("afe2:%ld\r\n",ulAfeinKmperLitre);
	}

	else if(( ulDeltaDistanceinKm == ulfinalDistanceinKm ) && (ulpreviousAFEinKmperLitre == 0))
	{
		ulinitialDistanceinKm = ulfinalDistanceinKm;
		ucinitialFuelPercentage = ucfinalFuelPercentage;
		ulAfeinKmperLitre = DEFAULT_AFE;
//		printf("afe3:%ld\r\n",ulAfeinKmperLitre);
	}
	else if(ulinitialDistanceinKm > ulfinalDistanceinKm)
	{
		ulinitialDistanceinKm = ulfinalDistanceinKm;
		ucinitialFuelPercentage = ucfinalFuelPercentage;
		ulAfeinKmperLitre = ulpreviousAFEinKmperLitre;
//		printf("afe4:%ld\r\n",ulAfeinKmperLitre);
	}
	else if(( ulDeltaDistanceinKm != 0 ) && (ulpreviousAFEinKmperLitre != 0))
	{
		ulAverageDitsance = calculateMovingAverage(ulDeltaDistanceinKm,&l_Odo_MA_t);
		usdeltaFuelInPercentage = ucinitialFuelPercentage - ucfinalFuelPercentage;
//		printf("DF_Pmmmmmmmmmmmmmmmmmm:%ld\r\n",usdeltaFuelInPercentage);

		if(usdeltaFuelInPercentage <= 0)
		{
			ulinitialDistanceinKm = ulfinalDistanceinKm;
			ucinitialFuelPercentage = ucfinalFuelPercentage;
			printf("I_Per:%d\t",ucinitialFuelPercentage);
			ulAfeinKmperLitre  = ulpreviousAFEinKmperLitre;
		}
		else
		{
			usdeltaFuelInLitres = (uint16_t)(prvconvert_FuelPercentageToLitres(usdeltaFuelInPercentage));
			usAverageFuel = calculateMovingAverage(usdeltaFuelInLitres,&l_Fuel_MA_t);
//			printf("Fuel_MAmmmmmmmmmmmmmmmmmmmm:%u\t", usAverageFuel);

			if (usAverageFuel == 0)
			{
				// Handle the division by zero case
				ulAfeinKmperLitre = DEFAULT_AFE;
//				printf("afe5:%ld\r\n",ulAfeinKmperLitre);
			}
			else
			{
				ulAfeinKmperLitre = (ulAverageDitsance * 10) /(uint32_t)(usAverageFuel);
//				printf("AFE_C:%ld\n\r", ulAfeinKmperLitre);
				ulinitialDistanceinKm = ulfinalDistanceinKm;
				ucinitialFuelPercentage = ucfinalFuelPercentage;
			}
		}
	}
	OdoUnits = xGetToggleMetrics();
	if(OdoUnits == UNITS_IN_KM)
	{
		ulAfe = ulAfeinKmperLitre;
//		printf("Afekm:%ld",ulAfe);

	}
	else
	{
		ulAfe = (ulAfeinKmperLitre * KMTOLITRE_TO_MILESPERGALLON_MULTIPLICATION_FACTOR * 10) / KMTOLITRE_TO_MILESPERGALLON_DIVISION_FACTOR ;
		//printf("AfeM:%ld",ulAfe);

	}
	ulpreviousAFEinKmperLitre = ulAfeinKmperLitre;
//    ModeStatus.AverageFuelEconomy = ulAfe;

   // return ulAfe;
}

/**
* @brief Calculate and display the Distance to Empty (DTE) value in Kilometers and Miles
*
* This function calculates the Distance to Empty (DTE) based on the current fuel level and average fuel economy.
* It uses the odometer readings and a simulated fuel level for testing purposes to determine the actual and displayed DTE values.
* The function ensures the displayed DTE is within acceptable thresholds and updates the ModeStatus with the calculated DTE value.
*
* @param None
*
* @return Void.
*/

void vCalculateRange(void)
{
	static uint16_t usfuelRemainingInLitres = 0;
	static uint16_t usCalculated_DTEinKm = 0;
	static uint16_t uspresent_DTEinKm = 0;
	static uint16_t uspresent_DTE = 0 ;
	static uint16_t usprevious_DTEinKm = 0;
	static uint16_t usDelta_DTEinKm = 0;
	static uint8_t uccount1 = 0;
	static int8_t ucfuelremaingvalueinPercentage = 0;
	DriverInfo_Units_t AfeUnits = 0;

	uccount1++;
	ucfuelremaingvalueinPercentage = ucinitialFuelPercentage;
	if(ucfuelremaingvalueinPercentage == 0)
	{
		uspresent_DTEinKm = 0;
	}
	else
	{
		usfuelRemainingInLitres = (uint16_t)prvconvert_FuelPercentageToLitres(ucfuelremaingvalueinPercentage);

		//printf("Fuel: %d\n\r", usfuelRemainingInLitres);
		if(uccount1 == 1)
		{
			//printf("inside_If\r\n");
			usfuelRemainingInLitres = FINAL_FUEL_LEVEL;
			usCalculated_DTEinKm = (uint16_t)(FINAL_FUEL_LEVEL * DEFAULT_AFE );
			//printf("C_DTE:%d\t",usCalculated_DTEinKm);
			uspresent_DTEinKm= usCalculated_DTEinKm;
			//printf("PIN_DTE:%d\t",uspresent_DTEinKm);
		}
		else
		{
			usCalculated_DTEinKm = (usfuelRemainingInLitres * ulAfeinKmperLitre) / 10;
		 	uspresent_DTEinKm = usCalculated_DTEinKm;
			//printf("POUT_DTE:%d\t",uspresent_DTEinKm);
			/*Here, if DTE = 28 then it's actual value is 2.8*/
		}


		if(uspresent_DTEinKm <= usprevious_DTEinKm)
		{
			usDelta_DTEinKm = usprevious_DTEinKm - uspresent_DTEinKm;
		}
		else
		{
			usDelta_DTEinKm = uspresent_DTEinKm - usprevious_DTEinKm;
		}

		if(uspresent_DTEinKm >= MAX_THRESHOLD_DTE)
		{
			uspresent_DTEinKm = MAX_THRESHOLD_DTE;
			//printf("P_DTE:%d\t",uspresent_DTEinKm);
//			ModeStatus.Range = uspresent_DTEinKm;
			//return uspresent_DTEinKm;
		}
		else
		{
			if(usDelta_DTEinKm < MIN_DISPLAYED_DTE)
			{
				uspresent_DTEinKm = usprevious_DTEinKm - 1;
			}
			else if (usDelta_DTEinKm > MAX_DISPLAYED_DTE)
			{
				uspresent_DTEinKm = usCalculated_DTEinKm;
			}
			else if (usDelta_DTEinKm >= MIN_DISPLAYED_DTE && usDelta_DTEinKm <= MAX_DISPLAYED_DTE)
			{
				uspresent_DTEinKm = usprevious_DTEinKm - 2;
			}
			else
			{
			}
		}
	}
	AfeUnits = xGetToggleMetrics();
	if(AfeUnits == UNITS_IN_KM)
	{
		uspresent_DTE = uspresent_DTEinKm;

	}
	else
	{
		uspresent_DTE = (uspresent_DTEinKm * KMTOLITRE_TO_MILESPERGALLON_MULTIPLICATION_FACTOR ) / KMTOLITRE_TO_MILESPERGALLON_DIVISION_FACTOR;

	}
	ModeStatus.Range = uspresent_DTE;
	usprevious_DTEinKm = uspresent_DTEinKm;
	//printf("DTE:%d\r\n",uspresent_DTEinKm);
	//printf("DTE1:%d\n\r",ModeStatus.Range);
    //return uspresent_DTEinKm;
}


uint16_t DisplayDTE(bool flag,uint16_t uspresent_DTE )
{
	static uint16_t Error_Value = 0;
	Error_Value = 9999;
	if(flag)
	{
#if(DRIVERINFO_TEST_MACRO == 1)
		printf("---\n");
		printf("E_V:%hu\n\r",Error_Value);
#endif
		return Error_Value;

	}
	else
	{
#if(DRIVERINFO_TEST_MACRO == 1)
		printf("DTE1: %u\n",usdisplayed_DTE);
		printf("E_V:%ld\n\r",uspresent_DTE);
#endif
		return ModeStatus.Range;
		//return uspresent_DTE;
	}
}


uint32_t xGetAVSstatus(void)
{
	//printf("AVS:%ld\n",ModeStatus.AverageVehicleSpeed);
	return ModeStatus.AverageVehicleSpeed;

//	return ulFinal_AVS;
}



uint32_t xGetAFEstatus(void)
{
	//printf("AFE:%ld\n",ModeStatus.AverageFuelEconomy);
	return ModeStatus.AverageFuelEconomy;
	//return ulAfe;
}


uint16_t xGetRANGEstatus(void)
{
	uint16_t RangeValue = 0;
	uint16_t FinalRange = 0;
	if((ModeStatus.Range < BLINK_THRESHOLD_LOW) || (ModeStatus.Range > MAX_THRESHOLD_DTE))
		{
			//DisplayDTE(true,ModeStatus.Range);
			//ModeStatus.Range =1;
			RangeValue = DisplayDTE(true,ModeStatus.Range);
		}
		else
		{
			RangeValue = DisplayDTE(false,ModeStatus.Range);
		}

		//uint16_t FinalDte = (uint16_t)ModeStatus.Range;
		FinalRange = RangeValue;
		//printf("Range:%ld\n",FinalRange);

		return FinalRange;
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
