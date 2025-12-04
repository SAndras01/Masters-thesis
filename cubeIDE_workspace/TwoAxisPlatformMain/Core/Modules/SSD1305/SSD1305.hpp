/**
 * @file SSD1305.hpp
 * @brief SSD1305 OLED display driver interface.
 *
 * This file declares the SSD1305 OLED display driver class, command definitions,
 * enumerations, and public API for controlling an SSD1305-based OLED display
 * via I2C using STM32 HAL.
 *
 * Features:
 * - Display initialization and configuration
 * - Framebuffer-based graphics rendering
 * - Text rendering using external font tables
 * - Direct access to SSD1305 controller commands
 *
 * @note
 * Portions of the drawing and text rendering logic are adapted from the
 * SSD1306 STM32 HAL library by Olivier Van den Eede (ovde.be),
 * used under the MIT License.
 *
 * Original repository:
 * https://github.com/4ilo/ssd1306-stm32HAL
 *
 * SSD1305 Datasheet:
 * https://www.solomon-systech.com/en/product/ssd1305/
 *
 * @author Sásdi András
 * @date 2025-09-02
 */


#ifndef MODULES_SSD1305_SSD1305_HPP_
#define MODULES_SSD1305_SSD1305_HPP_

#include <stdint.h>
#include "fonts.h"
#include "test_bitmaps.hpp"
#include "main.h"

/// @defgroup SSD1305_Constants SSD1305 Constants
/// @{

#define DISPLAY_WIDTH   128 /**< Display width in pixels */
#define DISPLAY_HEIGHT  32  /**< Display height in pixels */

#define COMMAND_ADDRESS 0x00 /**< I2C command address */
#define DATA_ADDRESS    0x40 /**< I2C data address */

/// @}
/**
 * @defgroup SSD1305_Fundamental_Commands Fundamental Commands
 * @brief Core command set of the SSD1305 OLED controller.
 *
 * These commands configure memory addressing, contrast, display mode,
 * scan direction, power settings and basic display behavior.
 *
 * Refer to SSD1305 datasheet, section "Command Table".
 * @{
 */

/** @brief Set lower nibble of column start address (00h–0Fh). */
#define SSD1305_SET_LOWER_COLUMN        0x00

/** @brief Set higher nibble of column start address (10h–1Fh). */
#define SSD1305_SET_HIGHER_COLUMN       0x10

/**
 * @brief Set memory addressing mode.
 *
 * Followed by one of:
 * - SSD1305_ADDRMODE_HORIZONTAL
 * - SSD1305_ADDRMODE_VERTICAL
 * - SSD1305_ADDRMODE_PAGE
 */
#define SSD1305_MEMORY_ADDR_MODE        0x20

/** @brief Horizontal addressing mode. */
#define SSD1305_ADDRMODE_HORIZONTAL     0b00

/** @brief Vertical addressing mode. */
#define SSD1305_ADDRMODE_VERTICAL       0b01

/** @brief Page addressing mode. */
#define SSD1305_ADDRMODE_PAGE           0b10

/** @brief Set column address range. */
#define SSD1305_SET_COLUMN_ADDR         0x21

/** @brief Set page address range. */
#define SSD1305_SET_PAGE_ADDR           0x22

/**
 * @brief Set display start line (40h–7Fh).
 *
 * Maps RAM line 0 to display line N.
 */
#define SSD1305_SET_START_LINE          0x40

/** @brief Set contrast control register. */
#define SSD1305_SET_CONTRAST            0x81

/**
 * @brief Set brightness for area color mode.
 *
 * Affects alternate color banks when color mode is enabled.
 */
#define SSD1305_SET_BRIGHTNESS          0x82

/** @brief Set OLED lookup table (LUT). */
#define SSD1305_SET_LUT                 0x91

/** @brief Set area color bank 1. */
#define SSD1305_SET_BANK_COLOR1         0x92

/** @brief Set area color bank 2. */
#define SSD1305_SET_BANK_COLOR2         0x93

/**
 * @brief Segment remap command.
 *
 * Controls left-right mirroring of the display.
 */
