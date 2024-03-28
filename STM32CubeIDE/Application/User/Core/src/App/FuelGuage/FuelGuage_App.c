    /******************************************************************************************
 * Feature Name: FuelGuage.c
 *
 * Feature Short Name: FuelGuage
 *
 * Description: FuelGuage.c file performs to find the current
 and update the last display Fuel level.
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

extern uint16_t gl_ADC_Value_u16;
uint16_t gl_Current_FuelLevel_u16;


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

static uint32_t l_FuelLevel_InPercentage_u32;
static uint32_t l_Dampout_value_u32;

static uint16_t l_adcValues_u16A[WINDOW_SIZE];
static uint8_t l_currentIndex_u8 = 0;
static uint16_t l_SampleCount_u16 = 0;
static uint16_t l_TotalSum_u16 = 0;

static uint8_t l_Initial_samplingOver_Flag_u8=0;
static uint8_t l_FillType_DetctOver_Flag_u8=0;
static FillType_State_T l_FillType_t;
static FillType_State_T l_Previous_FillType_t;
static FillType_State_T l_Current_FillType_t;

static uint16_t l_FastFillCount_16;
static uint16_t l_SlowFillCount_u16;
static uint16_t l_NormalFillCount_u16;


extern uint16_t l_count_u16[1];
extern Input_Thresholds_T inp_thresholds[1];

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
static uint16_t prvInital_SamplingProcess(void);
static FillType_State_T prvOffline_FillTypeDtcn_Prcs(void);
static FillType_State_T prvOnline_FillTypeDtcn_Prcs(void);
static void prvSet_FuelLevel(void);
static uint16_t calculateAverage(void);
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

    
    switch(MainData.Main_state)
    {
        
        case INIT_Sampling_State:
        {
            gl_Current_FuelLevel_u16 = prvInital_SamplingProcess();
            printf("CFL-%d\r\n",gl_Current_FuelLevel_u16);
            printf("IGN_OFF\n");
            if(l_SampleCount_u16 >= WINDOW_SIZE)
            {
                if ((usIgnitionGetCurrentState() == IgnON_mode) && (l_Initial_samplingOver_Flag_u8==1))
                {
                	l_SampleCount_u16=0;
                    MainData.Main_state = Offline_FillType_Dtcn_State;
                }
            }
            break;
        }
        case Offline_FillType_Dtcn_State:
        {
            l_FillType_t = prvOffline_FillTypeDtcn_Prcs();
            l_Current_FillType_t = l_FillType_t;
            printf("FT-%d\r\n",l_FillType_t);
            printf("IGN_ON\n");
            if((usIgnitionGetCurrentState() == IgnON_mode) && (l_FillType_DetctOver_Flag_u8==1))
            {
                 if((l_FillType_t == Normal_fill) || (l_FillType_t == Slow_fill))
                {
                    MainData.Main_state = Online_Process_State;
                    SubData.Sub_state = l_FillType_t;
                }
                else /*Instantaneous_Update*/ 
                {
                    /*Instantaneous update code*/
                    inp_thresholds[0].Min_time = INSTANTANEOUS_FILTER_UPDATERATE;
                    inp_thresholds[0].Max_Step_Size = INSTANTANEOUS_FILTER_STEPSIZE;
                    printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                    printf("IUCnt %d\t", inp_thresholds[0].Min_time );
                    printf("IUSiz %d\t",inp_thresholds[0].Max_Step_Size);
                    DAMP_OUT ();
                    l_Dampout_value_u32 = Get_DAMP_OUT(0);
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
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    while(l_FastFillCount_16 <= FASTFILL_TIMEOUT_MS)
                    {
                        if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                            l_FastFillCount_16=0;
                            break;
                        }
                        else
                        {
                            l_FastFillCount_16++;
                            /*Fast Fill code*/
                            inp_thresholds[0].Min_time = FAST_FILL_LOSS_FILTER_UPDATERATE;
                            inp_thresholds[0].Max_Step_Size = FAST_FILL_LOSS_FILTER_STEPSIZE;
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("FFCnt %d\t", inp_thresholds[0].Min_time );
                            printf("FFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                            DAMP_OUT ();
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            prvSet_FuelLevel();
                        }
                    }      
                    break;
                }
                case Slow_fill:
                {
                    /*Slow Fill code*/
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    while(l_SlowFillCount_u16 <= SLOWFILL_TIMEOUT_MS)
                    {
                         if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                            l_SlowFillCount_u16=0;
                            break;
                        }
                        else
                        {
                            l_SlowFillCount_u16++;
                            /*Slow Fill code*/
                            inp_thresholds[0].Min_time = SLOW_FILL_LOSS_FILTER_UPDATERATE;
                            inp_thresholds[0].Max_Step_Size = SLOW_FILL_LOSS_FILTER_STEPSIZE;
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("SFCnt %d\t", inp_thresholds[0].Min_time );
                            printf("SFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                            DAMP_OUT ();
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            prvSet_FuelLevel();    
                        }   
                    }
                    break;
                }
                case Normal_fill:
                {
                    /*Normal Fill code*/
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                        l_count_u16[FuelIndex]= 0;
                    }
                    while(l_NormalFillCount_u16 <= NORMALFILL_TIMEOUT_MS)
                    {
                        if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                            l_NormalFillCount_u16=0;
                            break;
                        }
                        else
                        {
                            l_NormalFillCount_u16++;
                            /*Normal Fill code*/
                            inp_thresholds[0].Min_time = NORMAL_FILL_LOSS_FILTER_UPDATERATE;
                            inp_thresholds[0].Max_Step_Size = NORMAL_FILL_LOSS_FILTER_STEPSIZE;
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("NFCnt %d\t", inp_thresholds[0].Min_time );
                            printf("NFSiz %d\t",inp_thresholds[0].Max_Step_Size);
                            DAMP_OUT ();
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            prvSet_FuelLevel();
                        }
                             
                    }     
                    break;
                }
                default:
                {
                    break;
                } 
            }
            l_Previous_FillType_t=l_Current_FillType_t;
            l_FillType_t = prvOnline_FillTypeDtcn_Prcs();
            l_Current_FillType_t = l_FillType_t;
            printf("FT-%d\r\n",l_FillType_t);
            if(l_FillType_t == Fast_fill)
            {
                SubData.Sub_state = Fast_fill;
            }
            else if(l_FillType_t == Slow_fill)
            {
                SubData.Sub_state = Slow_fill;
            }
            else
            {
                SubData.Sub_state = Normal_fill;
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


static uint16_t prvInital_SamplingProcess(void)
{
    uint16_t l_res_t=0;
    uint16_t fl_sensorValue_u16;
    
    fl_sensorValue_u16 = gl_ADC_Value_u16;/*adc*/;
    // Store the value in the circular buffer
    l_adcValues_u16A[l_currentIndex_u8] = fl_sensorValue_u16;

    // Move to the next index in the circular buffer
    l_currentIndex_u8 = (l_currentIndex_u8 + 1) % WINDOW_SIZE;

    // Accumulate the ADC values
    l_TotalSum_u16 += fl_sensorValue_u16;
    l_SampleCount_u16++;

    // If we have accumulated enough samples, calculate the average
    if (l_SampleCount_u16 >= WINDOW_SIZE)
    {
        l_res_t = calculateAverage();
        l_Initial_samplingOver_Flag_u8=1;

        // Subtract the oldest sample from the total sum
        l_TotalSum_u16 -= l_adcValues_u16A[l_currentIndex_u8];
    
    }
    return l_res_t;
    
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
static FillType_State_T prvOffline_FillTypeDtcn_Prcs(void)
{
    uint16_t fl_delta_u16;
    FillType_State_T l_res_t;
    uint16_t fl_Last_Displayed_Level_u16;
    
    fl_Last_Displayed_Level_u16 = (uint16_t)l_Dampout_value_u32;
    if(gl_Current_FuelLevel_u16 > fl_Last_Displayed_Level_u16 )
    {
        fl_delta_u16 = gl_Current_FuelLevel_u16 - fl_Last_Displayed_Level_u16;
    }
    else
    {
        fl_delta_u16 = fl_Last_Displayed_Level_u16 - gl_Current_FuelLevel_u16;
    }
    l_FillType_DetctOver_Flag_u8=1;
    
    if(fl_delta_u16 >= FAST_FILL_RANGE)
    {
        l_res_t = Instantaneous_Update;
    }
    else if((fl_delta_u16 >= SLOW_FILL_RANGE) && (fl_delta_u16 < FAST_FILL_RANGE))
    {
        l_res_t = Slow_fill;
    }
    else
    {
        l_res_t = Normal_fill;
    }
    return l_res_t;
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
static FillType_State_T prvOnline_FillTypeDtcn_Prcs(void)
{
    uint16_t fl_delta_u16;
    FillType_State_T l_res_t;
    uint16_t fl_Last_Displayed_Level_u16;
    
    gl_Current_FuelLevel_u16 = gl_ADC_Value_u16;/*ADC*/
    printf("CFL-%d\r\n",gl_Current_FuelLevel_u16);
    fl_Last_Displayed_Level_u16 = (uint16_t)l_Dampout_value_u32;
    if(gl_Current_FuelLevel_u16 > fl_Last_Displayed_Level_u16)
    {  
        fl_delta_u16 = gl_Current_FuelLevel_u16 - fl_Last_Displayed_Level_u16;
    }
    else
    {
        fl_delta_u16 = fl_Last_Displayed_Level_u16 - gl_Current_FuelLevel_u16;
    }
    
    if(fl_delta_u16 >= FAST_FILL_RANGE)
    {
        l_res_t = Fast_fill;
    }
    else if((fl_delta_u16 >= SLOW_FILL_RANGE) && (fl_delta_u16< FAST_FILL_RANGE))
    {
        l_res_t = Slow_fill;
    }
    else
    {
        l_res_t = Normal_fill;
    }
    
    return l_res_t;
    
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
static void prvSet_FuelLevel(void)
{
    l_FuelLevel_InPercentage_u32 = (l_Dampout_value_u32 * 100)/(MAXIMUM_ADC_RANGE);
    printf("DO: %lu\tFL:%lu\r\n",l_Dampout_value_u32, l_FuelLevel_InPercentage_u32);
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
uint8_t xGet_FuelLevel(IndicationStatus_t* pucFuelWarning_Indictr_u16p, bool* p_Warning_status_bool)
{
   uint8_t fl_FuelLevel_Res_u8 = 0 ;
   *p_Warning_status_bool=false;
   
   fl_FuelLevel_Res_u8 = (uint8_t)l_FuelLevel_InPercentage_u32;
   if(fl_FuelLevel_Res_u8 <= WARNING_FUELLEVEL)
    {
       *p_Warning_status_bool=true;
       pucFuelWarning_Indictr_u16p->indicators.Fuel_warning_indicator=1;
    }
    
	return fl_FuelLevel_Res_u8;
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
static uint16_t calculateAverage(void)
{
    uint16_t fl_average_u16;
    fl_average_u16 = l_TotalSum_u16 / WINDOW_SIZE;
    
    return averfl_average_u16age;

}



