#include <Wire.h>
#include <Arduino.h>
#include <HCSR04.h>

#include "util/protocol.h"
#include "stdio/serial.h"

#define I2C_ADDRESS 8

#define USS_PIN1 9
#define USS_PIN2 10

UltraSonicDistanceSensor m_DistanceSensor(USS_PIN1, USS_PIN2);

void setup()
{
    stdio_to_serial(9600);
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveData);
}

void receiveData(int byteCount)
{
    char buffer[PROTOCOL_MSG_LEN];
    Wire.readBytes(buffer, sizeof(buffer));

    CmdProtocol protocol;
    if (!deserialize(buffer, &protocol))
        return;

    switch (protocol.m_eCommand)
    {
    case CMD_REQUEST_METRICS:
        sendMetrics();
        break;
    }
}

void sendMetrics()
{
    long distance = m_DistanceSensor.measureDistanceCm(25);
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(distance);
    Wire.endTransmission();
}