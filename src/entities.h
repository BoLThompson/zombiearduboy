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



//so when Game::runAndGun calls entities::step() {
//for each element i of entities
  //continue if i is null
  //execute i.fncptr(i)

struct Entity {
  void (*funcptr)(&Entity me);  //a pointer to a public goddamned function being run by the global instance with a pointer to the entity that it's operating on
};

#endif