/*
 * memory.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include <memorySlot.hpp>

MemorySlot::MemorySlot(uint8_t number, uint16_t setDegree, axes fixedAx, axes trackedAx)
{
	this->number = number;
	this->setDegree = setDegree;

	this->setFixedAx(fixedAx);
	this->setTrackedAx(trackedAx);
}

bool MemorySlot::setFixedAx(axes fixedAx_p)
{
	//we can simply put the previous fixed to the tracked without any hesitation as any axes can be tracked
	if(fixedAx_p == trackedAx)
	{
		trackedAx = fixedAx;
		fixedAx = fixedAx_p;
		return false;
	}
	if(fixedAx_p == z)
	{
		return false;
	}
	else
	{
		fixedAx = fixedAx_p;
		return true;
	}
}


bool MemorySlot::setTrackedAx(axes trackedAx_p)
{
	if(trackedAx_p == fixedAx)
	{
		switch (trackedAx_p) {
			case x:
				fixedAx = y;
				break;
			case y:
				fixedAx = x;
				break;
			default: //if tracked = fixed, then tracked cant be Z as fixed can never be z
				break;
		}
		trackedAx = trackedAx_p;
		return false;
	}
	else
	{
		trackedAx = trackedAx_p;
		return true;
	}
}
axes MemorySlot::getFixedAx(){return fixedAx;}
axes MemorySlot::getTrackedAx(){return trackedAx;}
