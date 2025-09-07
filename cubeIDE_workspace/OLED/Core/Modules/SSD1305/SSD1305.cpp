/*
 * SSD1305.cpp
 *
 *  Created on: 2025. szept. 2.
 *      Author: SNA1BP
 */

#include "SSD1305.hpp"

SSD1305::SSD1305(
		I2C_HandleTypeDef* hi2c_p,
		uint8_t address_p,
		uint8_t width_p,
		uint8_t height_p)
{
	this->hi2c = hi2c_p;
	this->address = address_p;
	this->width = width_p;
	this->height = height_p;
}

bool SSD1305::Init()
{
    uint8_t v_offset = 4;

    int status = 0;

	status += SetDisplayON_OFF(DisplayOffSleepMode);
	status += SetMultiplexRatio(height-1);
	status += SetDisplayOffset(0);
	status += SetDisplayStartLine(0);
	status += SetColorAndPowerMode(monochromeMode, normalPowerMode);
	status += SetMemoryAddressingMode(horizontal);
	status += SetSegmentReMap(columnAddress131toSEG0);
	status += SetLUT(0x3F, 0x3F, 0x3F, 0x3F);
	status += SetPrechargePeriod(13, 2);
	status += SetDisplayOffset(0);
	status += SetComOutputScanDirection(remappedMode);
	status += SetNormalInverse(normal);

    status += SetColumnAddress(v_offset, (width - 1) + v_offset);
	status += SetPageAddress(0, 3);

	status += Fill(Black);

    status += SetDisplayON_OFF(DisplayOnNormalMode);
    status += EntireDisplayON(ResumeToRAMContent);

    if (status != 0) {
        return false;
    }

    return true;
}

uint8_t SSD1305::GetHeight(){return height;}
uint8_t SSD1305::GetWidth(){return width;}

HAL_StatusTypeDef SSD1305::WriteBitmapToScreen()
{
	HAL_StatusTypeDef status;

	size_t size = sizeof(bitmapBuffer);

    status =  SetMemoryAddressingMode(horizontal);

    if (status != HAL_OK)
    {
    	return status;
    }
    else
    {
		return HAL_I2C_Mem_Write(hi2c, address<<1, DATA_ADDRESS, 1, bitmapBuffer, size, size*10);
    }
}

HAL_StatusTypeDef SSD1305::WriteBitmapToScreen(uint8_t* bitmap, size_t size)
{
	HAL_StatusTypeDef status;

    status =  SetMemoryAddressingMode(horizontal);

    if (status != HAL_OK)
    {
    	return status;
    }
    else
    {
		return HAL_I2C_Mem_Write(hi2c, address<<1, DATA_ADDRESS, 1, bitmap, size, size*10);
    }
}

HAL_StatusTypeDef SSD1305::Fill(SSD1305_COLOR color_p)
{
	HAL_StatusTypeDef status;
	status = EnterReadModifyWrite();

    if (status != HAL_OK)
    {
    	return status;
    }
    else
    {
		uint8_t data = (color_p == Black) ? 0x00 : 0xFF;

		for(int i = 0; i<(width * height) / 8; i++)
		{
			bitmapBuffer[i] = data;
			status = HAL_I2C_Mem_Write(hi2c, address<<1, DATA_ADDRESS, 1, &data, 1, 10);
		    if (status != HAL_OK)
		    {
		    	return status;
		    }
		}
    }

	status = ExitReadModifyWrite();

    if (status != HAL_OK)
    {
    	return status;
    }
	return status;
}

//this method is based on the method void ssd1306_DrawPixel
bool SSD1305::DrawPixel(uint8_t x, uint8_t y, SSD1305_COLOR color_p)
{
	if (x >= width || y >= height)
	{
		// Don't write outside the buffer
		return 0;
	}

	// Draw in the correct color
	if (color_p == White)
	{
		bitmapBuffer[x + (y / 8) * width] |= 1 << (y % 8);
	}
	else
	{
		bitmapBuffer[x + (y / 8) * width] &= ~(1 << (y % 8));
	}

	return 1;
}

