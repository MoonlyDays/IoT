#include <Arduino.h>
#include <L298N.h>

#include "stdio/serial.h"
#include "util/prompts.h"
#include "drivers/relay.h"
#include "drivers/potentiometer.h"

#define LCD_COLS 20
#define LCD_ROWS 4
#define MOTOR_PIN1 7
#define MOTOR_PIN2 8

LiquidCrystal_I2C m_LCD(0x27, LCD_COLS, LCD_ROWS);
L298N m_Motor(MOTOR_PIN1, MOTOR_PIN2);

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

        speed = map(speed, -100, 100, 0, 0xFF);
        m_Motor.setSpeed(speed);

        printf("Changing MOTOR speed to %d\n", speed);
        return;
    }

    printf("Invalid command \"%s\".\n", buf); 
}