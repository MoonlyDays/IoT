#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

#include "stdio/serial.h"

LED m_Led1(10);
LED m_Led2(8);
Button m_Button(2);
Potentiometer m_Potentiometer(A1);

QueueHandle_t m_xLed1TurnedOn;
QueueHandle_t m_xLed2Interval;
int m_iLed2Interval = 500;

void task1(void *arg);
void task2(void *arg);
void task3(void *arg);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();

    m_xLed2Interval = xSemaphoreCreateBinary();
    xSemaphoreGive(m_xLed2Interval);
    m_xLed1TurnedOn = xSemaphoreCreateBinary();
    xSemaphoreGive(m_xLed1TurnedOn);

    xTaskCreate(task1, "task1", 128, NULL, 2, NULL);
    xTaskCreate(task2, "task2", 128, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 128, NULL, 2, NULL);
}

void task1(void *arg)
{
    while (1)
    {
        if (m_Button.pressed())
        {
            if (m_Led1.isOff())
            {
                if (xSemaphoreTake(m_xLed1TurnedOn, 5) == pdTRUE)
                {
                    printf("LED 1 turned on.\n");
                    m_Led1.turnOn();
                }
            }
            else
            {
                printf("LED 1 turned off.\n");
                xSemaphoreGive(m_xLed1TurnedOn);
                m_Led1.turnOff();
            }
        }

        m_Button.rememberState();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task2(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(m_xLed1TurnedOn, 5) == pdTRUE)
        {
            m_Led2.toggle();
            xSemaphoreGive(m_xLed1TurnedOn);
        }

        if (xSemaphoreTake(m_xLed2Interval, 0) == pdTRUE)
        {
            printf("delayed for %d\n", m_iLed2Interval);
            vTaskDelay(pdMS_TO_TICKS(m_iLed2Interval));
            xSemaphoreGive(m_xLed1TurnedOn);
        } e
    }
}

void task3(void *arg)
{
    int ms = m_Potentiometer.read();
    if (ms == m_iLed2Interval)
    {
        return;
    }

    if (xSemaphoreTake(m_xLed2Interval, 0) == pdTRUE)
    {
        printf("Updated update interval: %dms\n", m_iLed2Interval);
        m_iLed2Interval = ms;
        xSemaphoreGive(m_xLed2Interval);
    }
    
    vTaskDelay(pdMS_TO_TICKS(100));
}