#define SSD1305_SEG_REMAP               0xA0

/**
 * @brief Entire display ON.
 *
 * Forces all pixels ON regardless of RAM content.
 */
#define SSD1305_ENTIRE_DISPLAY_ON       0xA4

/**
 * @brief Set normal or inverse display mode.
 *
 * - Normal: RAM = pixel ON
 * - Inverse: RAM = pixel OFF
 */
#define SSD1305_SET_NORMAL_INVERSE      0xA6

/**
 * @brief Set multiplex ratio.
 *
 * Value range depends on panel height.
 */
#define SSD1305_SET_MULTIPLEX_RATIO     0xA8

/**
 * @brief Enable dim mode with reduced brightness.
 */
#define SSD1305_DIM_MODE                0xAB

/**
 * @brief Master configuration command.
 *
 * Enables/disables internal charge pump settings.
 */
#define SSD1305_MASTER_CONFIG           0xAD

/**
 * @brief Display ON/OFF control.
 *
 * OFF enters sleep mode, ON resumes normal operation.
 */
#define SSD1305_SET_DISPLAY_ON_OFF      0xAC

/**
 * @brief Set page start address (B0h–B7h).
 */
#define SSD1305_SET_PAGE_START          0xB0

/**
 * @brief Set COM output scan direction normal.
 */
#define SSD1305_COM_SCAN_INC            0xC0

/**
 * @brief Set COM output scan direction remapped.
 */
#define SSD1305_COM_SCAN_DEC            0xC8

/** @brief Set vertical display offset. */
#define SSD1305_SET_DISPLAY_OFFSET      0xD3

/**
 * @brief Set display clock divide ratio and oscillator frequency.
 */
#define SSD1305_SET_CLOCK_DIV           0xD5

/**
 * @brief Set color mode and power mode.
 */
#define SSD1305_SET_COLOR_n_POWER_MODE  0xD8

/**
 * @brief Set pre-charge period.
 */
#define SSD1305_SET_PRECHARGE_PERIOD    0xD9

/**
 * @brief Set COM pins hardware configuration.
 */
#define SSD1305_SET_COM_PINS_HW_CNFG    0xDA

/**
 * @brief Set VCOMH deselect level.
 */
#define SSD1305_SET_VCOMH_DESELECT      0xDB

/**
 * @brief Enter Read-Modify-Write mode.
 *
 * Enables partial RAM modification without resetting column address.
 */
#define SSD1305_READ_MODIFY_WRITE       0xE0

/** @brief No operation command. */
#define SSD1305_NOP                     0xE3

/**
 * @brief Exit Read-Modify-Write mode.
 */
#define SSD1305_EXIT_RMW                0xEE

/** @} */



/**
 * @defgroup SSD1305_Scrolling_Commands Scrolling Commands
 * @brief Hardware scrolling command set.
 *
 * Enables horizontal and vertical scrolling using internal SSD1305 timing logic.
 * @{
 */

/** @brief Continuous horizontal scroll to the right. */
#define SSD1305_SCROLL_RIGHT            0x26

/** @brief Continuous horizontal scroll to the left. */
#define SSD1305_SCROLL_LEFT             0x27

/**
 * @brief Continuous vertical and right horizontal scroll.
 */
#define SSD1305_SCROLL_VERT_RIGHT       0x29

/**
 * @brief Continuous vertical and left horizontal scroll.
 */
#define SSD1305_SCROLL_VERT_LEFT        0x2A

/** @brief Deactivate scrolling. */
#define SSD1305_DEACTIVATE_SCROLL       0x2E

/** @brief Activate scrolling. */
#define SSD1305_ACTIVATE_SCROLL         0x2F

/**
 * @brief Set vertical scroll area.
 *
 * Defines fixed and scrollable rows.
 */
#define SSD1305_SET_SCROLL_AREA         0xA3

/** @} */

/**
 * @enum SSD1305_COLOR
 * @brief Pixel color definition.
 */
enum SSD1305_COLOR{
    Black = 0x00,   // Black color, no pixel
    White = 0x01,   // Pixel is set. Color depends on LCD
};

 /**
  * @enum MemoryAddressingMode
  * @brief GDDRAM addressing modes.
  */
