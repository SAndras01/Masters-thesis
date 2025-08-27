/*
 * StepperController.cpp
 *
 *  Created on: Aug 21, 2025
 *      Author: SNA1BP
 */

#include "StepperController.hpp"

LUTTable StepperController::minusArcSinLUT = {
{
    0,   10101,   20202,   30303,   40404,   50505,   60606,
70707,   80808,   90909,  101010,  111111,  121212,  131313,
141414,  151515,  161616,  171717,  181818,  191919,  202020,
212121,  222222,  232323,  242424,  252525,  262626,  272727,
282828,  292929,  303030,  313131,  323232,  333333,  343434,
353535,  363636,  373737,  383838,  393939,  404040,  414141,
424242,  434343,  444444,  454545,  464646,  474747,  484848,
494949,  505050,  515151,  525252,  535353,  545454,  555555,
565656,  575757,  585858,  595959,  606060,  616161,  626262,
636363,  646464,  656565,  666666,  676767,  686868,  696969,
707070,  717171,  727272,  737373,  747474,  757575,  767676,
777777,  787878,  797979,  808080,  818181,  828282,  838383,
848484,  858585,  868686,  878787,  888888,  898989,  909090,
919191,  929292,  939393,  949494,  959595,  969696,  979797,
989898, 1000000
},
{
        0,    -848499,   -1697085,   -2545844,   -3394863,
 -4244229,   -5094030,   -5944354,   -6795287,   -7646921,
 -8499343,   -9352645,  -10206917,  -11062251,  -11918740,
-12776479,  -13635562,  -14496087,  -15358151,  -16221854,
-17087298,  -17954584,  -18823819,  -19695109,  -20568563,
-21444293,  -22322412,  -23203036,  -24086286,  -24972283,
-25861152,  -26753023,  -27648027,  -28546300,  -29447982,
-30353218,  -31262156,  -32174950,  -33091759,  -34012746,
-34938082,  -35867942,  -36802510,  -37741975,  -38686535,
-39636394,  -40591766,  -41552875,  -42519953,  -43493243,
-44473000,  -45459490,  -46452994,  -47453805,  -48462232,
-49478601,  -50503254,  -51536554,  -52578883,  -53630649,
-54692281,  -55764236,  -56847003,  -57941100,  -59047082,
-60165544,  -61297123,  -62442504,  -63602428,  -64777691,
-65969160,  -67177773,  -68404555,  -69650624,  -70917207,
-72205657,  -73517466,  -74854290,  -76217978,  -77610601,
-79034491,  -80492293,  -81987026,  -83522160,  -85101718,
-86730410,  -88413802,  -90158563,  -91972782,  -93866446,
-95852119,  -97945981, -100169480, -102552091, -105136281,
-107987272, -111214941, -115033700, -119997578, -131946891
}};

void XferCplt_Callback(DMA_HandleTypeDef *_hdma)
{
	//The Parent is type StepperController*, and its "stepTimer" is a TIM_HandleTypeDef*
	HAL_TIM_PWM_Stop((TIM_HandleTypeDef*)((StepperController*)_hdma->Parent) -> stepTimer, TIM_CHANNEL_1);

	((StepperController*)_hdma->Parent)->steppingFinished = true;
}

StepperController::StepperController(	TIM_HandleTypeDef* stepTimer,
						DMA_HandleTypeDef* timerUpdaterDMA,
						GPIO* DIR_pin,
						double fullstep_deg,
						double u_step)
{
	this -> stepTimer = stepTimer;
	this -> timerUpdaterDMA = timerUpdaterDMA;
	this -> DIR_pin = DIR_pin;
	this -> timerUpdaterDMA->Parent = this;


	this -> fullstep_deg = fullstep_deg;
	this -> u_step = u_step;

	HAL_DMA_RegisterCallback(timerUpdaterDMA, HAL_DMA_XFER_CPLT_CB_ID, XferCplt_Callback);
}

