/** \addtogroup TEMPLATE
 *  @{
 * @Indicator_App.h
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
/**
 * Flag to indicate that the required mode of ADC conversion is Continuous Mode
 */
#define LEFTTURNINDICATOR_STATUS      1
#define RIGHTTURNINDICATOR_STATUS     1
#define PARKINGINDICATORS_STATUS      1
#define HIGHBEAMINDICATOR_STATUS      0
#define LOWBEAMINDICATOR_STATUS       1
#define ENGTEMPINDICATOR_STATUS       1
#define SEATBELTWARINDICATOR_STATUS   1
#define DOOROPENWARINDICATOR_STATUS   1
#define ABSINDICATOR_STATUS           0
#define ENGINEMALFUNCTION_STATUS      1
#define FAULTYLEFT_STATUS             0
#define FAULTYRIGHT_STATUS            1



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
         uint8_t low_battery_indicator : 1;
         uint8_t engine_oil_temp_indicator : 1;
         uint8_t seat_belt_indicator : 1;
         uint8_t engine_malfunction_indicator : 1;
         uint8_t service_reminder_indicator : 1;
         uint8_t door_open_indicator : 1;
         uint8_t abs_warning_indicator : 1;
         uint8_t tachometer_indicator : 1;
         uint8_t over_speed_indicator : 1;
         uint8_t Fuel_warning_indicator : 1;
         uint8_t FaultyLeft_indicator : 1;
         uint8_t FaultyRight_indicator :1;
         uint32_t reserved :15;
     }indicators;

}IndicationStatus_t;
/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

extern void vIndicatorsInit(void);
extern void vIndicator_App_Task(void);
extern uint32_t  xGetIndicatorstatus(void);
#endif /* FILE_TEMPLATE_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
