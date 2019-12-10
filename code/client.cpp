// compile with -DDEBUG=1 for debug couts as well 


#include <iostream>
using namespace std;

#include "ioDevice.h"
#include "memory.h"
#include "cpu.h"
#include "process.h"


/*
memeBlock declared extern in memory.h
a gloack block of memory can now be accessed 
just have to include "memory.h"
*/
memory memBlock;

int main(){

    cout << "System Emulation " <<endl; 

    /*
        i want to create an io device of a particular type 
        and make sure only one instance of that device is created
    */

    deviceType type = typeMouse;
    ioDevice* myIoDevice = ioDevice::create(type); 
    myIoDevice->whoami();

    myIoDevice = ioDevice::create(type); 
    myIoDevice->whoami();

    delete myIoDevice;

    type = typeKeyboard;
    myIoDevice = ioDevice::create(type); 
    myIoDevice->whoami();

    myIoDevice = ioDevice::create(type); 
    myIoDevice->whoami();

    delete myIoDevice;

    #ifdef EXCEPTION_CASES
    type = notSupportedDevice;
    myIoDevice = ioDevice::create(type); 
    myIoDevice->whoami();

    delete myIoDevice;
    #endif

    
    /*
    ioDevice is triggering event - start application
    mouse does this by calling -> double click
    keyboard does this by calling -> click enter

    this event is sent to 'bus' via a 'port' 

    bus wraps this as a new 'job' 
    and is added to the jobQueue of the 'memory'
    */
    type = typeKeyboard;
    myIoDevice = ioDevice::create(type); 

    myIoDevice->startApplication("Browser");

    myIoDevice->startApplication("Paint");

    delete myIoDevice;

    // #ifdef DEBUG
    // cout << "\n\nlist of applications in queue\n";
    // while(memBlock.hasNext()){
        
    //     cout << "xxxxxxxx" << memBlock.next().getApplicationName() << "xxxxxxxx\n";
    // }
    // #endif

    SchedulingStrategy* schedulingStrategy = new SjfSchedule();

    Context c(schedulingStrategy);

    Cpu cpu(c);
    cpu.loadJob(memBlock.next(), cpu.getClock(), false);
    cpu.loadJob(memBlock.next(), cpu.getClock(), false);
    bool result = cpu.startProcessing();
    if(result == false)
        cout << "processing complete\n";

    return 0;
}


// why does bus control process num and not job