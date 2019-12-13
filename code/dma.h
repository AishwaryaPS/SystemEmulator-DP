#ifndef Dma_H_
#define Dma_H_

#include "memory.h"

/*
    Singleton direct memory access object
    To access memory without blocking the cpu
*/
class Dma{
    private:
    static Dma* _instance; 
    Dma(){};
    Dma(const Dma& rhs) = delete;

    public :
    
    ~Dma();
    void findMem(int pid);
    static Dma* createInstance(); 
};
#endif