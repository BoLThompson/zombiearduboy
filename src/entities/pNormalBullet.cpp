#include "pNormalBullet.h"
#include "entities.h"
#include "game.h"

void pNormalBulletStep(uint8_t index) {
  PNormalBullet *me = (PNormalBullet *) entities[index]; //FIXME this seems dangerous

  ab.fillRect(me->pos.x-Game::cameraX, me->pos.y-Game::cameraY, 3, 3, WHITE);
  
  if ((me->dir&LEFT) != 0) {
    me->pos.x-=5;
  }
  else if ((me->dir&RIGHT) != 0) {
    me->pos.x+=5;
  }

  if ((me->dir&UP) != 0) {
    me->pos.y-=5;
  }
  else if ((me->dir&DOWN) != 0) {
    me->pos.y+=5;
  }

  if ((me->pos.x > Game::cameraX+SCREEN_WIDTH) 
  || (me->pos.x < Game::cameraX)
  || (me->pos.y < Game::cameraY)
  || (me->pos.y > Game::cameraY+SCREEN_HEIGHT)) {
    entities[index] = NULL;
    delete me;
  }
}