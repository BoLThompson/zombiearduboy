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

#define NORTHWEST UP_BUTTON+LEFT_BUTTON
#define SOUTHWEST DOWN_BUTTON+LEFT_BUTTON
#define NORTHEAST UP_BUTTON+RIGHT_BUTTON
#define SOUTHEAST UP_BUTTON+LEFT_BUTTON

extern Arduboy2Base ab;
extern Sprites sprites;

#endif