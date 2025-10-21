/*
 * ICM2098.hpp
 *
 *  Created on: Oct 5, 2025
 *      Author: Andris
 */

#ifndef MODULES_ICM2098_ICM2098_HPP_
#define MODULES_ICM2098_ICM2098_HPP_

#include "ICM2098_Registers.hpp"
#include "main.h"
#include <math.h>

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

#define ICM2098_SELECT_BANK_0				0x00
#define ICM2098_SELECT_BANK_1				0x10
#define ICM2098_SELECT_BANK_2				0x20
#define ICM2098_SELECT_BANK_3				0x30

#define ICM2098_WHOAMI_EXPECTED				0xEA


#define AK09916_I2C_ADDR					0x0C
#define AK09916_WHOAMI_EXPECTED				0x09

enum AccRange
{
	FS_plus_minus_2G = 0b00,
	FS_plus_minus_4G = 0b01,
	FS_plus_minus_8G = 0b10,
	FS_plus_minus_16G = 0b11
};

enum GyroRange
{
	FS_250DPS  = 0b00,
	FS_500DPS  = 0b01,
	FS_1000DPS = 0b10,
	FS_2000DPS = 0b11
};

class ICM2098
{
private:
	AccRange accRange;
	GyroRange gyroRange;
	I2C_HandleTypeDef* hi2c;
	uint8_t address;

	float accScale;
	float gyroScale;

	bool magnetoEnabled;

	HAL_StatusTypeDef writeReg(uint8_t reg, uint8_t data);
	HAL_StatusTypeDef readRegs(uint8_t reg, uint8_t* buf, uint8_t len);
	void setBank(uint8_t bank);

	bool initMagnetometer();

public:
	ICM2098(I2C_HandleTypeDef* hi2c, uint8_t address,
			AccRange accRange = FS_plus_minus_2G,
			GyroRange gyroRange = FS_250DPS);

	bool init(bool enableMagneto = false);

	void setAccRange(AccRange range);
	void setGyroRange(GyroRange range);

	void readAccel(float* ax, float* ay, float* az);
	void readGyro(float* gx, float* gy, float* gz);
	float readTemperature();

	bool getMagneto(float* mx, float* my, float* mz);
};

#endif /* MODULES_ICM2098_ICM2098_HPP_ */
