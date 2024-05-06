/*
 * DriverInfoApp.h
 *
 *  Created on: Apr 4, 2024
 *      Author: dhana
 */

#ifndef APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_
#define APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_

#include "stdbool.h"

//#define FUELTANKCAPACITY 40
//#define MAXIMUMDTE AverageFuelEconomy * FUELTANKCAPACITY
//#define GetFuellevel() AverageFuelEconomy
//#define BLINK_THRESHOLD_LOW 50
//#define BLINK_THRESHOLD_HIGH > MaxThresholdDTE
//#define MIN_DISPLAYED_DTE 5
//#define MAX_DISPLAYED_DTE 20

void vCalculateAvsAfeRange(void);
uint16_t vCalculateAVSInKmperhour(void);
uint16_t vCalculateAFEKmperLitre(void);
uint16_t vCalculateDTE(void);
uint8_t Convertintolitres(uint8_t Fuel_ConsumedinPer);
//void vReadOdoValues(void);
void DisplayDTE(bool flag,uint16_t displayed_DTE);
//driverInfoModeStatus_t xGetInfostatus(void);
//extern uint8_t xGetOdoReadings(void);
//extern uint8_t xGet_FuelLevel(void);

//driverInfoModeStatus_t xGetInfostatus(void);
//
//typedef struct{
//	uint16_t AverageVehicleSpeed;
//	uint16_t AverageFuelEconomy;
//	uint16_t DistanceToEmpty;
//}driverInfoModeStatus_t;
//
//driverInfoModeStatus_t  ModeStatus;

void xGetInfostatus(uint16_t *avgVehicleSpeed, uint16_t *avgFuelEconomy, uint16_t *displayedDTE);


#endif /* APPLICATION_USER_CORE_SRC_APP_DRIVERINFO_APP_DRIVERINFOAPP_H_ */
