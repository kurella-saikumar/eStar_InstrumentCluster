/** \addtogroup
 *  @{
 * @file DisplayInit.c
 * @file DisplayInit.h
 * @brief Template Source File
 *
 * File Short Name:
 *
 * Author:
 *
 * Create Date:
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 **********************************************************************************************/

/**************************************************************************************************
 * Include Platform or Standard Headers
 ***************************************************************************************************/

/**************************************************************************************************
 * Include Project Specific Headers
 ***************************************************************************************************/

#include "DisplayInit.h"
#include "main.h"
#include "string.h"
#include "cmsis_os.h"
#include "libjpeg.h"
#include "app_touchgfx.h"
#include "InstrumentClusterInit.h"
#include "stm32h735g_discovery_ospi.h"
#include <touchgfx/hal/Config.hpp>
#include "eeprom_emul.h"

/**************************************************************************************************
 * DEFINE FILE SCOPE MACROS
 ***************************************************************************************************/

/**************************************************************************************************
 * DEFINE FILE SCOPE TYPES
 ***************************************************************************************************/

/**************************************************************************************************
 * DECLARE GLOBAL VARIABLES
 ***************************************************************************************************/



KEEP extern const unsigned char image_abs_detection1_const[];
KEEP extern const unsigned char image_abs_detection2_const[];
KEEP extern const unsigned char image_background_const[];
KEEP extern const unsigned char image_clustericons1_const[];
KEEP extern const unsigned char image_clustericons2_const[];
KEEP extern const unsigned char image_doorswarning1_const[];
KEEP extern const unsigned char image_doorswarning2_const[];
KEEP extern const unsigned char image_engineoil1_const[];
KEEP extern const unsigned char image_engineoil2_const[];
KEEP extern const unsigned char image_enginewarning_w_const[];
KEEP extern const unsigned char image_enginewarning_y_const[];
KEEP extern const unsigned char image_fuelbar01_const[];
KEEP extern const unsigned char image_fuelbar02_const[];
KEEP extern const unsigned char image_fuelbar03_const[];
KEEP extern const unsigned char image_fuelbar04_const[];
KEEP extern const unsigned char image_fuelbar05_const[];
KEEP extern const unsigned char image_fuelbar06_const[];
KEEP extern const unsigned char image_fuelbar07_const[];
KEEP extern const unsigned char image_fuelbar08_const[];
KEEP extern const unsigned char image_fuelbar09_const[];
KEEP extern const unsigned char image_fuelbar10_const[];
KEEP extern const unsigned char image_high_beam_const[];
KEEP extern const unsigned char image_high_beam_1_const[];
KEEP extern const unsigned char image_highbeam1_const[];
KEEP extern const unsigned char image_highbeam2_const[];
KEEP extern const unsigned char image_leftindicator1_const[];
KEEP extern const unsigned char image_leftindicator2_const[];
KEEP extern const unsigned char image_lowbattery1_const[];
KEEP extern const unsigned char image_lowbattery2_const[];
KEEP extern const unsigned char image_lowbeam1_const[];
KEEP extern const unsigned char image_lowbeam2_const[];
KEEP extern const unsigned char image_parking_r_const[];
KEEP extern const unsigned char image_parking_w_const[];
KEEP extern const unsigned char image_rightindicator1_const[];
KEEP extern const unsigned char image_rightindicator2_const[];
KEEP extern const unsigned char image_rpmbar01_const[];
KEEP extern const unsigned char image_rpmbar02_const[];
KEEP extern const unsigned char image_rpmbar03_const[];
KEEP extern const unsigned char image_rpmbar04_const[];
KEEP extern const unsigned char image_rpmbar05_const[];
KEEP extern const unsigned char image_rpmbar06_const[];
KEEP extern const unsigned char image_rpmbar07_const[];
KEEP extern const unsigned char image_rpmbar08_const[];
KEEP extern const unsigned char image_rpmbar09_const[];
KEEP extern const unsigned char image_rpmbar10_const[];
KEEP extern const unsigned char image_rpmicon1_const[];
KEEP extern const unsigned char image_rpmicon2_const[];
KEEP extern const unsigned char image_seatbelt_r_const[];
KEEP extern const unsigned char image_seatbelt_w_const[];
KEEP extern const unsigned char image_servicereminder_w_const[];
KEEP extern const unsigned char image_servicereminder_y_const[];
KEEP extern const unsigned char image_tempicon1_const[];
KEEP extern const unsigned char image_tempicon2_const[];

