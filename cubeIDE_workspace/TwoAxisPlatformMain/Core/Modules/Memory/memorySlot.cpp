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

MemorySlot::MemorySlot()
{
	this->number = 0;
	this->setDegree = 0;

	this->setFixedAx(x);
	this->setTrackedAx(y);
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

bool MemorySlot::setFixedAx(int axesCodedAsNum)
{
	switch (axesCodedAsNum) {
		case 1:
			return setFixedAx(x);
			break;
		case 2:
			return setFixedAx(y);
			break;
		default:
			return setFixedAx(x);
			break;
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

bool MemorySlot::setTrackedAx(int axesCodedAsNum)
{
	switch (axesCodedAsNum) {
		case 1:
			return setTrackedAx(x);
			break;
		case 2:
			return setTrackedAx(y);
			break;
		case 3:
			return setTrackedAx(z);
			break;
		default:
			return setTrackedAx(y);
			break;
	}
}


bool MemorySlot::setSetDegree(int setDegree_p)
{
	if(setDegree_p < 0)
	{
		setDegree = 0;
		return false;
	}
	if(setDegree_p > 360)
	{
		setDegree = 360;
		return false;
	}
	setDegree = setDegree_p;
	return true;
}

uint16_t MemorySlot::getSetDegree(){return setDegree;}

axes MemorySlot::getFixedAx(){return fixedAx;}
axes MemorySlot::getTrackedAx(){return trackedAx;}

uint8_t ax2int(axes ax)
{
	switch (ax) {
		case x:
			return 1;
			break;
		case y:
			return 2;
			break;
		case z:
			return 3;
			break;
		default:
			return 0;
			break;
	}
}

uint8_t MemorySlot::getFixedAxAsInt()
{
	return ax2int(fixedAx);
}

uint8_t MemorySlot::getTrackedAxAsInt()
{
	return ax2int(trackedAx);
}

















