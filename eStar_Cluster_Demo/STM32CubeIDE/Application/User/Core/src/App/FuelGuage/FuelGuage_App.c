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
 * Purpose: The purpose of usADCValue variable is to store the ADC value and used in application.
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
extern uint16_t usADCValue;

/**************************************************************************************************
 * Purpose: The purpose of usCurrentFuelLevel variable is to store the current fuel level.
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
uint16_t usCurrentFuelLevel;


/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/
/**************************************************************************************************
 * Purpose: The purpose of ulFuelLevelInPercentage variable is to store the fuel level in percentage.
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
static uint32_t ulFuelLevelInPercentage;

/**************************************************************************************************
 * Purpose: The purpose of ulDampout_value variable is to store the updated damp out value with step size parameter.
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
static uint32_t ulDampout_value;

/**************************************************************************************************
 * Purpose: The purpose of usADCValues_A array is store the continuous moving average values from ADC.
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
static uint16_t usADCValues_A[configWINDOW_SIZE];

/**************************************************************************************************
 * Purpose: The purpose of usSampleCount variable is to keep track of the number of samples
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
static uint16_t usSampleCount = 0;

/**************************************************************************************************
 * Purpose: The purpose of usTotalSum variable is to add and store the total sum of ADC values
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
static uint16_t usTotalSum = 0;

/**************************************************************************************************
 * Purpose: The purpose of ucInitialSamplingOverFlag flag to indicate if initial sampling process is over
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
static uint8_t ucInitialSamplingOverFlag=0;

/**************************************************************************************************
 * Purpose: The purpose of ucFillTypeDetctOverFlag flag to indicate if fill type detection process is over
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
static uint8_t ucFillTypeDetctOverFlag=0;

/**************************************************************************************************
 * Purpose: The purpose of usFastFillCount variable to count the duration of fast fill operation
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
static uint16_t usFastFillCount;

/**************************************************************************************************
 * Purpose: The purpose of  usSlowFillCount variable to count the duration of slow fill operation
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
static uint16_t usSlowFillCount;

/**************************************************************************************************
 * Purpose: The purpose of usNormalFillCount variable to count the duration of normal fill operation
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
static uint16_t usNormalFillCount;

static FillType_State_T xFillType;
static FillType_State_T xPrevious_FillType;
static FillType_State_T xCurrent_FillType;


extern uint16_t l_count_u16[1];

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
static uint16_t prvInitalSamplingProcess(void);
static FillType_State_T prvOfflineFillTypeDtcnPrcs(void);
static FillType_State_T prvOnlineFillTypeDtcnPrcs(void);
static void prvSetFuelLevel(void);
static uint16_t prvCalculateAverage(void);
/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**************************************************************************************************
 * Function Name: vFuelGuageTaskInit
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to Initialize the main state.
 *
 ***************************************************************************************************/
void vFuelGuageTaskInit(void)
{
    MainData.Main_state = INIT_Sampling_State;
    
}

/**************************************************************************************************vFuelGuageTask
 *
 * Function Name: 
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to update the fuelLevel
 *
 ***************************************************************************************************/
