#include "pNormalBullet.h"
#include "entities.h"
#include "game.h"

void pNormalBulletStep(uint8_t index) {
  PNormalBullet *me = (PNormalBullet *) entities[index]; //FIXME this seems dangerous

  ab.fillRect(me->pos.x-Game::cameraX, me->pos.y-Game::cameraY, 3, 3, WHITE);
  
  if (me->dir == LEFT) {
    me->pos.x-=5;
  }
  else if (me->dir == RIGHT) {
    me->pos.x+=5;
  }

  if ((me->pos.x > Game::cameraX+SCREEN_WIDTH) || (me->pos.x < Game::cameraX)) {
    entities[index] = NULL;
    delete me;
  }
}