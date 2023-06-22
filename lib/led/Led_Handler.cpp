/**
 * Author:     Jonas Bechler
 * Date  :     22.06.2023
 */

/**
 * Led Handler Class
 *
 * Handles an led.
 */

/***************************************************
 * includes
 ***************************************************/
#include "Led_Handler.h"

/***************************************************
 * Con- & Destructor
 ***************************************************/
Led_Handler::Led_Handler(int pin, int max_value)
{
    this->pin = pin;
    this->max_value = max_value;
}

/***************************************************
 * Setters
 ***************************************************/
void Led_Handler::setValue(int value)
{
  analogWrite(this->pin, map(value, 0, 256, 0, this->max_value));
}