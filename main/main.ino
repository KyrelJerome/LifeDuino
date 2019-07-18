#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "LightModes/colorWipe.cpp"
#include "Modules/LightingModule.cpp"
#ifdef __AVR__
#include <avr/power.h>
#endif
<<<<<<< HEAD
//OUTPUT PINS
#define DESK_PIN 8
=======
>>>>>>> modules

//OUTPUT PINS
#define DESK_PIN 13

// DEFINE LIGHT LightModes
#define MODE_WHITE 0
#define MODE_RED 1
#define MODE_GREEN 2
#define MODE_BLUE 3
<<<<<<< HEAD
#define MODE_WHITE 3
#define SHOWBOAT 4

//COLOURS
#define WHITE stripDesk.Color(255, 255, 255)
#define GREEN stripDesk.Color(0, 255, 0)
#define RED stripDesk.Color(255, 0, 0)
#define BLUE stripDesk.Color(0, 0, 255)
#define YELLOW stripDesk.Color(255, 255, 0)
#define OFF stripDesk.Color(0, 0, 0)
#define LED 13

#define NUM_LIGHTS_DESK 40
#define BRIGHTNESS_DESK 100
Adafruit_NeoPixel stripDesk = Adafruit_NeoPixel(NUM_LIGHTS_DESK, DESK_PIN, NEO_GRB + NEO_KHZ800);
=======
#define MODE_OFF 4
#define light
#define WHITE Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 255, 255)
#define GREEN  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 255, 0)
#define RED  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 0, 0)
#define BLUE  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 255)
#define OFF  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 0)

#define NUM_MODES_DESK 5
#define NUM_LIGHTS_DESK 200
#define BRIGHTNESS_DESK 50
>>>>>>> modules

LightingModule* computerDesk;
void setup()
{
  pinMode(LED, OUTPUT);   
  
  Serial.begin(9600);
  computerDesk = &LightingModule(NUM_LIGHTS_DESK, DESK_PIN, getDeskModes());
  computerDesk->setBrightness(0);
  computerDesk->enable();
}


void loop()
{
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);      
  updateInputs();
  updateMode();
  update();
}

void updateInputs()
{
}

void updateMode()
{

<<<<<<< HEAD
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
    currentMode = MODE_RED;
  }
  else
  {
    currentMode = MODE_RED;
  }
  if (currentMode != lastMode)
  {
   // deskModes[lastMode]->disable();
  }
}
void update()
{
  deskModes[0]->update(stripDesk);
 // tvModes[tvMode]->update(stripTV);
  lastMode = currentMode;
=======
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
  modes[4] = &WipeModeStrategy(OFF, NUM_LIGHTS_DESK);
  return modes;
>>>>>>> modules
}