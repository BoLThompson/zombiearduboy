#ifndef ENTITIES_H
#define ENTITIES_H

#include "global.h"

//entities is an array of pointers to objects

//player wants to create a bullet
//player calls entities::createBullet(Pos pos, uint8_t aim)
  //calls firstAvailable to find an empty slot
  //exit if NULL
  //creates an instance of class Bullet with the required parameters

//this seems pretty good?

//in order for entities to point to "some object", I think all of those objects need to inherit from an entities class

struct Entity {
};

#endif