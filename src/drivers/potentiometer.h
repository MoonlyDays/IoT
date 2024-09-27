
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer
{
public:
    Potentiometer(int pin);
    int read();
private:
    int m_iPin;
};

#endif