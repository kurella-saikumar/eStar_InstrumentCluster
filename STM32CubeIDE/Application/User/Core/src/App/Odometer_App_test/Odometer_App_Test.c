/** \addtogroup  
 *  @{
 * @file odometer_App_Test.c
 * @file odometer_App_Test.h
 * @brief Template Source File
 *
 * File Short Name: 
 *
 * Author: 
 *
 * Create Date: 
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************** @}*/
/* 
 * File:   odometer_App_Test.c
 * Author: Monika
 *
 * Created on February 28, 2024, 12:38 PM
 */

#ifndef ODOMETER_APP_TEST_C
#define	ODOMETER_APP_TEST_C


/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/
#include "../Odometer_App/Odometer_App.h"


/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
bool temp_IgnitionStatus = 0;
uint32_t OdoForDisplay  = 0;
bool switch_pressed=0;
/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
 ***************************************************************************************************/
bool xGetIgnitionStatus(void)
{   
    //temp_IgnitionStatus = Ign_pin_GetValue();
    temp_IgnitionStatus = 1;
    
    if(temp_IgnitionStatus)   
        return true;
    else 
        return false;
}

//    OdoForDisplay = xGetOdoReadings(displayOdoUnits);
//        
//    printf("s: %d\t", OdoForDisplay);
//    printf("u: %d\n", displayOdoUnits);


void vReadOdoUnitsCustomizePin(void)
{
    //if(odoU_cust_sw_GetValue())
	if(1)
    {
//        //do nothing
        printf("c: t\n");
    }
    else
    {
        printf("c: f\n");
        //vToggleOdoUnits();
    }
}
#endif	/* ODOMETER_APP_TEST_C */

