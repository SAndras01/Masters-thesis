/**
 * @file ICM20948.hpp
 * @brief High-level C++ driver for the ICM-20948 9-axis motion sensor.
 *
 * Provides I2C access to accelerometer, gyroscope and optional AK09916 magnetometer.
 * This driver is designed for STM32 HAL I2C blocking API (HAL_I2C_Mem_Read/Write).
 *
 * @details
 * Features:
 *  - Bank switching helper
 *  - Accelerometer & gyroscope range configuration
 *  - Read functions returning SI-like units (g, deg/s)
 *  - Temperature readout (Celsius)
 *  - Optional magnetometer initialization and readout (AK09916)
 *
 * Example:
 * \code
 * ICM20948 icm(&hi2c1, ICM20948_ADDR_AD0_LOW);
 * if(icm.init(true)) {
 *     float ax,ay,az;
 *     icm.readAccel(&ax,&ay,&az);
 * }
 * \endcode
 *
 * @author Andris
 * @date October 2025
 */

#ifndef MODULES_ICM20948_ICM20948_HPP_
#define MODULES_ICM20948_ICM20948_HPP_

#include "main.h"
#include <math.h>
#include "accelerometer.hpp"
#include "ICM20948_Registers.hpp"


/// I2C addresses (depending on AD0 pin)
#define ICM20948_ADDR_AD0_LOW				0x68
#define ICM20948_ADDR_AD0_HIGH				0x69

/// Accelerometer scale factors (LSB per g)
#define ICM20948_ACCEL_SCALE_FACTOR_2G		16384.0f
#define ICM20948_ACCEL_SCALE_FACTOR_4G		8192.0f
#define ICM20948_ACCEL_SCALE_FACTOR_8G		4096.0f
#define ICM20948_ACCEL_SCALE_FACTOR_16G		2048.0f

/// Gyroscope scale factors (LSB per dps)
#define ICM20948_GYRO_SCALE_FACTOR_250DPS	131.0f
#define ICM20948_GYRO_SCALE_FACTOR_500DPS	65.5f
#define ICM20948_GYRO_SCALE_FACTOR_1000DPS	32.8f
#define ICM20948_GYRO_SCALE_FACTOR_2000DPS	16.4f

/// Bank select constants (write to REG_BANK_SEL)
#define ICM20948_SELECT_BANK_0				0x00
#define ICM20948_SELECT_BANK_1				0x10
#define ICM20948_SELECT_BANK_2				0x20
#define ICM20948_SELECT_BANK_3				0x30

/** @brief Expected WHO_AM_I value for ICM-20948. */
#define ICM20948_WHOAMI_EXPECTED				0xEA

/** @brief AK09916 I2C address (redundant with registers header for convenience). */
#define AK09916_I2C_ADDR					0x0C
/** @brief AK09916 WHOAMI expected value. */
#define AK09916_WHOAMI_EXPECTED				0x09


/**
 * @enum AccRange
 * @brief Full-scale selection for accelerometer.
 */
enum AccRange
{
	FS_plus_minus_2G = 0b00,  /*!< ±2g */
	FS_plus_minus_4G = 0b01,  /*!< ±4g */
	FS_plus_minus_8G = 0b10,  /*!< ±8g */
	FS_plus_minus_16G = 0b11  /*!< ±16g */
};

/**
 * @enum GyroRange
 * @brief Full-scale selection for gyroscope.
 */
enum GyroRange
{
	FS_250DPS  = 0b00, /*!< 250 °/s */
	FS_500DPS  = 0b01, /*!< 500 °/s */
	FS_1000DPS = 0b10, /*!< 1000 °/s */
	FS_2000DPS = 0b11  /*!< 2000 °/s */
};


/**
 * @class ICM20948
 * @brief C++ wrapper for ICM-20948 sensor.
 *
 * The class uses STM32 HAL I2C blocking APIs for register access.
 * It implements basic init, range configuration and read functions.
 *
 * @note The magnetometer code is partially TODO — see @todo tags in the implementation.
 */
