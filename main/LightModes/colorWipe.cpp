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
    }
    void disable()
    {
        hasWiped = true;
    }
    void enable()
    {
        hasWiped = false;
    }

protected:
    void setup()
    {
        this->hasSetup = true;
    }
    bool shouldSetup()
    {
        return !hasSetup;
    }
    bool shouldUpdate()
    {
        return !this->hasWiped;
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
