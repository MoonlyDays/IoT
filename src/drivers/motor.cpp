#include "motor.h"
#include <Arduino.h>

Motor::Motor(int pinA, int pinB)
{
    m_iPinA = pinA;
    m_iPinB = pinB;

    pinMode(m_iPinA, INPUT);
    pinMode(m_iPinB, INPUT);
}

void Motor::setSpeed(int speed)
{
    speed = constrain(speed, -100, 100);

    analogWrite(m_iPinA, speed > 0 ? map(abs(speed), 0, 100, 0, 0xFF) : 0);
    analogWrite(m_iPinB, speed < 0 ? map(abs(speed), 0, 100, 0, 0xFF) : 0);
}
