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
#include "../Indicator_App/Indicator_App.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define FuelApp_TestMacro (0)
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


/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/
/*The best practice is to never use a global variables but use get/set functions instead*/
//extern uint32_t gl_tmpl_system_timer_ID_u32;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern void vFuelGuageTaskInit(void);
extern void vFuelGuageTask(void);


#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t xGetFuelLevel(void);

#ifdef __cplusplus
}
#endif

#endif /* FUELGUAGE_APP_H */
