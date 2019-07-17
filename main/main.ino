#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "LightModes/colorWipe.cpp"
#include "Modules/LightingModule.cpp"
#include "LightModes/RainbowGlow.cpp"
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
#define MODE_RAINBOW 4
#define MODE_OFF 5

#define WHITE Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 255, 255)
#define GREEN  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 255, 0)
#define RED  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 0, 0)
#define BLUE  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 255)
#define OFF  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 0)

#define NUM_MODES_DESK 6
#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50


#define INPUTDELAY 300

int mode;
LightingModule* computerDesk;
void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning Setup");
  mode = 0;
  computerDesk = &LightingModule(NUM_MODES_DESK, NUM_LIGHTS_DESK, DESK_PIN, getDeskModes());
  computerDesk->setBrightness(0);
  computerDesk->enable();
  
  Serial.println("Setup Complete");
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
  computerDesk->update();
}

LightModeStrategy** getDeskModes(){
  LightModeStrategy** modes = malloc(sizeof(LightModeStrategy*)*NUM_MODES_DESK);
  for(int i = 0; i < NUM_MODES_DESK; i ++){
      modes[i] = malloc(sizeof(LightModeStrategy));
  }
  modes[0] = &WipeModeStrategy(WHITE, NUM_LIGHTS_DESK);
  modes[1] = &WipeModeStrategy(RED, NUM_LIGHTS_DESK);
  modes[2] = &WipeModeStrategy(GREEN, NUM_LIGHTS_DESK);
  modes[3] = &WipeModeStrategy(BLUE, NUM_LIGHTS_DESK);
  modes[4] = &RainbowGlowStrategy(NUM_LIGHTS_DESK);
  modes[5] = &WipeModeStrategy(OFF, NUM_LIGHTS_DESK);
  return modes;
}