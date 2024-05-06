/*
 * Indicator_App.h
 *
 *  Created on: Apr 3, 2024
 *      Author: 91810
 */

#ifndef INDICATOR_APP_H_
#define INDICATOR_APP_H_

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
extern IndicationStatus_t IndicationStatus;


#endif /* APPLICATION_USER_CORE_SRC_APP_INDICATOR_APP_INDICATOR_APP_H_ */
