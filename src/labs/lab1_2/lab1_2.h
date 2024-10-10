#ifndef LAB1_2_H
#define LAB1_2_H

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#include "util/labs.h"
#include "drivers/led.h"

#define KEYPAD_SIZE 4
#define PASSWORD "14BA"

struct Lab1_2 : Lab
{
    Lab1_2();
    void loop() override;

private:
    char m_vKeys[KEYPAD_SIZE][KEYPAD_SIZE] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '=', 'D'},
    };
    
    byte m_rowPins[KEYPAD_SIZE] = {5, 4, 3, 2};
    byte m_colPins[KEYPAD_SIZE] = {9, 8, 7, 6};

    Keypad* m_Keypad;
    LiquidCrystal_I2C* m_LCD;
    
    LED* m_LEDOn;
    LED* m_LEDOff;
    
    char m_szCode[16];
    int m_nLength;
};

#endif