#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>

#define FPS 60

#define FIELD_WIDTH 128
#define FIELD_HEIGHT 64

#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 8

extern Arduboy2Base ab;
extern Sprites sprites;

enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};

#endif