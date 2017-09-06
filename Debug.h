#ifndef DEBUG_H
#define DEBUG_H
#include "mbed.h"

#define HIGH  1
#define LOW   0

class Debug{
    
    public:
            Debug();
            void debugPin(int, int);
    
            DigitalOut *debugPin_1;
            DigitalOut *debugPin_2;
            DigitalOut *debugPin_3;
            DigitalOut *debugPin_4;

};

#endif
