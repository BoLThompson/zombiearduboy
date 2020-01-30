#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>

#define FPS 60

#define FIELD_WIDTH 128
#define FIELD_HEIGHT 64

#define PLAYER_WIDTH 6
#define PLAYER_HEIGHT 12
#define GUN_WIDTH 7
#define GUN_HEIGHT 4
#define FIRE_BUTTON B_BUTTON
#define JUMP_BUTTON A_BUTTON

#define TEMP_GROUND (FIELD_HEIGHT/4)*3

#define ENTITY_MAX 30

#define NORTHWEST UP_BUTTON+LEFT_BUTTON
#define SOUTHWEST DOWN_BUTTON+LEFT_BUTTON
#define NORTHEAST UP_BUTTON+RIGHT_BUTTON
#define SOUTHEAST UP_BUTTON+LEFT_BUTTON

struct Pos {
  int16_t x;
  int16_t y;
};

struct Speed {
  int16_t h;
  int16_t v;
};

struct SubPos {
  uint8_t x;
  uint8_t y;
};

extern Arduboy2Base ab;
extern Sprites sprites;

enum Direction {
  UP        = UP_BUTTON,
  UPRIGHT   = UP_BUTTON+RIGHT_BUTTON,
  UPLEFT    = UP_BUTTON+LEFT_BUTTON,
  RIGHT     = RIGHT_BUTTON,
  LEFT      = LEFT_BUTTON,
  DOWNRIGHT = DOWN_BUTTON+RIGHT_BUTTON,
  DOWNLEFT  = DOWN_BUTTON+LEFT_BUTTON,
  DOWN      = DOWN_BUTTON,
};

#endif