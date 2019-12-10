#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include "process.h"

using namespace std;

Process::Process(bool memAccess, int t, int processNum, int port, string appName, int prior): memAccessSlow(memAccess),pid(processNum), portNo(port), applicationName(appName), priority(prior),time(t){
    remainingTime = rand()%((20 - 0) + 1);
    cout << "remaining time for " << appName << " is " << remainingTime << endl;
    state = waiting;
}

Process::Process(bool memAccess, int t, int processNum, int port, string appName, int prior, int rem): memAccessSlow(memAccess),pid(processNum), portNo(port), applicationName(appName), priority(prior),time(t), remainingTime(rem){
    cout << "remaining time for " << appName << " is " << remainingTime << endl;
    state = waiting;
}

Process::~Process(){}

void Process::addMem(mainmemory m){
    associatedMem.push_back(m);
}

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

int Process::getRemainingTime(){
    return remainingTime;
}