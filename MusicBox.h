#ifndef MUSICBOXMODULE_H
#define MUSICBOXMODULE_H

#include "Module.h"
#include "MusicNotes.h"

// { musicbox_menu, musicbox_item, musicbox_name }
String TUNES[][3] = {
  {   "m0", "m0", "MUSIC BOX" },
  {   "m0", "m1", "ETUDES" },
  {   "m0", "m2", "SCALES" },
  {   "m0", "m3", "TUNES" },
  {   "m0", "playTest_NoteTypes",  "Note Types" },

  {   "m1", "m0", "ETUDES" },
  {   "m1", "playTune_Hatikvuh",     "Hatikvuh" },
  {   "m1", "playTune_LargoHandel",  "Largo - Handel" },
  {   "m1", "playTune_PrestoHaydn",  "Presto - Haydn" },
  {   "m1", "playTune_PrestoMozart",  "Presto - Mozart" },

  {   "m2", "m0", "SCALES" },
  // major
  {   "m2", "playScale_C4",  "C4 Major" },
  {   "m2", "playScale_D4",  "D4 Major" },
  {   "m2", "playScale_E4",  "E4 Major" },
  {   "m2", "playScale_F4",  "F4 Major" },
  {   "m2", "playScale_G4",  "G4 Major" },
  {   "m2", "playScale_A4",  "A4 Major" },
  {   "m2", "playScale_B4",  "B4 Major" },
  // minor
  // blues

  {   "m3", "m0", "TUNES" },
  {   "m3", "playTune_AlleyCat",  "Alley Cat" },
  {   "m3", "playTune_BigBen",  "Big Ben" },
  {   "m3", "playTune_MissionImpossible",  "Mission Impossible" },
  {   "m3", "playTune_StarWars",  "Star Wars" },
  // masterpiece
  // 007?

  };

/**
 * play simple tunes with the onboard tone generator
 *   void Adafruit_CircuitPlayground::playTone(uint16_t freq, uint16_t time, bool wait)
 * display tune name, bpm, graph range, and current note name
 * graph notes with simplified music notation
 */
