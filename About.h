#ifndef ABOUTMODULE_H
#define ABOUTMODULE_H

#include "Module.h"

/**
 * Show info
 * prototype "pages" for modules
 */
class About: public Module
{
public:
  About() {}   // use moduleSetup() for activate
  ~About() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("About::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);
    analogWrite(TFT_BACKLIGHT, 222);

    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("About::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false);
  }

  virtual void moduleReset()
  {
    about_mode  = 0;
    about_state = 0;
    about_delay = 100;
    Serial.println("About::moduleReset()");
  }

  virtual void leftButton()
  {
    about_mode  = (about_mode+1) % 2;
    about_state = 0;
    about_delay = 100;
    Serial.print("About::leftButton() - about_mode - "); Serial.println(about_mode);
  }

  virtual void rightButton()
  {
    about_delay = 100;
    Serial.println("About::rightButton()");
  }

  virtual unsigned long getModuleDelay() {
    return about_delay;
  }

  virtual void loop()
  {
    //Serial.print("About::loop() - "); Serial.println(millis());

    if (about_mode == 1) {
      page_one();
    } else {
      page_zero();
    }
  }

private:
  int about_mode;
  int about_state;
  int about_delay;

  /*
   * scrolling text, ala star wars
   */
  void page_zero()
  {
    //Serial.println("About::page_zero()");
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(false);

    String msg[] = {
      "",
      "",
      "",
      "",
      "---",
      "hardware by",
      "Adafruit",
      "",
      "Circuit",
      "Playground",
      "Bluefruit LE",
      "+",
      "TFT Gizmo",
      "",
      "---",
      "software by",
      "kwmccabe",
      };

    int line = 1;
    int cy = tft.height()/4;
    for (int i = about_state; i < about_state + ELEMENTS(msg); i++) {
      int idx = i % ELEMENTS(msg);

      int textSize = line;
      tft.setTextSize(textSize);
      int textWidth  = getTextWidth( msg[idx] );
      int textHeight = getTextHeight( msg[idx] );
      int cx = (tft.width()/2)-(textWidth/2);

      tft.setCursor(cx, cy);
      tft.print(msg[idx]);
//Serial.print("About::page_zero - "); Serial.print(idx); Serial.print(","); Serial.println(msg[idx]);

      cy += textHeight;
      if (cy > tft.height()) { break; }
      line++;
    }
    about_state = (about_state+1) % ELEMENTS(msg);
    about_delay = 1000;
//Serial.print("About::page_zero - about_state - "); Serial.println(about_state);
  }

   /*
   * static text
   */
  void page_one()
  {
    String msg[] = {
      "Jabberwocky",
      "By Lewis Carroll",
      "",
      "'Twas brillig, and the slithy toves",
      "  Did gyre and gimble in the wabe:",
      "All mimsy were the borogoves,",
      "  And the mome raths outgrabe.",
      "",
      "\"Beware the Jabberwock, my son!",
      "  The jaws that bite, the claws that catch!",
      "Beware the Jubjub bird, and shun",
      "  The frumious Bandersnatch!\"",
      "",
      "He took his vorpal sword in hand;",
      "  Long time the manxome foe he sought—",
      "So rested he by the Tumtum tree",
      "  And stood awhile in thought.",
      "",
      "And, as in uffish thought he stood,",
      "  The Jabberwock, with eyes of flame,",
      "Came whiffling through the tulgey wood,",
      "  And burbled as it came!",
      "",
      "One, two! One, two! And through and through",
      "  The vorpal blade went snicker-snack!",
      "He left it dead, and with its head",
      "  He went galumphing back.",
      "",
      "\"And hast thou slain the Jabberwock?",
      "  Come to my arms, my beamish boy!",
      "O frabjous day! Callooh! Callay!\"",
      "  He chortled in his joy.",
      "",
      "'Twas brillig, and the slithy toves",
      "  Did gyre and gimble in the wabe:",
      "All mimsy were the borogoves,",
      "  And the mome raths outgrabe.",
      "",
      "","","","",
    };

    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(true);


    int textSize = 1;
    tft.setTextSize(textSize);
    int textHeight = getTextHeight( "000" );

    int cx = 1;
    int cy = cx;
    //cy = printTitle( "Playground", 0, cy );

    int line = 1;
    for (int i = about_state; i < about_state + ELEMENTS(msg); i++) {
      int idx = i % ELEMENTS(msg);

      if (idx == 0) {
        cy = printTitle( msg[idx], 0, cy );
        tft.setTextSize(textSize);  // reset

      } else {
        tft.setCursor(cx, cy);
        tft.print(msg[idx]);
        cy += textHeight;
      }
//Serial.print("About::page_one - "); Serial.print(idx); Serial.print(","); Serial.println(msg[idx]);

      if (cy > tft.height()) { break; }
      line++;
    }

    about_state = (about_state+tft.height()/textHeight/4) % ELEMENTS(msg);
    about_delay = 60*1000;
//Serial.print("About::page_one - about_state - "); Serial.println(about_state);
  }


};

#endif

