#include <Arduino.h>

#include "labs/Lab1.h"
#include "labs/Lab2.h"
#include "labs/lab.h"

Lab* current;
#define USE_LAB(n) current = new Lab##n();

void setup()
{
    USE_LAB(2)
}

void loop()
{
    current->loop();
}