class MusicBox: public Module {
public:
  MusicBox() {}   // use moduleSetup() for activate
  ~MusicBox() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup()
  {
    Serial.println("MusicBox::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_BLACK);
    analogWrite(TFT_BACKLIGHT, 222);
    tft.setTextWrap(false);

    moduleReset();
  }

  virtual void moduleTeardown()
  {
    Serial.println("MusicBox::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false);
  }

  virtual void moduleReset()
  {
    MUTE = true;
    musicbox_mode  = 0;

    musicbox_menu = "m0";
    musicbox_item = "";
    musicbox_tune = "";
    
    //musicbox_state = 0;
    musicbox_delay = 500;
    //musicbox_bpm = 90;
    Serial.println("MusicBox::moduleReset()");
    show_options();
    //update_background();
  }

  virtual void leftButton()
  {
    if (musicbox_mode == 0) {
      String menu_value = getOption( musicbox_menu, musicbox_item, 1 );
//Serial.print("MusicBox::leftButton() - menu_value - "); Serial.println(menu_value);

      if (menu_value.length() > 3) {
        musicbox_mode = 1;
        musicbox_item = menu_value; 
        musicbox_tune = getOption( musicbox_menu, musicbox_item, 2 );
        update_background();
      } else if (menu_value.length() > 0) {
        musicbox_menu = menu_value;
        musicbox_item = getNextOption( musicbox_menu, "" );
        musicbox_tune = "";
        show_options();
      } else {
        musicbox_menu = "m0";
        musicbox_item = "m0";
        musicbox_tune = "";
      }
Serial.print("MusicBox::leftButton() - musicbox_menu,musicbox_item - "); Serial.print(musicbox_menu); Serial.print(","); Serial.println(musicbox_item);        
      return;
    }
    
    // if (musicbox_mode != 0) :
    Serial.println("MusicBox::leftButton()");
    moduleReset();
}

  virtual void rightButton()
  {
    if (musicbox_mode == 0) {
      musicbox_item = getNextOption( musicbox_menu, musicbox_item );
      if (musicbox_item.equals(musicbox_menu)) { musicbox_item = getNextOption( musicbox_menu, musicbox_item ); }
      Serial.print("MusicBox::rightButton() - musicbox_menu,musicbox_item - "); Serial.print(musicbox_menu); Serial.print(","); Serial.println(musicbox_item);
      show_options();
      return;
    }
    
    // if (musicbox_mode != 0) :
    Serial.println("MusicBox::rightButton()");
    MUTE = !MUTE;
    update_background();
  }

  virtual unsigned long getModuleDelay() {
    return musicbox_delay;
  }

  virtual void loop()
  {
    //Serial.print("MusicBox::loop() - "); Serial.println(millis());

    if (musicbox_mode == 0) {
      // use show_options() to explicitly redraw menu
      return;
    }

    // if (musicbox_mode != 0) :
    //int chars = musicbox_tune.length();

    if (musicbox_item == "playTest_NoteTypes") { playTest_NoteTypes(); }

    if (musicbox_item == "playScale_C4") { playScale_C4(); }
    if (musicbox_item == "playScale_D4") { playScale_D4(); }
    if (musicbox_item == "playScale_E4") { playScale_E4(); }
    if (musicbox_item == "playScale_F4") { playScale_F4(); }
    if (musicbox_item == "playScale_G4") { playScale_G4(); }
    if (musicbox_item == "playScale_A4") { playScale_A4(); }
    if (musicbox_item == "playScale_B4") { playScale_B4(); }

    if (musicbox_item == "playTune_Hatikvuh")     { playTune_Hatikvuh(); }
    if (musicbox_item == "playTune_LargoHandel")  { playTune_LargoHandel(); }
    if (musicbox_item == "playTune_PrestoHaydn")  { playTune_PrestoHaydn(); }
    if (musicbox_item == "playTune_PrestoMozart") { playTune_PrestoMozart(); }

    if (musicbox_item == "playTune_AlleyCat")          { playTune_AlleyCat(); }
    if (musicbox_item == "playTune_BigBen")            { playTune_BigBen(); }
    if (musicbox_item == "playTune_MissionImpossible") { playTune_MissionImpossible(); }
    if (musicbox_item == "playTune_StarWars")          { playTune_StarWars(); }

    //if (musicbox_tune.length() != chars) {
      //update_tune_name();
    //}
  }


private:
  bool MUTE = true;
  int musicbox_mode;      // select vs play

  String musicbox_menu;   // selected menu
  String musicbox_item;   // selected tune
  String musicbox_tune;   // tune name

  int musicbox_state;     // current tone index
  int musicbox_delay;     // set per tone duration
  int musicbox_bpm;       // set per tune

  // graph data
  int box_size = 10;
  int box[10][2];         // { tone_idx, time_idx }
  int box_idx;            // current box index
  int box_range_min;      // tone_idx
  int box_range_max;      // tone_idx
  
  /*
   * get option value per musicbox_menu, musicbox_item, and idx 0,1,2
   */
  String getOption( String menu_key, String option_key, int fld_idx ) 
  {
    String result = "";
    for (int i = 0; i < ELEMENTS(TUNES); i++) {
      if (TUNES[i][0] != menu_key) { continue; }
      if (TUNES[i][1] == option_key) {
        result = TUNES[i][fld_idx]; 
        break;
      }
    }
//Serial.print("MusicBox::getOption( "); Serial.print(musicbox_menu); Serial.print(", "); Serial.print(option_key); Serial.print(", "); Serial.print(fld_idx); Serial.println(" )");
//Serial.print("MusicBox::getOption() - result - "); Serial.println(result); 
    return result;
  }

  /*
   * get menu value per current musicbox_menu
   */
  String getNextOption( String menu_key, String option_key ) 
  {
    String result = "";
    bool next = false;
    for (int i = 0; i < ELEMENTS(TUNES); i++) {
      if (TUNES[i][0] != menu_key) { continue; }
      if (result.length() == 0) { result = TUNES[i][1]; }
      if (next) { 
        result = TUNES[i][1];
        break;
      }      
      if (TUNES[i][1] == option_key) { 
        next = true; 
      }
    }
//Serial.print("MusicBox::getNextOption( "); Serial.print(musicbox_menu); Serial.print(", "); Serial.print(option_key); Serial.println(" )");
//Serial.print("MusicBox::getNextOption() - result - "); Serial.println(result); 
    return result;
  }

  /*
   * show option names and selected description
   */
  void show_options() 
  {
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);
    
    // main title
    String display_value = getOption( "m0", "m0", 2 );
    int textSize = 3;
    tft.setTextSize(textSize);
    int textWidth = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = 6;
    int cy = cx;// + textHeight;
    tft.setCursor(cx, cy);
    tft.print(display_value);
    cy += textHeight;

    // options
    textSize--;
    tft.setTextSize(textSize);
    textHeight = getTextHeight( "X" );

    bool first = (musicbox_menu.equals("m0"));
    for (int i = 0; i < ELEMENTS(TUNES); i++) {
      if (TUNES[i][0] != musicbox_menu) { continue; }
      if (first) { first = false; continue; }

      display_value = TUNES[i][2];
      String lead = (TUNES[i][1] == musicbox_item) ? "+ " : "- ";

      tft.setCursor(cx, cy);
      tft.print(lead + display_value);
      cy += textHeight;
    }
    
  }
  
  /*
   * (re)init graph data
   */
  void clear_box()
  {
    musicbox_state = 0;
    box_range_max = fC6;  // { fF5, fC6, fC6, fC7, fC8, fB8 }
    box_range_min = fC2;  // { fG2, fC2, fC1, fC1, fA0, fC0 }
    for (int i = 0; i < box_size; i++) {
      box[i][0] = -1;
      box[i][1] = -1;
    }
  }

  /*
   * insert graph data
   */
  void add_box_note( int tone_idx, int time_idx )
  {
    box_idx = (box_idx+1) % box_size;
    box[box_idx][0] = tone_idx;
    box[box_idx][1] = time_idx;
//Serial.print("MusicBox.add_box_note( "); Serial.print(tone_idx); Serial.print(", "); Serial.print(time_idx);  Serial.println(" )");

    // expand box_range if level out-of-bounds
    if (0 < TONES[tone_idx].level && TONES[tone_idx].level < TONES[box_range_min].level) 
      { box_range_min = min(tone_idx+3,fC0); }
    if (0 < TONES[tone_idx].level && TONES[tone_idx].level > TONES[box_range_max].level) 
      { box_range_max = max(tone_idx-3,fB8); }
  }
  
  /*
   * show mode info
   */
  void update_background()
  {
//Serial.println("MusicBox::update_background()");
    tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);

    int textSize   = 2;
    tft.setTextSize(textSize);
    //int textWidth  = getTextWidth( "X" );
    int textHeight = getTextHeight( "X" );
    int cx = 0;
    int cy = 0;

    // upper-left corner - mode
    String display_value = String(musicbox_bpm) + "bpm";
    cx = 6;
    cy = cx;
    tft.setCursor(cx, cy);
    tft.print(display_value);

    // upper-left corner - range
    cy += textHeight;
    display_value = TONES[box_range_min].name + "-" + TONES[box_range_max].name;
    tft.setCursor(cx, cy);
    tft.print(display_value);

    // bottom-center - title
    update_tune_name();

    // main
    clear_box();
    update_foreground();
  }

  /*
   * show tone name
   */
  void update_foreground()
  {
//Serial.println("MusicBox::update_foreground()");

    update_meter();

    tft.setTextColor(ST77XX_BLACK);
    int textSize = 4;
    tft.setTextSize(textSize);

    // upper-right corner - current freq
    String display_value = "--";
    if (box[box_idx][0] >= 0) {
      display_value = TONES[box[box_idx][0]].name;
    }
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = tft.width()-textWidth;
    int cy = 6;

    if (box[box_idx][0] >= 0 && TONES[box[box_idx][0]].freq > 0) {
      tft.fillRect(tft.width()/2, cy, tft.width()/2, textHeight, ST77XX_WHITE);

      tft.setCursor(cx, cy);
      tft.print(display_value);
    }

  }

