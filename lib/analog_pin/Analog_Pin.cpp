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
Analog_Pin::Analog_Pin(Analog_Pin_Config* config)
{
  this->config = config;

  switch (this->config->smoothing_method)
  {
  case none:
    break;
  
  case low_pass:
    break;

  case floating_avg:
    free(this->floating_avg_buffer);
    this->floating_avg_buffer = ( int )malloc(this->config->floating_avg_size);
    break;
  }
}

Analog_Pin::~Analog_Pin() {
  switch (this->config->smoothing_method)
  {
  case none:
    break;
  
  case low_pass:
    break;

  case floating_avg:
    free(this->floating_avg_buffer);
    break;
  }
}

/***************************************************
 * Init + Update
 ***************************************************/
void Analog_Pin::init()
{
  switch (this->config->smoothing_method)
  {
  case none:
    this->none_buffer = analogRead(this->config->pin);
    break;
  
  case low_pass:
    low_pass_buffer = analogRead(this->config->pin);
    break;

  case floating_avg:
    floating_avg_index = 0;

    for (int i = 0; i < this->config->floating_avg_size; i++){
      this->floating_avg_buffer[i] = analogRead(this->config->pin);
      delay(1);
    }
    break;
  }
}

void Analog_Pin::update()
{
  switch (this->config->smoothing_method)
  {
  case none:
    this->none_buffer = analogRead(this->config->pin);
    break;
  
  case low_pass:
    this->low_pass_buffer = this->low_pass_buffer * (1 - this->config->low_pass_value) + analogRead(this->config->pin) * this->config->low_pass_value;
    break;

  case floating_avg:
    this->floating_avg_buffer[this->floating_avg_index] = analogRead(this->config->pin);
    if(this->floating_avg_index < this->config->floating_avg_size - 1){
      this->floating_avg_index = this->floating_avg_index + 1;
    }
    else{
      this->floating_avg_index = 0;
    }
    break;
  }
}
    
/***************************************************
 * Getters
 ***************************************************/
int Analog_Pin::getState()
{
  int ret_val = 0;
  switch (this->config->smoothing_method)
  {
  case none:
    ret_val = none_buffer; 
    break;
  
  case low_pass:
    ret_val = (int) low_pass_buffer; 
    break;

  case floating_avg:
    for (int i = 0; i < this->config->floating_avg_size; i++){
      ret_val += this->floating_avg_buffer[i];
    }
    ret_val = (int) (ret_val / this->config->floating_avg_size);
    break;
  }
  return ret_val;
}