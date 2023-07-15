// lets start
// main controller for esp32 to controll 4 lights with the gy521 and turns on when a theshold is detectetd (floating average 1-10s?)
// Kondesnatoren und stepdown?

#include "../GY521_Handler/GY521_Handler.h"
#include "../analog_pin/Analog_Pin.h"
#include "../led/Led_Handler.h"
#include "../filter/Low_Pass_Filter.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


// Leds
int delay_duration = 1000;
Led_Handler left_led(25, 100, delay_duration);
Led_Handler center_led(26, 100, delay_duration);
Led_Handler right_led(27, 100, delay_duration);
Led_Handler extra_led(14, 100, delay_duration);
Led_Handler back_led(12, 100, delay_duration);



// Gyro
GY521 gyro(0x68);
Data_GY521 gyro_data;
Data_GY521 gyro_data_old;
Data_GY521 delta_gyro_data;
Data_GY521 lowpass_delta_gyro_data;
float lowpass_value = 0.99;

unsigned long t_now = 0;
unsigned long t_last = 0;
int t_diff = 0;

float curve_speed_theshold = 0.01;
float break_accl_theshold = 0.1;


// Photoresistor
Analog_Pin photo_resistor(32);
Low_Pass photo_resistor_lowpass(0.9);

float day_night_theshold = 4000.0;

void processLeds();





void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);


  Wire.begin();
  delay(100);
  init_GY521(&gyro);

  photo_resistor.init();
  photo_resistor_lowpass.start(photo_resistor.getValue());



  delay(10);
  gyro.read();
  setData_GY521(&gyro, &gyro_data);
  gyro_data_old = gyro_data;


  left_led.setValue(255);
  center_led.setValue(255);
  right_led.setValue(255);
  extra_led.setValue(0);
  back_led.setValue(100);

  delay(1000);

}


void loop() {
  photo_resistor.update();
  photo_resistor_lowpass.next(photo_resistor.getValue());
  //Serial.println(photo_resistor_lowpass.get());

  if (photo_resistor.getValue() < day_night_theshold) {
    processLeds();
  }
  else{
    left_led.set(false);
    center_led.set(false);
    right_led.set(false);
    extra_led.set(false);
    back_led.set(false);
  }

  delay(200);
}



void processLeds() {
  gyro_data_old = gyro_data;

  gyro.read();
  // capture time difference
  t_now = millis();
  t_diff = t_now - t_last;
  t_last = t_now;


  setData_GY521(&gyro, &gyro_data);
  check_over_under_flow(&gyro_data, &gyro_data_old);
  
  

  // delta_gyro_data = (gyro_data - gyro_data_old) / t_diff
  delta_gyro_data = gyro_data_old;
  neg_Data_GY521(&delta_gyro_data);
  add_Data_GY521(&delta_gyro_data, &gyro_data);
  mult_Data_GY521(&delta_gyro_data, 1.0 / t_diff);
  //Serial.println(t_diff);

  
  // lowpass_delta_gyro_data = lowpass_delta_gyro_data * lowpass_value + delta_gyro_data * (1 - lowpass_value)
  mult_Data_GY521(&lowpass_delta_gyro_data, lowpass_value);
  mult_Data_GY521(&delta_gyro_data, 1.0 - lowpass_value);
  add_Data_GY521(&lowpass_delta_gyro_data, &delta_gyro_data);

  center_led.set(true);
  back_led.set(true);


  // negative -> left
  if (lowpass_delta_gyro_data.Yaw < -curve_speed_theshold)
  {
    left_led.set(true);
    right_led.set(false);
  }
  // positive -> right
  else if (lowpass_delta_gyro_data.Yaw > curve_speed_theshold)
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

  if (lowpass_delta_gyro_data.AccX < -break_accl_theshold) {
    back_led.setValue(255);
  }



  //delta_lowpass_gyro_data
  String bufferString;
  getDataString_GY521(&lowpass_delta_gyro_data, bufferString);
  //Serial.println(bufferString);
  std::ostringstream buf;
  buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << gyro_data.AccY;
  //buf <<  "\t";
  //buf << std::fixed << std::setw(10) << std::setfill(' ') << std::setprecision(6) << lowpass_delta_gyro_data.Yaw;

  Serial.println(buf.str().c_str());
}