#include <stdio.h>

#ifndef SERIAL_H
#define SERIAL_H

void serial_setup();
int serial_putchar(char c, FILE* f);
int serial_getchar(FILE* f);

#endif