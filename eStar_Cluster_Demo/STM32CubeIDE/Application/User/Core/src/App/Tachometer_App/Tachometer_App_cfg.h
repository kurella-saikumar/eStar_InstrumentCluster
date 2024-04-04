/** \addtogroup TEMPLATE
 *  @{
 * @Tachometer_cfg.h
 *
 * @brief This file contains an example template of how the .h 
 *
 * File Short Name: tmpl
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
#ifndef TACHOMETER_CFG_H    /* Guard against multiple inclusion */
#define TACHOMETER_CFG_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdbool.h>
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define IDLE_ENGINE_RPM 700
#define WARNING_ENGINE_RPM 10000
#define MAXIMUM_ENGINE_RPM 12000
//#define ERROR_THRESHOLD_RPM  >12000 
#define FIXED_PPR_VALUE 1
#define TIME 1

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/


/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/




#endif /* TACHOMETER_CFG_H*/

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
