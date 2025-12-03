/**
 * @file ICM20948_Registers.hpp
 * @brief Complete register map for ICM-20948 gyroscope, accelerometer and magnetometer.
 *
 * This header contains register addresses used across the ICM20948 driver.
 * It includes Bank 0..3 registers (accelerometer/gyro/core + I2C master for magnetometer)
 * and AK09916 magnetometer register definitions and mode constants.
 *
 * @details
 * The register addresses and modes are taken from the official InvenSense / TDK datasheet.
 * Use these defines when accessing device registers via I2C/SPI and when switching register banks.
 *
 * @see https://invensense.tdk.com/wp-content/uploads/2016/06/DS-000189-ICM-20948-v1.3.pdf
 *
 * @author Andris
 * @date October 2025
 */

#ifndef MODULES_ICM20948_ICM20948_REGISTERS_HPP_
#define MODULES_ICM20948_ICM20948_REGISTERS_HPP_

// ==========================
// Common Registers (Bank 0)
// ==========================

/**
 * @brief WHO_AM_I register (Bank0).
 * @note Expected value: 0xEA for ICM-20948.
 */
#define ICM20948_REG_WHO_AM_I             0x00

/** @brief USER_CTRL register (Bank0). */
#define ICM20948_REG_USER_CTRL            0x03

/** @brief Low-power configuration (Bank0). */
#define ICM20948_REG_LP_CONFIG            0x05

/** @brief Power management 1 (Bank0). */
#define ICM20948_REG_PWR_MGMT_1           0x06

/** @brief Power management 2 (Bank0). */
#define ICM20948_REG_PWR_MGMT_2           0x07

/** @brief Interrupt pin / routing configuration (Bank0). */
#define ICM20948_REG_INT_PIN_CFG          0x0F

/** @brief Interrupt enable (Bank0). */
#define ICM20948_REG_INT_ENABLE           0x10

/** @brief Interrupt enable 1 (Bank0). */
#define ICM20948_REG_INT_ENABLE_1         0x11

/** @brief Interrupt enable 2 (Bank0). */
#define ICM20948_REG_INT_ENABLE_2         0x12

/** @brief Interrupt enable 3 (Bank0). */
#define ICM20948_REG_INT_ENABLE_3         0x13

/** @brief I2C master status (Bank0). */
#define ICM20948_REG_I2C_MST_STATUS       0x17

/** @brief Interrupt status (Bank0). */
#define ICM20948_REG_INT_STATUS           0x19

/** @brief Interrupt status 1 (Bank0). */
#define ICM20948_REG_INT_STATUS_1         0x1A

/** @brief Interrupt status 2 (Bank0). */
#define ICM20948_REG_INT_STATUS_2         0x1B

/** @brief Interrupt status 3 (Bank0). */
#define ICM20948_REG_INT_STATUS_3         0x1C

/** @brief Delay time (high) (Bank0). */
#define ICM20948_REG_DELAY_TIMEH          0x28

/** @brief Delay time (low) (Bank0). */
#define ICM20948_REG_DELAY_TIMEL          0x29

/** @brief Accel X OUT high byte (Bank0). */
#define ICM20948_REG_ACCEL_XOUT_H         0x2D
/** @brief Accel X OUT low byte (Bank0). */
#define ICM20948_REG_ACCEL_XOUT_L         0x2E
/** @brief Accel Y OUT high byte (Bank0). */
#define ICM20948_REG_ACCEL_YOUT_H         0x2F
/** @brief Accel Y OUT low byte (Bank0). */
#define ICM20948_REG_ACCEL_YOUT_L         0x30
/** @brief Accel Z OUT high byte (Bank0). */
#define ICM20948_REG_ACCEL_ZOUT_H         0x31
/** @brief Accel Z OUT low byte (Bank0). */
#define ICM20948_REG_ACCEL_ZOUT_L         0x32

