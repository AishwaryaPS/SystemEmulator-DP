#ifndef CPU_H_
#define CPU_H_

#include <deque>
#include "process.h"
#include "job.h"

using namespace std;

class SchedulingStrategy{
    public:
        SchedulingStrategy(){}
        virtual ~SchedulingStrategy(){}
        virtual void changeProcess(deque<Process>&) = 0;
};

class FifoSchedule: public SchedulingStrategy{
    public:
        FifoSchedule(){}
        ~FifoSchedule(){}
        void changeProcess(deque<Process>&);
};

class PrioritySchedule: public SchedulingStrategy{
    public:
        PrioritySchedule(){}
        ~PrioritySchedule(){}
        void changeProcess(deque<Process>&);
};

class SjfSchedule: public SchedulingStrategy{
    public:
        SjfSchedule(){}
        ~SjfSchedule(){}
        void changeProcess(deque<Process>&);
};

class RoundRobinSchedule: public SchedulingStrategy{
    public:
        RoundRobinSchedule(){}
        ~RoundRobinSchedule(){}
        void changeProcess(deque<Process>&);
};

class Context{
    public:
        SchedulingStrategy* schedulingStrategy;
        Context(SchedulingStrategy*);
        Context();
};

class Cpu{
    private:
        Process* currProcess;
        int clock;
        deque<Process> processes;
        Context context;
    public:
        Cpu();
        Cpu(Context c);
        Cpu(deque<Process> p, Context c);
        ~Cpu();
        bool callDMA();
        bool performOperation();
        bool startProcessing();
        void increaseClock();
        int getClock();
        void contextSwitch(Process* newProcess);
        void addProcess(Process p);
        Process* nextProcess();
        void loadJob(job j, int time, bool memAccess);
};


#endif