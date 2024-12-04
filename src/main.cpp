#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#include "stdio/serial.h"
#include "drivers/potentiometer.h"
#include "drivers/relay.h"

#define POTENTIOMETER_PIN A1
#define RELAY_PIN 3
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define HYSTERESIS 1.0

Relay m_Relay(RELAY_PIN);
DHT m_DHT(DHT_PIN, DHT_TYPE);
Potentiometer m_Potentiometer(POTENTIOMETER_PIN);
LiquidCrystal_I2C m_LCD(0x20, 20, 4);

float setPoint = 25.0;
float currentTemperature = 0;
bool relayState = false;

void setup()
{
    stdio_to_serial(9600);
    stdio_to_lcd(&m_LCD);
    m_DHT.begin();

    m_LCD.init();
    m_LCD.backlight();
    m_LCD.setCursor(0, 0);

    m_Relay.turnOff();
}

void loop()
{
    currentTemperature = m_DHT.readTemperature();

    int potValue = m_Potentiometer.read();
    potValue = map(potValue, 0, 1024, 10, 35);

    if (currentTemperature < setPoint - HYSTERESIS)
        relayState = true;
    else if (currentTemperature > setPoint + HYSTERESIS)
        relayState = false;

    m_Relay.setState(relayState);
    printf(
        "Temp: %d | SetPoint: %d | Relay: %s",
        currentTemperature, potValue, relayState ? "ON" : "OFF");

    delay(2000);
}
