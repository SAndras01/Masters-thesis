/*
 * SSD1305.hpp
 *
 *  Created on: 2025. szept. 2.
 *      Author: SNA1BP
 */

#ifndef MODULES_SSD1305_SSD1305_HPP_
#define MODULES_SSD1305_SSD1305_HPP_

#include <stdint.h>
#include "stm32f4xx_hal.h"


// ===========================
// Fundamental Commands
// ===========================
#define SSD1305_SET_LOWER_COLUMN        0x00    // 00h~0Fh
#define SSD1305_SET_HIGHER_COLUMN       0x10    // 10h~1Fh

#define SSD1305_MEMORY_ADDR_MODE        0x20
#define   SSD1305_ADDRMODE_HORIZONTAL   0b00
#define   SSD1305_ADDRMODE_VERTICAL     0b01
#define   SSD1305_ADDRMODE_PAGE         0b10

#define SSD1305_SET_COLUMN_ADDR         0x21
#define SSD1305_SET_PAGE_ADDR           0x22

#define SSD1305_SET_START_LINE          0x40    // 40h~7Fh

#define SSD1305_SET_CONTRAST            0x81
#define SSD1305_SET_BRIGHTNESS          0x82    // area color mode
#define SSD1305_SET_LUT                 0x91
#define SSD1305_SET_BANK_COLOR1         0x92
#define SSD1305_SET_BANK_COLOR2         0x93

#define SSD1305_SEG_REMAP        		0xA0

#define SSD1305_ENTIRE_DISPLAY_ON   	0xA4

#define SSD1305_SET_NORMAL_INVERSE		0xA6

#define SSD1305_SET_MULTIPLEX_RATIO     0xA8
#define SSD1305_DIM_MODE                0xAB
#define SSD1305_MASTER_CONFIG           0xAD


#define SSD1305_SET_DISPLAY_ON_OFF		0xAC

#define SSD1305_SET_PAGE_START          0xB0    // B0h~B7h

#define SSD1305_COM_SCAN_INC            0xC0
#define SSD1305_COM_SCAN_DEC            0xC8

#define SSD1305_SET_DISPLAY_OFFSET      0xD3
#define SSD1305_SET_CLOCK_DIV           0xD5
#define SSD1305_SET_COLOR_n_POWER_MODE	0xD8
#define SSD1305_SET_PRECHARGE_PERIOD    0xD9
#define SSD1305_SET_COM_PINS_HW_CNFG	0xDA
#define SSD1305_SET_VCOMH_DESELECT      0xDB

#define SSD1305_READ_MODIFY_WRITE       0xE0
#define SSD1305_NOP                     0xE3
#define SSD1305_EXIT_RMW                0xEE

// ===========================
// Scrolling Commands
// ===========================
#define SSD1305_SCROLL_RIGHT            0x26
#define SSD1305_SCROLL_LEFT             0x27
#define SSD1305_SCROLL_VERT_RIGHT       0x29
#define SSD1305_SCROLL_VERT_LEFT        0x2A
#define SSD1305_DEACTIVATE_SCROLL       0x2E
#define SSD1305_ACTIVATE_SCROLL         0x2F
#define SSD1305_SET_SCROLL_AREA         0xA3

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

#define COMMAND_ADDRESS 0X00
#define DATA_ADDRESS	0X40
//
//  Enumeration for screen colors
//
enum SSD1305_COLOR{
    Black = 0x00,   // Black color, no pixel
    White = 0x01,   // Pixel is set. Color depends on LCD
};

enum MemoryAddressingMode
{
	horizontal = SSD1305_ADDRMODE_HORIZONTAL,
	vertical = SSD1305_ADDRMODE_VERTICAL,
	page = SSD1305_ADDRMODE_PAGE
};

enum SegmentRemap
{
	columnAddress0toSEG0 = 0b0,
	columnAddress131toSEG0 = 0b1
};

enum DisplayONMode
{
	ResumeToRAMContent = 0xA4,
	IgnoreRAMContent = 0xA5
};

enum DisplayMode
{
	DisplayOnDimMode = 0xAC,
	DisplayOffSleepMode = 0xAE,
	DisplayOnNormalMode = 0xAF
};

enum DisplayInverseMode
{
	normal = 0xA6,
	inverse = 0xA7
};

enum ComOutputScanDirection
{
	normalMode = 0xC0,
	remappedMode= 0xC8
};

enum ColorMode
{
	monochromeMode = 	0b00000000,
	colorMode = 0b00110000
};

enum PowerMode
{
	normalPowerMode = 0b0000,
	lowPowerMode= 0b0101
};

