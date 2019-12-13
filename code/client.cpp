// compile with -DDEBUG=1 for debug couts as well 


#include <iostream>
using namespace std;

#include "ioDevice.h"
#include "memory.h"
#include "cpu.h"
#include "process.h"
#include "bus.h"


/*
memBlock declared extern in memory.h
a global block of memory can now be accessed 
just have to include "memory.h"
*/
memory memBlock;

/*
global variables that is to be shared between the threads
*/
SchedulingStrategy* schedulingStrategy = new FifoSchedule();

Context c(schedulingStrategy);

Cpu cpu(c);

deviceType type = typeKeyboard;
ioDevice* myIoDevice = ioDevice::create(type); 
interrupt event;

void addProcess(){
    Process p(false, rand()%15+1,rand()%100+100, 1, "Computational background process", rand()%5);
    cpu.addProcess(p);
}

/*
    threaded function to paralelly receive input and fire processes or interrupts from the user while the cpu is processing
*/
void* getNewApps(void* arg){
    cout << "Enter 1 for Paint\n2 for Browser\n3 for Solitaire\n4 for Word\n5 for Excel\n6 for Background process\n7 for interrupt\nany other number to end\n";
    int choice;
    while(true){
        cin >> choice;

        switch(choice){
            case 1:
                myIoDevice->startApplication("Paint");
                cpu.loadJob(memBlock.next(), cpu.getClock());
                break;
            case 2:
                myIoDevice->startApplication("Browser");
                cpu.loadJob(memBlock.next(), cpu.getClock());
                break;
            case 3:
                myIoDevice->startApplication("Solitaire");
                cpu.loadJob(memBlock.next(), cpu.getClock());
                break;
            case 4:
                myIoDevice->startApplication("Word");
                cpu.loadJob(memBlock.next(), cpu.getClock());
                break;
            case 5:
                myIoDevice->startApplication("Excel");
                cpu.loadJob(memBlock.next(), cpu.getClock());
                break;
            case 6:
                addProcess();
                break;
            case 7:
                event.triggerHardwareInterrupt(cpu,myIoDevice,"terminal interrupt");
                break;
            default:
                delete myIoDevice;
                delete schedulingStrategy;
                exit(0);
                return nullptr;
        }
    }

    return nullptr;
}

int main(){

    cout << "System Emulation " <<endl; 

    /*
        i want to create an io device of a particular type 
        and make sure only one instance of that device is created
    */
    #ifdef SAMPLE_CODE
    type = typeMouse;
    myIoDevice = ioDevice::create(type); 
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
    from jobQueue it is loaded in main memory as a process
    */

    myIoDevice->startApplication("Browser");

    myIoDevice->startApplication("Paint");

    #ifdef SAMPLE_CODE
    cout << "\n\nlist of applications in queue\n";
    while(memBlock.hasNext()){
        
        cout << "xxxxxxxx" << memBlock.next().getApplicationName() << "xxxxxxxx\n";
    }
    #endif

// sample processes
    cpu.loadJob(memBlock.next(), cpu.getClock());
    cpu.loadJob(memBlock.next(), cpu.getClock());

    pthread_t thread_id;
    pthread_create(&thread_id, nullptr, getNewApps, nullptr);

// sample interrupts
    event.triggerHardwareInterrupt(cpu,myIoDevice,"ctrl+x");
    event.triggerHardwareInterrupt(cpu,myIoDevice,"ctrl+z");

    cpu.startProcessing();

    return 0;
}