#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "LightModes/colorWipe.cpp"
#include "Modules/LightingModule.cpp"
#ifdef __AVR__
#include <avr/power.h>
#endif

//OUTPUT PINS
#define DESK_PIN 13

// DEFINE LIGHT LightModes
#define MODE_WHITE 0
#define MODE_RED 1
#define MODE_GREEN 2
#define MODE_BLUE 3
#define MODE_OFF 4

#define WHITE Adafruit_NeoPixel.Color(255, 255, 255)
#define GREEN  Adafruit_NeoPixel.Color(0, 255, 0)
#define RED  Adafruit_NeoPixel.Color(255, 0, 0)
#define BLUE  Adafruit_NeoPixel.Color(0, 0, 255)
#define OFF  Adafruit_NeoPixel.Color(0, 0, 0)

#define NUM_MODES_DESK 5
#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50

LightingModule computerDesk;
{
  Serial.begin(9600);
  lastMode = -1;
  computerDesk = LightingModule(NUM_LIGHTS_DESK, DESK_PIN, lightModes, &getDeskModes());
  computerDesk.enable();
}


void loop()
{
  updateInputs();
  updateMode();
  update();
}

void updateInputs()
{
}

void updateMode()
{

}
void update()
{
  computerDesk.update();
}

LightModeStrategy* getDeskModes(){
  LightModeStrategy* modes = malloc(sizeof(LightModeStrategy*)*NUM_MODES_DESK);
  for(int i = 0; i < NUM_MODES_DESK; i ++){
      modes[i] = malloc(sizeof(LightModeStrategy));
  }
  modes[0] = & WipeModeStrategy(WHITE, NUM_LIGHTS_DESK);
  modes[1] = & WipeModeStrategy(RED, NUM_LIGHTS_DESK);
  modes[2] = & WipeModeStrategy(GREEN, NUM_LIGHTS_DESK);
  modes[3] = & WipeModeStrategy(BLUE, NUM_LIGHTS_DESK);
  modes[4] = & WipeModeStrategy(OFF, NUM_LIGHTS_DESK);
  return modes;
}