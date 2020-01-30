#include "game.h"
#include "player.h"
#include "entities.h"

//gameplay initialization, sets us up for the actual run and gun
void Game::init() {

  Player::init();   //set up all the values
  Entities::init(); //set up entities
}

//run and gun game loop.
void Game::loop() {   //TODO rename to something more descriptive

  (*Player::stepRoutine)();
  Entities::step();
}

//death
  //show score
  //try again?

//contact details