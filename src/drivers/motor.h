#ifndef MOTOR_H
#define MOTOR_H

struct Motor
{
    Motor(int ENA, int IN1, int IN2);
    void setSpeed(int speed);

private:
    int m_iENA;
    int m_iIN1;
    int m_iIN2;
};

#endif