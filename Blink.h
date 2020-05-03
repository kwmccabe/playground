#ifndef BLINKMODULE_H
#define BLINKMODULE_H

#include "Module.h"
#define BLINK_PIN 13

/**
 * Blink is a minimal implementation of class Module
 * 
 * moduleSetup()    : default 3 blinks per cycle
 * moduleTeardown() : turn-off LED
 * moduleReset()    : reset 1 blink per cycle
 * leftButton()    : cycle 1-10 blinks
 * rightButton()     : ?
 * getModuleDelay() : 300ms between blinks ; 2s between cycles
 * loop()           : blink_state=on/off ; blink_count=cycle
 */
class Blink: public Module 
{
public:
  Blink() {}   // use moduleSetup() for activate
  ~Blink() {}  // use moduleTeardown() for deactivate

  virtual void moduleSetup() 
  {
    Serial.println("Blink::moduleSetup()");
    blink_mode  = 2;
    blink_state = 0;
    blink_count = 0;
  }

  virtual void moduleTeardown() 
  {
    Serial.println("Blink::moduleTeardown()");
    digitalWrite(BLINK_PIN, LOW);
  }
  
  virtual void moduleReset() 
  {
    blink_mode  = 0;
    blink_count = 0;
    Serial.println("Blink::moduleReset()");
  }

  virtual void rightButton() 
  {
    blink_mode = (blink_mode+1) % 10;
    blink_count = 0;
    Serial.print("Blink::rightButton() - "); Serial.println(blink_mode);
  }

  virtual void leftButton() 
  {
    Serial.println("Blink::leftButton()");
  }

  virtual unsigned long getModuleDelay() {
    unsigned long r = 300;
    if (blink_count == 0 && blink_state == 1) { r = 2000; }
    return r;    
  }

  virtual void loop() 
  {
    //Serial.print("Blink::loop() - "); Serial.println(millis());
    if (blink_state == 0) { 
      digitalWrite(BLINK_PIN, LOW); 
    }
    if (blink_state == 1) { 
      digitalWrite(BLINK_PIN, HIGH); 
      blink_count = (blink_count+1) % (blink_mode+1);
    }
    blink_state = (blink_state+1) % 2;
  }

private:
  int blink_mode;
  int blink_state;
  int blink_count;
};

#endif
