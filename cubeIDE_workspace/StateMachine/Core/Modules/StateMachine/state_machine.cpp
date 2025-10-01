/*
 * state_machine.cpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#include "state_machine.hpp"

uint16_t digits2num(uint8_t digits[3])
{
	uint16_t numberFromDigits = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		numberFromDigits = 10 * numberFromDigits + digits[i];
	}
	return numberFromDigits;
}

//Get the data from the eeprom with data validity checks.
bool getMemorySlotFromEEPROM(MemorySlot* memorySlotHandle, uint8_t memorySlotNumber, EEPROMmemory* eepromHandle)
{
	bool state = true;
	memorySlotHandle->number = memorySlotNumber;

	//In the eeprom there are key-value pairs
	char eepromFixAxKey[20];
	char eepromTrackAxKey[20];
	char eepromSetDegKey[20];
	snprintf(eepromFixAxKey, sizeof(eepromFixAxKey), "MS%u_fixAx", memorySlotNumber);
	snprintf(eepromTrackAxKey, sizeof(eepromTrackAxKey), "MS%u_trackAx", memorySlotNumber);
	snprintf(eepromSetDegKey, sizeof(eepromSetDegKey), "MS%u_setDeg", memorySlotNumber);

	//Get the values from the EEPROM
	uint8_t fixAxBuffer = 0;
	uint8_t trackAxBuffer = 0;
	uint16_t setDegBuffer = 0;

	//All the conversions and checks are implemented in the setter functions
	state &= eepromHandle->getValue(eepromFixAxKey, &fixAxBuffer);
	state &= eepromHandle->getValue(eepromTrackAxKey, &trackAxBuffer);
	state &= eepromHandle->getValue(eepromSetDegKey, &setDegBuffer);

	state &= memorySlotHandle->setFixedAx(fixAxBuffer);
	state &= memorySlotHandle->setTrackedAx(trackAxBuffer);
	state &= memorySlotHandle->setSetDegree(setDegBuffer);

	return state;
}

bool saveMemorySlotToEEPROM(MemorySlot memorySlot, EEPROMmemory* eepromHandle)
{
	bool state = true;

	//In the eeprom there are key-value pairs
	char eepromFixAxKey[20];
	char eepromTrackAxKey[20];
	char eepromSetDegKey[20];
	snprintf(eepromFixAxKey, sizeof(eepromFixAxKey), "MS%u_fixAx", memorySlot.number);
	snprintf(eepromTrackAxKey, sizeof(eepromTrackAxKey), "MS%u_trackAx", memorySlot.number);
	snprintf(eepromSetDegKey, sizeof(eepromSetDegKey), "MS%u_setDeg", memorySlot.number);

	//Write it to the eeprom
	state &= eepromHandle->setValue(eepromFixAxKey, (uint8_t)memorySlot.getFixedAx());
	state &= eepromHandle->setValue(eepromTrackAxKey, (uint8_t)memorySlot.getTrackedAx());
	state &= eepromHandle->setValue(eepromSetDegKey, memorySlot.getSetDegree());

	return state;
}

StateMachine::StateMachine(
		State* initial, /*Initial state*/
		State_Settings* settings, State_SelectMemory* selectMemory, /*States*/
		SSD1305* displayHandle, Accelerometer* referenceAccel, EEPROMmemory* eepromHandle /*Resources*/
		)
{
	this->settings = settings;
	this->selectMemory = selectMemory;
	this->displayHandle = displayHandle;
	this->referenceAccel = referenceAccel;
	this->eepromHandle = eepromHandle;
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
/////////////////////////////////////////////////////////////
////////////////////////SETTINGS STAE////////////////////////
/////////////////////////////////////////////////////////////

State_Settings::State_Settings()
{
}

void State_Settings::onEnter(StateMachine* master)
{
    float* refAngles = master->referenceAccel->getAngles();
	DrawGUI(master->displayHandle, currentMemorySlot, refAngles[0], refAngles[1], refAngles[2]);
	numberDigits[0] = (currentMemorySlot.getSetDegree()/100)%10;
	numberDigits[1] = (currentMemorySlot.getSetDegree()/10)%10;
	numberDigits[2] = currentMemorySlot.getSetDegree()%10;
}

void State_Settings::run(StateMachine* master)
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
		DisplayTrackedAx(master->displayHandle, currentMemorySlot.getTrackedAx(), false); //Remove highlight
		DisplaySetAngle(master->displayHandle, currentMemorySlot.getSetDegree()); //Remove highlight
		//ON ENTER OF SET_FIX_AX SUBSTATE
	}

	if(HAL_GPIO_ReadPin(GREEN_BTN_GPIO_Port, GREEN_BTN_Pin))
	{
		HAL_Delay(10);
		while(HAL_GPIO_ReadPin(GREEN_BTN_GPIO_Port, GREEN_BTN_Pin)){__NOP();}
		HAL_Delay(10);
		currentSettingState = setTrackAx;
		//ON ENTER OF SET_TRACK_AX SUBSTATE
		DisplayFixedAx(master->displayHandle, currentMemorySlot.getFixedAx(), false); //Remove highlight
		DisplaySetAngle(master->displayHandle, currentMemorySlot.getSetDegree()); //Remove highlight
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
					axUpdate = currentMemorySlot.setFixedAx(x);
					break;
				case 2:
					axUpdate = currentMemorySlot.setFixedAx(y);
					break;
				default:
					break;
			}
			DisplayFixedAx(master->displayHandle, currentMemorySlot.getFixedAx(), true);
			if(!axUpdate) DisplayTrackedAx(master->displayHandle, currentMemorySlot.getTrackedAx(), false);

			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit1;
				//ON EXIT OF SET_FIX_AX SUBSTATE
				DisplayFixedAx(master->displayHandle, currentMemorySlot.getFixedAx(), false);
				//ON EXIT OF SET_FIX_AX SUBSTATE
			}

			break;
		case setTrackAx:
			switch (currentDigit) {
				case 1:
					axUpdate = currentMemorySlot.setTrackedAx(x);
					break;
				case 2:
					axUpdate = currentMemorySlot.setTrackedAx(y);
					break;
				case 3:
					axUpdate = currentMemorySlot.setTrackedAx(z);
					break;
				default:
					break;
			}
			DisplayTrackedAx(master->displayHandle, currentMemorySlot.getTrackedAx(), true);
			if(!axUpdate) DisplayFixedAx(master->displayHandle, currentMemorySlot.getFixedAx(), false);

			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentSettingState = setDigit1;
				//ON EXIT OF SET_TRACK_AX SUBSTATE
				DisplayTrackedAx(master->displayHandle, currentMemorySlot.getTrackedAx(), false);
				//ON EXIT OF SET_TRACK_AX SUBSTATE
			}

			break;
		default:
			break;
	}

	currentMemorySlot.setSetDegree(digits2num(numberDigits));
	DisplaySetAngle(master->displayHandle, currentMemorySlot.getSetDegree(), currentSettingState);

	DisplayRefDegs(master->displayHandle, refAngles[0], refAngles[1], refAngles[2]);

	master->displayHandle->WriteBitmapToScreen();


	////////////////////////////////
	///state changing scenarios/////
	////////////////////////////////
	if(HAL_GPIO_ReadPin(BLUE_BTN_GPIO_Port, BLUE_BTN_Pin))
	{
		HAL_Delay(10);
		while(HAL_GPIO_ReadPin(BLUE_BTN_GPIO_Port, BLUE_BTN_Pin)){__NOP();}
		HAL_Delay(10);
		master->changeState(master->selectMemory);
	}
}

