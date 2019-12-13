#include <iostream>
#include <unistd.h>
#include "dma.h"

using namespace std;

Dma* Dma::_instance = nullptr;

Dma* Dma::createInstance(){
    if(Dma::_instance == nullptr){       
        cout << "creating a new instance of Dma \n";
        Dma::_instance = new Dma();
    }
    return Dma::_instance;
}

/*
    operation to find memory that unblocks cpu
*/
void Dma::findMem(int pid){
    cout << "Dma finding required memory object\n";
    mainmemorypool* memPool = mainmemorypool::getInstance();
    mainmemory* memObj;
    memObj = memPool->findUsedMem(pid);
    if(memObj)
        cout << "Dma found memory object for pid " << memObj->getPid() << " at " << &memObj << "\n";
}