#ifndef BUTTON_H
#define BUTTON_H

struct Button
{
    Button(int pin);

    bool down();
    bool up();

    bool pressed();
    bool released();

    void rememberState();

private:
    int m_iPin;
    bool m_bWasPressed;
};

#endif