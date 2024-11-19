#include <Arduino.h>

#include "drivers/relay.h"
#include "drivers/motor.h"

#define RELAY_PIN 7
#define MOTOR_PINA 5
#define MOTOR_PINB 6

Relay m_Relay(RELAY_PIN);
Motor m_Motor(MOTOR_PINA, MOTOR_PINB);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available())
    {
        char cmd = Serial.read();
        if (cmd == '1')
        {
            m_Relay.turnOn();
        }

        if (cmd == '0')
        {
            m_Relay.turnOff();
        }
    }
}