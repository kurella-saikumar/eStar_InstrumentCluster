/** \addtogroup  STATE_MACHINE_HANDLER
 *  @{
 * @file IGN_SmHandler_Demo.c
 *
 * @brief Template Source File
 *
 * File Short Name:
 *
 * Author:k.saikumar
 *
 * Create Date: 08/07/2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
// #include "stdint.h"
 #include "stdio.h"
//#include "types.h"

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "ECUPwrMode_SmHandler.h"
//#include "debug.h"
//#include "tcc_pmgpio.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/
void ECUPwrModeStandBy_To_Off_EntryAction(void);
void PwrModeActive_To_Off_EntryAction(void);
void ECUPwrModeOff_To_StandBy_EntryAction(void);
void ECUPwrModeStatic_To_StandBy_EntryAction(void);
void ECUPwrModeActive_To_StandBy_EntryAction(void);
void ECUPwrModeStandBy_To_Static_EntryAction(void);
void ECUPwrModeActive_To_Static_EntryAction(void);
void ECUPwrModeStandBy_To_Crank_EntryAction(void);
void ECUPwrModeStatic_To_Crank_EntryAction(void);
void ECUPwrModeActive_To_Crank_EntryAction(void);
void ECUPwrModeStandBy_To_Active_EntryAction(void);
void ECUPwrModeStatic_To_Active_EntryAction(void);
void ECUPwrModeCrank_To_Active_EntryAction(void);
void ECUPwrModeOff_Action(void);
void ECUPwrModeStandBy_Action(void);
void ECUPwrModeStatic_Action(void) ;
void ECUPwrModeCrank_Action(void);
void ECUPwrModeActive_Action(void);

void ECUPwrModeOff_Active_ENtryAction(void);
void ECUPerModeInitial_Off_EntryAction(void);
void ECUPwrModeInitial_Action(void);

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
 * @brief  ECUPwrModeStandBy_To_Off_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Off_EntryAction(void)
{
    printf("ECUPwrModeStandBy_To_Off_EntryAction\n");
}

/**
 * @brief  PwrModeActive_To_Off_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void PwrModeActive_To_Off_EntryAction(void)
{
    printf("wrModeActive_To_Off_EntryAction\n");
    //PowerDown(Hw_ACC_DET);
}

/**
 * @brief  ECUPwrModeOff_To_StandBy_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_OFF to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_To_StandBy_EntryAction(void)
{
    printf("ECUPwrModeOff_To_StandBy_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStatic_To_StandBy_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_StandBy_EntryAction(void)
{
    printf("ECUPwrModeStatic_To_StandBy_EntryAction\n");
}

/**
 * @brief  ECUPwrModeActive_To_StandBy_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_StandBy_EntryAction(void)
{
    printf("ECUPwrModeActive_To_StandBy_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStandBy_To_Static_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Static_EntryAction(void)
{
    printf("ECUPwrModeStandBy_To_Static_EntryAction\n");
}

/**
 * @brief  ECUPwrModeActive_To_Static_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Static_EntryAction(void)
{
    printf("ECUPwrModeActive_To_Static_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStandBy_To_Crank_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Crank_EntryAction(void)
{
    printf("ECUPwrModeStandBy_To_Crank_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStatic_To_Crank_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_Crank_EntryAction(void)
{
    printf("ECUPwrModeStatic_To_Crank_EntryAction\n");
}

/**
 * @brief  ECUPwrModeActive_To_Crank_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_ACTIVE to ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_To_Crank_EntryAction(void)
{
    printf("ECUPwrModeActive_To_Crank_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStandBy_To_Active_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STANDBY to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_To_Active_EntryAction(void)
{
    printf("ECUPwrModeStandBy_To_Active_EntryAction\n");
}

/**
 * @brief  ECUPwrModeStatic_To_Active_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_STATIC to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_To_Active_EntryAction(void)
{
    printf("ECUPwrModeStatic_To_Active_EntryAction\n");
}

/**
 * @brief  ECUPwrModeCrank_To_Active_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_CRANK to ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeCrank_To_Active_EntryAction(void)
{
    printf("ECUPwrModeCrank_To_Active_EntryAction\n");

}
/**
 * @brief  ECUPerModeInitial_Off_EntryAction function is to perform some action when the state changed from ECU_POWER_MODE_Initial to ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPerModeInitial_Off_EntryAction(void)
{
    printf("ECUPerModeInitial_Off_EntryAction\n");

}

/**
 * @brief  ECUPwrModeOff_Action function is to perform some action when the state remain in ECU_POWER_MODE_OFF
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeOff_Action(void)
{
    //Enable Wakeup Settings
    // Enter into sleep mode
    printf("ECUPwrModeOff_Action\n");
}

/**
 * @brief  ECUPwrModeStandBy_Action function is to perform some action when the state remain in ECU_POWER_MODE_STANDBY
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStandBy_Action(void)
{
    printf("ECUPwrModeStandBy_Action\n");
}

/**
 * @brief  ECUPwrModeStatic_Action function is to perform some action when the state remain in ECU_POWER_MODE_STATIC
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeStatic_Action(void)
{
    printf("ECUPwrModeStatic_Action\n");
}

/**
 * @brief  ECUPwrModeCrank_Action function is to perform some action when the state remain in ECU_POWER_MODE_CRANK
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeCrank_Action(void)
{
    printf("ECUPwrModeCrank_Action\n");
}

/**
 * @brief  ECUPwrModeActive_Action function is to perform some action when the state remain in ECU_POWER_MODE_ACTIVE
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeActive_Action(void)
{
    printf("ECUPwrModeActive_Action\n");
}
/**
 * @brief  ECUPwrModeInitial_Action function is to perform some action when the state remain in ECU_POWER_MODE_INITIAL
 *
 * @param[in] void type
 *
 * @return void
 *
 */
void ECUPwrModeInitial_Action(void)
{
    printf("ECUPwrModeInitial_Action\n");
}
/**
 * @brief  ECUPwrModeOff_Active_ENtryAction function is to perform some action when the state  change from ECU_POWER_MODE_OFF to Active
 *
 * @param[in] void type
 *
 * @return void
 *
 */

void ECUPwrModeOff_Active_ENtryAction()
{
    printf("ECUPwrModeOff_Active_ENtryAction\n");
    //PowerDown(Hw_ACC_DET);
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
