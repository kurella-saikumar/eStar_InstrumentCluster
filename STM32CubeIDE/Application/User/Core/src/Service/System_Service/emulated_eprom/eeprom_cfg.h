/*
 * eeprom_emul_cfg.h
 *
 * Created on	: Mar 23, 2024
 * @author		: DEVIDRAJ.K
 */

#ifndef INC_EEPROM_EMUL_CFG_H_
#define INC_EEPROM_EMUL_CFG_H_

/* Exported variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Flash base address and end addresses */
#define FLASH_BASE_ADDR      		(uint32_t)(0x90000000U)			/* Ospi NOR FLash Base Address */
#define FLASH_END_ADDR       		(uint32_t)(0x93FFFFFFU) 		/* 64 MegaBytes */

#define EE_FLASH_BASE_ADDR      	FLASH_BASE_ADDR
#define EE_FLASH_SECTOR_SIZE 		4096U 							/* 4096Bytes //BSP_OSPI_NOR_BLOCK_4K */
#define CYCLES_NUMBER           	100000U  				 		/*!< Number of Erase/Write cycles given by manufacturer*/
#define NB_OF_VARIABLES         	100U  							/*!< Number of variables to handle in eeprom */
#define NB_OF_WRITES				1600000U 						/* Number of writes required by each variable */


/* Page Header status*/
#define EE_ELEMENT_SIZE         	10U                         	 /*!< Size of element in Bytes */
#define EE_HEADER_ELEMENT_SIZE      8U                          	 /*!< Size of element in Bytes */
#define PAGE_HEADER_SIZE       		EE_HEADER_ELEMENT_SIZE * 4U      /*!< Page Header is 4 elements to save page state */ //32Bytes//

//#define EE_PAGE_HEADER_IN_BYTES 8U

#endif /* INC_EEPROM_EMUL_CFG_H_ */
