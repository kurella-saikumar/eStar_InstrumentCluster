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

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
Main_DATA MainData;
Sub_DATA SubData;
IndicationStatus_t IndicationStatus;
/**************************************************************************************************
 * Purpose: The purpose of gl_ADC_Value_u16 variable is to store the ADC value and used in application.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
extern uint16_t gl_ADC_Value_u16;

/**************************************************************************************************
 * Purpose: The purpose of gl_Current_FuelLevel_u16 variable is to store the current fuel level.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
uint16_t gl_Current_FuelLevel_u16;


/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/**************************************************************************************************
 * Purpose: The purpose of l_FuelLevel_InPercentage_u32 variable is to store the fuel level in percentage.
 *
 * Unit: 32 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 4294967295
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint32_t l_FuelLevel_InPercentage_u32;

/**************************************************************************************************
 * Purpose: The purpose of l_Dampout_value_u32 variable is to store the updated damp out value with step size parameter.
 *
 * Unit: 32 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 4294967295
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint32_t l_Dampout_value_u32;

/**************************************************************************************************
 * Purpose: The purpose of l_adcValues_u16A array is store the continuous moving average values from ADC.
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_adcValues_u16A[WINDOW_SIZE];

/**************************************************************************************************
 * Purpose: The purpose of l_SampleCount_u16 variable is to keep track of the number of samples
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_SampleCount_u16 = 0;

/**************************************************************************************************
 * Purpose: The purpose of l_TotalSum_u16 variable is to add and store the total sum of ADC values
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_TotalSum_u16 = 0;

/**************************************************************************************************
 * Purpose: The purpose of l_Initial_samplingOver_Flag_u8 flag to indicate if initial sampling process is over
 *
 * Unit: 8 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 255
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint8_t l_Initial_samplingOver_Flag_u8=0;

/**************************************************************************************************
 * Purpose: The purpose of l_FillType_DetctOver_Flag_u8 flag to indicate if fill type detection process is over
 *
 * Unit: 8 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 255
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint8_t l_FillType_DetctOver_Flag_u8=0;

/**************************************************************************************************
 * Purpose: The purpose of l_FastFillCount_16 variable to count the duration of fast fill operation
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_FastFillCount_16;

/**************************************************************************************************
 * Purpose: The purpose of static variable to count the duration of slow fill operation
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_SlowFillCount_u16;

/**************************************************************************************************
 * Purpose: The purpose of l_NormalFillCount_u16 variable to count the duration of normal fill operation
 *
 * Unit: 16 bit
 *
 * Resolution: 1 Bit
 *
 * Range: 0 to 65535
 *
 * Power On Init Value\Action: 0
 *
 * Wakeup Value\Action: 0
 *
 * Shutdown Value\Action: Don't Care
 *
 ***************************************************************************************************/
static uint16_t l_NormalFillCount_u16;

static FillType_State_T l_FillType_t;
static FillType_State_T l_Previous_FillType_t;
static FillType_State_T l_Current_FillType_t;


extern uint16_t l_count_u16[1];

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
 * Description: This function is designed to Initialize the main state.
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
        	/**:Perform initial sampling process to get the continuous moving average values for 3sec time period;*/
            gl_Current_FuelLevel_u16 = prvInital_SamplingProcess();
#if(TESTMACRO == 1)
            printf("CFL-%d\r\n",gl_Current_FuelLevel_u16);
            printf("IGN_OFF\n");
