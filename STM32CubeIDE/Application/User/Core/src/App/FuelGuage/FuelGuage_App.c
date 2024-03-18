    /******************************************************************************************
 * Feature Name: FuelGuage.c
 *
 * Feature Short Name: FuelGuage
 *
 * Description: FuelGuage.c file performs to find the current FuelLevel and update the last display Fuel level.
 *
 * Author: Saikumar kurella.
 *
 * Create Date: 22-Feb-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 *****************************************************************************************/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

//#include "../include/musl/bits/alltypes.h"
//#include "../src/third_party/rtos/FreeRTOS/Source/portable/GCC/ARM_CM0/portmacro.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

#include "FuelGuage_App.h"
#include "FuelGuage_App_cfg.h"
#include "damp_out.h"
#include "IGN_SmHandler.h"
#include "stm32h7xx_hal.h"


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
//#define TIMER_ID_POWERON_START 5000

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
Main_DATA MainData;
Sub_DATA SubData;

uint32_t FuelLevel;
uint32_t Dampout_value;
uint16_t Last_Displayed_Level;
uint16_t Current_FuelLevel;
uint16_t sensorValue;
FillType_State_T FillType;

uint16_t adcValues[WINDOW_SIZE];
uint8_t currentIndex = 0;
uint16_t sampleCount = 0;
uint16_t totalSum = 0;

uint8_t Initial_samplingOver_Flag=0;
uint8_t FillType_DetctOver_Flag=0;

bool IGN;

FillType_State_T Previous_FillType;
FillType_State_T Current_FillType;

extern uint16_t ADC_Value;
extern uint16_t l_count_u16[1];
extern Input_Thresholds_T inp_thresholds[1];


/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * Purpose: A flag to that is used to mark if a request to change
 * availability has been received or not
 *
 * Unit: Boolean
 *
 * Resolution: 1 Bit
 *
 * Range: TRUE/FALSE
 *
 * Power On Init Value\Action: FALSE
 *
 * Wakeup Value\Action: FALSE
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
//static bool l_schedule_change_availability_bool;

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
uint16_t prvInital_SamplingProcess(void);
FillType_State_T prvOffline_FillTypeDtcn_Prcs(void);
FillType_State_T prvOnline_FillTypeDtcn_Prcs(void);
void prvSet_FuelLevel(void);
uint16_t calculateAverage(void);
/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**************************************************************************************************
 * Function Name: vFuelGuage_TaskInit
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to Initialize.
 *
 ***************************************************************************************************/
void vFuelGuage_TaskInit(void)
{
    MainData.Main_state = INIT_Sampling_State;
    
}

/**************************************************************************************************vFuelGuage_Task
 *
 * Function Name: 
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to update the fuelLevel
 *
 ***************************************************************************************************/
