#include "serial.h"
#include <Arduino.h>

int __serial_putchar(char c, FILE* file)
{
    Serial.write(c);
    return c;
}

int __serial_getchar(FILE* f)
{
    while( !Serial.available());
    int c = Serial.read();

    if(c == 8) {
        printf("\b \b");
        return c;
    }

    printf("%c", c);
    return c;
}

void serial_use_stdio()
{
    static FILE m_STDOUT;
    static FILE m_STDIN;

    fdev_setup_stream(&m_STDOUT,   &__serial_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&m_STDIN,    NULL, &__serial_getchar, _FDEV_SETUP_READ);

    stdout = &m_STDOUT;
    stdin = &m_STDIN;
}