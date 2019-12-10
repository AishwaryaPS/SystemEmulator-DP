#ifndef CPU_H_
#define CPU_H_

#include <deque>
#include "process.h"
#include "job.h"
#include "ioDevice.h"

using namespace std;

enum interruptType{
    software, hardware
};

class interrupt;
class Cpu;

class interrupt{

    string interruptMsg;
    interruptType type;
    string interruptingDevice;

    public :
    interrupt();
    ~interrupt();

    void triggerHardwareInterrupt(Cpu &cpu,ioDevice* interruptCaller, string interruptMsg);
    string getInterruptingDeviceName();
    string getInterruptMsg(); 
};


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
        deque<interrupt> interruptQueue;
    public:
        Cpu();
        Cpu(Context c);
        Cpu(deque<Process> p, Context c);
        ~Cpu();
        bool callDMA();
        bool performOperation();
        void startProcessing();
        void increaseClock();
        int getClock();
        void contextSwitch(Process* newProcess);
        void addProcess(Process p);
        Process* nextProcess();
        void loadJob(job j, int time);
        void interruptHandler(interrupt interruptor);
};


#endif