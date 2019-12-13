#ifndef JOB_H_
#define JOB_H_

#include <iostream>
using namespace std;
/*
job class 
contains fields which represent a job to be picked up by cpu
bus will create a job and drop off at memeory 
cpu will pick up job from memory
*/
class job{

    int jobNum;
    string applicationName;
    int portNo;
    bool ioOperation;
    int priority;

    public:

    job(int jobNum, string applicationName, int portNo, bool ioOperation,int priority);
    ~job();
    
    int getJobNum();
    int getPortNo();
    int getPriority();
    bool isIoOperation();
    string getApplicationName();
};

#endif