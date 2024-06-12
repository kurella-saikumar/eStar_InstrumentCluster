
/** \addtogroup  
 *  @{
 * @file ICU_driver.h
 *
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
 * File:   ICU_driver.h
 * Author:
 *
 * Created on February 22, 2024, 4:19 PM
 */

#ifndef ICU_DRIVER_H
#define	ICU_DRIVER_H

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

#include <stdint.h>
//#include "ICU_driver_cfg.h"
#include "../../../../PlatformConfig/ICU_driver_cfg.h"
/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
 ***************************************************************************************************/
#define USHRT_MAX	65535
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/
 extern uint16_t edge_Counter[MAX_CHANNELS];
 extern uint8_t edge_Counter_Rollover_Flag[MAX_CHANNELS];
 extern uint32_t temp_edgeCounter;
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
 ***************************************************************************************************/
 void vTriggeredEdge_Counter(uint8_t channelNum);
uint32_t xGetRollingPulseCount(uint8_t channelNum);
void vEnable_OdoSpeedo_Channel_Interrupts(void);
void vDisable_OdoSpeedo_Channel_Interrupts(void);



#endif	/* ICU_DRIVER_H */

