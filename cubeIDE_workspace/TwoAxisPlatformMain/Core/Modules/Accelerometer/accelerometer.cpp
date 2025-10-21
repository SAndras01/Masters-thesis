/*
 * accelerometer.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "accelerometer.hpp"

float* Accelerometer::getRefAccels()
{
	static float dummyDegs[3] = {120.1, 35.4, 1.8};
	return dummyDegs;
}
