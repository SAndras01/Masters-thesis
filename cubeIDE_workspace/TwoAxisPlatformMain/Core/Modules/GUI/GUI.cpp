/*
 * GUI.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "GUI.hpp"

void DrawGUI(	SSD1305* display, MemorySlot memSlot,
		float refX, float refY, float refZ,
		bool highlightMem, bool highlightFixed, bool highlightTracked)
{
	//MEM section -> x = 0..21
	display->SetCursor(0, LINE_1_Y);
	display->WriteString("MEM", Font_7x10, White);

	DisplayMemslot(display, memSlot.number, highlightMem);

	DrawYline(display, 23, White);

	//Fixed, Tracked, Angle -> x = 22...78
	display->SetCursor(25, LINE_1_Y);
	display->WriteString("FixAx:", Font_7x10, White);
	display->SetCursor(25, LINE_2_Y);
	display->WriteString("Track:", Font_7x10, White);
	display->SetCursor(25, LINE_3_Y);
	display->WriteString("Deg:", Font_7x10, White);

	DisplayFixedAx(display, memSlot.getFixedAx(), highlightFixed);
	DisplayTrackedAx(display, memSlot.getTrackedAx(), highlightTracked);
	DisplaySetAngle(display, memSlot.getSetDegree());

	DrawYline(display, 76, White);

	//REF section -> x = 78...
	display->SetCursor(78, LINE_1_Y);
	display->WriteString("rx", Font_7x10, White);
	display->SetCursor(78, LINE_2_Y);
	display->WriteString("ry", Font_7x10, White);
	display->SetCursor(78, LINE_3_Y);
	display->WriteString("rz", Font_7x10, White);

	DisplayRefDegs(display, refX, refY, refZ);

	//Put all to display
	display->WriteBitmapToScreen();
}

void DrawYline(SSD1305* display, uint8_t x, SSD1305_COLOR color)
{
	for(uint8_t i = 0; i < display->GetHeight(); i++)
	{
		display->DrawPixel(x, i, color);
	}
}

void DisplayMemslot(SSD1305* display, uint8_t memslot, bool highlight)
{
	SSD1305_COLOR color = (highlight) ? Black : White;

	char memslotDigit = memslot + '0';
	display->SetCursor(5, 12);
	display->WriteChar(memslotDigit, Font_11x18, color);
}

void DisplayFixedAx(SSD1305* display, axes fixedax, bool highlight)
{
	char axesChar;
	switch (fixedax) {
		case x:
			axesChar = 'x';
			break;
		case y:
			axesChar = 'y';
			break;
		case z:
			axesChar = 'z';
			break;
		default:
			break;
	}

	display->SetCursor(67, LINE_1_Y);
	SSD1305_COLOR color = (highlight) ? Black : White;
	display->WriteChar(axesChar, Font_7x10, color);

}

void DisplayTrackedAx(SSD1305* display, axes trackedax, bool highlight)
{
	char axesChar;
	switch (trackedax) {
		case x:
			axesChar = 'x';
			break;
		case y:
			axesChar = 'y';
			break;
		case z:
			axesChar = 'z';
			break;
		default:
			break;
	}

	display->SetCursor(67, LINE_2_Y);
	SSD1305_COLOR color = (highlight) ? Black : White;
	display->WriteChar(axesChar, Font_7x10, color);
}

void DisplaySetAngle(SSD1305* display, uint16_t setdeg, int selectedDigit)
{
	char digits[3];

    digits[0] = ((setdeg/100)%10) + '0';
    digits[1] = ((setdeg/10)%10) + '0';
    digits[2] = (setdeg%10) + '0';

    FontDef font = Font_7x10;
	for(int i = 0; i<3; i++)
	{
	  display->SetCursor(53 + i*font.FontWidth, LINE_3_Y);
	  if(i == selectedDigit)
	  {
		  display->WriteChar(digits[i], font, Black);
	  }
	  else
	  {
		  display->WriteChar(digits[i], font, White);
	  }
	}
}

void DisplaySetAngle(SSD1305* display, uint8_t* digits, int selectedDigit)
{
    FontDef font = Font_7x10;
	for(int i = 0; i<3; i++)
	{
	  display->SetCursor(53 + i*font.FontWidth, LINE_3_Y);
	  if(i == selectedDigit)
	  {
		  display->WriteChar(digits[i] + '0', font, Black);
	  }
	  else
	  {
		  display->WriteChar(digits[i] + '0', font, White);
	  }
	}
}

void DisplayRefDegs(SSD1305* display, float refX, float refY, float refZ)
{
	char refDegStr[6];
	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refX);
	display->SetCursor(93, LINE_1_Y);
	display->WriteString(refDegStr, Font_7x10, White);

	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refY);
	display->SetCursor(93, LINE_2_Y);
	display->WriteString(refDegStr, Font_7x10, White);

	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refZ);
	display->SetCursor(93, LINE_3_Y);
	display->WriteString(refDegStr, Font_7x10, White);
}