/** @brief Gyro X OUT high byte (Bank0). */
#define ICM20948_REG_GYRO_XOUT_H          0x33
/** @brief Gyro X OUT low byte (Bank0). */
#define ICM20948_REG_GYRO_XOUT_L          0x34
/** @brief Gyro Y OUT high byte (Bank0). */
#define ICM20948_REG_GYRO_YOUT_H          0x35
/** @brief Gyro Y OUT low byte (Bank0). */
#define ICM20948_REG_GYRO_YOUT_L          0x36
/** @brief Gyro Z OUT high byte (Bank0). */
#define ICM20948_REG_GYRO_ZOUT_H          0x37
/** @brief Gyro Z OUT low byte (Bank0). */
#define ICM20948_REG_GYRO_ZOUT_L          0x38

/** @brief Temperature OUT high byte (Bank0). */
#define ICM20948_REG_TEMP_OUT_H           0x39
/** @brief Temperature OUT low byte (Bank0). */
#define ICM20948_REG_TEMP_OUT_L           0x3A

/** @brief External slave sensor data base (Bank0). */
#define ICM20948_REG_EXT_SLV_SENS_DATA_00 0x3B

/** @brief FIFO enable 1 (Bank0). */
#define ICM20948_REG_FIFO_EN_1            0x66
/** @brief FIFO enable 2 (Bank0). */
#define ICM20948_REG_FIFO_EN_2            0x67
/** @brief FIFO reset (Bank0). */
#define ICM20948_REG_FIFO_RST             0x68
/** @brief FIFO mode (Bank0). */
#define ICM20948_REG_FIFO_MODE            0x69
/** @brief FIFO count high (Bank0). */
#define ICM20948_REG_FIFO_COUNTH          0x70
/** @brief FIFO count low (Bank0). */
#define ICM20948_REG_FIFO_COUNTL          0x71
/** @brief FIFO read/write (Bank0). */
#define ICM20948_REG_FIFO_R_W             0x72

/** @brief Data ready status (Bank0). */
#define ICM20948_REG_DATA_RDY_STATUS      0x74

/** @brief FIFO configuration (Bank0). */
#define ICM20948_REG_FIFO_CFG             0x76

/** @brief Bank select register (Bank0). */
#define ICM20948_REG_BANK_SEL             0x7F


// ==========================
// Bank 1 Registers
// (Offset calibration values)
// ==========================
/** @brief Self-test X gyro (Bank1). */
#define ICM20948_REG_SELF_TEST_X_GYRO     0x02
/** @brief Self-test Y gyro (Bank1). */
#define ICM20948_REG_SELF_TEST_Y_GYRO     0x03
/** @brief Self-test Z gyro (Bank1). */
#define ICM20948_REG_SELF_TEST_Z_GYRO     0x04
/** @brief Self-test X accel (Bank1). */
#define ICM20948_REG_SELF_TEST_X_ACCEL    0x0E
/** @brief Self-test Y accel (Bank1). */
#define ICM20948_REG_SELF_TEST_Y_ACCEL    0x0F
/** @brief Self-test Z accel (Bank1). */
#define ICM20948_REG_SELF_TEST_Z_ACCEL    0x10

/** @brief Accel X offset high (Bank1). */
#define ICM20948_REG_XA_OFFS_H            0x14
/** @brief Accel X offset low (Bank1). */
#define ICM20948_REG_XA_OFFS_L            0x15
/** @brief Accel Y offset high (Bank1). */
#define ICM20948_REG_YA_OFFS_H            0x17
/** @brief Accel Y offset low (Bank1). */
#define ICM20948_REG_YA_OFFS_L            0x18
/** @brief Accel Z offset high (Bank1). */
#define ICM20948_REG_ZA_OFFS_H            0x1A
/** @brief Accel Z offset low (Bank1). */
#define ICM20948_REG_ZA_OFFS_L            0x1B

/** @brief Gyro X offset MSB (Bank1). */
#define ICM20948_REG_XG_OFFS_USRH         0x03
/** @brief Gyro X offset LSB (Bank1). */
#define ICM20948_REG_XG_OFFS_USRL         0x04
/** @brief Gyro Y offset MSB (Bank1). */
#define ICM20948_REG_YG_OFFS_USRH         0x05
/** @brief Gyro Y offset LSB (Bank1). */
#define ICM20948_REG_YG_OFFS_USRL         0x06
/** @brief Gyro Z offset MSB (Bank1). */
#define ICM20948_REG_ZG_OFFS_USRH         0x07
/** @brief Gyro Z offset LSB (Bank1). */
#define ICM20948_REG_ZG_OFFS_USRL         0x08


