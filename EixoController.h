#ifndef EIXO_CONTROLLER_H
#define EIXO_CONTROLLER_H

#include "Debug.h"
#include "Stepp.h"
#include "mbed.h"


class EixoController{

    public:
        EixoController(float, float, Stepp*, PinName, PinName );
                bool goToOrigem(DigitalIn, int);
                void calibragem(int);
                int conversao(int);
                void goToPosition(int, int );   
                
    private:
                int totalPathPulse;
                int totalPathCm;    
                
                DigitalIn swOrigin;
                DigitalIn swEnd;
                Stepp*       motor ;
                Debug*       debug;
};

#endif

