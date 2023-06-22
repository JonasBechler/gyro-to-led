#include "GY521_Handler.h"

void init_GY521(GY521 *sensor)
{
  while (sensor->wakeup() == false)
  {
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor->setAccelSensitivity(1); //  4g
  sensor->setGyroSensitivity(0);  //  250 degrees/s

  sensor->setThrottle();

  //  set calibration values from calibration sketch.
  sensor->axe = 0.0707690;
  sensor->aye = 0.0140771;
  sensor->aze = -1.1019092;
  sensor->gxe = 10.1912212;
  sensor->gye = -2.3874810;
  sensor->gze = -0.7128244;
}

void setData_GY521(GY521 *sensor, Data_GY521 *data)
{
  data->AccX = sensor->getAccelX();
  data->AccY = sensor->getAccelY();
  data->AccZ = sensor->getAccelZ();
  data->AngX = sensor->getAngleX();
  data->AngY = sensor->getAngleY();
  data->AngZ = sensor->getAngleZ();
  data->GyroX = sensor->getGyroX();
  data->GyroY = sensor->getGyroY();
  data->GyroZ = sensor->getGyroZ();
  data->Roll = sensor->getRoll();
  data->Pitch = sensor->getPitch();
  data->Yaw = sensor->getYaw();
  data->Temp = sensor->getTemperature();
}

void getDataStringInit_GY521(String &buf)
{
  buf = "accX,\taccY,\taccZ,\t\tangX,\tangY,\tangZ,\t\tgyroX,\tgyroY,\tgyroZ,\t\troll,\tpitch,\tyaw,\t\ttemp\t\ttime,\n";
}

void getDataString_GY521(Data_GY521 *data, String &buf)
{
  buf = "";
  buf += data->AccX;
  buf += ",\t";
  buf += data->AccY;
  buf += ",\t";
  buf += data->AccZ;
  buf += ",\t";
  buf += "\t";
  buf += data->AngX;
  buf += ",\t";
  buf += data->AngY;
  buf += ",\t";
  buf += data->AngZ;
  buf += ",\t";
  buf += "\t";
  buf += data->GyroX;
  buf += ",\t";
  buf += data->GyroY;
  buf += ",\t";
  buf += data->GyroZ;
  buf += ",\t";
  buf += "\t";
  buf += data->Roll;
  buf += ",\t";
  buf += data->Pitch;
  buf += ",\t";
  buf += data->Yaw;
  buf += ",\t";
  buf += "\t";
  buf += data->Temp;
  buf += ",\t";
  buf += "\t";
  buf += millis();
  buf += "\n";
}

void neg_Data_GY521(Data_GY521 *dataA)
{
  dataA->AccX = -dataA->AccX;
  dataA->AccY = -dataA->AccY;
  dataA->AccZ = -dataA->AccZ;
  dataA->AngX = -dataA->AngX;
  dataA->AngY = -dataA->AngY;
  dataA->AngZ = -dataA->AngZ;
  dataA->GyroX = -dataA->GyroX;
  dataA->GyroY = -dataA->GyroY;
  dataA->GyroZ = -dataA->GyroZ;
  dataA->Roll = -dataA->Roll;
  dataA->Pitch = -dataA->Pitch;
  dataA->Yaw = -dataA->Yaw;
  dataA->Temp = -dataA->Temp;
}

void add_Data_GY521(Data_GY521 *dataA, Data_GY521 *dataB)
{
  dataA->AccX = dataA->AccX + dataB->AccX;
  dataA->AccY = dataA->AccY + dataB->AccY;
  dataA->AccZ = dataA->AccZ + dataB->AccZ;
  dataA->AngX = dataA->AngX + dataB->AngX;
  dataA->AngY = dataA->AngY + dataB->AngY;
  dataA->AngZ = dataA->AngZ + dataB->AngZ;
  dataA->GyroX = dataA->GyroX + dataB->GyroX;
  dataA->GyroY = dataA->GyroY + dataB->GyroY;
  dataA->GyroZ = dataA->GyroZ + dataB->GyroZ;
  dataA->Roll = dataA->Roll + dataB->Roll;
  dataA->Pitch = dataA->Pitch + dataB->Pitch;
  dataA->Yaw = dataA->Yaw + dataB->Yaw;
  dataA->Temp = dataA->Temp + dataB->Temp;
}

void mult_Data_GY521(Data_GY521 *dataA, float factor)
{
  dataA->AccX = dataA->AccX * factor;
  dataA->AccY = dataA->AccY * factor;
  dataA->AccZ = dataA->AccZ * factor;
  dataA->AngX = dataA->AngX * factor;
  dataA->AngY = dataA->AngY * factor;
  dataA->AngZ = dataA->AngZ * factor;
  dataA->GyroX = dataA->GyroX * factor;
  dataA->GyroY = dataA->GyroY * factor;
  dataA->GyroZ = dataA->GyroZ * factor;
  dataA->Roll = dataA->Roll * factor;
  dataA->Pitch = dataA->Pitch * factor;
  dataA->Yaw = dataA->Yaw * factor;
  dataA->Temp = dataA->Temp * factor;
}
