#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/potentiometer.h"

#include "stdio/serial.h"

#define LED1_PIN 10
#define LED2_PIN 8
#define BUTTON_PIN 2
#define POTENTIOMETER_PIN A1

#define POTENTIOMETER_MIN_VALUE 0
#define POTENTIOMETER_MAX_VALUE 1024
#define TASK2_MIN_MS 100
#define TASK2_MAX_MS 1000

LED m_Led1(LED1_PIN);
LED m_Led2(LED2_PIN);
Button m_Button(BUTTON_PIN);
Potentiometer m_Potentiometer(POTENTIOMETER_PIN);

float m_iTask2Ticks = 500;
bool m_bButtonPressed;
QueueHandle_t m_xButtonPressed;

void task1(void *arg);
void task2(void *arg);
void task3(void *arg);
void task4(void *arg);

void setup()
{
    Serial.begin(9600);
    serial_use_stdio();

    m_xButtonPressed = xSemaphoreCreateBinary();

    xTaskCreate(task1, "task1", 128, NULL, 2, NULL);
    xTaskCreate(task2, "task2", 128, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 128, NULL, 2, NULL);
    vTaskStartScheduler();
}

void task1(void *arg)
{
    for (;;)
    {
        if (m_Button.down())
        {
            if (!m_bButtonPressed)
            {
                vTaskDelay(pdMS_TO_TICKS(50));
                if (m_Button.down())
                {
                    m_Led1.toggle();

                    xSemaphoreGive(m_xButtonPressed);
                    if(m_Led1.isOn()) {
                        xSemaphoreTake(m_xButtonPressed, portMAX_DELAY);
                    } else {
                        xSemaphoreGive(m_xButtonPressed);
                    }
                }
            }
        }
        else
        {
            m_bButtonPressed = false;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void task2(void *arg)
{
    for (;;)
    {
        if (xSemaphoreTake(m_xButtonPressed, portMAX_DELAY) == pdTRUE)
        {
            m_Led2.toggle();
            xSemaphoreGive(m_xButtonPressed);
        }
        
        vTaskDelay(pdMS_TO_TICKS(m_iTask2Ticks));
    }
}

void task3(void* arg) {

    for(;;)
    {
        int value = m_Potentiometer.read();
        m_iTask2Ticks = map(
            value,
            POTENTIOMETER_MIN_VALUE, POTENTIOMETER_MAX_VALUE,
            TASK2_MIN_MS, TASK2_MAX_MS
        );
    }

}