#include "map.h"
#include "assets.h"

uint16_t Map::cameraX;
uint16_t Map::cameraY;

namespace {
  // tileset;
};

void Map::init() {  //TODO: take map index as argument
  cameraX = 0;
  cameraY = 0;
}

void Map::draw() {
  uint8_t tileIndex;

  for (int tileX = 0; tileX < (SCREEN_WIDTH/TILE_SIZE); tileX++) { //iterate through columns
    for (int tileY = 0; tileY < (SCREEN_HEIGHT/TILE_SIZE); tileY++) { //iterate through tiles
      //determine tile type
      sprites.drawOverwrite(tileX*TILE_SIZE, tileY*TILE_SIZE, tiles, 1); //draw tile
    }
  }
}