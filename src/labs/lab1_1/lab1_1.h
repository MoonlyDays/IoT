#include "drivers/led.h"
#include "labs/lab.h"

#ifndef LAB1_1_H
#define LAB1_1_H

struct Lab1_1 : Lab
{
    Lab1_1();
    void loop() override;

private:
    LED* m_Led;
};

#endif