// lets start
// main controller for esp32 to controll 4 lights with the gy521 and turns on when a theshold is detectetd (floating average 1-10s?)
// Kondesnatoren und stepdown?

#include "../gyro/GY521_Handler.h"
#include "../analog_pin/Analog_Pin.h"
#include "../led/Led_Handler.h"


// Leds
Led_Handler left_led(5, 100);
Led_Handler right_led(5, 100);
Led_Handler top_led(5, 100);
Led_Handler bottom_led(5, 100);

// Gyro
GY521 gyro(0x68);
Data_GY521 gyro_data;

// Photoresistor
Analog_Pin_Config photo_resistor_config = {
    5,                          // pin
    Smoothing_Method::low_pass, // smoothing_method
    0.1f,                       // low_pass_value
    5                           // floating_avg_size
};

Analog_Pin photo_resistor(&photo_resistor_config);






void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);

  photo_resistor.init();


}

void loop() {
  photo_resistor.update();

}

