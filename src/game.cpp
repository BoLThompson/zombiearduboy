#include "game.h"
#include "player.h"

//gameplay initialization, sets us up for the actual run and gun
void Game::init() {

  Player::init();   //set up all the values
}

//run and gun game loop.
void Game::loop() {   //TODO rename to something more descriptive

  (*Player::stepRoutine)();
  Player::bullets.step();

  Player::draw();
}

//death
  //show score
  //try again?

//contact details