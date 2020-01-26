#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"

class Player {
  private:
    uint16_t x;
    uint16_t y;
    uint16_t dir;
    void (Player::*fireRoutine)();
    void (Player::*stepRoutine)();
    void idle();
  public:
    void init();
    void step();
    void draw();
};

#endif