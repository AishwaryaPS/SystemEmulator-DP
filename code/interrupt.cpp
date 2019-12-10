#include "interrupt.h"

interrupt :: interrupt(){
    #ifdef DEBUG
    cout << "interrupt ctor\n";
    #endif
}


interrupt :: ~interrupt(){
    #ifdef DEBUG
    cout << "interrupt dtor\n";
    #endif
}

void interrupt :: triggerHardwareInterrupt(Cpu &cpu,ioDevice* interruptCaller, string interruptMsg){
    #ifdef DEGUB
    cout << "hardware interrupt has been triggered\n";
    #endif
    this->interruptMsg = interruptMsg;
    this->type = hardware;
    this->interruptingDevice = interruptCaller->whoami();

    cpu.interruptHandler(*this);

}

string interrupt :: getInterruptingDeviceName(){
    return interruptingDevice;
}

string interrupt :: getInterruptMsg(){
    return interruptMsg;
}
