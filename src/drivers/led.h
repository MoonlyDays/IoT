#ifndef LED_H
#define LED_H

class LED
{
public:
    LED(int pin);

    bool getState();
    void setState(bool state);

    void turnOn();
    void turnOff();

private:
    int m_iPin;
};

#endif