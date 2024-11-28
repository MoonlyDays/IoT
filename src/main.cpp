#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "stdio/serial.h"
#include "util/prompts.h"
#include "drivers/motor.h"

#define ENA 8
#define IN1 7
#define IN2 6

LiquidCrystal_I2C m_LCD(0x27, 20, 4);
Motor m_Motor(ENA, IN1, IN2);

void setup()
{
    stdio_to_serial(9600);
    stdio_to_lcd(&m_LCD);

    m_LCD.init();
    m_LCD.backlight();
}

void loop()
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    printf("Command: %s\n", buf);

    char *token = strtok(buf, " ");
    if (token && strcmp(token, "SPEED") == 0)
    {
        token = strtok(NULL, buf);
        int speed = atoi(token);

        if(speed < -100)  speed = -100;
        if(speed > 100)   speed = 100;

        m_Motor.setSpeed(speed);

        printf("Changing MOTOR speed to %d\n", speed);
        return;
    }

    printf("Invalid command \"%s\".\n", buf); 
}