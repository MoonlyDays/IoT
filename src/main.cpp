#include "labs/lab2_1/lab2_1.h"

#include "Arduino.h"
#include "stdio/serial.h"

void task1(Task *me);
void task2(Task *me);
void task3(Task *me);
void task4(Task *me);

Task m_T1(100, task1);
Task m_T2(400, task2);
Task m_T3(100, task3);
Task m_T4(1000, task4);

LED m_Led1(10);
LED m_Led2(8);
Button m_Button(2);
Potentiometer m_Potentiometer(A1);

bool m_bButtonWasPressed;
void setup()
{
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    serial_use_stdio();

    // Add tasks to the SoftTimer scheduler
    SoftTimer.add(&m_T1);
    SoftTimer.add(&m_T2);
    SoftTimer.add(&m_T3);
    SoftTimer.add(&m_T4);
}

void task1(Task *me)
{
    if (m_Button.pressed())
    {
        m_bButtonWasPressed = true;
        m_Led1.toggle();
    }

    m_Button.rememberState();
}

void task2(Task *me)
{
    if (m_Led1.isOff())
    {
        m_Led2.toggle();
    }
}

void task3(Task *me)
{
    int ms = m_Potentiometer.read();
    ms += map(ms, 0, 1024, 100, 1000);
    m_T2.setPeriodMs(ms);
}

void task4(Task *me)
{
    printf(
        "LED1: %s, LED2: %s\n",
        m_Led1.isOn() ? "ON" : "OFF",
        m_Led1.isOff() ? "ON" : "OFF");

    if (m_bButtonWasPressed)
    {
        m_bButtonWasPressed = false;
        printf("BUTTON WAS PRESSED\n");
    }
}