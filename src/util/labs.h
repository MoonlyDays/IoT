#ifndef LABS_H
#define LABS_H

struct Lab
{
    virtual void loop() {};
};

extern Lab* current;

#define __DEFINE_SETUP(n) \
    void setup() { current = new Lab##n(); };

#define __DEFINE_LOOP(n) \
    void loop() { Lab::current()->loop(); };

#define DEFINE_LAB(n) \
    __DEFINE_SETUP(n) \
    __DEFINE_LOOP(n)

#define DEFINE_LAB_NOLOOP(n) \
    __DEFINE_SETUP(n)

#endif

