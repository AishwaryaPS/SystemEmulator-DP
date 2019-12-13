#include "memory.h"
#include "cpu.h"

#include <vector>

/*
    multiple memory classes implementation
    memory class is for the part of the memory that is used by the OS
    mainmemory class that holds data relevant to processes
    mainmemorypool is a singleton class
    it is an object pool used to handle mainmemory
*/

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

int mainmemory::getData(){
    return data;
}

void mainmemory::setData(int val){
    data = val;
}

bool mainmemory::isMemObjUsed(){
    return isUsed;
}

void mainmemory::setAsUsed(int p){
    isUsed = true;
    pid = p;
}

void mainmemory::releaseMem(){
    isUsed = false;
}

int mainmemory::getPid(){
    return pid;
}

mainmemorypool* mainmemorypool::_instance = nullptr;

/*
    find free memory to allocate to processes
*/
mainmemory* mainmemorypool::findFreeMem(){
    for(int i=0;i<memoryPool.size();++i){
        if(memoryPool[i].isMemObjUsed() == false){
            return &memoryPool[i];
        }
    }

    return nullptr;
}

/*
    used by dma to find process relevant memory
*/
mainmemory* mainmemorypool::findUsedMem(int pid){
    for(int i=0;i<memoryPool.size();++i){
        if(memoryPool[i].isMemObjUsed() && memoryPool[i].getPid() == pid){
            return &memoryPool[i];
        }
    }

    return nullptr;
}

/*
    used by process destructor to free the memory occupied by that process
*/
void mainmemorypool::freeMem(int pid){
    for(int i=0;i<memoryPool.size();++i){
        if(memoryPool[i].isMemObjUsed() && memoryPool[i].getPid() == pid){
            cout << "freeing memory\n";
            memoryPool[i].releaseMem();
        }
    }
}

/*
    get singleton instance
*/
mainmemorypool* mainmemorypool::getInstance(){
    if(mainmemorypool::_instance == nullptr){       
        cout << "creating a new instance of mainmemorypool \n";
        mainmemorypool::_instance = new mainmemorypool();
    }
    return mainmemorypool::_instance;
}