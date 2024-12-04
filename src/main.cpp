#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

long last_time = 0;
char data[100];

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void connectToWiFi()
{
    WiFi.begin("Redmi Note 9 Pro", "0987654321");

    Serial.write("Connecting to ");
    Serial.write("Redmi Note 9 Pro");


    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.write(".");
        delay(500);
    }

    Serial.write("Connected\n");
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.write("Callback - ");
    Serial.write("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.write("%c", payload[i]);
    }
}

void setupMQTT()
{
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
}

void reconnect()
{
    Serial.write("Connecting to MQTT Broker...");
    while (!mqttClient.connected())
    {
        Serial.write("Reconnecting to MQTT Broker..");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str()))
        {
            Serial.write("Connected.");
            mqttClient.subscribe("/swa/commands");
        }
    }
}

void setup()
{
    Serial.begin(9600);
    connectToWiFi();
    setupMQTT();
}

void loop()
{
    if (!mqttClient.connected())
        reconnect();

    mqttClient.loop();

    long now = millis();
    if (now - last_time > 60000)
    {
        float temp = 27.0;
        float hum = 70;

        sprintf(data, "%f", temp);
        Serial.write(data);
        mqttClient.publish("/swa/temperature", data);
        sprintf(data, "%f", hum);
        Serial.write("%.2f", hum);
        mqttClient.publish("/swa/humidity", data);
        last_time = now;
    }
}