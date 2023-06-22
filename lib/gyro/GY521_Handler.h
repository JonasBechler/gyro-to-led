#ifndef GY521_HANDLER_h
#define GY521_HANDLER_h

#include "Arduino.h"
#include <GY521.h>

struct Data_GY521
{
  float AccX;
  float AccY;
  float AccZ;
  float AngX;
  float AngY;
  float AngZ;
  float GyroX;
  float GyroY;
  float GyroZ;
  float Roll;
  float Pitch;
  float Yaw;
  float Temp;
};

void init_GY521(GY521 *sensor);

void setData_GY521(GY521 *sensor, Data_GY521 *data);

// Beautyfy
void getDataStringInit_GY521(String &buf);
void getDataString_GY521(Data_GY521 *data, String &buf);

// Maths
void neg_Data_GY521(Data_GY521 *dataA);
void add_Data_GY521(Data_GY521 *dataA, Data_GY521 *dataB);
void mult_Data_GY521(Data_GY521 *dataA, float factor);

#endif