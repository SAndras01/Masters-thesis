/*
 * state_machine.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_STATEMACHINE_STATE_MACHINE_HPP_
#define MODULES_STATEMACHINE_STATE_MACHINE_HPP_

#include <memorySlot.hpp>
#include "memory.hpp"
#include <stdint.h>
#include "GUI.hpp"
#include "accelerometer.hpp"
#include "numpad.hpp"
#include "main.h"

//Function typedefs
uint16_t digits2num(uint8_t digits[3]);
bool getMemorySlotFromEEPROM(MemorySlot* memorySlotHandle, uint8_t memorySlotNumber, EEPROMmemory* eepromHandle);
//Function typedefs

class StateMachine;
class State_SelectMemory;
class State_Settings;

class State
{
public:
    virtual void onEnter(StateMachine* master){};
    virtual void onExit(StateMachine* master){};
    virtual void run(StateMachine* master) = 0; //=0 -> needs to be overriden
};

class StateMachine
{
private:
	State* current = nullptr;
public:
	SSD1305* displayHandle;
	Accelerometer* referenceAccel;
	EEPROMmemory* eepromHandle;

	//states
	State_Settings* settings = nullptr;
	State_SelectMemory* selectMemory = nullptr;

	StateMachine(
				State* initial, /*Initial state*/
				State_Settings* settings, State_SelectMemory* selectMemory, /*States*/
				SSD1305* displayHandle, Accelerometer* referenceAccel, EEPROMmemory* eepromHandle /*Resources*/
				);
    void changeState(State* next);
    void run();
};

class State_Settings : public State
{
private:
	enum SettingSelectState {setDigit1 = 0, setDigit2 = 1, setDigit3 = 2, setFixAx = 4, setTrackAx = 5};
	SettingSelectState currentSettingState = setDigit1;
	uint8_t currentDigit;
	uint8_t numberDigits[3] = {0,0,0};
public:

	MemorySlot currentMemorySlot;

	State_Settings();
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;
};

class State_SelectMemory : public State
{
private:
	uint8_t currentDigit;
public:

	State_SelectMemory();
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;
};

#endif /* MODULES_STATEMACHINE_STATE_MACHINE_HPP_ */
