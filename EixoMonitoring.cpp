#include "EixoMonitoring.h" 

bool EixoMonitoring::stopAll                = false; 
bool EixoMonitoring::isCalibrated   = false;


EixoMonitoring::EixoMonitoring(PinName pinOrigin, PinName pinEnd) { 
        
        this->stopMoviment   = false;
        this->stopMonitoring = false;
        this->delayTimer         = 700;
        PinName pin_End      = pinEnd;
        PinName pin_Origin = pinOrigin;
        
        sensor_End          = new DigitalIn(pin_End);
        sensorInput_End = 0;
        sensor_Origin       = new DigitalIn(pin_Origin);
        sensorInput_Origin = 0;
        
        debug = new Debug();        
}


void EixoMonitoring::startThreads(){          
        hitSensor = 0; 
      this->stopMoviment   = false;
        this->stopMonitoring = false;
    
    sensorThread_End.start( callback(this, &EixoMonitoring::readSensor_End) );
    handleSensorThread_End.start( callback(this, &EixoMonitoring::handleReadSensor_End) );
    
        sensorThread_Origin.start( callback(this, &EixoMonitoring::readSensor_Origin) );
    handleSensorThread_Origin.start( callback(this, &EixoMonitoring::handleReadSensor_Origin) );              
}

void EixoMonitoring::readSensor_End(){  
    while(stopMonitoring == false){
        stdioMutex.lock();
        sensorInput_End = sensor_End->read();           
        stdioMutex.unlock();        
        Thread::wait(50);
    }
}


void EixoMonitoring::readSensor_Origin(){   
    while(stopMonitoring == false){
        stdioMutex.lock();
        sensorInput_Origin = sensor_Origin->read();                    
        stdioMutex.unlock();        
        Thread::wait(50);
    }
}

void EixoMonitoring::handleReadSensor_End(){
        Timer* timerLeitura = new Timer();
        timerLeitura->start();
         
        while(stopMonitoring == false){         
                if (stopMoviment == false){
                        stdioMutex.lock();
                        if(sensorInput_End == 1 && timerLeitura->read_ms()> this->delayTimer ){ // sensor pressionado ? e passou meio segundo
                             hitSensor++;                                                                           
                             timerLeitura->reset();
                        }
                        stdioMutex.unlock();
                }           
                
                                
                // SEGURANÇA DA CNC:
                if (isCalibrated == false){ 
                
                        if(hitSensor > 1){ // Na fase de calibragem, se bateu + de 2 vezes(achou origem e na contagem de passos): -> true
                            stopMoviment = true; 
                            stopAll = true;
                            timerLeitura->stop();                           
                        }
                }
                else{ 
                        if(hitSensor > 0){ // Na fase de teste, se bateu + de 1 vez: -> true
                            stopMoviment = true; 
                            stopAll = true;
                            timerLeitura->stop();
                        }
                } 
                
                Thread::wait(50);
    }
        timerLeitura->stop();       
}

void EixoMonitoring::handleReadSensor_Origin(){
    
        Timer* timerLeitura = new Timer();
        timerLeitura->start();
    
        while(stopMonitoring == false){       
        
        if (stopMoviment == false){
                        stdioMutex.lock();
                        if(sensorInput_Origin == 1 && timerLeitura->read_ms()> this->delayTimer){ // sensor pressionado ?
                             hitSensor++;
                             timerLeitura->reset();
                        }
                        stdioMutex.unlock();
        }           
       
                
                // SEGURANÇA DA CNC:
                if (isCalibrated == false){ 
                        if(hitSensor > 1){ // Na fase de calibragem, se bateu + de 2 vezes(achou origem e na contagem de passos): -> true
                            stopMoviment = true; 
                            stopAll = true;
                            timerLeitura->stop();
                        }
                }
                else{ 
                        if(hitSensor > 0){ // Na fase de teste, se bateu + de 1 vez: -> true
                            stopMoviment = true; 
                            stopAll = true;
                            timerLeitura->stop();
                        }
                }   
                
        Thread::wait(50);
    }
        timerLeitura->stop();
}

void EixoMonitoring::stopThreads(){ 
                 
    this->stopMoviment   = true;
    this->stopMonitoring = true;
    
    sensorThread_End.join();
    handleSensorThread_End.join();
    sensorThread_Origin.join();
    handleSensorThread_Origin.join();

    sensorThread_End.terminate();
    handleSensorThread_End.terminate();
    sensorThread_Origin.terminate();
    handleSensorThread_Origin.terminate();
       
}
