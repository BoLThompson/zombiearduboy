#include "game.h"
#include "player.h"

extern Player player;

//title screen
  // maybe a difficulty toggle
  // sound toggle?
  // button layout

//game initialization
void Game::init() {

  //instantiate the player
  player.init();
}

//game loop
void Game::loop() {

  //do player shit
  player.step();

  //do enemy shit

  
  player.draw();
}

//death
  //show score
  //try again?

//contact details