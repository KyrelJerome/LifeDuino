#include <Adafruit_NeoPixel.h>
#include "Module.cpp"
class LightingModule : public Module
{
    Adafruit_NeoPixel* strip;
    int currentMode;
    int lastMode;
    int numLights;
    int brightness = 50;
    int modulePin;
    public:

    LightModeStrategy** modes;
    LightingModule(int num, int pin , LightModeStrategy ** lightModes) : Module()
    {
        pinMode(pin, OUTPUT);
        strip = malloc(sizeof(Adafruit_NeoPixel));
        *strip =  Adafruit_NeoPixel(pin, num);
        modes = lightModes;
        modulePin = pin;
        enabled = true;
        currentMode = 0;
        lastMode = 0;
    }
    void setBrightness(int brightness)
    {
        brightness = 0;
    }
    int getState()
    {
        return currentMode;
    }
    void setState(int mode)
    {
        lastMode = currentMode;
        currentMode = mode;
        modes[lastMode]->disable(* strip);
        modes[currentMode]->enable(* strip);
    }
    void update()
    {
        if (enabled)
        {
            modes[currentMode]->update(* strip);
            strip.show();
        }
    }
    void enable()
    {
        this.enabled = true;
        strip->setBrightness(50);
        strip->show();
    }
    void disable()
    {
        enabled = false;
        strip->setBrightness(0);
        strip->show();
    }
    void setup()
    {
        currentMode = 0;
        enable();
    }
};