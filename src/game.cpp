#include "game.h"
#include "player.h"
#include "entities.h"
#include "map.h"

uint16_t Game::cameraX;
uint16_t Game::cameraY;

//gameplay initialization, sets us up for the actual run and gun
void Game::init() {

  Player::init();   //set up all the values
  Entities::init(); //set up entities
  Map::init();
}

//run and gun game loop.
void Game::runAndGun() {

  (*Player::stepRoutine)();

  if ((Player::pos.x>>8) > cameraX+(SCREEN_WIDTH-CAMERA_RIGHT_BUFFER)) {
    cameraX = (Player::pos.x>>8)-(SCREEN_WIDTH-CAMERA_RIGHT_BUFFER);
    cameraX = min(cameraX, (Map::width*TILE_SIZE)-SCREEN_WIDTH);
  }
  else if (((Player::pos.x>>8) < cameraX+CAMERA_LEFT_BUFFER) && (Player::pos.x>>8 > CAMERA_LEFT_BUFFER)) {
    cameraX = (Player::pos.x>>8)-CAMERA_LEFT_BUFFER;
    // cameraX = max(cameraX,0);
  }

  Map::draw();

  (*Player::drawRoutine)();

  Entities::step();
}

//death
  //show score
  //try again?

//contact details