class ICM20948: public Accelerometer
{
private:
	AccRange accRange;                 ///< Current accelerometer range selection.
	GyroRange gyroRange;               ///< Current gyroscope range selection.
	I2C_HandleTypeDef* hi2c;           ///< HAL I2C handle used for communication.
	uint8_t address;                   ///< I2C address (7-bit).
	float accScale;                    ///< Current accel scale factor (LSB/g).
	float gyroScale;                   ///< Current gyro scale factor (LSB/°/s).
	bool magnetoEnabled;               ///< True when magnetometer was successfully initialized.

	/**
	 * @brief Write single byte to a device register.
	 * @param reg Register address.
	 * @param data Byte to write.
	 * @return HAL status.
	 */
	HAL_StatusTypeDef writeReg(uint8_t reg, uint8_t data);

	/**
	 * @brief Read consecutive registers into buffer.
	 * @param reg Start register.
	 * @param buf Destination buffer pointer.
	 * @param len Number of bytes to read.
	 * @return HAL status.
	 */
	HAL_StatusTypeDef readRegs(uint8_t reg, uint8_t* buf, uint8_t len);

	/**
	 * @brief Select register bank (0..3).
	 * @param bank One of ICM20948_SELECT_BANK_*
	 */
	void setBank(uint8_t bank);

	/**
	 * @brief Initialize embedded AK09916 magnetometer via the I2C master interface.
	 * @return True if magnetometer initialization succeeded.
	 * @note Implementation currently TODO in source file.
	 */
	bool initMagnetometer();

public:
	/**
	 * @brief Constructor.
	 * @param hi2c_p HAL I2C handle.
	 * @param address_p 7-bit I2C address (ICM20948_ADDR_AD0_LOW or _HIGH).
	 * @param accRange Default accelerometer range.
	 * @param gyroRange Default gyro range.
	 */
	ICM20948(I2C_HandleTypeDef* hi2c, uint8_t address,
			AccRange accRange = FS_plus_minus_2G,
			GyroRange gyroRange = FS_250DPS);

	/**
	 * @brief Initialize sensor core (WHO_AM_I check, wake-up, configure ranges).
	 * @param enableMagneto If true, attempt to initialize AK09916 magnetometer.
	 * @return True on success.
	 */
	bool init(bool enableMagneto = false);

	/** @brief Set accelerometer full-scale range. */
	void setAccRange(AccRange range);

	/** @brief Set gyroscope full-scale range. */
	void setGyroRange(GyroRange range);

	/**
	 * @brief Read accelerometer raw data and convert to g.
	 * @param ax Pointer to store X (g).
	 * @param ay Pointer to store Y (g).
	 * @param az Pointer to store Z (g).
	 */
	void readAccel(float* ax, float* ay, float* az);

	/**
	 * @brief Read gyroscope raw data and convert to °/s.
	 * @param gx Pointer to store X (°/s).
	 * @param gy Pointer to store Y (°/s).
	 * @param gz Pointer to store Z (°/s).
	 */
	void readGyro(float* gx, float* gy, float* gz);

	/**
	 * @brief Read internal temperature and convert to Celsius.
	 * @return Temperature in °C.
	 */
	float readTemperature();

	/**
	 * @brief Read magnetometer values (AK09916) if enabled.
	 * @param mx Pointer to store X (uT or raw, depending on scaling implementation).
	 * @param my Pointer to store Y.
	 * @param mz Pointer to store Z.
	 * @return True if data was read successfully, false otherwise.
	 * @warning not yet implemented
	 * @todo Implement magnetometer readout and scaling.
	 */
	bool getMagneto(float* mx, float* my, float* mz);

	/**
	 * @brief Convenience: returns pointer to a static array with last accel sample.
	 * @note The returned pointer points to an internal static array and is overwritten on each call.
	 */
	float* getRefAccels();
};

#endif /* MODULES_ICM20948_ICM20948_HPP_ */
