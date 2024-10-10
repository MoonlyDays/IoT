#include "labs/lab2_1/lab2_1.h"

#include "Arduino.h"
#include "stdio/serial.h"

Lab2_1::Lab2_1()
{
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    serial_use_stdio();

    m_Led1 = new LED(10);
    m_Led2 = new LED(8);
    m_Button = new Button(2);
    m_Potentiometer = new Potentiometer(A1);

    m_T1 = new Task(100, lab2_1_task1);
    m_T2 = new Task(400, lab2_1_task2);
    m_T3 = new Task(100, lab2_1_task3);
    m_T4 = new Task(1000, lab2_1_task4);

    // Add tasks to the SoftTimer scheduler
    SoftTimer.add(m_T1);
    SoftTimer.add(m_T2);
    SoftTimer.add(m_T3);
    SoftTimer.add(m_T4);
}

void Lab2_1::task1()
{
    if (m_Button->pressed())
    {
        m_bButtonWasPressed = true;
        m_Led1->toggle();
    }

    m_Button->rememberState();
}

void Lab2_1::task2()
{
    if (m_Led1->isOff())
    {
        m_Led2->toggle();
    }
}

void Lab2_1::task3()
{
    int ms = m_Potentiometer->read();
    ms += map(ms, 0, 1024, 100, 1000);
    m_T2->setPeriodMs(ms);
}

void Lab2_1::task4()
{
    printf(
        "LED1: %s, LED2: %s\n",
        m_Led1->isOn() ? "ON" : "OFF",
        m_Led1->isOff() ? "ON" : "OFF");

    if (m_bButtonWasPressed)
    {
        m_bButtonWasPressed = false;
        printf("BUTTON WAS PRESSED\n");
    }
}

void lab2_1_task1(Task* me) {
    static_cast<Lab2_1*>(current)->task1();
}

void lab2_1_task2(Task* me) {
    static_cast<Lab2_1*>(current)->task2();
}

void lab2_1_task3(Task* me) {
    static_cast<Lab2_1*>(current)->task3();
}

void lab2_1_task4(Task* me) {
    static_cast<Lab2_1*>(current)->task4();
}