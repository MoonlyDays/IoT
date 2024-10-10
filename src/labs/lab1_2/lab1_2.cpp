#include "labs/lab1_2/lab1_2.h"

#include <Arduino.h>

Lab1_2::Lab1_2()
{
    Serial.begin(9600);
    
    m_Keypad = new Keypad(makeKeymap(m_vKeys), m_rowPins, m_colPins, KEYPAD_SIZE, KEYPAD_SIZE);

    m_LCD = new LiquidCrystal_I2C(0x27, 16, 2);
    m_LCD->init();
    m_LCD->backlight();
    m_LCD->setCursor(0, 0);

    m_LEDOn = new LED(12);
    m_LEDOff = new LED(13);

    m_LEDOff->turnOn();
}

void Lab1_2::loop()
{
    char key = m_Keypad->getKey();

    if (! key)
    {
        return;
    }

    // If the '*' key is pressed, reset the code entry
    if (key == '*')
    {
        // Clear the LCD screen
        m_LCD->clear();
        // Set the cursor to the beginning of the first row
        m_LCD->setCursor(0, 0);
        // Reset the length of the code entered to 0
        m_nLength = 0;

        // Clear the code buffer by setting all characters to the null character
        for (int i = 0; i < 16; i++)
        {
            m_szCode[i] = '\0';
        }
    }
    else
    {
        // If a key other than '*' is pressed and the code length is less than 16
        if (m_nLength < 16)
        {
            // Increment the code length
            m_nLength++;
            // Add the key pressed to the code array
            m_szCode[strlen(m_szCode)] = key;
        }
    }

    // Clear the LCD screen
    m_LCD->clear();
    // Set the cursor to the beginning of the first row
    m_LCD->setCursor(0, 0);
    // Display the current code entered on the LCD screen
    m_LCD->print(m_szCode);
    // Check if the code entered matches "14BA"
    bool success = strcmp(m_szCode, PASSWORD) != 0;

    // Set the LED state: if the code is correct, turn on m_LEDOn, otherwise m_LEDOff
    m_LEDOn->setState(success);
    m_LEDOff->setState(!success);
}
