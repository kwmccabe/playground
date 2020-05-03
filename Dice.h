#ifndef DICEMODULE_H
#define DICEMODULE_H

#include "Module.h"

/**
 * Select random number per optional number of faces
 */
class Dice: public Module 
{
public:  
  Dice() {}   // use moduleSetup() for activate
  ~Dice() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup() 
  {
    Serial.println("Dice::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(faces[dice_mode][1]);
    analogWrite(TFT_BACKLIGHT, 222);
    tft.setTextWrap(false);

    dice_mode  = 0;  // index to faces[]
    dice_state = 0;  // countdown for roll animation
    dice_roll  = 0;  // current result

    moduleReset();
  }
  
  virtual void moduleTeardown() 
  {
    Serial.println("Dice::moduleTeardown()");

    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false); 
  }
  
  virtual void moduleReset() 
  {
    dice_state = random(6,18);
    Serial.println("Dice::moduleReset()");
    update_background();
  }

  virtual void leftButton() 
  {
    dice_mode = (dice_mode+1) % ELEMENTS(faces);
    Serial.print("Dice::leftButton() - dice_mode,faces - "); Serial.print(dice_mode);Serial.print(","); Serial.println(faces[dice_mode][0]);
    moduleReset();
  }

  virtual void rightButton() 
  {
    Serial.println("Dice::rightButton()");
    moduleReset();
  }

  virtual unsigned long getModuleDelay() {
    if (dice_state > random(4,7)) { return 100; }
    if (dice_state > random(1,3)) { return 240; }
    return 400;
  }

  virtual void loop() 
  {
    //Serial.print("Dice::loop() - "); Serial.println(millis());
    
    if (dice_state == 0) { return; }
    int sides = faces[dice_mode][0];
    dice_roll = random( 1, (sides+1) );
    Serial.print("Dice::loop() - sides,roll - "); Serial.print(sides); Serial.print(","); Serial.println(dice_roll);
    
    update_foreground();
    CircuitPlayground.playTone(random(262,1047), 20, false); 

    dice_state = (dice_state > 0) ? dice_state-1 : 0;
  }

private:
  int dice_mode;
  int dice_state;
  int dice_roll;

  const uint16_t faces[9][3] = { 
      {   2, ST77XX_WHITE,   ST77XX_BLACK },
      {   3, ST77XX_MAGENTA, ST77XX_BLACK },
      {   4, ST77XX_BLUE,    ST77XX_YELLOW },
      {   6, ST77XX_CYAN,    ST77XX_BLACK },
      {   8, ST77XX_GREEN,   ST77XX_BLACK },
      {  10, ST77XX_YELLOW,  ST77XX_BLUE },
      {  12, ST77XX_ORANGE,  ST77XX_BLACK },
      {  20, ST77XX_RED,     ST77XX_BLACK },
      { 100, ST77XX_BLACK,   ST77XX_WHITE }
      };

  /*
   * show mode info
   */
  void update_background() 
  {
    tft.fillScreen(faces[dice_mode][1]);
    tft.setTextColor(faces[dice_mode][2]);

    int textSize = 4;       // char width=textsize*6, height=textsize*8
    tft.setTextSize(textSize);
    int cx = 20;
    int cy = 20;

    //tft.fillRect(cx, cy, 4*textSize*6, textSize*8, faces[dice_mode][1]);
    tft.setCursor(cx, cy);
    tft.print("D"); tft.print(faces[dice_mode][0]);
  }
  
  /*
   * show dice value
   */
  void update_foreground() 
  {
    //tft.fillScreen(faces[dice_mode][1]);
    tft.setTextColor(faces[dice_mode][2]);

    String display_value = String(dice_roll);

    int textSize = 8;
    tft.setTextSize(textSize);
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = tft.width()/2 - textWidth/2;
    int cy = tft.height()/2 - textHeight/2;

    textWidth  = getTextWidth( "XXX" );
    tft.fillRect((tft.width()/2 - textWidth/2), cy, textWidth, textHeight, faces[dice_mode][1]);
    
    tft.setCursor(cx, cy);
    tft.print(display_value);
  }
  
};

#endif
