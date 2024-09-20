#ifndef LAB2_H
#define LAB2_H

#include "drivers/led.h"
#include "labs/lab.h"
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

struct Lab2 : Lab
{
    Lab2();
    void loop() override;

private:
    Keypad* m_Keypad;
    LiquidCrystal_I2C* m_LCD;
};

#endif