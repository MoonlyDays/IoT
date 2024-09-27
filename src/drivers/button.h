#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button(int pin);
    void pullup();
    
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