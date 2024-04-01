/**
  ******************************************************************************
  * @file    EEPROM_Emulation/inc/eeprom.h 
  * @author  DEVIDRAJ.K
  * @brief   This file contains all the functions prototypes for the EEPROM 
  *          emulation firmware library.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "eeprom_cfg.h"
#include "STM32H735xx.H"

/* Exported constants --------------------------------------------------------*/

/* EEPROM emulation firmware error codes */
//#define EE_OK      				(uint32_t)HAL_OK
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

#define EEPROM_START_ADDRESS  		EE_FLASH_BASE_ADDR /* sector0 of bank 1 */

#define EEPROM_OFFSET 		  		EEPROM_START_ADDRESS

#define NB_MAX_ELEMENTS_BY_PAGE 	((PAGE_SIZE - PAGE_HEADER_SIZE) / EE_ELEMENT_SIZE) /*!< Max number of elements by page *///506//
#define NB_MAX_WRITTEN_ELEMENTS    	((NB_MAX_ELEMENTS_BY_PAGE * PAGES_NUMBER) / 2U)  /*!< Max number of elements written before triggering pages transfer */
#define PAGES_NUMBER				(NB_TOTAL_WRITES/(CYCLES_NUMBER *NB_MAX_ELEMENTS_BY_PAGE)+1U)  /*!< Number of consecutive pages used by the application */
#define NB_TOTAL_WRITES				(NB_OF_WRITES * NB_OF_VARIABLES) /* Number of total writes used in entire application life time */
#define EMPTY_BYTES_FOR_PAGE		4U  /* Number of bytes wasted for page */

//#define REQUIRED_PAGES				PAGES_NUMBER/EE_TOTAL_ERASE_CYCLES
#define START_PAGE_ADDRESS 		 	(uint32_t)(0x90000000U) /*!< Start address of the 1st page in flash, for EEPROM emulation */
#define BANK_SIZE					(uint32_t)(PAGES_NUMBER * PAGE_SIZE)/* Flash Bank Size*/
#define PAGE(__ADDRESS__)       	(uint32_t)((((__ADDRESS__) - FLASH_BASE) % BANK_SIZE) / FLASH_PAGE_SIZE) /*!< Get page index from page address */
#define PAGE_ADDRESS(__PAGE__)  	(uint32_t)(FLASH_BASE + (__PAGE__) * PAGE_SIZE + ((START_PAGE_ADDRESS - FLASH_BASE) / BANK_SIZE) * BANK_SIZE) /*!< Get page address from page index */
#define PREVIOUS_PAGE(__PAGE__)  	(uint32_t)((((__PAGE__) - START_PAGE - 1U + PAGES_NUMBER) % PAGES_NUMBER) + START_PAGE) /*!< Get page index of previous page, among circular page list */
#define FOLLOWING_PAGE(__PAGE__) 	(uint32_t)((((__PAGE__) - START_PAGE + 1U) % PAGES_NUMBER) + START_PAGE) /*!< Get page index of following page, among circular page list */
#define START_PAGE             		PAGE(START_PAGE_ADDRESS)                         /*!< Page index of the 1st page used for EEPROM emul, in the bank */
#define CALCULATED_END_ADDRESS		(EEPROM_START_ADDRESS + BANK_SIZE)

/* Page state header */
#define EE_PAGESTAT_ERASED      	(uint64_t)0xFFFFFFFFFFFFFFFFU  /*!< State saved in 1st,2nd,3rd,4th data type of page header */
#define EE_PAGESTAT_RECEIVE     	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 1st data type of page header */
#define EE_PAGESTAT_ACTIVE      	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 2nd data type of page header */
#define EE_PAGESTAT_VALID       	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 3rd data type of page header */
#define EE_PAGESTAT_ERASING     	(uint64_t)0xAAAAAAAAAAAAAAAAU  /*!< State saved in 4th data type of page header */


/* Description of the 8 Bytes (64 bits) element in flash   */
/* Bit:  63                  32  31      16  15         0  */
/*       <--- Data Value ----->  <-unused->  <-VirtAddr->  */
//#define EE_ELEMENT_SIZE         8U                            /*!< Size of element in Bytes */
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


/* Macros to manipulate elements */
#define EE_VIRTUALADDRESS_VALUE(__ELEMENT__)            (EE_VIRTUALADDRESS_TYPE)((__ELEMENT__) & EE_MASK_VIRTUALADDRESS) /*!< Get virtual address value from element value */
#define EE_DATA_VALUE(__ELEMENT__)                      (EE_DATA_TYPE)((__ELEMENT__) & EE_MASK_DATA)  /*!< Get Data value from element value */
#define EE_ELEMENT_VALUE(__VIRTADDR__,__DATA__) 		(((EE_ELEMENT_TYPE)(__DATA__) << EE_DATA_SHIFT) | (__VIRTADDR__)) /*!< Get element value from data, virtual addrvalues */


/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void vEEpromDemoFunc(void);
#endif /* __EEPROM_H */

