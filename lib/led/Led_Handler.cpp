#include "Led_Handler.h"

Led_Handler::Led_Handler(int pin, int max_value, unsigned long delay_duration)
    : pin(pin), max_value(max_value), delay_duration(delay_duration), value(5), led_state(false), previous_millis(0)
{
}

void Led_Handler::init()
{
  analogWrite(this->pin, 0);
}

void Led_Handler::set(bool onoff)
{
  if (onoff && !this->led_state)
  {
    analogWrite(this->pin, map(this->value, 0, 256, 0, this->max_value));
    this->led_state = true;
    this->previous_millis = millis();
  }
  else if (!onoff && millis() - this->previous_millis >= this->delay_duration)
  {
    this->led_state = false;
    analogWrite(this->pin, 0);
  }
}

void Led_Handler::setValue(int new_value)
{
  if (this->value != new_value)
  {
    this->value = new_value;
    if (this->led_state && millis() - this->previous_millis >= this->delay_duration)
    {
      analogWrite(this->pin, map(this->value, 0, 256, 0, this->max_value));
      this->previous_millis = millis();
    }
  }
}

void Led_Handler::blink(int t_on_off)
{
  uint8_t current_value = (millis() / t_on_off) % 2;
  analogWrite(this->pin, map(this->value * current_value, 0, 256, 0, this->max_value));
  this->previous_millis = millis();
}
