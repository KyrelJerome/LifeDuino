#include <Adafruit_NeoPixel.h>
#include "../Modules/Module.cpp"

#define INPUTDELAY 300
class ButtonController : public Controller
{
public:
    Module *module;
    #define INPUTDELAY 300

    int enabled;
    Button(): Controller()
    {
    }
    void init(){
        enabled = true;
    }
    void update()
    {
        if (enabled)
        {
            if(){

            }
        }
    }
    void enable()
    {

    }
    void disable()
    {

    }
};