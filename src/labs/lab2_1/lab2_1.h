#include "drivers/led.h"
#include "drivers/button.h"
#include "labs/lab.h"

#ifndef LAB2_1_H
#define LAB2_1_H

struct Lab2_1 : Lab
{
    Lab2_1();
    void loop() override;

private:
    void task1();
    void task2();
    void task3();

    LED* m_Led1;
    LED* m_Led2;
    Button* m_Button;
};

#endif