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

  if (!ab.nextFrame()) return;  //wait for next frame
  ab.clear();                   //blank the screen
  ab.pollButtons();             //hur durr

  Game::loop();                 //TODO replace this with a pointer, since the game loop will change depending on stuff
  ab.display();                 //make the screen happen
}