#include <Adafruit_NeoPixel.h>
class LightModeStrategy
{
public:
    int numLights;
    LightModeStrategy(int nLights)
    {
        numLights = nLights;
    }

    void update(Adafruit_NeoPixel* strip)
    {
        Serial.println("LightStrategy: Updating");
        delay(1000);
        if (shouldSetup())
        {
            Serial.println("LightStrategy: Calling internal setup strip");
            delay(1000);
            setup();
        }
        if (shouldUpdate())
        {
            
            Serial.println("LightStrategy: Calling internal Update strip");
            delay(1000);
            _update(strip);
        }
    }

    virtual void disable() = 0;
    virtual void enable() = 0;
protected:
    virtual void setup() = 0;
    virtual bool shouldSetup() = 0;
    virtual bool shouldUpdate() = 0;
    virtual void _update(Adafruit_NeoPixel* strip) = 0;
};
