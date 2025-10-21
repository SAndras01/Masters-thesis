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
		0,    -969713,   -1939525,   -2909536,   -3879843,
 -4850548,   -5821749,   -6793547,   -7766043,   -8739338,
 -9713535,  -10688737,  -11665048,  -12642572,  -13621417,
-14601690,  -15583500,  -16566956,  -17552173,  -18539262,
-19528340,  -20519525,  -21512936,  -22508696,  -23506930,
-24507763,  -25511328,  -26517756,  -27527184,  -28539752,
-29555603,  -30574883,  -31597745,  -32624343,  -33654837,
-34689392,  -35728179,  -36771372,  -37819153,  -38871710,
-39929236,  -40991934,  -42060012,  -43133686,  -44213183,
-45298736,  -46390590,  -47489000,  -48594232,  -49706563,
-50826286,  -51953703,  -53089137,  -54232921,  -55385409,
-56546973,  -57718005,  -58898919,  -60090153,  -61292170,
-62505464,  -63730556,  -64968003,  -66218400,  -67482379,
-68760621,  -70053854,  -71362862,  -72688489,  -74031647,
-75393326,  -76774598,  -78176634,  -79600713,  -81048237,
-82520751,  -84019961,  -85547760,  -87106261,  -88697830,
-90325133,  -91991192,  -93699458,  -95453897,  -97259106,
-99120468, -101044346, -103038357, -105111751, -107275939,
-109545279, -111938264, -114479405, -117202390, -120155750,
-123414025, -127102789, -131467086, -137140089, -150796447
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

	//Start the timer with the first timer vale so the actual Init value doesn't interfere
	memcpy((void*)&(stepTimer->Instance->ARR), &timer_values[0], sizeof(uint32_t));

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
