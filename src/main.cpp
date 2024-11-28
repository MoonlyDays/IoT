#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "util/prompts.h"
#include "stdio/serial.h"
#include "drivers/relay.h"
#include "drivers/led.h"

#define LCD_COLS 20
#define LCD_ROWS 4

#define RELAY_PIN 7

Relay m_Relay(RELAY_PIN);
LiquidCrystal_I2C m_LCD(0x27, LCD_COLS, LCD_ROWS);

void setup()
{
    stdio_to_serial(9600);
    stdio_to_lcd(&m_LCD);
}

void loop()
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    printf("Command: %s\n", buf);

    if (strcmp(buf, "RELAY ON") == 0)
    {
        printf("Turning the RELAY on...\n");
        m_Relay.turnOn();
        return;
    }

    if (strcmp(buf, "RELAY OFF") == 0)
    {
        printf("Turning the RELAY off...\n");
        m_Relay.turnOff();
        return;
    }

    printf("Invalid command \"%s\".\n", buf);
}