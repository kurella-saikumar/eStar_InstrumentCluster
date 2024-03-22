/** \addtogroup TACHO_APP
 *  @{
 * @Tachometer.h
 *
 * @brief This file contains an example template of how the .h 
 *
 * File Short Name: Tachometer_App.h
 *
 * @author: _________
 *
 * @date: __________
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef TACHOMETER_H   /* Guard against multiple inclusion */
#define TACHOMETER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "Tachometer_App_cfg.h"
#include "../ICU_middleware/ICU_driver.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
void vTacho_Init(void);
uint32_t prvMeasureRPM(void);
uint16_t xGet_TachometerData(IndicationStatus_t* Indication,bool *status);
void vTacho_App(void);






#endif /* TACHOMETER_H*/

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
