#include <Adafruit_NeoPixel.h>
class Controller
{ 
public:
    bool enabled;
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void disable() = 0;
    virtual void enable() = 0;
};