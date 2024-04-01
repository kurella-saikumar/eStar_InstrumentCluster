/**
  ******************************************************************************
  * @file    EEPROM/EEPROM_Emulation/src/eeprom.c 
  * @author  DEVIDRAJ.K
  * @brief   This file provides all the EEPROM emulation firmware functions.
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

/** @addtogroup EEPROM_Emulation
  * @{
  */ 

/* Includes ------------------------------------------------------------------*/
#include "eeprom.h"
#include "stdio.h"
#include "string.h"
#include "../../Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.h"
#include "eeprom_cfg.h"
#include "../checksum/checksum.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Global variable used to store variable value in read sequence */
uint32_t DataVar = 0;
uint32_t NextWriteAddress = EEPROM_START_ADDRESS-EEPROM_OFFSET;

/* During the cleanup phase in EE_Init, AddressRead is the address being read */
__IO uint32_t AddressRead = 0;
/* Flag equal to 1 when the cleanup phase is in progress, 0 if not */
__IO uint8_t CleanupPhase = 0;


/* Global variables used to store eeprom status */
 uint16_t uhNbWrittenElements = 0U;                  /*!< Nb of elements written in valid and active pages */
 uint8_t ubCurrentActivePage = 0U;                   /*!< Current active page (can be active or receive state) */
 uint32_t uwAddressNextWrite = ((0x00000000)+(PAGE_HEADER_SIZE));     /*!< Initialize write position just after page header */


uint8_t ucReadData[PAGE_SIZE]={0};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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


typedef enum {
   EE_FORCED_ERASE,
   EE_CONDITIONAL_ERASE
} EE_Erase_type;



EE_Status EE_Format(EE_Erase_type EraseType);
EE_Status EE_Init(EE_Erase_type EraseType);
EE_Status EE_ReadVariable32bits(uint32_t VirtAddress, uint32_t* pData);
EE_Status EE_WriteVariable32bits(uint32_t VirtAddress, uint32_t Data);
EE_Status EE_CleanUp(void);





EE_Status ReadVariable(uint32_t VirtAddress, EE_DATA_TYPE* pData);
EE_Status WriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data);
EE_Status PagesTransfer(uint32_t VirtAddress, EE_DATA_TYPE Data, EE_Transfer_type Type);
EE_Status VerifyPageFullyErased(uint32_t Address, uint32_t PageSize);
uint32_t FindPage(EE_Find_type Operation);
EE_Status VerifyPagesFullWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data);
EE_Status SetPageState(uint32_t Page, EE_State_type State);
EE_State_type GetPageState(uint32_t Address);


/**
  * @brief  Erases PAGE and PAGE1 and writes VALID_PAGE header to PAGE
  * @param  None
  * @retval Status of the last operation (Flash write or erase) done during
  *         EEPROM formatting
  */

EE_Status EE_Format(EE_Erase_type EraseType)
{
  uint32_t page = 0U;

  /* Erase All Pages */
  for (page = START_PAGE; page < (START_PAGE + PAGES_NUMBER); page++)
  {
	  if (EraseType == EE_FORCED_ERASE)
	  {
		  if(EE_OK != BSP_OSPI_NOR_Erase_Block(0, (uint32_t)(PAGE_ADDRESS(page)-START_PAGE_ADDRESS), BSP_OSPI_NOR_ERASE_4K))
		  {
			  return EE_ERASE_ERROR;
		  }
	  }
	  else /* EraseType == EE_CONDITIONAL_ERASE */
	  {
		/* Check if Page is not yet fully erased */
		if (VerifyPageFullyErased(PAGE_ADDRESS(page), PAGE_SIZE) == EE_PAGE_NOTERASED)
		{
		  /* Erase the page */
		  /* If Erase operation was failed, a Flash error code is returned */
		  if (EE_OK != BSP_OSPI_NOR_Erase_Block(0, (uint32_t)PAGE_ADDRESS(page), BSP_OSPI_NOR_ERASE_4K))
		  {
			 return EE_ERASE_ERROR;
		  }
		}
	  }

   }

  /* Set first Page in Active State */
  /* If program operation was failed, a Flash error code is returned */
    if (SetPageState(START_PAGE, STATE_PAGE_ACTIVE) != EE_OK)
    {
      return EE_WRITE_ERROR;
    }

    /* Reset global variables */
    uhNbWrittenElements = (uint16_t)0U;
    ubCurrentActivePage = START_PAGE;
    uwAddressNextWrite = PAGE_HEADER_SIZE; /* Initialize write position just after page header */

 return EE_OK;
 }






/**
  * @brief  Returns the last stored variable data, if found, which correspond to
  *         the passed virtual address
  * @param VirtAddress Variable virtual address on 16 bits (can't be 0x00000000 or 0xFFFFFFFF)
  * @param  pData Variable containing the 32bits read variable value
  * @retval EE_Status
  *           - EE_OK: if variable was found
  *           - EE error code: if an error occurs
  */
