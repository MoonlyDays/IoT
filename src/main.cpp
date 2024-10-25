#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

// Подключение необходимых файлов заголовков для работы с DHT-сенсором и сериалом
#include "stdio/serial.h"
#include "util/macro.h"

// Определение пина для подключения DHT-сенсора и его типа (DHT11)
#define PIN 8
#define TYPE DHT11

// Создание экземпляра DHT_Unified для взаимодействия с датчиком на пине PIN и типа TYPE
DHT_Unified dht(PIN, TYPE);

void setup()
{
    // Инициализация последовательного соединения для вывода данных в монитор порта
    Serial.begin(9600);
    serial_use_stdio(); // Настройка использования стандартного вывода для сериализации
    dht.begin();        // Инициализация датчика DHT
}

void loop()
{
    delay(1000); // Задержка в 1 секунду между измерениями

    sensors_event_t event; // Создание структуры для хранения показаний датчика

    // Чтение температуры с DHT-сенсора
    dht.temperature().getEvent(&event);
    float fTemp = event.temperature; // Получение значения температуры

    // Чтение влажности с DHT-сенсора
    dht.humidity().getEvent(&event);
    float fHum = event.relative_humidity; // Получение значения влажности

    // Проверка на ошибку чтения данных с датчика (возвращается NaN, если чтение не удалось)
    if (isnan(fTemp) || isnan(fHum))
    {
        printf("Error reading temperature!\n"); // Сообщение об ошибке, если данные недоступны
        return;
    }

    // Вывод значений температуры и влажности в монитор порта
    printf("Temp = %d C, Humidity = %d %%\n", R(fTemp), R(fHum)); // R() - макрос для округления
}
