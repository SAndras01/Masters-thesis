/**
 * @file StepperController.hpp
 * @brief Controls a stepper motor using a timer, DMA, and a DIR GPIO pin.
 *
 * Provides functions to calculate movement profiles, start stepping, and configure microsteps.
 * Includes a LUT for negative arcsin approximation.
 *
 * @author Sásdi András (SNA1BP)
 * @date 2025-08-21
 */
#include <stdint.h>
#include "GPIO.hpp"
#include <cstring>
#include "stm32f7xx_hal_tim.h"

#ifndef MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_
#define MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_

// Defines
#define MAX_SIZE 200*64 + 1      /**< Maximum size of the timer ARR table */
#define FREQ_TMR 96000000UL      /**< Timer frequency in Hz */
#define FULL_STEP_DEG 1.8        /**< Full step angle in degrees */
#define PI 3.14159265358979323846
#define LUT_SIZE 100             /**< Size of LUT for negative arcsin approximation */

// Scalers
#define T_SCALER FREQ_TMR        /**< Time scaler for timer calculation */
#define THETA_SCALER 1000000UL   /**< Angle scaler for fixed-point calculations */

/**
 * @brief Lookup table structure for linear interpolation.
 */
struct LUTTable
{
    int32_t x_values[LUT_SIZE]; /**< X values (input) */
    int32_t y_values[LUT_SIZE]; /**< Y values (output) */
};

/**
 * @brief Stepper motor controller class.
 *
 * Manages stepping, movement profile calculation, and microstep configuration.
 * @todo error handling
 */
class StepperController
{
private:
	//Peripherals
    DMA_HandleTypeDef* timerUpdaterDMA; /**< DMA handle for updating timer ARR */
    GPIO* DIR_pin = nullptr;            /**< Direction GPIO pin */

	//Arrays
    uint32_t timer_values[MAX_SIZE];    /**< Precomputed timer values for stepping */
    static LUTTable minusArcSinLUT;     /**< LUT for negative arcsin approximation */

    // Physical characteristics
    double fullstep_deg; /**< Stepper full step angle in degrees */
    double u_step;       /**< Microstep fraction */
    uint32_t n_steps;    /**< Number of steps for current movement */

    /**
     * @brief Interpolates a value from a LUT.
     *
     * Uses linear approximation between points
     *
     * @param x Input value.
     * @param LUT Lookup table.
     * @return int32_t Interpolated value.
     */
    int32_t interpolate_from_LUT(int32_t x, LUTTable LUT);

public:
    TIM_HandleTypeDef* stepTimer; /**< Timer used for step generation */
    bool steppingFinished;        /**< Flag set when stepping is finished */

    /**
     * @brief Constructs the stepper controller.
     *
     * @param stepTimer Timer handle for step generation.
     * @param timerUpdaterDMA DMA handle for updating the timer.
     * @param DIR_pin Direction GPIO pin.
     * @param fullstep_deg Stepper full step angle in degrees.
     * @param u_step Microstep fraction.
     */
	StepperController(	TIM_HandleTypeDef* stepTimer,
						DMA_HandleTypeDef* timerUpdaterDMA,
						GPIO* DIR_pin,
						double fullstep_deg,
						double u_step);

    /**
     * @brief Calculates movement profile and precomputes timer ARR values.
     *
     * @param delta_Theta Angle to move in degrees.
     * @param delta_t Movement duration in seconds.
     * @return true if calculation was successful, false otherwise.
     */
	bool calculate_movement(uint32_t  delta_Theta, float delta_t);

    /**
     * @brief Starts stepping the motor in the specified direction.
     *
     * When stepping is finished the flag steppingFinished is set to true
     *
     * @param direction 1 for forward, -1 for reverse.
     * @return true if the stepper started successfully, false otherwise.
     */
	bool start_stepping(int8_t direction);

    /**
     * @brief Sets the microstep fraction.
     *
     * @param u_step Microstep fraction.
     */
	void set_ustep(float u_step);

    /**
     * @brief Returns the current microstep fraction.
     *
     * @return float Current microstep fraction.
     */
	float get_ustep();

    /**
     * @brief Returns the direction GPIO pin.
     *
     * @return GPIO* Pointer to the DIR GPIO.
     */
	GPIO* get_DIR_pin();
};




#endif /* MODULES_STEPPERCONTROLLER_STEPPERCONTROLLER_HPP_ */
