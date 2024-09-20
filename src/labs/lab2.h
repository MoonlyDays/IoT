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
    void UpdateLEDState();

    Keypad* m_Keypad;
    LiquidCrystal_I2C* m_LCD;

    LED* m_OnLED;
    LED* m_OffLED;

    char m_szCode[16] = "";
    int m_nLength = 0;
};

#endif