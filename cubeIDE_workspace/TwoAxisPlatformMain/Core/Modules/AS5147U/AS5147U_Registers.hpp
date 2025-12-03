/**
 * @file AS5147U_Registers.hpp
 * @brief Register map definitions for the AS5147U magnetic rotary encoder.
 *
 * This file contains register address definitions for both volatile and
 * non-volatile memory areas of the AMS AS5147U magnetic position sensor.
 *
 * @details
 * The register addresses defined here are intended to be used with the
 * AS5147U SPI driver implementation. Registers are grouped into
 * volatile (read-only runtime data) and non-volatile (configuration)
 * sections according to the datasheet.
 *
 * For the detailed description of registers, bit fields, timing diagrams
 * and SPI protocol, refer to the official AMS datasheet:
 *
 * @see https://look.ams-osram.com/m/d4566ea9c648455/original/AS5147U-AS5247U-DS000639.pdf
 *
 * @author Sásdi András
 * @date October 10, 2025
 */

#ifndef MODULES_AS5147U_AS5147U_REGISTERS_HPP_
#define MODULES_AS5147U_AS5147U_REGISTERS_HPP_

/* ============================================================
 * Volatile Memory Register Table
 * ============================================================ */

/**
 * @brief No operation register.
 *
 * Used as a dummy access to trigger an SPI response frame.
 */
#define AS5147U_NOP             0x0000

/**
 * @brief Error flags register.
 *
 * Contains error and diagnostic flags reported by the device.
 */
#define AS5147U_ERRFL           0x0001

/**
 * @brief Programming control register.
 */
#define AS5147U_PROG            0x0003

/**
 * @brief Diagnostic register.
 *
 * Provides internal diagnostic information.
 */
#define AS5147U_DIA             0x3FF5

/**
 * @brief Automatic Gain Control (AGC) register.
 *
 * Indicates the detected magnetic field strength.
 */
#define AS5147U_AGC             0x3FF9

/**
 * @brief Raw digital sine channel data.
 */
#define AS5147U_SIN_DATA        0x3FFA

/**
 * @brief Raw digital cosine channel data.
 */
#define AS5147U_COS_DATA        0x3FFB

/**
 * @brief Angular velocity register.
 *
 * Contains the estimated rotational speed of the shaft.
 */
#define AS5147U_VEL             0x3FFC

/**
 * @brief CORDIC magnitude register.
 *
 * Represents the calculated magnitude of the magnetic field.
 */
#define AS5147U_MAG             0x3FFD

/**
 * @brief Uncompensated angle register.
 *
 * Measured angle without dynamic angle error compensation.
 */
#define AS5147U_ANGLEUNC        0x3FFE

/**
 * @brief Compensated angle register.
 *
 * Measured angle with dynamic angle error compensation applied.
 */
#define AS5147U_ANGLECOM        0x3FFF

/**
 * @brief ECC checksum register.
 *
 * Contains an ECC checksum calculated based on current register settings.
 */
#define AS5147U_ECC_Checksum    0x00D1


/* ============================================================
 * Non-Volatile Memory Register Table
 * ============================================================ */

/**
 * @brief Output and filter disable register.
 *
 * Controls output drivers and internal filters.
 */
#define AS5147U_DISABLE         0x0015

/**
 * @brief Zero position MSB register.
 *
 * Stores the most significant bits of the zero position offset.
 */
#define AS5147U_ZPOSM           0x0016

/**
 * @brief Zero position LSB / magnetic diagnostic register.
 *
 * Stores the least significant bits of the zero position offset and
 * provides magnet diagnostic information.
 */
#define AS5147U_ZPOSL           0x0017

/**
 * @brief Customer settings register 1.
 *
 * Contains configuration bits for hysteresis, gain and filtering.
 */
#define AS5147U_SETTINGS1       0x0018

/**
 * @brief Customer settings register 2.
 *
 * Contains interface and output configuration options.
 */
#define AS5147U_SETTINGS2       0x0019

/**
 * @brief Customer settings register 3.
 */
#define AS5147U_SETTINGS3       0x001A

/**
 * @brief ECC configuration register.
 *
 * Controls the ECC behavior for non-volatile registers.
 */
#define AS5147U_ECC             0x001B

#endif /* MODULES_AS5147U_AS5147U_REGISTERS_HPP_ */
