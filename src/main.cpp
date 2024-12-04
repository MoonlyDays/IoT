#include <Arduino.h>

#include "drivers/button.h"
#include "stdio/serial.h"

#define BUTTON_PIN 2

enum State
{
    STATE_IDLE,
    STATE_SHORT_PRESS,
    STATE_LONG_PRESS,
    STATE_RELEASED,
    STATE_DOUBLE_PRESS
};

Button m_Button(BUTTON_PIN);

State currentState = STATE_IDLE;
unsigned long lastPressTime = 0;
unsigned long buttonHoldTime = 0;
bool lastButtonState = LOW;
unsigned long doublePressTimeout = 300;
unsigned long longPressThreshold = 1000;
unsigned long lastReleaseTime = 0;

void setup()
{
    stdio_to_serial(9600);
}

void loop()
{
    bool buttonState = m_Button.down();

    switch (currentState)
    {
    case STATE_IDLE:
        if (buttonState)
        {
            currentState = STATE_SHORT_PRESS;
            lastPressTime = millis();
            printf("STATE_SHORT_PRESS\n");
        }
        break;

    case STATE_SHORT_PRESS:
        if (buttonState)
        {
            buttonHoldTime = millis() - lastPressTime;
            if (buttonHoldTime > longPressThreshold)
            {
                currentState = STATE_LONG_PRESS;
                printf("STATE_LONG_PRESS\n");
            }
        }
        else
        {
            lastReleaseTime = millis();
            if (millis() - lastPressTime < longPressThreshold)
            {
                currentState = STATE_RELEASED;
                printf("STATE_RELEASED\n");
            }
        }
        break;

    case STATE_LONG_PRESS:
        if (!buttonState)
        {
            currentState = STATE_IDLE;
            printf("STATE_IDLE\n");
        }
        break;

    case STATE_RELEASED:
        if (buttonState && (millis() - lastReleaseTime < doublePressTimeout))
        {
            currentState = STATE_DOUBLE_PRESS;
            printf("STATE_DOUBLE_PRESS\n");
        }
        else if (millis() - lastReleaseTime >= doublePressTimeout)
        {
            currentState = STATE_IDLE;
            printf("STATE_IDLE\n");
        }
        break;

    case STATE_DOUBLE_PRESS:
        if (!buttonState)
        {
            currentState = STATE_IDLE;
            printf("STATE_IDLE\n");
        }
        break;
    }

    delay(10);
}
