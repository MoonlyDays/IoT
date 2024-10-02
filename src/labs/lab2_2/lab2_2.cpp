#include <Arduino.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

#include "stdio/serial.h"
#include "labs/lab2_2/lab2_2.h"

LED m_Led1(10);
LED m_Led2(8);
Button m_Button(2);
Potentiometer m_Potentiometer(A1);

bool m_bButtonWasPressed;

void lab2_2_setup() 
{
    Serial.begin(9600);
    serial_use_stdio();

    xTaskCreate(
        lab2_2_task1,
        "lab2_2_task1",
        128, NULL,
        2, NULL
    );

    xTaskCreate(
        lab2_2_task2,
        "lab2_2_task2",
        128, NULL,
        2, NULL
    );

    xTaskCreate(
        lab2_2_task3,
        "lab2_2_task3",
        128, NULL,
        2, NULL
    );

    xTaskCreate(
        lab2_2_task4,
        "lab2_2_task4",
        128, NULL,
        2, NULL
    );
}

void lab2_2_task1(void *arg) {
    if(m_Button.pressed()) {
        m_bButtonWasPressed = true;
        m_Led1.toggle();
    }

    m_Button.rememberState();
}

void lab2_2_task2(void *arg) {
    if(m_Led1.isOff()) {
        m_Led2.toggle();
    }
}

void lab2_2_task3(void *arg) {
    int ms = m_Potentiometer.read();
    ms += map(ms, 0, 1024, 100, 1000);
}

void lab2_2_task4(void *arg) {
    printf(
        "LED1: %s, LED2: %s\n", 
        m_Led1.isOn()   ? "ON" : "OFF",
        m_Led1.isOff()  ? "ON" : "OFF"
    );

    if(m_bButtonWasPressed) {
        m_bButtonWasPressed = false;
        printf("BUTTON WAS PRESSED\n");
    }
}