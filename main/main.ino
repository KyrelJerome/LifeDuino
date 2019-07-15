#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "LightModes/colorWipe.cpp"
#include "Modules/LightingModule.cpp"
#ifdef __AVR__
#include <avr/power.h>
#endif

//OUTPUT PINS
#define DESK_PIN 13

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

#define NUM_MODES_DESK 5
#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50


int toggleState;
int currentMode;
int lastMode;

int NUM_LIGHT_MODES = 5;
LightModeStrategy* deskModes[4] = {
  &WIPEBLUE, &WIPEWHITE, &WIPERED,
  &WIPEGREEN};
LightingModule computerDesk = void setup()
{
  Serial.begin(9600);
  pinMode(DESK_PIN, OUTPUT);
  stripDesk.setBrightness(BRIGHTNESS_DESK);
  lastMode = -1;
  currentMode = MODE_RED;
  computerDesk = LightingModule(NUM_LIGHTS_DESK, DESK_PIN, lightModes, getDeskModes());

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

LightModeStrategy* getModes(){
  LightModeStrategy* modes = malloc(sizeof(LightModeStrategy*)*NUM_MODES_DESK);
  for(int i = 0; i < NUM_MODES_DESK; i ++){
      modes[i] = malloc(sizeof(LightModeStrategy));
  }
  modes[0] = WipeModeStrategy(WHITE, NUM_LIGHTS_DESK);
  modes[1] = WipeModeStrategy(RED, NUM_LIGHTS_DESK);
  modes[2] = WipeModeStrategy(GREEN, NUM_LIGHTS_DESK);
  modes[3] = WipeModeStrategy(BLUE, NUM_LIGHTS_DESK);
  modes[4] = WipeModeStrategy(OFF, NUM_LIGHTS_DESK);
  return modes;
}
