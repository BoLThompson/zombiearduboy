#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"

class Player {
  private:
    int x;
    int y;
    direction dir;
    void (Player::*fireRoutine)();
    void (Player::*stepRoutine)();
    void idle();
  public:
    void init();
    void step();
    void draw();
};

#endif