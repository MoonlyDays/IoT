#include <Arduino.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

#include "stdio/serial.h"
#include "labs/lab2_1/lab2_1.h"

Task t1(100, lab2_1_task1);
Task t2(400, lab2_1_task2);
Task t3(100, lab2_1_task3);
Task t4(1000, lab2_1_task4);

LED m_Led1(10);
LED m_Led2(8);
Button m_Button(2);
Potentiometer m_Potentiometer(A1);

bool m_bButtonWasPressed;

void lab2_1_setup() 
{
    Serial.begin(9600);
    serial_use_stdio();

    SoftTimer.add(&t1);
    SoftTimer.add(&t2);
    SoftTimer.add(&t3);
    SoftTimer.add(&t4);
}

void lab2_1_task1(Task* me) {
    if(m_Button.pressed()) {
        m_bButtonWasPressed = true;
        m_Led1.toggle();
    }

    m_Button.rememberState();
}

void lab2_1_task2(Task* me) {
    if(m_Led1.isOff()) {
        m_Led2.toggle();
    }
}

void lab2_1_task3(Task* me) {
    int ms = m_Potentiometer.read();
    ms += map(ms, 0, 1024, 100, 1000);
    t2.setPeriodMs(ms);
}

void lab2_1_task4(Task* me) {
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