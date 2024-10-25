#include <Arduino.h>
#include <Wire.h>
#include "stdio/serial.h"

#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();

    accel.begin();
    accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) 
{
  sensors_event_t event; 
  accel.getEvent(&event);
 
  printf("X: %.2f ", event.acceleration.x);
  printf("Y: %.2f ", event.acceleration.y);
  printf("Z: %.2f ", event.acceleration.z);
  
  delay(500);
}