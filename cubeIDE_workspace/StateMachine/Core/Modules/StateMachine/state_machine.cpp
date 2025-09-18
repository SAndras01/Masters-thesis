/*
 * state_machine.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "state_machine.hpp"

StateMachine::StateMachine(State* initial, SSD1305* displayHandle, Accelerometer* referenceAccel)
{
	this->displayHandle = displayHandle;
	this->referenceAccel = referenceAccel;
	changeState(initial);
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

StateSetFixTrackDeg::StateSetFixTrackDeg(MemorySlot initialMemorySlot)
{
	this->currentMemorySlot = initialMemorySlot;
}

void StateSetFixTrackDeg::onEnter(StateMachine* master)
{
    float* refAngles = master->referenceAccel->getAngles();
	DrawGUI(master->displayHandle, currentMemorySlot, refAngles[0], refAngles[1], refAngles[2]);
	numberDigits[0] = (currentMemorySlot.setDegree/100)%10;
	numberDigits[1] = (currentMemorySlot.setDegree/10)%10;
	numberDigits[2] = currentMemorySlot.setDegree%10;

}

void StateSetFixTrackDeg::run(StateMachine* master)
{
    float* refAngles = master->referenceAccel->getAngles();

	if(adcValue2Digit() != 10) //It cant be 10 so 10 indicates no input
	{
		currentDigit = adcValue2Digit();
	}
	else
	{
		currentDigit = numberDigits[currentDigitState];
	}

	switch (currentDigitState)
	{
		case setDigit1:
			numberDigits[0] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit2;
			}
			break;
		case setDigit2:
			numberDigits[1] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit3;
			}
			break;
		case setDigit3:
			numberDigits[2] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentDigitState = setDigit1;
			}
			break;
		default:
			break;
	}

	uint16_t numberFromDigits = 0;
	for (uint8_t i = 0; i < 3; i++)
		numberFromDigits = 10 * numberFromDigits + numberDigits[i];

	currentMemorySlot.setDegree = numberFromDigits;

	DisplaySetAngle(master->displayHandle, currentMemorySlot.setDegree, currentDigitState);

	DisplayRefDegs(master->displayHandle, refAngles[0], refAngles[1], refAngles[2]);

	master->displayHandle->WriteBitmapToScreen();
}

void StateSetFixTrackDeg::onExit(StateMachine* master)
{

}




