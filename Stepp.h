#ifndef MBED_STEPPER_H
#define MBED_STEPPER_H

#include "mbed.h"
#include "Debug.h"
#include "EixoMonitoring.h" 

#define START_STOP_SPEED 300  // define the Stepper Motor save start/stop speed 
#define VERSION 0.3                     // define Library version number

class Stepp {
    public:
            Stepp(PinName clk, PinName dir, PinName en);
            int step(int n_steps, bool direction);  
            bool findLimits(int n_steps, bool direction, DigitalIn sensor);  
            float version(void);   
        
    private:  
                        int speed;
                        bool acell;
                        PinName pinOrigin;
                        PinName pinEnd;
            DigitalOut _clk;
            DigitalOut _dir;
            DigitalOut _en;
            Debug* debug;
            
};

#endif
