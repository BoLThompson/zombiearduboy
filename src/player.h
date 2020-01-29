#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"

class BulletList {
  private:
  public:
    struct Bullet *head = NULL, *tail = NULL;
    struct Bullet * getHead();
    struct Bullet * getTail();
    struct Bullet * append();
    // struct Bullet * insert();
    // struct Bullet * insert(uint8_t index);
    void step();
    void draw();
};

struct Bullet {
  struct Bullet *next;
  uint32_t x;
  uint32_t y;
  direction dir;
  uint8_t timer;
  morality faction;
  void (Bullet::*stepRoutine)();

  void destroy();
  void step();
  void normalStep();
  void draw();
};

namespace Player {

    //32 bit coordinates, low byte is subpixels
    extern uint32_t x;
    extern uint32_t y;

    //used for air movement, low byte is subpixels per frame
    extern int16_t vSpeed;
    extern int16_t hSpeed;

    //facing direction
    extern bool faceRight;

    //TODO try and rework the entire bullet thing because linked lists are sort of pointless here
    extern struct BulletList bullets;

    //pointer to the code which is executed on fire
    extern void (*fireRoutine)();

    //pointer to the code which is executed next frame
    extern void (*stepRoutine)();

    //idle step
    void idleStep();
    //in air
    void jumpStep();

    //normal firing action
    void fireNormal();

    void jumpAction();
    void shootAction();

    void init();
    void draw();
};

#endif