/**
 * Author:     Jonas Bechler
 * Date  :     22.06.2023
 */

/**
 * Analog Pin Class
 *
 * Handles an analog pin. 
 * Different smoothing methods available, seen in "Smoothing_Method"
 */

/***************************************************
 * includes
 ***************************************************/
#include "Analog_Pin.h"

/***************************************************
 * Con- & Destructor
 ***************************************************/
Analog_Pin::Analog_Pin(int pin)
{
  this->pin = pin;

}

/***************************************************
 * Init + Update
 ***************************************************/
void Analog_Pin::init()
{
  this->buf = analogRead(this->pin);
}

void Analog_Pin::update()
{
  this->buf = analogRead(this->pin);
}
    
/***************************************************
 * Getters
 ***************************************************/
int Analog_Pin::getState()
{
  int ret_val = this->buf;
  return ret_val;
}