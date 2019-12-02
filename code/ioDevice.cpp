#include "ioDevice.h"


/*
private static instance variables of each device type to be redeclared here 
and assigned  nullptr
*/
keyboard* keyboard :: _instance = nullptr;
mouse* mouse :: _instance = nullptr;


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
    cout << "type :"<< type <<"\n";
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
        return nullptr;
    }
}



/*
keyboard implementations ---------------------------------------------------------------------------
*/
keyboard :: keyboard(){
    #ifdef DEBUG
    cout << "keyboard  ctor \n";
    #endif
}

keyboard :: ~keyboard(){
    #ifdef DEBUG
    cout << "keyboard  dtor \n";
    #endif
}
void keyboard :: whoami(){
    cout << "ioDevice : keyboard \n"; 
}
int keyboard :: startApplication(int applicationNumber){
    cout << "Event triggered by keyboard\n";
    return 1;
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

/*
mouse implementations ---------------------------------------------------------------------------
*/
mouse :: mouse(){
    #ifdef DEBUG
    cout << "mouse  ctor \n";
    #endif
}
mouse :: ~mouse(){
    #ifdef DEBUG
    cout << "mouse  dtor \n";
    #endif
}
void mouse :: whoami(){
    cout << "ioDevice : mouse \n"; 
}
int mouse :: startApplication(int applicationNumber){
    cout << "Event triggered by mouse\n";
    return 1;
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