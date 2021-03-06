//#include <Adafruit_NeoPixel.h>
#define updateDelay 100
class RainbowGlowStrategy : public LightModeStrategy
{
public:
    long firstPixelHue;
    long lastUpdate;
    bool hasSetup;
    RainbowGlowStrategy(int numLights) : LightModeStrategy(numLights)
    {
        firstPixelHue = 0;
        lastUpdate = millis();
        this->hasSetup = 0;
    }
    void disable()
    {
    }
    void enable()
    {
        this->hasSetup = false;
    }
    void setup()
    {
        this->firstPixelHue = 0;
        this->lastUpdate = millis();
        this->hasSetup = true;
    }
    bool shouldSetup()
    {
        return !(this->hasSetup);
    }
    bool shouldUpdate()
    {
        return !(this->lastUpdate + updateDelay <= millis());
    }
    void _update(Adafruit_NeoPixel *strip)
    {
        this->firstPixelHue += 256;
        if (firstPixelHue > 5 * 65536)
        {
            firstPixelHue = 0;
        }
        for (int i = 0; i < strip->numPixels(); i++)
        { // For each pixel in strip...
            // Offset pixel hue by an amount to make one full revolution of the
            // color wheel (range of 65536) along the length of the strip
            // (strip.numPixels() steps):
            int pixelHue = firstPixelHue + (i * 65536L / strip->numPixels());
            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
            // optionally add saturation and value (brightness) (each 0 to 255).
            // Here we're using just the single-argument hue variant. The result
            // is passed through strip.gamma32() to provide 'truer' colors
            // before assigning to each pixel:
            strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue)));
        }
        this->lastUpdate = millis();
        strip->show(); // Update strip with new contents
    }
};
