/*
 * AS5147U.hpp
 *
 *  Created on: 2025. okt. 10.
 *      Author: SNA1BP
 */

#ifndef MODULES_AS5147U_AS5147U_HPP_
#define MODULES_AS5147U_AS5147U_HPP_

#include "AS5147U_Registers.hpp"
#include "GPIO.hpp"
#include "string.h"
#include "main.h"

#define AS5147U_ANGLE_SCALER 16383.0f

uint8_t AS5x47_CalcCRC8(uint16_t data);
bool AS5x47_Read16(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address, uint16_t* result);
bool AS5x47_WriteRegister(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address, uint16_t data);

//@todo implement further functionalities
class AS5147U
{
private:
	/**
	 * @brief The HAL SPI handle that will be used to communicate with the device
	 */
	SPI_HandleTypeDef *hspi;

	/**
	 * @brief The \link GPIO \endlink that is used as the chip select pin.
	 */
	GPIO_TypeDef *CS_Port;
	uint16_t CS_Pin;
	uint16_t zeroOffset = 0;

	uint16_t getRawAngleData();
public:

	AS5147U(SPI_HandleTypeDef *hspi_p, GPIO_TypeDef *CS_Port, uint16_t CS_Pin);
	bool init();

	float getDegrees();
	uint8_t getAGC();

	void setZeroOffset(uint16_t offset);
	uint16_t getZeroOffset();
};


#endif /* MODULES_AS5147U_AS5147U_HPP_ */
