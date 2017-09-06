#include "Stepp.h" 
 
Stepp::Stepp(PinName clk, PinName dir, PinName en) : _clk(clk), _dir(dir), _en(en) {
    _clk = 0, _dir = 0, _en = 0;
   
        debug = new Debug();
        this->speed = 50;
        this->acell = true;
        //PinName pinOrigin;
}
 
int Stepp::step(int n_steps, bool direction) {
    
        int accelspeed;
    if(this->acell) accelspeed = START_STOP_SPEED;
    else accelspeed = this->speed;
    
    _en = 0; // habilita move
      _dir = direction;
    
        for(int i=0; (i< n_steps && EixoMonitoring::stopAll == false); i++){
            
        if(this->acell){//linear acceleration
          if(i < START_STOP_SPEED) if (--accelspeed == this->speed) accelspeed ++; 
          if(i > (n_steps-START_STOP_SPEED)) if(++accelspeed == START_STOP_SPEED) accelspeed--;
        }  
       
        _clk = 1;
        wait_us(1);
        _clk = 0;
        wait_us(1);
        wait_us(accelspeed);
    }
     _en = 1;

    return 1;
}
 
bool Stepp::findLimits(int n_steps, bool direction, DigitalIn sensor) {
       
    int accelspeed = 0;
    if(this->acell) accelspeed = START_STOP_SPEED;
    else accelspeed = this->speed;
    
    int i = 0;
    _en   = 0; // habilita move   
    _dir  = direction;
    
        while(sensor.read() == 0 &&  EixoMonitoring::stopAll == false){ // n chegou na origem   
                
              if(this->acell){ //linear acceleration
                        if(i < START_STOP_SPEED) if (--accelspeed == this->speed) accelspeed ++; 
                        if(i > (n_steps-START_STOP_SPEED)) if(++accelspeed == START_STOP_SPEED) accelspeed--;
                }  
                
                _clk = 1;
                wait_us(1);
                _clk = 0;
                wait_us(1);
                wait_us(accelspeed);
                
                i++;
        }
        _en = 1; 
        
        
         if(sensor.read() == 0){
                return 0;
         }
         else return 1;           
} 

 
float Stepp::version(void) { // version() returns the version number of the library
    return VERSION;    
}
