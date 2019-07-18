[1mdiff --git a/main/LightModes/rainbowGlow.cpp b/main/LightModes/rainbowGlow.cpp[m
[1mindex 2ecd611..0d46169 100644[m
[1m--- a/main/LightModes/rainbowGlow.cpp[m
[1m+++ b/main/LightModes/rainbowGlow.cpp[m
[36m@@ -1,5 +1,4 @@[m
 //#include <Adafruit_NeoPixel.h>[m
[31m-#include "strategy.h"[m
 #define updateDelay 100[m
 class RainbowGlowStrategy : public LightModeStrategy[m
 {[m
[36m@@ -33,31 +32,31 @@[m [mprotected:[m
     bool shouldUpdate()[m
     {    [m
         if (lastUpdate + updateDelay <= millis() ){[m
[31m-            return false[m
[32m+[m[32m            return false;[m
         }[m
         return true;[m
     }[m
[31m-    void _update(Adafruit_NeoPixel strip)[m
[32m+[m[32m    void _update(Adafruit_NeoPixel * strip)[m
     {[m
         firstPixelHue += 256;[m
         if (firstPixelHue > 5 * 65536)[m
         {[m
             firstPixelHue = 0;[m
         }[m
[31m-        for (int i = 0; i < strip.numPixels(); i++)[m
[32m+[m[32m        for (int i = 0; i < strip->numPixels(); i++)[m
         { // For each pixel in strip...[m
             // Offset pixel hue by an amount to make one full revolution of the[m
             // color wheel (range of 65536) along the length of the strip[m
             // (strip.numPixels() steps):[m
[31m-            int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());[m
[32m+[m[32m            int pixelHue = firstPixelHue + (i * 65536L / strip->numPixels());[m
             // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or[m
             // optionally add saturation and value (brightness) (each 0 to 255).[m
             // Here we're using just the single-argument hue variant. The result[m
             // is passed through strip.gamma32() to provide 'truer' colors[m
             // before assigning to each pixel:[m
[31m-            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));[m
[32m+[m[32m            strip->setPixelColor(i, strip->gamma32(strip->ColorHSV(pixelHue)));[m
         }[m
         lastUpdate = millis();[m
[31m-        strip.show(); // Update strip with new contents[m
[32m+[m[32m        strip->show(); // Update strip with new contents[m
     }[m
 };[m
\ No newline at end of file[m
[1mdiff --git a/main/Modules/LightingModule.cpp b/main/Modules/LightingModule.cpp[m
[1mindex 192fa46..52ef866 100644[m
[1m--- a/main/Modules/LightingModule.cpp[m
[1m+++ b/main/Modules/LightingModule.cpp[m
[36m@@ -2,29 +2,33 @@[m
 #include "Module.cpp"[m
 class LightingModule : public Module[m
 {[m
[31m-    Adafruit_NeoPixel* strip;[m
[32m+[m[32m    Adafruit_NeoPixel *strip;[m
     int currentMode;[m
[31m-    int lastMode;[m
[32m+[m[32m    int numModes;[m
     int numLights;[m
[31m-    int brightness = 50;[m
[32m+[m[32m    int brightness;[m
     int modulePin;[m
[31m-    public:[m
[31m-[m
[31m-    LightModeStrategy** modes;[m
[31m-    LightingModule(int num, int pin , LightModeStrategy ** lightModes) : Module()[m
[32m+[m[32m    int lastMode;[m
[32m+[m[32mpublic:[m
[32m+[m[32m    LightModeStrategy **modes;[m
[32m+[m[32m    LightingModule(int totalModes, int totalLights, int pin, LightModeStrategy **lightModes) : Module()[m
     {[m
[31m-        pinMode(pin, OUTPUT);[m
[32m+[m[32m        pinMode(pin, OUTPUT);[m[41m   [m
         strip = malloc(sizeof(Adafruit_NeoPixel));[m
[31m-        *strip =  & Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);[m
[32m+[m[32m        *strip = &Adafruit_NeoPixel(totalLights, pin, NEO_GRB + NEO_KHZ800);[m
         modes = lightModes;[m
[32m+[m[32m        brightness = 50;[m
         modulePin = pin;[m
         enabled = true;[m
         currentMode = 0;[m
         lastMode = 0;[m
     }[m
[32m+[m[32m    int totalStates(){[m
[32m+[m[32m        return numModes;[m
[32m+[m[32m    }[m
     void setBrightness(int newBrightness)[m
     {[m
[31m-        brightness =  newBrightness;[m
[32m+[m[32m        brightness = newBrightness;[m
         strip->setBrightness(brightness);[m
     }[m
     int getState()[m
[36m@@ -33,10 +37,13 @@[m [mclass LightingModule : public Module[m
     }[m
     void setState(int mode)[m
     {[m
[31m-        lastMode = currentMode;[m
[31m-        currentMode = mode;[m
[31m-        modes[lastMode]->disable();[m
[31m-        modes[currentMode]->enable();[m
[32m+[m[32m        if (mode < numModes)[m
[32m+[m[32m        {[m
[32m+[m[32m            lastMode = currentMode;[m
[32m+[m[32m            currentMode = mode;[m
[32m+[m[32m            modes[lastMode]->disable();[m
[32m+[m[32m            modes[currentMode]->enable();[m
[32m+[m[32m        }[m
     }[m
     void update()[m
     {[m
[1mdiff --git a/main/Modules/Module.cpp b/main/Modules/Module.cpp[m
[1mindex 67aa78f..b5442b6 100644[m
[1m--- a/main/Modules/Module.cpp[m
[1m+++ b/main/Modules/Module.cpp[m
[36m@@ -5,6 +5,7 @@[m [mpublic:[m
     bool enabled;[m
     virtual int getState() = 0;[m
     virtual void setState(int state);[m
[32m+[m[32m    virtual int totalStates();[m
     virtual void update() = 0;[m
     virtual void setup() = 0;[m
     virtual void disable() = 0;[m
[1mdiff --git a/main/main.ino b/main/main.ino[m
[1mindex 7939018..754c17a 100644[m
[1m--- a/main/main.ino[m
[1m+++ b/main/main.ino[m
[36m@@ -2,6 +2,10 @@[m
 #include <Adafruit_NeoPixel.h>[m
 #include "LightModes/colorWipe.cpp"[m
 #include "Modules/LightingModule.cpp"[m
[32m+[m[32m#include "LightModes/RainbowGlow.cpp"[m
[32m+[m[32m#include "Controllers/controller.cpp"[m
[32m+[m[32m#include "Controllers/buttonController.cpp"[m
[32m+[m
 #ifdef __AVR__[m
 #include <avr/power.h>[m
 #endif[m
[36m@@ -20,6 +24,7 @@[m
 #define MODE_GREEN 2[m
 #define MODE_BLUE 3[m
 <<<<<<< HEAD[m
[32m+[m[32m<<<<<<< HEAD[m
 #define MODE_WHITE 3[m
 #define SHOWBOAT 4[m
 [m
[36m@@ -38,40 +43,59 @@[m [mAdafruit_NeoPixel stripDesk = Adafruit_NeoPixel(NUM_LIGHTS_DESK, DESK_PIN, NEO_G[m
 =======[m
 #define MODE_OFF 4[m
 #define light[m
[32m+[m[32m=======[m
[32m+[m[32m#define MODE_RAINBOW 4[m
[32m+[m[32m#define MODE_OFF 5[m
[32m+[m
[32m+[m[32m>>>>>>> controller[m
 #define WHITE Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 255, 255)[m
 #define GREEN  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 255, 0)[m
 #define RED  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(255, 0, 0)[m
 #define BLUE  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 255)[m
 #define OFF  Adafruit_NeoPixel(0,0,NEO_GRB + NEO_KHZ800).Color(0, 0, 0)[m
 [m
[31m-#define NUM_MODES_DESK 5[m
[32m+[m[32m#define NUM_MODES_DESK 6[m
 #define NUM_LIGHTS_DESK 200[m
 #define BRIGHTNESS_DESK 50[m
 >>>>>>> modules[m
 [m
[32m+[m
[32m+[m
 LightingModule* computerDesk;[m
 void setup()[m
 {[m
   pinMode(LED, OUTPUT);   [m
   [m
   Serial.begin(9600);[m
[31m-  computerDesk = &LightingModule(NUM_LIGHTS_DESK, DESK_PIN, getDeskModes());[m
[32m+[m[32m  Serial.println("Beginning Setup");[m
[32m+[m[32m  computerDesk = &LightingModule(NUM_MODES_DESK, NUM_LIGHTS_DESK, DESK_PIN, getDeskModes());[m
[32m+[m[41m  [m
   computerDesk->setBrightness(0);[m
   computerDesk->enable();[m
[32m+[m[32m  computerDesk->setState(0);[m
[32m+[m[32m  computerDesk->update();[m
[32m+[m[32m  Serial.println("Setup Complete");[m
 }[m
 [m
 [m
 void loop()[m
[32m+[m[32m<<<<<<< HEAD[m
 {[m
   digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)[m
   delay(1000);      [m
[32m+[m[32m=======[m
[32m+[m[32m{[m[41m  [m
[32m+[m[32m  Serial.println("Loop");[m
[32m+[m[32m>>>>>>> controller[m
   updateInputs();[m
   updateMode();[m
   update();[m
[32m+[m[32m  delay(50);[m
 }[m
 [m
 void updateInputs()[m
 {[m
[32m+[m[41m  [m
 }[m
 [m
 void updateMode()[m
[36m@@ -125,7 +149,8 @@[m [mLightModeStrategy** getDeskModes(){[m
   modes[1] = &WipeModeStrategy(RED, NUM_LIGHTS_DESK);[m
   modes[2] = &WipeModeStrategy(GREEN, NUM_LIGHTS_DESK);[m
   modes[3] = &WipeModeStrategy(BLUE, NUM_LIGHTS_DESK);[m
[31m-  modes[4] = &WipeModeStrategy(OFF, NUM_LIGHTS_DESK);[m
[32m+[m[32m  modes[4] = &RainbowGlowStrategy(NUM_LIGHTS_DESK);[m
[32m+[m[32m  modes[5] = &WipeModeStrategy(OFF, NUM_LIGHTS_DESK);[m
   return modes;[m
 >>>>>>> modules[m
 }[m
\ No newline at end of file[m
