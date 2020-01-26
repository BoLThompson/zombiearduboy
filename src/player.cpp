#include "player.h"

//player initialization
void Player::init() {
  x = (FIELD_WIDTH/2)<<8;
  y = (FIELD_HEIGHT/2)<<8;
  dir = SOUTH;
  stepRoutine = &Player::idle;
}

void Player::step() {
  (this->*stepRoutine)();
}

void Player::idle() {

  //button state of only dirkeys
  uint8_t dirkeys = ab.buttonsState() & ~(A_BUTTON+B_BUTTON);

  //match the player's direction to the arrow keys
  dir = dirkeys;

  //additional walking speed if the player is walking cardinally
  uint8_t fineSpeed = 102;
  
  //remove the additional walking speed if the player is holding more than one directional key
  if ((dirkeys & (dirkeys-1)) != 0) fineSpeed=0;
  
  if (dirkeys & LEFT_BUTTON) {
    x-=(1<<8)+fineSpeed;
  }
  if (dirkeys & RIGHT_BUTTON) {
    x+=(1<<8)+fineSpeed;
  }
  if (dirkeys & UP_BUTTON) {
    y-=(1<<8)+fineSpeed;
  }
  if (dirkeys & DOWN_BUTTON) {
    y+=(1<<8)+fineSpeed;
  }
}

void Player::draw() {
  uint8_t dispX = x>>8;
  uint8_t dispY = y>>8;
  ab.fillRect(dispX-PLAYER_WIDTH/2+1,dispY-PLAYER_HEIGHT/2+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-PLAYER_WIDTH/2, dispY-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
}