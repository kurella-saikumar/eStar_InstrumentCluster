/******************************************************************************************
 * Feature Name: ServiceRequest_App.h
 *
 * Feature Short Name: ServiceRequest_App
 *
 * Description:
 *
 * Author: Kuella Saikumar
 *
 * Create Date: 8th-April-2024
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 *****************************************************************************************/

#ifndef SERVICEREQUEST_APP_H
#define SERVICEREQUEST_APP_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stdbool.h"
#include "Indicator_app.h"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define ServiceRequest_TestMacro 0
#define TimeBasedServiceDemo 0
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern void vServiceRequestTask(void);
extern void vServiceRequestTask_Init(void);
void vGetSrvcReqStatus(IndicationStatus_t* pucSrvcReq_Indictr, bool* p_Warning_status_bool);
void vRTCDemoApp(void);

#endif /* SERVICEREQUEST_APP_H */
