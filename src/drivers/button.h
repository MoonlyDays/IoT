#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button(int pin);
    void pullup();
    bool pressed();

private:
    int m_iPin;
};

#endif