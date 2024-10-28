/*
 * moving_avg.c
 *
 *  Created on: 14-Jul-2023
 *      Author: 91970
 */
/** \addtogroup APP
 *  @{
 * @file moving_avg.c
 *
 * @brief Application file handling the business logic
 *
 * Author: Srujith
 *
 * Create Date: 17th-july-2023
 *
 * Copyright:  All information contained herein is, and remains the property of
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED and its suppliers, if any.
 * Dissemination of this information or reproduction of this material is strictly
 * forbidden unless prior written permission is obtained from
 * eSTAR TECHNOLOGIES(OPC) PRIVATE LIMITED
 ********************************************************************************************* @}*/
#include "moving_avg.h"
#include "stdint.h"

//uint32_t fl_mv_return_f32 = 0.0;
//uint32_t fl_sum_f64 = 0.0;
uint32_t calculateMovingAverage(uint32_t p_rawData_f32, MV_data_t * p_ma_data_ptr)
{
	uint32_t fl_mv_return_f32 = 0.0;
	uint32_t fl_sum_f64 = 0;
	uint16_t fl_data_index_U16 = p_ma_data_ptr->window_index; // 6
	uint16_t fl_avg_loop_counter_U16 = 0;
	//printf("rS: %d\n", p_rawData_f32); // p_rawData_f32 == Speed values

	p_ma_data_ptr->dataInp_ptr[p_ma_data_ptr->raw_ip_index] = p_rawData_f32; //AVS[0] = Speed values

	//printf("MA_Vs_RPM_input_Data[%d]: %ld\n", p_ma_data_ptr->raw_ip_index, p_ma_data_ptr->dataInp_ptr[p_ma_data_ptr->raw_ip_index]);
	//printf("raw_ip_index: %d\n", p_ma_data_ptr->raw_ip_index);

	if(p_ma_data_ptr->min_raw_data_counter <= p_ma_data_ptr->window_size)
	{
		p_ma_data_ptr->min_raw_data_counter++;
		//printf("min_raw_data_counter: %d\n", p_ma_data_ptr->min_raw_data_counter);
	}
	else
	{
		for(fl_avg_loop_counter_U16 = 0; fl_avg_loop_counter_U16 < p_ma_data_ptr->window_size; fl_avg_loop_counter_U16++)
		{
			fl_sum_f64 += p_ma_data_ptr->dataInp_ptr[fl_data_index_U16];
			//printf("arrayy : %d\n\r ", p_ma_data_ptr->dataInp_ptr[fl_data_index_U16]);
		//	printf("fl_sum_f64: %ld\n", fl_sum_f64);

			if(fl_data_index_U16 < (p_ma_data_ptr->raw_data_size) -1 )
			{
				fl_data_index_U16++;
				//printf("fl_data_index_U16: %d\n",fl_data_index_U16);
			}
			else
			{
				fl_data_index_U16 = 0;
			}
		}

		fl_mv_return_f32 = (uint32_t)(fl_sum_f64/p_ma_data_ptr->window_size);
	//	printf("fl_mv_return_f32: %ld\n", fl_mv_return_f32);
	   if(p_ma_data_ptr->window_index < (p_ma_data_ptr->raw_data_size - 1))
	   {
			p_ma_data_ptr->window_index++;
			//printf("window_index: %d\n", p_ma_data_ptr->window_index);
	   }
	   else
	   {
		   p_ma_data_ptr->window_index =0;
	   }
	}

	if(p_ma_data_ptr->raw_ip_index < (p_ma_data_ptr->raw_data_size - 1))
	{
		p_ma_data_ptr->raw_ip_index++;
	}
	else
	{
		p_ma_data_ptr->raw_ip_index = 0;
	}
	//printf("fl_mv_return_f32: %d\n", fl_mv_return_f32);
	return (fl_mv_return_f32);
}

/**
 * @brief First-Order Moving Average Filter
 *
 * This function applies a first-order moving average filter to the input raw data.
 * The filter calculates the average value based on a specified window size.
 *
 * @param p_rawData_f32        Input raw data to be filtered.
 * @param p_ma_data_ptr       Pointer to the data structure holding moving average filter parameters.
 *
 * @return Filtered output value after applying the first-order moving average filter.
 */
uint32_t MovingAverage_1stOrder_filter(uint32_t p_rawData_f32, MV_1stOrderFilter_data_t * p_ma_data_ptr)
{/** @startuml */ /** start */
	uint32_t fl_mv_return_f32 = 0.0;

	if(p_ma_data_ptr->min_raw_data_counter < p_ma_data_ptr->window_size)
	{/**if(Check if minimum raw data counter is less than the window size) then(YES)*/

		 /**:Increment the minimum raw data counter;*/
		p_ma_data_ptr->min_raw_data_counter++;
		/**:Add the raw data to the raw data sum;*/
		p_ma_data_ptr->raw_data_sum += p_rawData_f32;

		/**:Check if the minimum raw data counter equals the window size;*/
		if(p_ma_data_ptr->min_raw_data_counter == p_ma_data_ptr->window_size)
		{/**if(Check if the minimum raw data counter equals the window size) then(YES)*/

			/**:Calculate the filtered output using the raw data sum and window size;*/
			fl_mv_return_f32 = (uint32_t)((p_ma_data_ptr->raw_data_sum)/(p_ma_data_ptr->window_size));
		}/**endif*/
	}
	else
	{/**else (FALSE)*/
		/**:Update the raw data sum by subtracting the last averaged value and adding the new raw data;*/
		p_ma_data_ptr->raw_data_sum = (p_ma_data_ptr->raw_data_sum - p_ma_data_ptr->last_avg_value) + p_rawData_f32;
		/**:Calculate the filtered output using the updated raw data sum and window size;*/
		fl_mv_return_f32 = (uint32_t)((p_ma_data_ptr->raw_data_sum)/(p_ma_data_ptr->window_size));
	}/**endif*/

	//printf("min_raw_data_counter: %d\n", p_ma_data_ptr->min_raw_data_counter);
	//printf("raw_data_sum: %f\n", p_ma_data_ptr->raw_data_sum);
	//printf("fl_mv_return_f32: %f\n", fl_mv_return_f32);

	 /**:Update the last averaged value;*/
	p_ma_data_ptr->last_avg_value = fl_mv_return_f32;
	 /**:Update the last averaged value;*/
	return (fl_mv_return_f32);
}/** end*/ /** @enduml */
