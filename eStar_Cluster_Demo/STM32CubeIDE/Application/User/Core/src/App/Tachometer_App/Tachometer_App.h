/** \addtogroup TACHO_APP
 *  @{
 * @Tachometer_App.h
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
//#include "Tachometer_App_cfg.h"
//#include "../ICU_middleware/ICU_driver.h"
//#include "Indicator_App.h"
#include "../../../../Core/PlatformConfig/Tachometer_App_cfg.h"
#include "../../../src/App/Indicator_App/Indicator_App.h"
#include "../../../src/Service/IO_HAL/ICU_middleware/ICU_driver.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define TACHO_TEST_MACRO 0


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
void vMeasureRPM(void);
void vTacho_App(void);


#ifdef __cplusplus
extern "C" {
#endif

uint16_t xGet_TachometerData(void);

#ifdef __cplusplus
}
#endif



#endif /* TACHOMETER_H*/

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
