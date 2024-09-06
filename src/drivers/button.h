#ifndef BUTTON_H
#define BUTTON_H

#define PIN_BUTTON 12

void button_setup();
void button_pullup();
int button_pressed();

#endif