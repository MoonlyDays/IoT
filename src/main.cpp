#include <Arduino.h>
#include <HCSR04.h>

#include "stdio/serial.h"

UltraSonicDistanceSensor m_DistanceSensor(9, 10);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();
}

void loop()
{
    double fDistance = m_DistanceSensor.measureDistanceCm(25.0);
    int iDistance = (int)round(fDistance);
    printf("%d cm\n", iDistance);
    delay(200);
}