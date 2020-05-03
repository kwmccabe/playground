/**
 * Circuit Playground BLE + Gizmo TFT
 *
 * components:
 * - Finder      - required first module
 * - About       - reference module
 * - Blink       - reference module
 * - Dice        - D2, D3, D4, D6, D8, D10, D12, D20, D100
 * - Life        - Conway's Game of Life
 * - MusicBox    - pure-tone tunes
 * - ColorSensor -
 * - LightSensor -
 * - SoundSensor -
 * - TempSensor  -
 *
 * loop:
 * Check slideswitch left/-
 * - module->moduleTeardown()
 * - sleep until slideswitch right/+
 * - module->moduleSetup()
 * Check module_delay
 * - module->loop()
 * - module->getModuleDelay()
 * Check finder.MODULE
 * Check left/right buttons
 * - Left+Right : return to finder
 * - Left       : module->leftButton()
 * - Right      : module->rightButton()
 * Check shake
 * - module->moduleReset()
 *
 */
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_GFX.h>        // Core graphics library, includes 5x7 classic font
#include <Adafruit_ST7789.h>     // Hardware-specific library for ST7789
#include <Adafruit_SleepyDog.h>  // Watchdog timer
#include <Wire.h>
#include <SPI.h>
//#include <math.h>

#include <Fonts/Org_01.h>         // Wx6
//#include <Fonts/Tiny3x3a2pt7b.h>  // 3x3
//#include <Fonts/TomThumb>         // 3x5

/* GIZMO
@brief  Instantiate Adafruit ST7789 driver with selectable hardware SPI
@param  spiClass  Pointer to an SPI device to use - &SPI, or &SPI1 if (SPI_INTERFACES_COUNT > 1)
@param  cs        Chip select pin #
@param  dc        Data/Command pin #
@param  rst       Reset pin # (optional, pass -1 if unused)
*/
#define TFT_CS        0
#define TFT_DC        1
#define TFT_RST       -1
#define TFT_BACKLIGHT PIN_A3
SPIClass* spi = &SPI;
Adafruit_ST7789 tft = Adafruit_ST7789(spi, TFT_CS, TFT_DC, TFT_RST);

/* MODULES */
#include "Module.h"
#include "Finder.h"
#include "About.h"
#include "Blink.h"
#include "Dice.h"
#include "Life.h"
#include "MusicBox.h"
#include "ColorSensor.h"
#include "LightSensor.h"
#include "SoundSensor.h"
#include "TempSensor.h"

Finder finder;
About about;
Blink blink;
Dice dice;
Life life;
MusicBox musicBox;
ColorSensor colorSensor;
LightSensor lightSensor;
SoundSensor soundSensor;
TempSensor tempSensor;

Module* MODULES[] = {
  &finder,
  &about,
  &blink,
  &dice,
  &life,
  &musicBox,
  &colorSensor,
  &lightSensor,
  &soundSensor,
  &tempSensor,
};
int module = 0;

String MENUS[][4] = {
  {   "m0", "m0", "PLAYGROUND", "[LFT] Open selection \n[RGT] Select next \n[SHAKE] Clear selection" },
  {   "m0", "m1", "GAMES",      "[LFT] Open Submenu" },
  {   "m0", "5",  "MUSIC BOX",    "[LFT] Open Submenu" },
  {   "m0", "m2", "SENSORS",    "[LFT] Open Submenu" },
  {   "m0", "1",  "About",        "[LFT] Open About\n[RGT] Next" },
  {   "m1", "m0", "GAMES",      "[LFT] Open selection \n[RGT] Select next \n[SHAKE] Clear selection" },
  {   "m1", "2",  "Blink",        "[LFT] Open Blink\n[RGT] Add one (1) to blink #\n[SHAKE] Reset" },
  {   "m1", "3",  "Dice",         "[LFT] Open Dice\n[RGT] D2, 3, 4, 6, 8, 10, 12, 20, 100\n[SHAKE] Roll" },
  {   "m1", "4",  "Game of Life", "[LFT] Open Life\n[RGT] Regenerate colors\n[SHAKE] Regenerate colony" },
//  {   "m1", "5",  "Music Box",    "[LFT] Open Music Box\n[RGT] Next tune\n[SHAKE] Reset" },
  {   "m2", "m0", "SENSORS",    "[LFT] Open selection \n[RGT] Select next \n[SHAKE] Clear selection" },
  {   "m2", "6",  "Color Sensor", "[LFT] Open Sensor" },
  {   "m2", "7",  "Light Sensor", "[LFT] Open Sensor\n[RGT] Set range" },
  {   "m2", "8",  "Sound Sensor", "[LFT] Open Sensor\n[RGT] Set range" },
  {   "m2", "9",  "Temp Sensor",  "[LFT] Open Sensor\n[RGT] Set range" },
  };


