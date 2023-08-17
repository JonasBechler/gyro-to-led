#include "Low_Pass_Filter.h"

Low_Pass::Low_Pass(float low_pass_value)
    : low_pass_value(low_pass_value), val(0)
{
}

void Low_Pass::start(float start_value)
{
  this->val = start_value;
}

void Low_Pass::next(float value)
{
  this->val = this->val * this->low_pass_value + value * (1 - this->low_pass_value);
}

float Low_Pass::get() const
{
  float retval = this->val;
  return retval;
}