#include "player.h"
#include "entities.h"

Pos Player::pos;
Speed Player::speed;
bool Player::faceRight;
uint8_t Player::fireTimer;
void (*Player::fireRoutine)();
void (*Player::stepRoutine)();

//player initialization
void Player::init() {
  pos.x = (FIELD_WIDTH/8)<<8;
  pos.y = TEMP_GROUND<<8;
  stepRoutine = &Player::idleStep;
  fireRoutine = &Player::fireNormal;
  fireTimer = 0;
  faceRight = true;
}

void Player::idleStep() {

  //walking and moonwalking
  
  //if holding Left
  if (ab.pressed(LEFT_BUTTON)) {

    //at least move half a pixel
    pos.x-=_BV(7);

    //if we're not shooting,
    if (!ab.pressed(FIRE_BUTTON)) {

      //turn to the left
      faceRight = false;

      //move an additional half pixel
      pos.x-=_BV(7);
    }
    //if we are shooting, only move the extra half pixel if we're facing the right way
    else if (!faceRight) pos.x-=_BV(7);

  }

  //and all that again for the right
  if (ab.pressed(RIGHT_BUTTON)) {
    pos.x+=_BV(7);
    if (!ab.pressed(FIRE_BUTTON)) {
      faceRight = true;
      pos.x+=_BV(7);
    }
    else if (faceRight) pos.x+=_BV(7);
  }

  //shoot maybe?
  shootAction();

  //possibly jump
  jumpAction();

  draw();
}

void Player::jumpStep() {
  pos.y+= speed.v;
  speed.v = min(speed.v+64,5<<8);

  pos.x+= speed.h;

  if (ab.pressed(RIGHT_BUTTON)) faceRight = true;
  else if (ab.pressed(LEFT_BUTTON)) faceRight = false;

  if (pos.y >= TEMP_GROUND<<8) {
    pos.y = TEMP_GROUND<<8;
    stepRoutine = &Player::idleStep;
  }

  shootAction();

  draw();
}

void Player::shootAction() {
  if (fireTimer > 0) {
    fireTimer --;
    return;
  }

  if (ab.pressed(FIRE_BUTTON)) {
    (*fireRoutine)();
  }
}

void Player::jumpAction() {
  if (ab.justPressed(JUMP_BUTTON)) {
    stepRoutine = &Player::jumpStep;
    speed.v = -3*(_BV(8));
    if (ab.pressed(RIGHT_BUTTON)) {
      speed.h = _BV(8);
    }
    else if (ab.pressed(LEFT_BUTTON)) {
      speed.h = _BV(8)*-1;
    }
    else speed.h=0;
  }
}

void Player::fireNormal() {
  fireTimer = 5;

  Pos bulletPos;
  bulletPos.x = (pos.x>>8) + 5 * (faceRight ? 1 : -1);
  bulletPos.y = (pos.y>>8) - 7;

  Entities::createPNormalBullet(bulletPos, faceRight ? RIGHT : LEFT);
}

void Player::draw() {
  uint16_t dispX = pos.x>>8;
  uint16_t dispY = pos.y>>8;
  ab.fillRect(dispX-PLAYER_WIDTH/2+1,dispY-PLAYER_HEIGHT+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-PLAYER_WIDTH/2, dispY-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
  ab.drawRect(dispX-(faceRight==true ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3)*2, GUN_WIDTH, GUN_HEIGHT, WHITE);
}