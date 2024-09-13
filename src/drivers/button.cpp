#include "button.h"
#include <Arduino.h>

Button::Button(int pin) 
{
    m_iPin = pin;
    pinMode(m_iPin, INPUT);
}

void Button::pullup()
{
    pinMode(m_iPin, INPUT_PULLUP);
}

bool Button::pressed()
{
    return digitalRead(m_iPin) == LOW;
}