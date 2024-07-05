/*
 * DriverInfoApp_cfg.h
 *
 *  Created on: Apr 30, 2024
 *      Author: dhana
 */

#ifndef DRIVERINFOAPP_CFG_H
#define DRIVERINFOAPP_CFG_H

#define SECONDS_TO_HOURS_FACTOR 		3600  	/*This factor refers seconds to hours conversion factor( 1 hour = 3600seconds)*/
#define NO_OF_SAMPLES 					5	  	/*This refers the number of collected Average speed samples*/
#define DELTA_TIME						5	  	/*The time taken to calculate average speed*/
#define FUEL_TANK_CAPACITY 				40	  	/*The Total Capacity of Fuel Tank */
#define BLINK_THRESHOLD_LOW 			50	  	/*The DTE MINIMUM THRESHOLD Limit*/
#define MIN_DISPLAYED_DTE 				5	  	/*The DTE MINIMUM  Limit*/
#define MAX_DISPLAYED_DTE 				20	  	/*The DTE MAXIMUM Limit*/
#define IDLE_VEHICLE_MILEAGE 			20	  	/*The vehicle possible efficiency*/
#define MULTIPLICATION_FACTOR			10    	/*This is multiplication factor which is used to calculate usMaxThresholdDTE */
#define usMaxThresholdDTE  				(FUEL_TANK_CAPACITY * IDLE_VEHICLE_MILEAGE * MULTIPLICATION_FACTOR) /*The DTE MAXIMUM THRESHOLD Limit .Here (40 * 20 * 10 = 8000) but usMaxThresholdDTE value should be within the 800.0 threshold  */

#define DEFAULT_AFE 					15.0	/*Manufacturer-provided value*/

#define FINAL_FUEL_PERCENTAGE 			100		/*Initial fuel level in Percentages*/

#define FINAL_FUEL_LEVEL 				40.0	/*Initial fuel level in liters*/

#define WINDOW_SIZE						5		/*The number of samples taken to calculate Moving Average of Distance and Fuel values*/




#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_CFG_H_ */
