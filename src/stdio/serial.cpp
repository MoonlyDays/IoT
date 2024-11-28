#include "serial.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C *__lcd;

int __serial_putchar(char c, FILE *file)
{
    Serial.write(c);
    return c;
}

int __serial_getchar(FILE *f)
{
    while (!Serial.available())
        ;
    return Serial.read();
}

void stdio_to_serial(unsigned long baud)
{
    Serial.begin(baud);

    static FILE m_STDOUT;
    static FILE m_STDIN;

    fdev_setup_stream(&m_STDIN, NULL, __serial_getchar, _FDEV_SETUP_READ);
    fdev_setup_stream(&m_STDOUT, __serial_putchar, NULL, _FDEV_SETUP_WRITE);

    stdout = &m_STDOUT;
    stdin = &m_STDIN;
}

int __lcd_putchar(char c, FILE *file)
{
    __lcd->write(c);
}

void stdio_to_lcd(LiquidCrystal_I2C *lcd)
{
    __lcd = lcd;
    static FILE m_STDOUT;
    fdev_setup_stream(&m_STDOUT, __lcd_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &m_STDOUT;
}

void setup_stdio(
    int (*__getchar)(FILE *),
    int (*__putchar)(char, FILE *))
{
    static FILE m_STDOUT;
    static FILE m_STDIN;

    fdev_setup_stream(&m_STDIN, NULL, __getchar, _FDEV_SETUP_READ);
    fdev_setup_stream(&m_STDOUT, __putchar, NULL, _FDEV_SETUP_WRITE);

    stdout = &m_STDOUT;
    stdin = &m_STDIN;
}