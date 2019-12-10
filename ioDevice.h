#ifndef IO_DEVICE_H_
#define IO_DEVICE_H_

#include <iostream>
using namespace std;

#include "bus.h"

/*
using keyboard and mouse for now , to start a process 
keyboard -> click enter
mouse    -> double right click 
*/
enum deviceType{
    typeKeyboard, typeMouse , notSupportedDevice
};


/*
class with the factory method : 'create' 
*/
class ioDevice{

    public:
    ioDevice();
    virtual ~ioDevice();

    virtual void startApplication(string application) = 0;
    virtual string whoami() = 0;

    static ioDevice* create(deviceType type);

    protected:
    static int count;
    int portNum;
};


/*
singleton keyboard classe
*/
class keyboard : public ioDevice {
    private:
    static keyboard* _instance; 
    keyboard();
    keyboard(const keyboard& rhs) = delete;

    public :
    
    ~keyboard();

    static keyboard* createInstance(); 
    
    string whoami();
    void startApplication(string application);

    void clickEnter(string application);
};


/*
singleton mouse classe
*/
class mouse : public ioDevice {

    private:
    static mouse* _instance; 
    mouse();
    mouse(const mouse& rhs) = delete;

    public : 

    ~mouse();

    static mouse* createInstance();

    string whoami();
    void startApplication(string application);

    void doubleClick(string application);
     
};


/*
port class that acts as an adaptor between ioDevice and Bus
*/
class port :  private bus, public ioDevice{

    public:
    port(int portNum);
    ~port();

    void startApplication(string application);

    string whoami();

}; 



#endif