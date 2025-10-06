/*
 * ICM2098_Registers.hpp
 *
 * @brief Complete register map for ICM-20948 gyroscope, accelerometer, and magnetometer.
 *
 * Contains addresses from:
 *  - Chapter 7:  REGISTER MAP FOR GYROSCOPE AND ACCELEROMETER
 *  - Chapter 12: REGISTER MAP FOR MAGNETOMETER (AK09916)
 *
 * Author: Andris
 */

#ifndef MODULES_ICM2098_ICM2098_REGISTERS_HPP_
#define MODULES_ICM2098_ICM2098_REGISTERS_HPP_


// ==========================
// Common Registers (Bank 0)
// ==========================
#define ICM20948_REG_WHO_AM_I             0x00
#define ICM20948_REG_USER_CTRL            0x03
#define ICM20948_REG_LP_CONFIG            0x05
#define ICM20948_REG_PWR_MGMT_1           0x06
#define ICM20948_REG_PWR_MGMT_2           0x07
#define ICM20948_REG_INT_PIN_CFG          0x0F
#define ICM20948_REG_INT_ENABLE           0x10
#define ICM20948_REG_INT_ENABLE_1         0x11
#define ICM20948_REG_INT_ENABLE_2         0x12
#define ICM20948_REG_INT_ENABLE_3         0x13
#define ICM20948_REG_I2C_MST_STATUS       0x17
#define ICM20948_REG_INT_STATUS           0x19
#define ICM20948_REG_INT_STATUS_1         0x1A
#define ICM20948_REG_INT_STATUS_2         0x1B
#define ICM20948_REG_INT_STATUS_3         0x1C
#define ICM20948_REG_DELAY_TIMEH          0x28
#define ICM20948_REG_DELAY_TIMEL          0x29
#define ICM20948_REG_ACCEL_XOUT_H         0x2D
#define ICM20948_REG_ACCEL_XOUT_L         0x2E
#define ICM20948_REG_ACCEL_YOUT_H         0x2F
#define ICM20948_REG_ACCEL_YOUT_L         0x30
#define ICM20948_REG_ACCEL_ZOUT_H         0x31
#define ICM20948_REG_ACCEL_ZOUT_L         0x32
#define ICM20948_REG_GYRO_XOUT_H          0x33
#define ICM20948_REG_GYRO_XOUT_L          0x34
#define ICM20948_REG_GYRO_YOUT_H          0x35
#define ICM20948_REG_GYRO_YOUT_L          0x36
#define ICM20948_REG_GYRO_ZOUT_H          0x37
#define ICM20948_REG_GYRO_ZOUT_L          0x38
#define ICM20948_REG_TEMP_OUT_H           0x39
#define ICM20948_REG_TEMP_OUT_L           0x3A
#define ICM20948_REG_EXT_SLV_SENS_DATA_00 0x3B
#define ICM20948_REG_FIFO_EN_1            0x66
#define ICM20948_REG_FIFO_EN_2            0x67
#define ICM20948_REG_FIFO_RST             0x68
#define ICM20948_REG_FIFO_MODE            0x69
#define ICM20948_REG_FIFO_COUNTH          0x70
#define ICM20948_REG_FIFO_COUNTL          0x71
#define ICM20948_REG_FIFO_R_W             0x72
#define ICM20948_REG_DATA_RDY_STATUS      0x74
#define ICM20948_REG_FIFO_CFG             0x76
#define ICM20948_REG_BANK_SEL             0x7F

// ==========================
// Bank 1 Registers
// (Offset calibration values)
// ==========================
#define ICM20948_REG_SELF_TEST_X_GYRO     0x02
#define ICM20948_REG_SELF_TEST_Y_GYRO     0x03
#define ICM20948_REG_SELF_TEST_Z_GYRO     0x04
#define ICM20948_REG_SELF_TEST_X_ACCEL    0x0E
#define ICM20948_REG_SELF_TEST_Y_ACCEL    0x0F
#define ICM20948_REG_SELF_TEST_Z_ACCEL    0x10
#define ICM20948_REG_XA_OFFS_H            0x14
#define ICM20948_REG_XA_OFFS_L            0x15
#define ICM20948_REG_YA_OFFS_H            0x17
#define ICM20948_REG_YA_OFFS_L            0x18
#define ICM20948_REG_ZA_OFFS_H            0x1A
#define ICM20948_REG_ZA_OFFS_L            0x1B
#define ICM20948_REG_XG_OFFS_USRH         0x03
#define ICM20948_REG_XG_OFFS_USRL         0x04
#define ICM20948_REG_YG_OFFS_USRH         0x05
#define ICM20948_REG_YG_OFFS_USRL         0x06
#define ICM20948_REG_ZG_OFFS_USRH         0x07
#define ICM20948_REG_ZG_OFFS_USRL         0x08

