#include "labs/lab2_2/lab2_2.h"

#include <Arduino.h>
#include "stdio/serial.h"

Lab2_2::Lab2_2()
{
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    serial_use_stdio();

    m_Led1 = new LED(10);
    m_Led2 = new LED(8);
    m_Button = new Button(2);
    m_Potentiometer = new Potentiometer(A1);

    xTaskCreate(
        lab2_2_task1,
        "lab2_2_task1",
        128, NULL,
        2, NULL);

    xTaskCreate(
        lab2_2_task2,
        "lab2_2_task2",
        128, NULL,
        2, NULL);

    xTaskCreate(
        lab2_2_task3,
        "lab2_2_task3",
        128, NULL,
        2, NULL);

    xTaskCreate(
        lab2_2_task4,
        "lab2_2_task4",
        128, NULL,
        2, NULL);
}

void Lab2_2::task1()
{
    while (1)
    {
        if (m_Button->pressed())
        {
            // m_bButtonWasPressed = true;
            m_Led1->toggle();
        }

        m_Button->rememberState();

        vTaskDelay(100);
    }
}

void Lab2_2::task2()
{
    while (1)
    {
        if (m_Led1->isOff())
        {
            m_Led2->toggle();
        }

        vTaskDelay(100);
    }
}

void Lab2_2::task3()
{
    while (1)
    {
        int ms = m_Potentiometer->read();
        ms += map(ms, 0, 1024, 100, 1000);

        vTaskDelay(100);
    }
}

void Lab2_2::task4()
{
    while (1)
    {
        printf(
            "LED1: %s, LED2: %s\n",
            m_Led1->isOn() ? "ON" : "OFF",
            m_Led1->isOff() ? "ON" : "OFF");

        vTaskDelay(100);
    }
}