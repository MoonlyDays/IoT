#include <Arduino.h>

#include "drivers/relay.h"
#include "drivers/motor.h"
#include "drivers/potentiometer.h"

#define MOTOR_PINA A2
#define MOTOR_PINB A3
#define PMETER_PIN A4

Potentiometer m_Potentiometer(PMETER_PIN);
Motor m_Motor(MOTOR_PINA, MOTOR_PINB);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int value = m_Potentiometer.read();
    int power = map(value, 0, 1023, -100, 100);
    m_Motor.setSpeed(power);
}