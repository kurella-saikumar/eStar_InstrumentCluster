/*
 * DriverInfoApp_cfg.h
 *
 *  Created on: Apr 30, 2024
 *      Author: dhana
 */

#ifndef APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_CFG_H_
#define APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_CFG_H_

#define SecondsToHoursFactor 3600
#define NoOfSpeedSamples 5
#define fueltankcapacity 40
#define BLINK_THRESHOLD_LOW 50
#define MIN_DISPLAYED_DTE 5
#define MAX_DISPLAYED_DTE 20
#define IDLE_VEHICLE_MILEAGE 20
#define usMaxThresholdDTE  fueltankcapacity * IDLE_VEHICLE_MILEAGE
//Manufacturer-provided value
#define DEFAULT_AFE 15.0
// Initial fuel level in Percentages
#define FINAL_FUEL_PERCENTAGE 100
// Initial fuel level in liters
#define FINAL_FUEL_LEVEL 40.0




#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_CFG_H_ */
