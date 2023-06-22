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


#ifndef ANALOG_PIN_h
#define ANALOG_PIN_h

#include "Arduino.h"
#include <Analog_Pin.h>


enum Smoothing_Method{
  none,
  low_pass,
  floating_avg
};



struct Analog_Pin_Config
{
  int pin;
  Smoothing_Method smoothing_method;
  float low_pass_value;
  int floating_avg_size;
};

class Analog_Pin
{
private:
    Analog_Pin_Config* config;
    int none_buffer;
    float low_pass_buffer;
    int floating_avg_index;
    int* floating_avg_buffer;




public:
    Analog_Pin(Analog_Pin_Config* config);

    void init();
    void update();
    
    int getState();
};
#endif