#if 1
extern unsigned char ucImage_abs_detection1_HypRAM[64*64];
extern unsigned char ucImage_abs_detection2_HypRAM[64*64];
extern unsigned char ucImage_background_HypRAM[480*272];
extern unsigned char ucImage_clustericons1_HypRAM[64*64];
extern unsigned char ucImage_clustericons2_HypRAM[64*64];
extern unsigned char ucImage_doorswarning1_HypRAM[64*64];
extern unsigned char ucImage_doorswarning2_HypRAM[64*64];
extern unsigned char ucImage_engineoil1_HypRAM[64*64];
extern unsigned char ucImage_engineoil2_HypRAM[64*64];
extern unsigned char ucImage_enginewarning_w_HypRAM[64*64];
extern unsigned char ucImage_enginewarning_y_HypRAM[64*64];
extern unsigned char ucImage_fuelbar01_HypRAM[75*128];
extern unsigned char ucImage_fuelbar02_HypRAM[75*128];
extern unsigned char ucImage_fuelbar03_HypRAM[75*128];
extern unsigned char ucImage_fuelbar04_HypRAM[75*128];
extern unsigned char ucImage_fuelbar05_HypRAM[75*128];
extern unsigned char ucImage_fuelbar06_HypRAM[75*128];
extern unsigned char ucImage_fuelbar07_HypRAM[75*128];
extern unsigned char ucImage_fuelbar08_HypRAM[75*128];
extern unsigned char ucImage_fuelbar09_HypRAM[75*128];
extern unsigned char ucImage_fuelbar10_HypRAM[75*128];
extern unsigned char ucImage_highbeam1_HypRAM[64*64];
extern unsigned char ucImage_highbeam2_HypRAM[64*64];
extern unsigned char ucImage_leftindicator1_HypRAM[64*64];
extern unsigned char ucImage_leftindicator2_HypRAM[64*64];
extern unsigned char ucImage_lowbattery1_HypRAM[64*64];
extern unsigned char ucImage_lowbattery2_HypRAM[64*64];
extern unsigned char ucImage_lowbeam1_HypRAM[64*64];
extern unsigned char ucImage_lowbeam2_HypRAM[64*64];
extern unsigned char ucImage_parking_r_HypRAM[64*64];
extern unsigned char ucImage_parking_w_HypRAM[64*64];
extern unsigned char ucImage_rightindicator1_HypRAM[64*64];
extern unsigned char ucImage_rightindicator2_HypRAM[64*64];
extern unsigned char ucImage_rpmbar01_HypRAM[75*128];
extern unsigned char ucImage_rpmbar02_HypRAM[75*128];
extern unsigned char ucImage_rpmbar03_HypRAM[75*128];
extern unsigned char ucImage_rpmbar04_HypRAM[75*128];
extern unsigned char ucImage_rpmbar05_HypRAM[75*128];
extern unsigned char ucImage_rpmbar06_HypRAM[75*128];
extern unsigned char ucImage_rpmbar07_HypRAM[75*128];
extern unsigned char ucImage_rpmbar08_HypRAM[75*128];
extern unsigned char ucImage_rpmbar09_HypRAM[75*128];
extern unsigned char ucImage_rpmbar10_HypRAM[75*128];
extern unsigned char ucImage_rpmicon1_HypRAM[64*64];
extern unsigned char ucImage_rpmicon2_HypRAM[64*64];
extern unsigned char ucImage_seatbelt_r_HypRAM[64*64];
extern unsigned char ucImage_seatbelt_w_HypRAM[64*64];
extern unsigned char ucImage_servicereminder_w_HypRAM[64*64];
extern unsigned char ucImage_servicereminder_y_HypRAM[64*64];
extern unsigned char ucImage_tempicon1_HypRAM[64*64];
extern unsigned char ucImage_tempicon2_HypRAM[64*64];

