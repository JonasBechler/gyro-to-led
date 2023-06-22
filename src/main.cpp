// lets start
// main controller for esp32 to controll 4 lights with the gy521 and turns on when a theshold is detectetd (floating average 1-10s?)
// Kondesnatoren und stepdown?

#include "../gyro/GY521_Handler.h"
#include "../analog_pin/Analog_Pin.h"
#include "../led/Led_Handler.h"

//library für analog machen? :)
//library für 4 leds machen? :(

//TODO: correct pins
#define LeftLedPin 5
#define RightLedPin 5
#define TopLedPin 5
#define BottomLedPin 5

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

