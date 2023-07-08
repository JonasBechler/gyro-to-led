#pragma once

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






class Analog_Pin
{
private:
    int pin;
    int buf;




public:
    Analog_Pin(int pin);

    void init();
    void update();
    
    int getState();
};
#endif


