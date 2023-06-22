/**
 * Author:     Jonas Bechler
 * Date  :     22.06.2023
 */

/**
 * Led Handler Class
 *
 * Handles an led.
 */



#ifndef LED_HANDLER_h
#define LED_HANDLER_h

#include "Arduino.h"
#include <Led_Handler.h>



class Led_Handler
{
private:
    int pin;
    int max_value;

public:
    Led_Handler(int pin, int max_value);
    void setValue(int value);
};
#endif

