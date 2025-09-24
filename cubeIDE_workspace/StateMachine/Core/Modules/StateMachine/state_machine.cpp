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

StateSetFixTrackDeg::StateSetFixTrackDeg(MemorySlot* initialMemorySlot)
{
	this->currentMemorySlot = initialMemorySlot;
}

void StateSetFixTrackDeg::onEnter(StateMachine* master)
{
    float* refAngles = master->referenceAccel->getAngles();
	DrawGUI(master->displayHandle, *currentMemorySlot, refAngles[0], refAngles[1], refAngles[2]);
	numberDigits[0] = (currentMemorySlot->setDegree/100)%10;
	numberDigits[1] = (currentMemorySlot->setDegree/10)%10;
	numberDigits[2] = currentMemorySlot->setDegree%10;

}

uint16_t digits2num(uint8_t digits[3])
{
	uint16_t numberFromDigits = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		numberFromDigits = 10 * numberFromDigits + digits[i];
	}
	return numberFromDigits;
}

void StateSetFixTrackDeg::run(StateMachine* master)
{
    float* refAngles = master->referenceAccel->getAngles();

    //It cant be 10 so 10 indicates no input. As we use the numpad to select the axes,
    // the invalid 10 should be overwritten only if we are number mode as we want to know no button was pressed in axes mode too
	currentDigit = adcValue2Digit(); //will be invalid (=10) if no button pressed

	if(HAL_GPIO_ReadPin(PURPLE_BTN_GPIO_Port, PURPLE_BTN_Pin))
	{
		HAL_Delay(10);
		while(HAL_GPIO_ReadPin(PURPLE_BTN_GPIO_Port, PURPLE_BTN_Pin)){__NOP();}
		HAL_Delay(10);
		currentSettingState = setFixAx;
		//ON ENTER OF SET_FIX_AX SUBSTATE
		DisplayTrackedAx(master->displayHandle, currentMemorySlot->getTrackedAx(), false); //Remove highlight
		DisplaySetAngle(master->displayHandle, currentMemorySlot->setDegree); //Remove highlight
		//ON ENTER OF SET_FIX_AX SUBSTATE
	}

	if(HAL_GPIO_ReadPin(GREEN_BTN_GPIO_Port, GREEN_BTN_Pin))
	{
		HAL_Delay(10);
		while(HAL_GPIO_ReadPin(GREEN_BTN_GPIO_Port, GREEN_BTN_Pin)){__NOP();}
		HAL_Delay(10);
		currentSettingState = setTrackAx;
		//ON ENTER OF SET_TRACK_AX SUBSTATE
		DisplayFixedAx(master->displayHandle, currentMemorySlot->getFixedAx(), false); //Remove highlight
		DisplaySetAngle(master->displayHandle, currentMemorySlot->setDegree); //Remove highlight
		//ON ENTER OF SET_TRACK_AX SUBSTATE
	}

	/*if the same axes was set as the tracked and fixed,
	 * then the previous value of the written axes will be written as the other
	 * resulting in the need to update both fields*/
	bool axUpdate = false;

	switch (currentSettingState)
	{
		case setDigit1:
			if(currentDigit == 10) currentDigit = numberDigits[currentSettingState];
			numberDigits[0] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit2;
			}
			break;
		case setDigit2:
			if(currentDigit == 10) currentDigit = numberDigits[currentSettingState];
			numberDigits[1] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit3;
			}
			break;
		case setDigit3:
			if(currentDigit == 10) currentDigit = numberDigits[currentSettingState];
			numberDigits[2] = currentDigit;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit1;
			}
			break;
		case setFixAx:
			switch (currentDigit) {
				case 1:
					axUpdate = currentMemorySlot->setFixedAx(x);
					break;
				case 2:
					axUpdate = currentMemorySlot->setFixedAx(y);
					break;
				default:
					break;
			}
			DisplayFixedAx(master->displayHandle, currentMemorySlot->getFixedAx(), true);
			if(!axUpdate) DisplayTrackedAx(master->displayHandle, currentMemorySlot->getTrackedAx(), false);

			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit1;
				//ON EXIT OF SET_FIX_AX SUBSTATE
				DisplayFixedAx(master->displayHandle, currentMemorySlot->getFixedAx(), false);
				//ON EXIT OF SET_FIX_AX SUBSTATE
			}

			break;
		case setTrackAx:
			switch (currentDigit) {
				case 1:
					axUpdate = currentMemorySlot->setTrackedAx(x);
					break;
				case 2:
					axUpdate = currentMemorySlot->setTrackedAx(y);
					break;
				case 3:
					axUpdate = currentMemorySlot->setTrackedAx(z);
					break;
				default:
					break;
			}
			DisplayTrackedAx(master->displayHandle, currentMemorySlot->getTrackedAx(), true);
			if(!axUpdate) DisplayFixedAx(master->displayHandle, currentMemorySlot->getFixedAx(), false);

			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit1;
				//ON EXIT OF SET_TRACK_AX SUBSTATE
				DisplayTrackedAx(master->displayHandle, currentMemorySlot->getTrackedAx(), false);
				//ON EXIT OF SET_TRACK_AX SUBSTATE
			}

			break;
		default:
			break;
	}

	currentMemorySlot->setDegree = digits2num(numberDigits);
	DisplaySetAngle(master->displayHandle, currentMemorySlot->setDegree, currentSettingState);

	DisplayRefDegs(master->displayHandle, refAngles[0], refAngles[1], refAngles[2]);

	master->displayHandle->WriteBitmapToScreen();
}

void StateSetFixTrackDeg::onExit(StateMachine* master)
{

}