#endif
            /**Check if enough samples are accumulated and ignition is ON for state transition*/
            if(l_SampleCount_u16 >= WINDOW_SIZE)
            {
                if ((usIgnitionGetCurrentState() == IgnON_mode) && (l_Initial_samplingOver_Flag_u8==1))
                {
                	/**:Reset sample count;*/
                	l_SampleCount_u16=0;
                	/**:Transition to Offline_FillType_Dtcn_State:*/
                    MainData.Main_state = Offline_FillType_Dtcn_State;
                }
            }
            break;
        }
        case Offline_FillType_Dtcn_State:
        {
        	/**:Perform offline fill type detection process to check the current fill type;*/
            l_FillType_t = prvOffline_FillTypeDtcn_Prcs();
            /**:Update current fill type;*/
            l_Current_FillType_t = l_FillType_t;
#if(TESTMACRO ==1)
            printf("IGN_ON\n");
#endif
            /**Check if ignition is ON and fill type detection is over for state transition*/
            if((usIgnitionGetCurrentState() == IgnON_mode) && (l_FillType_DetctOver_Flag_u8==1))
            {
                 if((l_FillType_t == Normal_fill) || (l_FillType_t == Slow_fill))
                {
                	/**:Transition to Online_Process_State;*/
                    MainData.Main_state = Online_Process_State;
                    /**: Set sub-state;*/
                    SubData.Sub_state = l_FillType_t;
                }
                else /*Instantaneous_Update*/ 
                {
                	/**:perform vUpdateParametrs function to update the min time and step size of Instantaneous_Update filter;*/
                	vUpdateParametrs(INSTANTANEOUS_FILTER_UPDATERATE, INSTANTANEOUS_FILTER_STEPSIZE);
#if(TESTMACRO ==1)
                    printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                    printf("IUCnt %d\t", INSTANTANEOUS_FILTER_UPDATERATE );
                    printf("IUSiz %d\t",INSTANTANEOUS_FILTER_STEPSIZE);
#endif
                    /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                    DAMP_OUT ();
                    /**: Get the updated damp out value;*/
                    l_Dampout_value_u32 = Get_DAMP_OUT(0);
                    /**: perform Set fuel level function to update the fuel level in percentage;*/
                    prvSet_FuelLevel();
                    /**:Transition to Online_Process_State;*/
                    MainData.Main_state = Online_Process_State;
                    /**: Set sub-state to invalid;*/
                    SubData.Sub_state = Invalid;
                }
            }
            break;
        }
        case Online_Process_State:
        {
#if(TESTMACRO ==1)
        	printf("IGN_ON: \r\n");
#endif
            switch(SubData.Sub_state)
            {
                case Fast_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                    	/**: Reset fast fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute fast fill process within a timeout period*/
                    while(l_FastFillCount_16 <= FASTFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                        if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                        	/**:Reset fast fill count;*/
                            l_FastFillCount_16=0;
                            /**:Exit loop if current fuel level matches damp out value;*/
                            break;
                        }
                        else
                        {
                        	/**:Increment fast fill count;*/
                            l_FastFillCount_16++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Fast Fill filter;*/
                            vUpdateParametrs(FAST_FILL_LOSS_FILTER_UPDATERATE, FAST_FILL_LOSS_FILTER_STEPSIZE);
#if(TESTMACRO ==1)
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("FFCnt %d\t", FAST_FILL_LOSS_FILTER_UPDATERATE );
                            printf("FFSiz %d\t",FAST_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
                            prvSet_FuelLevel();
                        }
                    }      
                    break;
                }
                case Slow_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                    	/**: Reset slow fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute slow fill process within a timeout period*/
                    while(l_SlowFillCount_u16 <= SLOWFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                         if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                        	/**:Reset slow fill count;*/
                            l_SlowFillCount_u16=0;
                            /**Exit loop if current fuel level matches damp out value*/
                            break;
                        }
                        else
                        {
                        	/**:Increment slow fill count;*/
                            l_SlowFillCount_u16++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Slow Fill filter;*/
                            vUpdateParametrs(SLOW_FILL_LOSS_FILTER_UPDATERATE, SLOW_FILL_LOSS_FILTER_STEPSIZE);
#if(TESTMACRO ==1)
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("SFCnt %d\t",SLOW_FILL_LOSS_FILTER_UPDATERATE);
                            printf("SFSiz %d\t",SLOW_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
                            prvSet_FuelLevel();    
                        }   
                    }
                    break;
                }
                case Normal_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(l_Previous_FillType_t != l_Current_FillType_t)
                    {
                    	/**: Reset Normal fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute Normal fill process within a timeout period*/
                    while(l_NormalFillCount_u16 <= NORMALFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                        if(gl_Current_FuelLevel_u16 == l_Dampout_value_u32 )
                        {
                        	/**:Reset slow fill count;*/
                            l_NormalFillCount_u16=0;
                            /**:Exit loop if current fuel level matches damp out value;*/
                            break;
                        }
                        else
                        {
                        	/**:Increment Normal fill count;*/
                            l_NormalFillCount_u16++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Normal Fill filter;*/
                            vUpdateParametrs(NORMAL_FILL_LOSS_FILTER_UPDATERATE, NORMAL_FILL_LOSS_FILTER_STEPSIZE);
#if(TESTMACRO ==1)
                            printf("CFL-%d\t",gl_Current_FuelLevel_u16);
                            printf("NFCnt %d\t", NORMAL_FILL_LOSS_FILTER_UPDATERATE);
                            printf("NFSiz %d\t",NORMAL_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            l_Dampout_value_u32 = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
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
            /**: Update previous fill type with Current_FillType;*/
            l_Previous_FillType_t=l_Current_FillType_t;
            /**:Perform online fill type detection process to check the current fill type in online;*/
            l_FillType_t = prvOnline_FillTypeDtcn_Prcs();
            /**: Update current fill type;*/
            l_Current_FillType_t = l_FillType_t;
            /**:Update sub-state based on fill type;*/
            /**check if fill type is Fast fill*/
            if(l_FillType_t == Fast_fill)
            {
            	/**:Set sub-state to Fast_fill;*/
                SubData.Sub_state = Fast_fill;
            }
            /**check if fill type is Slow fill*/
            else if(l_FillType_t == Slow_fill)
            {
            	/**: Set sub-state to Slow_fill;*/
                SubData.Sub_state = Slow_fill;
            }
            else
            {
            	/**:Set sub-state to Normal_fill;*/
                SubData.Sub_state = Normal_fill;
            }
            /**Check ignition state for state transition*/
            if(usIgnitionGetCurrentState() == IgnOFF_mode)
            {
            	/**:Transition to INIT_Sampling_State;*/
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
	/**:Variable to store the Resulting calculated average;*/
    uint16_t l_res_t=0;
    /**:Variable to store the Sensor value from ADC;*/
    uint16_t fl_sensorValue_u16;
    /**: Static variable to track the circular buffer index;*/
    static uint8_t l_currentIndex_u8 = 0;
    
    fl_sensorValue_u16 = gl_ADC_Value_u16;
    /**: Store the value in the circular buffer;*/
    l_adcValues_u16A[l_currentIndex_u8] = fl_sensorValue_u16;

    /**: Move to the next index in the circular buffer;*/
    l_currentIndex_u8 = (l_currentIndex_u8 + 1) % WINDOW_SIZE;

    /**: Accumulate the ADC values;*/
    l_TotalSum_u16 += fl_sensorValue_u16;
    l_SampleCount_u16++;

    /** If we have accumulated enough samples, calculate the average*/
    if (l_SampleCount_u16 >= WINDOW_SIZE)
    {

    	/*:do the avaerage calculation of adc samples;*/
        l_res_t = calculateAverage();
        /*:set l_Initial_samplingOver_Flag_u8 flag bit tp 1;*/
        l_Initial_samplingOver_Flag_u8=1;

        /**: Subtract the oldest sample from the total sum;*/
        l_TotalSum_u16 -= l_adcValues_u16A[l_currentIndex_u8];
    
    }
    /**:Return the calculated average;*/
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
	/**:Variable to store the difference between current and last displayed levels;*/
    uint16_t fl_delta_u16;
    /**:Variable to store the Resulting fill type state;*/
    FillType_State_T l_res_t;
    /**:Variable to store the Last displayed fuel level;*/
    uint16_t fl_Last_Displayed_Level_u16;
    
    /**: Get the last displayed fuel level from dampout value;*/
    fl_Last_Displayed_Level_u16 = (uint16_t)l_Dampout_value_u32;
    /**: Calculate the difference between current fuel level and last displayed levels;*/
    if(gl_Current_FuelLevel_u16 > fl_Last_Displayed_Level_u16 )
    {
        fl_delta_u16 = gl_Current_FuelLevel_u16 - fl_Last_Displayed_Level_u16;
    }
    else
    {
        fl_delta_u16 = fl_Last_Displayed_Level_u16 - gl_Current_FuelLevel_u16;
    }
    /**:set the l_FillType_DetctOver_Flag_u8 to 1 after offline fill type detection completed;*/
    l_FillType_DetctOver_Flag_u8=1;

    /**: Determine fill type based on the difference;*/
    /**check if delta is greater than or equal to FAST_FILL_RANGE*/
    if(fl_delta_u16 >= FAST_FILL_RANGE)
    {
    	/**: set fill type is Instantaneous_Update;*/
        l_res_t = Instantaneous_Update;
    }
    /**check if delta is greater than or equal to  SLOW_FILL_RANGE and less than FAST_FILL_RANGE*/
    else if((fl_delta_u16 >= SLOW_FILL_RANGE) && (fl_delta_u16 < FAST_FILL_RANGE))
    {
    	/**: set fill type is Slow_fill;*/
        l_res_t = Slow_fill;
    }
    else
    {
    	/**: set fill type is Normal_fill;*/
        l_res_t = Normal_fill;
    }
    /**:Return the fill type state;*/
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
	/**:Variable to store the difference between current fuel level and last displayed levels;*/
    uint16_t fl_delta_u16;
    /**:Resulting fill type state;*/
    FillType_State_T l_res_t;
    /**:Variable to store the Damp_out value;*/
    uint16_t fl_Last_Displayed_Level_u16;
    
    /**: Get current fuel level from ADC;*/
    gl_Current_FuelLevel_u16 = gl_ADC_Value_u16;
#if(TESTMACRO ==1)
    printf("CFL-%d\r\n",gl_Current_FuelLevel_u16);
#endif
    /**:Get the last displayed fuel level from dampout value;*/
    fl_Last_Displayed_Level_u16 = (uint16_t)l_Dampout_value_u32;
    /**:Calculate the difference between current fuel level and last displayed levels;*/
    if(gl_Current_FuelLevel_u16 > fl_Last_Displayed_Level_u16)
    {  
        fl_delta_u16 = gl_Current_FuelLevel_u16 - fl_Last_Displayed_Level_u16;
    }
    else
    {
        fl_delta_u16 = fl_Last_Displayed_Level_u16 - gl_Current_FuelLevel_u16;
    }
    /**:Determine fill type based on the difference;*/
    /**check if delta is greater than or equal to FAST_FILL_RANGE*/
    if(fl_delta_u16 >= FAST_FILL_RANGE)
    {
    	/**: set fill type is Fast_fill;*/
        l_res_t = Fast_fill;
    }
    /**check if delta is greater than or equal to  SLOW_FILL_RANGE and less than FAST_FILL_RANGE*/
    else if((fl_delta_u16 >= SLOW_FILL_RANGE) && (fl_delta_u16< FAST_FILL_RANGE))
    {
    	/**: set fill type is Slow_fill;*/
        l_res_t = Slow_fill;
    }
    else
    {
    	/**: set fill type is Normal_fill;*/
        l_res_t = Normal_fill;
    }
    /**:Return the fill type state;*/
    return l_res_t;
    
}

/**************************************************************************************************
 * Function Name:  prvSet_FuelLevel
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to set the fuel level in percentage.#ifdef TESTMACRO
 *
 ***************************************************************************************************/
static void prvSet_FuelLevel(void)
{
	/**: Calculate fuel level as a percentage;*/
    l_FuelLevel_InPercentage_u32 = (l_Dampout_value_u32 * 100)/(MAXIMUM_ADC_RANGE);
#if(TESTMACRO ==1)
    printf("DO: %lu\t FL:%lu\r\n",l_Dampout_value_u32, l_FuelLevel_InPercentage_u32);
#endif
}

/**************************************************************************************************
 * Function Name: xGet_FuelLevel
 *
 * output Parameters: ucFuelWarning_Indictr, Warning_status
 *
 * Return Value: Fuel level in percentage
 *
 * Description: This function is designed to get the Updated FuelLevel and providing the status of Fuel bar and Fuel Icon
 *
 ***************************************************************************************************/
uint8_t xGet_FuelLevel(IndicationStatus_t* pucFuelWarning_Indictr_u16p, bool* p_Warning_status_bool)
{
	/**:Variable to store the fuel level;*/
    uint8_t fl_FuelLevel_Res_u8 = 0 ;
    /**:Initialize warning status to false;*/
    *p_Warning_status_bool=false;
    /**:Get fuel level as a percentage;*/
    fl_FuelLevel_Res_u8 = (uint8_t)l_FuelLevel_InPercentage_u32;
    /**check if fl_FuelLevel_Res_u8 is less than or equeal to WARNING_FUELLEVEL*/
    if(fl_FuelLevel_Res_u8 <= WARNING_FUELLEVEL)
    {
       /**:Set warning status to true;*/
       *p_Warning_status_bool=true;
       /**:Update fuel warning indicator;*/
       pucFuelWarning_Indictr_u16p->indicators.Fuel_warning_indicator=1;
    }
    /**:Return the fuel level;*/
	return fl_FuelLevel_Res_u8;
}

/**************************************************************************************************
 * Function Name: calculateAverage
 *
 * Input Parameter: void
 *
 * Return Value: return the average value.
 *
 * Description: This function is designed to get the average value of ADC raw inputs for 3sec time period.
 *
 ***************************************************************************************************/
static uint16_t calculateAverage(void)
{
	/**:Variable to store the calculated average;*/
    uint16_t fl_average_u16;
    /**:Calculate the average by dividing the total sum by the window size;*/
    fl_average_u16 = l_TotalSum_u16 / WINDOW_SIZE;
    /**:Return the calculated average;*/
    return fl_average_u16;

}



