/*
 * state_machine.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "state_machine.hpp"

StateMachine::StateMachine(State* initial)
{
	this->current = initial;
}

void StateMachine::changeState(State* next)
{
	if(current)
	{
		current->onExit(this);
	}

	current = next;

	if(current)
	{
		current->onEnter(this);
	}
}

void StateMachine::run()
{
	if(current)
	{
		current->run(this);
	}
}

mainMachine::mainMachine(State* initial, SSD1305* displayHandle, Accelerometer* referenceAccel):StateMachine(initial)
{
	this->displayHandle = displayHandle;
	this->referenceAccel = referenceAccel;
	changeState(initial);
}

StateSetFixTrackDeg::StateSetFixTrackDeg(MemorySlot initialMemorySlot)
{
	this->currentMemorySlot = initialMemorySlot;
}

void StateSetFixTrackDeg::onEnter(StateMachine* master)
{
    mainMachine* mm = static_cast<mainMachine*>(master);
    float* refAngles = mm->referenceAccel->getAngles();
	DrawGUI(mm->displayHandle, currentMemorySlot, refAngles[0], refAngles[1], refAngles[2]);
}

void StateSetFixTrackDeg::run(StateMachine* master)
{
    mainMachine* mm = static_cast<mainMachine*>(master);
    float* refAngles = mm->referenceAccel->getAngles();

	if(adcValue2Digit() != 10)
	{
	  currentNum = adcValue2Digit();
	}

	switch (currentDigitState)
	{
		case setDigit1:
			numberDigits[0] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit2;
				currentNum = numberDigits[1];
			}
			break;
		case setDigit2:
			numberDigits[1] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit3;
				currentNum = numberDigits[2];
			}
			break;
		case setDigit3:
			numberDigits[2] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit1;
				currentNum = numberDigits[0];
			}
			break;
		default:
			break;
	}

	uint16_t numberFromDigits = 0;
	for (uint8_t i = 0; i < 3; i++)
		numberFromDigits = 10 * numberFromDigits + numberDigits[i];

	currentMemorySlot.setDegree = numberFromDigits;

	DisplaySetAngle(mm->displayHandle, numberFromDigits, currentDigitState);

	DisplayRefDegs(mm->displayHandle, refAngles[0], refAngles[1], refAngles[2]);

	mm->displayHandle->WriteBitmapToScreen();
}

void StateSetFixTrackDeg::onExit(StateMachine* master)
{

}




