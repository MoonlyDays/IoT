
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

struct Potentiometer
{
    Potentiometer(int pin);
    int read();

private:
    int m_iPin;
};

#endif