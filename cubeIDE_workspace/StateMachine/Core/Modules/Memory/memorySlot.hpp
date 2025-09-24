/*
 * memory.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_MEMORY_MEMORYSLOT_HPP_
#define MODULES_MEMORY_MEMORYSLOT_HPP_

#include <stdint.h>


enum axes
{
	x,
	y,
	z
};

class MemorySlot
{
private:
	axes fixedAx;
	axes trackedAx;
public:
	uint8_t number;
	uint16_t setDegree;

	MemorySlot(uint8_t number, uint16_t setDegree, axes fixedAx, axes trackedAx);

	bool setFixedAx(axes fixedAx_p);
	bool setTrackedAx(axes trackedAx_p);
	axes getFixedAx();
	axes getTrackedAx();

};

#endif /* MODULES_MEMORY_MEMORYSLOT_HPP_ */
