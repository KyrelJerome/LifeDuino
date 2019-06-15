#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
//OUTPUT PINS
#define RING_PIN 7
#define LEFT_PIN 6
#define RIGHT_PIN 5
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

#define WHITE stripRing.color(255, 255, 255)
#define GREEN stripRing.Color(0, 255, 0)
#define RED stripRing.Color(255, 0, 0)
#define BLUE stripRing.Color(0, 0, 255)
#define YELLOW stripRing.Color(255, 255, 0)
#define OFF stripRing.Color(0, 0, 0)

Adafruit_NeoPixel stripRight = Adafruit_NeoPixel(18, RIGHT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLeft = Adafruit_NeoPixel(18, LEFT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripRing = Adafruit_NeoPixel(16, RING_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    // put your setup code here, to run once:
    //Sets RIO related pins to INPUT
    pinMode(RIO_PINA, INPUT);
    pinMode(RIO_PINB, INPUT);
    pinMode(TOGGLE_PIN, INPUT);

    pinMode(RING_PIN, OUTPUT);
    pinMode(RIGHT_PIN, OUTPUT);
    pinMode(LEFT_PIN, OUTPUT);

    stripRight.begin();
    stripRight.show();

    stripLeft.begin();
    stripLeft.show();

    stripRing.begin();
    stripRing.show();
}

int AState = 0;
int BState = 0;
int toggleState = 0;
int currentMode = 0;
void loop()
{
    // put your main code here, to run repeatedly:
    AState = digitalRead(RIO_PINA);
    BState = digitalRead(RIO_PINB);
    lastMode = -1;
    currentMode = 0;
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
        lastMode = curentMode;
    }
    stripLeft.show();
    stripRight.show();
    stripRing.show();
    delay(40);
}
void colorWipe(int32_t c)
{
    for (int i = 0; i < 18; i++)
    {
        stripRight.setPixelColor(i, GREEN);
        stripLeft.setPixelColor(i, GREEN);
    }
    for (int i = 0; i < 17; i++)
    {
        stripRing.setPixelColor(i, GREEN);
    }
}