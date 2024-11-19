#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    Motor(int pinA, int pinB);

    void setSpeed(int speed);

private:
    int m_iPinA;
    int m_iPinB;
};

#endif