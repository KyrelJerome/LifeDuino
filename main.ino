#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
//OUTPUT PINS
#define DESK_PIN 6
//INPUT PINS
#define RIO_PINA 4
#define RIO_PINB 3
#define TOGGLE_PIN 2
// DEFINE RIO MODES

#define MODE_GREEN 0
#define MODE_YELLOW 1
#define MODE_RED 2
#define MODE_BLUE 3
#define SHOWBOAT 4

#define WHITE stripDesk.Color(255, 255, 255)
#define GREEN stripDesk.Color(0, 255, 0)
#define RED stripDesk.Color(255, 0, 0)
#define BLUE stripDesk.Color(0, 0, 255)
#define YELLOW stripDesk.Color(255, 255, 0)
#define OFF stripDesk.Color(0, 0, 0)

#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50
Adafruit_NeoPixel stripDesk = Adafruit_NeoPixel(NUM_LIGHTS_DESK, DESK_PIN, NEO_GRB + NEO_KHZ800);

int AState;
int BState;
int toggleState;
int currentMode;
int lastMode;

void setup()
{
    Serial.begin(9600);
    // put your setup code here, to run once:
    //Sets RIO related pins to INPUT
    pinMode(RIO_PINA, INPUT);
    pinMode(RIO_PINB, INPUT);
    pinMode(TOGGLE_PIN, INPUT);

    pinMode(DESK_PIN, OUTPUT);
    stripDesk.show();
    stripDesk.setBrightness(50);
    AState = 0;
    BState = 0;
    toggleState = 0;
    lastMode = -1;
    currentMode = 0;
}

void loop()
{
    updateInputs();
    updateMode();
    if (currentMode != lastMode)
    {
        switch (currentMode)
        {
        case MODE_YELLOW:
            colorWipe(YELLOW);
            break;
        case MODE_GREEN:
            colorWipe(GREEN);
            break;
        case MODE_RED:
            colorWipe(RED);
            break;
        case MODE_BLUE:
            colorWipe(BLUE);
        }
        lastMode = currentMode;
    }
    update();
    stripDesk.show();
    delay(40);
}
updateInputs()
{
    AState = digitalRead(RIO_PINA);
    BState = digitalRead(RIO_PINB);
}
updateMode()
{

    if (AState == 1 && BState == 1)
    {
        currentMode = MODE_BLUE;
    }
    else if (AState == 1 && BState == 0)
    {
        currentMode = MODE_YELLOW;
    }
    else if (AState == 0 && BState == 1)
    {
        currentMode = MODE_RED;
    }

    else if (AState == 0 && BState == 0)
    {
        currentMode = MODE_GREEN;
    }
    else
    {
        currentMode = MODE_GREEN;
    }
}
update(){
    
}

void colorWipe(int32_t c)
{
    for (int i = 0; i < NUM_LIGHTS_DESK; i++)
    {
        stripDesk.setPixelColor(i, c);
    }
}
