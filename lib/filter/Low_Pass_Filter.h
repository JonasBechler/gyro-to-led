#pragma once

#include "Arduino.h"

/**
 * @brief The Low_Pass class implements a simple low-pass filter.
 */
class Low_Pass
{
private:
    float low_pass_value; /**< The smoothing factor for the low-pass filter. */
    float val;            /**< The current filtered value. */

public:
    /**
     * @brief Constructor for the Low_Pass class.
     * @param low_pass_value The smoothing factor for the low-pass filter.
     */
    Low_Pass(float low_pass_value);

    /**
     * @brief Initializes the low-pass filter with a starting value.
     * @param start_value The initial value to start the filter.
     */
    void start(float start_value);

    /**
     * @brief Updates the filter with a new value and computes the filtered result.
     * @param value The new value to be filtered.
     */
    void next(float value);

    /**
     * @brief Retrieves the current filtered value.
     * @return The current filtered value.
     */
    float get() const;
};
