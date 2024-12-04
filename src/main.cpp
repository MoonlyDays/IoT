#include <Arduino.h>

#include "drivers/led.h"

#define RED_LED_PIN 2
#define YELLOW_LED_PIN 3
#define GREEN_LED_PIN 4

LED m_Red(RED_LED_PIN);
LED m_Yellow(YELLOW_LED_PIN);
LED m_Green(GREEN_LED_PIN);

enum TrafficLightState
{
    STATE_RED,
    STATE_RED_YELLOW,
    STATE_GREEN,
    STATE_YELLOW,
};

TrafficLightState currentState = STATE_RED;

unsigned long lastStateChangeTime = 0;

const unsigned long RED_DURATION = 5000;
const unsigned long RED_YELLOW_DURATION = 2000;
const unsigned long GREEN_DURATION = 5000;
const unsigned long YELLOW_DURATION = 2000;

void setTrafficLight(TrafficLightState state)
{
    m_Red.turnOff();
    m_Yellow.turnOff();
    m_Green.turnOff();

    switch (state)
    {
    case STATE_RED:
        m_Red.turnOn();
        break;
    case STATE_RED_YELLOW:
        m_Yellow.turnOn();
        break;
    case STATE_GREEN:
        m_Green.turnOn();
        break;
    case STATE_YELLOW:
    m_Yellow.turnOn();
        break;
    }
}

void setup()
{
    setTrafficLight(currentState);
    lastStateChangeTime = millis();
}

void loop()
{
    unsigned long currentTime = millis();

    switch (currentState)
    {
    case STATE_RED:
        if (currentTime - lastStateChangeTime >= RED_DURATION)
        {
            currentState = STATE_RED_YELLOW;
            lastStateChangeTime = currentTime;
            setTrafficLight(currentState);
        }
        break;

    case STATE_RED_YELLOW:
        if (currentTime - lastStateChangeTime >= RED_YELLOW_DURATION)
        {
            currentState = STATE_GREEN;
            lastStateChangeTime = currentTime;
            setTrafficLight(currentState);
        }
        break;

    case STATE_GREEN:
        if (currentTime - lastStateChangeTime >= GREEN_DURATION)
        {
            currentState = STATE_YELLOW;
            lastStateChangeTime = currentTime;
            setTrafficLight(currentState);
        }
        break;

    case STATE_YELLOW:
        if (currentTime - lastStateChangeTime >= YELLOW_DURATION)
        {
            currentState = STATE_RED;
            lastStateChangeTime = currentTime;
            setTrafficLight(currentState);
        }
        break;
    }
}
