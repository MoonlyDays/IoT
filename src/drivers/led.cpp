#include "led.h"
#include <Arduino.h>

LED::LED(int pin)
    : m_iPin(pin)
{
    pinMode(m_iPin, OUTPUT);
}

bool LED::getState()
{
    return digitalRead(m_iPin);
}

void LED::setState(bool state) {
    digitalWrite(m_iPin, state);
}

void LED::turnOn() {
    setState(HIGH);
}

void LED::turnOff() {
    setState(LOW);
}