void vFuelGuageTask(void)
{

    
    switch(MainData.Main_state)
    {
        
        case INIT_Sampling_State:
        {
        	/**:Perform initial sampling process to get the continuous moving average values for 3sec time period;*/
            usCurrentFuelLevel = prvInitalSamplingProcess();
#if(FuelApp_TestMacro == 1)
            printf("CFL-%d\r\n",usCurrentFuelLevel);
            printf("IGN_OFF\n");
#endif
            /**Check if enough samples are accumulated and ignition is ON for state transition*/
            if(usSampleCount >= configWINDOW_SIZE)
            {
                if ((usIgnitionGetCurrentState() == IgnON_mode) && (ucInitialSamplingOverFlag==1))
                {
                	/**:Reset sample count;*/
                	usSampleCount=0;
                	/**:Transition to Offline_FillType_Dtcn_State:*/
                    MainData.Main_state = Offline_FillType_Dtcn_State;
                }
            }
            break;
        }
        case Offline_FillType_Dtcn_State:
        {
        	/**:Perform offline fill type detection process to check the current fill type;*/
            xFillType = prvOfflineFillTypeDtcnPrcs();
            /**:Update current fill type;*/
            xCurrent_FillType = xFillType;
#if(FuelApp_TestMacro ==1)
            printf("IGN_ON\n");
#endif
            /**Check if ignition is ON and fill type detection is over for state transition*/
            if((usIgnitionGetCurrentState() == IgnON_mode) && (ucFillTypeDetctOverFlag==1))
            {
                 if((xFillType == Normal_fill) || (xFillType == Slow_fill))
                {
                	/**:Transition to Online_Process_State;*/
                    MainData.Main_state = Online_Process_State;
                    /**: Set sub-state;*/
                    SubData.Sub_state = xFillType;
                }
                else /*Instantaneous_Update*/ 
                {
                	/**:perform vUpdateParametrs function to update the min time and step size of Instantaneous_Update filter;*/
                	vUpdateParametrs(configINSTANTANEOUS_FILTER_UPDATERATE, configINSTANTANEOUS_FILTER_STEPSIZE);
#if(FuelApp_TestMacro ==1)
                    printf("CFL-%d\t",usCurrentFuelLevel);
                    printf("IUCnt %d\t", configINSTANTANEOUS_FILTER_UPDATERATE );
                    printf("IUSiz %d\t",configINSTANTANEOUS_FILTER_STEPSIZE);
#endif
                    /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                    DAMP_OUT ();
                    /**: Get the updated damp out value;*/
                    ulDampout_value = Get_DAMP_OUT(0);
                    /**: perform Set fuel level function to update the fuel level in percentage;*/
                    prvSetFuelLevel();
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
#if(FuelApp_TestMacro ==1)
        	printf("IGN_ON: \r\n");
#endif
            switch(SubData.Sub_state)
            {
                case Fast_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(xPrevious_FillType != xCurrent_FillType)
                    {
                    	/**: Reset fast fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute fast fill process within a timeout period*/
                    while(usFastFillCount <= configFASTFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                        if(usCurrentFuelLevel == ulDampout_value )
                        {
                        	/**:Reset fast fill count;*/
                            usFastFillCount=0;
                            /**:Exit loop if current fuel level matches damp out value;*/
                            break;
                        }
                        else
                        {
                        	/**:Increment fast fill count;*/
                            usFastFillCount++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Fast Fill filter;*/
                            vUpdateParametrs(configFAST_FILL_LOSS_FILTER_UPDATERATE, configFAST_FILL_LOSS_FILTER_STEPSIZE);
#if(FuelApp_TestMacro ==1)
                            printf("CFL-%d\t",usCurrentFuelLevel);
                            printf("FFCnt %d\t", configFAST_FILL_LOSS_FILTER_UPDATERATE );
                            printf("FFSiz %d\t",configFAST_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            ulDampout_value = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
                            prvSetFuelLevel();
                        }
                    }      
                    break;
                }
                case Slow_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(xPrevious_FillType != xCurrent_FillType)
                    {
                    	/**: Reset slow fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute slow fill process within a timeout period*/
                    while(usSlowFillCount <= configSLOWFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                         if(usCurrentFuelLevel == ulDampout_value )
                        {
                        	/**:Reset slow fill count;*/
                            usSlowFillCount=0;
                            /**Exit loop if current fuel level matches damp out value*/
                            break;
                        }
                        else
                        {
                        	/**:Increment slow fill count;*/
                            usSlowFillCount++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Slow Fill filter;*/
                            vUpdateParametrs(configSLOW_FILL_LOSS_FILTER_UPDATERATE, configSLOW_FILL_LOSS_FILTER_STEPSIZE);
#if(FuelApp_TestMacro ==1)
                            printf("CFL-%d\t",usCurrentFuelLevel);
                            printf("SFCnt %d\t",configSLOW_FILL_LOSS_FILTER_UPDATERATE);
                            printf("SFSiz %d\t",configSLOW_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            ulDampout_value = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
                            prvSetFuelLevel();    
                        }   
                    }
                    break;
                }
                case Normal_fill:
                {
                	/**check if the Previous_FillType and Current_FillType is not same*/
                    if(xPrevious_FillType != xCurrent_FillType)
                    {
                    	/**: Reset Normal fill count;*/
                        l_count_u16[0]= 0;
                    }
                    /**Execute Normal fill process within a timeout period*/
                    while(usNormalFillCount <= configNORMALFILL_TIMEOUT_MS)
                    {
                    	/**check if Current_FuelLevel and Dampout_values are equal*/
                        if(usCurrentFuelLevel == ulDampout_value )
                        {
                        	/**:Reset slow fill count;*/
                            usNormalFillCount=0;
                            /**:Exit loop if current fuel level matches damp out value;*/
                            break;
                        }
                        else
                        {
                        	/**:Increment Normal fill count;*/
                            usNormalFillCount++;
                            /**:perform vUpdateParametrs function to update the min time and step size of Normal Fill filter;*/
                            vUpdateParametrs(configNORMAL_FILL_LOSS_FILTER_UPDATERATE, configNORMAL_FILL_LOSS_FILTER_STEPSIZE);
#if(FuelApp_TestMacro ==1)
                            printf("CFL-%d\t",usCurrentFuelLevel);
                            printf("NFCnt %d\t", configNORMAL_FILL_LOSS_FILTER_UPDATERATE);
                            printf("NFSiz %d\t",configNORMAL_FILL_LOSS_FILTER_STEPSIZE);
#endif
                            /**:Perform damp_out task to update the dampout value to the current fuel level;*/
                            DAMP_OUT ();
                            /**: Get the updated damp out value;*/
                            ulDampout_value = Get_DAMP_OUT(0);
                            /**: perform Set fuel level function to update the fuel level in percentage;*/
                            prvSetFuelLevel();
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
            xPrevious_FillType=xCurrent_FillType;
            /**:Perform online fill type detection process to check the current fill type in online;*/
            xFillType = prvOnlineFillTypeDtcnPrcs();
            /**: Update current fill type;*/
            xCurrent_FillType = xFillType;
            /**:Update sub-state based on fill type;*/
            /**check if fill type is Fast fill*/
            if(xFillType == Fast_fill)
            {
            	/**:Set sub-state to Fast_fill;*/
                SubData.Sub_state = Fast_fill;
            }
            /**check if fill type is Slow fill*/
            else if(xFillType == Slow_fill)
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
 * Function Name: prvInitalSamplingProcess
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to calculate the 3sec continuous moving average value.
 *
 ***************************************************************************************************/
static uint16_t prvInitalSamplingProcess(void)
{
	/**:Variable to store the Resulting calculated average;*/
    uint16_t us_res=0;
    /**:Variable to store the Sensor value from ADC;*/
    uint16_t us_sensorValue;
    /**: Static variable to track the circular buffer index;*/
    static uint8_t l_currentIndex_u8 = 0;
    
    us_sensorValue = usADCValue;
    /**: Store the value in the circular buffer;*/
    usADCValues_A[l_currentIndex_u8] = us_sensorValue;

    /**: Move to the next index in the circular buffer;*/
    l_currentIndex_u8 = (l_currentIndex_u8 + 1) % configWINDOW_SIZE;

    /**: Accumulate the ADC values;*/
    usTotalSum += us_sensorValue;
    usSampleCount++;

    /** If we have accumulated enough samples, calculate the average*/
    if (usSampleCount >= configWINDOW_SIZE)
    {

    	/*:do the avaerage calculation of adc samples;*/
        us_res = prvCalculateAverage();
        /*:set ucInitialSamplingOverFlag flag bit tp 1;*/
        ucInitialSamplingOverFlag=1;

        /**: Subtract the oldest sample from the total sum;*/
        usTotalSum -= usADCValues_A[l_currentIndex_u8];
    
    }
    /**:Return the calculated average;*/
    return us_res;
    
}

/**************************************************************************************************
 * Function Name: prvOfflineFillTypeDtcnPrcs.
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to detect the fillType(slow_fill,Normal_fill,Instantaneous_update)in offline.
 *
 ***************************************************************************************************/
static FillType_State_T prvOfflineFillTypeDtcnPrcs(void)
{
	/**:Variable to store the difference between current and last displayed levels;*/
    uint16_t us_delta;
    /**:Variable to store the Resulting fill type state;*/
    FillType_State_T xFillTypeRes;
    /**:Variable to store the Last displayed fuel level;*/
    uint16_t us_Last_Displayed_Level;
    
    /**: Get the last displayed fuel level from dampout value;*/
    us_Last_Displayed_Level = (uint16_t)ulDampout_value;
    /**: Calculate the difference between current fuel level and last displayed levels;*/
    if(usCurrentFuelLevel > us_Last_Displayed_Level )
    {
        us_delta = usCurrentFuelLevel - us_Last_Displayed_Level;
    }
    else
    {
        us_delta = us_Last_Displayed_Level - usCurrentFuelLevel;
    }
    /**:set the ucFillTypeDetctOverFlag to 1 after offline fill type detection completed;*/
    ucFillTypeDetctOverFlag=1;

    /**: Determine fill type based on the difference;*/
    /**check if delta is greater than or equal to configFAST_FILL_RANGE*/
    if(us_delta >= configFAST_FILL_RANGE)
    {
    	/**: set fill type is Instantaneous_Update;*/
        xFillTypeRes = Instantaneous_Update;
    }
    /**check if delta is greater than or equal to  configSLOW_FILL_RANGE and less than configFAST_FILL_RANGE*/
    else if((us_delta >= configSLOW_FILL_RANGE) && (us_delta < configFAST_FILL_RANGE))
    {
    	/**: set fill type is Slow_fill;*/
        xFillTypeRes = Slow_fill;
    }
    else
    {
    	/**: set fill type is Normal_fill;*/
        xFillTypeRes = Normal_fill;
    }
    /**:Return the fill type state;*/
    return xFillTypeRes;
}

/**************************************************************************************************
 * Function Name:  prvOnlineFillTypeDtcnPrcs
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to detect the fillType(slow_fill,Normal_fill, Fast_fill)in online.
 *
 ***************************************************************************************************/
static FillType_State_T prvOnlineFillTypeDtcnPrcs(void)
{
	/**:Variable to store the difference between current fuel level and last displayed levels;*/
    uint16_t us_delta;
    /**:Resulting fill type state;*/
    FillType_State_T xFillTypeRes;
    /**:Variable to store the Damp_out value;*/
    uint16_t us_Last_Displayed_Level;
    
    /**: Get current fuel level from ADC;*/
    usCurrentFuelLevel = usADCValue;
#if(FuelApp_TestMacro ==1)
    printf("CFL-%d\r\n",usCurrentFuelLevel);
#endif
    /**:Get the last displayed fuel level from dampout value;*/
    us_Last_Displayed_Level = (uint16_t)ulDampout_value;
    /**:Calculate the difference between current fuel level and last displayed levels;*/
    if(usCurrentFuelLevel > us_Last_Displayed_Level)
    {  
        us_delta = usCurrentFuelLevel - us_Last_Displayed_Level;
    }
    else
    {
        us_delta = us_Last_Displayed_Level - usCurrentFuelLevel;
    }
    /**:Determine fill type based on the difference;*/
    /**check if delta is greater than or equal to configFAST_FILL_RANGE*/
    if(us_delta >= configFAST_FILL_RANGE)
    {
    	/**: set fill type is Fast_fill;*/
        xFillTypeRes = Fast_fill;
    }
    /**check if delta is greater than or equal to  configSLOW_FILL_RANGE and less than configFAST_FILL_RANGE*/
    else if((us_delta >= configSLOW_FILL_RANGE) && (us_delta< configFAST_FILL_RANGE))
    {
    	/**: set fill type is Slow_fill;*/
        xFillTypeRes = Slow_fill;
    }
    else
    {
    	/**: set fill type is Normal_fill;*/
        xFillTypeRes = Normal_fill;
    }
    /**:Return the fill type state;*/
    return xFillTypeRes;
    
}

/**************************************************************************************************
 * Function Name:  prvSetFuelLevel
 *
 * Input Parameter: void
 *
 * Return Value: void
 *
 * Description: This function is designed to set the fuel level in percentage.#ifdef FuelApp_TestMacro
 *
 ***************************************************************************************************/
static void prvSetFuelLevel(void)
{
	/**: Calculate fuel level as a percentage;*/
    ulFuelLevelInPercentage = (ulDampout_value * 100)/(configMAXIMUM_ADC_RANGE);
#if(FuelApp_TestMacro ==1)
    printf("DO: %lu\t FL:%lu\r\n",ulDampout_value, ulFuelLevelInPercentage);
#endif
}

/**************************************************************************************************
 * Function Name: xGetFuelLevel
 *
 * output Parameters: ucFuelWarning_Indictr, Warning_status
 *
 * Return Value: Fuel level in percentage
 *
 * Description: This function is designed to get the Updated FuelLevel and providing the status of Fuel bar and Fuel Icon
 *
 ***************************************************************************************************/
uint8_t xGetFuelLevel(IndicationStatus_t* pucFuelWarning_Indictr_u16p, bool* p_Warning_status_bool)
{
	/**:Variable to store the fuel level;*/
    uint8_t uc_FuelLevel_Res = 0 ;
    /**:Initialize warning status to false;*/
    *p_Warning_status_bool=false;
    /**:Get fuel level as a percentage;*/
    uc_FuelLevel_Res = (uint8_t)ulFuelLevelInPercentage;
    /**check if uc_FuelLevel_Res is less than or equeal to configWARNING_FUELLEVEL*/
    if(uc_FuelLevel_Res <= configWARNING_FUELLEVEL)
    {
       /**:Set warning status to true;*/
       *p_Warning_status_bool=true;
       /**:Update fuel warning indicator;*/
       pucFuelWarning_Indictr_u16p->indicators.Fuel_warning_indicator=1;
    }
    /**:Return the fuel level;*/
	return uc_FuelLevel_Res;
}

/**************************************************************************************************
 * Function Name: prvCalculateAverage
 *
 * Input Parameter: void
 *
 * Return Value: return the average value.
 *
 * Description: This function is designed to get the average value of ADC raw inputs for 3sec time period.
 *
 ***************************************************************************************************/
static uint16_t prvCalculateAverage(void)
{
	/**:Variable to store the calculated average;*/
    uint16_t us_average;
    /**:Calculate the average by dividing the total sum by the window size;*/
    us_average = usTotalSum / configWINDOW_SIZE;
    /**:Return the calculated average;*/
    return us_average;

}



