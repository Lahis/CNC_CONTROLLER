#include "EixoController.h"


EixoController::EixoController(float totalPathPulse, float totalPathCm, Stepp *motor, PinName pinOrigin, PinName pinEnd): swOrigin(pinOrigin), swEnd(pinEnd)  {
     
     this->totalPathPulse = totalPathPulse;
     this->totalPathCm = totalPathCm;
     this->motor = motor;
         
         debug = new Debug();       
}


bool EixoController:: goToOrigem(DigitalIn swOrigem, int dirOrigem){   
        if(swOrigem == 1){ // já está na origem ?   
        return true;
    }
    else{ // vá para a origem
        return motor->findLimits(50000, dirOrigem, swOrigem);            
    }           
}

void EixoController:: calibragem(int startDirection){
    int teste1 = 0;
    int teste2 = 0;
    
    while (1){ // repita até calibragem correta
                teste1 = motor->step(totalPathPulse, startDirection);    
                wait(0.2);
                teste2 = motor->step(totalPathPulse, !startDirection);
                        
        if(teste1 == teste2){
            // Passos iguais
            break;
        }
        else{
            // Passos Diferentes
            break;
        }    
    }
    
}


int EixoController::conversao(int posCm){ // 38cm == 30000 passos
    float pulses  = (totalPathPulse*posCm)/totalPathCm; // regra de três
    return (int)pulses;
}
     
void EixoController:: goToPosition(int posCm, int dir){
    
      int pulses = conversao(posCm);    
    motor->step(pulses, dir);
            
} 

