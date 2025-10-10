/*
 * AS5147U.cpp
 *
 *  Created on: 2025. okt. 10.
 *      Author: SNA1BP
 */

#include "AS5147U.hpp"


// AS5147U CRC8 calculation (AMS polynomial 0x1D)
uint8_t AS5x47_CalcCRC8(uint16_t data)
{
    uint8_t crc = 0xC4;
    uint8_t bytes[2] = { (uint8_t)(data >> 8), (uint8_t)(data & 0xFF) };

    for (int i = 0; i < 2; i++) {
        crc ^= bytes[i];
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80)
                crc = ((crc << 1) ^ 0x1D) & 0xFF;
            else
                crc = (crc << 1) & 0xFF;
        }
    }
    crc ^= 0xFF;
    return crc;
}


bool AS5x47_Read16(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address, uint16_t* result)
{
    uint8_t tx[2];
    uint8_t rx[2];
    uint16_t cmd = (0x4000u | (address & 0x3FFFu)); // bit14=1 -> read

    tx[0] = (uint8_t)(cmd >> 8);
    tx[1] = (uint8_t)(cmd & 0xFF);

    // 1) Send the read command (address with bit14 set to 1)
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    if(HAL_SPI_Transmit(hspi, tx, 2, HAL_MAX_DELAY) != HAL_OK) return false;
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    // 2) Read the reply
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    if(HAL_SPI_Receive(hspi, rx, 2, HAL_MAX_DELAY) != HAL_OK) return false;
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    uint16_t tmp = ((uint16_t)rx[0] << 8) | rx[1];
    memcpy(result, &tmp, sizeof(uint16_t));

    return true;
}

bool AS5x47_WriteRegister(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address, uint16_t data)
{
    uint8_t frame[3];

    // Első 24-bit frame: write command
    uint16_t cmd = (address & 0x3FFFu);  // bit14=0 (write)
    uint8_t crc_cmd = AS5x47_CalcCRC8(cmd);

    frame[0] = (uint8_t)(cmd >> 8);
    frame[1] = (uint8_t)(cmd & 0xFF);
    frame[2] = crc_cmd;

    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    if(HAL_SPI_Transmit(hspi, frame, 3, HAL_MAX_DELAY) != HAL_OK) return false;
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    HAL_Delay(1); // kis szünet a két frame között

    // Második 24-bit frame: data + CRC
    uint8_t crc_data = AS5x47_CalcCRC8(data);
    frame[0] = (uint8_t)(data >> 8);
    frame[1] = (uint8_t)(data & 0xFF);
    frame[2] = crc_data;

    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    if(HAL_SPI_Transmit(hspi, frame, 3, HAL_MAX_DELAY) != HAL_OK) return false;
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    return true;
}

AS5147U::AS5147U(SPI_HandleTypeDef *hspi_p, GPIO_TypeDef *CS_Port, uint16_t CS_Pin)
{
	this->hspi = hspi_p;
	this->CS_Port = CS_Port;
	this->CS_Pin = CS_Pin;
}

bool AS5147U::init()
{
	//Low rotation speeds -> K_min is set to 0
	uint16_t settings1 = 0;
	uint16_t settings1_check = 0;

	uint16_t errors = 0;

	//Set min K value to 0
	if( !AS5x47_Read16(hspi, CS_Port, CS_Pin, AS5147U_SETTINGS1, &settings1)) return false;
	settings1 |= (0b101 << 3);
	if( !AS5x47_WriteRegister(hspi, CS_Port, CS_Pin, 0x0018, settings1)) return false;

	if( !AS5x47_Read16(hspi, CS_Port, CS_Pin, AS5147U_SETTINGS1, &settings1_check)) return false;

	if( settings1 != settings1_check) return false;

	if( !AS5x47_Read16(hspi, CS_Port, CS_Pin, AS5147U_ERRFL, &errors)) return false;
	//todo error management
	if( errors != 0) return false;

	return true;
}

uint16_t AS5147U::getRawAngleData()
{
	uint16_t rawAngleData = 0;
	AS5x47_Read16(hspi, CS_Port, CS_Pin, AS5147U_ANGLECOM, &rawAngleData);
	rawAngleData &= 0x3FFF;

	return rawAngleData;
}

float AS5147U::getDegrees()
{
	return (float)getRawAngleData()/AS5147U_ANGLE_SCALER * (float)360;
}

uint8_t AS5147U::getAGC()
{
	uint16_t AGCdata = 0;
	AS5x47_Read16(hspi, CS_Port, CS_Pin, AS5147U_AGC, &AGCdata);
	AGCdata &= 0xFF;

	return (uint8_t)AGCdata;
}

void AS5147U::setZeroOffset(uint16_t offset)
{
	if(offset >= (uint16_t)AS5147U_ANGLE_SCALER)
	{
		offset = (uint16_t)AS5147U_ANGLE_SCALER;
		return;
	}
	zeroOffset = offset;
}


uint16_t AS5147U::getZeroOffset()
{
	return zeroOffset;
}
