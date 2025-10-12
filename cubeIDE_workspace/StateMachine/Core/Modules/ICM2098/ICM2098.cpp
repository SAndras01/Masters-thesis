/*
 * ICM2098.cpp
 *
 *  Created on: Oct 5, 2025
 *      Author: Andris
 */

#include "ICM2098.hpp"

ICM2098::ICM2098(	I2C_HandleTypeDef *hi2c, uint8_t address,
					AccRange accRange, GyroRange gyroRange)
{
	this->hi2c = hi2c;
	this->address = address;
	this->accRange = accRange;
	this->gyroRange = gyroRange;
}
