#include "bus.h"
/*
initialzise static memenber processNum that keeps a count of events triggered
*/
int bus::processNum = 0; 


bus :: bus(int portNum, string application): application(application) , portNum(portNum){
    ++processNum;
    #ifdef DEBUG
    cout << "bus ctor \n"; 
    #endif
}

bus :: ~bus(){
    #ifdef DEBUG
    cout <<"bus dtor \n";
    #endif
}

/*
bus will wrap the event as a new 'job' and add to the memory
*/
void bus :: storeToMemory(bool isIoOperation){
    int priority = rand() % 5 ; 
    #ifdef DEBUG
    cout << "\nSTEP 4 : BUS will keep a record of this process in memory for cpu to pick up\n";
    
    cout <<"application : "<<application<<" from portNum :"<<portNum<<"\n";
    cout <<"process : " << bus::processNum <<  " written to memory \n";
    cout << "priorty set to : "<<priority <<"\n";
    #endif
    
    memBlock.addJob(job(bus::processNum, application, portNum, isIoOperation, priority));
}


