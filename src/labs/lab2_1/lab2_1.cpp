#include <Arduino.h>
#include <SoftTimer.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

#include "stdio/serial.h"
#include "labs/lab2_1/lab2_1.h"

void task1(Task* me);
void task2(Task* me);
void task3(Task* me);

Task t1(100, task1);
Task t2(400, task2);
Task t3(100, task3);

LED g_Led1(10);
LED g_Led2(8);
Button g_Button(2);
Potentiometer m_Potentiometer(A1);

Lab2_1::Lab2_1() 
{
    Serial.begin(9600);
    serial_use_stdio();

    // SoftTimer.add(&t1);
    SoftTimer.add(&t2);
    SoftTimer.add(&t3);
}

void Lab2_1::loop() 
{
}

void task1(Task* me) {
    if(g_Button.pressed()) {
        g_Led1.toggle();
    }

    g_Button.rememberState();
}

void task2(Task* me) {
    // if(g_Led1.isOff()) {
        g_Led2.toggle();
    // }
}

void task3(Task* me) {
    int ms = m_Potentiometer.read();
    ms += map(ms, 0, 1024, 100, 1000);
    t2.setPeriodMs(ms);
}