//this method is based on the method ssd1306_WriteChar
char SSD1305::WriteChar(char ch, FontDef Font, SSD1305_COLOR color)
{
    uint32_t i, b, j;

    // Check remaining space on current line
    if (width < (currentX + Font.FontWidth) ||
        height < (currentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Translate font to screenbuffer
    for (i = 0; i < Font.FontHeight; i++)
    {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for (j = 0; j < Font.FontWidth; j++)
        {
            if ((b << j) & 0x8000)
            {
            	DrawPixel(currentX + j, (currentY + i), color);
            }
            else
            {
            	DrawPixel(currentX + j, (currentY + i), (SSD1305_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    currentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}

//this method is based on the method ssd1306_WriteString
bool SSD1305::WriteString(const char* str, FontDef Font, SSD1305_COLOR color)
{
    // Write until null-byte
    while (*str)
    {
        if (WriteChar(*str, Font, color) != *str)
        {
            // Char could not be written
            return 0;
        }

        // Next char
        str++;
    }

    // Everything ok
    return 1;
}

void SSD1305::SetCursor(uint8_t x, uint8_t y)
{
	currentX = x;
	currentY = y;
}

/////////////////////////////////////
////REALISE THE METHODS OF THE IC////
/////////////////////////////////////


HAL_StatusTypeDef SSD1305::SendCommand(uint8_t commandSize)
{
	return HAL_I2C_Mem_Write(hi2c, address<<1, COMMAND_ADDRESS, 1, commandBuffer, commandSize, 10);
}

HAL_StatusTypeDef SSD1305::SetLowerColumnStartAddress(uint8_t startAddress_p)
{
	if(startAddress_p > 0x0F)
	{
		startAddress_p = 0x0F;
	}
	commandBuffer[0] = SSD1305_SET_LOWER_COLUMN | startAddress_p;
	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetHigherColumnStartAddress(uint8_t startAddress_p)
{
	if(startAddress_p > 0x0F)
	{
		startAddress_p = 0x0F;
	}
	commandBuffer[0] = SSD1305_SET_HIGHER_COLUMN | startAddress_p;
	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetMemoryAddressingMode(MemoryAddressingMode mode_p)
{
	commandBuffer[0] = SSD1305_MEMORY_ADDR_MODE;
	commandBuffer[1] = mode_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetColumnAddress(uint8_t startAddres_p, uint8_t endAddres_p)
{
	if(startAddres_p > 131)
	{
		startAddres_p = 130;
	}
	if(endAddres_p > 131)
	{
		endAddres_p =  131;
	}

	commandBuffer[0] = SSD1305_SET_COLUMN_ADDR;
	commandBuffer[1] = startAddres_p;
	commandBuffer[2] = endAddres_p;

	return SendCommand(3);
}

HAL_StatusTypeDef SSD1305::SetPageAddress(uint8_t startAddres_p, uint8_t endAddres_p)
{
	if(startAddres_p > 7)
	{
		startAddres_p = 7;
	}
	if(endAddres_p > 7)
	{
		endAddres_p =  7;
	}

	commandBuffer[0] = SSD1305_SET_PAGE_ADDR;
	commandBuffer[1] = startAddres_p;
	commandBuffer[2] = endAddres_p;

	return SendCommand(3);
}

HAL_StatusTypeDef SSD1305::SetDisplayStartLine(uint8_t line_p)
{
	if(line_p > 63)
	{
		line_p = 63;
	}

	commandBuffer[0] = SSD1305_SET_START_LINE | line_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetContrastControllBANK0(uint8_t contrast_p)
{
	commandBuffer[0] = SSD1305_SET_CONTRAST;
	commandBuffer[1] = contrast_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetBrightnessForAreaColorBanks(uint8_t brightness_p)
{
	commandBuffer[0] = SSD1305_SET_BRIGHTNESS;
	commandBuffer[1] = brightness_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetLUT(uint8_t LUT_BANK0_p, uint8_t LUT_ColorA_p, uint8_t LUT_ColorB_p, uint8_t LUT_ColorC_p)
{
	if(LUT_BANK0_p < 32){
		LUT_BANK0_p = 32;
	}
	if(LUT_BANK0_p > 63){
		LUT_BANK0_p = 63;
	}
	//--//
	if(LUT_ColorA_p < 32){
		LUT_ColorA_p = 32;
	}
	if(LUT_ColorA_p > 63){
		LUT_ColorA_p = 63;
	}
	//--//
	if(LUT_ColorB_p < 32){
		LUT_ColorB_p = 32;
	}
	if(LUT_ColorB_p > 63){
		LUT_ColorB_p = 63;
	}
	//--//
	if(LUT_ColorC_p < 32){
		LUT_ColorC_p = 32;
	}
	if(LUT_ColorC_p > 63){
		LUT_ColorC_p = 63;
	}

	commandBuffer[0] = SSD1305_SET_LUT;
	commandBuffer[1] = LUT_BANK0_p;
	commandBuffer[2] = LUT_ColorA_p;
	commandBuffer[3] = LUT_ColorB_p;
	commandBuffer[4] = LUT_ColorC_p;

	return SendCommand(5);
}

HAL_StatusTypeDef SSD1305::SetSegmentReMap(SegmentRemap remap_p)
{
	commandBuffer[0] = SSD1305_SEG_REMAP | remap_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::EntireDisplayON(DisplayONMode displayONMode_p)
{
	commandBuffer[0] = displayONMode_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetNormalInverse(DisplayInverseMode inversMode_p)
{
	commandBuffer[0] = inversMode_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetMultiplexRatio(uint8_t ratio_p)
{
	if(ratio_p < 15)
	{
		ratio_p = 15;
	}

	commandBuffer[0] = 	SSD1305_SET_MULTIPLEX_RATIO;
	commandBuffer[1] = ratio_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetDimMode(uint8_t contrastBANK0_p, uint8_t brightnessForColorBank_p)
{
	commandBuffer[0] = SSD1305_DIM_MODE;
	commandBuffer[1] = 0;
	commandBuffer[2] = contrastBANK0_p;
	commandBuffer[3] = brightnessForColorBank_p;

	return SendCommand(4);
}

HAL_StatusTypeDef SSD1305::SetDisplayON_OFF(DisplayMode mode_p)
{
	commandBuffer[0] = mode_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetPageStartAddress(uint8_t startAddres_p)
{
	if(startAddres_p > 7)
	{
		startAddres_p = 7;
	}

	commandBuffer[0] = SSD1305_SET_PAGE_START | startAddres_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetComOutputScanDirection(ComOutputScanDirection scanDirection_p)
{
	commandBuffer[0] = scanDirection_p;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::SetDisplayOffset(uint8_t verticalShift_p)
{
	if (verticalShift_p > 63)
	{
		verticalShift_p = 63;
	}

	commandBuffer[0] = SSD1305_SET_DISPLAY_OFFSET;
	commandBuffer[1] = verticalShift_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetDisplayClockDivideRatio_OscillatorFrequency(uint8_t divideRatio_p, uint8_t fOscillator_p)
{
	if(divideRatio_p > 0xF)
	{
		divideRatio_p = 0xF;
	}

	if(fOscillator_p > 0xF)
	{
		fOscillator_p = 0xF;
	}

	commandBuffer[0] = SSD1305_SET_CLOCK_DIV;
	commandBuffer[1] = (fOscillator_p << 4) | divideRatio_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetColorAndPowerMode(ColorMode colorMode_p, PowerMode powerMode_p)
{
	commandBuffer[0] = SSD1305_SET_COLOR_n_POWER_MODE;
	commandBuffer[1] = (colorMode_p << 4) | powerMode_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetPrechargePeriod(uint8_t phase1_p, uint8_t phase2_p)
{
	if(phase1_p > 0xF)
	{
		phase1_p = 0xF;
	}

	if(phase2_p > 0xF)
	{
		phase2_p = 0xF;
	}

	commandBuffer[0] = SSD1305_SET_PRECHARGE_PERIOD;
	commandBuffer[1] = (phase2_p << 4) | phase1_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetCOMPinsHWConfig(COMPinConfig pinConfig_p, EnableCOMRemap remapEnable_p)
{
	commandBuffer[0] = SSD1305_SET_COM_PINS_HW_CNFG;
	commandBuffer[1] = pinConfig_p | remapEnable_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::SetVcomhDeselectLevel(VcomhDeselectLevel vcomhDeselectLevel_p)
{
	commandBuffer[0] = SSD1305_SET_VCOMH_DESELECT;
	commandBuffer[1] = vcomhDeselectLevel_p;

	return SendCommand(2);
}

HAL_StatusTypeDef SSD1305::EnterReadModifyWrite()
{
	commandBuffer[0] = SSD1305_READ_MODIFY_WRITE;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::NOP()
{
	commandBuffer[0] = SSD1305_NOP;

	return SendCommand(1);
}

HAL_StatusTypeDef SSD1305::ExitReadModifyWrite()
{
	commandBuffer[0] = SSD1305_EXIT_RMW;

	return SendCommand(1);
}
