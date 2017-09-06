#include "mbed.h"
#include "Debug.h"
#include "Stepp.h"
#include "EixoController.h"
#include "EixoMonitoring.h" 

#define LEFT  0
#define RIGHT 1
#define FRONT 1
#define BACK  0

// =============== Pinos Driver ===============
PinName clkPinX = p20;
PinName dirPinX = p19;
PinName enPinX  = p18;

PinName clkPinZ = p17;
PinName dirPinZ = p16;
PinName enPinZ = p15;

PinName swOrignX = p5;
PinName swEndX   = p6;

PinName swOrignZ = p7;
PinName swEndZ   = p8;
// ============================================


// =============== Pinos Swtches ===============
DigitalIn swLeft(p5); //X0 --> origem
DigitalIn swRight(p6); //X0 --> origem
DigitalIn swBack(p7); //X0 --> origem
DigitalIn swFront(p8); //X0 --> origem
//DigitalIn swRight(p6);//Xf --> final
// ============================================

DigitalIn leituraOlimex(p21);
Debug *debug = new Debug();

Stepp* motorX = new Stepp(clkPinX, dirPinX, enPinX);
Stepp* motorZ = new Stepp(clkPinZ, dirPinZ, enPinZ);

EixoController* eixoX = new EixoController( 49000, 38.10, motorX, swOrignX, swEndX);
//EixoController* eixoZ = new EixoController( 14000, 9.00, motorZ,swOrignZ, swEndZ);//40.55
EixoMonitoring*                 eixoMonitoring = new EixoMonitoring( swOrignX, swEndX) ;

// 0 - esquerda        1 - direita ---> Eixo X
// 1 - frente          0 - trás    ---> Eixo Z
// 1 - pressionado     0 - solto   ---> Switches


int main() { 

    bool teste = false;
    bool start = true; // mudar p/false com o uso do olimex

    if(start == true){

            teste = eixoX->goToOrigem(swLeft , LEFT);
            
            EixoMonitoring::isCalibrated = false;           
            eixoMonitoring->startThreads();
            
            if(teste == 1){// se está na origem    
                    eixoX->calibragem(RIGHT);                   
                  EixoMonitoring::isCalibrated = true;
                  eixoMonitoring->hitSensor = 0;
                    eixoMonitoring->stopAll = false;
                    
                
                    eixoX->goToPosition(17,RIGHT);
                    
            }
    }
        
        eixoMonitoring->stopThreads();
        
        
        /*
    wait(0.5);
    start = true; 
    if(start == true){
        teste = eixoZ->goToOrigem(swBack, FRONT);
        if(teste == true){// se está na origem
            eixoZ->calibragem(FRONT); 
            eixoZ->goToPosition(3,FRONT);
        }
        }
        */
}

