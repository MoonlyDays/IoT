#include <Arduino.h>
#include "labs/lab2.h"

#define KEYPAD_SIZE 4
char keys[KEYPAD_SIZE][KEYPAD_SIZE] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

byte rowPins[KEYPAD_SIZE] = {5, 4, 3, 2};
byte colPins[KEYPAD_SIZE] = {9, 8, 7, 6};

Lab2::Lab2() 
{
    Serial.begin(9600);

    m_Keypad = new Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_SIZE, KEYPAD_SIZE);
    
    m_LCD = new LiquidCrystal_I2C(0x27, 16, 2);
    m_LCD->init();
    m_LCD->backlight();
}

void Lab2::loop() 
{
    char key = m_Keypad->getKey();
    if (key) {
        Serial.println(key);
    }
}
