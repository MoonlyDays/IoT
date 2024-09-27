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

bool Button::down()
{
    return digitalRead(m_iPin) == HIGH;
}

bool Button::up()
{
    return !down();
}

bool Button::pressed()
{
    return !m_bWasPressed && down();
}

bool Button::released()
{
    return m_bWasPressed && !down();
}

void Button::rememberState()
{
    m_bWasPressed = down();
}