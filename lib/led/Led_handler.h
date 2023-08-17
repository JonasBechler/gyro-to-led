#pragma once

#include "Arduino.h"

/**
 * @brief The Led_Handler class provides an interface to control an LED with various functionalities.
 */
class Led_Handler
{
private:
    int pin;                       /**< The pin number to which the LED is connected. */
    int value;                     /**< The current intensity value of the LED (brightness). */
    int max_value;                 /**< The maximum intensity value the LED can have. */
    bool led_state;                /**< The current state of the LED (on/off). */
    unsigned long previous_millis; /**< Stores the previous time (milliseconds) value for blinking. */
    unsigned long delay_duration;  /**< The delay after the LED turns off. */

public:
    /**
     * @brief Constructor for the Led_Handler class.
     * @param pin The pin number to which the LED is connected.
     * @param max_value The maximum intensity value the LED can have.
     * @param delay_duration The duration for blinking.
     */
    Led_Handler(int pin, int max_value, unsigned long delay_duration);

    /**
     * @brief Initializes the LED handler by setting up the necessary initial configurations.
     */
    void init();

    /**
     * @brief Sets the state of the LED.
     * @param onoff The desired state of the LED (true for on, false for off).
     */
    void set(bool onoff);

    /**
     * @brief Sets the intensity value of the LED.
     * @param value The intensity value to set for the LED.
     */
    void setValue(int value);

    /**
     * @brief Blinks the LED for a specified time duration.
     * @param t_on_off The time duration for each on-off cycle of the blink.
     */
    void blink(int t_on_off);
};
