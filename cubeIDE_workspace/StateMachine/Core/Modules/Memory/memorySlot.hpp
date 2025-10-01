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
	x = 1,
	y = 2,
	z = 3
};

class MemorySlot
{
private:
	axes fixedAx;
	axes trackedAx;
	uint16_t setDegree;
public:
	uint8_t number;

	MemorySlot(); //default constructor
	MemorySlot(uint8_t number, uint16_t setDegree, axes fixedAx, axes trackedAx);

	bool setFixedAx(axes fixedAx_p);
	bool setFixedAx(int axesCodedAsNum);
	bool setTrackedAx(axes trackedAx_p);
	bool setTrackedAx(int axesCodedAsNum);
	bool setSetDegree(int setDegree_p);

	axes getFixedAx();
	axes getTrackedAx();

	uint8_t getFixedAxAsInt();
	uint8_t getTrackedAxAsInt();

	uint16_t getSetDegree();
};

#endif /* MODULES_MEMORY_MEMORYSLOT_HPP_ */
