#include "job.h"

/*
job class implementations ----------------------------------------------------------------------------------
*/

job :: job(int jobNum, string applicationName, int portNo, bool ioOperation,int priority) :
jobNum(jobNum), applicationName(applicationName), portNo(portNo), ioOperation(ioOperation), priority(priority){
    #ifdef DEBUG
    cout << "job ctor \n";
    #endif
}

job :: ~job(){
    #ifdef DEBUG
    cout << "job dtor \n";
    #endif
}


int job :: getJobNum(){
    return this->jobNum;
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
