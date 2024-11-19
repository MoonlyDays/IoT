#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    Motor(int pinA, int pinB);
private:
    int m_iPinA;
    int m_iPinB;
};

#endif