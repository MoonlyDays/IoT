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

    void toggle();

    bool isOn();
    bool isOff();

private:
    int m_iPin;
};

#endif