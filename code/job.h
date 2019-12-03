#ifndef JOB_H_
#define JOB_H_

#include <iostream>
using namespace std;
/*
job class 
contains feilds which represent a job to be picked up by cpu
bus will create a job and drop off at memeory 
cpu will pick up job form memory
*/
class job{

    int processNum;
    string applicationName;
    int portNo;
    bool ioOperation;
    int priority;

    public:

    job(int processNum, string applicationName, int portNo, bool ioOperation,int priority);
    ~job();
    
    int getProcessNum();
    int getPortNo();
    int getPriority();
    bool isIoOperation();
    string getApplicationName();
};

#endif