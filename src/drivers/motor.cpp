#include "motor.h"
#include <Arduino.h>

Motor::Motor(int pinA, int pinB)
{
    m_iPinA = pinA;
    m_iPinB = pinB;

    pinMode(m_iPinA, INPUT);
    pinMode(m_iPinB, INPUT);
}