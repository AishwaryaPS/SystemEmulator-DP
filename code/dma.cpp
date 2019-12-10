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

void Dma::findMem(){
    cout << "Dma finding required memory object\n";
    sleep(2);
    cout << "Dma found memory object\n";
}