#include <Wire.h>
#include <Arduino.h>

#include "stdio/serial.h"
#include "util/protocol.h"

#define I2C_ADDRESS 8

int receivedDistance = 0;
int lastPacket = 0;

void setup()
{
    stdio_to_serial(9600);
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveData);
}

void loop()
{
    requestData();
    delay(5000);
}

void requestData()
{
    CmdProtocol protocol;
    protocol.m_iID = lastPacket++;
    protocol.m_iEmiterID = 2;
    protocol.m_iSenderID = 1;
    protocol.m_eCommand = CMD_REQUEST_METRICS;

    char buffer[PROTOCOL_MSG_LEN];
    serialize(&protocol, buffer);

    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(buffer, PROTOCOL_MSG_LEN);
    Wire.endTransmission();
}

void receiveData(int byteCount)
{
    while (Wire.available())
    {
        int receivedDistance = Wire.read();
        printf("Distance: %dcm\n", receivedDistance);
    }
}
