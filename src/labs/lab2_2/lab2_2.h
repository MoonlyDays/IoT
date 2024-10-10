#ifndef LAB2_2_H
#define LAB2_2_H

#include "util/labs.h"

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

struct Lab2_2 : Lab
{
    Lab2_2();

    LED *m_Led1;
    LED *m_Led2;
    Button *m_Button;
    Potentiometer *m_Potentiometer;

    QueueHandle_t m_xButtonWasPressed = xSemaphoreCreateBinary();

    void task1();
    void task2();
    void task3();
    void task4();
};

void lab2_2_task1(void *arg);
void lab2_2_task2(void *arg);
void lab2_2_task3(void *arg);
void lab2_2_task4(void *arg);

#endif