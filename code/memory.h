#ifndef MEMORY_H_
#define MEMORY_H_


#include <iostream>
using namespace std;
#include <deque>

#include "job.h"

/*
memeory class
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

    /* no need for these 
    class iterator{
        
        deque<job> jobQueueIter;

        public:
        iterator(deque<job> &jobs):jobQueueIter(jobs) {
            #ifdef DEBUG
            cout<<"memory iter ctor \n";
            #endif
        }

        //job operator[](int n){
        //    return jobQueueIter[n];
        //}

        job operator *() const {
            return jobQueueIter.front();
        }

        iterator operator++(int){
            iterator temp(*this);
            jobQueueIter.pop_front();
            return temp;
        }

        iterator operator++(){
            jobQueueIter.pop_front();
            return *this;
        }



    };

    iterator begin();
    iterator end();

    */
    

};

/*
declared extern so that multiple files can access the same mem obj
needed when bus class drops a new job in memory
and cpu has to pick it up
*/
extern memory memBlock;

class mainmemory{
    private:
        int data;
        uint32_t address;
};

#endif