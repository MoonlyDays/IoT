#include "led.h"
#include <Arduino.h>

void led_setup() {
    pinMode(PIN_LED, OUTPUT);
}

int led_get_state() {
    return digitalRead(PIN_LED);
}

void led_set_state(int state) {
    digitalWrite(PIN_LED, state);
}

void led_on() {
    led_set_state(HIGH);
}

void led_off() {
    led_set_state(LOW);
}
