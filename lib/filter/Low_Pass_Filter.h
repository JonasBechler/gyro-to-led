#pragma once

/**
 * Author:     Jonas Bechler
 * Date  :     08.07.2023
 */

/**
 * flowing avg filter class
 * 
 */



#ifndef LOW_PASS_h
#define LOW_PASS_h

#include "Arduino.h"



class Low_Pass
{
private:
    float low_pass_value;
    float buf;
    
public:
    Low_Pass(float low_pass_value);
    void start(float start_value);
    void next(float value);
    float get();
};
#endif