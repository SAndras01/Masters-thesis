/*
 * GUI.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_GUI_GUI_HPP_
#define MODULES_GUI_GUI_HPP_

#include "SSD1305.hpp"
#include "memory.hpp"
#include <stdio.h>

#define LINE_1_Y 0
#define LINE_2_Y 11
#define LINE_3_Y 22



void DrawGUI(SSD1305* display, MemorySlot memslot, float refX, float refY, float refZ);
void DrawYline(SSD1305* display, uint8_t x, SSD1305_COLOR color);
void DisplayMemslot(SSD1305* display, uint8_t memslot);
void DisplayFixedAx(SSD1305* display, axes fixedax);
void DisplayTrackedAx(SSD1305* display, axes trackedax);
void DisplaySetAngle(SSD1305* display, uint16_t setdeg, int selectedDigit = -1);
void DisplaySetAngle(SSD1305* display, uint8_t* digits, int selectedDigit = -1);
void DisplayRefDegs(SSD1305* display, float refX, float refY, float refZ);



#endif /* MODULES_GUI_GUI_HPP_ */
