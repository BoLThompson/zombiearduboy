#include "game.h"

Player player;

//title screen
  //maybe a difficulty toggle
  //sound toggle?
  //button layout

//game initialization
void Game::init() {

  //instantiate the director
  // d.init();
  // d.begin();

  //instantiate the player
  player.init();
}

//game loop
void Game::loop() {
  //do player shit
  player.step();
  player.draw();
  //do enemy shit
}

//director
  //difficulty +
    //wave
      //certain amount of difficulty points are allotted for enemies to be spawned
      //enemy groups are selected
      //enemy group spawns are consumed as possible
      //enemy group spawns are fully consumed and all enemies are defeated

//death
  //show score
  //try again?

//contact details




//player initialization
void Player::init() {
  x = FIELD_WIDTH/2;
  y = FIELD_HEIGHT/2;
  dir = SOUTH;
}

void Player::step() {
  if (ab.pressed(LEFT_BUTTON)) {
    x--;
  }
  if (ab.pressed(RIGHT_BUTTON)) {
    x++;
  }
  if (ab.pressed(UP_BUTTON)) {
    y--;
  }
  if (ab.pressed(DOWN_BUTTON)) {
    y++;
  }
}

void Player::draw() {
  ab.drawRect(x-PLAYER_WIDTH/2, y-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
}