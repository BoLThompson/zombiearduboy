#include "player.h"

//player initialization
void Player::init() {
  x = FIELD_WIDTH/2;
  y = FIELD_HEIGHT/2;
  dir = SOUTH;
  stepRoutine = &Player::idle;
}

void Player::step() {
  (this->*stepRoutine)();
}

void Player::idle() {
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
  ab.fillRect(x-PLAYER_WIDTH/2+1,y-PLAYER_HEIGHT/2+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(x-PLAYER_WIDTH/2, y-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
}