#include "potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin)
    : m_iPin(pin)
{
    pinMode(m_iPin, INPUT);
}

int Potentiometer::read()
{
    return analogRead(m_iPin);
}