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

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define ServiceRequest_TestMacro 1
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
extern void prvServiceRequestTask(void)
void vGetSrvcReqStatus(IndicationStatus_t* pucSrvcReq_Indictr, bool* p_Warning_status_bool);
extern void checkServiceRequest(uint32_t totalDistance, RTC_DateTypeDef xTime);
void resetServiceFlags(void);

#endif /* SERVICEREQUEST_APP_H */
