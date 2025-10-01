/*
 * numpad.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "numpad.hpp"

uint16_t adc_buff_written;
uint16_t adc_buff_read;

uint16_t* ptr_adc_written_buff = &adc_buff_written;
uint16_t* ptr_adc_read_buff = &adc_buff_read;


HAL_StatusTypeDef numpadEnable()
{
	return HAL_TIM_Base_Start_IT( &dmaCyclerTimer );

}

HAL_StatusTypeDef numpadDisable()
{
	return HAL_TIM_Base_Stop_IT(&dmaCyclerTimer);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim == &dmaCyclerTimer)
	{
		uint16_t* tmp = ptr_adc_read_buff;
		ptr_adc_read_buff = ptr_adc_written_buff;
		ptr_adc_written_buff = tmp;

		HAL_ADC_Start_DMA(&configedADC, (uint32_t*)ptr_adc_written_buff, 1);
	}

}

uint8_t adcValue2Digit()
{
	if(adc_buff_read > 3000)
	{
		return 3;
	}
	else if(adc_buff_read > 1800)
	{
		return 2;
	}
	else if(adc_buff_read > 1000)
	{
		return 1;
	}

	return 10; //10 is not a numbert on the numpad therefore used as default wrong value
}
