#include "drivers/button.h"
#include "drivers/led.h"
#include "drivers/serial.h"
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    serial_setup();
    led_setup();
}

void loop( ) 
{
    printf("Commands: \n");
    printf("- LED ON: turn on the LED\n");
    printf("- LED OFF: turn off the LED\n");
    printf("\n");

    char buf[32];
    scanf("%s", buf);

    if(strcmp(buf, "LED") == 0) {
        
        printf("LED ");
        scanf("%s", buf);
        printf(buf);
        printf("\n");

        if(strcmp(buf, "ON") == 0) {
            printf("Turning on...\n");
            led_on();
            return;
        }

        if(strcmp(buf, "OFF") == 0) {
            printf("Turning off...\n");
            led_off();
            return;
        }

        printf("Usage: LED <ON|OFF>\n");
        return;
    }
    
    printf("Invalid command \"%s\".\n", buf);
}
