#include "../gy521/GY521_Handler.h"
#include "../analog_pin/Analog_Pin.h"
#include "../led/Led_Handler.h"
#include "../filter/Low_Pass_Filter.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

#define SERIAL_PRINT_DEBUG

// Functions
void processLeds();
void turnOffLeds();
void print_debug();
void print_float(float value);
void println_float(float value);

// Define constants
const int delay_duration = 1000;
const float lowpass_value = 0.975;
const float curve_speed_threshold = 0.015;
const float brake_accl_threshold = 0.1;
const float emergency_brake_accl_threshold = 0.3;
const float day_night_threshold = 4000.0;

// Define LED handlers
Led_Handler left_led(25, 80, delay_duration);
Led_Handler center_led(26, 80, delay_duration);
Led_Handler right_led(27, 80, delay_duration);
Led_Handler extra_led(14, 100, delay_duration);
Led_Handler back_led(12, 255, delay_duration);

// Define GY521 gyro
GY521 gyro(0x68);
Data_GY521 gyro_data;
Data_GY521 lowpass_gyro_data;
Data_GY521 lowpass_gyro_data_old;
Data_GY521 delta_lowpass_gyro_data;
Data_GY521 gyro_data_buffer_1;
Data_GY521 gyro_data_buffer_2;

// Define Photoresistor
Analog_Pin photo_resistor(32);
Low_Pass photo_resistor_lowpass(0.99);

unsigned long t_now = 0;
unsigned long t_last = 0;
int t_diff = 0;

void setup()
{
  #ifdef SERIAL_PRINT_DEBUG
    Serial.begin(115200);
    Serial.println();
    Serial.println(__FILE__);
  #endif

  // Initialize LED handlers
  left_led.init();
  center_led.init();
  right_led.init();
  extra_led.init();
  back_led.init();

  // Initialize Wire and GY521
  Wire.begin();
  delay(100);
  init_GY521(&gyro);

  // Initialize photoresistor and low-pass filter
  photo_resistor.init();
  photo_resistor_lowpass.start(photo_resistor.getValue());

  delay(10);
  gyro.read();
  setData_GY521(&gyro, &gyro_data);
  lowpass_gyro_data = gyro_data;

  // Set initial LED values
  left_led.setValue(255);
  center_led.setValue(255);
  right_led.setValue(255);
  extra_led.setValue(0);
  back_led.setValue(0);
}

void loop()
{
  photo_resistor.update();
  photo_resistor_lowpass.next(photo_resistor.getValue());

  // if (photo_resistor.getValue() < day_night_threshold)
  // {
  //   processLeds();
  // }
  // else
  // {
  //   turnOffLeds();
  // }
  processLeds();

  delay(5);
}

void processLeds()
{
  gyro.read();
  setData_GY521(&gyro, &gyro_data);

  t_now = millis();
  t_diff = t_now - t_last;
  t_last = t_now;

  lowpass_gyro_data_old = lowpass_gyro_data;

  check_over_under_flow(&gyro_data, &lowpass_gyro_data);

  // lowpass_gyro_data = lowpass_gyro_data * lowpass_value + gyro_data * (1 - lowpass_value)
  gyro_data_buffer_1 = lowpass_gyro_data;
  gyro_data_buffer_2 = gyro_data;
  mult_Data_GY521(&gyro_data_buffer_1, lowpass_value);
  mult_Data_GY521(&gyro_data_buffer_2, 1.0 - lowpass_value);
  add_Data_GY521(&gyro_data_buffer_1, &gyro_data_buffer_2);
  lowpass_gyro_data = gyro_data_buffer_1;

  check_over_under_flow(&lowpass_gyro_data, &lowpass_gyro_data_old);

  // delta_lowpass_gyro_data = (lowpass_gyro_data - lowpass_gyro_data_old) / t_diff
  gyro_data_buffer_1 = lowpass_gyro_data;
  gyro_data_buffer_2 = lowpass_gyro_data_old;
  neg_Data_GY521(&gyro_data_buffer_2);
  add_Data_GY521(&gyro_data_buffer_1, &gyro_data_buffer_2);
  mult_Data_GY521(&gyro_data_buffer_1, 1.0 / t_diff);
  delta_lowpass_gyro_data = gyro_data_buffer_1;

  center_led.set(true);
  back_led.set(true);

  // negative -> left
  if (delta_lowpass_gyro_data.Roll < -curve_speed_threshold)
  {
    left_led.set(true);
    right_led.set(false);
  }
  // positive -> right
  else if (delta_lowpass_gyro_data.Roll > curve_speed_threshold)
  {
    left_led.set(false);
    right_led.set(true);
  }
  // in center range
  else
  {
    left_led.set(false);
    right_led.set(false);
  }

  // print_float(gyro_data.AccX);
  // print_float(gyro_data.AccY);
  // print_float(gyro_data.AccZ);
  // println_float(sq(gyro_data.AccX) + sq(gyro_data.AccY) + sq(gyro_data.AccZ + 1));

  if (lowpass_gyro_data.AccY > emergency_brake_accl_threshold)
  {
    back_led.setValue(255);
    back_led.blink(250);
  }
  else if (lowpass_gyro_data.AccY > brake_accl_threshold)
  {
    back_led.setValue(255);
  }
  else
  {
    back_led.setValue(40);
  }

  // print_debug();
}

void turnOffLeds()
{
  left_led.set(false);
  center_led.set(false);
  right_led.set(false);
  extra_led.set(false);
  back_led.set(false);
}

void print_float(float value)
{
#ifdef SERIAL_PRINT_DEBUG
  std::ostringstream buf;
  buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << value;
  Serial.print(buf.str().c_str());
#endif
}
void println_float(float value)
{
#ifdef SERIAL_PRINT_DEBUG
  std::ostringstream buf;
  buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << value;
  Serial.println(buf.str().c_str());
#endif
}

void print_debug()
{
#ifdef SERIAL_PRINT_DEBUG
  // delta_lowpass_gyro_data
  String bufferString;
  getDataString_GY521(&delta_lowpass_gyro_data, bufferString);
  // Serial.println(bufferString);
  std::ostringstream buf;
// buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << total_acc_xyz_sq;
// buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << lowpass_gyro_data.AccX;

// buf <<  "\t";
// buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << lowpass_delta_gyro_data.Yaw;

// Serial.println(buf.str().c_str());
#endif
}