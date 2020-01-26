#include "player.h"

//player initialization
void Player::init() {
  x = (FIELD_WIDTH/8)<<8;
  y = ((FIELD_HEIGHT/3)*2)<<8;
  stepRoutine = &Player::idle;
  faceRight = true;
}

void Player::step() {
  (this->*stepRoutine)();
}

void Player::idle() {

  //walking and moonwalking
  
  //if holding Left
  if (ab.buttonsState() & LEFT_BUTTON) {

    //at least move half a pixel
    x-=_BV(7);

    //if we're not shooting,
    if (!(ab.buttonsState() & B_BUTTON)) {

      //turn to the left
      faceRight = false;

      //move an additional half pixel
      x-=_BV(7);
    }
    //if we are shooting, only move the extra half pixel if we're facing the right way
    else if (!faceRight) x-=_BV(7);

  }

  //and all that again for the right
  if (ab.buttonsState() & RIGHT_BUTTON) {
    x+=_BV(7);
    if (!(ab.buttonsState() & B_BUTTON)) {
      faceRight = true;
      x+=_BV(7);
    }
    else if (faceRight) x+=_BV(7);
  }
  
}

void Player::draw() {
  uint8_t dispX = x>>8;
  uint8_t dispY = y>>8;
  ab.fillRect(dispX-PLAYER_WIDTH/2+1,dispY-PLAYER_HEIGHT/2+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-PLAYER_WIDTH/2, dispY-PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
  ab.drawRect(dispX-(faceRight==true ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3), GUN_WIDTH, GUN_HEIGHT, WHITE);
}