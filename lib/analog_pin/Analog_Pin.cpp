#include "Analog_Pin.h"

Analog_Pin::Analog_Pin(int pin)
    : pin(pin), val(0)
{
}

void Analog_Pin::init()
{
  this->update();
}

void Analog_Pin::update()
{
  this->val = analogRead(this->pin);
}

int Analog_Pin::getValue() const
{
  return this->val;
}