/*
 * memory.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_MEMORY_MEMORY_HPP_
#define MODULES_MEMORY_MEMORY_HPP_

#include <stdint.h>


enum axes
{
	x,
	y,
	z
};

struct MemorySlot
{
	uint8_t number;
	axes fixAx;
	axes trackedAx;
	uint16_t setDegree;
};

#endif /* MODULES_MEMORY_MEMORY_HPP_ */
