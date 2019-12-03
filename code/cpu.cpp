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
    currProcess = nextProcess();
    context = c;
}

Cpu::~Cpu(){
    cout << "cpu destroyed\n";
}

void Cpu::callDMA(){
    cout << "dma called\n";
    int val = fork();
    if(val > 0){
        int s;
        if(waitpid(val, &s, WNOHANG) > 0)
        {
            cout << "dma complete\n";
            kill(val, SIGKILL);
        }
        contextSwitch(nextProcess()); //should clock increase?
        performOperation();
    }
    else if(val == 0){
        // Dma* dma = create_instance();
        sleep(2);
        currProcess->setState(waiting);
    }
}

void Cpu::performOperation(){
    if(currProcess->isMemAccessSlow()){
        callDMA();    
    }
    else{
        cout << "cpu performing operation on " << currProcess->getApplicationName() << "\n";
        increaseClock();
        bool check = currProcess->decreaseRemainingTime(1);
        if(!check){
            currProcess->setState(complete);
            processes.erase(processes.begin());
            contextSwitch(nextProcess());
            performOperation();
        }
        if(clock%3==0){
            contextSwitch(nextProcess());
            performOperation();
        }
        performOperation();
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
        return nextProcess();
    }
    return &processes[0];
}
        
void Cpu::contextSwitch(Process* newProcess){
    currProcess->setState(waiting);
    currProcess = newProcess;
    currProcess->setState(executing);
}

void Cpu::loadJob(job j, int time, bool memAccess){
    cout << "loading job into memory as a process - " << j.getApplicationName() << " at time - " << time << endl;
    Process* p = new Process(memAccess, time, j.getProcessNum(), j.getPortNo(), j.getApplicationName(), j.getPriority());
    addProcess(*p);
}

void Cpu::startProcessing(){
    currProcess = nextProcess();
    currProcess->setState(executing);
    performOperation();
}

void FifoSchedule::changeProcess(deque<Process>& p){
    int mini = p[0].time;
    int index = 0;
    for(int i=1;i<p.size();++i){
        if(p[i].time< mini && p[i].getState() != processState::executing){
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
        if(p[i].priority > maxi && p[i].getState() != processState::executing){
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
        if(p[i].remainingTime > mini && p[i].getState() != processState::executing){
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