int32_t StepperController::interpolate_from_LUT(int32_t x, LUTTable LUT)
{
	int sign = 1;
	if (x < 0) {
		sign = -1;
		x = -x;
	}

	if (x <= (int32_t)LUT.x_values[0]) return sign * (int32_t)LUT.y_values[0];
	if (x >= (int32_t)LUT.x_values[LUT_SIZE - 1]) return sign * (int32_t)LUT.y_values[LUT_SIZE - 1];

	int16_t idx = 0;
	// bináris keresés helyett egyszerű lineáris (mert LUT kicsi)
	while (idx < LUT_SIZE - 1 && x > (int32_t)LUT.x_values[idx+1]) idx++;

	//idx = binarySearch(LUT.x_values, LUT_SIZE, x);


	int32_t x0 = LUT.x_values[idx];
	int32_t x1 = LUT.x_values[idx+1];
	int32_t y0 = LUT.y_values[idx];
	int32_t y1 = LUT.y_values[idx+1];

	// lineáris interpoláció
	int32_t dy = y1 - y0;
	int32_t dx = x1 - x0;
	int32_t dt = x - x0;

	// (dy * dt) / dx
	int32_t y = y0 + (int32_t)((int64_t)dy * dt / dx);

	return sign * y;
}

bool StepperController::calculate_movement(uint32_t delta_Theta, float delta_t)
{
	double alpha_rad = ( fullstep_deg * PI / 180.0 ) * u_step;

	int32_t alpha_rad_scaled = (int32_t)(alpha_rad * THETA_SCALER);

	double Theta_rad = delta_Theta * PI / 180.0;

	int32_t Theta_rad_scaled = (int32_t)(Theta_rad * THETA_SCALER);

	int32_t T_scaled = (int32_t)(delta_t * T_SCALER);

	n_steps = (int)(delta_Theta / (fullstep_deg * u_step));

	// Calculate t_k and ARR
	int32_t t_k_scaled[n_steps+1];
	uint32_t k = 0;

	int32_t pi_scaled = (int32_t)(PI * T_SCALER);
	int32_t pi_scaled_half = pi_scaled/2;

	for (k = 0; k <= n_steps; k++)
	{
		int32_t neg_arcsin_arg_scaled = THETA_SCALER - 2 * THETA_SCALER * ((int64_t)k * alpha_rad_scaled) / (Theta_rad_scaled);

		int32_t neg_arcsin_scaled = interpolate_from_LUT(neg_arcsin_arg_scaled, minusArcSinLUT);

		t_k_scaled[k] = (int32_t)(( (int64_t)(neg_arcsin_scaled + pi_scaled_half) * T_scaled) / pi_scaled);
	}

	for (k = 0; k < n_steps; k++)
	{
	  int32_t dt_scaled = t_k_scaled[k+1] - t_k_scaled[k];
	  int32_t ARR = dt_scaled - 1; //as the time scaler and the frequency is equal we don't need to do any further scaling
	  timer_values[k] = ARR;
	}
	//TODO: return0 if ARR<PWM
	return 1;
}


bool StepperController::start_stepping(int8_t direction)
{
	if(direction < 0 )
	{
		DIR_pin->digitalWrite(GPIO_PIN_SET);
	}
	else
	{
		DIR_pin->digitalWrite(GPIO_PIN_RESET);
	}

    uint32_t DstAddress = (uint32_t) & (stepTimer->Instance->ARR);

	HAL_StatusTypeDef State1;
	HAL_StatusTypeDef State2;
	HAL_StatusTypeDef State3;

	steppingFinished = false;

	State1 = HAL_TIM_Base_Start_IT(stepTimer);

	State2 = HAL_TIM_PWM_Start(stepTimer, TIM_CHANNEL_1);

	State3 = HAL_DMA_Start_IT(timerUpdaterDMA, (uint32_t)timer_values, DstAddress, n_steps);

	__HAL_TIM_ENABLE_DMA(stepTimer, TIM_DMA_UPDATE);

	if(State1 == HAL_OK && State2 == HAL_OK && State3 == HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void StepperController::set_ustep(float u_step){this->u_step = u_step;}

float StepperController::get_ustep(){return u_step;}

GPIO* StepperController::get_DIR_pin(){return DIR_pin;}
