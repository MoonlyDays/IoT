#include "motor.h"
#include <Arduino.h>

Motor::Motor(int ENA, int IN1, int IN2)
    : m_iENA(ENA), 
    m_iIN1(IN1), 
    m_iIN2(IN2)
{
    pinMode(m_iENA, OUTPUT);
    pinMode(m_iIN1, OUTPUT);
    pinMode(m_iIN2, OUTPUT);
    
	digitalWrite(m_iIN1, LOW);
	digitalWrite(m_iIN2, LOW);
}

void Motor::setSpeed(int speed)
{
    int pwm = map(abs(speed), 0, 100, 0, 0xFF);
    analogWrite(m_iENA, pwm);

    digitalWrite(m_iIN1, speed < 0 ? HIGH : LOW);
    digitalWrite(m_iIN2, speed > 0 ? HIGH : LOW);
}
