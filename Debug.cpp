#include "Debug.h"

Debug::Debug(){
    debugPin_1 = new DigitalOut(LED1);
    debugPin_2 = new DigitalOut(LED2);
    debugPin_3 = new DigitalOut(LED3);
    debugPin_4 = new DigitalOut(LED4);
}


void Debug::debugPin(int led, int state){

    switch(led){
        case 1:
            debugPin_1->write(state);
            break;
        case 2:
            debugPin_2->write(state);
            break;
        case 3:
            debugPin_3->write(state);
            break;
        case 4:
            debugPin_4->write(state);
            break;
        default:
            debugPin_1->write(state);
            debugPin_2->write(state);
            debugPin_3->write(state);
            debugPin_4->write(state);
            break;
    }
    
}
