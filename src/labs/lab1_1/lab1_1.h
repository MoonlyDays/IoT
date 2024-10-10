#ifndef LAB1_1_H
#define LAB1_1_H

#include "util/labs.h"
#include "drivers/led.h"

struct Lab1_1 : Lab
{
    Lab1_1();
    void loop() override;
    
    LED* m_Led;
};

#endif