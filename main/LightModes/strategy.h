#include <Adafruit_NeoPixel.h>
class LightModeStrategy
{
public:
    int numLights;
    LightModeStrategy(int nLights)
    {
        numLights = nLights;
    }

    void update(Adafruit_NeoPixel strip)
    {
        if (shouldSetup())
        {
            setup();
        }
        if (shouldUpdate())
        {
            _update(strip);
        }
    }

    virtual void disable(Adafruit_NeoPixel strip) = 0;
    virtual void enable(Adafruit_NeoPixel strip) = 0;
protected:
    virtual void setup() = 0;
    virtual bool shouldSetup() = 0;
    virtual bool shouldUpdate() = 0;
    virtual void _update(Adafruit_NeoPixel strip) = 0;
};