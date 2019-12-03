#include "memory.h"
#include "cpu.h"


memory :: memory():numOfJobs(0){
    #ifdef DEBUG
    cout << "memory ctor \n";
    #endif
}
memory :: ~memory(){
    #ifdef DEBUG
    cout << "memory dtor \n";
    #endif
}


void memory :: addJob(job newJob){
    #ifdef DEBUG
    cout << "\nSTEP 5: new job being added to memory\n";
    #endif

    this->jobQueue.push_back(newJob);
    cout << "New Job \'"<< newJob.getApplicationName() <<"\' added to wait queue.\n";
} 

bool memory :: hasNext(){
    #ifdef DEBUG
    cout << boolalpha;
    cout <<"has next called -- "<< (jobQueue.end() != jobQueue.begin()) <<"\n";
    #endif
    return jobQueue.end() != jobQueue.begin();
}

job memory :: next(){
    #ifdef DEBUG
    cout << "next called \n";
    #endif
    job temp(jobQueue.front());
    jobQueue.pop_front();
    return temp;
}