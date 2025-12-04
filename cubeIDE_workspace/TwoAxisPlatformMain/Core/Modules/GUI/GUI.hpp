/**
 * @file GUI.hpp
 * @brief Graphical User Interface helper functions for SSD1305 OLED display.
 *
 * This module provides utility functions to draw a simple GUI layout on the
 * SSD1305 display, including memory slots, fixed/tracked axes, set angles,
 * and reference coordinates.
 *
 * @author Sásdi András
 * @date 2025-09-17
 */

#ifndef MODULES_GUI_GUI_HPP_
#define MODULES_GUI_GUI_HPP_

#include <memorySlot.hpp>
#include "SSD1305.hpp"
#include <stdio.h>

/** @brief Y-coordinate of line 1 on the display */
#define LINE_1_Y 0
/** @brief Y-coordinate of line 2 on the display */
#define LINE_2_Y 11
/** @brief Y-coordinate of line 3 on the display */
#define LINE_3_Y 22

/**
 * @brief Draw the main GUI on the display.
 *
 * Clears the screen and draws all sections: memory slot, fixed/tracked axes,
 * set angle, and reference coordinates.
 *
 * @param display Pointer to SSD1305 instance.
 * @param memSlot MemorySlot structure containing current memory slot and settings.
 * @param refX Reference X coordinate in degrees.
 * @param refY Reference Y coordinate in degrees.
 * @param refZ Reference Z coordinate in degrees.
 * @param highlightMem Highlight the memory slot section if true.
 * @param highlightFixed Highlight the fixed axis if true.
 * @param highlightTracked Highlight the tracked axis if true.
 */
void DrawGUI(SSD1305* display, MemorySlot memSlot,
             float refX, float refY, float refZ,
             bool highlightMem = false, bool highlightFixed = false, bool highlightTracked = false);

/**
 * @brief Draw a vertical line at given x position.
 *
 * @param display Pointer to SSD1305 instance.
 * @param x X-coordinate of the vertical line.
 * @param color Color of the line (Black or White).
 */
void DrawYline(SSD1305* display, uint8_t x, SSD1305_COLOR color);

/**
 * @brief Display the memory slot number on the display.
 *
 * @param display Pointer to SSD1305 instance.
 * @param memslot Memory slot number (0–9).
 * @param highlight If true, invert color for highlighting.
 */
void DisplayMemslot(SSD1305* display, uint8_t memslot, bool highlight = false);

/**
 * @brief Display the fixed axis character (x, y, z).
 *
 * @param display Pointer to SSD1305 instance.
 * @param fixedax Axis enum value (x, y, or z).
 * @param highlight If true, invert color for highlighting.
 */
void DisplayFixedAx(SSD1305* display, axes fixedax, bool highlight = false);

/**
 * @brief Display the tracked axis character (x, y, z).
 *
 * @param display Pointer to SSD1305 instance.
 * @param trackedax Axis enum value (x, y, or z).
 * @param highlight If true, invert color for highlighting.
 */
void DisplayTrackedAx(SSD1305* display, axes trackedax, bool highlight = false);

/**
 * @brief Display a 3-digit set angle.
 *
 * @param display Pointer to SSD1305 instance.
 * @param setdeg Angle in degrees (0–999).
 * @param selectedDigit Index of digit to highlight (0–2), -1 for none.
 */
void DisplaySetAngle(SSD1305* display, uint16_t setdeg, int selectedDigit = -1);

/**
 * @brief Display set angle using pre-split digits.
 *
 * @param display Pointer to SSD1305 instance.
 * @param digits Array of 3 digits (0–9).
 * @param selectedDigit Index of digit to highlight (0–2), -1 for none.
 */
void DisplaySetAngle(SSD1305* display, uint8_t* digits, int selectedDigit = -1);

/**
 * @brief Display reference X, Y, Z angles on the display.
 *
 * @param display Pointer to SSD1305 instance.
 * @param refX Reference X coordinate in degrees.
 * @param refY Reference Y coordinate in degrees.
 * @param refZ Reference Z coordinate in degrees.
 */
void DisplayRefDegs(SSD1305* display, float refX, float refY, float refZ);

#endif /* MODULES_GUI_GUI_HPP_ */