EE_Status EE_ReadVariable32bits(uint32_t VirtAddress, uint32_t* pData)
{
  if((VirtAddress != 0x00000000) && (VirtAddress != 0xFFFFFFFF))
  {
    EE_DATA_TYPE datatmp = 0U;
    EE_Status status = EE_OK;

    /* Read variable of size EE_DATA_TYPE, then cast it to 32bits */
    status = ReadVariable(VirtAddress, &datatmp);
    *pData = (uint32_t) datatmp;

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
  *           - EE_CLEANUP_REQUIRED: success and user has to trig flash pages cleanup
  *           - EE error code: if an error occurs
  */
EE_Status EE_WriteVariable32bits(uint32_t VirtAddress, uint32_t Data)
{
	if((VirtAddress != 0x00000000) && (VirtAddress != 0xFFFFFFFF))
	{
		return WriteVariable(VirtAddress, (EE_DATA_TYPE) Data);
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

 EE_State_type GetPageState(uint32_t Address)
{
	EE_ELEMENT_TYPE status1 = 0U, status2 = 0U, status3 = 0U, status4 = 0U;

	uint32_t Header_firstByte0=0;
	uint32_t Header_firstByte1=0;
	uint32_t Header_secondByte0=0;
	uint32_t Header_secondByte1=0;
	uint32_t Header_thirdByte0=0;
	uint32_t Header_thirdByte1=0;
	uint32_t Header_forthByte0=0;
	uint32_t Header_forthByte1=0;


  /* Get page state information from page header (3 first elements) */
	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_firstByte0, (uint32_t)(Address-START_PAGE_ADDRESS), sizeof(Header_firstByte0))))
	{
		return HAL_ERROR;
	}


	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_firstByte1, (uint32_t)((Address-START_PAGE_ADDRESS)+4U), sizeof(Header_firstByte1))))
		{
			return HAL_ERROR;
		}

	// Combine the two 4bytes to form the Header element 8 byte(64-bit value)
	status1 = ((uint64_t)Header_firstByte1 << 32) | Header_firstByte0;


	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_secondByte0, (uint32_t)((Address-START_PAGE_ADDRESS) + EE_HEADER_ELEMENT_SIZE), sizeof(Header_secondByte0))))
	{
		return HAL_ERROR;
	}
	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_secondByte1, (uint32_t)(((Address-START_PAGE_ADDRESS) + EE_HEADER_ELEMENT_SIZE)+4U), sizeof(Header_secondByte1))))
		{
			return HAL_ERROR;
		}

	// Combine the two 4bytes to form the Header element 8 byte(64-bit value)
	status2 = ((uint64_t)Header_secondByte1 << 32) | Header_secondByte0;


	if(HAL_OK!= (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_thirdByte0, (uint32_t)((Address-START_PAGE_ADDRESS) + (EE_HEADER_ELEMENT_SIZE*2U)), sizeof(Header_thirdByte0))))
	{
		return HAL_ERROR;
	}

	if(HAL_OK!= (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_thirdByte1, (uint32_t)(((Address-START_PAGE_ADDRESS) + (EE_HEADER_ELEMENT_SIZE*2U))+4U), sizeof(Header_thirdByte1))))
		{
			return HAL_ERROR;
		}

	// Combine the two 4bytes to form the Header element 8 byte(64-bit value)
	status3 = ((uint64_t)Header_thirdByte1 << 32) | Header_thirdByte0;


	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_forthByte0, (uint32_t)((Address-START_PAGE_ADDRESS) + (EE_HEADER_ELEMENT_SIZE*3U)), sizeof(Header_forthByte0))))
	{
		return HAL_ERROR;
	}

	if(HAL_OK != (BSP_OSPI_NOR_Read(0, (uint8_t *)&Header_forthByte1, (uint32_t)(((Address-START_PAGE_ADDRESS) + (EE_HEADER_ELEMENT_SIZE*3U))+4U), sizeof(Header_forthByte1))))
		{
			return HAL_ERROR;
		}

	// Combine the two 4bytes to form the Header element 8 byte(64-bit value)
	status4 = ((uint64_t)Header_forthByte1 << 32) | Header_forthByte0;


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
 EE_Status SetPageState(uint32_t Page, EE_State_type State)
{
  uint32_t header1 = 0U, header2 = 0U, header3 = 0U, header4 = 0U;

  uint8_t RECEIVE[4] = {0xAA,0xAA,0xAA,0xAA};
  uint8_t ACTIVE [4]= {0xAA,0xAA,0xAA,0xAA};
  uint8_t VALID [4]= {0xAA,0xAA,0xAA,0xAA};
  uint8_t ERASING [4]= {0xAA,0xAA,0xAA,0xAA};

  header1 = PAGE_ADDRESS(Page);
  header2 = PAGE_ADDRESS(Page) + EE_HEADER_ELEMENT_SIZE;
  header3 = PAGE_ADDRESS(Page) + (EE_HEADER_ELEMENT_SIZE*2U);
  header4 = PAGE_ADDRESS(Page) + (EE_HEADER_ELEMENT_SIZE*3U);

  switch(State)
   {
   case STATE_PAGE_RECEIVE:
     {
       /* Set new Page status to STATE_PAGE_RECEIVE status */
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)RECEIVE, (header1-START_PAGE_ADDRESS), sizeof(RECEIVE)) != HAL_OK)
       {
         return EE_WRITE_ERROR;
       }
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)RECEIVE, ((header1-START_PAGE_ADDRESS)+4U), sizeof(RECEIVE)) != HAL_OK)
	  {
		return EE_WRITE_ERROR;
	  }
       ubCurrentActivePage = Page;
     }
     break;
   case STATE_PAGE_ACTIVE:
     {
       /* Set new Page status to STATE_PAGE_ACTIVE status */
       if (BSP_OSPI_NOR_Write(0, (uint8_t*)ACTIVE, (header2-START_PAGE_ADDRESS), sizeof(ACTIVE)) != HAL_OK)
       {
         return EE_WRITE_ERROR;
       }
       if (BSP_OSPI_NOR_Write(0, (uint8_t*)ACTIVE, ((header2-START_PAGE_ADDRESS)+4U), sizeof(ACTIVE)) != HAL_OK)
	  {
		return EE_WRITE_ERROR;
	  }
       ubCurrentActivePage = Page;
     }
     break;
   case STATE_PAGE_VALID:
     {
       /* Set new Page status to STATE_PAGE_VALID status */
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)VALID, (header3-START_PAGE_ADDRESS), sizeof(VALID)) != HAL_OK)
       {
         return EE_WRITE_ERROR;
       }
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)VALID, ((header3-START_PAGE_ADDRESS)+4U), sizeof(VALID)) != HAL_OK)
		 {
		   return EE_WRITE_ERROR;
		 }


     }
     break;
   case STATE_PAGE_ERASING:
     {
       /* Set new Page status to STATE_PAGE_ERASING status */
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)ERASING, (header4-START_PAGE_ADDRESS), sizeof(ERASING)) != HAL_OK)
       {
         return EE_WRITE_ERROR;
       }
       if (BSP_OSPI_NOR_Write(0,(uint8_t*)ERASING, ((header4-START_PAGE_ADDRESS)+4U), sizeof(ERASING)) != HAL_OK)
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
  * @brief  Restore the pages to a known good state in case of page's status
  *   corruption after a power loss.
  * @param  None.
  * @retval - Flash error code: on write Flash error
  *         - FLASH_COMPLETE: on success
  */