#endif


void Disp_imgDataHyperRAM_Init(void)
{


	memset(ucImage_abs_detection1_HypRAM, 0 ,(64*64));
	memset(ucImage_abs_detection2_HypRAM, 0 ,(64*64));
	memset(ucImage_background_HypRAM, 0 ,(480*272));
	memset(ucImage_clustericons1_HypRAM, 0 ,(64*64));
	memset(ucImage_clustericons2_HypRAM, 0 ,(64*64));
	memset(ucImage_doorswarning1_HypRAM, 0 ,(64*64));
	memset(ucImage_doorswarning2_HypRAM, 0 ,(64*64));
	memset(ucImage_engineoil1_HypRAM, 0 ,(64*64));
	memset(ucImage_engineoil2_HypRAM, 0 ,(64*64));
	memset(ucImage_enginewarning_w_HypRAM, 0 ,(64*64));
	memset(ucImage_enginewarning_y_HypRAM, 0 ,(64*64));
	memset(ucImage_fuelbar01_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar02_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar03_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar04_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar05_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar06_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar07_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar08_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar09_HypRAM, 0 ,(75*128));
	memset(ucImage_fuelbar10_HypRAM, 0 ,(75*128));
//	memset(ucImage_high_beam_HypRAM, 0 ,(64*64));
//	memset(ucImage_high_beam_1_HypRAM, 0 ,(50*50));
	memset(ucImage_highbeam1_HypRAM, 0 ,(64*64));
	memset(ucImage_highbeam2_HypRAM, 0 ,(64*64));
	memset(ucImage_leftindicator1_HypRAM, 0 ,(64*64));
	memset(ucImage_leftindicator2_HypRAM, 0 ,(64*64));
	memset(ucImage_lowbattery1_HypRAM, 0 ,(64*64));
	memset(ucImage_lowbattery2_HypRAM, 0 ,(64*64));
	memset(ucImage_lowbeam1_HypRAM, 0 ,(64*64));
	memset(ucImage_lowbeam2_HypRAM, 0 ,(64*64));
	memset(ucImage_parking_r_HypRAM, 0 ,(64*64));
	memset(ucImage_parking_w_HypRAM, 0 ,(64*64));
	memset(ucImage_rightindicator1_HypRAM, 0 ,(64*64));
	memset(ucImage_rightindicator2_HypRAM, 0 ,(64*64));
	memset(ucImage_rpmbar01_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar02_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar03_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar04_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar05_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar06_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar07_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar08_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar09_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmbar10_HypRAM, 0 ,(75*128));
	memset(ucImage_rpmicon1_HypRAM, 0 ,(64*64));
	memset(ucImage_rpmicon2_HypRAM, 0 ,(64*64));
	memset(ucImage_seatbelt_r_HypRAM, 0 ,(64*64));
	memset(ucImage_seatbelt_w_HypRAM, 0 ,(64*64));
	memset(ucImage_servicereminder_w_HypRAM, 0 ,(64*64));
	memset(ucImage_servicereminder_y_HypRAM, 0 ,(64*64));
	memset(ucImage_tempicon1_HypRAM, 0 ,(64*64));
	memset(ucImage_tempicon2_HypRAM, 0 ,(64*64));

#if 1
	uint32_t Address1= (uint32_t )(&image_abs_detection1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_abs_detection1_HypRAM,Address1,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-1\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success1\n\r");
#endif
	}

	uint32_t Address2= (uint32_t )(&image_abs_detection2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_abs_detection2_HypRAM,Address2,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-2\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success2\n\r");
#endif
	}

	uint32_t Address3= (uint32_t )(&image_background_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_background_HypRAM,Address3,(480*272*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-3\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success3\n\r");
#endif
	}

	uint32_t Address4= (uint32_t )(&image_clustericons1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_clustericons1_HypRAM,Address4,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-4\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success4\n\r");
#endif
	}

	uint32_t Address5= (uint32_t )(&image_clustericons2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_clustericons2_HypRAM,Address5,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-5\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success5\n\r");
#endif
	}

	uint32_t Address6= (uint32_t )(&image_doorswarning1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_doorswarning1_HypRAM,Address6,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-6\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success6\n\r");
#endif
	}

	uint32_t Address7= (uint32_t )(&image_doorswarning2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_doorswarning2_HypRAM,Address7,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-7\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success7\n\r");
#endif
	}

	uint32_t Address8= (uint32_t )(&image_engineoil1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_engineoil1_HypRAM,Address8,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-8\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success8\n\r");
#endif
	}

	uint32_t Address9= (uint32_t )(&image_engineoil2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_engineoil2_HypRAM,Address9,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-9\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success9\n\r");
#endif
	}

	uint32_t Address10= (uint32_t )(&image_enginewarning_w_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_enginewarning_w_HypRAM,Address10,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-10\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success10\n\r");
#endif
	}

	uint32_t Address11= (uint32_t )(&image_enginewarning_y_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_enginewarning_y_HypRAM,Address11,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-11\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success11\n\r");
#endif
	}


	uint32_t Address12= (uint32_t )(&image_fuelbar01_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar01_HypRAM,Address12,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-12\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success12\n\r");
#endif
	}
	uint32_t Address13= (uint32_t )(&image_fuelbar02_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar02_HypRAM,Address13,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-13\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success13\n\r");
#endif
	}
	uint32_t Address14= (uint32_t )(&image_fuelbar03_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar03_HypRAM,Address14,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-14\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success14\n\r");
#endif
	}

	uint32_t Address15= (uint32_t )(&image_fuelbar04_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar04_HypRAM,Address15,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-15\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success15\n\r");
#endif
	}

	uint32_t Address16= (uint32_t )(&image_fuelbar05_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar05_HypRAM,Address16,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-16\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success16\n\r");
#endif
	}

	uint32_t Address17= (uint32_t )(&image_fuelbar06_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar06_HypRAM,Address17,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-17\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success17\n\r");
#endif
	}

	uint32_t Address18= (uint32_t )(&image_fuelbar07_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar07_HypRAM,Address18,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-18\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success18\n\r");
#endif
	}

	uint32_t Address19= (uint32_t )(&image_fuelbar08_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar08_HypRAM,Address19,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-19\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success19\n\r");
#endif
	}

	uint32_t Address20= (uint32_t )(&image_fuelbar09_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar09_HypRAM,Address20,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-20\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success20\n\r");
#endif
	}

	uint32_t Address21= (uint32_t )(&image_fuelbar10_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_fuelbar10_HypRAM,Address21,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-21\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success21\n\r");
#endif
	}
#if 0
	uint32_t Address22= (uint32_t )(&image_high_beam_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_high_beam_HypRAM,Address22,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-22\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success22\n\r");
#endif
	}

	uint32_t Address23= (uint32_t )(&image_high_beam_1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_high_beam_1_HypRAM,Address23,(50*50*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-23\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success23\n\r");
#endif
	}
#endif
	uint32_t Address24= (uint32_t )(&image_highbeam1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_highbeam1_HypRAM,Address24,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-24\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success24\n\r");
#endif
	}

	uint32_t Address25= (uint32_t )(&image_highbeam2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_highbeam2_HypRAM,Address25,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-25\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success25\n\r");
#endif
	}


	uint32_t Address26= (uint32_t )(&image_leftindicator1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_leftindicator1_HypRAM,Address26,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-26\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success26\n\r");
#endif
	}

	uint32_t Address27= (uint32_t )(&image_leftindicator2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_leftindicator2_HypRAM,Address27,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-27\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success27\n\r");
#endif
	}

	uint32_t Address28= (uint32_t )(&image_lowbattery1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbattery1_HypRAM,Address28,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-28\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success28\n\r");
#endif
	}

	uint32_t Address29= (uint32_t )(&image_lowbattery2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbattery2_HypRAM,Address29,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-29\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success29\n\r");
#endif
	}

	uint32_t Address30= (uint32_t )(&image_lowbeam1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbeam1_HypRAM,Address30,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-30\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success30\n\r");
#endif
	}

	uint32_t Address31= (uint32_t )(&image_lowbeam2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_lowbeam2_HypRAM,Address31,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-31\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success31\n\r");
#endif
	}

	uint32_t Address32= (uint32_t )(&image_parking_r_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_parking_r_HypRAM,Address32,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-32\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success32\n\r");
#endif
	}

	uint32_t Address33= (uint32_t )(&image_parking_w_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_parking_w_HypRAM,Address33,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-33\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success33\n\r");
#endif
	}

	uint32_t Address34= (uint32_t )(&image_rightindicator1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rightindicator1_HypRAM,Address34,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-34\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success34\n\r");
#endif
	}

	uint32_t Address35= (uint32_t )(&image_rightindicator2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rightindicator2_HypRAM,Address35,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-35\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success35\n\r");
#endif
	}


	uint32_t Address36= (uint32_t )(&image_rpmbar01_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar01_HypRAM,Address36,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-36\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success36\n\r");
#endif
	}

	uint32_t Address37= (uint32_t )(&image_rpmbar02_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar02_HypRAM,Address37,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-37\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success37\n\r");
#endif
	}

	uint32_t Address38= (uint32_t )(&image_rpmbar03_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar03_HypRAM,Address38,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-38\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success38\n\r");
#endif
	}

	uint32_t Address39= (uint32_t )(&image_rpmbar04_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar04_HypRAM,Address39,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-39\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success39\n\r");
#endif
	}

	uint32_t Address40= (uint32_t )(&image_rpmbar05_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar05_HypRAM,Address40,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-40\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success40\n\r");
#endif
	}

	uint32_t Address41= (uint32_t )(&image_rpmbar06_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar06_HypRAM,Address41,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-41\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success41\n\r");
#endif
	}

	uint32_t Address42= (uint32_t )(&image_rpmbar07_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar07_HypRAM,Address42,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-42\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success42\n\r");
#endif
	}

	uint32_t Address43= (uint32_t )(&image_rpmbar08_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar08_HypRAM,Address43,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-43\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success43\n\r");
#endif
	}

	uint32_t Address44= (uint32_t )(&image_rpmbar09_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar09_HypRAM,Address44,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-44\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success44\n\r");
#endif
	}


	uint32_t Address45= (uint32_t )(&image_rpmbar10_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmbar10_HypRAM,Address45,(75*128*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-45\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success45\n\r");
#endif
	}

	uint32_t Address46= (uint32_t )(&image_rpmicon1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmicon1_HypRAM,Address46,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-46\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success46\n\r");
#endif
	}

	uint32_t Address47= (uint32_t )(&image_rpmicon2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_rpmicon2_HypRAM,Address47,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-47\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success47\n\r");
#endif
	}


	uint32_t Address48= (uint32_t )(&image_seatbelt_r_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_seatbelt_r_HypRAM,Address48,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-48\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success48\n\r");
#endif
	}

	uint32_t Address49= (uint32_t )(&image_seatbelt_w_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_seatbelt_w_HypRAM,Address49,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-49\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success49\n\r");
#endif
	}

	uint32_t Address50= (uint32_t )(&image_servicereminder_w_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_servicereminder_w_HypRAM,Address50,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-50\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success50\n\r");
#endif
	}

	uint32_t Address51= (uint32_t )(&image_servicereminder_y_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_servicereminder_y_HypRAM,Address51,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-51\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success51\n\r");
#endif
	}

	uint32_t Address52= (uint32_t )(&image_tempicon1_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_tempicon1_HypRAM,Address52,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-52\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success52\n\r");
#endif
	}

	uint32_t Address53= (uint32_t )(&image_tempicon2_const[0] - FLASH_BASE_ADDR);
	if(BSP_OSPI_NOR_Read(BSP_INSTANCE,ucImage_tempicon2_HypRAM,Address53,(64*64*4)))
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Fail-53\n\r");
#endif
	}
	else
	{
#if(DBGPrints_TestMacro == 1)
		printf("Copy Success53\n\r");
#endif
	}
#endif

}




