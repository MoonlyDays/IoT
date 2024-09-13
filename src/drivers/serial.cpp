#include "serial.h"
#include <Arduino.h>

void serial_setup()
{
    static FILE serial_stdout;
    static FILE serial_stdin;
    
    fdev_setup_stream(&serial_stdout,   &serial_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&serial_stdin,    NULL, &serial_getchar, _FDEV_SETUP_READ);

    stdout = &serial_stdout;
    stdin = &serial_stdin;
}

int serial_putchar(char c, FILE* file)
{
    Serial.write(c);
    return c;
}

int serial_getchar(FILE* f)
{
    while( !Serial.available());
    return Serial.read();
}