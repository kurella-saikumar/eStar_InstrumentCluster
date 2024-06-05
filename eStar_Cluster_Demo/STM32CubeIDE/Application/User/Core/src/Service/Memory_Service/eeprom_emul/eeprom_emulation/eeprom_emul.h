/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file eeprom_emul.h
 *
 * @brief This file contains all the functions prototypes for the EEPROM emulation firmware library.
 *
 * File Short Name: eeprom_emul
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
#ifndef __EEPROM_H   /* Guard against multiple inclusion */
#define __EEPROM_H

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "eeprom_emul_cfg.h"
#include "STM32H735xx.H"
/**************************************************************************************************
 * DEFINE GLOBAL SCOPE MACROS
***************************************************************************************************/
/* EEPROM emulation firmware error codes */
#define EE_ERROR   					(uint32_t)HAL_ERROR
#define EE_BUSY    					(uint32_t)HAL_BUSY
#define EE_TIMEOUT 					(uint32_t)HAL_TIMEOUT

/* Define the size of the sectors to be used */
#define PAGE_SIZE              		EE_FLASH_SECTOR_SIZE  /* Page size = Sub Sector Size, 4KByte */
#define FLASH_PAGE_SIZE				PAGE_SIZE

/* Device voltage range supposed to be [2.7V to 3.6V], the operation will 
   be done by word  */
#define VOLTAGE_RANGE           	(uint8_t)VOLTAGE_RANGE_3

/* EEPROM emulation start address in Flash */
#define START_PAGE_ADDRESS 		  	EE_EMULATION_START_ADDR/*!< Start address of the 1st page in flash, for EEPROM emulation */

//#define EEPROM_START_ADDRESS  		EE_FLASH_BASE_ADDR /* sector0 of bank 1 */
#define NB_MAX_ELEMENTS_BY_PAGE 	((PAGE_SIZE - PAGE_HEADER_SIZE) / EE_ELEMENT_SIZE) /*!< Max number of elements by page *///506//
#define NB_MAX_WRITTEN_ELEMENTS   	((NB_MAX_ELEMENTS_BY_PAGE * PAGES_NUMBER) / 2U)  /*!< Max number of elements written before triggering pages transfer */
#define NB_TOTAL_WRITES				(NB_OF_WRITES * NB_OF_VARIABLES) /* Number of total writes used in entire application life time */
#define NB_OF_PAGES  				((NB_TOTAL_WRITES/(CYCLES_NUMBER *NB_MAX_ELEMENTS_BY_PAGE))+1)
#define PAGES_NUMBER				((NB_OF_PAGES)+(NB_OF_PAGES%2))  /*!< Number of consecutive pages used by the application */
#define EMPTY_BYTES_FOR_PAGE 		(uint32_t)((EE_FLASH_SECTOR_SIZE - PAGE_HEADER_SIZE)% EE_ELEMENT_SIZE) /*4U Number of bytes wasted for page */
#define BANK_SIZE					(uint32_t)(PAGES_NUMBER * PAGE_SIZE)/* Flash Bank Size*/
#define PAGE(__ADDRESS__)       	(uint32_t)((((__ADDRESS__)) % BANK_SIZE) / FLASH_PAGE_SIZE) /*!< Get page index from page address */
#define PAGE_ADDRESS(__PAGE__)  	(uint32_t)( (__PAGE__) * PAGE_SIZE + ((START_PAGE_ADDRESS) / BANK_SIZE) * BANK_SIZE) /*!< Get page address from page index */
#define PREVIOUS_PAGE(__PAGE__)  	(uint32_t)((((__PAGE__) - START_PAGE - 1U + PAGES_NUMBER) % PAGES_NUMBER) + START_PAGE) /*!< Get page index of previous page, among circular page list */
#define FOLLOWING_PAGE(__PAGE__) 	(uint32_t)((((__PAGE__) - START_PAGE + 1U) % PAGES_NUMBER) + START_PAGE) /*!< Get page index of following page, among circular page list */
#define START_PAGE             		PAGE(START_PAGE_ADDRESS)                         /*!< Page index of the 1st page used for EEPROM emul, in the bank */
#define CALCULATED_END_ADDRESS		(START_PAGE_ADDRESS+ BANK_SIZE)          /*Calculated end address*/
#define PAGE_GROUP					PAGES_NUMBER / 2U		/* Page Group */
/* Page state header */
#define EE_PAGESTAT_ERASED      	(uint64_t)0xFFFFFFFFFFFFFFFFU  /*!< State saved in 1st,2nd,3rd,4th data type of page header */
#define EE_PAGESTAT_RECEIVE     	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 1st data type of page header */
#define EE_PAGESTAT_ACTIVE      	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 2nd data type of page header */
#define EE_PAGESTAT_VALID       	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 3rd data type of page header */
#define EE_PAGESTAT_ERASING     	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 4th data type of page header */

