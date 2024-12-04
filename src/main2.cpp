#include <Wire.h>               // Подключение библиотеки для работы с I2C
#include <Arduino.h>             // Подключение основной библиотеки Arduino

#include "stdio/serial.h"        // Подключение библиотеки для работы с сериалом

#define I2C_ADDRESS 8           // Устанавливаем I2C-адрес для этого устройства (ведомого устройства)

int receivedDistance = 0;       // Переменная для хранения полученного расстояния (в см)

void setup()
{
    // Настройка последовательной передачи данных для отладки
    stdio_to_serial(9600); 

    // Инициализация шины I2C в режиме ведомого с указанным адресом
    Wire.begin(I2C_ADDRESS); 
    
    // Настройка функции обработки полученных данных по I2C
    Wire.onReceive(receiveData); 
}

void loop()
{
    // Отправка полученного расстояния в сериал порт для отладки
    printf("Distance: %dcm\n", receivedDistance); 
    delay(1000);  // Задержка в 1 секунду между выводами
}

// Эта функция будет вызываться при получении данных по I2C
void receiveData(int byteCount)
{
    // Чтение данных, если они доступны
    while (Wire.available()) 
    {
        // Считываем 1 байт данных и сохраняем его в переменной receivedDistance
        receivedDistance = Wire.read();  
    }
}
