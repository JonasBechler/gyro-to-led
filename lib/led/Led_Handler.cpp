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
Led_Handler::Led_Handler(int pin, int max_value, unsigned long delay_duration)
{
  this->pin = pin;
  this->led_state = false;
  this->max_value = max_value;
  this->delay_duration = delay_duration;
  this->value = 5;
}

/***************************************************
 * Setters
 ***************************************************/
void Led_Handler::set(bool onoff)
{
  if (onoff)
  {
    if (!this->led_state)
    {
      analogWrite(this->pin, map(this->value, 0, 256, 0, this->max_value));
      this->led_state = true;
      this->previous_millis = millis();
    }
  }
  else
  {
    if (millis() - this->previous_millis >= this->delay_duration)
    {
      this->led_state = false;
      analogWrite(this->pin, 0);
    }
  }
}

void Led_Handler::setValue(int value)
{
  this->value = value;
  analogWrite(this->pin, map(this->value, 0, 256, 0, this->max_value));
}