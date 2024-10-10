#ifndef LAB2_1_H
#define LAB2_1_H

#include "util/labs.h"
#include <SoftTimer.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

struct Lab2_1 : Lab
{
    Lab2_1();

    Task* m_T1;
    Task* m_T2;
    Task* m_T3;
    Task* m_T4;

    LED* m_Led1;
    LED* m_Led2;
    Button* m_Button;
    Potentiometer* m_Potentiometer;

    bool m_bButtonWasPressed;

    void task1();
    void task2();
    void task3();
    void task4();
};

void lab2_1_task1(Task* me);
void lab2_1_task2(Task* me);
void lab2_1_task3(Task* me);
void lab2_1_task4(Task* me);

#endif