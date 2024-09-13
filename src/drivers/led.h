#ifndef LED_H
#define LED_H

#define PIN_LED 13

void led_setup();
int led_get_state();
void led_set_state(int state);
void led_on();
void led_off();

#endif