enum MemoryAddressingMode
{
	horizontal = SSD1305_ADDRMODE_HORIZONTAL,
	vertical = SSD1305_ADDRMODE_VERTICAL,
	page = SSD1305_ADDRMODE_PAGE
};

/**
 * @enum SegmentRemap
 * @brief Segment remapping configuration.
 */
enum SegmentRemap
{
	columnAddress0toSEG0 = 0b0,
	columnAddress131toSEG0 = 0b1
};

/**
 * @enum DisplayONMode
 * @brief Entire display ON control.
 */
enum DisplayONMode
{
	ResumeToRAMContent = 0xA4,
	IgnoreRAMContent = 0xA5
};


/**
 * @enum DisplayMode
 * @brief Display power mode.
 */
enum DisplayMode
{
	DisplayOnDimMode = 0xAC,
	DisplayOffSleepMode = 0xAE,
	DisplayOnNormalMode = 0xAF
};

/**
 * @enum DisplayInverseMode
 * @brief Normal or inverse display mode.
 */
enum DisplayInverseMode
{
	normal = 0xA6,
	inverse = 0xA7
};

/**
 * @enum ComOutputScanDirection
 * @brief COM scan direction.
 */
enum ComOutputScanDirection
{
	normalMode = 0xC0,
	remappedMode = 0xC8
};

/**
 * @enum ColorMode
 * @brief Color operation mode.
 */
enum ColorMode
{
	monochromeMode = 	0b00000000,
	colorMode = 0b00110000
};

/**
 * @enum PowerMode
 * @brief Display power mode.
 */
enum PowerMode
{
	normalPowerMode = 0b0000,
	lowPowerMode= 0b0101
};

/**
 * @enum COMPinConfig
 * @brief COM pin hardware configuration.
 */
enum COMPinConfig
{
	sequential = 0b00000010,
	alternative= 0b00010010
};

/**
 * @enum EnableCOMRemap
 * @brief Enable or disable COM remapping.
 */
enum EnableCOMRemap
{
	enable = 0b00100010,
	disable= 0b00000010
};

/**
 * @enum VcomhDeselectLevel
 * @brief VCOMH deselect voltage levels.
 */
enum VcomhDeselectLevel
{
	VCCx0p43 = 0x0,
	VCCx0p77 = 0x34,
	VCCx0p83 = 0x3C
};

/**
 * @class SSD1305
 * @brief SSD1305 OLED display driver.
 *
 * Provides a high-level interface for controlling an SSD1305 OLED display
 * via I2C using STM32 HAL.
 *
 * The driver uses an internal framebuffer which can be modified using
 * drawing and text rendering functions, then transferred to the display.
 *
 * @note
 * - Blocking I2C communication
 * - Not thread-safe
 *
 * Typical usage:
 * @code
 * SSD1305 oled(&hi2c1, 0x3C, 128, 32);
 * oled.Init();
 * oled.Fill(Black);
 * oled.SetCursor(0, 0);
 * oled.WriteString("Hello", Font_7x10, White);
 * oled.WriteBitmapToScreen();
 * @endcode
 */
class SSD1305
{
private:
    /**
     * @brief Pointer to the HAL I2C handle used for communication.
     */
	I2C_HandleTypeDef* hi2c;

    /**
     * @brief 7-bit I2C slave address of the SSD1305.
     */
	uint8_t address;

    /**
     * @brief Display width in pixels.
     */
	uint8_t width;

    /**
     * @brief Display height in pixels.
     */
	uint8_t height;

    /**
     * @brief Current cursor X position (column).
     */
    uint16_t currentX;

    /**
     * @brief Current cursor Y position (page/row).
     */
    uint16_t currentY;

    /**
     * @brief Temporary command buffer used for I2C command transfers.
     *
     * First byte typically contains control byte (0x00),
     * followed by up to 4 command bytes.
     */
    uint8_t commandBuffer[5];

