#include <Arduino.h>

#include "labs/lab1_1/lab1_1.h"
#include "labs/lab1_2/lab1_2.h"
#include "labs/lab2_1/lab2_1.h"
#include "labs/lab.h"

Lab* current;
#define USE_LAB(n) current = new Lab##n();

void setup()
{
    USE_LAB(2_1)
}
