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
        *strip =  & Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);
        modes = lightModes;
        modulePin = pin;
        enabled = true;
        currentMode = 0;
        lastMode = 0;
    }
    void setBrightness(int newBrightness)
    {
        brightness =  newBrightness;
        strip->setBrightness(brightness);
    }
    int getState()
    {
        return currentMode;
    }
    void setState(int mode)
    {
        lastMode = currentMode;
        currentMode = mode;
        modes[lastMode]->disable();
        modes[currentMode]->enable();
    }
    void update()
    {
        if (enabled)
        {
            modes[currentMode]->update(strip);
            strip->show();
        }
    }
    void enable()
    {
        enabled = true;
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