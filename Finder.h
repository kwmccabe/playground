#ifndef FINDERMODULE_H
#define FINDERMODULE_H

#include "Module.h"
extern String MENUS[30][4];

/**
 * Hierarchical listing of available modules 
 * MENUS is global as defined in the main file, playground.ino
 * 
 * MENUS[i]:
 * [0] string finder_menu name
 * [1] string finder_menu || int MODULE index for global Module* modules[] = {}
 * [2] string menu title
 * [3] string menu description, 3 lines max
 */
class Finder: public Module 
{
public:
  int MODULE;  // see Main::loop()

  Finder() {}    // use moduleSetup() for activate
  ~Finder() {}   // use moduleTeardown() for deactivate
  
  virtual void moduleSetup() 
  {
    Serial.println("Finder::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_WHITE);
    analogWrite(TFT_BACKLIGHT, 222);
    tft.setTextWrap(true);

    moduleReset();
  }
  
  virtual void moduleTeardown() 
  {
    Serial.println("Finder::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false); 
  }
  
  virtual void moduleReset() 
  {
    MODULE = 0;
    finder_menu = "m0";
    finder_item = 0;
    Serial.println("Finder::moduleReset()");
    update_display();
  }

  virtual void leftButton() 
  {
    String menu_value = getOption( finder_item, 1 );
    if (menu_value.toInt() > 0) {
      MODULE = menu_value.toInt();
    } else {
      finder_menu = menu_value;
    }
    finder_item = 0;
    
    Serial.print("Finder::leftButton() - finder_menu,finder_item - "); Serial.print(finder_menu); Serial.print(","); Serial.println(finder_item);
    update_display();
  }

  virtual void rightButton() 
  {
    int cnt_options = countOptions();
    finder_item = (finder_item+1) % cnt_options;
    Serial.print("Finder::rightButton() - finder_menu,finder_item - "); Serial.print(finder_menu); Serial.print(","); Serial.println(finder_item);
    update_display();
  }

  virtual unsigned long getModuleDelay() {
    return 1000;    
  }

  virtual void loop() 
  {
    //Serial.print("Finder::loop() - "); Serial.println(millis());
    //update_display();
  }


private:
  String finder_menu;
  int finder_item;

  /*
   * count menu values per current finder_menu
   */
  int countOptions()
  {
    int result = 0;
    for (int i = 0; i < ELEMENTS(MENUS); i++) {
      if (MENUS[i][0] != finder_menu) { continue; }
      result++;
    }
//Serial.print("Finder::countMenuOption( "); Serial.print(finder_menu); Serial.print(" ) - "); Serial.println(result);
    return result;
  }
  
  /*
   * get menu value per current finder_menu
   */
  String getOption( int option_idx, int fld_idx ) 
  {
    String result = "";
    int idx = 0;
    for (int i = 0; i < ELEMENTS(MENUS); i++) {
      if (MENUS[i][0] != finder_menu) { continue; }
      if (idx == option_idx) { 
        result = MENUS[i][fld_idx]; 
        break;
      }
      idx++;
    }
Serial.print("Finder::getOption( "); Serial.print(finder_menu); Serial.print(", "); Serial.print(option_idx); Serial.print(", "); Serial.print(fld_idx); Serial.print(" )");
Serial.print(" - "); Serial.println(result); 
    return result;
  }

  /*
   * show option names and selected description
   */
  void update_display() 
  {
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    //tft.setFont(&Org_01);
    
    // main title
    String display_value = getOption( 0, 2 );
    int textSize = 3;
    tft.setTextSize(textSize);
    int textWidth = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = 6;
    int cy = cx; // + textHeight;
    tft.setCursor(cx, cy);
    tft.print(display_value);
    cy += textHeight;

    // options
    textSize--;
    tft.setTextSize(textSize);
    textHeight = getTextHeight( "X" );
    
    int cnt_options = countOptions();
    for (int i = 1; i < cnt_options; i++) {
      display_value = getOption( i, 2 );
      String lead = (i == finder_item) ? "+ " : "- ";

      tft.setCursor(cx, cy);
      tft.print(lead + display_value);
      cy += textHeight;
    }

    // desc
    display_value = getOption( finder_item, 3 );
    if (display_value != "") {
      textSize--;
      tft.setTextSize(textSize);
      textHeight = getTextHeight( "X" );
      cx = 0;
      cy = floor(tft.height() - (3*textHeight)) - cx;
      tft.setCursor(cx, cy);
      tft.print(display_value);
    }
    
    //tft.setFont();
  }
  
};

#endif
