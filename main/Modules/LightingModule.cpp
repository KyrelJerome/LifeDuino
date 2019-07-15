#include <Adafruit_NeoPixel.h>
#include "Module.cpp"
class LightingModule(Module)
{
public:
    Adafruit_NeoPixel* strip;
    int currentMode;
    int lastMode;
    int numLights;
    int brightness = 50;

    LightModeStrategy *modes;
    LightingModule(int num; int pin , LightModeStrategy * lightModes) : Module
    {
        strip = malloc(sizeof(Adafruit_NeoPixel);
        strip* = Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);
        this->modes = lightModes;
        enabled = true;
        currentMode = 0;
        lastMode = 0;
    }
    int getState()
    {
        return currentMode;
    }
    void setState(int mode)
    {
        lastMode = currentMode;
        currentMode = mode;
        deskModes[lastMode]->disable();
        deskModes[currentMode]->enable();
    }
    void update()
    {
        if (enabled)
        {
            modes[currentMode].update();
            strip.show();
        }
    }
    void enable()
    {
        this.enabled = true;
        strip.setBrightness(50);
        strip.show();
    }
    void disable()
    {
        enabled = false;
        strip.setBrightness(0);
        strip.show();
    }
    void setup()
    {
        currentMode = 0;
        enable();
    }
};