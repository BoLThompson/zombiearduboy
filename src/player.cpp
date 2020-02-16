#include "player.h"
#include "entities.h"
#include "game.h"
#include "map.h"
#include "assets.h"

Pos Player::pos;
Speed Player::speed;
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
  const Box floorBox = {
    (PLAYER_WIDTH>>1), 0,
    PLAYER_WIDTH, 1
  };
};

//player initialization
void Player::init() {
  pos.x = (SCREEN_WIDTH/8);
  pos.y = 0;
  stepRoutine = &Player::jumpStep;
  fireRoutine = &Player::fireNormal;
  fireTimer = 0;
  aim = RIGHT;
}

void Player::idleStep() {

  speed.v = 0;

  //walking and moonwalking

  //shoot maybe?
  shootAction();

  if ((ab.pressed(LEFT_BUTTON))
  and ((aim & LEFT_BUTTON) || (ab.everyXFrames(3)))
  and (!Map::collide(pos.x-1, pos.y>>8, normalBox)))
    pos.x-=1;

  else if ((ab.pressed(RIGHT_BUTTON))
  and ((aim & RIGHT_BUTTON) || (ab.everyXFrames(3)))
  and (!Map::collide(pos.x+1, pos.y>>8, normalBox)))
    pos.x+=1;

  //possibly jump
  jumpAction();

  drawRoutine = draw;

  if (!Map::collide(pos.x,(pos.y>>8),floorBox)) { //ground detection
    stepRoutine = &Player::jumpStep;
    if (ab.pressed(RIGHT_BUTTON)) {
      speed.h = 1;
    }
    else if (ab.pressed(LEFT_BUTTON)) {
      speed.h = -1;
    }
  }
}

void Player::jumpStep() {
  pos.y+= speed.v;

  if (speed.h != 0) {
    if (!Map::collide((pos.x+speed.h),pos.y>>8,normalBox))
      pos.x+= speed.h;
  }

  // if (ab.pressed(RIGHT_BUTTON)) faceRight = true;
  // else if (ab.pressed(LEFT_BUTTON)) faceRight = false;

  //detect ground
  if ((Map::collide(pos.x,(pos.y>>8),floorBox))
  and (speed.v > 0)) {
    pos.y = pos.y>>8; //don't care about subpixels
    pos.y = pos.y/TILE_SIZE; //tile position
    pos.y = pos.y*TILE_SIZE; //position of that tile
    pos.y = pos.y<<8;
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
    // else aim = faceRight? RIGHT : LEFT;
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
      speed.h = 1;
    }
    else if (ab.pressed(LEFT_BUTTON)) {
      speed.h = -1;
    }
    else speed.h=0;
  }
}

void Player::fireNormal() {
  fireTimer = 5;

  Pos bulletPos;
  bulletPos.x = (pos.x); //+ 5 * (faceRight ? 1 : -1);
  bulletPos.y = (pos.y>>8) - 7;

  Entities::createPNormalBullet(bulletPos, (Direction) aim);
}

void Player::draw() {
  uint16_t dispX = (pos.x)-Game::cameraX;
  uint16_t dispY = (pos.y>>8)-Game::cameraY;
  // ab.fillRect(dispX-(PLAYER_WIDTH>>1)+1,dispY-PLAYER_HEIGHT+1, PLAYER_WIDTH-1, PLAYER_HEIGHT-2, BLACK);
  // ab.drawRect(dispX-(PLAYER_WIDTH>>1), dispY-PLAYER_HEIGHT, PLAYER_WIDTH+1, PLAYER_HEIGHT, WHITE);
  // ab.drawRect(dispX-(aim & RIGHT_BUTTON ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3)*2, GUN_WIDTH, GUN_HEIGHT, WHITE);
  ab.drawBitmap(dispX-5, dispY-24, player_sprite+2, pgm_read_byte(player_sprite), pgm_read_byte(player_sprite+1), WHITE);
  // sprites.drawBitmap()
}