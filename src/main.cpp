// lets start
// main controller for esp32 to controll 4 lights with the gy521 and turns on when a theshold is detectetd (floating average 1-10s?)
// Kondesnatoren und stepdown?

#include "../GY521_Handler/GY521_Handler.h"
//#include "../analog_pin/Analog_Pin.h"
//#include "../led/Led_Handler.h"


// Leds
/*
Led_Handler left_led(5, 100);
Led_Handler right_led(5, 100);
Led_Handler top_led(5, 100);
Led_Handler bottom_led(5, 100);
*/

// Gyro
GY521 gyro(0x68);
Data_GY521 gyro_data;
Data_GY521 delta_gyro_data;
Data_GY521 gyro_data_old;
Data_GY521 lowpass_gyro_data;
Data_GY521 lowpass_gyro_data_old;
Data_GY521 delta_lowpass_gyro_data;
float lowpass_value = 0.75;

unsigned long t_now = 0;
unsigned long t_last = 0;
int t_diff = 0;


// Photoresistor
/*
Analog_Pin_Config photo_resistor_config = {
    5,                          // pin
    Smoothing_Method::low_pass, // smoothing_method
    0.1f,                       // low_pass_value
    5                           // floating_avg_size
};

Analog_Pin photo_resistor(&photo_resistor_config);
*/

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  //photo_resistor.init();
  Wire.begin();
  delay(100);
  init_GY521(&gyro);
  gyro.read();
  setData_GY521(&gyro, &gyro_data);
  gyro_data_old = gyro_data;
  lowpass_gyro_data = gyro_data;
  lowpass_gyro_data_old = gyro_data;

}


void loop() {
  //photo_resistor.update();

  gyro_data_old = gyro_data;
  lowpass_gyro_data_old = lowpass_gyro_data;

  gyro.read();
  // capture time difference
  t_now = millis();
  t_diff = t_now - t_last;
  t_last = t_now;


  setData_GY521(&gyro, &gyro_data);

  check_over_under_flow(&gyro_data, &gyro_data_old);
  
  /*
  // lowpass_gyro_data = lowpass_gyro_data * lowpass_value + gyro_data * (1 - lowpass_value)
  mult_Data_GY521(&lowpass_gyro_data, lowpass_value);
  mult_Data_GY521(&gyro_data, 1.0 - lowpass_value);
  add_Data_GY521(&lowpass_gyro_data, &gyro_data);

  check_over_under_flow(&lowpass_gyro_data, &lowpass_gyro_data_old);
  */

  // delta_gyro_data = (gyro_data - gyro_data_old) / t_diff
  delta_gyro_data = gyro_data_old;
  neg_Data_GY521(&delta_gyro_data);
  add_Data_GY521(&delta_gyro_data, &gyro_data);
  mult_Data_GY521(&delta_gyro_data, 1.0 / t_diff);
  //Serial.println(t_diff);

  //delta_lowpass_gyro_data
  String bufferString;
  getDataString_GY521(&delta_gyro_data, bufferString);
  Serial.println(bufferString);

  delay(10);

}