// ==========================
// Bank 2 Registers
// (Main sensor config)
// ==========================
/** @brief Gyro sample rate divider (Bank2). */
#define ICM20948_REG_GYRO_SMPLRT_DIV      0x00

/** @brief Gyro configuration 1 (Bank2). */
#define ICM20948_REG_GYRO_CONFIG_1        0x01

/** @brief Gyro configuration 2 (Bank2). */
#define ICM20948_REG_GYRO_CONFIG_2        0x02

/** @brief XG offset MSB (Bank2). */
#define ICM20948_REG_XG_OFFS_USRH_2       0x03
/** @brief XG offset LSB (Bank2). */
#define ICM20948_REG_XG_OFFS_USRL_2       0x04
/** @brief YG offset MSB (Bank2). */
#define ICM20948_REG_YG_OFFS_USRH_2       0x05
/** @brief YG offset LSB (Bank2). */
#define ICM20948_REG_YG_OFFS_USRL_2       0x06
/** @brief ZG offset MSB (Bank2). */
#define ICM20948_REG_ZG_OFFS_USRH_2       0x07
/** @brief ZG offset LSB (Bank2). */
#define ICM20948_REG_ZG_OFFS_USRL_2       0x08

/** @brief ODR align enable (Bank2). */
#define ICM20948_REG_ODR_ALIGN_EN         0x09

/** @brief Accel sample rate divider 1 (Bank2). */
#define ICM20948_REG_ACCEL_SMPLRT_DIV_1   0x10
/** @brief Accel sample rate divider 2 (Bank2). */
#define ICM20948_REG_ACCEL_SMPLRT_DIV_2   0x11

/** @brief Accel intelligent control (Bank2). */
#define ICM20948_REG_ACCEL_INTEL_CTRL     0x12

/** @brief Accel wake-on-motion threshold (Bank2). */
#define ICM20948_REG_ACCEL_WOM_THR        0x13

/** @brief Accel configuration (Bank2). */
#define ICM20948_REG_ACCEL_CONFIG         0x14

/** @brief Accel configuration 2 (Bank2). */
#define ICM20948_REG_ACCEL_CONFIG_2       0x15

/** @brief FSYNC configuration (Bank2). */
#define ICM20948_REG_FSYNC_CONFIG         0x52

/** @brief Temperature configuration (Bank2). */
#define ICM20948_REG_TEMP_CONFIG          0x53

/** @brief Module control user (Bank2). */
#define ICM20948_REG_MOD_CTRL_USR         0x54


// ==========================
// Bank 3 Registers
// (I²C Master / Slave for magnetometer communication)
// ==========================
/** @brief I2C master ODR config (Bank3). */
#define ICM20948_REG_I2C_MST_ODR_CONFIG   0x00

/** @brief I2C master control (Bank3). */
#define ICM20948_REG_I2C_MST_CTRL         0x01

/** @brief I2C master delay control (Bank3). */
#define ICM20948_REG_I2C_MST_DELAY_CTRL   0x02

/** @brief I2C SLV0 address (Bank3). */
#define ICM20948_REG_I2C_SLV0_ADDR        0x03

/** @brief I2C SLV0 register (Bank3). */
#define ICM20948_REG_I2C_SLV0_REG         0x04

/** @brief I2C SLV0 control (Bank3). */
#define ICM20948_REG_I2C_SLV0_CTRL        0x05

/** @brief I2C SLV0 data out (Bank3). */
#define ICM20948_REG_I2C_SLV0_DO          0x06

/** @brief I2C SLV1 address (Bank3). */
#define ICM20948_REG_I2C_SLV1_ADDR        0x07

/** @brief I2C SLV1 register (Bank3). */
#define ICM20948_REG_I2C_SLV1_REG         0x08

/** @brief I2C SLV1 control (Bank3). */
#define ICM20948_REG_I2C_SLV1_CTRL        0x09

