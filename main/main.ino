#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "LightModes/colorWipe.cpp"
#include "Modules/LightingModule.cpp"
#ifdef __AVR__
#include <avr/power.h>
#endif
//OUTPUT PINS
#define DESK_PIN 6

//INPUT PINS
#define RIO_PINA 4
#define RIO_PINB 3
#define TOGGLE_PIN 2

// DEFINE LIGHT MODES
#define MODE_GREEN 0
#define MODE_RED 1
#define MODE_BLUE 2
#define MODE_WHITE 3

#define WHITE stripDesk.Color(255, 255, 255)
#define GREEN stripDesk.Color(0, 255, 0)
#define RED stripDesk.Color(255, 0, 0)
#define BLUE stripDesk.Color(0, 0, 255)
#define YELLOW stripDesk.Color(255, 255, 0)
#define OFF stripDesk.Color(0, 0, 0)

#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50

int AState;
int BState;
int toggleState;
int currentMode;
int lastMode;
WipeModeStrategy WIPEWHITE = WipeModeStrategy(WHITE, NUM_LIGHTS_DESK);
WipeModeStrategy WIPERED = WipeModeStrategy(RED, NUM_LIGHTS_DESK);
WipeModeStrategy WIPEGREEN = WipeModeStrategy(GREEN, NUM_LIGHTS_DESK);
WipeModeStrategy WIPEBLUE = WipeModeStrategy(BLUE, NUM_LIGHTS_DESK);
int NUM_LIGHT_MODES = 5;
LightModeStrategy* deskModes[4] = {
  &WIPEBLUE, &WIPEWHITE, &WIPERED,
  &WIPEGREEN};
LightingModule computerDesk = LightingModule(NUM_LIGHTS_DESK)
void setup()
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Sets RIO related pins to INPUT
  pinMode(RIO_PINA, INPUT);
  pinMode(RIO_PINB, INPUT);
  pinMode(TOGGLE_PIN, INPUT);
  pinMode(DESK_PIN, OUTPUT);
  stripDesk.setBrightness(BRIGHTNESS_DESK);

  lastMode = -1;
  currentMode = MODE_RED;
}

void loop()
{
  updateInputs();
  updateMode();
  update();
  stripDesk.show();
}
void updateInputs()
{
  AState = digitalRead(RIO_PINA);
  BState = digitalRead(RIO_PINB);
}

void updateMode()
{

  if (AState == 1 && BState == 1)
  {
    currentMode = MODE_BLUE;
  }
  else if (AState == 1 && BState == 0)
  {
    currentMode = MODE_WHITE;
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
    currentMode = MODE_RED;
  }
  if (currentMode != lastMode)
  {
    deskModes[lastMode]->disable();
  }
}
void update()
{
  deskModes[currentMode]->update(stripDesk);
  tvModes[tvMode]->update(stripTV);
  lastMode = currentMode;
}