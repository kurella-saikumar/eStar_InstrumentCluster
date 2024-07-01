/*
 * DriverInfoApp_cfg.h
 *
 *  Created on: Apr 30, 2024
 *      Author: dhana
 */

#ifndef DRIVERINFOAPP_CFG_H
#define DRIVERINFOAPP_CFG_H

#define SECONDS_TO_HOURS_FACTOR 		3600
#define NO_OF_SAMPLES 					5
#define FUEL_TANK_CAPACITY 				40
#define BLINK_THRESHOLD_LOW 			50
#define MIN_DISPLAYED_DTE 				5
#define MAX_DISPLAYED_DTE 				20
#define IDLE_VEHICLE_MILEAGE 			20
#define usMaxThresholdDTE  				FUEL_TANK_CAPACITY * IDLE_VEHICLE_MILEAGE

#define DEFAULT_AFE 					15.0	//Manufacturer-provided value

#define FINAL_FUEL_PERCENTAGE 			100		// Initial fuel level in Percentages

#define FINAL_FUEL_LEVEL 				40.0	// Initial fuel level in liters

#define WINDOW_SIZE						5




#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_CFG_H_ */
