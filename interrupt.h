#ifndef INTERRUPT_
#define INTERRUPT_

#include "ioDevice.h"
#include "cpu.h"

enum interruptType{
    software, hardware
};

class interrupt{

    string interruptMsg;
    interruptType type;
    string interruptingDevice;

    public :
    interrupt();
    ~interrupt();

    void triggerHardwareInterrupt(Cpu &cpu,ioDevice* interruptCaller, string interruptMsg);
    string getInterruptingDeviceName();
    string getInterruptMsg(); 
};

#endif 