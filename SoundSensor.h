#ifndef SOUNDSENSORMODULE_H
#define SOUNDSENSORMODULE_H

#include "Module.h"

// sensor ranges
static int minSound[] = {    0,   0,   0,   0 };
static int maxSound[] = { 1023, 500, 250, 100 };

#define SAMPLE_WINDOW   10  // sample window for average level
#define PEAK_HANG       24  // loop count before peak dot falls
#define PEAK_FALL        4  // loop count falling peak dot
#define INPUT_FLOOR     56  // min mic sensitivity in dB SPL
#define INPUT_CEILING  110  // max mic sensitivity in db SPL

/**
 * detect overall sound level
 * display current value on neopixels
 * display hanging peak dot on neopixel
 */
class SoundSensor: public Module {
public:
  SoundSensor() {}   // use moduleSetup() for activate
  ~SoundSensor() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("SoundSensor::moduleSetup()");
    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("SoundSensor::moduleTeardown()");
    CircuitPlayground.clearPixels();
  }

  virtual void moduleReset()
  {
    Serial.println("SoundSensor::moduleReset()");
    sensor_mode = 0;
  }

  virtual void leftButton()
  {
    sensor_mode = (sensor_mode+1) % 3;
    Serial.print("SoundSensor::leftButton() - sensor_mode - "); Serial.println(sensor_mode);
  }

  virtual void rightButton()
  {
    Serial.println("SoundSensor::rightButton()");
  }

  virtual unsigned long getModuleDelay() {
    return 100;
  }

  virtual void loop()
  {
    //Serial.print("SoundSensor::loop() - "); Serial.println(millis());

    int numPixels = CircuitPlayground.strip.numPixels();
    float peakToPeak = 0;   // peak-to-peak level
    unsigned int c, y;

    // fill the strip with rainbow gradient
    for (int i = 0; i < numPixels; i++) {
      CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(map(i,0,numPixels-1,30,150)));
    }

    // get peak sound pressure level over the sample window
    peakToPeak = CircuitPlayground.mic.soundPressureLevel(SAMPLE_WINDOW);
    // limit to the floor value
    peakToPeak = max(INPUT_FLOOR, peakToPeak);
    // map ascending value to descending number of neopixels
    c = lerp(peakToPeak, INPUT_FLOOR, INPUT_CEILING, numPixels, 0);
    // turn off pixels down to volume threshold
    if (c < peak) {
      peak = c;          // update peak dot
      dotHangCount = 0;  // reset counter
    }
    if (c <= numPixels) { // Fill partial column with off pixels
      setPixelColors(numPixels, numPixels-c, CircuitPlayground.strip.Color(0, 0, 0));
    }
Serial.print("SoundSensor::peakToPeak,c - "); Serial.print(peakToPeak); Serial.print(","); Serial.println(c);

    // update peak dot with gradient color
    y = numPixels - peak;
    CircuitPlayground.strip.setPixelColor(y-1,CircuitPlayground.colorWheel(map(y,0,numPixels-1,30,150)));
    CircuitPlayground.strip.show();

    // update counters
    if (dotHangCount > PEAK_HANG) {  // Peak pause length
      if (++dotCount >= PEAK_FALL) { // Fall rate
        peak++;
        dotCount = 0;
      }
    } else {
      dotHangCount++;
    }
  }

private:
  int sensor_mode;

  byte peak = 16;        // Peak level of column; used for falling dots
  byte dotCount = 0;     // Frame counter for peak dot
  byte dotHangCount = 0; // Frame counter for holding peak dot

};

#endif
