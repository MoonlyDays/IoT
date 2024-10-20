#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#include "stdio/serial.h"
#include "util/macro.h"

#define PIN 8
#define TYPE DHT11

DHT_Unified dht(PIN, TYPE);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();
    dht.begin();
}

void loop()
{
    delay(1000);

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float fTemp = event.temperature;
    dht.humidity().getEvent(&event);
    float fHum = event.relative_humidity;
    if (isnan(fTemp) || isnan(fHum))
    {
        printf("Error reading temperature!\n");
        return;
    }

    printf("Temp = %d C, Humidity = %d %%\n", R(fTemp), R(fHum));
}