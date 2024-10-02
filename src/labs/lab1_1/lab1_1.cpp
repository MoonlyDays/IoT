#include <Arduino.h>
#include "drivers/led.h"
#include "labs/lab1_1/lab1_1.h"
#include "util/prompts.h"
#include "stdio/serial.h"

LED m_Led(13);

void lab1_1_setup() 
{
    serial_use_stdio();
    Serial.begin(9600);
    
    printf("Commands: \n");
    printf("\t- LED ON:   turn on the LED\n");
    printf("\t- LED OFF:  turn off the LED\n");
    printf("\n");
}

void lab1_1_loop() 
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    printf("Command: %s\n", buf);

    if(strcmp(buf, "LED ON") == 0) {
        printf("Turning the LED on...\n");
        m_Led.turnOn();
        return;
    }

    if(strcmp(buf, "OFF") == 0) {
        printf("Turning the LED off...\n");
        m_Led.turnOff();
        return;
    }

    printf("Invalid command \"%s\".\n", buf);
}
