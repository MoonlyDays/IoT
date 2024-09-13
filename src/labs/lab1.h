#include "drivers/led.h"
#include "labs/lab.h"

#ifndef LAB1_H
#define LAB1_H

struct Lab1 : Lab
{
    Lab1();
    void loop() override;

private:
    LED* m_Led;
};

#endif