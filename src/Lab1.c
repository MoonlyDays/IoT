#include "drivers/button.h"
#include "drivers/led.h"
#include <Arduino.h>

int mode = 0;
int wasPressed = 0;

void lab1_setup()
{
    button_setup();
    led_setup();
}

void lab1_loop() 
{
    int pressed = button_pressed();

    if(wasPressed != pressed) {
        wasPressed = pressed;
        
        if(pressed) {
            mode = !mode;
            led_set_state(mode);
        } 
    }
}