// ==========================
// Bank 2 Registers
// (Main sensor config)
// ==========================
#define ICM20948_REG_GYRO_SMPLRT_DIV      0x00
#define ICM20948_REG_GYRO_CONFIG_1        0x01
#define ICM20948_REG_GYRO_CONFIG_2        0x02
#define ICM20948_REG_XG_OFFS_USRH_2       0x03
#define ICM20948_REG_XG_OFFS_USRL_2       0x04
#define ICM20948_REG_YG_OFFS_USRH_2       0x05
#define ICM20948_REG_YG_OFFS_USRL_2       0x06
#define ICM20948_REG_ZG_OFFS_USRH_2       0x07
#define ICM20948_REG_ZG_OFFS_USRL_2       0x08
#define ICM20948_REG_ODR_ALIGN_EN         0x09
#define ICM20948_REG_ACCEL_SMPLRT_DIV_1   0x10
#define ICM20948_REG_ACCEL_SMPLRT_DIV_2   0x11
#define ICM20948_REG_ACCEL_INTEL_CTRL     0x12
#define ICM20948_REG_ACCEL_WOM_THR        0x13
#define ICM20948_REG_ACCEL_CONFIG         0x14
#define ICM20948_REG_ACCEL_CONFIG_2       0x15
#define ICM20948_REG_FSYNC_CONFIG         0x52
#define ICM20948_REG_TEMP_CONFIG          0x53
#define ICM20948_REG_MOD_CTRL_USR         0x54

// ==========================
// Bank 3 Registers
// (I²C Master / Slave for magnetometer communication)
// ==========================
#define ICM20948_REG_I2C_MST_ODR_CONFIG   0x00
#define ICM20948_REG_I2C_MST_CTRL         0x01
#define ICM20948_REG_I2C_MST_DELAY_CTRL   0x02
#define ICM20948_REG_I2C_SLV0_ADDR        0x03
#define ICM20948_REG_I2C_SLV0_REG         0x04
#define ICM20948_REG_I2C_SLV0_CTRL        0x05
#define ICM20948_REG_I2C_SLV0_DO          0x06
#define ICM20948_REG_I2C_SLV1_ADDR        0x07
#define ICM20948_REG_I2C_SLV1_REG         0x08
#define ICM20948_REG_I2C_SLV1_CTRL        0x09
#define ICM20948_REG_I2C_SLV1_DO          0x0A
#define ICM20948_REG_I2C_SLV2_ADDR        0x0B
#define ICM20948_REG_I2C_SLV2_REG         0x0C
#define ICM20948_REG_I2C_SLV2_CTRL        0x0D
#define ICM20948_REG_I2C_SLV2_DO          0x0E
#define ICM20948_REG_I2C_SLV3_ADDR        0x0F
#define ICM20948_REG_I2C_SLV3_REG         0x10
#define ICM20948_REG_I2C_SLV3_CTRL        0x11
#define ICM20948_REG_I2C_SLV3_DO          0x12
#define ICM20948_REG_I2C_SLV4_ADDR        0x13
#define ICM20948_REG_I2C_SLV4_REG         0x14
#define ICM20948_REG_I2C_SLV4_CTRL        0x15
#define ICM20948_REG_I2C_SLV4_DO          0x16
#define ICM20948_REG_I2C_SLV4_DI          0x17

// =========================================
// Magnetometer (AK09916) Registers
// =========================================
#define AK09916_I2C_ADDR                 0x0C
#define AK09916_REG_WIA2                 0x01
#define AK09916_REG_ST1                  0x10
#define AK09916_REG_HXL                  0x11
#define AK09916_REG_HXH                  0x12
#define AK09916_REG_HYL                  0x13
#define AK09916_REG_HYH                  0x14
#define AK09916_REG_HZL                  0x15
#define AK09916_REG_HZH                  0x16
#define AK09916_REG_ST2                  0x18
#define AK09916_REG_CNTL2                0x31
#define AK09916_REG_CNTL3                0x32
#define AK09916_REG_TS1                  0x33
#define AK09916_REG_TS2                  0x34
#define AK09916_REG_ASTC                 0x0C

// Magnetometer mode settings (for AK09916)
#define AK09916_MODE_POWER_DOWN          0x00
#define AK09916_MODE_SINGLE_MEASURE      0x01
#define AK09916_MODE_CONT_10HZ           0x02
#define AK09916_MODE_CONT_20HZ           0x04
#define AK09916_MODE_CONT_50HZ           0x06
#define AK09916_MODE_CONT_100HZ          0x08
#define AK09916_MODE_SELF_TEST           0x10



#endif /* MODULES_ICM2098_ICM2098_REGISTERS_HPP_ */
