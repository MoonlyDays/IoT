#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "labs/lab1_2/lab1_2.h"

#define KEYPAD_SIZE 4
char keys[KEYPAD_SIZE][KEYPAD_SIZE] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '=', 'D'},
};

byte rowPins[KEYPAD_SIZE] = {5, 4, 3, 2};
byte colPins[KEYPAD_SIZE] = {9, 8, 7, 6};

Keypad m_Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_SIZE, KEYPAD_SIZE);
LiquidCrystal_I2C m_LCD(0x27, 16, 2);

LED m_LEDOn(12);
LED m_LEDOff(13);

char m_szCode[16] = "";
int m_nLength = 0;

void lab1_2_setup() 
{
    Serial.begin(9600);
    
    m_LCD.init();
    m_LCD.backlight();
    m_LCD.setCursor(0, 0);

    m_LEDOff.turnOn();
}

void lab1_2_loop() 
{
    char key = m_Keypad.getKey();
    if (! key) {
        return;
    }

    if(key == '*') {
        m_LCD.clear();
        m_LCD.setCursor(0, 0);

        m_nLength = 0;
        for(int i = 0; i < 16; i++) {
            m_szCode[i] = '\0';
        }

    } else {
        if(m_nLength < 16) {
            m_nLength++;
            m_szCode[strlen(m_szCode)] = key;
        }
    }

    m_LCD.clear();
    m_LCD.setCursor(0, 0);
    m_LCD.print(m_szCode);

    bool success = strcmp(m_szCode, "14BA") != 0;
    m_LEDOn.setState(success);
    m_LEDOff.setState(! success);
}
