#include <Arduino.h>
#include <HCSR04.h>

#include "stdio/serial.h"
#include "filters/sap.h"
#include "filters/avg.h"

#define LCD_COLS 20
#define LCD_ROWS 4
#define USS_PIN1 9
#define USS_PIN2 10
#define TEMPERATURE 20.0

LiquidCrystal_I2C m_LCD(0x27, LCD_COLS, LCD_ROWS);
UltraSonicDistanceSensor m_DistanceSensor(USS_PIN1, USS_PIN2);

SATFilter m_SATFilter;
AVGFilter m_AVGFilter;

void setup()
{
    stdio_to_lcd(&m_LCD);
}

void loop(void) 
{
    double fDistance = m_DistanceSensor.measureDistanceCm(TEMPERATURE);
    m_SATFilter.push(fDistance);
    m_AVGFilter.push(fDistance);

    printf("| R: %.2f | ", fDistance);

    m_SATFilter.m_bFilled
        ? printf("F1: %.2f | ", m_SATFilter.output())
        : printf("F1:  ~~  | ");

    m_AVGFilter.m_bFilled
        ? printf("F2: %.2f | ", m_AVGFilter.output())
        : printf("F2:  ~~  | ");

    printf("\n");
}