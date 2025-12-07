/**
 * @file state_machine.hpp
 * @brief Implements a simple state machine for memory slot selection and settings.
 *
 * Provides classes for a generic state, a state machine manager.
 * Includes helper functions for converting digits
 * to numbers and reading/writing memory slots from EEPROM.
 *
 * @author Sásdi András
 * @date 2025-09-17
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

/**
 * @brief Converts a 3-digit array into a single integer number.
 *
 * @param digits Array of 3 digits.
 * @return uint16_t The corresponding number.
 */
uint16_t digits2num(uint8_t digits[3]);

/**
 * @brief Reads a memory slot from EEPROM and updates the given MemorySlot object.
 *
 * Validates the retrieved data using the setter functions.
 *
 * @param memorySlotHandle Pointer to the MemorySlot to populate.
 * @param memorySlotNumber Number of the memory slot to read.
 * @param eepromHandle Pointer to the EEPROMmemory object.
 * @return true if the memory slot was successfully read and set, false otherwise.
 */
bool getMemorySlotFromEEPROM(MemorySlot* memorySlotHandle, uint8_t memorySlotNumber, EEPROMmemory* eepromHandle);

/**
 * @brief Saves a MemorySlot object to EEPROM.
 *
 * @param memorySlot MemorySlot object to save.
 * @param eepromHandle Pointer to the EEPROMmemory object.
 * @return true if successfully written, false otherwise.
 */
bool saveMemorySlotToEEPROM(MemorySlot memorySlot, EEPROMmemory* eepromHandle);

class StateMachine;
class State_SelectMemory;
class State_Settings;
class State_Moving;
class State_FreeMove;
class State_Remote;
/**
 * @brief Abstract base class for a state in the state machine.
 */
class State
{
public:
    /** Called when entering the state */
    virtual void onEnter(StateMachine* master){};

    /** Called when exiting the state */
    virtual void onExit(StateMachine* master){};

    /** State logic; must be implemented by derived classes */
    virtual void run(StateMachine* master) = 0;
};

/**
 * @brief State machine manager class.
 *
 * Holds references to the current state, states objects, and shared resources.
 */
class StateMachine
{
private:
    State* current = nullptr;

public:
    SSD1305* displayHandle;           /**< Display interface */
    Accelerometer* referenceAccel;    /**< Reference accelerometer */
    EEPROMmemory* eepromHandle;       /**< EEPROM interface */

    State_Settings* settings = nullptr;       /**< Pointer to the settings state */
    State_SelectMemory* selectMemory = nullptr; /**< Pointer to the memory selection state */
    State_Moving* moving = nullptr; /**< Pointer to the moving state */
    State_FreeMove* freeMove = nullptr; /**< Pointer to the free move selection state */
    State_Remote* remote = nullptr; /**< Pointer to the remote selection state */

    /**
     * @brief Constructs a StateMachine with initial state and resources.
     *
     * @param initial Initial state.
     * @param settings Pointer to State_Settings object.
     * @param selectMemory Pointer to State_SelectMemory object.
     * @param displayHandle Pointer to SSD1305 display.
     * @param referenceAccel Pointer to accelerometer.
     * @param eepromHandle Pointer to EEPROM memory.
     */
    StateMachine(State* initial,
                 State_Settings* settings, State_SelectMemory* selectMemory, State_Moving* moving, State_FreeMove* freeMove, State_Remote* remote,
                 SSD1305* displayHandle, Accelerometer* referenceAccel, EEPROMmemory* eepromHandle);

    /** @brief Changes the current state to the given next state. */
    void changeState(State* next);

    /** @brief Runs the current state's logic. */
    void run();
};

class State_Settings : public State
{
private:
	enum SettingSelectState {setDigit1 = 0, setDigit2 = 1, setDigit3 = 2, setFixAx = 4, setTrackAx = 5}; //substates
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

class State_Moving : public State
{
	State_Moving();
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;
};

class State_FreeMove : public State
{
	State_FreeMove();
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;
};

class State_Remote : public State
{
	State_Remote();
    void onEnter(StateMachine* master) override;
    void run(StateMachine* master) override;
    void onExit(StateMachine* master) override;
};




#endif /* MODULES_STATEMACHINE_STATE_MACHINE_HPP_ */
