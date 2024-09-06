#include "button.h"
#include <Arduino.h>

void button_setup()
{
    pinMode(PIN_BUTTON, INPUT);
}

void button_pullup() 
{
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

int button_pressed() 
{
    return digitalRead(PIN_BUTTON);
}