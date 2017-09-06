#ifndef EIXO_MONITORING_H
#define EIXO_MONITORING_H

#include "mbed.h" 
#include "rtos.h"
#include "Debug.h"


//#define DELAY_TIMER 500

class EixoMonitoring {
    
    public:
             int    delayTimer; 
             int    hitSensor;
       Debug* debug;  
             
    
       // Variáveis e Controle do Movimento do Eixo
             static bool stopAll;  // false: n calibrado       true: calibrado, cnc está no estágio de teste
             static bool isCalibrated;  // false: n calibrado       true: calibrado, cnc está no estágio de teste
       bool stopMoviment;         // false: gira motor        true: pára motor
       bool stopMonitoring;       // false: executa threads   true: pára threads 
    
       // Switches e seu vetor de leitura
             int sensorInput_End;  
             DigitalIn*  sensor_End;
             int sensorInput_Origin;  
             DigitalIn*  sensor_Origin;
            
            
             // Threads
         Mutex stdioMutex;                   // controle de Acesso Mútuo
             Thread sensorThread_End;             // threads de leitura dos sensores
             Thread handleSensorThread_End;       // threads para lidar com a leitura dos sensores
             Thread sensorThread_Origin;             // threads de leitura dos sensores
             Thread handleSensorThread_Origin;       // threads para lidar com a leitur
        
             EixoMonitoring(PinName, PinName);
             void startThreads();
         void stopThreads();
             void readSensor_End();       
            
             void handleReadSensor_End(); 
             void readSensor_Origin();
             void handleReadSensor_Origin(); 
};

#endif

