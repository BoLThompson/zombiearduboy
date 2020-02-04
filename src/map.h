#ifndef MAP_H
#define MAP_H
#include "global.h"

namespace Map {
  extern uint8_t width;
  extern uint8_t height;
  extern uint16_t cameraX;
  extern uint16_t cameraY;
  void draw();
  uint8_t getTileAt(uint8_t x, uint8_t y);
  void init();
};

#endif