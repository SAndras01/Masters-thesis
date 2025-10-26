/*
 * accelerometer.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_ACCELEROMETER_ACCELEROMETER_HPP_
#define MODULES_ACCELEROMETER_ACCELEROMETER_HPP_

#include <stdint.h>

class Accelerometer {
public:
	virtual float* getRefAccels();
};

#endif /* MODULES_ACCELEROMETER_ACCELEROMETER_HPP_ */
