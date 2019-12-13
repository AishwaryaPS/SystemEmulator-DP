#ifndef PROCESS_H_
#define PROCESS_H_

#include <vector>
#include "memory.h"
#include "job.h"

using namespace std;

enum processState{
    waiting, memoryop, executing, complete
};

class Process{
    private:
        int pid;
        int time;
        bool memAccessSlow;
        int remainingTime;
        int priority;
        string applicationName;
        int portNo;
        processState state;
    public:
        Process(bool memAccess, int t, int processNum, int port, string appName, int prior);
        Process(bool memAccess, int t, int processNum, int port, string appName, int prior, int rem);
        ~Process();
        void addMem(int data);
        bool decreaseRemainingTime(int t); // returns false if remaining time is 0
        bool isMemAccessSlow();
        void setState(processState);
        processState getState();
        string getApplicationName();

    friend class FifoSchedule;
    friend class PrioritySchedule;
    friend class SjfSchedule;
    friend class RoundRobinSchedule;
    friend class SchedulingStrategy;
    friend class Cpu;
};

#endif