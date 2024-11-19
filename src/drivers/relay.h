#include "drivers/led.h"

struct Relay : public LED
{
    Relay(int pin) : LED(pin) {}
};
