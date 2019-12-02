#include "bus.h"
/*
initialzise static memenber processNum that keeps a count of events triggered
*/
int bus::processNum = 0; 


bus :: bus(int portNum, string application): application(application) , portNum(portNum){
    ++processNum;
    #ifdef DEBUG
    cout << "bus ctor -- port : "<< portNum<< " & application :" <<application<<"\n"; 
    #endif
}

bus :: ~bus(){
    #ifdef DEBUG
    cout <<"bus dtor \n";
    #endif
}
/*
need to fill this with relavent code once memory component done
*/
void bus :: storeToMemory(){
    cout <<"application : "<<application<<" from portNum :"<<portNum<<"\n";
    cout <<"process : " << bus::processNum <<  " written to memory \n";
}
