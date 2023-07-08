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
#include "Low_Pass_Filter.h"

/***************************************************
 * Con- & Destructor
 ***************************************************/
Low_Pass::Low_Pass(float low_pass_value)
{
    this->low_pass_value = low_pass_value;
}

void Low_Pass::start(float start_value)
{
  this->buf = start_value;
}

void Low_Pass::next(float value)
{
  this->buf = this->buf * this->low_pass_value + value * (1 - this->low_pass_value);
}

float Low_Pass::get()
{
    float retval = this->buf;
    return retval;
}