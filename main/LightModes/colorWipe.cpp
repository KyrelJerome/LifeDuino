//#include <Adafruit_NeoPixel.h>
#include "strategy.h"
class WipeModeStrategy : public LightModeStrategy
{
public:
    bool hasWiped;
    bool hasSetup;
    uint32_t colour;
    WipeModeStrategy(uint32_t colour, int numLights) : LightModeStrategy(numLights)
    {
        this->hasWiped = false;
        this->colour = colour;
        this->hasSetup = 0;
    }
    void disable()
    {
        this->hasWiped = true;
    }
    void enable()
    {
        this->hasWiped = false;
    }

    void setup()
    {
        this->hasSetup = true;
    }

    bool shouldSetup()
    {
        //return !(this->hasSetup);
        Serial.println("setup marker");
        delay(1000);
        return false ;
    }

    bool shouldUpdate()
    {
        return !(this->hasWiped);
    }
    
    void _update(Adafruit_NeoPixel *strip)
    {
        for (int i = 0; i < numLights; i++)
        {
            strip->setPixelColor(i, colour);
        }
        this->hasWiped = true;
    }
};
