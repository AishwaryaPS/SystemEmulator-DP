#include "ioDevice.h"


/*
private static instance variables of each device type to be redeclared here 
and assigned  nullptr
*/
keyboard* keyboard :: _instance = nullptr;
mouse* mouse :: _instance = nullptr;

int ioDevice::count = 0;

/*
ioDevice implementations ---------------------------------------------------------------------------
*/
ioDevice :: ioDevice(){
    #ifdef DEBUG
    cout << "ioDevice ctor \n";
    #endif 

}

ioDevice :: ~ioDevice(){
    #ifdef DEBUG
    cout << "ioDevice dtor \n";
    #endif
}

/*
factory method to create io device required 
*/
ioDevice* ioDevice :: create(deviceType type){
    #ifdef DEBUG
    cout << "\nSTEP 1 : create IO Obj for type :"<< type <<"\n";
    #endif
    switch(type){
        case typeKeyboard :
        #ifdef DEBUG
        cout << "create - > keyboard object \n";
        #endif
        return keyboard::createInstance();
        break;

        case typeMouse :
        #ifdef DEBUG
        cout << "create  -> mouse obj \n";
        #endif
        return mouse::createInstance();
        break;

        default :
        #ifdef DEBUG
        cout << "create -> invlaid type \n";
        #endif
        throw invalid_argument("Device type specified not supported :(");
    }
}



/*
keyboard implementations ---------------------------------------------------------------------------
*/
keyboard :: keyboard(){
    #ifdef DEBUG
    cout << "keyboard  ctor \n";
    #endif

    portNum = ioDevice::count;
    ++ioDevice::count;
}

keyboard :: ~keyboard(){
    #ifdef DEBUG
    cout << "keyboard  dtor \n";
    #endif
    keyboard :: _instance = nullptr;
}
void keyboard :: whoami(){
    cout << "ioDevice : keyboard \n"; 
}
void keyboard :: startApplication(string application){
    cout << "Event triggered by keyboard\n";
    #ifdef DEBUG
    cout << "\nSTEP 2 : Io Obj triggers event\n";
    #endif
    clickEnter(application);
}

keyboard* keyboard:: createInstance(){
    if(keyboard :: _instance == nullptr){
       
        #ifdef DEBUG
        cout << "creating a new instance of keyboard \n";
        #endif

        keyboard :: _instance = new keyboard();

    }

    return keyboard :: _instance;
}

void keyboard :: clickEnter(string application){
    #ifdef DEBUG
    cout << "click Enter method called\n";
    #endif
    port* adaptor  = new port(portNum);
    adaptor->startApplication(application);    
}


/*
mouse implementations ---------------------------------------------------------------------------
*/

mouse :: mouse(){
    
    portNum = ioDevice::count;
    ++ioDevice::count;

    #ifdef DEBUG
    cout << "mouse  ctor  -- portNum: "<<portNum<<"\n" ;
    #endif

}
mouse :: ~mouse(){
    #ifdef DEBUG
    cout << "mouse  dtor \n";
    #endif
    mouse :: _instance = nullptr;
}
void mouse :: whoami(){
    cout << "ioDevice : mouse \n"; 
}
void mouse :: startApplication(string application){
    cout << "Event triggered by mouse : "<<application<<"\n";
    #ifdef DEBUG
    cout << "\nSTEP 2 : Io Obj triggers event\n";
    #endif
    doubleClick(application);
}

mouse* mouse:: createInstance(){
    if(mouse :: _instance == nullptr){
       
        #ifdef DEBUG
        cout << "creating a new instance of mouse \n";
        #endif

        mouse :: _instance = new mouse();
    }

    return mouse :: _instance;
}

void mouse :: doubleClick(string application){
    #ifdef DEBUG
    cout << "double click method called\n";
    #endif
    port* adaptor  = new port(portNum);
    adaptor->startApplication(application);
}




/*
port adaptor implementations ---------------------------------------------------------------------------
*/
port :: port(int portNum): bus(portNum, "") {
    #ifdef DEBUG
    cout << "port adaptor ctor - for port  no : "<<portNum<<"\n";
    #endif
    }

port :: ~port(){
    #ifdef DEBUG
    cout << "port dtor\n";
    #endif
}

void port :: startApplication(string application){
    this->application= application;
    #ifdef DEBUG
    cout <<"\nSTEP 3 : port calls startapplication \n";
    cout <<"inturn calling storeToMemory of bus\n";
    #endif
    storeToMemory();
}

void port :: whoami(){
    cout <<"port adaptor\n";
}