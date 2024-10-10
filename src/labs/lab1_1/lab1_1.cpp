#include "labs/lab1_1/lab1_1.h"

#include <Arduino.h>
#include "stdio/serial.h"
#include "util/prompts.h"

Lab1_1::Lab1_1()
{
    serial_use_stdio();
    Serial.begin(9600);

    m_Led = new LED(13);

    printf("Commands: \n");
    printf("\t- LED ON:   turn on the LED\n");
    printf("\t- LED OFF:  turn off the LED\n");
    printf("\n");
}

void Lab1_1::loop()
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    printf("Command: %s\n", buf);

    if (strcmp(buf, "LED ON") == 0)
    {
        printf("Turning the LED on...\n");
        m_Led->turnOn();
        return;
    }

    if (strcmp(buf, "OFF") == 0)
    {
        printf("Turning the LED off...\n");
        m_Led->turnOff();
        return;
    }

    printf("Invalid command \"%s\".\n", buf);
}
