/**
 * @file ICM20948.cpp
 * @brief Implementation of ICM20948 class functions.
 *
 * The implementation uses HAL I2C Mem read/write calls and assumes the
 * device uses the register bank switching mechanism (REG_BANK_SEL).
 *
 * @todo Magnetometer initialization & readout (AK09916) is not fully implemented.
 *
 * @author Sásdi András
 */

#include "ICM20948.hpp"

/**
 * @brief Constructor.
 */
ICM20948::ICM20948(I2C_HandleTypeDef *hi2c, uint8_t address,
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

/**
 * @brief Write one byte to device register (blocking).
 * @param reg Register address.
 * @param data Byte to write.
 * @return HAL status returned by HAL_I2C_Mem_Write.
 */
HAL_StatusTypeDef ICM20948::writeReg(uint8_t reg, uint8_t data)
{
	return HAL_I2C_Mem_Write(hi2c, address << 1, reg, 1, &data, 1, HAL_MAX_DELAY);
}

/**
 * @brief Read consecutive registers into a buffer (blocking).
 * @param reg Start register.
 * @param buf Destination buffer.
 * @param len Number of bytes to read.
 * @return HAL status returned by HAL_I2C_Mem_Read.
 */
HAL_StatusTypeDef ICM20948::readRegs(uint8_t reg, uint8_t* buf, uint8_t len)
{
	return HAL_I2C_Mem_Read(hi2c, address << 1, reg, 1, buf, len, HAL_MAX_DELAY);
}

/**
 * @brief Select register bank (0..3).
 * @param bank Bank selector constant (ICM20948_SELECT_BANK_*).
 * @note The function writes REG_BANK_SEL on bank 0 to switch banks,
 *       and waits 1 ms for the bank change to take effect.
 */
void ICM20948::setBank(uint8_t bank)
{
	HAL_I2C_Mem_Write(hi2c, address << 1, ICM20948_REG_BANK_SEL, 1, &bank, 1, HAL_MAX_DELAY);
	HAL_Delay(1);
}

// ---------------------------------------------------------
// Inicializálás
// ---------------------------------------------------------

/**
 * @brief Initialize ICM20948 core and optionally magnetometer.
 *
 * - Verifies WHO_AM_I
 * - Wakes device and enables sensors
 * - Configures accelerometer and gyro ranges
 * - Optionally initializes AK09916 magnetometer via I2C master
 *
 * @param enableMagneto If true, attempt magnetometer init.
 * @return true if initialization succeeded, false otherwise.
 */
bool ICM20948::init(bool enableMagneto)
{
	uint8_t data = 0;
	uint8_t whoami = 0;

	// WHO_AM_I CHECK
	setBank(ICM20948_SELECT_BANK_0);
	readRegs(ICM20948_REG_WHO_AM_I, &whoami, 1);
	if (whoami != ICM20948_WHOAMI_EXPECTED)
	{
		return false;
	}

	// wake up: set clock source auto-select
	data = 0x01;
	writeReg(ICM20948_REG_PWR_MGMT_1, data);

	// enable all sensors
	data = 0x00;
	writeReg(ICM20948_REG_PWR_MGMT_2, data);
	HAL_Delay(10);

	// accel config
	setBank(ICM20948_SELECT_BANK_2);
	setAccRange(accRange);

	// gyro config
	setGyroRange(gyroRange);

	// back to bank 0
	setBank(ICM20948_SELECT_BANK_0);
	HAL_Delay(10);

	// Optional magneto init
	if (enableMagneto)
	{
		magnetoEnabled = initMagnetometer();
	}

	return true;
}

/**
 * @brief Initialize AK09916 magnetometer via I2C master.
 * @note Implementation TODO — currently returns false.
 * @return True on success, false otherwise.
 */
bool ICM20948::initMagnetometer()
{
	// @todo implement magnetometer initialization sequence:
	//       - switch to bank 3, configure I2C master,
	//       - write to AK09916_CNTL2 to set measurement mode,
	//       - verify WHOAMI (AK09916_REG_WIA2),
	//       - set up continuous read via I2C_SLVx registers.
	return false;
}

// ---------------------------------------------------------
// Accelerometer range setup
// ---------------------------------------------------------

/**
 * @brief Set accelerometer full-scale range and update scale factor.
 * @param range Desired AccRange enum value.
 */
void ICM20948::setAccRange(AccRange range)
{
	setBank(ICM20948_SELECT_BANK_2);
	uint8_t reg = 0x00;
	readRegs(ICM20948_REG_ACCEL_CONFIG, &reg, 1);
	reg &= ~0b00000110;
	reg |= (range << 1);
	writeReg(ICM20948_REG_ACCEL_CONFIG, reg);

	switch (range)
	{
	case FS_plus_minus_2G:  accScale = ICM20948_ACCEL_SCALE_FACTOR_2G;  break;
	case FS_plus_minus_4G:  accScale = ICM20948_ACCEL_SCALE_FACTOR_4G;  break;
	case FS_plus_minus_8G:  accScale = ICM20948_ACCEL_SCALE_FACTOR_8G;  break;
	case FS_plus_minus_16G: accScale = ICM20948_ACCEL_SCALE_FACTOR_16G; break;
	}
	setBank(ICM20948_SELECT_BANK_0);
}

// ---------------------------------------------------------
// Gyroscope range setup
// ---------------------------------------------------------

/**
 * @brief Set gyroscope full-scale range and update scale factor.
 * @param range Desired GyroRange enum value.
 */
void ICM20948::setGyroRange(GyroRange range)
{
	setBank(ICM20948_SELECT_BANK_2);
	uint8_t reg = 0x00;
	readRegs(ICM20948_REG_GYRO_CONFIG_1, &reg, 1);
	reg &= ~0b00000110;
	reg |= (range << 1);
	writeReg(ICM20948_REG_GYRO_CONFIG_1, reg);

	switch (range)
	{
	case FS_250DPS:  gyroScale = ICM20948_GYRO_SCALE_FACTOR_250DPS;  break;
	case FS_500DPS:  gyroScale = ICM20948_GYRO_SCALE_FACTOR_500DPS;  break;
	case FS_1000DPS: gyroScale = ICM20948_GYRO_SCALE_FACTOR_1000DPS; break;
	case FS_2000DPS: gyroScale = ICM20948_GYRO_SCALE_FACTOR_2000DPS; break;
	}
	setBank(ICM20948_SELECT_BANK_0);
}

// ---------------------------------------------------------
// Accelerometer read
// ---------------------------------------------------------

/**
 * @brief Read and convert accelerometer samples.
 * @param ax Pointer to X (g).
 * @param ay Pointer to Y (g).
 * @param az Pointer to Z (g).
 */
void ICM20948::readAccel(float* ax, float* ay, float* az)
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

/**
 * @brief Read and convert gyroscope samples.
 * @param gx Pointer to X (°/s).
 * @param gy Pointer to Y (°/s).
 * @param gz Pointer to Z (°/s).
 */
void ICM20948::readGyro(float* gx, float* gy, float* gz)
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

/**
 * @brief Read temperature registers and convert to Celsius.
 * @return Temperature in degrees Celsius.
 * @note Conversion formula follows datasheet: Temp [°C] = ((TEMP_RAW - 21) / 333.87) + 21
 */
float ICM20948::readTemperature()
{
	uint8_t buf[2];
	int16_t raw;
	readRegs(ICM20948_REG_TEMP_OUT_H, buf, 2);
	raw = (int16_t)((buf[0] << 8) | buf[1]);
	return ((float)raw - 21.0f) / 333.87f + 21.0f; // datasheet formula
}

/**
 * @brief Return pointer to a static array containing last accel sample.
 * @note The returned pointer references internal static memory overwritten on each call.
 */
float* ICM20948::getRefAccels()
{
	static float accels[3];
	readAccel(&accels[0], &accels[1], &accels[2]);
	return accels;
}

/**
 * @brief Placeholder for magnetometer readout.
 * @todo Implement AK09916 readout using the I²C master interface (bank 3).
 */
bool ICM20948::getMagneto(float* mx, float* my, float* mz)
{
	// @todo implement magnetometer readback through I2C master registers (bank 3)
	return false;
}
