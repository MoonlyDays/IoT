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
QueueHandle_t m_xButtonPressed;
int m_iLed2Interval = 500;

void task1(void *arg);
void task2(void *arg);
void task3(void *arg);
void task4(void *arg);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();

    m_xLed2Interval = xSemaphoreCreateBinary();
    xSemaphoreGive(m_xLed2Interval);
    m_xLed1TurnedOn = xSemaphoreCreateBinary();
    xSemaphoreGive(m_xLed1TurnedOn);
    m_xButtonPressed = xSemaphoreCreateBinary();

    xTaskCreate(task1, "task1", 128, NULL, 2, NULL);
    xTaskCreate(task2, "task2", 128, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 128, NULL, 2, NULL);
    xTaskCreate(task4, "task4", 128, NULL, 2, NULL);
}

void task1(void *arg)
{
    for (;;)
    {
        if (m_Button.pressed())
        {
            printf("m_Button.pressed()\n");
            if (m_Led1.isOff())
            {
                printf("m_Led1.isOff()\n");
                if (xSemaphoreTake(m_xLed1TurnedOn, portMAX_DELAY) == pdTRUE)
                {
                    printf("m_Led1.turnOn()\n");
                    m_Led1.turnOn();
                }
            }
            else
            {
                printf("!m_Led1.isOff()\n");
                printf("!m_Led1.turnOff()\n");
                xSemaphoreGive(m_xLed1TurnedOn);
                m_Led1.turnOff();
            }

            xSemaphoreGive(m_xButtonPressed);
        }

        m_Button.rememberState();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task2(void *arg)
{
    for (;;)
    {
        if (xSemaphoreTake(m_xLed1TurnedOn, 5) == pdTRUE)
        {
            printf("!m_Led1.turnOff()\n");
            m_Led2.toggle();
        }

        vTaskDelay(pdMS_TO_TICKS(m_iLed2Interval));
    }
}

void task3(void *arg)
{
    for (;;)
    {
        int ms = m_Potentiometer.read();
        if (ms == m_iLed2Interval)
        {
            return;
        }

        m_iLed2Interval = ms;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task4(void *arg)
{
    for (;;)
    {
        if (xSemaphoreTake(m_xButtonPressed, portMAX_DELAY) == pdTRUE)
        {
            printf("Button was pressed!\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}