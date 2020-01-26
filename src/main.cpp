#include <Arduino.h>
#include <Arduboy2.h>
#include "game.h"
#include "global.h"

Game game;
// director d;

void setup() {
  ab.setFrameRate(FPS);
  ab.boot();
  ab.clear();

  game.init();
}

void loop() {
  if (!ab.nextFrame()) return;

  ab.clear();

  ab.pollButtons();
  game.loop();

  ab.display();
}