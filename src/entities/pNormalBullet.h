#ifndef PNORMALBULLET_H
#define PNORMALBULLET_H
#include "global.h"
#include "entities.h"

struct PNormalBullet: public Entity {
  Pos pos;
  Direction dir;
};

void pNormalBulletStep(uint8_t index);

#endif