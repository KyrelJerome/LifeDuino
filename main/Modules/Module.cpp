#include <Adafruit_NeoPixel.h>
class Module
{ 
public:
    bool enabled;
    virtual int getState() = 0;
    virtual void setState(int state);
    virtual int totalStates();
    virtual void update() = 0;
    virtual void setup() = 0;
    virtual void disable() = 0;
    virtual void enable() = 0;
};
