#include <Adafruit_NeoPixel.h>
#include "Module.cpp"
class LightingModule : public Module
{
    Adafruit_NeoPixel *strip;
    int currentMode;
    int numModes;
    int numLights;
    int brightness;
    int modulePin;
    int lastMode;
public:
    LightModeStrategy **modes;
    LightingModule(int totalModes, int totalLights, int pin, LightModeStrategy **lightModes) : Module()
    {
        pinMode(pin, OUTPUT);   
        strip = malloc(sizeof(Adafruit_NeoPixel));
        *strip  = Adafruit_NeoPixel(totalLights, pin, NEO_GRB + NEO_KHZ800);
        modes = lightModes;
        brightness = 50;
        modulePin = pin;
        enabled = true;
        currentMode = 0;
        lastMode = 0;
    }
    int totalStates(){
        return numModes;
    }
    void setBrightness(int newBrightness)
    {
        Serial.println("Module: Brightness Set");
        delay(1000);
        brightness = newBrightness;
        strip->setBrightness(brightness);
    }
    int getState()
    {
        Serial.println("Module: Getting State ");
        delay(1000);
        return currentMode;
    }
    void setState(int mode)
    {
        Serial.println("Module: State Set");
        delay(1000);
        if (mode < numModes)
        {
            lastMode = currentMode;
            currentMode = mode;
            modes[lastMode]->disable();
            modes[currentMode]->enable();
        }
        else{
            Serial.println("Module: Mode out of bounds wtf!")
        }
    }
    void update()
    {
        Serial.println("Module: Updating");
        delay(1000);
        if (enabled)
        {
            Serial.println("Module: Updating Strip");
            delay(1000);
            modes[currentMode]->update(strip);
            Serial.println("Module: Showing Strip");
            delay(1000);
            strip->show();
        }
        Serial.println("Module: Updated");
        delay(1000);
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
