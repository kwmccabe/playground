#ifndef TEMPSENSORMODULE_H
#define TEMPSENSORMODULE_H

#include "Module.h"

// sensor ranges - fahrenheit
static float minTempF[] = {  32.0,  0.0,  60.0 };
static float maxTempF[] = { 212.0, 60.0, 120.0 };

/**
 * detect temp
 * display current value on neopixels
 * display current value
 * graph recent values
 */
class TempSensor: public Module
{
public:
  TempSensor() {}   // use moduleSetup() for activate
  ~TempSensor() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("TempSensor::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextWrap(false);
    analogWrite(TFT_BACKLIGHT, 222);

    // seed readings
    sensor_value = CircuitPlayground.temperatureF();
    for (int i = 0; i < ELEMENTS(reading); i++) {
      add_reading(sensor_value);
    }
    
    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("TempSensor::moduleTeardown()");
    CircuitPlayground.clearPixels();

    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false);
  }

  virtual void moduleReset()
  {
    sensor_mode  = 0;
    sensor_range = 0;
    min_sensor_value = maxTempF[sensor_range];
    max_sensor_value = minTempF[sensor_range];

    Serial.println("TempSensor::moduleReset()");
    update_background();
  }

  virtual void leftButton()
  {
    sensor_mode = (sensor_mode+1) % (ELEMENTS(maxTempF)*2);
    sensor_range = sensor_mode % ELEMENTS(maxTempF);
    min_sensor_value = maxTempF[sensor_range];
    max_sensor_value = minTempF[sensor_range];

    Serial.print("TempSensor::leftButton() - sensor_mode - "); Serial.println(sensor_mode);
    update_background();
  }

  virtual void rightButton()
  {
    Serial.println("TempSensor::rightButton()");
    update_background();
  }

  virtual unsigned long getModuleDelay() {
    return 1000;
  }

  virtual void loop()
  {
    //Serial.print("TempSensor::loop - "); Serial.println(millis());

    sensor_value = CircuitPlayground.temperatureF();
    add_reading(sensor_value);   // reading[reading_idx]
    sensor_level = (int)lerp(sensor_value, minTempF[sensor_range], maxTempF[sensor_range], 0.0, 10.0);
Serial.print("TempSensor::sensor_level,sensor_value - "); Serial.print(sensor_level); Serial.print(","); Serial.println(sensor_value);

    update_neopixels();
    update_foreground();
    update_meter();
  }

