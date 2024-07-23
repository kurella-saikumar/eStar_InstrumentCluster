/** \addtogroup TEMPLATE
 *  @{
 * @Indicator_App.h
 *
 * @brief This file contains an example template of how the .h 
 *
 * File Short Name: tmpl
 *
 * @author: Roja Ramani
 *
 * @date: 15 Apr 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef INDICATOR_APP_H    /* Guard against multiple inclusion */
#define INDICATOR_APP_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define Indicator_Macro 0

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
typedef union {
     uint32_t Indicator_status;
     struct {
         uint8_t right_indicator : 1;
         uint8_t left_indicator : 1;
         uint8_t parking_indicator : 1;
         uint8_t HighBeam_indicator :1;
         uint8_t LowBeam_indicator : 1;
         uint8_t engine_oil_temp_indicator : 1;
         uint8_t seat_belt_indicator : 1;
         uint8_t engine_malfunction_indicator : 1;
         uint8_t door_open_indicator : 1;
         uint8_t abs_warning_indicator : 1;
         uint8_t FaultyRight_indicator : 1;																			  //
         uint8_t FaultyLeft_indicator :1;
         uint8_t Engine_Oil_indicator : 1;
         uint8_t low_battery_indicator : 1;
         uint8_t service_reminder_indicator : 1;
         uint8_t tachometer_indicator : 1;
         uint8_t over_speed_indicator : 1;
         uint8_t Fuel_warning_indicator : 1;
         uint32_t reserved :14;
     }indicators;

}IndicationStatus_t ;

extern IndicationStatus_t   Status;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

extern void vIndicatorsInit(void);
extern void vIndicator_App_Task(void);



#ifdef __cplusplus
extern "C" {
#endif

extern IndicationStatus_t xGetIndicatorstatus(void);

#ifdef __cplusplus
}
#endif



#endif /* FILE_TEMPLATE_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