enum COMPinConfig
{
	sequential = 0b00000010,
	alternative= 0b00010010
};

enum EnableCOMRemap
{
	enable = 0b00010010,
	disable= 0b00000010
};

enum VcomhDeselectLevel
{
	VCCx0p43 = 0x0,
	VCCx0p77 = 0x34,
	VCCx0p83 = 0x3C
};


class SSD1305
{
private:
	I2C_HandleTypeDef* hi2c;

	uint8_t address;
	uint8_t width;
	uint8_t height;

    uint16_t currentX;
    uint16_t currentY;
    uint8_t inverted;
    uint8_t initialized;

    uint8_t commandBuffer[5];
    uint8_t Buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];


    HAL_StatusTypeDef SendCommand(uint8_t commandSize);


public:
    SSD1305(	I2C_HandleTypeDef* hi2c_p,
    			uint8_t address_p,
				uint8_t width_p,
				uint8_t height_p);

    bool Init();

    HAL_StatusTypeDef UpdateScreen();

    bool Fill(SSD1305_COLOR color_p);
    bool DrawPixel(uint8_t x, uint8_t y, SSD1305_COLOR color_p);
    //bool WriteChar(char ch, FontDef Font, SSD1305_COLOR color);
    //bool WriteString(const char* str, FontDef Font, SSD1305_COLOR color);
    bool SetCursor(uint8_t x, uint8_t y);
    bool InvertColors(void);

    //IC functions


    HAL_StatusTypeDef EnterReadModifyWrite();

    HAL_StatusTypeDef SetLowerColumnStartAddress(uint8_t startAddress_p);
    HAL_StatusTypeDef SetHigherColumnStartAddress(uint8_t startAddress_p);
    HAL_StatusTypeDef SetMemoryAddressingMode(MemoryAddressingMode mode_p);
    HAL_StatusTypeDef SetColumnAddress(uint8_t startAddres_p, uint8_t endAddres_p);
    HAL_StatusTypeDef SetPageAddress(uint8_t startAddres_p, uint8_t endAddres_p);
    HAL_StatusTypeDef SetDisplayStartLine(uint8_t line_p);
    HAL_StatusTypeDef SetContrastControllBANK0(uint8_t contrast_p);
    HAL_StatusTypeDef SetBrightnessForAreaColorBanks(uint8_t brightness_p);
    HAL_StatusTypeDef SetLUT(uint8_t LUT_BANK0_p, uint8_t LUT_ColorA_p, uint8_t LUT_ColorB_p, uint8_t LUT_ColorC_p);
    HAL_StatusTypeDef SetSegmentReMap(SegmentRemap remap_p);
    HAL_StatusTypeDef EntireDisplayON(DisplayONMode displayONMode_p);
    HAL_StatusTypeDef SetNormalInverse(DisplayInverseMode inversMode_p);
    HAL_StatusTypeDef SetMultiplexRatio(uint8_t ratio_p);
    HAL_StatusTypeDef SetDimMode(uint8_t contrastBANK0_p, uint8_t brightnessForColorBank_p);
    HAL_StatusTypeDef SetDisplayON_OFF(DisplayMode mode_p);
    HAL_StatusTypeDef SetPageStartAddress(uint8_t startAddres_p);
    HAL_StatusTypeDef SetComOutputScanDirection(ComOutputScanDirection scanDirection_p);
    HAL_StatusTypeDef SetDisplayOffset(uint8_t verticalShift_p);
    HAL_StatusTypeDef SetDisplayClockDivideRatio_OscillatorFrequency(uint8_t divideRatio_p, uint8_t fOscillator_p);
    HAL_StatusTypeDef SetColorAndPowerMode(ColorMode colorMode_p, PowerMode powerMode_p);
    HAL_StatusTypeDef SetPrechargePeriod(uint8_t phase1_p, uint8_t phase2_p);
    HAL_StatusTypeDef SetCOMPinsHWConfig(COMPinConfig pinConfig_p, EnableCOMRemap remapEnable_p);
    HAL_StatusTypeDef SetVcomhDeselectLevel(VcomhDeselectLevel vcomhDeselectLevel_p);

    HAL_StatusTypeDef NOP();

    HAL_StatusTypeDef ExitReadModifyWrite();

    //ToBeImplemented for color displays
    HAL_StatusTypeDef SetBankColorOfBANK1toBANK16(); //returnError: unimplemented
    HAL_StatusTypeDef SetBankColorOfBANK17toBANK32(); //returnError: unimplemented


    //Graphic acceleration commands to be implemented as needed



};


#endif /* MODULES_SSD1305_SSD1305_HPP_ */
