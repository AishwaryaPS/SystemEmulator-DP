#ifndef MEMORY_H_
#define MEMORY_H_


#include <iostream>
using namespace std;
#include <deque>
#include <vector>
#include "job.h"

/*
    multiple memory classes implementation
    ready queue with jobs is held in the memory class
*/
class memory{  

    deque<job> jobQueue; 
    int numOfJobs;
    
    public:

    memory();
    ~memory();
    memory& operator =(const memory&) = delete;
    memory(const memory&) = delete;

    void addJob(job newJob);

    // iterator functions
    bool hasNext();
    job next();

};

/*
declared extern so that multiple files can access the same mem obj
needed when bus class drops a new job in memory
and cpu has to pick it up
*/
extern memory memBlock;

/*
    mainmemory class that holds data relevant to processes
*/
class mainmemory{
    private:
        bool isUsed;
        int data;
        int pid;
    public:
        mainmemory():isUsed(false),data(0){};
        int getData();
        void setData(int val);
        bool isMemObjUsed();
        void setAsUsed(int p);
        void releaseMem();
        int getPid();
};

/*
    mainmemorypool is a singleton class
    it is an object pool used to handle mainmemory
    it has a fixed size that is allocatedin its constructor
    uses two patterns: singleton and object pool
*/
class mainmemorypool {
    private:
        static mainmemorypool* _instance;
        vector<mainmemory> memoryPool;
        mainmemorypool(){
            memoryPool.resize(100);
        }
        mainmemorypool(const mainmemory& rhs) = delete;
    public:
        mainmemory* findFreeMem();
        mainmemory* findUsedMem(int pid);
        void freeMem(int pid);
        static mainmemorypool* getInstance();
};

#endif