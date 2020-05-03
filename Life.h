#ifndef LIFEMODULE_H
#define LIFEMODULE_H

#include "Module.h"

#define LIFETIME 1000  // msec/generation
#define LIFESIZE 10    // 3=80, 4=60, 5=48, 6=40, 8=30, 10=24, 13=18
#define WORLDMAX 24    // 240/LIFESIZE

/**
 * The Game of Life
 */
class Life: public Module 
{
public:
  Life() {}   // use moduleSetup() for activate
  ~Life() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup() 
  {
    Serial.println("Life::moduleSetup()");
    tft.enableDisplay(true);
    tft.fillScreen(ST77XX_BLACK);
    analogWrite(TFT_BACKLIGHT, 222);

    worldX = floor(tft.width()/cellSize);
    worldY = floor(tft.height()/cellSize);
    cellColor1 = ST77XX_GREEN;
    cellColor2 = ST77XX_BLUE;
  }
  
  virtual void moduleTeardown() 
  {
    Serial.println("Life::moduleTeardown()");
    analogWrite(TFT_BACKLIGHT, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.enableDisplay(false); 

    CircuitPlayground.clearPixels();
  }
  
  virtual void moduleReset() 
  {
    Serial.println("Life::moduleReset()");
    regenerate();
  }

  virtual void leftButton() 
  {
    Serial.println("Life::leftButton()");
    rotatecolors();
    moduleReset();
  }

  virtual void rightButton() 
  {
    Serial.println("Life::rightButton()");
    moduleReset();
  }

  virtual unsigned long getModuleDelay() {
    return LIFETIME;    
  }
  
  virtual void loop() 
  {
    //Serial.print("Life::loop - "); Serial.println(millis());
    evolution();
    generation();
    neopixels();
  }

private:
  uint8_t cellSize = LIFESIZE;
  int world[WORLDMAX][WORLDMAX][3];   // [3]=[curstate][curstate-1][curstate-2]
  int worldX, worldY;

  unsigned long generations = 0;
  float regenerate_density = 20; // if (random(100) < regenerate_density)
  
  uint16_t cellColor1, cellColor2;
  int color_state = 0;
  bool redraw = false;

  /*
   * true if generation[0] == generation[2]
   */
  bool done()
  {
    for (int x = 0; x < worldX; x=x+1) {
      for (int y = 0; y < worldY; y=y+1) {
        if (world[x][y][0] != world[x][y][2])
          { return false; }
      }
    }
    return true;
  }
  
  /*
   * set all cells off
   */
  void clearall()
  {
    generations = 0;
    for (int x = 0; x < WORLDMAX; x=x+1) {
      for (int y = 0; y < WORLDMAX; y=y+1) {
          world[x][y][0] = world[x][y][1] = world[x][y][2] = 0;
      }
    }
  }
  
  /*
   * set random cells on
   */
  void regenerate()
  {
//Serial.println("Life::regenerate()");
    clearall();
    for (int x = 0; x < worldX; x=x+1) {
      for (int y = 0; y < worldY; y=y+1) {
        if (random(100) < regenerate_density)
          { world[x][y][0] = 1; }
      }
    }
    evolution();
    redraw = true;
  }
  
  /*
   * Draw current generation
   */
  void generation()
  {
//Serial.println("Life::generation()");

    uint16_t cellColor = ST77XX_BLACK;
    for (int y = 0; y < worldY; y=y+1) {
      for (int x = 0; x < worldX; x=x+1) {
        int cellX = floor(x * cellSize); // + floor(cellSize / 2);  // rect vs circle
        int cellY = floor(y * cellSize); // + floor(cellSize / 2);
  
        if (world[x][y][0] == 0) {
          cellColor = ST77XX_BLACK;
        } else if (world[x][y][1] == 0) {
          cellColor = cellColor1;
        } else {
          cellColor = cellColor2;
        }
        if (redraw || world[x][y][0] != world[x][y][1] || world[x][y][1] != world[x][y][2]) {
          tft.fillRoundRect(cellX, cellY, cellSize, cellSize, floor(cellSize/2), cellColor);
        }
      }
    }
    redraw = false;
  }
  
  /*
   * Advance to next generation
   */
  void evolution()
  {
    // update cycle
    for (int x = 0; x < worldX; x=x+1) {
        for (int y = 0; y < worldY; y=y+1) {
          world[x][y][2] = world[x][y][1];
          world[x][y][1] = world[x][y][0];
        }
    }
  
    // birth and death cycle
    for (int x = 0; x < worldX; x=x+1) {
      for (int y = 0; y < worldY; y=y+1) {
        int count = neighbors(x, y);
        if (count == 3 && world[x][y][1] == 0) {
          world[x][y][0] = 1;
        }
        else if ((count < 2 || 3 < count) && world[x][y][1] == 1) {
          world[x][y][0] = 0;
        }
      }
    }
    generations++;
  
    if (generations % 30 == 0) { Serial.print("Life::generations - "); Serial.println(generations); }
    if (generations == 512 || done()) {
      Serial.print("Life::generations - "); Serial.print(generations); Serial.println(" - done");
      regenerate();
    }
  }
  
  /*
   * Count the number of adjacent cells 'on'
   */
  int neighbors(int x0, int y0)
  {
    int x1 = x0;                         int y1 = (y0 + worldY - 1) % worldY;
    int x2 = (x0 + 1) % worldX;          int y2 = (y0 + worldY - 1) % worldY;
    int x3 = (x0 + 1) % worldX;          int y3 = y0;
    int x4 = (x0 + 1) % worldX;          int y4 = (y0 + 1) % worldY;
    int x5 = x0;                         int y5 = (y0 + 1) % worldY;
    int x6 = (x0 + worldX - 1) % worldX; int y6 = (y0 + 1) % worldY;
    int x7 = (x0 + worldX - 1) % worldX; int y7 = y0;
    int x8 = (x0 + worldX - 1) % worldX; int y8 = (y0 + worldY - 1) % worldY;
  
    int result = world[x1][y1][1] +
                 world[x2][y2][1] +
                 world[x3][y3][1] +
                 world[x4][y4][1] +
                 world[x5][y5][1] +
                 world[x6][y6][1] +
                 world[x7][y7][1] +
                 world[x8][y8][1];  
//Serial.print("Life::neighbors("); Serial.print(x0); Serial.print(","); Serial.print(y0); Serial.print(") - ");  Serial.println(result);
      return result;
  }
  
  /*
   * Set cell colors
   */
  void rotatecolors()
  {
    // white
    if (color_state == 0) { 
      cellColor2 = ST77XX_WHITE; 
      cellColor1 = ST77XX_WHITE; 
    }
    // random color from 1/3 of colorwheel + complement
    if (color_state == 1 || color_state == 2 || color_state == 3) {  
      int c2 = int(random(1,85) + (color_state*85)) % 256;
      int c1 = int(c2 + 128) % 256;
      c2 = CircuitPlayground.colorWheel(c2);
      c1 = CircuitPlayground.colorWheel(c1);

      char c2_hex[7] = {0};
      sprintf(c2_hex,"%02X",c2);
      cellColor2 = RGB888toRGB565( c2_hex );

      char c1_hex[7] = {0};
      sprintf(c1_hex,"%02X",c1);
      cellColor1 = RGB888toRGB565( c1_hex );
    }
    // 2 random colors
    if (color_state == 4) {  
      int c2 = CircuitPlayground.colorWheel(random(256));
      int c1 = CircuitPlayground.colorWheel(random(256));

      char c2_hex[7] = {0};
      sprintf(c2_hex,"%02X",c2);
      cellColor2 = RGB888toRGB565( c2_hex );

      char c1_hex[7] = {0};
      sprintf(c1_hex,"%02X",c1);
      cellColor1 = RGB888toRGB565( c1_hex );
    }
  
  /*
    // basic colors + complements
    if (color_state == 4)  { cellColor2 = RGB888toRGB565("FF0000"); cellColor1 = RGB888toRGB565("00FFFF"); }
    if (color_state == 5)  { cellColor2 = RGB888toRGB565("FF8000"); cellColor1 = RGB888toRGB565("007FFF"); }
    if (color_state == 6)  { cellColor2 = RGB888toRGB565("FFFF00"); cellColor1 = RGB888toRGB565("0000FF"); }
    if (color_state == 7)  { cellColor2 = RGB888toRGB565("80FF00"); cellColor1 = RGB888toRGB565("7F00FF"); }
    if (color_state == 8)  { cellColor2 = RGB888toRGB565("00FF00"); cellColor1 = RGB888toRGB565("FF00FF"); }
    if (color_state == 9)  { cellColor2 = RGB888toRGB565("00FF80"); cellColor1 = RGB888toRGB565("FF007F"); }
    if (color_state == 10) { cellColor2 = RGB888toRGB565("00FFFF"); cellColor1 = RGB888toRGB565("FF0000"); }
    if (color_state == 11) { cellColor2 = RGB888toRGB565("0080FF"); cellColor1 = RGB888toRGB565("FF7F00"); }
    if (color_state == 12) { cellColor2 = RGB888toRGB565("0000FF"); cellColor1 = RGB888toRGB565("FFFF00"); }
  */
    color_state = (color_state+1) % 5;
    Serial.print("Life::color_state - "); Serial.println(color_state);
  }

  /*
   * map binary generations value to neopixel 0-10
   */
  void neopixels()
  {    
    String bin = String(generations,BIN);
    int bin_len = bin.length();
//Serial.print("Life::neopixels() - bin - "); Serial.println(bin);

    // lights off
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.strip.setPixelColor(i, 0);
    }
    // update
    if (color_state != 1) {
      for (int i = 0; i < 10 && i < bin_len; i++) {
        char val = bin.charAt(bin_len-1-i);
        if (val == '0') { continue; }
        
        uint32_t c32 = CircuitPlayground.colorWheel(map(i,0,9,220,30));
        CircuitPlayground.strip.setPixelColor(9-i, c32);
      }
    }
    // lights on
    CircuitPlayground.strip.show();
  }

};

#endif
