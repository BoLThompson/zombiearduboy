#include <Arduino.h>
#include <Arduboy2.h>

#include "game.h"
#include "global.h"

// director d;

void setup() {

  //arduboy stuff
  ab.setFrameRate(FPS); //framerate to global def
  ab.boot();            //init that shit
  ab.clear();           //clear the screen of any dumb crap that was there before

  Game::init();  
}

void loop() {
  if (!ab.nextFrame()) return;

  ab.clear();

  ab.pollButtons();
  Game::loop();

  ab.display();
}