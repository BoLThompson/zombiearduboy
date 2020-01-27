#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"

class BulletList {
  private:
    struct Bullet *head = NULL, *tail = NULL;
  public:
    // struct Bullet * getHead();
    // struct Bullet * getTail();
    struct Bullet * append();
    // struct Bullet * insert();
    // struct Bullet * insert(uint8_t index);
    void step();
    void draw();
};

struct Bullet {
  struct Bullet *next;
  uint16_t x;
  uint16_t y;
  direction dir;
  uint8_t timer;
  morality faction;
  void (Bullet::*stepRoutine)();

  void step();
  void normalStep();
  void draw();
};

struct Player {
  private:

    //16 bit coordinates, low byte is subpixels
    uint16_t x;
    uint16_t y;

    //facing direction
    bool faceRight;

    //pointer to the code which is executed on fire
    void (Player::*fireRoutine)();

    //pointer to the code which is executed next frame
    void (Player::*stepRoutine)();

    struct BulletList bullets;


    //idle step
    void idle();

    //normal firing action
    void fireNormal();

  public:
    void init();
    void step();
    void draw();
    morality faction = GOOD;
};

#endif