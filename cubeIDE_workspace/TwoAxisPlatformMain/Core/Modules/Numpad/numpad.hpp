/**
 * @file mumpad.hpp
 * @brief Numpad interface using ADC and timer input for STM32.
 *
 * Provides functions to enable/disable the numpad and read the pressed
 * digit using ADC values. Timer interrupt triggers ADC conversions.
 *
 * @author Sásdi András
 * @date 2025-09-17
 */

#ifndef MODULES_NUMPAD_NUMPAD_HPP_
#define MODULES_NUMPAD_NUMPAD_HPP_

#include "main.h"

/** @brief External ADC handle used for numpad readings */
extern ADC_HandleTypeDef hadc1;

/** @brief External timer handle used to trigger ADC conversions */
extern TIM_HandleTypeDef htim6;

/** @brief Alias for the ADC trigger timer */
#define ADCtimer htim6

/** @brief Alias for the ADC configured for the numpad */
#define configedADC hadc1

/**
 * @brief Enable the numpad input.
 *
 * Starts the timer and ADC so that periodic readings are available.
 *
 * @return HAL status of timer/ADC start operation.
 */
HAL_StatusTypeDef numpadEnable();

/**
 * @brief Disable the numpad input.
 *
 * Stops the ADC conversion to disable numpad readings.
 *
 * @return HAL status of ADC stop operation.
 */
HAL_StatusTypeDef numpadDisable();

/**
 * @brief Timer period elapsed callback.
 *
 * Triggered on timer interrupt. Starts an ADC conversion if the interrupt
 * corresponds to the configured numpad timer.
 *
 * @param htim Pointer to the timer handle that triggered the interrupt.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);

/**
 * @brief Convert the last ADC value to a numpad digit.
 *
 * Maps the ADC reading into digits 1–3. Returns 10 if the reading
 * does not correspond to a valid digit.
 *
 * @return uint8_t Numpad digit (1–3) or 10 if invalid.
 */
uint8_t adcValue2Digit();

#endif /* MODULES_NUMPAD_NUMPAD_HPP_ */
