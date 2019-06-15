class LightStrategy
{
public:
    LightModeStrategy(int numLights)
    {
        this.numLights = numLights;
    }

    void update()
    {
        if (shouldSetup())
        {
            setup();
        }
        if (shouldUpdate())
        {
            _update();
        }
    }
    
    virtual void disable() = 0;
    virtual void setup() = 0;

private:
    virtual void shouldSetup() = 0;
    virtual void shouldUpdate() = 0;
    virtual void _update() = 0;
    int numLights;
}