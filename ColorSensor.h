#ifndef COLORSENSORMODULE_H
#define COLORSENSORMODULE_H

#include "Module.h"

/**
 * Detect reflective color values
 * Show sensor value(s)
 */
class ColorSensor: public Module
{
public:
  ColorSensor() {}   // use moduleSetup() for activate
  ~ColorSensor() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("ColorSensor::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextWrap(false);
    analogWrite(TFT_BACKLIGHT, 222);

    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("ColorSensor::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false);

    CircuitPlayground.clearPixels();
  }

  virtual void moduleReset()
  {
    sensor_mode = 0;
    Serial.println("ColorSensor::moduleReset()");
    update_background();
  }

  virtual void leftButton()
  {
    sensor_mode = (sensor_mode+1) % 2;
    Serial.print("ColorSensor::leftButton() - sensor_mode - "); Serial.println(sensor_mode);
    update_background();
  }

  virtual void rightButton() 
  {
    Serial.println("ColorSensor::rightButton()");
    update_background();
  }

  virtual unsigned long getModuleDelay() {
    return 1000;
  }

  virtual void loop()
  {
    //Serial.print("ColorSensor::loop() - "); Serial.println(millis());

    CircuitPlayground.senseColor(sensor_red, sensor_green, sensor_blue);
//Serial.print("ColorSensor::red,green,blue - "); Serial.print(sensor_red); Serial.print(","); Serial.print(sensor_green); Serial.print(","); Serial.println(sensor_blue);

    update_foreground();
    update_meter();
  }

private:
  int sensor_mode;
  uint8_t sensor_red;
  uint8_t sensor_green;
  uint8_t sensor_blue;

  /*
   * show mode info
   */
  void update_background()
  {
//Serial.println("ColorSensor::update_background()");
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);

    // bottom-center - title
    String display_value = "Color Levels";

    int textSize = 2;
    tft.setTextSize(textSize);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = tft.width()/2 - textWidth/2;
    int cy = tft.height() - textHeight - 4;

    tft.setCursor(cx, cy);
    tft.print(display_value);
}

  /*
   * show sensor value
   */
  void update_foreground()
  {
//Serial.println("ColorSensor::update_foreground()");

    // get color values
    char rgb_hex[7] = {0};
    sprintf(rgb_hex,"%02X%02X%02X",sensor_red,sensor_green,sensor_blue);
    uint16_t rgb_color_565 = RGB888toRGB565( rgb_hex );
//Serial.print("ColorSensor::rgb_hex,rgb_color_565 - "); Serial.print(rgb_hex); Serial.print(","); Serial.println(rgb_color_565);

    // rgb color
    int cx = 6;
    int cy = cx;
    tft.fillRect(cx, cy, tft.width()-2*cx, tft.height()/2-cx*2, rgb_color_565);

    // rgb value
    int textSize = 4;
    tft.setTextSize(textSize);
    tft.setTextColor(ST77XX_WHITE);

    String display_value = String(rgb_hex);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    cx = tft.width() - textWidth - 6;
    cy = 12;
    tft.setCursor(cx, cy);
    tft.print(display_value);
}

  /*
   * graph values
   */
  void update_meter()
  {
//Serial.println("ColorSensor::update_meter()");

    int meter_x = 6;
    int meter_y = tft.height()/2;
    int meter_w = tft.width() - (2*meter_x);
    int meter_h = tft.height() - meter_y - 24;

    int bar_pad = 6;
    int bar_wid = floor((meter_w - bar_pad*4)/3);

    int textSize = 2;
    tft.setTextSize(textSize);
    tft.setTextColor(ST77XX_BLACK);
    
    String val = "000";
    int val_w = getTextWidth( val );
    int val_h = getTextHeight( val );
    int val_y = meter_y + meter_h - floor(val_h*3/2);
    int val_x = 0;

    int cx = meter_x + 1;
    int cy = meter_y + 1;
    int cw = meter_w - 2;
    int ch = meter_h - 2;

    // margin
    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    cx += bar_pad;

    // red bar
    int lvl = (int)lerp(sensor_red, 0, 255, 0, ch);
    tft.fillRect(cx, cy+ch-lvl, bar_wid, lvl,    ST77XX_RED);
    tft.fillRect(cx, cy,        bar_wid, ch-lvl, ST77XX_WHITE);
    // red val
    val = String(sensor_red);
    val_w = getTextWidth( val );
    val_x = cx + bar_wid/2 - val_w/2;
    tft.setCursor(val_x, val_y);
    tft.print(val);

    // margin
    cx += bar_wid;
    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    cx += bar_pad;

    // green
    lvl = (int)lerp(sensor_green, 0, 255, 0, ch);
    tft.fillRect(cx, cy+ch-lvl, bar_wid, lvl,    ST77XX_GREEN);
    tft.fillRect(cx, cy,        bar_wid, ch-lvl, ST77XX_WHITE);
    // green val
    val = String(sensor_green);
    val_w = getTextWidth( val );
    val_x = cx + bar_wid/2 - val_w/2;
    tft.setCursor(val_x, val_y);
    tft.print(val);

    // margin
    cx += bar_wid;
    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    cx += bar_pad;

    // blue
    lvl = (int)lerp(sensor_blue, 0, 255, 0, ch);
    tft.fillRect(cx, cy+ch-lvl, bar_wid, lvl,    ST77XX_BLUE);
    tft.fillRect(cx, cy,        bar_wid, ch-lvl, ST77XX_WHITE);
    // blue val
    val = String(sensor_blue);
    val_w = getTextWidth( val );
    val_x = cx + bar_wid/2 - val_w/2;
    tft.setCursor(val_x, val_y);
    tft.print(val);

    // margin + slop
    cx += bar_wid;
    if (cx < meter_x + meter_w - 1) {
      tft.fillRect(cx, cy, meter_x + meter_w - 1 - cx, ch, ST77XX_WHITE);
    }

    // outline
    tft.drawRect(meter_x, meter_y, meter_w, meter_h, ST77XX_BLACK);
  }

};

#endif
