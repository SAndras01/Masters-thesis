/*
 * ICM2098.cpp
 *
 *  Created on: Oct 5, 2025
 *      Author: Andris
 */

#include "ICM2098.hpp"

ICM2098::ICM2098(I2C_HandleTypeDef *hi2c, uint8_t address,
				 AccRange accRange, GyroRange gyroRange)
{
	this->hi2c = hi2c;
	this->address = address;
	this->accRange = accRange;
	this->gyroRange = gyroRange;
	this->magnetoEnabled = false;
}

// ---------------------------------------------------------
// I2C comm
// ---------------------------------------------------------
HAL_StatusTypeDef ICM2098::writeReg(uint8_t reg, uint8_t data)
{
	return HAL_I2C_Mem_Write(hi2c, address << 1, reg, 1, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef ICM2098::readRegs(uint8_t reg, uint8_t* buf, uint8_t len)
{
	return HAL_I2C_Mem_Read(hi2c, address << 1, reg, 1, buf, len, HAL_MAX_DELAY);
}

void ICM2098::setBank(uint8_t bank)
{
	HAL_I2C_Mem_Write(hi2c, address << 1, ICM20948_REG_BANK_SEL, 1, &bank, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
}

// ---------------------------------------------------------
// Inicializálás
// ---------------------------------------------------------
bool ICM2098::init(bool enableMagneto)
{
	uint8_t data = 0;
	uint8_t whoami = 0;

	// WHO_AM_I CHECK
	setBank(ICM2098_SELECT_BANK_0);
	readRegs(ICM20948_REG_WHO_AM_I, &whoami, 1);
	if (whoami != ICM2098_WHOAMI_EXPECTED)
	{
		return false;
	}

	// wake up
	data = 0x01; // clock source: auto select
	writeReg(ICM20948_REG_PWR_MGMT_1, data);

	data = 0x00; // enable all sensors
	writeReg(ICM20948_REG_PWR_MGMT_2, data);
	HAL_Delay(10);

	//accel config
	setBank(ICM2098_SELECT_BANK_2);
	setAccRange(accRange);

	//gyro config
	setGyroRange(gyroRange);

	//Bank0
	setBank(ICM2098_SELECT_BANK_0);
	HAL_Delay(10);

	// Optional magneto init
	if (enableMagneto)
	{
		magnetoEnabled = initMagnetometer();
	}

	return true;
}

//TODO implement this
bool ICM2098::initMagnetometer()
{

}

// Accelerometer range setup
void ICM2098::setAccRange(AccRange range)
{
	setBank(ICM2098_SELECT_BANK_2);
	uint8_t reg = 0x00;
	readRegs(ICM20948_REG_ACCEL_CONFIG, &reg, 1);
	reg &= ~0b00000110;
	reg |= (range << 1);
	writeReg(ICM20948_REG_ACCEL_CONFIG, reg);

	switch (range)
	{
	case FS_plus_minus_2G:  accScale = ICM2098_ACCEL_SCALE_FACTOR_2G;  break;
	case FS_plus_minus_4G:  accScale = ICM2098_ACCEL_SCALE_FACTOR_4G;  break;
	case FS_plus_minus_8G:  accScale = ICM2098_ACCEL_SCALE_FACTOR_8G;  break;
	case FS_plus_minus_16G: accScale = ICM2098_ACCEL_SCALE_FACTOR_16G; break;
	}
	setBank(ICM2098_SELECT_BANK_0);
}

// ---------------------------------------------------------
// Gyroscope range setup
// ---------------------------------------------------------
void ICM2098::setGyroRange(GyroRange range)
{
	setBank(ICM2098_SELECT_BANK_2);
	uint8_t reg = 0x00;
	readRegs(ICM20948_REG_GYRO_CONFIG_1, &reg, 1);
	reg &= ~0b00000110;
	reg |= (range << 1);
	writeReg(ICM20948_REG_GYRO_CONFIG_1, reg);

	switch (range)
	{
	case FS_250DPS:  gyroScale = ICM2098_GYRO_SCALE_FACTOR_250DPS;  break;
	case FS_500DPS:  gyroScale = ICM2098_GYRO_SCALE_FACTOR_500DPS;  break;
	case FS_1000DPS: gyroScale = ICM2098_GYRO_SCALE_FACTOR_1000DPS; break;
	case FS_2000DPS: gyroScale = ICM2098_GYRO_SCALE_FACTOR_2000DPS; break;
	}
	setBank(ICM2098_SELECT_BANK_0);
}

// ---------------------------------------------------------
// Accelerometer read
// ---------------------------------------------------------
void ICM2098::readAccel(float* ax, float* ay, float* az)
{
	uint8_t buf[6];
	int16_t raw[3];

	readRegs(ICM20948_REG_ACCEL_XOUT_H, buf, 6);

	for (int i = 0; i < 3; i++)
		raw[i] = (int16_t)(((uint16_t)buf[2*i] << 8) | buf[2*i+1]);

	*ax = (float)raw[0] / accScale;
	*ay = (float)raw[1] / accScale;
	*az = (float)raw[2] / accScale;
}

// ---------------------------------------------------------
// Gyroscope read
// ---------------------------------------------------------
void ICM2098::readGyro(float* gx, float* gy, float* gz)
{
	uint8_t buf[6];
	int16_t raw[3];

	readRegs(ICM20948_REG_GYRO_XOUT_H, buf, 6);

	for (int i = 0; i < 3; i++)
		raw[i] = (int16_t)(((uint16_t)buf[2*i] << 8) | buf[2*i+1]);

	*gx = (float)raw[0] / gyroScale;
	*gy = (float)raw[1] / gyroScale;
	*gz = (float)raw[2] / gyroScale;
}

// ---------------------------------------------------------
// Temperature read
// ---------------------------------------------------------
float ICM2098::readTemperature()
{
	uint8_t buf[2];
	int16_t raw;
	readRegs(ICM20948_REG_TEMP_OUT_H, buf, 2);
	raw = (int16_t)((buf[0] << 8) | buf[1]);
	return ((float)raw - 21.0f) / 333.87f + 21.0f; // datasheet formula
}

float* ICM2098::getRefAccels()
{
	static float accels[3];
	readAccel(&accels[0], &accels[1], &accels[2]);
	return accels;
}

//TODO implement
bool ICM2098::getMagneto(float* mx, float* my, float* mz)
{

}
