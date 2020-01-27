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

struct Player {
  private:

    //32 bit coordinates, low byte is subpixels
    uint32_t x;
    uint32_t y;

    //used for jumping
    int16_t vSpeed;
    int16_t hSpeed;

    //facing direction
    bool faceRight;

    struct BulletList bullets;

    //pointer to the code which is executed on fire
    void (Player::*fireRoutine)();

    //pointer to the code which is executed next frame
    void (Player::*stepRoutine)();

    //idle step
    void idleStep();
    //in air
    void jumpStep();

    //normal firing action
    void fireNormal();

    void jumpAction();
    void shootAction();

  public:
    struct BulletList * getBulletList();
    void init();
    void step();
    void draw();
    morality faction = GOOD;
};

#endif