/** @brief I2C SLV1 data out (Bank3). */
#define ICM20948_REG_I2C_SLV1_DO          0x0A

/** @brief I2C SLV2 address (Bank3). */
#define ICM20948_REG_I2C_SLV2_ADDR        0x0B

/** @brief I2C SLV2 register (Bank3). */
#define ICM20948_REG_I2C_SLV2_REG         0x0C

/** @brief I2C SLV2 control (Bank3). */
#define ICM20948_REG_I2C_SLV2_CTRL        0x0D

/** @brief I2C SLV2 data out (Bank3). */
#define ICM20948_REG_I2C_SLV2_DO          0x0E

/** @brief I2C SLV3 address (Bank3). */
#define ICM20948_REG_I2C_SLV3_ADDR        0x0F

/** @brief I2C SLV3 register (Bank3). */
#define ICM20948_REG_I2C_SLV3_REG         0x10

/** @brief I2C SLV3 control (Bank3). */
#define ICM20948_REG_I2C_SLV3_CTRL        0x11

/** @brief I2C SLV3 data out (Bank3). */
#define ICM20948_REG_I2C_SLV3_DO          0x12

/** @brief I2C SLV4 address (Bank3). */
#define ICM20948_REG_I2C_SLV4_ADDR        0x13

/** @brief I2C SLV4 register (Bank3). */
#define ICM20948_REG_I2C_SLV4_REG         0x14

/** @brief I2C SLV4 control (Bank3). */
#define ICM20948_REG_I2C_SLV4_CTRL        0x15

/** @brief I2C SLV4 data out (Bank3). */
#define ICM20948_REG_I2C_SLV4_DO          0x16

/** @brief I2C SLV4 data in (Bank3). */
#define ICM20948_REG_I2C_SLV4_DI          0x17


// =========================================
// Magnetometer (AK09916) Registers
// =========================================

/** @brief AK09916 I2C slave address. */
#define AK09916_I2C_ADDR                 0x0C

/** @brief AK09916 WHO_AM_I (WIA2) register. */
#define AK09916_REG_WIA2                 0x01

/** @brief AK09916 status 1 register (data-ready & error flags). */
#define AK09916_REG_ST1                  0x10

/** @brief Magnetometer data low/high registers. */
#define AK09916_REG_HXL                  0x11
#define AK09916_REG_HXH                  0x12
#define AK09916_REG_HYL                  0x13
#define AK09916_REG_HYH                  0x14
#define AK09916_REG_HZL                  0x15
#define AK09916_REG_HZH                  0x16

/** @brief AK09916 status 2 register (overflow, data-ready clear). */
#define AK09916_REG_ST2                  0x18

/** @brief AK09916 control registers for measurement mode. */
#define AK09916_REG_CNTL2                0x31
#define AK09916_REG_CNTL3                0x32

/** @brief Temperature sensor registers for AK09916 (TS1 / TS2). */
#define AK09916_REG_TS1                  0x33
#define AK09916_REG_TS2                  0x34

/** @brief Self-test control (AK09916). */
#define AK09916_REG_ASTC                 0x0C

// Magnetometer mode settings (for AK09916)

/** @brief Power down mode (AK09916). */
#define AK09916_MODE_POWER_DOWN          0x00
/** @brief Single measurement mode (AK09916). */
#define AK09916_MODE_SINGLE_MEASURE      0x01
/** @brief Continuous 10 Hz mode (AK09916). */
#define AK09916_MODE_CONT_10HZ           0x02
/** @brief Continuous 20 Hz mode (AK09916). */
#define AK09916_MODE_CONT_20HZ           0x04
/** @brief Continuous 50 Hz mode (AK09916). */
#define AK09916_MODE_CONT_50HZ           0x06
/** @brief Continuous 100 Hz mode (AK09916). */
#define AK09916_MODE_CONT_100HZ          0x08
/** @brief Self-test mode (AK09916). */
#define AK09916_MODE_SELF_TEST           0x10

#endif /* MODULES_ICM20948_ICM20948_REGISTERS_HPP_ */
