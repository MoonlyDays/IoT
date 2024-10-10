#include "button.h"
#include <Arduino.h>

Button::Button(int pin)
{
    m_iPin = pin;
    pinMode(m_iPin, INPUT);
}

/**
 * Check if the Button is currently down?
 */
bool Button::down()
{
    return digitalRead(m_iPin) == HIGH;
}

/**
 * Check if the Button is currently up?
 */
bool Button::up()
{
    return !down();
}

/**
 * Check if the Button was just pressed?
 */
bool Button::pressed()
{
    return !m_bWasPressed && down();
}

/**
 * Check if the Button was just released?
 */
bool Button::released()
{
    return m_bWasPressed && !down();
}

/**
 * This needs to be called after every loop to allow ->pressed() and ->released() methods to work correctly.
 */
void Button::rememberState()
{
    m_bWasPressed = down();
}