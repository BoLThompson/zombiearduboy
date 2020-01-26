#ifndef GAME_H
#define GAME_H
#include "global.h"

class Game {
  public:
    void init();
    void loop();
};

class Director {
  
};

class Player {
  private:
    int x;
    int y;
    direction dir;
  public:
    void init();
    void step();
    void draw();
};

#endif