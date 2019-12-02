#ifndef IO_DEVICE_H_
#define IO_DEVICE_H_

#include <iostream>
using namespace std;

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

    virtual int startApplication(int applicationNumber) = 0;
    virtual void whoami() = 0;

    static ioDevice* create(deviceType type);

};


/*
singleton classes 
*/
class keyboard : public ioDevice {
    private:
    static keyboard* _instance; 

    public :

    static keyboard* createInstance(); 
    
    void whoami();
    int startApplication(int applicationNumber);

    keyboard();
    ~keyboard();
};



class mouse : public ioDevice {

    private:
    static mouse* _instance; 

    public : 
    
    static mouse* createInstance();

    void whoami();
    int startApplication(int applicationNumber);

    mouse();
    ~mouse(); 
};


#endif