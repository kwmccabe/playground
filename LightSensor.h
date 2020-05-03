#ifndef LIGHTSENSORMODULE_H
#define LIGHTSENSORMODULE_H

#include "Module.h"

// sensor ranges
static int minLight[] = {    0,   0,   0,   0 };
static int maxLight[] = { 1023, 500, 250, 100 };

/**
 * detect overall light level
 * display current value
 * graph recent values
 */
class LightSensor: public Module
{
public:
  LightSensor() {}   // use moduleSetup() for activate
  ~LightSensor() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("LightSensor::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextWrap(false);
    analogWrite(TFT_BACKLIGHT, 222);

    // seed readings
    sensor_value = CircuitPlayground.lightSensor();
    for (int i = 0; i < ELEMENTS(reading); i++) {
      add_reading(sensor_value);
    }
    
    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("LightSensor::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false);

    CircuitPlayground.clearPixels();
  }

  virtual void moduleReset()
  {
    sensor_mode  = 0;
    sensor_range = 0;
    min_sensor_value = maxLight[sensor_range];
    max_sensor_value = minLight[sensor_range];
    Serial.println("LightSensor::moduleReset()");
    update_background();
  }

  virtual void leftButton()
  {
    sensor_mode = (sensor_mode+1) % (ELEMENTS(maxLight)*2);
    sensor_range = sensor_mode % ELEMENTS(maxLight);
    min_sensor_value = maxLight[sensor_range];
    max_sensor_value = minLight[sensor_range];
    Serial.print("LightSensor::leftButton() - sensor_mode - "); Serial.println(sensor_mode);
    update_background();
  }

  virtual void rightButton() 
  {
    Serial.println("LightSensor::rightButton()");
    update_background();
  }

  virtual unsigned long getModuleDelay() {
    return 250;
  }

  virtual void loop()
  {
    //Serial.print("LightSensor::loop - "); Serial.println(millis());

    sensor_value = CircuitPlayground.lightSensor();
    add_reading(sensor_value);   // reading[reading_idx]
    sensor_level = (int)lerp(sensor_value, minLight[sensor_range], maxLight[sensor_range], 0.0, 10.0);
Serial.print("LightSensor::sensor_level,sensor_value - "); Serial.print(sensor_level); Serial.print(","); Serial.println(sensor_value);

    update_neopixels();
    update_foreground();
    update_meter();
  }

private:
  int sensor_mode;
  int sensor_range;
  int sensor_level;
  uint16_t sensor_value;
  uint16_t min_sensor_value;
  uint16_t max_sensor_value;

  /*
   * sensor smoothing  (16*250ms = 4 seconds)
   */
  int reading_idx;
  int reading_size = 16;
  uint16_t reading[16];
  uint16_t reading_total;

  void add_reading( uint16_t sensor_value ) {
    reading_idx = (reading_idx+1) % reading_size;
    reading_total -= reading[reading_idx];
    reading[reading_idx] = sensor_value;
    reading_total += reading[reading_idx];

    if (sensor_value < min_sensor_value) { min_sensor_value = sensor_value; }
    if (sensor_value > max_sensor_value) { max_sensor_value = sensor_value; }
  }
  uint16_t avg_reading() {
    return round(reading_total/reading_size);
  }

  /*
   * map sensor value to neopixel 0-10
   */
  void update_neopixels()
  {
//Serial.println("LightSensor::update_neopixels()");
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
      CircuitPlayground.strip.setPixelColor(i, 0x00, 0x00, 0xFF);
    }
    // lights on
    CircuitPlayground.strip.show();
  }

  /*
   * show mode info
   */
  void update_background()
  {
//Serial.println("LightSensor::update_background()");
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);

    // bottom-left corner - title
    String display_value = "Light Level";

    int textSize = 2;
    tft.setTextSize(textSize);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = 6;
    int cy = tft.height() - textHeight - 4;

    tft.setCursor(cx, cy);
    tft.print(display_value);

    // bottom-right corner - range
    display_value = String(minLight[sensor_range]) + "-" + String(maxLight[sensor_range]);

    //textSize = 2;
    //tft.setTextSize(textSize);
    textWidth  = getTextWidth( display_value );
    //textHeight = getTextHeight( display_value );
    cx = tft.width() - textWidth;
    cy = tft.height() - textHeight - 4;

    tft.setCursor(cx, cy);
    tft.print(display_value);

    // upper-left min/max reading
    display_value = "max:";

    //textSize = 2;
    //tft.setTextSize(textSize);
    //textHeight = getTextHeight( "X" );
    cx = 6;
    cy = cx;
    tft.fillRect(0, cy, tft.width()/2, 2*textHeight, ST77XX_WHITE);

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
//Serial.println("LightSensor::update_foreground()");
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
    textHeight = getTextHeight( "XXXX" );
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
//Serial.println("LightSensor::update_foreground()");
    //tft.fillScreen(ST77XX_WHITE);

    int meter_x = 6;
    int meter_y = 40;
    int meter_w = tft.width() - (2*meter_x);
    int meter_h = tft.height() - meter_y - 24;

    int bar_pad = 2;
    int bar_wid = floor((meter_w - bar_pad*(reading_size+1))/reading_size);

    //tft.fillRect(0, cy-hgt, tft.width(), hgt, ST77XX_WHITE);
    int cx = meter_x + 1;
    int cy = meter_y + 1;
    int cw = meter_w - 2;
    int ch = meter_h - 2;

    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    cx += bar_pad;
    for (int i = 0; i < reading_size; ++i) {
      int idx = (reading_idx + 1 + i) % reading_size;
      int lvl = (int)lerp(reading[idx], minLight[sensor_range], maxLight[sensor_range], 0, ch);

      tft.fillRect(cx, cy+ch-lvl, bar_wid, lvl,    ST77XX_RED);
      tft.fillRect(cx, cy,        bar_wid, ch-lvl, ST77XX_WHITE);
      cx += bar_wid;
      tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
      cx += bar_pad;
    }
    if (cx < meter_x + meter_w - 1) {
      tft.fillRect(cx, cy, meter_x + meter_w - 1 - cx, ch, ST77XX_GREEN);
    }

    int avg_lvl = (int)lerp(avg_reading(), minLight[sensor_range], maxLight[sensor_range], 0, ch);
    tft.drawLine(meter_x+1, meter_y+meter_h-avg_lvl-1, meter_x+meter_w-1, meter_y+meter_h-avg_lvl-1, ST77XX_BLUE);

    tft.drawRect(meter_x, meter_y, meter_w, meter_h, ST77XX_BLACK);
  }

};

#endif
