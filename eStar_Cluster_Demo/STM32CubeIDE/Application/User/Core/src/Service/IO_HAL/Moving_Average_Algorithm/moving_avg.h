/*
 * moving_avg.h
 *
 *  Created on: 14-Jul-2023
 *      Author: 91970
 */

#ifndef MOVING_AVG_H
#define MOVING_AVG_H

#include "stdint.h"

typedef struct
{
	uint32_t * dataInp_ptr;
	uint32_t raw_data_size;
	uint16_t window_size;
	uint16_t window_index;
	uint16_t raw_ip_index;
	uint16_t min_raw_data_counter;
}MV_data_t;

typedef struct
{
	double raw_data_sum;
	uint16_t window_size;
	uint16_t min_raw_data_counter;
	uint32_t last_avg_value;
}MV_1stOrderFilter_data_t;

uint32_t calculateMovingAverage(uint32_t p_rawData_f32, MV_data_t * p_ma_data_ptr);
uint32_t MovingAverage_1stOrder_filter(uint32_t p_rawData_f32, MV_1stOrderFilter_data_t * p_ma_data_ptr);


#endif /* MOVING_AVG_H */
