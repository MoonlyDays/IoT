#include <Arduino.h>
#include <HCSR04.h>

#include "stdio/serial.h"
#include "filters/sap.h"
#include "filters/avg.h"

#define PIN1 9
#define PIN2 10
#define TEMP 20.0

UltraSonicDistanceSensor m_DistanceSensor(PIN1, PIN2);
SATFilter m_SATFilter;
AVGFilter m_AVGFilter;

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();
}

void loop(void) 
{
    double fDistance = m_DistanceSensor.measureDistanceCm(TEMP);
    m_SATFilter.push(fDistance);
    m_AVGFilter.push(fDistance);

    m_SATFilter.m_bFilled
        ? printf("SAT> Filtered: %.2f", m_SATFilter.output())
        : printf("SAT> Collecting data...");

    m_AVGFilter.m_bFilled
        ? printf("AVG> Filtered: %.2f", m_AVGFilter.output())
        : printf("AVG> Collecting data...");
}