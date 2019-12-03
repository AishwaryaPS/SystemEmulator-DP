#ifndef BUS_H_
#define BUS_H_

#include <iostream>
using namespace std;

#include "job.h"
#include "memory.h"
/*
bus class will keep updating the processes into memory 
from which the cpu can fetch one by one 
*/
class bus{

    public:
    bus(int portNum, string application);
    ~bus();

    void storeToMemory(bool isIoOperation);
   
    protected:
    static int processNum;
    string application;
    int portNum;

};


#endif