  /*
   * show mode info
   */
  void update_tune_name()
  {
//Serial.println("MusicBox::update_background()");
    //tft.fillScreen(ST77XX_WHITE);
    tft.setTextColor(ST77XX_BLACK);

    int textSize = 2;
    tft.setTextSize(textSize);

    // bottom-center
    String display_value = (musicbox_tune.length() > 0) ? musicbox_tune : "Music Box";
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );
    int cx = tft.width()/2 - textWidth/2;
    int cy = tft.height() - textHeight - 4;

    //tft.fillRect(0, cy, tft.width(), textHeight, ST77XX_WHITE);
    tft.fillRect(0, cy, tft.width(), tft.height()-cy, ST77XX_WHITE);
    tft.setCursor(cx, cy);
    tft.print(display_value);
  }

  /*
   * graph recent notes (box_size columns)
   * @uses drawClef()
   * @uses drawRest()
   * @uses drawNote()
   * @uses drawTime()
   */
  void update_meter()
  {
//Serial.println("MusicBox::update_meter()");

    int meter_x = 6;
    int meter_y = 40;
    int meter_w = tft.width() - (2*meter_x);
    int meter_h = tft.height() - meter_y - 24;

    int cx = meter_x + 1;
    int cy = meter_y + 1;
    int cw = meter_w - 2;
    int ch = meter_h - 2;

    int bar_pad = 4;
    int bar_wid = floor((cw - bar_pad*(box_size+1))/box_size);
    int bar_2nd = floor(bar_wid/2);

    int fF5_lvl  = (int)lerp(TONES[fF5].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, ch);
    int fD5_lvl  = (int)lerp(TONES[fD5].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, ch);
    int note_hgt = min(abs(fF5_lvl - fD5_lvl), bar_2nd);

    // opener
    tft.fillRect(cx, cy, bar_pad, ch, ST77XX_WHITE);
    drawClef( cx, cy, bar_pad, ch, -1 );

    cx += bar_pad;
    for (int i = 0; i < box_size; i++)
    {
      int idx = (box_idx + 1 + i) % box_size;
      int freq_idx = box[idx][0];
      int time_idx = box[idx][1];
//Serial.print("idx,freq_idx,time_idx - "); Serial.print(idx); Serial.print(","); Serial.print(freq_idx); Serial.print(","); Serial.println(time_idx);

      // clear
      tft.fillRect(cx, cy, bar_wid+bar_pad, ch, ST77XX_WHITE);
      drawClef( cx, cy, bar_wid+bar_pad, ch, freq_idx );
//tft.drawRect(cx, cy, bar_wid, ch, ST77XX_YELLOW);  // DEBUG

      // update
      if (freq_idx >= 0 && TONES[freq_idx].level > 0) {
        int lvl = (int)lerp(TONES[freq_idx].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, ch);
        drawNote( cx+bar_2nd, cy+ch-lvl, note_hgt, freq_idx, time_idx );

      } else if (time_idx >= 0 && TIMES[time_idx].time > 0) {
        drawRest( cx+bar_2nd, cy+ch, bar_wid, time_idx );

      }

      if (time_idx == T35 || time_idx == T25) {  // (3.5)  // (2.5)
        int fC4_lvl = (int)lerp(TONES[fC4].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, ch);
        drawTime( cx+bar_2nd, cy+ch-fC4_lvl, bar_wid, time_idx );
      }
      
      cx += bar_wid+bar_pad;
    }

    // closer
    if (cx < meter_x + meter_w - 1) {
      tft.fillRect(cx, cy, meter_x + meter_w - 1 - cx, ch, ST77XX_WHITE);
      drawClef( cx, cy, meter_x + meter_w - 1 - cx, ch, -1 );
    }

    // outline
    tft.drawRect(meter_x, meter_y, meter_w, meter_h, ST77XX_BLACK);
    tft.drawRect(meter_x-1, meter_y-1, meter_w+2, meter_h+2, ST77XX_WHITE);
    tft.drawRect(meter_x-2, meter_y-2, meter_w+4, meter_h+4, ST77XX_WHITE);
  }

  /*
   *
   */
  void drawTime( int x, int y, int w, int time_idx )
  {
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(1);

    String display_value = TIMES[time_idx].name;
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );

    //tft.fillRect(x-w/2, y-textHeight-2, w, textHeight+2, ST77XX_BLACK);
    tft.setCursor(x-textWidth/2, y-textHeight/2);
    tft.print(display_value);
  }

  /*
   *
   */
  void drawRest( int x, int y, int w, int time_idx )
  {
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    String display_value = TIMES[time_idx].name;
    int textWidth  = getTextWidth( display_value );
    int textHeight = getTextHeight( display_value );

    tft.fillRect(x-w/2, y-textHeight-2, w, textHeight+2, ST77XX_BLACK);
    tft.setCursor(x-textWidth/2, y-textHeight);
    tft.print(display_value);
  }

  /*
   *
   */
  void drawNote( int x, int y, int note_hgt, int freq_idx , int time_idx )
  {
    uint16_t color_base = ST77XX_BLACK;
    uint16_t color_mark = ST77XX_RED;
    
    int d2 = max(floor(note_hgt/2), 3);
    int d3 = max(floor(note_hgt/3), 2);
    int d4 = max(floor(note_hgt/4), 1);
    int d6 = max(floor(note_hgt/6), 1);
//Serial.print("note_hgt,d2,d3,d4- "); Serial.print(note_hgt); Serial.print(","); Serial.print(d2);  Serial.print(","); Serial.print(d3);  Serial.print(","); Serial.println(d4);

    //String tone_name = TONES[freq_idx].name;
    //int tone_freq    = TONES[freq_idx].freq;
    int tone_level   = TONES[freq_idx].level;
    String tone_type = TONES[freq_idx].type;

    int stem_up = (tone_level < TONES[fB2].level || (tone_level >= TONES[fC4].level && tone_level < TONES[fF5].level)) ? -1 : 1;

    if (tone_type.indexOf("+") != -1) {                                                  // SHARP
      // top-bot
      tft.drawLine(x-note_hgt-d4, y-d2, x-note_hgt-d4, y+d2, color_mark);
      tft.drawLine(x-note_hgt+d4, y-d2, x-note_hgt+d4, y+d2, color_mark);
      // lft-rgt
      tft.drawLine(x-note_hgt-d2, y-d4, x-note_hgt+d2, y-d4, color_mark);
      tft.drawLine(x-note_hgt-d2, y+d4, x-note_hgt+d2, y+d4, color_mark);
    
    } else if (tone_type.indexOf("-") != -1) {                                           // FLAT
      tft.drawCircle(x-note_hgt, y, d3, color_mark);
      tft.drawLine(x-note_hgt-d3, y-(2*note_hgt), x-note_hgt-d3, y, color_mark);
      
    }

    if (time_idx == T40) {         // (4.0) Whole note
      tft.drawCircle(x, y, d2, color_base);                                              // CIRCLE
      tft.drawCircle(x, y, d2+1, color_base);                                            // CIRCLE+1

    } else if (time_idx == T35) {  // (3.5)
//tft.drawCircle(x, y, d2, ST77XX_YELLOW);  // ???
      tft.drawCircle(x, y, d2, color_mark);                                              // CIRCLE

    } else if (time_idx == T30) {  // (3.0)
      tft.drawCircle(x, y, d2, color_base);                                              // CIRCLE
      tft.drawCircle(x, y, d2-1, color_base);                                            // CIRCLE-1
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillCircle(x+note_hgt, y-d2, d4, color_mark);                                  // DOT

    } else if (time_idx == T25) {  // (2.5)
//tft.drawCircle(x, y, d2, ST77XX_YELLOW);  // ???
      tft.drawCircle(x, y, d2, color_mark);                                              // CIRCLE

    } else if (time_idx == T20) {  // (2.0) Half
      tft.drawCircle(x, y, d2, color_base);                                              // CIRCLE
      tft.drawCircle(x, y, d2-1, color_base);                                            // CIRCLE-1
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE

    } else if (time_idx == T15) {  // (1.5)
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillCircle(x+note_hgt, y-d2, d4, color_mark);                                  // DOT

    } else if (time_idx == T10) {  // (1.0) Quarter
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE

    } else if (time_idx == t34) {  // (3/4)
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillCircle(x+note_hgt, y-d2, d4, color_mark);                                  // DOT
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up, note_hgt, -d3*stem_up, color_mark);                   // FLAG 1

    } else if (time_idx == t23) {  // (2/3)
      tft.drawTriangle(x-d2, y+d2, x+d2, y+d2, x, y-d2, color_base);                     // TRIANGLE
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y+d2, color_base);                // LINE 2

    } else if (time_idx == t12) {  // (1/2) Eighth
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up, note_hgt, -d3*stem_up, color_mark);                   // FLAG 1

    } else if (time_idx == t13) {  // (1/3) Twelfth
      tft.fillTriangle(x-d2, y+d2, x+d2, y+d2, x, y-d2, color_base);                     // TRIANGLE
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y+d2, color_base);                // LINE 2

    } else if (time_idx == t14) {  // (1/4) Sixteenth
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up, note_hgt, -d3*stem_up, color_mark);                   // FLAG 1
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up-(d3+2)*stem_up, note_hgt, -d3*stem_up, color_mark);    // FLAG 2

    } else if (time_idx == t18) {  // (1/8) Thirty-second
      tft.fillCircle(x, y, d2, color_base);                                              // DISK
      tft.drawLine(x+d2, y+(3*note_hgt)*stem_up, x+d2, y, color_base);                   // LINE
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up, note_hgt, -d3*stem_up, color_mark);                   // FLAG 1
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up-(d3+2)*stem_up, note_hgt, -d3*stem_up, color_mark);    // FLAG 2
      tft.fillRect(x+d2, y+(3*note_hgt)*stem_up-(2*d3+4)*stem_up, note_hgt, -d3*stem_up, color_mark);  // FLAG 3
    }

  }

  /*
   *
   */
  void drawClef( int x, int y, int w, int h, int freq_idx )
  {
    uint16_t color = RGB888toRGB565("C9C9C9");

    // treble clef
    int fF5_lvl = (int)lerp(TONES[fF5].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fD5_lvl = (int)lerp(TONES[fD5].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fB4_lvl = (int)lerp(TONES[fB4].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fG4_lvl = (int)lerp(TONES[fG4].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fE4_lvl = (int)lerp(TONES[fE4].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);

    tft.drawLine(x, y+h-fF5_lvl, x+w, y+h-fF5_lvl, color);
    tft.drawLine(x, y+h-fD5_lvl, x+w, y+h-fD5_lvl, color);
    tft.drawLine(x, y+h-fB4_lvl, x+w, y+h-fB4_lvl, color);
    tft.drawLine(x, y+h-fG4_lvl, x+w, y+h-fG4_lvl, color);
    tft.drawLine(x, y+h-fE4_lvl, x+w, y+h-fE4_lvl, color);

    // bass clef
    int fA3_lvl = (int)lerp(TONES[fA3].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fF3_lvl = (int)lerp(TONES[fF3].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fD3_lvl = (int)lerp(TONES[fD3].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fB2_lvl = (int)lerp(TONES[fB2].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
    int fG2_lvl = (int)lerp(TONES[fG2].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);

    tft.drawLine(x, y+h-fA3_lvl, x+w, y+h-fA3_lvl, color);
    tft.drawLine(x, y+h-fF3_lvl, x+w, y+h-fF3_lvl, color);
    tft.drawLine(x, y+h-fD3_lvl, x+w, y+h-fD3_lvl, color);
    tft.drawLine(x, y+h-fB2_lvl, x+w, y+h-fB2_lvl, color);
    tft.drawLine(x, y+h-fG2_lvl, x+w, y+h-fG2_lvl, color);

    if (freq_idx >= 0 &&
        TONES[box_range_min].level <= TONES[freq_idx].level &&
        TONES[freq_idx].level <= TONES[box_range_max].level
        )
    {
      int freq_level = TONES[freq_idx].level;

      // above-clef : fB8,fG8,fE8,fC8,fA7,fF7,fD7,fB6,fG6,fE6,fC6,fA5
      if (freq_level >= TONES[fG8].level) {
        int lvl = (int)lerp(TONES[fG8].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fE8].level) {
        int lvl = (int)lerp(TONES[fE8].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fC8].level) {
        int lvl = (int)lerp(TONES[fC8].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fA7].level) {
        int lvl = (int)lerp(TONES[fA7].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fF7].level) {
        int lvl = (int)lerp(TONES[fF7].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fD7].level) {
        int lvl = (int)lerp(TONES[fD7].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fB6].level) {
        int lvl = (int)lerp(TONES[fB6].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fG6].level) {
        int lvl = (int)lerp(TONES[fG6].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fE6].level) {
        int lvl = (int)lerp(TONES[fE6].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fE6].level) {
        int lvl = (int)lerp(TONES[fE6].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fC6].level) {
        int lvl = (int)lerp(TONES[fC6].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level >= TONES[fA5].level) {
        int lvl = (int)lerp(TONES[fA5].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }

      // mid-clef : fC4
      if (freq_level == TONES[fC4].level) {
        int lvl = (int)lerp(freq_level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }

      // below-clef : fE2,fC2,fA1,fF1,fD1,fB0,fG0,fE0,fC0
      if (freq_level <= TONES[fE2].level && freq_level >= TONES[box_range_min].level) {
        int lvl = (int)lerp(TONES[fE2].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fC2].level) {
        int lvl = (int)lerp(TONES[fC2].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fA1].level) {
        int lvl = (int)lerp(TONES[fA1].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fF1].level) {
        int lvl = (int)lerp(TONES[fF1].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fD1].level) {
        int lvl = (int)lerp(TONES[fD1].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fB0].level) {
        int lvl = (int)lerp(TONES[fB0].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fG0].level) {
        int lvl = (int)lerp(TONES[fG0].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fE0].level) {
        int lvl = (int)lerp(TONES[fE0].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
      if (freq_level <= TONES[fC0].level) {
        int lvl = (int)lerp(TONES[fC0].level, TONES[box_range_min].level, TONES[box_range_max].level, 0, h);
        tft.drawLine(x, y+h-lvl, x+w, y+h-lvl, color);
      }
    }
  }

  /*
   * increment musicbox_state, play tone, set musicbox_delay for next loop
   * called by playScale_C4(), etc
   */
  void playTones( int bpm, int melody[][2], int elements )
  {
    musicbox_bpm  = bpm;

    float freq = 0;
    float time = 0;

    if ((musicbox_state) >= elements) {
      musicbox_state = 0;

      add_box_note( fREST, T40 );
      musicbox_delay = 60000/musicbox_bpm * TIMES[T40].time;
    } else {
      add_box_note( melody[musicbox_state][0], melody[musicbox_state][1] );

      freq = TONES[melody[musicbox_state][0]].freq;
      time = TIMES[melody[musicbox_state][1]].time;
      musicbox_delay = 60000/musicbox_bpm * time;

      musicbox_state++;
    }

    update_foreground();

//Serial.print("CircuitPlayground.playTone( "); Serial.print(freq); Serial.print(", "); Serial.print(musicbox_delay);  Serial.println(", false )");
    if (!MUTE) {
      CircuitPlayground.playTone( freq, musicbox_delay, false );
    }


  }

  // C-major : C4,  D4,  E4,  F4,  G4,  A4,  B4, C5 : -
  void playScale_C4() {
    Serial.println("MusicBox::playScale_C4");
    int melody[][2] = {
      { fC4, t12 }, { fD4, t14 }, { fE4, t14 }, { fF4, t14 }, { fG4, t14 }, { fA4, t14 }, { fB4, t14 }, { fC5, t12 },
      { fREST, t12 }, { fC4, t12 }, { fC5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // D-major : D4,  E4, FS4,  G4,  A4,  B4, CS5, D5 : #:FC 
  void playScale_D4() {
    Serial.println("MusicBox::playScale_D4");
    int melody[][2] = {
      { fD4, t12 }, { fE4, t14 }, { fFS4, t14 }, { fG4, t14 }, { fA4, t14 }, { fB4, t14 }, { fCS5, t14 }, { fD5, t12 },
      { fREST, t12 }, { fD4, t12 }, { fD5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // E-major : E4, FS4, GS4,  A4,  B4, CS5, DS5, E5 : #:FCGD
  void playScale_E4() {
    Serial.println("MusicBox::playScale_E4");
    int melody[][2] = {
      { fE4, t12 }, { fFS4, t14 }, { fGS4, t14 }, { fA4, t14 }, { fB4, t14 }, { fCS5, t14 }, { fDS5, t14 }, { fE5, t12 },
      { fREST, t12 }, { fE4, t12 }, { fE5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // F-major : F4,  G4,  A4, BF4,  C5,  D5,  E5, F5 : b:B
  void playScale_F4() {
    Serial.println("MusicBox::playScale_F4");
    int melody[][2] = {
      { fF4, t12 }, { fG4, t14 }, { fA4, t14 }, { fBF4, t14 }, { fC5, t14 }, { fD5, t14 }, { fE5, t14 }, { fF5, t12 },
      { fREST, t12 }, { fF4, t12 }, { fF5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // G-major : G4,  A4,  B4,  C5,  D5,  E5, FS5, G5 : #:F
  void playScale_G4() {
    Serial.println("MusicBox::playScale_G4");
    int melody[][2] = {
      { fG4, t12 }, { fA4, t14 }, { fB4, t14 }, { fC5, t14 }, { fD5, t14 }, { fE5, t14 }, { fFS5, t14 }, { fG5, t12 },
      { fREST, t12 }, { fG4, t12 }, { fG5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // A-major : A4,  B4, CS5,  D5,  E5, FS5, GS5, A5 : #:FCG
  void playScale_A4() {
    Serial.println("MusicBox::playScale_A4");
    int melody[][2] = {
      { fA4, t12 }, { fB4, t14 }, { fCS5, t14 }, { fD5, t14 }, { fE5, t14 }, { fFS5, t14 }, { fGS5, t14 }, { fA5, t12 },
      { fREST, t12 }, { fA4, t12 }, { fA5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }
  // B-major : B4, CS5, DS5,  E5, FS5, GS5, AS5, B5 : #:FCGDA
  void playScale_B4() {
    Serial.println("MusicBox::playScale_B4");
    int melody[][2] = {
      { fB4, t12 }, { fCS5, t14 }, { fDS5, t14 }, { fE5, t14 }, { fFS5, t14 }, { fGS5, t14 }, { fAS5, t14 }, { fB5, t12 },
      //{ fB4, t12 }, { fDF5, t14 }, { fEF5, t14 }, { fE5, t14 }, { fGF5, t14 }, { fAF5, t14 }, { fBF5, t14 }, { fB5, t12 },
      { fREST, t12 }, { fB4, t12 }, { fB5, t12 }, { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }

  void playTune_AlleyCat() {
    //Serial.println("MusicBox::playTune_AlleyCat");
    int melody[][2] = {
      //{ fREST, T20 }, 
      { fREST, t12 }, { fDS4, t12 }, { fE4, t13 }, { fG4, t13 }, { fA4, t13 }, 
      { fC5, T10 }, { fB4, T10 }, { fA4, T10 }, { fAF4, T10 }, 
      { fG4, T10 }, { fGS4, T10 }, { fA4, T10 }, { fREST, T10 }, 
      { fG4, t12 }, { fG4, t12 }, { fGS4, T10 }, { fA4, T10 }, { fAS4, T10 }, 
      { fB4, T30 }, { fREST, T10 }, 
      { fC5, T10 }, { fB4, T10 }, { fA4, T10 }, { fAF4, T10 }, 
      { fG4, T10 }, { fGS4, T10 }, { fA4, T10 }, { fREST, T10 }, 
      { fG4, t12 }, { fG4, t12 }, { fGS4, T10 }, { fA4, T10 }, { fB4, T10 }, 
      { fC5, T20 }, { fREST, T10 }, 
      
      { fC5, T10 }, 
      { fD5, T10 }, { fD5, T20 }, { fCS4, T10 }, 
      { fD4, T30 }, { fC5, T10 }, 
      { fD5, T10 }, { fD5, T20 }, { fCS4, T10 }, 
      { fD4, T30 }, { fC5, T10 }, 
      { fD5, T10 }, { fD5, T20 }, { fCS4, T10 }, 
      { fD4, T30 }, { fC5, T10 }, 
      { fD5, T10 }, { fC5, T10 }, { fB4, T10 }, { fA4, T10 }, 
      { fG4, T10 }, { fGF4, T10 }, { fF4, t12 }, { fDS4, t12 }, { fE4, t13 }, { fG4, t13 }, { fA4, t13 }, 
      { fC5, T10 }, { fB4, T10 }, { fA4, T10 }, { fAF4, T10 }, 
      { fG4, T10 }, { fGS4, T10 }, { fA4, T10 }, { fREST, T10 }, 
      { fG4, t12 }, { fG4, t12 }, { fGS4, T10 }, { fA4, T10 }, { fAS4, T10 }, 
      { fB4, T30 }, { fREST, T10 }, 
      { fC5, T10 }, { fB4, T10 }, { fA4, T10 }, { fAF4, T10 }, 
      { fG4, T10 }, { fGS4, T10 }, { fA4, T10 }, { fREST, T10 }, 
      { fG4, t12 }, { fG4, t12 }, { fGS4, T10 }, { fA4, T10 }, { fB4, T10 }, 
      { fC5, T20 }, { fREST, T10 }, 
      
      { fE4, t12 }, { fC4, t12 }, 
      { fD4, t12 }, { fD4, t12 }, { fREST, T10 }, { fDS4, t12 }, { fDS4, t12 }, { fREST, T10 }, 
      { fE4, T10 }, { fG4, T10 }, { fB4, T15 }, { fA4, t12 }, 
      { fE5, T10 }, { fC5, t12 }, { fA4, t12 }, { fEF5, T10 }, { fD5, T10 }, 
      { fC5, T10 }, { fG4, T10 }, { fC4, T20 },

    };
    playTones( 130, melody, ELEMENTS(melody) );
  }

  void playTune_BigBen() {
    //Serial.println("MusicBox::playTune_BigBen");
    int melody[][2] = {
      { fB3, T10 }, { fG3, T10 }, { fA3, T10 }, { fD3, T10 },
      { fD3, T10 }, { fA3, T10 }, { fB3, T10 }, { fG3, T15 },
      { fREST, T40 }, 
    };
    playTones( 90, melody, ELEMENTS(melody) );
  }

  void playTune_MissionImpossible() {
    //Serial.println("MusicBox::playTune_MissionImpossible");
    int melody[][2] = {
      { fAS4, t12 }, { fG4, t12 }, { fD4, T20 },
      { fAS3, T10 }, { fC4, T10 },
      { fAS4, t12 }, { fG4, t12 }, { fCS4, T20 },
      { fF3, T10 }, { fFS3, T10 },
      { fAS4, t12 }, { fG4, t12 }, { fC4, T20 },
      { fAS3, T10 }, { fC4, T10 },
      { fAS4, t12 }, { fC5, t12 },

      { fG3, T10 }, { fREST, t12 }, { fG3, t12 }, { fG3, T10 },
      { fAS3, T10 }, { fC4, T10 },
      { fG3, T10 }, { fREST, t12 }, { fG3, t12 }, { fG3, T10 },
      { fF3, T10 }, { fFS3, T10 },
      { fG3, T10 }, { fREST, t12 }, { fG3, t12 }, { fG3, T10 },
      { fAS3, T10 }, { fC4, T10 },
      { fG3, T10 }, { fREST, t12 }, { fG3, t12 }, { fG3, T10 },
      { fF3, T10 }, { fFS3, T10 },
      { fREST, T30 }, 
    };
    playTones( 160, melody, ELEMENTS(melody) );
  }

  void playTune_StarWars() {
    //Serial.println("MusicBox::playTune_StarWars");
    int melody[][2] = {
      { fD4, t13 }, { fD4, t13 }, { fD4, t13 },
      { fG4, T20 }, { fD5, T20 },
      { fC5, t13 }, { fB4, t13 }, { fA4, t13 }, { fG5, T20 }, { fD5, T10 },
      { fC5, t13 }, { fB4, t13 }, { fA4, t13 }, { fG5, T20 }, { fD5, T10 },
      { fC5, t13 }, { fB4, t13 }, { fC5, t13 }, { fA4, T20 },
      { fD4, t13 }, { fREST, t13 }, { fD4, t13 },
      { fE4, T15 }, { fE4, t12 },
      { fC5, t14 }, { fB4, t14 }, { fA4, t14 }, { fG4, t14 },
      { fG4, t13 }, { fA4, t13 }, { fB4, t13 },
      { fA4, t13 }, { fREST, t13 }, { fE4, t13 },
      { fFS4, T10 },
      { fD4, t13 }, { fREST, t13 }, { fD4, t13 },
      { fG5, t13 }, { fREST, t13 }, { fF5, t13 },
      { fDS5, t13 }, { fREST, t13 }, { fD5, t13 },
      { fC5, t13 }, { fREST, t13 }, { fAS4, t13 },
      { fA4, t13 }, { fREST, t13 }, { fG4, t13 },
      { fD5, T20 },
      { fD4, t13 }, { fD4, t13 }, { fD4, t13 },
      { fD4, T20 },
      { fREST, T40 }, 
    };
    playTones( 120, melody, ELEMENTS(melody) );
  }

  void playTune_PrestoHaydn() {
    //Serial.println("MusicBox::playTune_PrestoHaydn");
    int melody[][2] = {
      { fB4, t12 }, { fG4, t12 }, { fB4, t12 }, { fG4, t12 }, { fC5, t12 }, { fG4, t12 }, 
      { fD5, t12 }, { fG4, t12 }, { fD5, t12 }, { fG4, t12 }, { fE5, t12 }, { fG4, t12 }, 
      { fG4, t12 }, { fFS4, t12 }, { fE4, t12 }, { fD4, t12 }, { fC5, T10 }, 
      { fC5, T10 }, { fB4, T10 }, { fREST, T10 }, 
      { fB4, t12 }, { fG4, t12 }, { fB4, t12 }, { fG4, t12 }, { fC5, t12 }, { fG4, t12 }, 
      { fD5, t12 }, { fG4, t12 }, { fD5, t12 }, { fG4, t12 }, { fE5, t12 }, { fG4, t12 }, 
      { fD5, T10 }, { fG4, T10 }, { fFS4, T10 }, 
      { fG4, T20 }, { fREST, T10 }, 
      { fREST, T30 },

      { fG2, T20 }, { fA2, T10 }, 
      { fB2, T20 }, { fC3, T10 }, 
      { fD3, T20 }, { fFS3, T10 }, 
      { fG3, T10 }, { fG2, T10 }, { fREST, T10 }, 
      { fG2, T20 }, { fA2, T10 }, 
      { fB2, T20 }, { fC3, T10 }, 
      { fB2, T10 }, { fD3, T10 }, { fD3, T10 }, 
      { fG3, T10 }, { fG2, T10 }, { fREST, T10 }, 
      { fREST, T30 },
    };
    playTones( 100, melody, ELEMENTS(melody) );
  }

    void playTune_PrestoMozart() {
    //Serial.println("MusicBox::playTune_PrestoMozart");
    int melody[][2] = {
      { fF4, T10 }, { fE4, T10 }, { fG4, T10 }, 
      { fG4, T10 }, { fF4, T10 }, { fA4, T10 }, 
      { fA4, T10 }, { fG4, T10 }, { fBF4, T10 }, 
      { fBF4, T10 }, { fA4, T10 }, { fF4, t12 }, { fF5, t12 }, 
      { fE5, T10 }, { fD5, T10 }, { fBF4, T10 }, 
      { fBF4, T10 }, { fA4, T10 }, { fD4, t12 }, { fD5, t12 }, 
      { fC5, T10 }, { fA4, T10 }, { fBF4, T10 }, 
      { fB4, T10 }, { fC5, T10 }, { fBF4, T10 }, 
      { fA4, t12 }, { fC5, t12 }, { fA4, t12 }, { fF4, t12 }, { fG4, t12 }, { fE4, t12 }, 
      { fF4, T20 }, { fREST, T10 }, 
      { fREST, T30 },

      { fA3, t12 }, { fC4, t12 }, { fG3, t12 }, { fC4, t12 }, { fBF3, t12 }, { fC4, t12 }, 
      { fBF3, t12 }, { fC4, t12 }, { fA3, t12 }, { fC4, t12 }, { fF3, t12 }, { fC4, t12 }, 
      { fF3, t12 }, { fC4, t12 }, { fE3, t12 }, { fC4, t12 }, { fG3, t12 }, { fC4, t12 }, 
      { fF3, t12 }, { fC4, t12 }, { fF3, t12 }, { fC4, t12 }, { fD4, T10 }, 
      { fC4, T10 }, { fBF3, T10 }, { fA3, T10 }, 
      { fG3, T10 }, { fF3, T10 }, { fBF3, T10 }, 
      { fA3, T10 }, { fF3, T10 }, { fG3, T10 }, 
      { fGS3, T10 }, { fA3, T10 }, { fE3, T10 }, 
      { fF3, t12 }, { fA3, t12 }, { fC4, T10 }, { fC3, T10 }, 
      { fF3, T10 }, { fF2, T10 }, { fREST, T10 }, 
      { fREST, T30 },
    };
    playTones( 100, melody, ELEMENTS(melody) );
  }

    void playTune_LargoHandel() {
    //Serial.println("MusicBox::playTune_LargoHandel");
    int melody[][2] = {
      { fF4, T10 }, { fF4, T10 }, { fREST, t12 },  { fG4, t12 }, 
      { fE4, T10 }, { fE4, T10 }, { fREST, T10 }, 
      { fA4, T10 }, { fA4, T10 }, { fREST, t12 },  { fBF4, t12 }, 
      { fG4, T10 }, { fG4, T10 }, { fREST, t12 },  { fA4, t12 }, 
      { fBF4, T10 }, { fBF4, T10 }, { fREST, t12 },  { fC5, t12 }, 
      { fA4, T10 }, { fA4, T10 }, { fREST, t12 },  { fA4, t12 }, 
      { fD5, t12 }, { fE5, t12 }, { fF5, T10 }, { fE5, t12 }, { fD5, t12 }, 
      { fD5, T10 }, { fD5, T20 }, 
      { fREST, T30 },

      { fA3, T10 }, { fA3, T10 }, { fREST, T10 }, 
      { fA2, T15 }, { fBF2, t12 }, { fA2, t12 }, { fG2, t12 }, 
      { fF2, T10 }, { fF3, T10 }, { fREST, T10 }, 
      { fC3, T15 }, { fC3, t12 }, { fBF2, t12 }, { fA2, t12 }, 
      { fG2, T10 }, { fG3, T10 }, { fG3, T10 }, 
      { fD3, T10 }, { fD3, T10 }, { fREST, t12 },  { fF3, t12 }, 
      { fG3, T10 }, { fA3, T10 }, { fA2, T10 }, 
      { fA3, T10 }, { fA3, T20 }, 
      { fREST, T30 },
    };
    playTones( 100, melody, ELEMENTS(melody) );
  }

    void playTune_Hatikvuh() {
    //Serial.println("MusicBox::playTune_Hatikvuh");
    int melody[][2] = {
      { fD4, t12 }, { fE4, t12 }, { fF4, t12 }, { fG4, t12 }, 
      { fA4, T10 }, { fA4, T10 }, 
      { fBF4, t12 }, { fA4, t12 }, { fBF4, t12 }, { fD5, t12 }, 
      { fA4, T20 }, 
      { fG4, T10 }, { fG4, T10 }, 
      { fF4, T10 }, { fF4, T10 }, 
      { fE4, t12 }, { fD4, t12 }, { fE4, t12 }, { fF4, t12 }, 
      { fD4, T20 }, 
      { fREST, T20 },

      { fD3, t12 }, { fA3, t12 }, { fA3, t12 }, { fA3, t12 }, 
      { fD3, t12 }, { fA3, t12 }, { fA3, t12 }, { fA3, t12 }, 
      { fD3, t12 }, { fBF3, t12 }, { fBF3, t12 }, { fBF3, t12 }, 
      { fD3, t12 }, { fA3, t12 }, { fA3, t12 }, { fA3, t12 }, 
      { fBF2, t12 }, { fG3, t12 }, { fBF2, t12 }, { fG3, t12 }, 
      { fA2, t12 }, { fF3, t12 }, { fA2, t12 }, { fF3, t12 }, 
      { fA2, T10 }, { fG3, T10 }, 
      { fD3, t12 }, { fA3, t12 }, { fD3, T10 }, 
      { fREST, T20 },
    };
    playTones( 100, melody, ELEMENTS(melody) );
  }


  void playTest_NoteTypes() {
    Serial.println("MusicBox::playTest_NoteTypes");
    int melody[][2] = {
      { fE4, T40 },  // (4.0) Whole note
      { fE4, T35 },  // (3.5) ?
      { fE4, T30 },  // (3.0) Three-quarter
      { fE4, T25 },  // (2.5) ?
      { fE4, T20 },  // (2.0) Half
      { fE4, T15 },  // (1.5)
      { fE4, T10 },  // (1.0) Quarter
      { fE4, t34 },  // (3/4)
      { fE4, t23 },  // (2/3)
      { fE4, t12 },  // (1/2) Eighth
      { fE4, t13 },  // (1/3) Twelfth
      { fE4, t14 },  // (1/4) Sixteenth
      { fE4, t18 },  // (1/8) Thirty-second
      { fREST, T10 },  // (0) Rest

      { fREST, T10 },  // (0) Rest
      { fA3, t18 },  // (1/8) Thirty-second
      { fA3, t14 },  // (1/4) Sixteenth
      { fA3, t13 },  // (1/3) Twelfth
      { fA3, t12 },  // (1/2) Eighth
      { fA3, t23 },  // (2/3)
      { fA3, t34 },  // (3/4)
      { fA3, T10 },  // (1.0) Quarter
      { fA3, T15 },  // (1.5)
      { fA3, T20 },  // (2.0) Half
      { fA3, T25 },  // (2.5) ?
      { fA3, T30 },  // (3.0) Three-quarter
      { fA3, T35 },  // (3.5) ?
      { fA3, T40 },  // (4.0) Whole note

      { fC0, T10 }, { fD0, t14 }, { fE0, t14 }, { fF0, t14 }, { fG0, t14 }, { fA0, t14 }, { fB0, t14 },
      { fC1, T10 }, { fD1, t14 }, { fE1, t14 }, { fF1, t14 }, { fG1, t14 }, { fA1, t14 }, { fB1, t14 },
      { fC2, T10 }, { fD2, t14 }, { fE2, t14 }, { fF2, t14 }, { fG2, t14 }, { fA2, t14 }, { fB2, t14 },
      { fC3, T10 }, { fD3, t14 }, { fE3, t14 }, { fF3, t14 }, { fG3, t14 }, { fA3, t14 }, { fB3, t14 },
      { fC4, T10 }, { fD4, t14 }, { fE4, t14 }, { fF4, t14 }, { fG4, t14 }, { fA4, t14 }, { fB4, t14 },
      { fC5, T10 }, { fD5, t14 }, { fE5, t14 }, { fF5, t14 }, { fG5, t14 }, { fA5, t14 }, { fB5, t14 },
      { fC6, T10 }, { fD6, t14 }, { fE6, t14 }, { fF6, t14 }, { fG6, t14 }, { fA6, t14 }, { fB6, t14 },
      { fC7, T10 }, { fD7, t14 }, { fE7, t14 }, { fF7, t14 }, { fG7, t14 }, { fA7, t14 }, { fB7, t14 },
      { fC8, T10 }, { fD8, t14 }, { fE8, t14 }, { fF8, t14 }, { fG8, t14 }, { fA8, t14 }, { fB8, t14 },

      { fREST, T40 }, 
    };
    playTones( 100, melody, ELEMENTS(melody) );
  }

};

#endif