/**
  * @brief  Erase group of pages which are erasing state, in polling mode.
  *         Could be either first half or second half of total pages number.
  * @note   This function should be called when EE_WriteVariableXXbits has
  *         returned EE_CLEANUP_REQUIRED status (and only in that case)
  * @retval EE_Status
  *           - EE_OK: in case of success
  *           - EE error code: if an error occurs
  */
EE_Status EE_CleanUp(void)
{
  uint32_t firstpage = 0U, page = 0U;
  uint32_t firstpageaddress = 0U, pageaddress = 0U;
  EE_State_type firstpagestatus = STATE_PAGE_INVALID, pagestatus = STATE_PAGE_INVALID;

  /* Check first half and second half page group */
  for (firstpage = START_PAGE; firstpage < (START_PAGE + PAGES_NUMBER); firstpage += (PAGES_NUMBER / 2U))
  {
    /* Check status of first page of the group */
    firstpageaddress = PAGE_ADDRESS(firstpage);
    firstpagestatus = GetPageState(firstpageaddress);

    /* If first page of the group is erasing state, check that all other pages
    of the group are also erasing state */
    if (firstpagestatus == STATE_PAGE_ERASING)
    {
	  for (page = (firstpage + 1U); page < (firstpage + (PAGES_NUMBER / 2U)); page++)
	  {
		pageaddress = PAGE_ADDRESS(page);
		pagestatus = GetPageState(pageaddress);

		/* If page is not erasing, return error */
		if (pagestatus != STATE_PAGE_ERASING)
		{
		  return EE_ERROR_NOERASING_PAGE;
		}
	  }

	  /* Erase all the pages of the group */
	  /* If erase operation fails, a Flash error code is returned */
	  for (page = 0; page < (PAGES_NUMBER / 2U); page+=PAGE_SIZE)
	  {
		if (BSP_OSPI_NOR_Erase_Block(0, (uint32_t)((PAGE_ADDRESS(firstpage)+page)-START_PAGE_ADDRESS), BSP_OSPI_NOR_ERASE_4K)!= EE_OK)
		{
			return EE_ERASE_ERROR;
		}
		else
		{
			return EE_OK;
		}
	  }
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
EE_Status VerifyPageFullyErased(uint32_t Address, uint32_t PageSize)
{
  EE_Status readstatus = EE_PAGE_ERASED;
  uint32_t counter = 0U;
  uint64_t addressvalue =0U;
  uint8_t ReadAddressValue[4]={0};
  uint8_t DataValue2[4]={0};


  /* Check each element in the page */
  while (counter < PageSize)
  {

		  BSP_OSPI_NOR_Read(0, (uint8_t *)ReadAddressValue, (uint32_t)(Address+counter), sizeof(ReadAddressValue));

	  	  BSP_OSPI_NOR_Read(0, (uint8_t *)DataValue2, (uint32_t)((Address+counter)+32U), sizeof(DataValue2));

	  	  for (int i = 0; i < 4; i++)
	  	  {
	  		  addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
	  		  addressvalue |= DataValue2[i]; // Add the byte from DataValue
	  	  }

	  	  for (int i = 0; i < 4; i++)
	  	  {
	  		  addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
	  		  addressvalue |= ReadAddressValue[i]; // Add the byte from ReadAddressValue
	  	  }

		if (addressvalue!= EE_PAGESTAT_ERASED)
		   {
			/* In case one element is not erased, reset readstatus flag */
			 readstatus = EE_PAGE_NOTERASED;
		   }
	    /* Next address location */
    counter = counter + EE_ELEMENT_SIZE;
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

EE_Status ReadVariable(uint32_t VirtAddress, EE_DATA_TYPE* pData)
{
	  EE_ELEMENT_TYPE addressvalue = 0U;
	  uint32_t page = 0U, pageaddress = 0U, counter = 0U ;
	  uint8_t ReadAddressValue[4] = {0X00};
	  uint8_t DataValue[4] = {0x00};
	  uint32_t ReadAddr = 0;
	  uint16_t crc_read = 0;
	  uint8_t crc [2]= {0x00};
	  uint16_t crc_calculated = 0;
	  uint32_t Data = 0;

    EE_State_type pagestate = STATE_PAGE_INVALID;

    /* Get active Page for read operation */
    page = FindPage(FIND_READ_PAGE);

    /* Check if there is no active page */
    if (page == EE_NO_PAGE_FOUND)
    {
      return EE_ERROR_NOACTIVE_PAGE;
    }
    pageaddress = PAGE_ADDRESS(page);
    pagestate = GetPageState(pageaddress);

    /* Search variable in active page and valid pages until erased page is found
       or in erasing pages until erased page is found */
    while ((pagestate == STATE_PAGE_ACTIVE) || (pagestate == STATE_PAGE_VALID) || (pagestate == STATE_PAGE_ERASING))
    {
      /* Set counter index to last element position in the page */
      counter = (PAGE_SIZE - EE_ELEMENT_SIZE)- EMPTY_BYTES_FOR_PAGE;

      /* Check each page address starting from end */
     while (counter >= PAGE_HEADER_SIZE)
      {
        /* Get the current location content to be compared with virtual address */

    	BSP_OSPI_NOR_Read(0, (uint8_t *)ReadAddressValue, (uint32_t)((pageaddress + counter + 4U)-START_PAGE_ADDRESS), sizeof(ReadAddressValue));

    	ReadAddr = (ReadAddressValue[0]|ReadAddressValue[1]<<8|ReadAddressValue[2]<<16|ReadAddressValue[3]<<24);

        if (ReadAddr != 0xFFFFFFFFU)
        {
          /* Compare the read address with the virtual address */
        	 if (ReadAddr == VirtAddress)
        	 {
				/* Get content of variable value */
        		 BSP_OSPI_NOR_Read(0, (uint8_t *)DataValue, (uint32_t)((pageaddress + counter)-START_PAGE_ADDRESS), sizeof(DataValue));

        		 *pData = (DataValue[0]|DataValue[1]<<8|DataValue[2]<<16|DataValue[3]<<24);

        		 Data = *pData ;

        		 crc_calculated = xCrc16BitPolinomial_1021(Data, sizeof(Data),0);

        		 BSP_OSPI_NOR_Read(0, (uint8_t *)crc, (uint32_t)((pageaddress + counter + 8U)-START_PAGE_ADDRESS), sizeof(crc));

        		 crc_read = (crc[0]|crc[1]<<8);

        		 if (crc_calculated == crc_read)
        		 {
        			 return EE_OK;
        		 }
        		 else
        		 {

        			 return EE_READ_DATA_INVALID;
        		 }
        	 }
        }
        /* Next address location */
			 counter -= EE_ELEMENT_SIZE;
      }
      /* Decrement page index circularly, among pages allocated to eeprom emulation */
      	   page = PREVIOUS_PAGE(page);
      	   pageaddress = PAGE_ADDRESS(page);
      	   pagestate = GetPageState(pageaddress);
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
  *           - EE_CLEANUP_REQUIRED: on success, with page transfer occured
  *           - EE_FLASH_USED: flash currently used by CPU2
  *           - EE error code: if an error occurs
  */

 EE_Status WriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data)
{
  EE_Status status = EE_OK;

  /* Write the variable virtual address and value in the EEPROM, if not full */
  status = VerifyPagesFullWriteVariable(VirtAddress, Data);
  if (status == EE_PAGE_FULL)
    {
      /* In case the EEPROM pages are full, perform Pages transfer */
      return PagesTransfer(VirtAddress, Data, EE_TRANSFER_NORMAL);
    }

  	  	printf( "uhNbWrittenElements=%d\n",uhNbWrittenElements);
  		printf( "ubCurrentActivePage=%d\n",ubCurrentActivePage);
  		printf( "uwAddressNextWrite=%lu\n",uwAddressNextWrite);

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
uint32_t FindPage(EE_Find_type Operation)
{
  EE_State_type currentpagestatus = STATE_PAGE_INVALID, followingpagestatus = STATE_PAGE_INVALID;
  uint32_t currentpage = 0U, followingpage = 0U, previouspage = 0U;

  /* Get currentpage status */
  currentpage = ubCurrentActivePage;
  currentpagestatus = GetPageState(PAGE_ADDRESS(currentpage));

  /* Get followingpage status */
  followingpage = FOLLOWING_PAGE(currentpage);
  followingpagestatus = GetPageState(PAGE_ADDRESS(followingpage));

  /* Get previouspage status */
  previouspage = PREVIOUS_PAGE(currentpage);

  /* Write, read or erase operation */
  switch (Operation)
  {
    case FIND_WRITE_PAGE:   /* ---- Write operation ---- */
      /* Normal operation, no page transfer on going */
      if (currentpagestatus == STATE_PAGE_ACTIVE)
      {
			/* Check if active page is not full */
			if (uwAddressNextWrite < PAGE_SIZE)
				{
				  /* Return current Active page */
				  return currentpage;
				}
			else
			/* No more space in current active page */
			{
			  /* Check if following page is erasing state */
			  if (followingpagestatus == STATE_PAGE_ERASING)
			  {
					/* Force Cleanup, as not yet performed by user */
					if (EE_CleanUp() != EE_OK)
					{
					  return EE_NO_PAGE_FOUND;
					}
			  }

			  /* Set current active page in valid state */
			  if (SetPageState(currentpage, STATE_PAGE_VALID) != EE_OK)
			  {
				  return EE_NO_PAGE_FOUND;
			  }

			  /* Set following page as active */
			  if (SetPageState(followingpage, STATE_PAGE_ACTIVE) != EE_OK)
			  {
				  return EE_NO_PAGE_FOUND;
			  }
			  uwAddressNextWrite = PAGE_HEADER_SIZE;   /* Skip page header */
			  return followingpage;         /* Following page is now active one */
			}
      	}
      /* Transfer is on going, page receiving data */
      else
      {
        if (currentpagestatus == STATE_PAGE_RECEIVE)
        {
			  /* Check if receive page is not full */
			  if (uwAddressNextWrite < PAGE_SIZE)
			  {
				/* Return current receive page */
				return currentpage;
			  }
			  else
			  /* No more space in current receive page */
			  {
					/* Check if following page is erasing state */
					if (followingpagestatus == STATE_PAGE_ERASING)
					{
						  /* Force Cleanup, as not yet performed by user */
						  if (EE_CleanUp() != EE_OK)
						  {
							return EE_NO_PAGE_FOUND;
						  }
					}

					/* Set current receive page in valid state */
					if (SetPageState(currentpage, STATE_PAGE_VALID) != EE_OK)
					{
					  return EE_NO_PAGE_FOUND;
					}

					/* Set following page as receive */
					if (SetPageState(followingpage, STATE_PAGE_RECEIVE) != EE_OK)
					{
					  return EE_NO_PAGE_FOUND;
					}
					uwAddressNextWrite = PAGE_HEADER_SIZE;   /* Skip page header */
					return followingpage;         /* Following page is now active one */
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
    	  return currentpage;
      }
      else
      {
			if (currentpagestatus == STATE_PAGE_RECEIVE)
			{
				return previouspage;
			}
			else
			{
				return EE_NO_PAGE_FOUND;   /* No active Page */
			}
      }

    case FIND_ERASE_PAGE: /* ---- Return the erased page */

      if (followingpagestatus == STATE_PAGE_ERASED)
      {
    	  return followingpage;
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

EE_Status VerifyPagesFullWriteVariable(uint32_t VirtAddress, EE_DATA_TYPE Data)
{

	uint16_t crc = 0;
	/* Check if pages are full, i.e. max number of written elements achieved */
	  if (uhNbWrittenElements >= NB_MAX_WRITTEN_ELEMENTS)
	  {
		return EE_PAGE_FULL;
	  }

	  /* Get active Page for write operation */
	  uint32_t activepage = FindPage(FIND_WRITE_PAGE);
	  uint32_t activepageaddress = 0U;

	  /* Check if there is no active page */
	  if (activepage == EE_NO_PAGE_FOUND)
	  {
		return EE_ERROR_NOACTIVE_PAGE;
	  }

	  activepageaddress = PAGE_ADDRESS(activepage);

	  crc = xCrc16BitPolinomial_1021(Data, sizeof(Data),0);

	  	/* Program variable data, virtual address,and CRC*/
		/* If program operation was failed, a Flash error code is returned */
		if (BSP_OSPI_NOR_Write(0, (uint8_t *)&Data, (uint32_t)((activepageaddress+uwAddressNextWrite)-START_PAGE_ADDRESS), sizeof(Data)) != HAL_OK)
		{
			return HAL_ERROR;
		}
		if (BSP_OSPI_NOR_Write(0, (uint8_t *)&VirtAddress, (uint32_t)(((activepageaddress+uwAddressNextWrite)+4U)-START_PAGE_ADDRESS), sizeof(VirtAddress)) != HAL_OK)
		{
			return HAL_ERROR;
		}
		if (BSP_OSPI_NOR_Write(0, (uint8_t *)&crc, (uint32_t)(((activepageaddress+uwAddressNextWrite)+8U)-START_PAGE_ADDRESS), sizeof(crc)) != HAL_OK)
		{
			return HAL_ERROR;
		}
	/* Increment global variables relative to write operation done*/
		uwAddressNextWrite += 10U;
		uhNbWrittenElements++;

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
  *           - EE_CLEANUP_REQUIRED: on success
  *           - EE error code: if an error occurs
  */

EE_Status PagesTransfer(uint32_t VirtAddress, EE_DATA_TYPE Data, EE_Transfer_type Type)
{
	  EE_State_type pagestatus = STATE_PAGE_INVALID;
	  uint32_t pageaddress = 0U;
	  uint32_t page = 0U;
	  uint32_t varidx = 0U;
	  EE_ELEMENT_TYPE addressvalue = 0U;
	  EE_Status status = EE_OK;
	  EE_DATA_TYPE DataValue = 0U;
	  uint8_t ReadAddressValue[4]={0};
	  uint8_t DataValue1[4]={0};
	  uint32_t PAGE_FOR_ERASE = 0U;

	/* Get receive Page for transfer operation */
	page = FindPage((Type == EE_TRANSFER_NORMAL?FIND_ERASE_PAGE:FIND_WRITE_PAGE));

	if (page == EE_NO_PAGE_FOUND)
	{
	  return EE_ERROR_NOERASE_PAGE;
	}

	/* Reinitialize number of data written in the pages, and current active page */
	uhNbWrittenElements = 0U;
	ubCurrentActivePage = page;
	uwAddressNextWrite = PAGE_HEADER_SIZE;

	/* Mark the erased page at receive state in case of normal transfer */
	/* It is already the case in recover transfer case */
	/* If program operation was failed, a Flash error code is returned */
    if (Type == EE_TRANSFER_NORMAL)
    {
      if (SetPageState(page, STATE_PAGE_RECEIVE) != EE_OK)
      {
        return EE_WRITE_ERROR;
      }
    }

	/* Set the previous active page and all previous valid pages to erasing state */
	/* In case of recover transfer, some of these pages may already be marked erasing */
	page = PREVIOUS_PAGE(page);
	pageaddress = PAGE_ADDRESS(page);
	pagestatus = GetPageState(pageaddress);

	if ((pagestatus == STATE_PAGE_ACTIVE) || (pagestatus == STATE_PAGE_ERASING))
	{
		PAGE_FOR_ERASE = page;
			  /* Set active page to erasing */
			  if (pagestatus == STATE_PAGE_ACTIVE)
			  {
				if (SetPageState(page, STATE_PAGE_ERASING) != EE_OK)
				{
				  return EE_WRITE_ERROR;
				}
			  }

			  /* Inspect the previous pages to set all valid pages to erasing state */
			  /* In case of recover, some valid pages may be already erasing state */
			  page = PREVIOUS_PAGE(page);
			  pageaddress = PAGE_ADDRESS(page);
			  pagestatus = GetPageState(pageaddress);

			  while ((pagestatus == STATE_PAGE_VALID) || (pagestatus == STATE_PAGE_ERASING))
			  {
				  /* Set valid page to erasing */
				if (pagestatus == STATE_PAGE_VALID)
				{
					if (SetPageState(page, STATE_PAGE_ERASING) != EE_OK)
					  {
						return EE_WRITE_ERROR;
					  }
				}

				/* decrement page index */
				page = PREVIOUS_PAGE(page);
				pageaddress = PAGE_ADDRESS(page);
				pagestatus = GetPageState(pageaddress);
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
		for (varidx = PAGE_HEADER_SIZE; varidx < PAGE_SIZE; varidx += EE_ELEMENT_SIZE)
		{
		  /* Get next element in receive page */
		  //addressvalue = (*(__IO EE_ELEMENT_TYPE*)(PAGE_ADDRESS(ubCurrentActivePage) + varidx));

		  BSP_OSPI_NOR_Read(0, (uint8_t *)ReadAddressValue, (uint32_t)((PAGE_ADDRESS(ubCurrentActivePage)-START_PAGE_ADDRESS) + varidx), sizeof(ReadAddressValue));

		  BSP_OSPI_NOR_Read(0, (uint8_t *)DataValue1, (uint32_t)(((PAGE_ADDRESS(ubCurrentActivePage)-START_PAGE_ADDRESS) + varidx)+4U), sizeof(DataValue1));

			  for (int i = 0; i < 4; i++)
			  {
				  addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
				  addressvalue |= DataValue1[i]; // Add the byte from DataValue
			  }

			  for (int i = 0; i < 4; i++)
			  {
				  addressvalue <<= 8; // Shift the existing bits to the left by 8 bits
				  addressvalue |= ReadAddressValue[i]; // Add the byte from ReadAddressValue
			  }


			  if (addressvalue != EE_PAGESTAT_ERASED)
			  {
				  /* Update global variables accordingly */
				  uhNbWrittenElements++;
				  uwAddressNextWrite += EE_ELEMENT_SIZE;
			  }
			else
				{
					break;
				}
		  }
		/* Count number of elements already transferred in previous valid pages */
		page = ubCurrentActivePage;
	   for (varidx = 0U; varidx < PAGES_NUMBER; varidx++)
	   {
		 /* Decrement page index among circular pages list */
		 page = PREVIOUS_PAGE(page);
		 pagestatus = GetPageState(PAGE_ADDRESS(page));

		 /* Check if page is valid state */
		 if (pagestatus == STATE_PAGE_VALID)
		 {
		   /* Update uhNbWrittenElements with number of elements in page */
		   uhNbWrittenElements += NB_MAX_ELEMENTS_BY_PAGE;
		 }
		 else
		   {
			 break;
		   }
		}
	  }

	// Write the variable passed as parameter in the new active page
	// If program operation was failed, a Flash error code is returned
	  if (VerifyPagesFullWriteVariable(VirtAddress, Data) != EE_OK)
	  {
		return EE_WRITE_ERROR;
	  }

/* Transfer process: transfer variables from old to the new active page */
/* First element in receive page can be any one, the following elements are */
/* ordered from the beginning. */
/* In case of recovery, Pre-Last element in receive page could be */
/* corrupted if reset occured during write of this element, */
/* and last element is dummy value that we have just written. */
/* Transfer shall then resume from (uhNbWrittenElements-3) variable index */

  for (varidx = (uhNbWrittenElements >= 3U?(uhNbWrittenElements-3U+1U):1U); varidx < NB_OF_VARIABLES+1; varidx++)
  {
         /* Check each variable except the one passed as parameter */
      if (varidx != VirtAddress)
      {
        /* Read the last variable updates */
        status = ReadVariable(varidx, &DataValue);
        if (status == EE_OK)
        {
          /* In case variable corresponding to the virtual address was found */
          /* Transfer the variable to the new active page */
          /* If program operation was failed, a Flash error code is returned */

        	status = VerifyPagesFullWriteVariable(varidx, DataValue);
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
	if (SetPageState(ubCurrentActivePage, STATE_PAGE_ACTIVE) != EE_OK)
	{
	 return EE_WRITE_ERROR;
	}

	/* Return last operation flash status */
	if (EE_OK != EE_CleanUp())
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

 EE_Status EE_Init(EE_Erase_type EraseType)
{
	EE_State_type pagestatus = STATE_PAGE_INVALID;
	uint32_t page = 0U, pageaddress = 0U, varidx = 0U,
	nbactivepage = 0U, nbactivereceivepage = 0U, nbvalidpage = 0U,
	lastvalidpage = 0U, firstvalidpage = 0U,
	recoverytransfer = 0U;
	uint64_t addressvalue = 0U;

	EE_State_Reliability pagestate = STATE_RELIABLE;
	EE_Status status = EE_OK;

	/* check the flash end address with calculated end address for required variables*/
	if (CALCULATED_END_ADDRESS >= FLASH_END_ADDR)
	{
		return EE_MEMORY_NOT_SUFFICIENT;
	}

  /***************************************************************************/
  /* Step 1: Read all lines of the flash pages of eeprom emulation to        */
  /*         delete corrupted lines detectable through NMI                   */
  /***************************************************************************/

  /***************************************************************************/
  /* Step 2: Handle case of reset during transfer with no receive page       */
  /*         present, by setting missing receive page state                  */
  /***************************************************************************/

	/* Check if no active page and no receive page present */
	/* Browse all pages */

	  for (page = START_PAGE; page < (START_PAGE + PAGES_NUMBER); page++)
	  {
	    pageaddress = PAGE_ADDRESS(page);
	    pagestatus = GetPageState(pageaddress);

	    /* Search for active and receive page */
	    if ((pagestatus == STATE_PAGE_ACTIVE) || (pagestatus == STATE_PAGE_RECEIVE))
	    {
	      nbactivereceivepage++;
	    }
	    /* Keep index of first valid page, and last valid page */
	    else if (pagestatus == STATE_PAGE_VALID)
	    {
	      if (nbvalidpage == 0U)
	      {
	        firstvalidpage = page;
	      }
	      lastvalidpage = page;
	      nbvalidpage++;
	    }
	  }

	  /* Check if no active and no receive page have been detected */
	  if (nbactivereceivepage == 0U)
	  {
	    /* Check if valid pages have been detected */
		if (nbvalidpage > 0U)
		{
		/* Check state of page just before first valid page.
		If it is erasing page, then page after last valid page shall be set
		to receiving state */

			if (GetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(firstvalidpage))) == STATE_PAGE_ERASING)
			{
				if (SetPageState(FOLLOWING_PAGE(lastvalidpage), STATE_PAGE_RECEIVE) != EE_OK)
				{
				  return EE_WRITE_ERROR;
				}
			}
			}
		/* Format flash pages used for eeprom emulation in case no active, no receive, no valid pages are found */
		else
		{
		return EE_Format(EE_FORCED_ERASE);
		}
	  }


  /*********************************************************************/
  /* Step 3: Handle case of reset during transfer, by performing       */
  /*         transfer recovery                                         */
  /*********************************************************************/

	  /* Browse all pages */
	  for (page = START_PAGE; page < (START_PAGE + PAGES_NUMBER); page++)
	  {
	    pageaddress = PAGE_ADDRESS(page);
	    pagestatus = GetPageState(pageaddress);

	    /* Check if there is receive page, meaning transfer has been interrupted */
	    if (pagestatus == STATE_PAGE_RECEIVE)
	    {
	      /* Verify that receive page is a true one, not a corrupted page state */
	      /* Check if page is not the first page of a bloc */
	      if ((page != START_PAGE) && (page != (uint32_t)(START_PAGE + (PAGES_NUMBER / 2U))))
	      {
	        /* Check that previous page is valid state */
	        if (GetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(page))) == STATE_PAGE_VALID)
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
	        if (GetPageState(PAGE_ADDRESS(FOLLOWING_PAGE(page))) == STATE_PAGE_ERASED)
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
	        ubCurrentActivePage = page;

	        /* Resume the interrupted page transfer, using dummy new data */

		  if (PagesTransfer(0U, 0U, EE_TRANSFER_RECOVER) != EE_CLEANUP_REQUIRED)
	        {
	          return EE_TRANSFER_ERROR;
	        }

	        /* Memorize transfer recovery occured */
	        recoverytransfer = 1U;

	        /* transfer recovery is done, then stop searching receive page */
	        break;
	      }
	    }
	  }

	  /*********************************************************************/
	  /* Step 4: Verify presence of one unique active page                 */
	  /*         If more than one active page, raise error                 */
	  /*         If no active page present, set missing active page        */
	  /*********************************************************************/

	  /* Browse all pages to search for active pages */
	  nbactivepage = 0U;
	  for (page = START_PAGE; page < (START_PAGE + PAGES_NUMBER); page++)
	  {
	    pageaddress = PAGE_ADDRESS(page);
	    pagestatus = GetPageState(pageaddress);

	    /* Search for active page */
	    if (pagestatus == STATE_PAGE_ACTIVE)
	    {
	      /* Verify that active page is a true one, not a corrupted page state */
	      /* Check if page is not the first page of a bloc */
	      if ((page != START_PAGE) && (page != (uint32_t)(START_PAGE + (PAGES_NUMBER / 2U))))
	      {

	        /* Check that previous page is valid state */
	        if (GetPageState(PAGE_ADDRESS(PREVIOUS_PAGE(page))) == STATE_PAGE_VALID)
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
	        if (GetPageState(PAGE_ADDRESS(FOLLOWING_PAGE(page))) == STATE_PAGE_ERASED)
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
	        if (nbactivepage == 0U)
	        {
	          ubCurrentActivePage = page;
	          nbactivepage++;
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
	      lastvalidpage = page;
	    }
	  }

	  /* In case no active page is found, set page after last valid page to active state */
	  if (nbactivepage == 0U)
	  {
	    ubCurrentActivePage = FOLLOWING_PAGE(lastvalidpage);
	    if (SetPageState(ubCurrentActivePage, STATE_PAGE_ACTIVE) != EE_OK)
	    {
	      return EE_WRITE_ERROR;
	    }
	  }


  /*********************************************************************/
  /* Step 5: Initialize eeprom emulation global variables relative     */
  /*         to active page                                            */
  /*********************************************************************/

  /* Initialize global variables, with elements detected in active page */

  uhNbWrittenElements = 0U;
  uwAddressNextWrite = PAGE_HEADER_SIZE;
  for (varidx = PAGE_HEADER_SIZE; varidx < PAGE_SIZE; varidx += EE_ELEMENT_SIZE)
    {

	  uint32_t ReadAddressValue, DataValue;

	  BSP_OSPI_NOR_Read(0, (uint8_t *)&ReadAddressValue, (uint32_t)((PAGE_ADDRESS(ubCurrentActivePage)-START_PAGE_ADDRESS) + varidx), sizeof(ReadAddressValue));

	  BSP_OSPI_NOR_Read(0, (uint8_t *)&DataValue, (uint32_t)(((PAGE_ADDRESS(ubCurrentActivePage)-START_PAGE_ADDRESS) + varidx)+4), sizeof(DataValue));

	  /* Adding two values to form element */

	  addressvalue =((uint64_t)DataValue << 32) | ReadAddressValue;

      if (addressvalue != EE_MASK_FULL)
	  {
		/* Then increment uhNbWrittenElements and uwAddressNextWrite */
		uhNbWrittenElements++;
		uwAddressNextWrite += EE_ELEMENT_SIZE;
	  }
	  else /* no more element in the page */
	  {
		break;
	  }
	}

  /*********************************************************************/
  /* Step 6: Finalize eeprom emulation global variables relative       */
  /*         to valid pages, and check consistency of pages sequence   */
  /*********************************************************************/

  /* Check consistency of pages sequence: one active page, optionnally some valid pages before */
  /* Update global variable uhNbWrittenElements if valid pages are found */
  page = ubCurrentActivePage;
  firstvalidpage = ubCurrentActivePage;
  while ((page != START_PAGE) && (page != (uint32_t)(START_PAGE + (PAGES_NUMBER / 2U))))
  {
    /* Decrement page index among circular pages list */
    page = PREVIOUS_PAGE(page);
    pagestatus = GetPageState(PAGE_ADDRESS(page));

    /* Check if page is valid state */
    if (pagestatus == STATE_PAGE_VALID)
    {
      /* Update uhNbWrittenElements with number of elements in full page */
      uhNbWrittenElements += NB_MAX_ELEMENTS_BY_PAGE;

      /* Keep index of first valid page */
      firstvalidpage = page;
    }
    else
    {
      /* Error: Pages sequence is not consistent */
      return EE_INVALID_PAGE_SEQUENCE;
    }
  }

	/*********************************************************************/
	/* Step 7: Ensure empty pages are erased                             */
	/*********************************************************************/

    /* Ensure all pages after active page, until first valid page, are erased */
    page = FOLLOWING_PAGE(ubCurrentActivePage);
    pageaddress = PAGE_ADDRESS(page);

    while (page != firstvalidpage)
    {
      /* Check if page erase has to be forced unconditionally (default case) */
      if (EraseType == EE_FORCED_ERASE )
      {
        /* Force page erase independently of its content */

        if (BSP_OSPI_NOR_Erase_Block(0, (uint32_t)(pageaddress-START_PAGE_ADDRESS), BSP_OSPI_NOR_ERASE_4K)!= EE_OK)
        {
          return EE_ERASE_ERROR;
        }
      }
      else /* EraseType == EE_CONDITIONAL_ERASE */
      {
        /* Check if page is fully erased */
        if (VerifyPageFullyErased(pageaddress, PAGE_SIZE) == EE_PAGE_NOTERASED)
        {
          /* Erase pages if not fully erased */
          if (BSP_OSPI_NOR_Erase_Block(0, (uint32_t)(pageaddress-START_PAGE_ADDRESS), BSP_OSPI_NOR_ERASE_4K)!= EE_OK)
          {
            return EE_ERASE_ERROR;
          }
        }
      }

      /* Increment page index among circular pages list, to get first page to erased */
      page = FOLLOWING_PAGE(page);
      pageaddress = PAGE_ADDRESS(page);
    }

		printf( "uhNbWrittenElements=%d\n",uhNbWrittenElements);
		printf( "ubCurrentActivePage=%d\n",ubCurrentActivePage);
		printf( "uwAddressNextWrite=%lu\n",uwAddressNextWrite);

 return EE_OK;
}
