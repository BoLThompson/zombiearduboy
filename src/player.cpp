#include "player.h"
#include "entities.h"
#include "game.h"
#include "map.h"

Pos Player::pos;
Speed Player::speed;
bool Player::faceRight;
uint8_t Player::fireTimer;
void (*Player::fireRoutine)();
void (*Player::stepRoutine)();
void (*Player::drawRoutine)();
Direction Player::aim;

namespace {
  const Box normalBox = {
    (PLAYER_WIDTH>>1), (PLAYER_HEIGHT),
    PLAYER_WIDTH, PLAYER_HEIGHT
  };
};

//player initialization
void Player::init() {
  pos.x = (SCREEN_WIDTH/8)<<8;
  pos.y = 0;
  stepRoutine = &Player::jumpStep;
  fireRoutine = &Player::fireNormal;
  fireTimer = 0;
  faceRight = true;
  aim = RIGHT;
}

void Player::idleStep() {

  speed.v = 0;

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

    if (Map::collide((pos.x>>8), pos.y>>8, normalBox)) { //if that put us into a wall, back out one pixel
      pos.x+=_BV(8);
    }
  }

  //and all that again for the right
  if (ab.pressed(RIGHT_BUTTON)) {
    pos.x+=_BV(7);
    if (!ab.pressed(FIRE_BUTTON)) {
      faceRight = true;
      pos.x+=_BV(7);
    }
    else if (faceRight) pos.x+=_BV(7);
    if (Map::collide((pos.x>>8), pos.y>>8, normalBox)) {
      pos.x-=_BV(8);
    }
  }

  //shoot maybe?
  shootAction();

  //possibly jump
  jumpAction();

  drawRoutine = draw;

  if (!Map::collide(pos.x>>8,(pos.y>>8)+1,normalBox)) {
    stepRoutine = &Player::jumpStep;
    if (ab.pressed(RIGHT_BUTTON)) {
      speed.h = _BV(8);
    }
    else if (ab.pressed(LEFT_BUTTON)) {
      speed.h = _BV(8)*-1;
    }
  }
}

void Player::jumpStep() {
  pos.y+= speed.v;

  if (speed.h != 0) {
    if (!Map::collide((pos.x+speed.h)>>8,pos.y>>8,normalBox))
      pos.x+= speed.h;
  }

  if (ab.pressed(RIGHT_BUTTON)) faceRight = true;
  else if (ab.pressed(LEFT_BUTTON)) faceRight = false;

  if (Map::collide(pos.x>>8,pos.y>>8,normalBox)) {
    pos.y = (((pos.y>>8)/TILE_SIZE)*TILE_SIZE)<<8;
    stepRoutine = &Player::idleStep;
  }

  speed.v = min(speed.v+64,5<<8);

  shootAction();

  drawRoutine = draw;
}

void Player::shootAction() {
  
  if (!ab.pressed(FIRE_BUTTON)) {
    uint8_t newAim = ab.buttonsState();

    newAim &= ~(A_BUTTON | B_BUTTON);

    if (newAim != 0) aim = (Direction) newAim;
    else aim = faceRight? RIGHT : LEFT;
  }

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

  Entities::createPNormalBullet(bulletPos, (Direction) aim);
}

void Player::draw() {
  uint16_t dispX = (pos.x>>8)-Game::cameraX;
  uint16_t dispY = (pos.y>>8)-Game::cameraY;
  ab.fillRect(dispX-(PLAYER_WIDTH>>1)+1,dispY-PLAYER_HEIGHT+1, PLAYER_WIDTH-1, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-(PLAYER_WIDTH>>1), dispY-PLAYER_HEIGHT, PLAYER_WIDTH+1, PLAYER_HEIGHT, WHITE);
  ab.drawRect(dispX-(faceRight==true ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3)*2, GUN_WIDTH, GUN_HEIGHT, WHITE);
}