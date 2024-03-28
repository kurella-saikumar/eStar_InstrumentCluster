/******************************************************************************************
 * Feature Name: FuelGuage_App.h
 *
 * Feature Short Name: FuelGuage
 *
 * Description: This file contains an example template of how the .h
 * file should be created and maintained. The contents cover the following information
 * 1. Avoid multiple include of the same file hence avoiding recursive includes of any files
 * 2. Usage of EXTERN helps define the global scope functions/variables. Any file using these
 * should include the header file and the prototype definition is there automatically
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

#ifndef FUELGUAGE_APP_H
#define FUELGUAGE_APP_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdint.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define FuelIndex 0
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/


typedef enum
{
    Instantaneous_Update=0,
    Fast_fill,
    Normal_fill,
    Slow_fill,
    Invalid,        
}FillType_State_T;

typedef enum
{
    /* Application's state machine's initial state. */
    INIT_Sampling_State=0,
    Offline_FillType_Dtcn_State,
    Online_Process_State,        
    /* TODO: Define states used by the application state machine. */
} Main_STATES;

typedef struct
{
    /* The application's current state */
   Main_STATES Main_state;
    /* TODO: Define any additional data used by the application. */
} Main_DATA;

typedef struct
{
    /* The application's current state */
   FillType_State_T Sub_state;
    /* TODO: Define any additional data used by the application. */
} Sub_DATA;

typedef union {
    struct {
        uint8_t right_indicator : 1;
        uint8_t left_indicator : 1;
        uint8_t parking_indicator : 1;
        uint8_t low_battery_indicator : 1;
        uint8_t engine_oil_temp_indicator : 1;
        uint8_t seat_belt_indicator : 1;
        uint8_t engine_malfunction_indicator : 1;
        uint8_t service_reminder_indicator : 1;
        uint8_t door_open_indicator : 1;
        uint8_t abs_warning_indicator : 1;
        uint8_t fuel_icon_indicator : 1;
        uint8_t tachometer_indicator : 1;
        uint8_t fuel_bar_indicator : 1;
        uint8_t over_speed_indicator : 1;
        uint8_t Fuel_warning_indicator : 1;
    } indicators;
    uint16_t all_indicators;
} IndicationStatus_t;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/*The best practice is to never use a global variables but use get/set functions instead*/
//extern uint32_t gl_tmpl_system_timer_ID_u32;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern void vFuelGuage_TaskInit(void);
extern void vFuelGuage_Task(void);
extern uint8_t xGet_FuelLevel(IndicationStatus_t* ucFuelWarning_Indictr, bool* Warning_status);

#endif /* FUELGUAGE_APP_H */
