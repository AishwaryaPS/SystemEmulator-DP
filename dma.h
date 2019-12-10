#ifndef Dma_H_
#define Dma_H_

class Dma{
    private:
    static Dma* _instance; 
    Dma(){};
    Dma(const Dma& rhs) = delete;

    public :
    
    ~Dma();
    void findMem();
    static Dma* createInstance(); 
};
#endif