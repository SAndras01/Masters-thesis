/**
 * @file AS5147U.hpp
 * @brief Interface for the AS5147U magnetic rotary encoder.
 *
 * This file provides a C++ driver interface for the AMS AS5147U
 * high-resolution magnetic position sensor using SPI communication.
 *
 * @details
 * The AS5147U is a 14-bit on-axis magnetic rotary encoder with SPI interface.
 * This driver supports:
 *  - Angle reading in degrees
 *  - Automatic Gain Control (AGC) readout
 *  - Device initialization
 *  - Software zero offset handling
 *
 * CRC8 checking and low-level SPI transactions are implemented
 * according to the AS5x47 device family specification.
 *
 * @author Sásdi András
 * @date October 10, 2025
 */

#ifndef MODULES_AS5147U_AS5147U_HPP_
#define MODULES_AS5147U_AS5147U_HPP_

#include "AS5147U_Registers.hpp"
#include "GPIO.hpp"
#include "string.h"
#include "main.h"

/// @brief Scaling factor for converting raw 14-bit angle data to degrees.
#define AS5147U_ANGLE_SCALER 16383.0f


/**
 * @brief Calculates CRC8 checksum according to AMS specification.
 *
 * Polynomial: 0x1D
 * Initial value: 0xC4
 * Final XOR: 0xFF
 *
 * @param data 16-bit data word to calculate CRC for.
 * @return Calculated CRC8 value.
 */
uint8_t AS5x47_CalcCRC8(uint16_t data);

/**
 * @brief Reads a 16-bit register from an AS5x47 device via SPI.
 *
 * A read operation consists of sending the read command frame,
 * followed by a second SPI transaction to receive the result.
 *
 * @param hspi HAL SPI handle.
 * @param CS_Port GPIO port of the chip select pin.
 * @param CS_Pin GPIO pin number of the chip select pin.
 * @param address Register address to read from.
 * @param result Pointer to store the received 16-bit data.
 *
 * @return True if the SPI communication was successful, false otherwise.
 */
bool AS5x47_Read16(SPI_HandleTypeDef *hspi,
                   GPIO_TypeDef *CS_Port,
                   uint16_t CS_Pin,
                   uint16_t address,
                   uint16_t* result);


/**
 * @brief Writes a 16-bit value to an AS5x47 device register.
 *
 * A write operation consists of two 24-bit SPI frames:
 *  - Address frame + CRC
 *  - Data frame + CRC
 *
 * @param hspi HAL SPI handle.
 * @param CS_Port GPIO port of the chip select pin.
 * @param CS_Pin GPIO pin number of the chip select pin.
 * @param address Register address to write.
 * @param data 16-bit data to be written.
 *
 * @return True if the SPI communication was successful, false otherwise.
 */
bool AS5x47_WriteRegister(SPI_HandleTypeDef *hspi,
                          GPIO_TypeDef *CS_Port,
                          uint16_t CS_Pin,
                          uint16_t address,
                          uint16_t data);


/**
 * @class AS5147U
 * @brief Driver class for the AMS AS5147U magnetic rotary encoder.
 *
 * This class provides high-level access to the AS5147U device functionality,
 * including initialization, angle reading, and AGC diagnostics.
 *
 * The driver assumes blocking SPI communication using the STM32 HAL.
 *
 * Example usage:
 * \code
 * AS5147U encoder(&hspi1, GPIOA, GPIO_PIN_4);
 *
 * encoder.init();
 *
 * while(1)
 * {
 *     float angle = encoder.getDegrees();
 * }
 * \endcode
 */
class AS5147U
{
private:
    /**
     * @brief HAL SPI handle used for device communication.
     */
    SPI_HandleTypeDef *hspi;

    /**
     * @brief GPIO port of the Chip Select pin.
     */
    GPIO_TypeDef *CS_Port;

    /**
     * @brief GPIO pin number of the Chip Select pin.
     */
    uint16_t CS_Pin;

    /**
     * @brief Software-defined zero offset in raw angle units.
     */
    uint16_t zeroOffset = 0;

    /**
     * @brief Reads raw 14-bit angle data from the device.
     *
     * @return Raw angle value (0–16383).
     */
    uint16_t getRawAngleData();

public:
    /**
     * @brief Constructor for the AS5147U driver class.
     *
     * @param hspi_p HAL SPI handle to be used.
     * @param CS_Port GPIO port of the Chip Select pin.
     * @param CS_Pin GPIO pin number of the Chip Select pin.
     */
    AS5147U(SPI_HandleTypeDef *hspi_p,
            GPIO_TypeDef *CS_Port,
            uint16_t CS_Pin);

    /**
     * @brief Initializes the AS5147U device.
     *
     * Configures internal settings and verifies communication
     * by reading back configuration and error flags.
     *
     * @return True if initialization was successful, false otherwise.
     */
    bool init();

    /**
     * @brief Returns the current angular position in degrees.
     *
     * @return Angle in degrees (0–360).
     */
    float getDegrees();

    /**
     * @brief Reads the Automatic Gain Control (AGC) value.
     *
     * The AGC value provides information about the magnetic field strength.
     *
     * @return AGC register value.
     */
    uint8_t getAGC();

    /**
     * @brief Sets a software zero offset.
     *
     * @param offset Zero offset in raw angle units (0–16383).
     */
    void setZeroOffset(uint16_t offset);

    /**
     * @brief Returns the currently configured zero offset.
     *
     * @return Zero offset in raw angle units.
     */
    uint16_t getZeroOffset();
};

#endif /* MODULES_AS5147U_AS5147U_HPP_ */
