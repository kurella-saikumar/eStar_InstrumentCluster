/** \addtogroup  checksum
 *  @{
 * @file checksum.h
 *
 * @brief checksum file is to calculate checksum
 *
 * File Short Name: checksum
 *
 * Author: Madhavi Manthri
 *
 * Create Date: 21-11-2023
 *
  * Copyright:  All information contained herein is, and remains the property of
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * TEST BASE SOLUTION(TBS) PRIVATE LIMITED
***************************************************************************************************/
#ifndef SRC_CHECKSUM_H_
#define SRC_CHECKSUM_H_
/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "main.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
typedef uint16_t resultType;

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
#define DEFAULT_CHECKSUM ((resultType)0)

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES
***************************************************************************************************/
resultType xCrc16BitPolinomial_1021(const uint8_t * pucData, uint32_t ulDataSize, resultType uxRemainder);

#endif /* SRC_CHECKSUM_H_ */
/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/

