#include <Arduino.h>
#include "drivers/led.h"
#include "labs/Lab1.h"
#include "util/prompts.h"

Lab1::Lab1() 
{
    m_Led = new LED(13);

    printf("Commands: \n");
    printf("\t- LED ON:   turn on the LED\n");
    printf("\t- LED OFF:  turn off the LED\n");
    printf("\n");
}

void Lab1::loop() 
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    printf("Command: %s\n", buf);

    if(strcmp(buf, "LED ON") == 0) {
        printf("Turning the LED on...\n");
        m_Led->turnOn();
        return;
    }

    if(strcmp(buf, "OFF") == 0) {
        printf("Turning the LED off...\n");
        m_Led->turnOff();
        return;
    }

    printf("Invalid command \"%s\".\n", buf);
}
