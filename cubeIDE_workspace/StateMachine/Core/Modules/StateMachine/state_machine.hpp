/*
 * state_machine.hpp
 *
 *  Created on: Sep 17, 2025
 *      Author: SNA1BP
 */

#ifndef MODULES_STATEMACHINE_STATE_MACHINE_HPP_
#define MODULES_STATEMACHINE_STATE_MACHINE_HPP_

#include <memorySlot.hpp>
#include <stdint.h>
#include "GUI.hpp"
#include "accelerometer.hpp"
#include "numpad.hpp"
#include "main.h"

class StateMachine;

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
	StateMachine(State* initial, SSD1305* displayHandle, Accelerometer* referenceAccel);
    void changeState(State* next);
    void run();
};

class StateSetFixTrackDeg : public State
{
private:
	enum SettingSelectState {setDigit1 = 0, setDigit2 = 1, setDigit3 = 2, setFixAx = 4, setTrackAx = 5};
	SettingSelectState currentSettingState = setDigit1;
	uint8_t currentDigit;
	uint8_t numberDigits[3] = {0,0,0};
	MemorySlot* currentMemorySlot;
public:
	StateSetFixTrackDeg(MemorySlot* initialMemorySlot);
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;

    void setMemorySlot(MemorySlot*);
    MemorySlot* getMemorySlot();
};
#endif /* MODULES_STATEMACHINE_STATE_MACHINE_HPP_ */
