/** \addtogroup CODE_TEMPLATE
 *  @{
 * @file eeprom_emul.c
 *
 * @brief This file provides all the EEPROM emulation firmware functions.
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
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/
#include "stdio.h"
#include "string.h"
/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "eeprom_emul.h"
#include "stm32h735g_discovery_ospi.h"
#include "eeprom_emul_cfg.h"
#include "checksum.h"
#include "flash_interface.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/
/* Type of state requested :
        ERASED  --> page is erased
        RECEIVE --> page used during data transfer when no more space available in the system
        ACTIVE  --> page contains valid data and is not full
        VALID   --> page contains valid data and is full
        ERASING --> page used during transfer, should be erased after transfer
        INVALID --> page invalid state */
typedef enum {
    STATE_PAGE_ERASED,
    STATE_PAGE_RECEIVE,
    STATE_PAGE_ACTIVE,
    STATE_PAGE_VALID,
    STATE_PAGE_ERASING,
    STATE_PAGE_INVALID
} EE_State_type;

/* Type of find requested :
        READ  --> page in active state
        WRITE --> page in receive state or active state
        ERASE --> page in erased state */
typedef enum {
    FIND_READ_PAGE,
    FIND_WRITE_PAGE,
    FIND_ERASE_PAGE
} EE_Find_type;


/* Definition of the different type of page transfer
        NORMAL  -> copy data page source to page destination
        RECOVER -> resume page transfer that has been interrupted */
typedef enum {
    EE_TRANSFER_NORMAL,
    EE_TRANSFER_RECOVER
} EE_Transfer_type;


/* Reliability of page state:
        RELIABLE  -> header of page is not corrupted, state is reliable
        CORRUPTED -> header of page is corrupted, state is corrupted */
typedef enum {
    STATE_RELIABLE,
    STATE_CORRUPTED
} EE_State_Reliability;

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES\n
***************************************************************************************************/
uint16_t usNbWrittenElements = 0U;                 					/*!< Nb of elements written in valid and active pages */
uint8_t ucCurrentActivePage = 0U;                  					/*!< Current active page (can be active or receive state) */
uint32_t ulAddressNextWrite = ((0x00000000)+(PAGE_HEADER_SIZE));    /*!< Initialize write position just after page header */

/**************************************************************************************************
 * DECLARE FILE STATIC VARIABLES\n
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE FUNCTION PROTOTYPES\n
***************************************************************************************************/
EE_Status prvEE_Format(EE_Erase_type EraseType);
EE_Status xEE_Init(EE_Erase_type EraseType);
EE_Status xEE_ReadVariable32bits(uint32_t VirtAddress, uint32_t* pData);
EE_Status xEE_WriteVariable32bits(uint32_t VirtAddress, uint32_t Data);
EE_Status prvEE_CleanUp(void);


EE_Status prvReadVariable(uint32_t VirtAddress, EE_DATA_TYPE* pData);
EE_Status prvWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data);
EE_Status prvPagesTransfer (uint32_t VirtAddress, EE_DATA_TYPE Data, EE_Transfer_type Type);
EE_Status prvVerifyPageFullyErased(uint32_t Address, uint32_t PageSize);
uint32_t prvFindPage(EE_Find_type Operation);
EE_Status prvVerifyPagesFullWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data);
EE_Status prvSetPageState(uint32_t Page, EE_State_type State);
EE_State_type prvGetPageState(uint32_t Address);
/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/

/**
  * @brief  Erases PAGE and PAGE1 and writes VALID_PAGE header to PAGE
  * @param  None
  * @retval Status of the last operation (Flash write or erase) done during
  *         EEPROM formatting
  */

EE_Status prvEE_Format(EE_Erase_type EraseType)
{
  uint32_t ulPage = 0U;

  /* Erase All Pages */
  for (ulPage = START_PAGE; ulPage < (START_PAGE + PAGES_NUMBER); ulPage++)
   {
		if (EraseType == EE_FORCED_ERASE)
		{
			if (xFI_PageErase(PAGE_ADDRESS(ulPage)-START_PAGE_ADDRESS + EE_EMULATION_START_ADDR)!= EE_OK)
			{
				return EE_ERASE_ERROR;
			}
		}
		else /* EraseType == EE_CONDITIONAL_ERASE */
		{
			/* Check if Page is not yet fully erased */
			if (prvVerifyPageFullyErased(PAGE_ADDRESS(ulPage), PAGE_SIZE) == EE_PAGE_NOTERASED)
			{
				/* Erase the page */
				/* If Erase operation was failed, a Flash error code is returned */
				if (xFI_PageErase(PAGE_ADDRESS(ulPage))!= EE_OK)
				{
					return EE_ERASE_ERROR;
				}
			}
		}
   }

	/* Set first Page in Active State */
	/* If program operation was failed, a Flash error code is returned */
    if (prvSetPageState(START_PAGE, STATE_PAGE_ACTIVE) != EE_OK)
    {
      return EE_WRITE_ERROR;
    }

    /* Reset global variables */
    usNbWrittenElements = (uint16_t)0U;
    ucCurrentActivePage = START_PAGE;
    ulAddressNextWrite = PAGE_HEADER_SIZE; /* Initialize write position just after page header */

 return EE_OK;
}



/**
  * @brief  Returns the last stored variable data, if found, which correspond to
  *         the passed virtual address
  * @param VirtAddress Variable virtual address on 32 bits (can't be 0x00000000 or 0xFFFFFFFF)
  * @param  pData Variable containing the 32bits read variable value
  * @retval EE_Status
  *           - EE_OK: if variable was found
  *           - EE error code: if an error occurs
  */
EE_Status xEE_ReadVariable32bits(uint32_t VirtAddress, uint32_t* pData)
{
  	if((VirtAddress != 0x00000000) && (VirtAddress != 0xFFFFFFFF))
  	{
		EE_DATA_TYPE uldatatmp = 0U;
		EE_Status status = EE_OK;

		/* Read variable of size EE_DATA_TYPE, then cast it to 32bits */
		status = prvReadVariable(VirtAddress, &uldatatmp);
		*pData = uldatatmp;

		return status;
  	}
	else
	{
		return EE_INVALID_VIRTUALADDRESS;
	}
}



/**
  * @brief  Writes/updates variable data in EEPROM.
  *         Trig internal Pages transfer if half of the pages are full.
  * @warning This function is not reentrant
  * @param VirtAddress Variable virtual address on 16 bits (can't be 0x0000 or 0xFFFF)
  * @param  Data 32bits data to be written
  * @retval EE_Status
  *           - EE_OK: on success
  *           - prvEE_CleanUp_REQUIRED: success and user has to trig flash pages cleanup
  *           - EE error code: if an error occurs
  */
EE_Status xEE_WriteVariable32bits(uint32_t VirtAddress, uint32_t Data)
{
	if((VirtAddress != 0x00000000) && (VirtAddress != 0xFFFFFFFF))
	{
		return prvWriteVariable(VirtAddress, (EE_DATA_TYPE) Data);
	}
	else
	{
		return EE_INVALID_VIRTUALADDRESS;
	}
}



