#include <Adafruit_NeoPixel.h>

#define REGISTERDELAY 300
class Button : public Controller
{
public:
    int pin;
    int enabled;
    int state;
    int lastState;
    int pressRegistered;
    Module* module;
    long stateStartTime;
    Button(int buttonPin, Module* actuator) : Controller()
    {
        module = actuator;
        pin = buttonPin;
        pinMode(pin, INPUT);
    }
    void init()
    {
        enable();
    }
    void update()
    {
        state = digitalRead(pin);
        if (enabled)
        {
            if (state != lastState)
            {
                stateStartTime = millis();
                if (lastState == HIGH)
                {
                    pressRegistered = false;
                }
            }
            else if(millis() - stateStartTime > REGISTERDELAY && !pressRegistered ){
                pressRegistered = true;
                int moduleState = module->getState() + 1;
                if(moduleState < module->totalStates()){
                    module->setState(moduleState);
                }
                else{
                    module->setState(0);
                }
            }
        }
    }
    void enable()
    {
        enabled = true;
        pressRegistered = false;
        lastState = digitalRead(pin);
        pinMode(pin, INPUT);
        state = lastState;
    }
    void disable()
    {
        enabled = false;
    }

protected:
    int getButtonState()
    {
        return state;
    }
};