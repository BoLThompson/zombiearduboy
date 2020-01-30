#include "pNormalBullet.h"
#include "entities.h"

void pNormalBulletStep(uint8_t index) {
  PNormalBullet *me = (PNormalBullet *) entities[index]; //FIXME this seems dangerous

  ab.fillRect(me->pos.x, me->pos.y, 3, 3, WHITE);
  
  if (me->dir == LEFT) {
    me->pos.x-=5;
  }
  else if (me->dir == RIGHT) {
    me->pos.x+=5;
  }

  if ((me->pos.x > 128) || (me->pos.x < 0)) {
    entities[index] = NULL;
    delete me;
  }
}