#include <Arduino.h>
#include "labs/lab2.h"

#define KEYPAD_SIZE 4
char keys[KEYPAD_SIZE][KEYPAD_SIZE] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '=', 'D'},
};

byte rowPins[KEYPAD_SIZE] = {5, 4, 3, 2};
byte colPins[KEYPAD_SIZE] = {9, 8, 7, 6};
bool dick = false;

byte customChar[] = {
  B00100,
  B01010,
  B01110,
  B01010,
  B01010,
  B01010,
  B10101,
  B11011
};

Lab2::Lab2() 
{
    Serial.begin(9600);

    m_Keypad = new Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_SIZE, KEYPAD_SIZE);
    
    m_LCD = new LiquidCrystal_I2C(0x27, 16, 2);
    m_LCD->init();
    m_LCD->backlight();
    m_LCD->setCursor(0, 0);
    m_LCD->createChar(0, customChar);

    m_OnLED = new LED(12);
    m_OffLED = new LED(13);
    m_OffLED->turnOn();
}

void Lab2::loop() 
{
    char key = m_Keypad->getKey();
    if (key) {
        if(key == '*') {
            m_LCD->clear();
            m_LCD->setCursor(0, 0);

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

        if(strcmp(m_szCode, "CD") == 0) {
            m_nLength = 0;
            for(int i = 0; i < 16; i++) {
                m_szCode[i] = '\0';
            }

            dick = ! dick;
        }

        m_LCD->clear();
        m_LCD->setCursor(0, 0);

        if(dick) {
            for(int j = 0; j < m_nLength; j++) {
                m_LCD->write(byte(0));
            }
        } else {
            m_LCD->print(m_szCode);
        }

        bool success = strcmp(m_szCode, "14BA") != 0;
        m_OnLED->setState(success);
        m_OffLED->setState(! success);
    }
}