/**
  * @brief  Get page state in page header
  * @param  Address Address of the FLASH Memory page
  * @retval State State of the page
  */

 EE_State_type prvGetPageState(uint32_t Address)
{
	EE_ELEMENT_TYPE status1 = 0U, status2 = 0U, status3 = 0U, status4 = 0U;

	uint8_t ucHeader_Receive_FirstWord[4] = {0x00};
	uint8_t ucHeader_Receive_SecondWord[4] = {0x00};
	uint8_t ucHeader_Active_FirstWord[4] = {0x00};
	uint8_t ucHeader_Active_SecondWord[4] = {0x00};
	uint8_t ucHeader_Valid_FirstWord[4] = {0x00};
	uint8_t ucHeader_Valid_SecondWord[4] = {0x00};
	uint8_t ucHeader_Erasing_FirstWord[4] = {0x00};
	uint8_t ucHeader_Erasing_SecondWord[4] = {0x00};

	uint32_t ulHeader_Receive_FirstWord=0;
	uint32_t ulHeader_Receive_SecondWord=0;
	uint32_t ulHeader_Active_FirstWord=0;
	uint32_t ulHeader_Active_SecondWord=0;
	uint32_t ulHeader_Valid_FirstWord=0;
	uint32_t ulHeader_Valid_SecondWord=0;
	uint32_t ulHeader_Erasing_FirstWord=0;
	uint32_t ulHeader_Erasing_SecondWord=0;


  	/* Get page state information from page header (3 first elements) */

	if(HAL_OK != xFI_ReadDoubleWord(((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR), ucHeader_Receive_FirstWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Receive_FirstWord = (ucHeader_Receive_FirstWord[0]<<24|ucHeader_Receive_FirstWord[1]<<16|ucHeader_Receive_FirstWord[2]<<8|ucHeader_Receive_FirstWord[0]);

	if(HAL_OK != xFI_ReadDoubleWord(((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR+4U), ucHeader_Receive_SecondWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Receive_SecondWord = (ucHeader_Receive_SecondWord[0]<<24|ucHeader_Receive_SecondWord[1]<<16|ucHeader_Receive_SecondWord[2]<<8|ucHeader_Receive_SecondWord[0]);

	/* Combine the two 4bytes to form the Header element 8 byte(64-bit value)*/
	status1 = ((uint64_t)ulHeader_Receive_SecondWord << 32) | ulHeader_Receive_FirstWord;


	if(HAL_OK != xFI_ReadDoubleWord(((Address-START_PAGE_ADDRESS) +EE_EMULATION_START_ADDR+ EE_HEADER_ELEMENT_SIZE), ucHeader_Active_FirstWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Active_FirstWord = (ucHeader_Active_FirstWord[0]<<24|ucHeader_Active_FirstWord[1]<<16|ucHeader_Active_FirstWord[2]<<8|ucHeader_Active_FirstWord[0]);

	if(HAL_OK != xFI_ReadDoubleWord((((Address-START_PAGE_ADDRESS) +EE_EMULATION_START_ADDR+ EE_HEADER_ELEMENT_SIZE)+4U), ucHeader_Active_SecondWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Active_SecondWord = (ucHeader_Active_SecondWord[0]<<24|ucHeader_Active_SecondWord[1]<<16|ucHeader_Active_SecondWord[2]<<8|ucHeader_Active_SecondWord[0]);

	/* Combine the two 4bytes to form the Header element 8 byte(64-bit value)*/
	status2 = ((uint64_t)ulHeader_Active_SecondWord << 32) | ulHeader_Active_FirstWord;


	if(HAL_OK != xFI_ReadDoubleWord(((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR + (EE_HEADER_ELEMENT_SIZE*2U)),ucHeader_Valid_FirstWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Valid_FirstWord =(ucHeader_Valid_FirstWord[0]<<24|ucHeader_Valid_FirstWord[1]<<16|ucHeader_Valid_FirstWord[2]<<8|ucHeader_Valid_FirstWord[0]);


	if(HAL_OK != xFI_ReadDoubleWord((((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR + (EE_HEADER_ELEMENT_SIZE*2U))+4U),ucHeader_Valid_SecondWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Valid_SecondWord = (ucHeader_Valid_SecondWord[0]<<24|ucHeader_Valid_SecondWord[1]<<16|ucHeader_Valid_SecondWord[2]<<8|ucHeader_Valid_SecondWord[0]);

	/* Combine the two 4bytes to form the Header element 8 byte(64-bit value)*/
	status3 = ((uint64_t)ulHeader_Valid_SecondWord << 32) | ulHeader_Valid_FirstWord;


	if(HAL_OK != xFI_ReadDoubleWord(((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR + (EE_HEADER_ELEMENT_SIZE*3U)),ucHeader_Erasing_FirstWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Erasing_FirstWord = (ucHeader_Erasing_FirstWord[0]<<24|ucHeader_Erasing_FirstWord[1]<<16|ucHeader_Erasing_FirstWord[2]<<8|ucHeader_Erasing_FirstWord[0]);

	if(HAL_OK != xFI_ReadDoubleWord((((Address-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR + (EE_HEADER_ELEMENT_SIZE*3U))+4U),ucHeader_Erasing_SecondWord))
	{
		return HAL_ERROR;
	}
	ulHeader_Erasing_SecondWord = (ucHeader_Erasing_SecondWord[0]<<24|ucHeader_Erasing_SecondWord[1]<<16|ucHeader_Erasing_SecondWord[2]<<8|ucHeader_Erasing_SecondWord[0]);

	/* Combine the two 4bytes to form the Header element 8 byte(64-bit value)*/
	status4 = ((uint64_t)ulHeader_Erasing_SecondWord << 32) | ulHeader_Erasing_FirstWord;


	/* Return erasing status, if element4 is not EE_PAGESTAT_ERASED value */
	if (status4 != EE_PAGESTAT_ERASED)
	{
		return STATE_PAGE_ERASING;
	}	

	/* Return valid status, if element3 is not EE_PAGESTAT_ERASED value */
	if (status3 != EE_PAGESTAT_ERASED)
	{
		return STATE_PAGE_VALID;
	}

	/* Return active status, if element2 is not EE_PAGESTAT_ERASED value */
	if (status2 != EE_PAGESTAT_ERASED)
	{
		return STATE_PAGE_ACTIVE;
	}

	/* Return receive status, if element1 is not EE_PAGESTAT_ERASED value */
	if (status1 != EE_PAGESTAT_ERASED)
	{
		return STATE_PAGE_RECEIVE;
	}

	/* Return erased status, if 4 first elements are EE_PAGESTAT_ERASED value */
	return STATE_PAGE_ERASED;
}

/**
  * @brief  Set page state in page header
  * @param  Page Index of the page
  * @param  State State of the page
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE error code: if an error occurs
  */
 EE_Status prvSetPageState(uint32_t Page, EE_State_type State)
{
  uint32_t ulHeader1 = 0U;
  uint32_t ulHeader2 = 0U;
  uint32_t ulHeader3 = 0U;
  uint32_t ulHeader4 = 0U;

  uint8_t ucReceive[4] = {0xAA,0xAA,0xAA,0xAA};
  uint8_t ucActive [4]= {0xAA,0xAA,0xAA,0xAA};
  uint8_t ucValid [4]= {0xAA,0xAA,0xAA,0xAA};
  uint8_t ucErasing [4]= {0xAA,0xAA,0xAA,0xAA};

  ulHeader1 = PAGE_ADDRESS(Page);
  ulHeader2 = PAGE_ADDRESS(Page) + EE_HEADER_ELEMENT_SIZE;
  ulHeader3 = PAGE_ADDRESS(Page) + (EE_HEADER_ELEMENT_SIZE*2U);
  ulHeader4 = PAGE_ADDRESS(Page) + (EE_HEADER_ELEMENT_SIZE*3U);

  switch(State)
   {
		case STATE_PAGE_RECEIVE:
			{
			/* Set new Page status to STATE_PAGE_RECEIVE status */

				if (xFI_WriteDoubleWord(((ulHeader1-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR), ucReceive)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}

				if (xFI_WriteDoubleWord(((ulHeader1-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR+EE_ADDRESS_OFFSET), ucReceive)!= HAL_OK)
				{
				return EE_WRITE_ERROR;
				}
				ucCurrentActivePage = Page;
			}
			break;

		case STATE_PAGE_ACTIVE:
			{
				/* Set new Page status to STATE_PAGE_ACTIVE status */
				if (xFI_WriteDoubleWord(((ulHeader2-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR), ucActive)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}

				if (xFI_WriteDoubleWord(((ulHeader2-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR+EE_ADDRESS_OFFSET), ucActive)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}
				ucCurrentActivePage = Page;
			}
			break;

		case STATE_PAGE_VALID:
			{
				/* Set new Page status to STATE_PAGE_VALID status */
				if (xFI_WriteDoubleWord(((ulHeader3-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR), ucValid)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}
				
				if (xFI_WriteDoubleWord(((ulHeader3-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR+EE_ADDRESS_OFFSET), ucValid)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}
			}
			break;

		case STATE_PAGE_ERASING:
			{
				/* Set new Page status to STATE_PAGE_ERASING status */
				if (xFI_WriteDoubleWord(((ulHeader4-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR), ucErasing)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}

				if (xFI_WriteDoubleWord(((ulHeader4-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR+EE_ADDRESS_OFFSET), ucErasing)!= HAL_OK)
				{
					return EE_WRITE_ERROR;
				}
			}
			break;
		default: 
		break;
   }
	/* Return last operation flash status */
	return EE_OK;
}


/**
  * @brief  Erase group of pages which are erasing state.
  *         Could be either first half or second half of total pages number.
  * @retval EE_Status
  *           - EE_OK: in case of success
  *           - EE error code: if an error occurs
  */
EE_Status prvEE_CleanUp(void)
{
  uint32_t ulFirstPage = 0U;
  uint32_t ulPage = 0U;
  uint32_t ulFirstPageAddress = 0U;
  uint32_t ulPageAddress = 0U;
  EE_State_type firstpagestatus = STATE_PAGE_INVALID, pagestatus = STATE_PAGE_INVALID;

  /* Check first half and second half page group */
  for (ulFirstPage = START_PAGE; ulFirstPage < (START_PAGE + PAGES_NUMBER); ulFirstPage += PAGE_GROUP)
  	{
		/* Check status of first page of the group */
		ulFirstPageAddress = PAGE_ADDRESS(ulFirstPage);
		firstpagestatus = prvGetPageState(ulFirstPageAddress);

		/* If first page of the group is erasing state, check that all other pages
		of the group are also erasing state */
		if (firstpagestatus == STATE_PAGE_ERASING)
		{
			for (ulPage = (ulFirstPage + 1U); ulPage < (ulFirstPage + PAGE_GROUP); ulPage++)
			{
				ulPageAddress = PAGE_ADDRESS(ulPage);
				pagestatus = prvGetPageState(ulPageAddress);

				/* If page is not erasing, return error */
				if (pagestatus != STATE_PAGE_ERASING)
				{
					return EE_ERROR_NOERASING_PAGE;
				}
			}

			/* Erase all the pages of the group */
			/* If erase operation fails, a Flash error code is returned */
			for (ulPage = 0; ulPage < ((PAGES_NUMBER *PAGE_SIZE) / 2U); ulPage+=PAGE_SIZE)
			{
				if (xFI_PageErase(((PAGE_ADDRESS(ulFirstPage)+ulPage)-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR)!= EE_OK)
				{
					return EE_ERASE_ERROR;
				}

			}
			return EE_OK;
		}
	}
	/* Error if no erasing pages group is found */
	return EE_ERROR_NOERASING_PAGE;
}


/**
  * @brief  Verify if specified page is fully erased.
  * @param  Address page address
  * @param  PageSize page size
  * @retval EE_Status
  *           - EE_PAGE_NOTERASED : if Page not erased
  *           - EE_PAGE_ERASED    : if Page erased
  */
EE_Status prvVerifyPageFullyErased(uint32_t Address, uint32_t PageSize)
{
  EE_Status readstatus = EE_PAGE_ERASED;
  uint32_t ulCounter = 0U;
  uint64_t addressvalue =0U;
  uint8_t ucReadAddressValue[4]={0};
  uint8_t ucDataValue[4]={0};


  /* Check each element in the page */
  while (ulCounter < PageSize)
	{

		xFI_ReadDoubleWord((Address+ulCounter), ucDataValue);
		xFI_ReadDoubleWord(((Address+ulCounter)+EE_ADDRESS_OFFSET), ucReadAddressValue);

		for (int i = 0; i < 4; i++)
		{
			addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
			addressvalue |= ucDataValue[i]; // Add the byte from DataValue
		}

		for (int i = 0; i < 4; i++)
		{
			addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
			addressvalue |= ucReadAddressValue[i]; // Add the byte from ReadAddressValue
		}

		if (addressvalue!= EE_PAGESTAT_ERASED)
		{
			/* In case one element is not erased, reset readstatus flag */
			readstatus = EE_PAGE_NOTERASED;
		}
			/* Next address location */
		ulCounter = ulCounter + EE_ELEMENT_SIZE;
 	}

  /* Return readstatus value */
  return readstatus;
}

/**
  * @brief  Returns the last stored variable data, if found, which correspond to
  *         the passed virtual address
  * @param VirtAddress Variable virtual address on 16 bits (can't be 0x0000 or 0xFFFF)
  * @param  pData Variable containing the EE_DATA_TYPE read variable value
  * @retval EE_Status
  *           - EE_OK: if variable was found
  *           - EE error code: if an error occurs
  */

EE_Status prvReadVariable(uint32_t VirtAddress, EE_DATA_TYPE* pData)
{
	uint32_t ulPage = 0U;
	uint32_t ulPageAddress = 0U;
	uint32_t ulCounter = 0U ;
	static uint8_t ucReadAddressValue[4] = {0X00,0x00,0x00,0x00};
	static uint8_t ucDataValue[4] = {0x00};
	uint32_t ulReadAddr = 0;
	uint16_t usCRCRead = 0;
	uint8_t ucCRC [2]= {0x00};
	uint16_t usCRCCalculated = 0;
	uint32_t ulData = 0;
	int32_t	slRet=0;

    EE_State_type pagestate = STATE_PAGE_INVALID;

    /* Get active Page for read operation */
    ulPage = prvFindPage(FIND_READ_PAGE);

    /* Check if there is no active page */
    if (ulPage == EE_NO_PAGE_FOUND)
    {
    	return EE_ERROR_NOACTIVE_PAGE;
    }
    ulPageAddress = PAGE_ADDRESS(ulPage);
    pagestate = prvGetPageState(ulPageAddress);

    /* Search variable in active page and valid pages until erased page is found
       or in erasing pages until erased page is found */
    while ((pagestate == STATE_PAGE_ACTIVE) || (pagestate == STATE_PAGE_VALID) || (pagestate == STATE_PAGE_ERASING))
    {
		/* Set counter index to last element position in the page */
		ulCounter = (PAGE_SIZE - EE_ELEMENT_SIZE)- EMPTY_BYTES_FOR_PAGE;

		/* Check each page address starting from end */
		while (ulCounter >= PAGE_HEADER_SIZE)
		{
			/* Get the current location content to be compared with virtual address */
			slRet = xFI_ReadDoubleWord(((ulPageAddress + ulCounter + EE_ADDRESS_OFFSET)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), ucReadAddressValue);
			if(slRet != 0)
			{
				return slRet;
			}
			ulReadAddr = (ucReadAddressValue[0]<<24|ucReadAddressValue[1]<<16|ucReadAddressValue[2]<<8|ucReadAddressValue[3]);

			if (ulReadAddr != 0xFFFFFFFFU)
        	{
				/* Compare the read address with the virtual address */
				if (ulReadAddr == VirtAddress)
				{
					/* Get content of variable value */

					xFI_ReadDoubleWord(((ulPageAddress + ulCounter)+EE_EMULATION_START_ADDR-START_PAGE_ADDRESS), ucDataValue);

					ulData = (ucDataValue[0]<<24|ucDataValue[1]<<16|ucDataValue[2]<<8|ucDataValue[3]);

					usCRCCalculated = xCrc16BitPolinomial_1021(ucDataValue, sizeof(ucDataValue),0);

					xFI_ReadDoubleWord(((ulPageAddress + ulCounter + EE_CRC_OFFSET)+EE_EMULATION_START_ADDR-START_PAGE_ADDRESS), ucCRC);

					usCRCRead = (ucCRC[0]<<8|ucCRC[1]);

					if (usCRCCalculated == usCRCRead)
					{
						*pData = ulData ;
						return EE_OK;
					}
					else
					{
						return EE_READ_DATA_INVALID;
					}
        		}
        	}
        	/* Next address location */
			ulCounter -= EE_ELEMENT_SIZE;
      	}
      	/* Decrement page index circularly, among pages allocated to eeprom emulation */
		ulPage = PREVIOUS_PAGE(ulPage);
		ulPageAddress = PAGE_ADDRESS(ulPage);
		pagestate = prvGetPageState(ulPageAddress);
    }
	/* Variable is not found */
	return EE_NO_DATA;
}


/**
  * @brief  Writes/updates variable data in EEPROM
  *         Trig internal Pages transfer if half of the pages are full
  * @param VirtAddress Variable virtual address on 16 bits (can't be 0x0000 or 0xFFFF)
  * @param  Data EE_DATA_TYPE data to be written
  * @retval EE_Status
  *           - EE_OK: on success, without page transfer
  *           - prvEE_CleanUp_REQUIRED: on success, with page transfer occured
  *           - EE_FLASH_USED: flash currently used by CPU2
  *           - EE error code: if an error occurs
  */

 EE_Status prvWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data)
{
  EE_Status status = EE_OK;

  /* Write the variable virtual address and value in the EEPROM, if not full */
  status = prvVerifyPagesFullWriteVariable(VirtAddress, Data);
  if (status == EE_PAGE_FULL)
    {
      /* In case the EEPROM pages are full, perform Pages transfer */
      return prvPagesTransfer (VirtAddress, Data, EE_TRANSFER_NORMAL);
    }
	/* Return last operation status */
	return status;
}

/**
  * @brief  Find suitable page for read/write/erase operation.
  *   It also update pages state if current page is full.
  *   And it force cleanup if all pages are full.
  * @param  Operation Type of page to be requested.
  *   This parameter can be one of the following values:
  *     @arg @ref FIND_READ_PAGE return the active page index
  *     @arg @ref FIND_WRITE_PAGE return the write page index
  *     @arg @ref FIND_ERASE_PAGE return the erase page index
  * @retval Page_Index
  *           - Page Index: on success
  *           - @ref EE_NO_PAGE_FOUND : if an error occurs
  */
uint32_t prvFindPage(EE_Find_type Operation)
{
  EE_State_type currentpagestatus = STATE_PAGE_INVALID;
  EE_State_type followingpagestatus = STATE_PAGE_INVALID;
  uint32_t ulCurrentPage = 0U;
  uint32_t ulFollowingPage = 0U;
  uint32_t ulPreviousPage = 0U;

  /* Get currentpage status */
  ulCurrentPage = ucCurrentActivePage;
  currentpagestatus = prvGetPageState(PAGE_ADDRESS(ulCurrentPage));

  /* Get followingpage status */
  ulFollowingPage = FOLLOWING_PAGE(ulCurrentPage);
  followingpagestatus = prvGetPageState(PAGE_ADDRESS(ulFollowingPage));

  /* Get previouspage status */
  ulPreviousPage = PREVIOUS_PAGE(ulCurrentPage);

  /* Write, read or erase operation */
  switch (Operation)
	{
		case FIND_WRITE_PAGE:   /* ---- Write operation ---- */

			/* Normal operation, no page transfer on going */
			if (currentpagestatus == STATE_PAGE_ACTIVE)
			{
				/* Check if active page is not full */
				if (ulAddressNextWrite < (PAGE_SIZE - EE_ELEMENT_SIZE))
				{
					/* Return current Active page */
					printf("Writing in %ld Page (Current)\n\r", ulCurrentPage);
					return ulCurrentPage;
				}
				else
				/* No more space in current active page */
				{
					printf("Writing in %ld Page (Following) \n\r", ulFollowingPage);
					/* Check if following page is erasing state */
					if (followingpagestatus == STATE_PAGE_ERASING)
					{
						/* Force Cleanup, as not yet performed by user */
						if (prvEE_CleanUp() != EE_OK)
						{
							return EE_NO_PAGE_FOUND;
						}
					}

					/* Set current active page in valid state */
					if (prvSetPageState(ulCurrentPage, STATE_PAGE_VALID) != EE_OK)
					{
						return EE_NO_PAGE_FOUND;
					}

					/* Set following page as active */
					if (prvSetPageState(ulFollowingPage, STATE_PAGE_ACTIVE) != EE_OK)
					{
						return EE_NO_PAGE_FOUND;
					}
					ulAddressNextWrite = PAGE_HEADER_SIZE;   /* Skip page header */
					return ulFollowingPage;         /* Following page is now active one */
				}
			}
			/* Transfer is on going, page receiving data */
			else
			{
				if (currentpagestatus == STATE_PAGE_RECEIVE)
				{
					/* Check if receive page is not full */
					if (ulAddressNextWrite < PAGE_SIZE)
					{
						/* Return current receive page */
						return ulCurrentPage;
					}
					else
					/* No more space in current receive page */
					{
						/* Check if following page is erasing state */
						if (followingpagestatus == STATE_PAGE_ERASING)
						{
							/* Force Cleanup, as not yet performed by user */
							if (prvEE_CleanUp() != EE_OK)
							{
								return EE_NO_PAGE_FOUND;
							}
						}

						/* Set current receive page in valid state */
						if (prvSetPageState(ulCurrentPage, STATE_PAGE_VALID) != EE_OK)
						{
							return EE_NO_PAGE_FOUND;
						}

						/* Set following page as receive */
						if (prvSetPageState(ulFollowingPage, STATE_PAGE_RECEIVE) != EE_OK)
						{
							return EE_NO_PAGE_FOUND;
						}
						ulAddressNextWrite = PAGE_HEADER_SIZE;   /* Skip page header */
						return ulFollowingPage;         /* Following page is now active one */
					}
				}
				else
				{
				return EE_NO_PAGE_FOUND;   /* No active Page */
				}
			}

		case FIND_READ_PAGE:  /* ---- Read operation ---- */

			if (currentpagestatus == STATE_PAGE_ACTIVE)
			{
				return ulCurrentPage;
			}
			else
			{
				if (currentpagestatus == STATE_PAGE_RECEIVE)
				{
					return ulPreviousPage;
				}
				else
				{
					return EE_NO_PAGE_FOUND;   /* No active Page */
				}
			}

		case FIND_ERASE_PAGE: /* ---- Return the erased page */

			if (followingpagestatus == STATE_PAGE_ERASED)
			{
				return ulFollowingPage;
			}
			else
			{
				return EE_NO_PAGE_FOUND;  /* No erased Page */
			}

		default:
		;
  	}
  return EE_NO_PAGE_FOUND;
}

/**
  * @brief  Verify if pages are full
  *   then if not the case, writes variable in EEPROM.
  * @param  VirtAddress 16 bit virtual address of the variable
  * @param  Data @ref EE_DATA_TYPE data to be written as variable value
  * @param  Write_type Type of writing on going (see EE_Write_type)
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_FULL: if half pages are full
  *           - EE_FLASH_USED: flash currently used by CPU2
  *           - EE error code: if an error occurs
  */

EE_Status prvVerifyPagesFullWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data)
{
	uint16_t usCRC = 0;
	uint8_t  ucDataArray[4]={Data >> 24,Data >> 16,Data >> 8,Data};
//	uint8_t readCpyArray[4];
	uint8_t  ucVirtAddressArray[4]={VirtAddress >> 24,VirtAddress >> 16,VirtAddress >> 8,VirtAddress};

	/* Check if pages are full, i.e. max number of written elements achieved */
	if (usNbWrittenElements >= NB_MAX_WRITTEN_ELEMENTS)
	{
	return EE_PAGE_FULL;
	}

	/* Get active Page for write operation */
	uint32_t activepage = prvFindPage(FIND_WRITE_PAGE);
	uint32_t activepageaddress = 0U;

	/* Check if there is no active page */
	if (activepage == EE_NO_PAGE_FOUND)
	{
		return EE_ERROR_NOACTIVE_PAGE;
	}

	activepageaddress = PAGE_ADDRESS(activepage);
	/*calculate CRC */

	//usCRC = xCrc16BitPolinomial_1021(Data, sizeof(Data),0);
	usCRC = xCrc16BitPolinomial_1021(ucDataArray, sizeof(ucDataArray),0);

	uint8_t  ucCRCArray[2]={usCRC >> 8,usCRC};

	/* Program variable data, virtual address,and CRC*/
	/* If program operation was failed, a Flash error code is returned */
	if (xFI_WriteDoubleWord(((activepageaddress+ulAddressNextWrite)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), ucDataArray)!= HAL_OK)
	{
		return HAL_ERROR;
	}
//	xFI_ReadDoubleWord(((activepageaddress+ulAddressNextWrite)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), readCpyArray);
//	if(!memcmp(readCpyArray, ucDataArray, 4))
	{
//		while(1);
	}

	if (xFI_WriteDoubleWord((((activepageaddress+ulAddressNextWrite)+EE_ADDRESS_OFFSET)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), ucVirtAddressArray)!= HAL_OK)
	{
		return HAL_ERROR;
	}

	if (xFI_WriteDoubleWord((((activepageaddress+ulAddressNextWrite)+EE_CRC_OFFSET)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), ucCRCArray)!= HAL_OK)
	{
		return HAL_ERROR;
	}

	uint8_t read_array[10];
	BSP_OSPI_NOR_Read(BSP_INSTANCE, read_array, ((activepageaddress+ulAddressNextWrite)+EE_EMULATION_START_ADDR -START_PAGE_ADDRESS), 10);
	printf("read_array = %x,%x,%x,%x,%x,%x,%x,%x,%x,%x \n\r",read_array[0],read_array[1],read_array[2],read_array[3],read_array[4],read_array[5],read_array[6],read_array[7],read_array[8],read_array[9]);

	/* Increment global variables relative to write operation done*/
	ulAddressNextWrite += EE_ELEMENT_SIZE;
	usNbWrittenElements++;

	printf( "usNbWrittenElements=%d\n",usNbWrittenElements);
	printf( "ucCurrentActivePage=%d\n",ucCurrentActivePage);
	printf( "ulAddressNextWrite=%lu\n",ulAddressNextWrite);
	return EE_OK;
}


/**
  * @brief  Writes a new variable data in fresh new page in case of normal
  *         transfer, and transfers last updated elements from full pages to
  *         empty pages in any cases.
  * @param  VirtAddress 16 bit virtual address of the new variable data
  * @param  Data @ref EE_DATA_TYPE data value of the new variable data
  * @param  Type Type of transfer.
  *         This parameter can be one of the EE_Transfer_type enum values.
  *            @arg @ref EE_TRANSFER_NORMAL Pages transfer during normal processing
  *            @arg @ref EE_TRANSFER_RECOVER Recovering pages transfer at Init
  * @retval EE_Status
  *           - prvEE_CleanUp_REQUIRED: on success
  *           - EE error code: if an error occurs
  */

EE_Status prvPagesTransfer (uint32_t VirtAddress, EE_DATA_TYPE Data, EE_Transfer_type Type)
{
	EE_State_type pagestatus = STATE_PAGE_INVALID;
	uint32_t ulPageAddress = 0U;
	uint32_t ulPage = 0U;
	uint32_t ulVarIdx = 0U;
	EE_ELEMENT_TYPE addressvalue = 0U;
	EE_Status status = EE_OK;
	EE_DATA_TYPE DataValue = 0U;
	uint8_t ucReadAddressValue[4]={0x00};
	uint8_t ucDataValue1[4]={0};

	/* Get receive Page for transfer operation */
	ulPage = prvFindPage((Type == EE_TRANSFER_NORMAL?FIND_ERASE_PAGE:FIND_WRITE_PAGE));

	if (ulPage == EE_NO_PAGE_FOUND)
	{
	  return EE_ERROR_NOERASE_PAGE;
	}

	/* Reinitialize number of data written in the pages, and current active page */
	usNbWrittenElements = 0U;
	ucCurrentActivePage = ulPage;
	ulAddressNextWrite = PAGE_HEADER_SIZE;

	/* Mark the erased page at receive state in case of normal transfer */
	/* It is already the case in recover transfer case */
	/* If program operation was failed, a Flash error code is returned */
    if (Type == EE_TRANSFER_NORMAL)
    {
      if (prvSetPageState(ulPage, STATE_PAGE_RECEIVE) != EE_OK)
      {
        return EE_WRITE_ERROR;
      }
    }

	/* Set the previous active page and all previous valid pages to erasing state */
	/* In case of recover transfer, some of these pages may already be marked erasing */
	ulPage = PREVIOUS_PAGE(ulPage);
	ulPageAddress = PAGE_ADDRESS(ulPage);
	pagestatus = prvGetPageState(ulPageAddress);

	if ((pagestatus == STATE_PAGE_ACTIVE) || (pagestatus == STATE_PAGE_ERASING))
	{
		/* Set active page to erasing */
		if (pagestatus == STATE_PAGE_ACTIVE)
		{
			if (prvSetPageState(ulPage, STATE_PAGE_ERASING) != EE_OK)
			{
				return EE_WRITE_ERROR;
			}
		}

		/* Inspect the previous pages to set all valid pages to erasing state */
		/* In case of recover, some valid pages may be already erasing state */
		ulPage = PREVIOUS_PAGE(ulPage);
		ulPageAddress = PAGE_ADDRESS(ulPage);
		pagestatus = prvGetPageState(ulPageAddress);

		while ((pagestatus == STATE_PAGE_VALID) || (pagestatus == STATE_PAGE_ERASING))
		{
			/* Set valid page to erasing */
			if (pagestatus == STATE_PAGE_VALID)
			{
				if (prvSetPageState(ulPage, STATE_PAGE_ERASING) != EE_OK)
				{
					return EE_WRITE_ERROR;
				}
			}

			/* decrement page index */
			ulPage = PREVIOUS_PAGE(ulPage);
			ulPageAddress = PAGE_ADDRESS(ulPage);
			pagestatus = prvGetPageState(ulPageAddress);
		}
	}
    else
    {
		if ((Type == EE_TRANSFER_RECOVER) && (pagestatus == STATE_PAGE_VALID))
		{
			/* This can happen in case of recover transfer. It indicates that previous */
			/* transfer goes far enough to fill a complete receive page at least */
			/* (valid state). Then erasing state marking was already completed */
		}
		else
		{
			/* Inconsistent previous page state */
			return EE_INVALID_PAGE_SEQUENCE;
		}
    }
	/* In case of recover transfer, transfer must be resumed where it has been stopped */
	/* Update global variables to reflect current transfer status */
	if (Type == EE_TRANSFER_RECOVER)
	{
		/* Count number of elements already transferred in current receive page */
		for (ulVarIdx = PAGE_HEADER_SIZE; ulVarIdx < PAGE_SIZE; ulVarIdx += EE_ELEMENT_SIZE)
		{
			/* Get next element in receive page */
			xFI_ReadDoubleWord(((PAGE_ADDRESS(ucCurrentActivePage)-START_PAGE_ADDRESS) +EE_EMULATION_START_ADDR+ ulVarIdx), ucDataValue1);
			xFI_ReadDoubleWord((((PAGE_ADDRESS(ucCurrentActivePage)-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR + ulVarIdx)+EE_ADDRESS_OFFSET),ucReadAddressValue );


			for (int i = 0; i < 4; i++)
			{
				addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
				addressvalue |= ucDataValue1[i]; // Add the byte from DataValue
			}

			for (int i = 0; i < 4; i++)
			{
				addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
				addressvalue |= ucReadAddressValue[i]; // Add the byte from ReadAddressValue
			}

			if (addressvalue != EE_PAGESTAT_ERASED)
			{
				/* Update global variables accordingly */
				usNbWrittenElements++;
				ulAddressNextWrite += EE_ELEMENT_SIZE;
			}
			else
			{
				break;
			}
		}
		/* Count number of elements already transferred in previous valid pages */
		ulPage = ucCurrentActivePage;
		for (ulVarIdx = 0U; ulVarIdx < PAGES_NUMBER; ulVarIdx++)
		{
			/* Decrement page index among circular pages list */
			ulPage = PREVIOUS_PAGE(ulPage);
			pagestatus = prvGetPageState(PAGE_ADDRESS(ulPage));

			/* Check if page is valid state */
			if (pagestatus == STATE_PAGE_VALID)
			{
				/* Update usNbWrittenElements with number of elements in page */
				usNbWrittenElements += NB_MAX_ELEMENTS_BY_PAGE;
			}
			else
			{
				break;
			}
		}
	}
	// Write the variable passed as parameter in the new active page
	// If program operation was failed, a Flash error code is returned
	if (prvVerifyPagesFullWriteVariable(VirtAddress, Data) != EE_OK)
	{
		return EE_WRITE_ERROR;
	}
	/* Transfer process: transfer variables from old to the new active page */
	/* First element in receive page can be any one, the following elements are */
	/* ordered from the beginning. */
	/* In case of recovery, Pre-Last element in receive page could be */
	/* corrupted if reset occured during write of this element, */
	/* and last element is dummy value that we have just written. */
	/* Transfer shall then resume from (usNbWrittenElements-3) variable index */

//	for (ulVarIdx = (usNbWrittenElements >= 3U?(usNbWrittenElements-3U):0U); ulVarIdx < (sizeof(eepromVariables) / sizeof(eepromVariables[0])); ulVarIdx++)
	for (ulVarIdx = 0U; ulVarIdx < (uint32_t)(sizeof((void*)eepromVariables) / sizeof((void*)eepromVariables[0])); ulVarIdx++)
	{
        /* Check each variable except the one passed as parameter */
		if ((uint32_t)eepromVariables[ulVarIdx] !=VirtAddress)
		{
			/* Read the last variable updates */
			status = prvReadVariable((uint32_t)eepromVariables[ulVarIdx], &DataValue);

			if (status == EE_OK)
			{
				/* In case variable corresponding to the virtual address was found */
				/* Transfer the variable to the new active page */
				/* If program operation was failed, a Flash error code is returned */
				status = prvVerifyPagesFullWriteVariable((uint32_t)eepromVariables[ulVarIdx], DataValue);

				if (status != EE_OK)
				{
					return status;
				}
			}
	 		else
			{
				if (status != EE_NO_DATA)
				{
					/* In case variable is not found , do nothing */
					/* Any other status is error code occurs during variable read */
					return status;
				}
			}
	    }
    }

	/* Transfer is now done, mark the receive state page as active */
	if (prvSetPageState(ucCurrentActivePage, STATE_PAGE_ACTIVE) != EE_OK)
	{
	 	return EE_WRITE_ERROR;
	}
	/* Return last operation flash status */
	if (EE_OK != prvEE_CleanUp())
	{
		return EE_ERROR_NOERASING_PAGE ;
	}
	else
	{
		return EE_OK ;
	}
}

/**
  * @brief  Restore the pages to a known good state in case of page's status
  *   corruption after a power loss.
  * @param  None.
  * @retval - Flash error code: on write Flash error
  *         - FLASH_COMPLETE: on success
  */

 EE_Status xEE_Init(EE_Erase_type EraseType)
{
	EE_State_type pagestatus = STATE_PAGE_INVALID;
	uint32_t ulPage = 0U;
	uint32_t ulPageAddress = 0U;
	uint32_t ulVarIdx = 0U;
	uint32_t ulNbActivePage = 0U;
	uint32_t ulNbActiveReceivePage = 0U;
	uint32_t ulNbValidPage = 0U;
	uint32_t ulLastValidPage = 0U;
	uint32_t ulFirstValidPage = 0U;

//	prvEE_Format(EE_FORCED_ERASE);

	EE_State_Reliability pagestate = STATE_RELIABLE;

	/* check the flash end address with calculated end address for required variables*/
	if (CALCULATED_END_ADDRESS >= FLASH_END_ADDR)
	{
		return EE_MEMORY_NOT_SUFFICIENT;
	}

	/***************************************************************************/
	/* Step 1: Handle case of reset during transfer with no receive page       */
	/*         present, by setting missing receive page state                  */
	/***************************************************************************/

	/* Check if no active page and no receive page present */
	/* Browse all pages */
	for (ulPage = START_PAGE; ulPage < (START_PAGE + PAGES_NUMBER); ulPage++)
	{
		ulPageAddress = PAGE_ADDRESS(ulPage);
		pagestatus = prvGetPageState(ulPageAddress);

		/* Search for active and receive page */
		if ((pagestatus == STATE_PAGE_ACTIVE) || (pagestatus == STATE_PAGE_RECEIVE))
		{
			ulNbActiveReceivePage++;
		}
		/* Keep index of first valid page, and last valid page */
		else if (pagestatus == STATE_PAGE_VALID)
		{
			if (ulNbValidPage == 0U)
			{
				ulFirstValidPage = ulPage;
			}
			ulLastValidPage = ulPage;
			ulNbValidPage++;
		}
	}

	/* Check if no active and no receive page have been detected */
	if (ulNbActiveReceivePage == 0U)
	{
		/* Check if valid pages have been detected */
		if (ulNbValidPage > 0U)
		{
			/* Check state of page just before first valid page.
			If it is erasing page, then page after last valid page shall be set
			to receiving state */
			if (prvGetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(ulFirstValidPage))) == STATE_PAGE_ERASING)
			{
				if (prvSetPageState(FOLLOWING_PAGE(ulLastValidPage), STATE_PAGE_RECEIVE) != EE_OK)
				{
					return EE_WRITE_ERROR;
				}
			}
		}
		/* Format flash pages used for eeprom emulation in case no active, no receive, no valid pages are found */
		else
		{
			return prvEE_Format(EE_FORCED_ERASE);
		}
	}

	/*********************************************************************/
	/* Step 2: Handle case of reset during transfer, by performing       */
	/*         transfer recovery                                         */
	/*********************************************************************/

	/* Browse all pages */
	for (ulPage = START_PAGE; ulPage < (START_PAGE + PAGES_NUMBER); ulPage++)
	{
		ulPageAddress = PAGE_ADDRESS(ulPage);
		pagestatus = prvGetPageState(ulPageAddress);

		/* Check if there is receive page, meaning transfer has been interrupted */
		if (pagestatus == STATE_PAGE_RECEIVE)
		{
			/* Verify that receive page is a true one, not a corrupted page state */
			/* Check if page is not the first page of a bloc */
			if ((ulPage != START_PAGE) && (ulPage != (uint32_t)(START_PAGE + PAGE_GROUP)))
			{
				/* Check that previous page is valid state */
				if (prvGetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(ulPage))) == STATE_PAGE_VALID)
				{
					/* The receive page is a true receive page */
					pagestate = STATE_RELIABLE;
				}
				else /* Previous page is not valid state */
				{
					/* The receive page is false receive page due to header corruption */
					pagestate = STATE_CORRUPTED;
				}
			}
			else /* The receive page is the first page of a bloc */
			{
				/* Check that following page is erased state */
				if (prvGetPageState(PAGE_ADDRESS(FOLLOWING_PAGE(ulPage))) == STATE_PAGE_ERASED)
				{
					/* The receive page is a true receive page */
					pagestate = STATE_RELIABLE;
				}
				else /* Following page is not erased state */
				{
					/* The receive page is false receive page due to header corruption */
					pagestate = STATE_CORRUPTED;
				}
			}

			/* If the receive page is a true receive page, resume pages transfer */
			if (pagestate == STATE_RELIABLE)
			{
				/* Initialize current active page */
				ucCurrentActivePage = ulPage;

				/* Resume the interrupted page transfer, using dummy new data */
				if (prvPagesTransfer (0U, 0U, EE_TRANSFER_RECOVER) != EE_CLEANUP_REQUIRED)
				{
					return EE_TRANSFER_ERROR;
				}
				/* transfer recovery is done, then stop searching receive page */
				break;
			}
		}
	}

	/*********************************************************************/
	/* Step 3: Verify presence of one unique active page                 */
	/*         If more than one active page, raise error                 */
	/*         If no active page present, set missing active page        */
	/*********************************************************************/

	/* Browse all pages to search for active pages */
	ulNbActivePage = 0U;
	for (ulPage = START_PAGE; ulPage < (START_PAGE + PAGES_NUMBER); ulPage++)
	{
	    ulPageAddress = PAGE_ADDRESS(ulPage);
	    pagestatus = prvGetPageState(ulPageAddress);

	    /* Search for active page */
	    if (pagestatus == STATE_PAGE_ACTIVE)
	    {
			/* Verify that active page is a true one, not a corrupted page state */
			/* Check if page is not the first page of a bloc */
			if ((ulPage != START_PAGE) && (ulPage != (uint32_t)(START_PAGE + PAGE_GROUP)))
			{
				/* Check that previous page is valid state */
				if (prvGetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(ulPage))) == STATE_PAGE_VALID)
				{
					/* The active page is a true active page */
					pagestate = STATE_RELIABLE;
				}
				else /* Previous page is not valid state */
				{
					/* The active page is false active page due to header corruption */
					pagestate = STATE_CORRUPTED;
				}
	      	}
			else /* The active page is the first page of a bloc */
			{
				/* Check that following page is erased state */
				if (prvGetPageState(PAGE_ADDRESS(FOLLOWING_PAGE(ulPage))) == STATE_PAGE_ERASED)
				{
					/* The active page is a true active page */
					pagestate = STATE_RELIABLE;
				}
				else /* Following page is not erased state */
				{
					/* The active page is false active page due to header corruption */
					pagestate = STATE_CORRUPTED;
				}
			}

			/* If the active page is a true active page, initialize global variables */
			if (pagestate == STATE_RELIABLE)
			{
				if (ulNbActivePage == 0U)
				{
					ucCurrentActivePage = ulPage;
					ulNbActivePage++;
				}
				else
				{
					/* Error: More than one reliable active page is present */
					return EE_INVALID_PAGE_SEQUENCE;
				}
			}
	    }
	    /* Keep index of last valid page, will be required in case no active page is found */
	    else if (pagestatus == STATE_PAGE_VALID)
	    {
			ulLastValidPage = ulPage;
	    }
	}

	/* In case no active page is found, set page after last valid page to active state */
	if (ulNbActivePage == 0U)
	{
		ucCurrentActivePage = FOLLOWING_PAGE(ulLastValidPage);
		if (prvSetPageState(ucCurrentActivePage, STATE_PAGE_ACTIVE) != EE_OK)
		{
			return EE_WRITE_ERROR;
		}
	}


	/*********************************************************************/
	/* Step 4: Initialize eeprom emulation global variables relative     */
	/*         to active page                                            */
	/*********************************************************************/

	/* Initialize global variables, with elements detected in active page */
	usNbWrittenElements = 0U;
	ulAddressNextWrite = PAGE_HEADER_SIZE;
	for (ulVarIdx = PAGE_HEADER_SIZE; ulVarIdx < (PAGE_SIZE); ulVarIdx += EE_ELEMENT_SIZE)
	{
		uint32_t ulDataValue;
		uint32_t ulReadAddressValue;
		uint8_t ucReadAddressValue[4]= {0x00};
		uint8_t ucDataValue[4]= {0x00};

		xFI_ReadDoubleWord(((PAGE_ADDRESS(ucCurrentActivePage)-START_PAGE_ADDRESS) +EE_EMULATION_START_ADDR + ulVarIdx), ucDataValue);

		ulDataValue = (ucDataValue[0]<<24|ucDataValue[1]<<16|ucDataValue[2]<<8|ucDataValue[3]);

		xFI_ReadDoubleWord((((PAGE_ADDRESS(ucCurrentActivePage)-START_PAGE_ADDRESS) +EE_EMULATION_START_ADDR + ulVarIdx)+EE_ADDRESS_OFFSET),ucReadAddressValue );

		ulReadAddressValue =(ucReadAddressValue[0]<<24|ucReadAddressValue[1]<<16|ucReadAddressValue[2]<<8|ucReadAddressValue[3]);

		if ((ulDataValue != EE_NO_DATA_FOUND) && (ulReadAddressValue != EE_NO_DATA_FOUND))
		{
			/* Then increment usNbWrittenElements and ulAddressNextWrite */
			usNbWrittenElements++;
			ulAddressNextWrite += EE_ELEMENT_SIZE;
		}
		else /* no more element in the page */
		{
			break;
		}
	}

	/*********************************************************************/
	/* Step 5: Finalize eeprom emulation global variables relative       */
	/*         to valid pages, and check consistency of pages sequence   */
	/*********************************************************************/

	/* Check consistency of pages sequence: one active page, optionnally some valid pages before */
	/* Update global variable usNbWrittenElements if valid pages are found */
	ulPage = ucCurrentActivePage;
	ulFirstValidPage = ucCurrentActivePage;
	while ((ulPage != START_PAGE) && (ulPage != (uint32_t)(START_PAGE + PAGE_GROUP)))
	{
		/* Decrement page index among circular pages list */
		ulPage = PREVIOUS_PAGE(ulPage);
		pagestatus = prvGetPageState(PAGE_ADDRESS(ulPage));

		/* Check if page is valid state */
		if (pagestatus == STATE_PAGE_VALID)
		{
			/* Update usNbWrittenElements with number of elements in full page */
			usNbWrittenElements += NB_MAX_ELEMENTS_BY_PAGE;

			/* Keep index of first valid page */
			ulFirstValidPage = ulPage;
		}
		else
		{
			/* Error: Pages sequence is not consistent */
			return EE_INVALID_PAGE_SEQUENCE;
		}
	}

	/*********************************************************************/
	/* Step 6: Ensure empty pages are erased                             */
	/*********************************************************************/

    /* Ensure all pages after active page, until first valid page, are erased */
    ulPage = FOLLOWING_PAGE(ucCurrentActivePage);
    ulPageAddress = PAGE_ADDRESS(ulPage);

    while (ulPage != ulFirstValidPage)
    {
		/* Check if page erase has to be forced unconditionally (default case) */
		if (EraseType == EE_FORCED_ERASE )
		{
			/* Force page erase independently of its content */
			if (xFI_PageErase((ulPageAddress-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR)!= EE_OK)
			{
				return EE_ERASE_ERROR;
			}
		}
		else /* EraseType == EE_CONDITIONAL_ERASE */
		{
			/* Check if page is fully erased */
			if (prvVerifyPageFullyErased(ulPageAddress, PAGE_SIZE) == EE_PAGE_NOTERASED)
			{
				/* Erase pages if not fully erased */
				if (xFI_PageErase((ulPageAddress-START_PAGE_ADDRESS)+EE_EMULATION_START_ADDR)!= EE_OK)
				{
					return EE_ERASE_ERROR;
				}
			}
		}

		/* Increment page index among circular pages list, to get first page to erased */
		ulPage = FOLLOWING_PAGE(ulPage);
		ulPageAddress = PAGE_ADDRESS(ulPage);
    }

	printf( "usNbWrittenElements=%d\n",usNbWrittenElements);
	printf( "ucCurrentActivePage=%d\n",ucCurrentActivePage);
	printf( "ulAddressNextWrite=%lu\n",ulAddressNextWrite);

 return EE_OK;
}

/**************************************************************************************************
 * End Of File
***************************************************************************************************/
