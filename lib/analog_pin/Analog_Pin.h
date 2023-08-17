#pragma once

#include "Arduino.h"

/**
 * @brief The Analog_Pin class provides an interface for reading values from an analog pin.
 */
class Analog_Pin
{
private:
    int pin; /**< The analog pin number to read from. */
    int val; /**< The most recent read value from the analog pin. */

public:
    /**
     * @brief Constructor for the Analog_Pin class.
     * @param pin The analog pin number to read from.
     */
    Analog_Pin(int pin);

    /**
     * @brief Initializes the analog pin for reading.
     */
    void init();

    /**
     * @brief Updates the stored value by reading the analog pin.
     */
    void update();

    /**
     * @brief Retrieves the most recent read value from the analog pin.
     * @return The most recent analog value.
     */
    int getValue() const;
};