/* Description of the 10 Bytes (80 bits) element in flash   */
/* Bit:  0                  31  32             	   63  64		    80		*/
/*       <--- Data Value ---->  <---- VirtAddr ----->  <---  CRC --->		*/
#define EE_ELEMENT_TYPE        		uint64_t                      /*!< Type of element */
#define EE_VIRTUALADDRESS_TYPE  	uint32_t                      /*!< Type of Virtual Address */
#define EE_VIRTUALADDRESS_SHIFT 	0U                            /*!< Bits Shifting to get Virtual Address in element */
#define EE_CRC_TYPE             	uint16_t                      /*!< Type of Crc */
#define EE_CRC_SHIFT            	16U                           /*!< Bits Shifting to get Crc in element */
#define EE_DATA_TYPE            	uint32_t                      /*!< Type of Data */
#define EE_DATA_SHIFT           	32U                           /*!< Bits Shifting to get Data value in element */
#define EE_MASK_VIRTUALADDRESS  	(uint64_t)0x00000000FFFFFFFFU
#define EE_MASK_DATA            	(uint64_t)0xFFFFFFFF00000000U
#define EE_MASK_FULL            	(uint64_t)0xFFFFFFFFFFFFFFFFU
#define EE_NO_PAGE_FOUND      		(uint32_t)0xFFFFFFFFU
#define EE_NO_DATA_FOUND			(uint32_t)0xFFFFFFFFU
#define EE_WORD_SIZE				2U
#define EE_DOUBLE_WORD_SIZE			(EE_WORD_SIZE *2U)
#define EE_ADDRESS_OFFSET			4U
#define EE_CRC_OFFSET				8U
/* Macros to manipulate elements */
#define EE_VIRTUALADDRESS_VALUE(__ELEMENT__)            (EE_VIRTUALADDRESS_TYPE)((__ELEMENT__) & EE_MASK_VIRTUALADDRESS) /*!< Get virtual address value from element value */
#define EE_DATA_VALUE(__ELEMENT__)                      (EE_DATA_TYPE)((__ELEMENT__) & EE_MASK_DATA)  /*!< Get Data value from element value */
#define EE_ELEMENT_VALUE(__VIRTADDR__,__DATA__) 	    (((EE_ELEMENT_TYPE)(__DATA__) << EE_DATA_SHIFT) | (__VIRTADDR__)) /*!< Get element value from data, virtual addrvalues */


/**************************************************************************************************
 * DEFINE GLOBAL SCOPE TYPES
***************************************************************************************************/
typedef enum {
    /* External return codes : ok */
    EE_OK= 0U,
    /* External return codes : errors */
    EE_ERASE_ERROR,
    EE_WRITE_ERROR,
    EE_ERROR_NOACTIVE_PAGE,
    EE_ERROR_NOERASE_PAGE,
    EE_ERROR_NOERASING_PAGE,
    EE_ERROR_NOACTIVE_NORECEIVE_NOVALID_PAGE,
    EE_NO_DATA,
    EE_INVALID_VIRTUALADDRESS,
    EE_INVALID_PAGE,
    EE_INVALID_PAGE_SEQUENCE,
    EE_INVALID_ELEMENT,
    EE_TRANSFER_ERROR,
    EE_DELETE_ERROR,
    EE_INVALID_BANK_CFG,
    /* Internal return code */
    EE_NO_PAGE_FOUND1,
    EE_PAGE_NOTERASED,
    EE_PAGE_ERASED,
    EE_PAGE_FULL,
    /* External return code : action required */
    EE_CLEANUP_REQUIRED = 0x100U,
    EE_MEMORY_NOT_SUFFICIENT,
    EE_READ_DATA_INVALID
} EE_Status;

/* Type of page erasing:
    EE_FORCED_ERASE     --> pages to erase are erased unconditionally
    EE_CONDITONAL_ERASE --> pages to erase are erased only if not fully erased
*/
typedef enum {
    EE_FORCED_ERASE,
    EE_CONDITIONAL_ERASE
} EE_Erase_type;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE GLOBAL SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
//EE_Status EE_Format(EE_Erase_type EraseType);
EE_Status xEE_Init(EE_Erase_type EraseType);
EE_Status xEE_ReadVariable32bits(uint32_t VirtAddress, uint32_t* pData);
EE_Status xEE_WriteVariable32bits(uint32_t VirtAddress, uint32_t Data);

extern uint16_t xES_WriteVariable(uint32_t VirtAddress, uint32_t Data,uint32_t *UpdateToShadowRAM);
extern void vShadowRAM_Init(void);
extern void vEE_Demo(void);
uint32_t xShadowUpdate(void);
#endif /* __EEPROM_H */

/**************************************************************************************************
 * End Of File
********************************************************************************************** @}*/