/* TIMERS */
unsigned long module_timer = 0;
unsigned long module_delay = 1000;
unsigned long button_timer = 0;
unsigned long button_delay = 500;


/*
 * Init serial port, circuit playground library, tft screen
 * Modules should call tft.enableDisplay(true); in moduleSetup() and tft.enableDisplay(false); in moduleTeardown()
 */
void setup()
{
  if (!Serial) { delay(3000); }  // wait for (optional) serial
  Serial.begin(9600);

  CircuitPlayground.begin();
  //CircuitPlayground.begin(BRIGHTNESS);
  CircuitPlayground.clearPixels();
  randomSeed(CircuitPlayground.lightSensor());  // random sensor value

  pinMode(TFT_BACKLIGHT, OUTPUT);
  analogWrite(TFT_BACKLIGHT, 0); // backlight off

  tft.init(240, 240);              // ST7789 : 240x240
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);    // blank bkgnd
  tft.enableTearing(true);         // partial redraws
  tft.enableDisplay(false);        // disable
  //tft.setFont(&Org_01);

  MODULES[module]->moduleSetup();

  Serial.println("Main::setup() complete");
}

/*
 * main loop()
 */
void loop()
{
  //Serial.print("Main::loop() - "); Serial.println(millis()); delay(500);

  // check switch
  bool sleepy = false;
  while (!CircuitPlayground.slideSwitch()) {
    if (!sleepy) {
      MODULES[module]->moduleTeardown();
      sleepy = true;
    }
    Watchdog.sleep(3000);
  }
  if (sleepy) {
    MODULES[module]->moduleSetup();
    sleepy = false;
  }

  // after module_delay msecs, call module->loop() and module->getModuleDelay()
  unsigned long curtime = millis();
  if (curtime - module_timer > module_delay) {
    module_timer = curtime;
    MODULES[module]->loop();
    module_delay = MODULES[module]->getModuleDelay();
  }

  // check finder for updated module selection
  if (module == 0) {
    if (0 < finder.MODULE && finder.MODULE < ELEMENTS(MODULES)) {
      MODULES[module]->moduleTeardown();
      module = finder.MODULE;
      MODULES[module]->moduleSetup();
    }
  }

  // check buttons
  curtime = millis();
  bool lftBtn = CircuitPlayground.leftButton();
  bool rgtBtn = CircuitPlayground.rightButton();
  delay(10);

  // lftBtn+rgtBtn : return to finder
  // lftBtn/rgtBtn call module->leftButton() or module->rightButton()
  if ((lftBtn || rgtBtn) && (curtime - button_timer > button_delay)) {
    button_timer = curtime;
    if (lftBtn && rgtBtn) {
      Serial.println("Main::leftButton && rightButton");
      MODULES[module]->moduleTeardown();
      module = 0;
      MODULES[module]->moduleSetup();

      Serial.print("Main::module - "); Serial.println(module, DEC);
    } else if (lftBtn) {
      //Serial.println("Main::leftButton");
      MODULES[module]->leftButton();
      module_delay = MODULES[module]->getModuleDelay();

    } else if (rgtBtn) {
      //Serial.println("Main::rightButton");
      MODULES[module]->rightButton();
      module_delay = MODULES[module]->getModuleDelay();

    }
  }

  // call shake
  bool shake = shakeDetect();
  if (shake) {
    Serial.println("Dice::loop - shake");
    MODULES[module]->moduleReset();
    module_delay = MODULES[module]->getModuleDelay();
  }

  // tap ?
}

/*
// @see https://stackoverflow.com/questions/14427917/call-function-in-main-program-from-a-library-in-arduino/14428921
void setBacklight(int level)
{
  level = level % 256;
  if (level > 0) {
    tft.enableDisplay(true);
    analogWrite(TFT_BACKLIGHT, level);
  } else {
    tft.enableDisplay(false);
  }
}
*/
