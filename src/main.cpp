// lets start
// main controller for esp32 to controll 4 lights with the gy521 and turns on when a theshold is detectetd (floating average 1-10s?)
// Kondesnatoren und stepdown?

#include "../GY521_Handler/GY521_Handler.h"
#include "../analog_pin/Analog_Pin.h"
#include "../led/Led_Handler.h"
#include "../filter/Low_Pass_Filter.h"


// Leds
Led_Handler left_led(25, 255);
Led_Handler center_led(26, 255);
Led_Handler right_led(27, 255);


// Gyro
GY521 gyro(0x68);
Data_GY521 gyro_data;
Data_GY521 gyro_data_old;
Data_GY521 delta_gyro_data;
Data_GY521 lowpass_delta_gyro_data;
float lowpass_value = 0.75;

unsigned long t_now = 0;
unsigned long t_last = 0;
int t_diff = 0;

float curve_speed_theshold = 0.005;


// Photoresistor
Analog_Pin photo_resistor(5);
Low_Pass photo_resistor_lowpass(0.98);


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  left_led.setValue(255);
  center_led.setValue(255);
  right_led.setValue(255);

  Wire.begin();
  delay(100);
  init_GY521(&gyro);

  photo_resistor.init();
  photo_resistor_lowpass.start(photo_resistor.getState());



  delay(10);
  gyro.read();
  setData_GY521(&gyro, &gyro_data);
  gyro_data_old = gyro_data;

}


void loop() {
  photo_resistor.update();
  photo_resistor_lowpass.next(photo_resistor.getState());

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

  // negative -> right
  if (lowpass_delta_gyro_data.Yaw < -curve_speed_theshold)
  {
    left_led.set(false);
    right_led.set(true);
  }
  // positive -> left
  else if (lowpass_delta_gyro_data.Yaw > curve_speed_theshold)
  {
    left_led.set(true);
    right_led.set(false);
  }
  // in center range
  else
  {
    left_led.set(false);
    right_led.set(false);
  }



  //delta_lowpass_gyro_data
  String bufferString;
  getDataString_GY521(&lowpass_delta_gyro_data, bufferString);
  Serial.println(bufferString);

  delay(10);

}