private:
  int sensor_mode;
  int sensor_range;
  int sensor_level;
  float sensor_value;
  int min_sensor_value;
  int max_sensor_value;

  /*
   * sensor smoothing
   */
  int reading_idx;
  int reading_size = 16;
  float reading[16];
  float reading_total;

  void add_reading( float sensor_value ) {
    reading_idx = (reading_idx+1) % reading_size;
    reading_total -= reading[reading_idx];
    reading[reading_idx] = sensor_value;
    reading_total += reading[reading_idx];

    if (sensor_value < min_sensor_value) { min_sensor_value = ceil(sensor_value); }
    if (sensor_value > max_sensor_value) { max_sensor_value = floor(sensor_value); }
  }
  float avg_reading() {
    return round((reading_total/reading_size) * 10) / 10.0;
  }

  /*
   * map sensor value to neopixel 0-10
   */
  void update_neopixels()
  {
//Serial.println("TempSensor::update_neopixels()");
    if (sensor_mode != sensor_range) {
      CircuitPlayground.clearPixels();
      return;
    }

    // lights off
    for (int i = 0; i < 10; ++i) {
      CircuitPlayground.strip.setPixelColor(i, 0);
    }
    // update
    for (int i = 0; i < sensor_level; ++i) {
      CircuitPlayground.strip.setPixelColor(i, 0xFF, 0x00, 0x00);
    }
    // lights on
    CircuitPlayground.strip.show();
  }

  /*
   * show mode info
   */
  void update_background()
  {
//Serial.println("TempSensor::update_background()");
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);

    // bottom-left corner - title
    String display_value = "Fahrenheit";

    int textSize = 2;
    tft.setTextSize(textSize);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = 6;
    int cy = tft.height() - textHeight - 4;

    tft.setCursor(cx, cy);
    tft.print(display_value);

    // bottom-right corner - range
    display_value = String(int(minTempF[sensor_range])) + "-" + String(int(maxTempF[sensor_range]));

    textSize = 2;
    tft.setTextSize(textSize);
    textWidth  = getTextWidth( display_value );
    textHeight = getTextHeight( display_value );
    cx = tft.width() - textWidth;
    cy = tft.height() - textHeight - 4;

    tft.setCursor(cx, cy);
    tft.print(display_value);

    // upper-left min/max reading
    display_value = "max:";

    textSize = 2;
    tft.setTextSize(textSize);
    textHeight = getTextHeight( "X" );
    cx = 6;
    cy = cx;
    //tft.fillRect(0, cy, tft.width()/2, 2*textHeight, ST77XX_WHITE);

    tft.setCursor(cx, cy);
    tft.print(display_value);

    display_value = "min:";
    cy += textHeight;

    tft.setCursor(cx, cy);
    tft.print(display_value);
}

  /*
   * show sensor value
   */
  void update_foreground()
  {
//Serial.println("TempSensor::update_foreground()");
    tft.setTextColor(ST77XX_BLACK);

    // upper-right corner - average
    String display_value = String(avg_reading());

    int textSize = 4;
    tft.setTextSize(textSize);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = tft.width()-textWidth;
    int cy = 6;

    tft.fillRect(tft.width()/2, cy, tft.width()/2, textHeight, ST77XX_WHITE);
    tft.setCursor(cx, cy);
    tft.print(display_value);

    // upper-left min/max reading
    display_value = String(max_sensor_value);

    textSize = 2;
    tft.setTextSize(textSize);
    textWidth  = getTextWidth( "XXXX" );
    textHeight = getTextHeight( "X" );
    cx = 6 + textWidth;
    cy = 6;
    tft.fillRect(cx, cy, cx, 2*textHeight, ST77XX_WHITE);

    tft.setCursor(cx, cy);
    tft.print(display_value);

    display_value = String(min_sensor_value);
    cy += textHeight;

    tft.setCursor(cx, cy);
    tft.print(display_value);
  }

  /*
   * graph sensor values
   */
  void update_meter()
  {
//Serial.println("TempSensor::update_meter()");
    int meter_x = 6;
    int meter_y = 40;
    int meter_w = tft.width() - (2*meter_x);
    int meter_h = tft.height() - meter_y - 24;

    int bar_pad = 2;
    int bar_wid = floor((meter_w - bar_pad*(reading_size+1))/reading_size);

    int cx = meter_x + 1;
    int cy = meter_y + 1;
    int cw = meter_w - 2;
    int ch = meter_h - 2;

    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    cx += bar_pad;
    for (int i = 0; i < reading_size; ++i) {
      int idx = (reading_idx + 1 + i) % reading_size;
      int lvl = (int)lerp(reading[idx], minTempF[sensor_range], maxTempF[sensor_range], 0, ch);

      tft.fillRect(cx, cy+ch-lvl, bar_wid, lvl,    ST77XX_RED);
      tft.fillRect(cx, cy,        bar_wid, ch-lvl, ST77XX_WHITE);
      cx += bar_wid;
      tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
      cx += bar_pad;
    }
    if (cx < meter_x + meter_w - 1) {
      tft.fillRect(cx, cy, meter_x + meter_w - 1 - cx, ch, ST77XX_GREEN);
    }

    int avg_lvl = (int)lerp(avg_reading(), minTempF[sensor_range], maxTempF[sensor_range], 0, ch);
    tft.drawLine(meter_x+1, meter_y+meter_h-avg_lvl-1, meter_x+meter_w-1, meter_y+meter_h-avg_lvl-1, ST77XX_BLUE);

    tft.drawRect(meter_x, meter_y, meter_w, meter_h, ST77XX_BLACK);
  }

};

#endif
