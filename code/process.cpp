#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "process.h"
#include "memory.h"


using namespace std;

/*
    constructors for process
    it also allocates memory for the process
*/
Process::Process(bool memAccess, int t, int processNum, int port, string appName, int prior): memAccessSlow(memAccess),pid(processNum), portNo(port), applicationName(appName), priority(prior),time(t){
    remainingTime = rand()%((20 - 0) + 1);
    cout << "remaining time for " << appName << " is " << remainingTime << endl;
    cout << "priority of process is " << priority << endl;
    state = waiting;
    mainmemorypool* temp;
    mainmemory* obj;
    temp = mainmemorypool::getInstance();
    obj = temp->findFreeMem();
    obj->setAsUsed(processNum);
    cout << "memory allocated\n";
}

Process::Process(bool memAccess, int t, int processNum, int port, string appName, int prior, int rem): memAccessSlow(memAccess),pid(processNum), portNo(port), applicationName(appName), priority(prior),time(t), remainingTime(rem){
    cout << "remaining time for " << appName << " is " << remainingTime << endl;
    cout << "priority of process is " << priority << endl;
    state = waiting;
    mainmemorypool* temp;
    mainmemory* obj;
    temp = mainmemorypool::getInstance();
    obj = temp->findFreeMem();
    obj->setAsUsed(processNum);
    obj->setData(20);
    cout << "memory allocated\n";
}

Process::~Process(){}

/*
    allocating additional memory bojects for this process
*/
void Process::addMem(int data){
    mainmemorypool* temp;
    mainmemory* obj;
    temp = mainmemorypool::getInstance();
    obj = temp->findFreeMem();
    obj->setAsUsed(pid);
    obj->setData(data);
    cout << "memory allocated\n";
}

/*
    to decrease time after processing
*/
bool Process::decreaseRemainingTime(int t){
    remainingTime-=t;
    return (remainingTime == 0? false:true);
}

bool Process::isMemAccessSlow(){
    return memAccessSlow;
}

void Process::setState(processState s){
    state = s;
}

processState Process::getState(){
    return state;
}

string Process::getApplicationName(){
    return applicationName;
}