    /**
     * @brief Local framebuffer storing display bitmap data.
     *
     * Each bit represents one pixel. Organized in pages
     * (8 vertical pixels per byte).
     *
     * Size = width × height / 8 bytes.
     */
    uint8_t bitmapBuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

    /**
     * @brief Vertical offset applied to display start line.
     *
     * Used for vertical shifting or panel alignment.
     */
    uint8_t v_offset;

    /**
     * @brief Send prepared command buffer to the display controller.
     *
     * @param commandSize Number of valid bytes in commandBuffer.
     * @return HAL status.
     */
    HAL_StatusTypeDef SendCommand(uint8_t commandSize);

public:
    /**
     * @brief Construct a new SSD1305 object
     *
     * @param hi2c_p Pointer to the HAL I2C handle
     * @param address_p I2C address of the display (7-bit)
     * @param width_p Display width in pixels
     * @param height_p Display height in pixels
     */
	SSD1305(	I2C_HandleTypeDef* hi2c_p,
				uint8_t address_p,
				uint8_t width_p,
				uint8_t height_p);

	/**
	 * @brief Initialise the display with the given orientation.
	 *
	 * @param orientation, positive or negative integer.
	 * @return true if all instructions got successfully sent.
	 */
	bool Init(int8_t orientation = 1);

    /**
     * @brief Write the internal bitmap buffer to the display
     *
     * Transfers the complete frame buffer to the display RAM.
     *
     * @retval HAL status
     */
	HAL_StatusTypeDef WriteBitmapToScreen();


    /**
     * @brief Write an external bitmap buffer to the display
     *
     * @param bitmap Pointer to bitmap data
     * @param size Size of bitmap data in bytes
     *
     * @retval HAL status
     */
	HAL_StatusTypeDef WriteBitmapToScreen(uint8_t* bitmap, size_t size);

    /**
     * @brief Fill internal bitmap buffer with a single color
     *
     * @param color_p Fill color (Black or White)
     */
	void FillBitmapBuffer(SSD1305_COLOR color_p);

    /**
     * @brief Fill the entire display with a single color
     *
     * Writes directly to display memory using read-modify-write mode.
     *
     * @param color_p Fill color (Black or White)
     *
     * @retval HAL status
     */
	HAL_StatusTypeDef Fill(SSD1305_COLOR color_p);

    /**
     * @brief Draw a single pixel into the frame buffer
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param color_p Pixel color
     *
     * @retval true  Pixel drawn successfully
     * @retval false Coordinates out of range
     */
	bool DrawPixel(uint8_t x, uint8_t y, SSD1305_COLOR color_p);

    /**
     * @brief Write a single character to the frame buffer
     *
     * The cursor position is automatically advanced.
     *
     * @param ch Character to write
     * @param Font Font definition structure
     * @param color Text color
     *
     * @return Written character on success, 0 otherwise
     */
	char WriteChar(char ch, FontDef Font, SSD1305_COLOR color);

    /**
     * @brief Write a null-terminated string to the frame buffer
     *
     * @param str Pointer to string
     * @param Font Font definition
     * @param color Text color
     *
     * @retval true  String written successfully
     * @retval false Writing failed
     */
	bool WriteString(const char* str, FontDef Font, SSD1305_COLOR color);

    /**
     * @brief Set the text cursor position
     *
     * @param x X coordinate in pixels
     * @param y Y coordinate in pixels
     */
	void SetCursor(uint8_t x, uint8_t y);


    /**
     * @brief Get display height in pixels
     * @return Display height
     */
	uint8_t GetHeight();

    /**
     * @brief Get display width in pixels
     * @return Display width
     */
	uint8_t GetWidth();

    /* ========================= */
    /*  Low-level SSD1305 API    */
    /* ========================= */

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
	/// @ todo implement color bank functionality
	HAL_StatusTypeDef SetBankColorOfBANK1toBANK16();  ///< @return HAL_ERROR (not implemented)
	HAL_StatusTypeDef SetBankColorOfBANK17toBANK32();  ///< @return HAL_ERROR (not implemented)


	//Graphic acceleration commands to be implemented as needed
};


#endif /* MODULES_SSD1305_SSD1305_HPP_ */
