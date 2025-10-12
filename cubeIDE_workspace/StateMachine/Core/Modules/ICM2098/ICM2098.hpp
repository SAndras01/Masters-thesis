/*
 * ICM2098.hpp
 *
 *  Created on: Oct 5, 2025
 *      Author: Andris
 */

#ifndef MODULES_ICM2098_ICM2098_HPP_
#define MODULES_ICM2098_ICM2098_HPP_

#include "accelerometer.hpp"
#include "ICM2098_Registers.hpp"
#include "main.h"

#define ICM2098_ADDR_AD0_LOW				0x68
#define ICM2098_ADDR_AD0_HIGH				0x69

#define ICM2098_ACCEL_SCALE_FACTOR_2G		16384.0f
#define ICM2098_ACCEL_SCALE_FACTOR_4G		8192.0f
#define ICM2098_ACCEL_SCALE_FACTOR_8G		4096.0f
#define ICM2098_ACCEL_SCALE_FACTOR_16G		2048.0f

#define ICM2098_GYRO_SCALE_FACTOR_250DPS	131.0f
#define ICM2098_GYRO_SCALE_FACTOR_500DPS	65.5f
#define ICM2098_GYRO_SCALE_FACTOR_1000DPS	32.8f
#define ICM2098_GYRO_SCALE_FACTOR_2000DPS	16.4f

enum AccRange
{
	FS_plus_minus_2G,
	FS_plus_minus_4G,
	FS_plus_minus_8G,
	FS_plus_minus_16G
};

enum GyroRange
{
	FS_250DPS,
	FS_500DPS,
	FS_1000DPS,
	FS_2000DPS
};

class ICM2098: Accelerometer
{
private:
	AccRange accRange;
	GyroRange gyroRange;
	I2C_HandleTypeDef* hi2c;
	uint8_t address;
public:
	ICM2098(I2C_HandleTypeDef* hi2c, uint8_t address, AccRange accRange = FS_plus_minus_2G, GyroRange gyroRange = FS_250DPS);
	bool init();

	void setAccRange();
	uint8_t getAccRange();

	void setGyroRange();
	uint16_t getGyroRange();

	float getTemp();

	float* getAngles();
	float* getGyro();
	float* getMagneto();
};


#endif /* MODULES_ICM2098_ICM2098_HPP_ */
