#include <stdio.h>
#include <LiquidCrystal_I2C.h>

#ifndef SERIAL_H
#define SERIAL_H

void stdio_to_serial(unsigned long baud);
void stdio_to_lcd(LiquidCrystal_I2C *lcd);

#endif