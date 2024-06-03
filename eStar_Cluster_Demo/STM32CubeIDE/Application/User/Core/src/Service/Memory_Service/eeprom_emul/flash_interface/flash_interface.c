/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file flash_interface.c
 *
 * @brief This file provides all the EEPROM emulation flash interface functions.
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
********************************************************************************************** @}*/


/* Define to prevent recursive inclusion -------------------------------------*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "main.h"
#include "../../Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.h"
#include "flash_interface.h"
#include "eeprom_emul.h"
#include "eeprom_emul_cfg.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/


/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
  * @brief  Write a double word at the given address in Flash
  * @param  Address Where to write
  * @param  Data What to write
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_WRITE_ERROR: if an error occurs
  */
int32_t xFI_WriteDoubleWord(uint32_t Address, uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Write Address at 0x%lx \n\r", Address);
#endif
  return BSP_OSPI_NOR_Write(BSP_INSTANCE, Data, Address, EE_DOUBLE_WORD_SIZE);
}



/**
  * @brief  Write a single word at the given address in Flash
  * @param  Address Where to write
  * @param  Data What to write
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_WRITE_ERROR: if an error occurs
  */
int32_t xFI_WriteSingleWord(uint32_t Address, uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Write Address at 0x%lx \n\r", Address);
#endif
  return BSP_OSPI_NOR_Write(BSP_INSTANCE, Data, Address, EE_WORD_SIZE);
}



/**
  * @brief  Write a single byte at the given address in Flash
  * @param  Address Where to write
  * @param  Data What to write
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_WRITE_ERROR: if an error occurs
  */
int32_t xFI_WriteByte(uint32_t Address, uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Write Address at 0x%lx \n\r", Address);
#endif
  return BSP_OSPI_NOR_Write(BSP_INSTANCE, Data, Address, 1);
}



/**
  * @brief  Read a double word at the given address in Flash
  * @param  Address Where to read
  * @param  Data What to read
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_READ_ERROR: if an error occurs
  */
int32_t xFI_ReadDoubleWord(uint32_t Address,  uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Read Address at 0x%lx \n\r", Address);
#endif
	return BSP_OSPI_NOR_Read(BSP_INSTANCE,Data, Address, EE_DOUBLE_WORD_SIZE);
}


/**
  * @brief  Read a single word at the given address in Flash
  * @param  Address Where to read
  * @param  Data What to read
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_READ_ERROR: if an error occurs
  */
int32_t xFI_ReadSingleWord(uint32_t Address,  uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Read Address at 0x%lx \n\r", Address);
#endif
	return BSP_OSPI_NOR_Read(BSP_INSTANCE,Data, Address, EE_WORD_SIZE);
}

/**
  * @brief  Read a single byte at the given address in Flash
  * @param  Address Where to read
  * @param  Data What to read
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_READ_ERROR: if an error occurs
  */
int32_t xFI_ReadByte(uint32_t Address,  uint8_t *Data)
{
#if(EMUL_DEBUG_ENABLE == 1)
//	printf("Read Address at 0x%lx \n\r", Address);
#endif
	return BSP_OSPI_NOR_Read(BSP_INSTANCE,Data, Address, 1);
}


/**
	  * @brief  Erase a memory page from given address in Flash
	  * @param  Address Page erase start address
	  * @retval EE_Status
	  *           - EE_OK: on success
	  *           - EE_ERROR: if an error occurs
	  */
int32_t xFI_PageErase(uint32_t Address)
{
  return BSP_OSPI_NOR_Erase_Block(BSP_INSTANCE, Address, BSP_OSPI_NOR_ERASE_4K);
}


/**************************************************************************************************
 * End Of File
***************************************************************************************************/
