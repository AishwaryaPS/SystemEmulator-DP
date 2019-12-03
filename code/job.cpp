#include "job.h"

/*
job class implementations ----------------------------------------------------------------------------------
*/

job :: job(int processNum, string applicationName, int portNo, bool ioOperation,int priority) :
processNum(processNum), applicationName(applicationName), portNo(portNo), ioOperation(ioOperation), priority(priority){
    #ifdef DEBUG
    cout << "job ctor \n";
    #endif
}

job :: ~job(){
    #ifdef DEBUG
    cout << "job dtor \n";
    #endif
}


int job :: getProcessNum(){
    return this->processNum;
}
int job :: getPortNo(){
    return this->portNo;
}
int job :: getPriority(){
    return this->priority;
}

bool job :: isIoOperation(){
    return this->ioOperation;
}
string job :: getApplicationName(){
    return this->applicationName;
}
