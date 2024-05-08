/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file flash_interface.h
 *
 * @brief This file provides all prototypes of flash interface.
 *
 * File Short Name: flash_interface
 *
 * @author: DEVIDRAJ.K
 *
 * @date: 4th April 2024
 *
 * @copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
***************************************************************************************************/
#ifndef FLASH_INTERFACE_H_   /* Guard against multiple inclusion */
#define FLASH_INTERFACE_H_

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

int32_t xFI_WriteDoubleWord(uint32_t Address, uint8_t *Data);
int32_t xFI_ReadDoubleWord(uint32_t Address,  uint8_t *Data);
int32_t xFI_PageErase(uint32_t Address);

#endif /* FLASH_INTERFACE_H_ */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
