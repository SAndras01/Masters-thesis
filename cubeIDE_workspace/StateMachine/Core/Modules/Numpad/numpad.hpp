/*
 * mumpad.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_NUMPAD_NUMPAD_HPP_
#define MODULES_NUMPAD_NUMPAD_HPP_

#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim5;

#define dmaCyclerTimer htim5
#define configedADC hadc1


HAL_StatusTypeDef numpadEnable();
HAL_StatusTypeDef numpadDisable();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);
uint8_t adcValue2Digit();

#endif /* MODULES_NUMPAD_NUMPAD_HPP_ */
