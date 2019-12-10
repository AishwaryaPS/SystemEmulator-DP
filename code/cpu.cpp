#include <deque>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "cpu.h"
#include "dma.h"


using namespace std;

Cpu::Cpu(){}

Cpu::Cpu(Context c){
    cout << "cpu created\n";
    clock = 0;
    context = c;
}

Cpu::Cpu(deque<Process> p, Context c){
    cout << "cpu created\n";
    clock = 0;
    processes = p;
    if(p.empty())
        throw invalid_argument("Must provide some processes");
    currProcess = nextProcess();
    context = c;
}

Cpu::~Cpu(){
    cout << "cpu destroyed\n";
}


bool Cpu::callDMA(){
    #ifndef WINDOWS
    Process* nextP;
    cout << "dma called\n";
    int val = fork();
    if(val > 0){
        int s;
        if(waitpid(val, &s, WNOHANG) > 0)
        {
            cout << "dma complete\n";
            kill(val, SIGKILL);
        }
        nextP = nextProcess();
            if(nextP == nullptr)
                return false;
            contextSwitch(nextP); //should clock increase?
        return performOperation();
    }
    else if(val == 0){
        Dma* dma = Dma::createInstance();
        dma->findMem();
        currProcess->setState(waiting);
    }
    #endif
    return true;
}

bool Cpu::performOperation(){

    while(!interruptQueue.empty()){
        cout << "process stalled for taking care of interrupt ... \n";
        cout << "interrupted by : " << interruptQueue.front().getInterruptingDeviceName() << "\n";
        cout << "msg : " << interruptQueue.front().getInterruptMsg() << "\n";
        interruptQueue.pop_front();
    }
    
    Process* nextP;
    if(currProcess->isMemAccessSlow()){
        currProcess->setState(memoryop);
        return callDMA();    
    }
    else{
        cout << "cpu performing operation on " << currProcess->getApplicationName() << "\n";
        increaseClock();
        bool check = currProcess->decreaseRemainingTime(1);
        if(!check){
            currProcess->setState(complete);
            processes.erase(processes.begin());
            nextP = nextProcess();
            if(nextP == nullptr)
                return false;
            contextSwitch(nextP);
            return performOperation();
        }
        if(clock%3==0){
            nextP = nextProcess();
            if(nextP == nullptr)
                return false;
            contextSwitch(nextP);
            return performOperation();
        }
        return performOperation();
    }
}
        
void Cpu::increaseClock(){
    ++clock;
    cout << "clock: " << clock << "\n";
}

int Cpu::getClock(){
    return clock;
}

void Cpu::addProcess(Process p){
    processes.push_back(p);
}

Process* Cpu::nextProcess(){
    context.schedulingStrategy->changeProcess(processes);
    if(processes.size()==0){
        cout << "waiting for more processes\n";
        sleep(1);
        while(!interruptQueue.empty()){
        cout << "process stalled for taking care of interrupt ... \n";
        cout << "interrupted by : " << interruptQueue.front().getInterruptingDeviceName() << "\n";
        cout << "msg : " << interruptQueue.front().getInterruptMsg() << "\n";
        interruptQueue.pop_front();
        }
        return nullptr;
    }
    return &processes[0];
}
        
void Cpu::contextSwitch(Process* newProcess){
    currProcess->setState(waiting);
    currProcess = newProcess;
    currProcess->setState(executing);
}

void Cpu::loadJob(job j, int time){
    cout << "loading job into memory as a process - " << j.getApplicationName() << " at time - " << time << endl;
    bool isSlow = false; // just so dma isnt called 
    Process* p = new Process(j.isIoOperation() && isSlow, time, j.getJobNum(), j.getPortNo(), j.getApplicationName(), j.getPriority());
    addProcess(*p);
}

bool Cpu::startProcessing(){
    currProcess = nextProcess();
    if(currProcess == nullptr)
        return false;
    currProcess->setState(executing);
    return performOperation();
}


void Cpu::interruptHandler(interrupt interruptor){

    interruptQueue.push_back(interruptor);
}



void FifoSchedule::changeProcess(deque<Process>& p){
    int mini = p[0].time;
    int index = 0;
    for(int i=1;i<p.size();++i){
        // cout << p[i].getState() << "\n";
        if(p[i].time< mini && p[i].getState() != processState::memoryop){
            index = i;
            mini = p[i].time;
        }
    }
    if(index != 0){
        Process temp = p[0];
        p[0] = p[index];
        p[index] = temp;
    }
}

void PrioritySchedule::changeProcess(deque<Process>& p){
    int maxi = p[0].priority;
    int index = 0;
    for(int i=1;i<p.size();++i){
        if(p[i].priority > maxi && p[i].getState() != processState::memoryop){
            index = i;
            maxi = p[i].priority;
        }
    }
    if(index != 0){
        Process temp = p[0];
        p[0] = p[index];
        p[index] = temp;
    }
}

void SjfSchedule::changeProcess(deque<Process>& p){
    int mini = p[0].remainingTime;
    int index = 0;
    for(int i=1;i<p.size();++i){
        if(p[i].remainingTime > mini && p[i].getState() != processState::memoryop){
            index = i;
            mini = p[i].remainingTime;
        }
    }
    if(index != 0){
        Process temp = p[0];
        p[0] = p[index];
        p[index] = temp;
    }
}

void RoundRobinSchedule::changeProcess(deque<Process>& p){
    Process curr = p.front();
    p.pop_front();
    p.push_back(curr);
}

Context::Context(SchedulingStrategy* strategy): schedulingStrategy(strategy){}

Context::Context(){}




interrupt :: interrupt(){
    #ifdef DEBUG
    cout << "interrupt ctor\n";
    #endif
}


interrupt :: ~interrupt(){
    #ifdef DEBUG
    cout << "interrupt dtor\n";
    #endif
}

void interrupt :: triggerHardwareInterrupt(Cpu &cpu,ioDevice* interruptCaller, string interruptMsg){
    #ifdef DEBUG
    cout << "hardware interrupt has been triggered\n";
    #endif
    this->interruptMsg = interruptMsg;
    this->type = hardware;
    this->interruptingDevice = interruptCaller->whoami();

    cpu.interruptHandler(*this);

}

string interrupt :: getInterruptingDeviceName(){
    return interruptingDevice;
}

string interrupt :: getInterruptMsg(){
    return interruptMsg;
}
