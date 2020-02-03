#include "game.h"
#include "player.h"
#include "entities.h"
#include "map.h"

//gameplay initialization, sets us up for the actual run and gun
void Game::init() {

  Player::init();   //set up all the values
  Entities::init(); //set up entities
  Map::init();
}

//run and gun game loop.
void Game::runAndGun() {

  Map::draw();
  (*Player::stepRoutine)();
  Entities::step();
}

//death
  //show score
  //try again?

//contact details