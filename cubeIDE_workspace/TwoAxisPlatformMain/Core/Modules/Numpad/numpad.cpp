/*
 * numpad.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "numpad.hpp"

uint16_t adc_buff_a;
uint16_t adc_buff_b;

uint16_t* ptr_adc_written_buff = &adc_buff_a;
uint16_t* ptr_adc_read_buff = &adc_buff_b;


HAL_StatusTypeDef numpadEnable()
{
	return HAL_TIM_Base_Start_IT( &ADCtimer );
	return HAL_ADC_Start(&configedADC);
}

HAL_StatusTypeDef numpadDisable()
{
	return HAL_ADC_Stop(&configedADC);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim == &ADCtimer)
	{
		HAL_ADC_Start(&configedADC);
	}

}


uint8_t adcValue2Digit()
{
	uint16_t ADCval = (uint16_t)HAL_ADC_GetValue(&configedADC);


	if(ADCval > 3000)
	{
		return 3;
	}
	else if(ADCval > 1800)
	{
		return 2;
	}
	else if(ADCval > 1000)
	{
		return 1;
	}

	return 10; //10 is not a numbert on the numpad therefore used as default wrong value
}
