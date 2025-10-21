/*
 * StepperController.hpp
 *
 *  Created on: Aug 21, 2025
 *      Author: SNA1BP
 */
#include <stdint.h>
#include "GPIO.hpp"
#include <cstring>
#include "stm32f7xx_hal_tim.h"

#ifndef MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_
#define MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_

//defines
#define MAX_SIZE 200*64 + 1		// Max size of ARR table

#define FREQ_TMR 96000000UL   // timer freq [Hz]
#define FULL_STEP_DEG 1.8     // deg / steo
#define MICRO_STEPS 0.125f    // 1/8
#define PI 3.14159265358979323846

#define LUT_SIZE 100			//Size of LUT for neg arcsin

// Scalers
#define T_SCALER FREQ_TMR      // time scaler (y axis)
#define THETA_SCALER 1000000UL // angle scaler (x axis)

struct LUTTable
{
	int32_t x_values[LUT_SIZE];
	int32_t y_values[LUT_SIZE];
};

// TODO error handling and documentation
class StepperController
{
private:
	//Peripherals
	DMA_HandleTypeDef* timerUpdaterDMA;
	GPIO* DIR_pin = NULL;

	//Arrays
	uint32_t timer_values[MAX_SIZE];
	static LUTTable minusArcSinLUT;

	//Physical characteristics
	double fullstep_deg;
	double u_step;
	uint32_t n_steps;

	//Private functions
	int32_t interpolate_from_LUT(int32_t x, LUTTable LUT);

public:
	TIM_HandleTypeDef* stepTimer;

	bool steppingFinished;

	StepperController(	TIM_HandleTypeDef* stepTimer,
						DMA_HandleTypeDef* timerUpdaterDMA,
						GPIO* DIR_pin,
						double fullstep_deg,
						double u_step);

	bool calculate_movement(uint32_t  delta_Theta, float delta_t);
	bool start_stepping(int8_t direction);

	void set_ustep(float u_step);
	float get_ustep();

	GPIO* get_DIR_pin();
};




#endif /* MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_ */
