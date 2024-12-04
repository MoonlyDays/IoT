#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#include "stdio/serial.h"

#define DHT_PIN 2
#define DHT_TYPE DHT11

char *SSID = "your_wifi_ssid";
const char *PWD = "your_wifi-pwd";

DHT m_DHT(DHT_PIN, DHT_TYPE);

long last_time = 0;
char data[100];

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setup()
{
    stdio_to_serial(9600);

    connectToWiFi();
    m_DHT.begin();
    setupMQTT();
}

void connectToWiFi()
{
    printf("Connectiog to ");

    WiFi.begin(SSID, PWD);
    printf(SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        printf(".");
        delay(500);
    }

    printf("Connected.");
}

void callback(char *topic, byte *payload, unsigned int length)
{
    printf("Callback - ");
    printf("Message:");
    for (int i = 0; i < length; i++)
    {
        printf("%c", payload[i]);
    }
}

void setupMQTT()
{
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
}

void reconnect()
{
    printf("Connecting to MQTT Broker...");
    while (!mqttClient.connected())
    {
        printf("Reconnecting to MQTT Broker..");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str()))
        {
            printf("Connected.");
            mqttClient.subscribe("/swa/commands");
        }
    }
}

void loop()
{
    if (!mqttClient.connected())
        reconnect();

    mqttClient.loop();

    long now = millis();
    if (now - last_time > 60000)
    {
        float temp = m_DHT.readTemperature();
        float hum = m_DHT.readHumidity();

        sprintf(data, "%f", temp);
        printf("%d", data);
        mqttClient.publish("/swa/temperature", data);
        sprintf(data, "%f", hum);
        printf("%d", hum);
        mqttClient.publish("/swa/humidity", data);
        last_time = now;
    }
}