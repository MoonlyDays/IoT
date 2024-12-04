#include <PID_v1_bc.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "drivers/motor.h"
#include "stdio/serial.h"
#include "util/prompts.h"

#define ENA 8
#define IN1 7
#define IN2 6

Motor m_Motor(ENA, IN1, IN2);
LiquidCrystal_I2C m_LCD(0x20, 16, 2);

double m_iSetPoint, m_iInput, m_iOutput;
double Kp = 2.0, Ki = 5.0, Kd = 1.0;

PID myPID(&m_iInput, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
    stdio_to_serial(9600);
    stdio_to_lcd(&m_LCD);

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 255);

    m_LCD.init();
    m_LCD.backlight();
}

void loop()
{
    char buf[32];
    prompt(NULL, buf, sizeof(buf));
    int newSetpoint = atoi(buf);

    if (newSetpoint >= 0 && newSetpoint <= 255)
    {
        m_iSetPoint = newSetpoint;
        printf("Setpoint: %d\n", m_iSetPoint);
    }
    else
    {
        printf("Please enter a value between 0 and 255.\n");
    }

    if (m_iInput < m_iSetPoint)
    {
        m_iInput += m_iOutput * 0.1;
        if (m_iInput > m_iSetPoint)
            m_iInput = m_iSetPoint;
    }
    else if (m_iInput > m_iSetPoint)
    {
        m_iInput -= m_iOutput * 0.1;
        if (m_iInput < m_iSetPoint)
            m_iInput = m_iSetPoint;
    }

    m_iOutput = myPID.Compute();
    m_Motor.setSpeed(m_iOutput);

    printf("SetPoint: %d | Current %d", m_iSetPoint, m_iInput);
    delay(100);
}
