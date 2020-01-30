#include "entities.h"
#include "entities/pNormalBullet.h"

struct Entity *entities[ENTITY_MAX];

void Entities::init() {

  for (uint8_t i = 0; i < ENTITY_MAX; i++) {  //for all entity slots
    entities[i] = NULL;                       //set that shit to null, we got no entities
  }
}

void Entities::step() {
  for (uint8_t i = 0; i < ENTITY_MAX; i++) {
    if (entities[i] != NULL) (*entities[i]->funcptr)(i);
  }
}

void Entities::createPNormalBullet(Pos pos, Direction dir) {
  uint8_t firstAvailable = 0;
  while (entities[firstAvailable] != NULL) {
    firstAvailable++;
    if (firstAvailable == ENTITY_MAX) return;  //give up if there's no room
}                                             //firstAvailable is now an empty entity slot

  PNormalBullet *child = new PNormalBullet;

  child->pos = pos;
  child->dir = dir;
  child->funcptr = pNormalBulletStep;

  entities[firstAvailable] = child;
}