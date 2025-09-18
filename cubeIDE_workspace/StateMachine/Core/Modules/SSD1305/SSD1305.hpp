/**
 * @file SSD1305.hpp
 * @brief SSD1305 OLED display driver header file.
 *
 * This file contains the definitions, enumerations, and class interface for
 * controlling an SSD1305-based OLED display via I2C. The class provides methods
 * for initialization, drawing pixels, writing text, sending bitmaps, and
 * executing SSD1305-specific IC functions as described in the datasheet.
 *
 * @date 2025-09-02
 * @author SNA1BP
 */

#ifndef MODULES_SSD1305_SSD1305_HPP_
#define MODULES_SSD1305_SSD1305_HPP_

#include <stdint.h>
#include "fonts.h"
#include "test_bitmaps.hpp"
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
	remappedMode = 0xC8
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
	enable = 0b00100010,
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

    uint8_t commandBuffer[5];
    uint8_t bitmapBuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

    uint8_t v_offset = 4;

    HAL_StatusTypeDef SendCommand(uint8_t commandSize);


public:
	SSD1305(	I2C_HandleTypeDef* hi2c_p,
				uint8_t address_p,
				uint8_t width_p,
				uint8_t height_p);

	bool Init();

	HAL_StatusTypeDef WriteBitmapToScreen();
	HAL_StatusTypeDef WriteBitmapToScreen(uint8_t* bitmap, size_t size);

	void FillBitmapBuffer(SSD1305_COLOR color_p);
	HAL_StatusTypeDef Fill(SSD1305_COLOR color_p);

	bool DrawPixel(uint8_t x, uint8_t y, SSD1305_COLOR color_p);
	char WriteChar(char ch, FontDef Font, SSD1305_COLOR color);
	bool WriteString(const char* str, FontDef Font, SSD1305_COLOR color);

	void SetCursor(uint8_t x, uint8_t y);


	uint8_t GetHeight();
	uint8_t GetWidth();

	//IC functions


	/**
	 * @brief Enter Read-Modify-Write mode.
	 *
	 * Allows modification of part of the display RAM without resetting the column/page address.
	 * After issuing this command, data writes modify only the specified bits.
	 *
	 * @return HAL status.
	 */
	HAL_StatusTypeDef EnterReadModifyWrite();

    /**
     * @brief Set the lower 4 bits of the column start address for Page Addressing Mode.
     *
     * @param startAddress_p Lower nibble (0x00–0x0F).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetLowerColumnStartAddress(uint8_t startAddress_p);

    /**
     * @brief Set the higher 4 bits of the column start address for Page Addressing Mode.
     *
     * @param startAddress_p Upper nibble (0x00–0x0F).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetHigherColumnStartAddress(uint8_t startAddress_p);

    /**
     * @brief Set memory addressing mode.
     *
     * Controls how RAM is accessed when writing data:
     * - horizontal: increments column, wraps to next page.
     * - vertical: increments page, wraps to next column.
     * - page: increments column only, page fixed.
     *
     * @param mode_p Addressing mode.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetMemoryAddressingMode(MemoryAddressingMode mode_p);

    /**
     * @brief Set column address range.
     *
     * @param startAddres_p Start column (0–131).
     * @param endAddres_p End column (0–131).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetColumnAddress(uint8_t startAddres_p, uint8_t endAddres_p);

    /**
     * @brief Set page address range.
     *
     * @param startAddres_p Start page (0–7).
     * @param endAddres_p End page (0–7).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetPageAddress(uint8_t startAddres_p, uint8_t endAddres_p);


    /**
     * @brief Set display start line.
     *
     * Defines which RAM line (0–63) maps to the COM0 output.
     *
     * @param line_p Line address (0–63).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetDisplayStartLine(uint8_t line_p);


    /**
     * @brief This command sets the Contrast Setting of the display. The chip has 256 contrast steps from 00h to FFh.
     * The segment output current increases as the contrast step value increases.
     *
     * @param contrast_p Contrast value (0x00–0xFF).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetContrastControllBANK0(uint8_t contrast_p);

    /**
     * @brief Set brightness for area color banks.
     *
     * @param brightness_p Brightness level (0x00–0xFF).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetBrightnessForAreaColorBanks(uint8_t brightness_p);

    /**
     * @brief Set Look-Up Table (LUT) for gray scale.
     *
     * Each parameter must be between 32–63 according to the datasheet.
     *
     * @param LUT_BANK0_p Gray scale level for bank 0.
     * @param LUT_ColorA_p Gray scale level for color A.
     * @param LUT_ColorB_p Gray scale level for color B.
     * @param LUT_ColorC_p Gray scale level for color C.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetLUT(uint8_t LUT_BANK0_p, uint8_t LUT_ColorA_p, uint8_t LUT_ColorB_p, uint8_t LUT_ColorC_p);

    /**
     * @brief Set segment remap.
     *
     * Changes the mapping of column addresses to SEG outputs.
     *
     * @param remap_p Remap option.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetSegmentReMap(SegmentRemap remap_p);

    /**
     * @brief Force the entire display ON or resume RAM content display.
     *
     * @param displayONMode_p Display ON mode.
     * @return HAL status.
     */
	HAL_StatusTypeDef EntireDisplayON(DisplayONMode displayONMode_p);

    /**
     * @brief Set normal or inverse display.
     *
     * @param inversMode_p normal or inverse.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetNormalInverse(DisplayInverseMode inversMode_p);

    /**
     * @brief Set multiplex ratio.
     *
     * Defines number of active COM lines = ratio_p + 1. Should be set to height-1
     *
     * @param ratio_p Multiplex ratio (15–63).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetMultiplexRatio(uint8_t ratio_p);

    /**
     * @brief Set dim mode parameters.
     *
     * Adjusts contrast and brightness for dim operation.
     *
     * @param contrastBANK0_p Contrast for bank 0.
     * @param brightnessForColorBank_p Brightness value for color banks.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetDimMode(uint8_t contrastBANK0_p, uint8_t brightnessForColorBank_p);

    /**
     * @brief Set display OFF/ON(normal or dim)
     *
     * @param mode_p Display mode.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetDisplayON_OFF(DisplayMode mode_p);

    /**
     * @brief Position the page start address from 0 to 7 in GDDRAM under Page Addressing Mode.
     *
     * @param startAddres_p Page start (0–7).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetPageStartAddress(uint8_t startAddres_p);


    /**
     * @brief Set COM output scan direction (flip the screen vertically).
     *
     * @param scanDirection_p Normal or remapped.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetComOutputScanDirection(ComOutputScanDirection scanDirection_p);

    /**
     * @brief Set display vertical offset.
     *
     * @param verticalShift_p Offset value (0–63).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetDisplayOffset(uint8_t verticalShift_p);

    /**
     * @brief Set clock divide ratio and oscillator frequency.
     *
     * @param divideRatio_p Clock divide ratio (0–15).
     * @param fOscillator_p Oscillator frequency (0–15).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetDisplayClockDivideRatio_OscillatorFrequency(uint8_t divideRatio_p, uint8_t fOscillator_p);

    /**
     * @brief Set color and power mode.
     *
     * @param colorMode_p Monochrome or area color.
     * @param powerMode_p Normal or low power.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetColorAndPowerMode(ColorMode colorMode_p, PowerMode powerMode_p);

    /**
     * @brief Set precharge the duration of the pre-charge period. The interval is counted in number of
     * DCLK, where RESET equals 2 DCLKs.
     *
     * @param phase1_p Phase 1 period (1–15).
     * @param phase2_p Phase 2 period (1–15).
     * @return HAL status.
     */
	HAL_StatusTypeDef SetPrechargePeriod(uint8_t phase1_p, uint8_t phase2_p);

    /**
     * @brief Set COM pin hardware configuration.
     *
     * @param pinConfig_p Sequential or alternative configuration.
     * @param remapEnable_p Enable/disable COM remap.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetCOMPinsHWConfig(COMPinConfig pinConfig_p, EnableCOMRemap remapEnable_p);

    /**
     * @brief Adjust the VCOMH regulator output..
     *
     * Defines the output voltage level for logic 1.
     *
     * @param vcomhDeselectLevel_p Deselect level option.
     * @return HAL status.
     */
	HAL_StatusTypeDef SetVcomhDeselectLevel(VcomhDeselectLevel vcomhDeselectLevel_p);

    /**
     * @brief No Operation command.
     *
     * Command is ignored by the display controller.
     *
     * @return HAL status.
     */
	HAL_StatusTypeDef NOP();

    /**
     * @brief Exit Read-Modify-Write mode.
     *
     * @return HAL status.
     */
	HAL_StatusTypeDef ExitReadModifyWrite();

	//ToBeImplemented for color displays
	HAL_StatusTypeDef SetBankColorOfBANK1toBANK16(); //returnError: unimplemented
	HAL_StatusTypeDef SetBankColorOfBANK17toBANK32(); //returnError: unimplemented


	//Graphic acceleration commands to be implemented as needed
};


#endif /* MODULES_SSD1305_SSD1305_HPP_ */
