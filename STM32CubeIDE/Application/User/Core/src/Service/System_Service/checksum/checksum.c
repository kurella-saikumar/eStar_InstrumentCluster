/** \addtogroup CHECKSUM
 *  @{
 * @file checksum.c
 *
 * @brief checksum Source File
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
********************************************************************************************** @}*/

/**************************************************************************************************
 * Include Platform or Standard Headers
***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
***************************************************************************************************/
#include "checksum.h"
/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
***************************************************************************************************/
#define POLYNOMIAL 0x1021U
#define WIDTH (8U * sizeof(resultType))
#define MSb ((resultType)1 << (WIDTH - 1U))
/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DECLARE FILE SCOPE STATIC VARIABLES
***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE STATIC FUNCTION PROTOTYPES
***************************************************************************************************/

/**************************************************************************************************
 * FUNCTION DEFINITIONS
***************************************************************************************************/
/**
 * @brief Calculates a 16-bit CRC using the polynomial 1021
 *
 * This function calculates a 16-bit CRC checksum using the polynomial 1021
 * for a given data buffer.
 *
 * @param[in] pucData Pointer to the data buffer
 * @param[in] ulDataSize Size of the data buffer
 * @param[in] uxRemainder Initial or previous remainder value
 *
 * @return resultType Calculated CRC checksum value
 */
resultType xCrc16BitPolinomial_1021(const uint8_t * pucData, uint32_t ulDataSize, resultType uxRemainder)
{
	/** @startuml */ /** start */
    uint32_t ulPos;
    uint8_t ucBitp;
	resultType uxChecksum;
	uxChecksum = uxRemainder;
    for (ulPos = 0U; ulPos < ulDataSize; ulPos++)
    {/**:while (valid data) is (taking each valid data based on position checking);*/
    	uxChecksum ^= ((resultType)pucData[ulPos] << (WIDTH - 8U));

    	/**: Process each bit in the byte;*/
        for (ucBitp = 8U; ucBitp > 0U; ucBitp--)
        {
            if ((uxChecksum & MSb) != 0U)
            {
            	/**: Shift the checksum by one bit to the left and XOR with the POLYNOMIAL value;*/
            	uxChecksum = ((uint16_t)(uxChecksum << 1U)) ^ POLYNOMIAL;
            }
            else
            {
            	/**: Shift the checksum by one bit to the left;*/
            	uxChecksum <<= 1U;
            }
        }
        /**: endwhile (All valid data bytes are taken);*/
    }
    /**: Return calculated checksum */
    return uxChecksum;
	 /** end*/ /** @enduml */
}
/**************************************************************************************************
 * End Of File
***************************************************************************************************/
