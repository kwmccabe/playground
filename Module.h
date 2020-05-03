#ifndef MODULE_H
#define MODULE_H

/*
 * Module base class
 * Define interface for functions called by main
 * module::moduleSetup(), module::moduleTeardown(), module::moduleReset()
 * module::leftButton(), module::rightButton()
 * module::loop() is called every subclass::getModuleDelay() milliseconds
 *
 * @see Blink.h for reference implementation
 */
class Module {
public:
  virtual ~Module() {}

  virtual void moduleSetup() = 0;
  virtual void moduleTeardown() = 0;
  virtual void moduleReset() = 0;
  virtual void leftButton() = 0;
  virtual void rightButton() = 0;
  virtual unsigned long getModuleDelay() = 0;
  virtual void loop() = 0;
};

/*
 * UTILS
 */
#define ELEMENTS(x)   (sizeof(x) / sizeof(x[0]))

/* UTIL: adjust tft backlight */
void setBacklight(int level)
{
  level = level % 256;
  analogWrite(TFT_BACKLIGHT, level);
}

/* UTIL: Linear interpolation */
float lerp(float x, float in_min, float in_max, float out_min, float out_max)
{
  if (x >= in_max) {
    return out_max;
  }
  if (x <= in_min) {
    return out_min;
  }
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* UTIL: Convert 32bit color value to 16bit */
uint16_t RGB888toRGB565(const char *rgb32_str_)
{
  long rgb32 = strtoul(rgb32_str_, 0, 16);
  return (rgb32>>8&0xf800)|(rgb32>>5&0x07e0)|(rgb32>>3&0x001f);
}

/* UTIL: Convert 16bit color value to 32bit */
uint32_t RGB565toRGB888(const char *rgb16_str_)
{
  long rgb16 = strtoul(rgb16_str_, 0, 16);
//return (rgb16>>11&0xf800)|(rgb16>>5&0x07e0)|(rgb16>>0&0x001f);

  int r = (rgb16 & 0xF800) >11;
  int g = (rgb16 & 0x07E0) >5;
  int b = (rgb16 & 0x001F);
Serial.print("RGB565toRGB888() - r,g,b- "); Serial.print(r); Serial.print(","); Serial.print(g); Serial.print(","); Serial.println(b);

/*
  r = r * 255 / 31;
  g = g * 255 / 63;
  b = b * 255 / 31;

  r = (int) floor( r * 255.0 / 31.0 + 0.5);
  g = (int) floor( g * 255.0 / 63.0 + 0.5);
  b = (int) floor( b * 255.0 / 31.0 + 0.5);
*/
  r = ( r * 527 + 23 ) >> 6;
  g = ( g * 259 + 33 ) >> 6;
  b = ( b * 527 + 23 ) >> 6;

Serial.print("RGB565toRGB888() - r,g,b- "); Serial.print(r); Serial.print(","); Serial.print(g); Serial.print(","); Serial.println(b);
  return (r << 16) | (g << 8) | b;
}

/* UTIL: Set neopixels color, index from->to */
static void setPixelColors(uint8_t from, uint8_t to, uint32_t c) {
  uint8_t first = (from > to) ? to : from;
  uint8_t last  = (from > to) ? from : to;
  for (int i = first; i <= last; i++) {
    CircuitPlayground.strip.setPixelColor(i, c);
  }
}

/* UTIL: detect lots of movement */
#define SHAKE_THRESHOLD     16          // Total acceleration threshold for roll detect
//#define TAP_THRESHOLD       10          // Tap detect threshold

bool shakeDetect()
{
  float X, Y, Z, totalAccel;
  X = Y = Z = 0;
  for (int i = 0; i < 10; i++) {
    X += CircuitPlayground.motionX();
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;
  totalAccel = sqrt(X*X + Y*Y + Z*Z);

  return (totalAccel > SHAKE_THRESHOLD) ? true : false;
}

/* UTIL: tft text bounds */
int getTextWidth( String text )
{
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text.c_str(), 0, 0, &x1, &y1, &w, &h);
  return w;
}
int getTextHeight( String text )
{
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text.c_str(), 0, 0, &x1, &y1, &w, &h);
  return h;
}
int getMaxTextSize( String text, int maxWidth )
{
  int textSize = 1;
  while(true) {
    textSize++;
    tft.setTextSize(textSize);
    int width = getTextWidth( text );
    if (width > maxWidth)
      { break; }
  }
  return textSize-1;
}

/*
* print text max size/width for display
* xpos>0 align left ; xpos=0 center ; xpos<0 align right
* return ypos plus calculated height
* eg: ypos = printTitle( "my text", 0, ypos );
*/
int printTitle( String text, int xpos, int ypos )
{
int textSize   = getMaxTextSize(text, tft.width());
tft.setTextSize(textSize);

int textWidth  = getTextWidth( text );
int textHeight = getTextHeight( text );
int cx = xpos; // if (xpos > 0)
if (xpos < 0)  { cx = tft.width() - xpos; }
if (xpos == 0) { cx = (tft.width()/2)-(textWidth/2); }
int cy = ypos;

tft.setCursor(cx, cy);
tft.print(text);

return ypos + textHeight;
}

#endif
