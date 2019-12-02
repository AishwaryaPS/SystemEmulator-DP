// compile with -DDEBUG=1 for debug couts as well 


#include <iostream>
using namespace std;

#include "ioDevice.h"


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
    



    return 0;
}