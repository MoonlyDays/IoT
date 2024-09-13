#include "drivers/serial.h"
#include <Arduino.h>

#include "labs/Lab1.h"
#include "labs/lab.h"

Lab* g_Current;

void setup()
{
    serial_use_stdio();
    Serial.begin(9600);

    for(;;)
    {
        printf("Select the program you wish to run:\n");
        printf("1. Lab1 - Control LED with stdio commands\n");

        int option;
        scanf("%d", &option);
        fflush(stdin);
        
        switch (option)
        {
            case 1: 
                g_Current = new Lab1();
                break;
                
            default:
                printf("[ERROR] Invalid program code.\n");
                break;
        }

        if(g_Current != NULL) {
            break;
        }
    }
}

void loop()
{
    g_Current->loop();
}