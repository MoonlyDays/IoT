#include <Arduino.h>
#include "labs/lab2_1/lab2_1.h"

Lab2_1::Lab2_1() 
{
    Serial.begin(9600);

    m_Button = new Button();
    m_Led1 = new LED();
    m_Led2 = new LED();
}

void Lab2_1::loop() 
{
    task1();
    task2();
    task3();
}

void Lab2_1::task1()
{
    
}

void Lab2_1::task2()
{
    
}

void Lab2_1::task3()
{
    
}