void vFuelGuage_Task(void)
{
    //printf("S1\r\n");
    
    switch(MainData.Main_state)
    {
        
        case INIT_Sampling_State:
        {
            Current_FuelLevel = prvInital_SamplingProcess();
            printf("CFL-%d\r\n",Current_FuelLevel);
            printf("IGN_OFF\n");
            if(sampleCount >= WINDOW_SIZE)
            {
                if ((usIgnitionGetCurrentState() == IgnON_mode) && (Initial_samplingOver_Flag==1))
                {
                    MainData.Main_state = Offline_FillType_Dtcn_State;
                }
            }
            break;
        }
        case Offline_FillType_Dtcn_State:
        {
            FillType = prvOffline_FillTypeDtcn_Prcs();
            printf("FT-%d\r\n",FillType);
            printf("IGN_ON\n");
            if((usIgnitionGetCurrentState() == IgnON_mode) && (FillType_DetctOver_Flag==1))
            {
                 if((FillType == Normal_fill) || (FillType == Slow_fill))
                {
                    MainData.Main_state = Online_Process_State;
                    SubData.Sub_state = FillType;
                }
                else /*Instantaneous_Update*/ 
                {
                    /*Instantaneous update code*/
                    inp_thresholds[FuelIndex].Min_time = Instantaneous_Filter_UpdateRate;
                    inp_thresholds[FuelIndex].Max_Step_Size = Instantaneous_Filter_StepSize;
                    printf("IUCnt %d \t", inp_thresholds[0].Min_time );
                    printf("IUSiz %d \t",inp_thresholds[0].Max_Step_Size);
                    DAMP_OUT ();
                    Dampout_value = Get_DAMP_OUT(0);
                    prvSet_FuelLevel();
                    MainData.Main_state = Online_Process_State;
                    SubData.Sub_state = Invalid;
                }
            }
            break;
        }
        case Online_Process_State:
        {
        	printf("IGN_ON: \r\n");
        	printf("Ignition_ON\n");
            switch(SubData.Sub_state)
            {
                case Fast_fill:
                {
                    /*Fast Fill code*/
                    if(Previous_FillType != Current_FillType)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    inp_thresholds[FuelIndex].Min_time = Fuel_Fast_Fill_Loss_Filter_UpdateRate;
                    inp_thresholds[FuelIndex].Max_Step_Size = Fuel_Fast_Fill_Loss_Filter_StepSize;
                    printf("FFCnt %d\t", inp_thresholds[0].Min_time );
                    printf("FFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                    DAMP_OUT ();
                    Dampout_value = Get_DAMP_OUT(0);
                    prvSet_FuelLevel();
                            
                    break;
                }
                case Slow_fill:
                {
                    /*Slow Fill code*/
                    if(Previous_FillType != Current_FillType)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    inp_thresholds[FuelIndex].Min_time = (uint16_t)Fuel_slow_Fill_Loss_Filter_UpdateRate;
                    inp_thresholds[FuelIndex].Max_Step_Size = (uint16_t) Fuel_slow_Fill_Loss_Filter_StepSize;
                    printf("SFCnt %d\t", inp_thresholds[0].Min_time );
                    printf("SFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                    DAMP_OUT ();
                    Dampout_value = Get_DAMP_OUT(0);
                    prvSet_FuelLevel();

                            
                    break;
                }
                case Normal_fill:
                {
                    /*Normal Fill code*/
                    if(Previous_FillType != Current_FillType)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    inp_thresholds[FuelIndex].Min_time = (uint16_t)Fuel_Normal_Fill_Loss_Filter_UpdateRate;
                    inp_thresholds[FuelIndex].Max_Step_Size =  (uint16_t)Fuel_Normal_Fill_Loss_Filter_StepSize;
                    printf("NFCnt %d\t", inp_thresholds[0].Min_time );
                    printf("NFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                    DAMP_OUT ();
                    Dampout_value = Get_DAMP_OUT(0);
                    prvSet_FuelLevel();      
                    break;
                }
                default:
                {
                    break;
                } 
            }
            Previous_FillType=Current_FillType;
            FillType = prvOnline_FillTypeDtcn_Prcs(); 
            Current_FillType = FillType;
            printf("FT-%d\r\n",FillType);
            if(FillType == Slow_fill)
            {
                SubData.Sub_state = Slow_fill;
            }
            else if(FillType == Normal_fill)
            {
                SubData.Sub_state = Normal_fill;
            }
            else
            {
                SubData.Sub_state = Fast_fill;
            }
            
            if(usIgnitionGetCurrentState() == IgnOFF_mode)
            {
                MainData.Main_state = INIT_Sampling_State;
            }
            break;
        }
        default:
        {
            break;
        }   
    } 
}

/**************************************************************************************************
 * Function Name: prvInital_SamplingProcess
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to calculate the 3sec continuous moving average value.
 *
 ***************************************************************************************************/


uint16_t prvInital_SamplingProcess(void)
{
    uint16_t res=0;
    
    sensorValue = ADC_Value;/*adc*/;
    // Store the value in the circular buffer
    adcValues[currentIndex] = sensorValue;

    // Move to the next index in the circular buffer
    currentIndex = (currentIndex + 1) % WINDOW_SIZE;

    // Accumulate the ADC values
    totalSum += sensorValue;
    sampleCount++;

    // If we have accumulated enough samples, calculate the average
    if (sampleCount >= WINDOW_SIZE) 
    {
        res = calculateAverage();
        Initial_samplingOver_Flag=1;

        // Subtract the oldest sample from the total sum
        totalSum -= adcValues[currentIndex];
    
    }
    return res;
    
}

/**************************************************************************************************
 * Function Name: prvOffline_FillTypeDtcn_Prcs.
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to detect the fillType(slow_fill,Normal_fill,Instantaneous_update)in offline.
 *
 ***************************************************************************************************/
FillType_State_T prvOffline_FillTypeDtcn_Prcs(void)
{
    uint16_t delta;
    FillType_State_T res;
    
    Last_Displayed_Level = (uint16_t)Dampout_value;
    if(Current_FuelLevel > Last_Displayed_Level )
    {
        delta = Current_FuelLevel - Last_Displayed_Level;
    }
    else
    {
        delta = Last_Displayed_Level - Current_FuelLevel; 
    }
    FillType_DetctOver_Flag=1;
    
    if(delta >= FastFillRange)
    {
        res = Instantaneous_Update;
    }
    else if((delta >= SlowFillRange) && (delta < FastFillRange))
    {
        res = Slow_fill;
    }
    else
    {
        res = Normal_fill;
    }
    return res;
}

/**************************************************************************************************
 * Function Name:  prvOnline_FillTypeDtcn_Prcs
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to detect the fillType(slow_fill,Normal_fill, Fast_fill)in online.
 *
 ***************************************************************************************************/
FillType_State_T prvOnline_FillTypeDtcn_Prcs(void)
{
    uint16_t delta;
    FillType_State_T res;
    
    Current_FuelLevel = ADC_Value;/*ADC*/
    printf("CFL-%d\r\n",Current_FuelLevel);
    Last_Displayed_Level = (uint16_t)Dampout_value;
    if(Current_FuelLevel > Last_Displayed_Level)
    {  
        delta = Current_FuelLevel - Last_Displayed_Level; 
    }
    else
    {
        delta = Last_Displayed_Level - Current_FuelLevel;
    }
    
    if(delta >= FastFillRange)
    {
        res = Fast_fill;
    }
    else if((delta >= SlowFillRange) && (delta< FastFillRange))
    {
        res = Slow_fill;
    }
    else
    {
        res = Normal_fill;
    }
    
    return res;
    
}

/**************************************************************************************************
 * Function Name:  prvSet_FuelLevel
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to set the fuel level in percentage.
 *
 ***************************************************************************************************/
void prvSet_FuelLevel(void)
{
    FuelLevel = (Dampout_value * 100)/(Maximum_ADC_Range);
    printf("DO: %lu \t FL:%lu\r\n",Dampout_value, FuelLevel);
}

/**************************************************************************************************
 * Function Name: xGet_FuelLevel
 *
 * output Parameters: ucFuelWarning_Indictr, Warning_status
 *
 * Return Value: 
 *
 * Description: This function is desined to get the Updated FuelLevel and providing the status of Fuelbar and Fuel Icon
 *
 ***************************************************************************************************/
uint8_t xGet_FuelLevel(IndicationStatus_t* ucFuelWarning_Indictr, bool* Warning_status)
{
   uint8_t p_FuelLevel_Res = 0 ;
   *Warning_status=false;
   
   p_FuelLevel_Res = (uint8_t)FuelLevel;
   if(p_FuelLevel_Res <= WARNING_FUELLEVEL)
    {
       *Warning_status=true;
       ucFuelWarning_Indictr->indicators.Fuel_warning_indicator=1;   
    }
    
	return p_FuelLevel_Res;
}

/**************************************************************************************************
 * Function Name: calculateAverage
 *
 * Input Parameter: void
 *
 * Return Value: return the average value.
 *
 * Description: This function is desined to get the average value of ADC raw inputs for 3 sec time period.
 *
 ***************************************************************************************************/
uint16_t calculateAverage(void)
{
    uint16_t average;
    average = totalSum / WINDOW_SIZE;
    
    return average;

}