void State_Settings::onExit(StateMachine* master)
{
	saveMemorySlotToEEPROM(currentMemorySlot, master->eepromHandle);
}


//////////////////////////////////////////////////////////////////////
////////////////////////MEMORY SELECTION STATE////////////////////////
//////////////////////////////////////////////////////////////////////

State_SelectMemory::State_SelectMemory(){};

void State_SelectMemory::onEnter(StateMachine* master)
{
	currentDigit = master->settings->currentMemorySlot.number;
	//remove highlights
	float* refAngles = master->referenceAccel->getAngles();
	DrawGUI(master->displayHandle, master->settings->currentMemorySlot, refAngles[0], refAngles[1], refAngles[2], true);
}

void State_SelectMemory::run(StateMachine* master)
{
	uint8_t previousRegisteredDigit = 0;

	currentDigit = adcValue2Digit();
	if(currentDigit != 10 && currentDigit != 0 && currentDigit != previousRegisteredDigit)
	{
		getMemorySlotFromEEPROM(&master->settings->currentMemorySlot, currentDigit, master->eepromHandle);
	}

	float* refAngles = master->referenceAccel->getAngles();
	DrawGUI(master->displayHandle, master->settings->currentMemorySlot, refAngles[0], refAngles[1], refAngles[2], true);

	previousRegisteredDigit = currentDigit;

	if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
	{
		HAL_Delay(10);
		while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
		HAL_Delay(10);
		master->changeState(master->settings);
	}
}

void State_SelectMemory::onExit(StateMachine* master)
{

}
