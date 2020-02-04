#include "map.h"
#include "assets.h"
#include "game.h"

uint8_t Map::width;
uint8_t Map::height;

namespace {
  // tileset;
  const uint8_t *mapPointer;
};

void Map::init() {  //TODO: take map index as argument
  Game::cameraX = 0;
  Game::cameraY = 0;
  mapPointer = stage1_1;
  width = pgm_read_byte(mapPointer);
  height = pgm_read_byte(mapPointer+1);
}

uint8_t Map::getTileAt(uint8_t x, uint8_t y) {
  return pgm_read_byte(x+(y*width)+(mapPointer+2));
}

void Map::draw() {
  uint8_t tileIndex;
  uint16_t byteIndex = 0;

  uint8_t startX = Game::cameraX / 8;
  uint8_t startY = Game::cameraY / 8;

   for (uint8_t tileY = startY; tileY <= (startY+(SCREEN_HEIGHT/TILE_SIZE)); tileY++){ //iterate through columns
    for (uint8_t tileX = startX; tileX <= (startX+(SCREEN_WIDTH/TILE_SIZE)); tileX++) { //iterate through tiles
      //determine tile type
      tileIndex = getTileAt(tileX,tileY);

      //draw the tile
      sprites.drawOverwrite(tileX*TILE_SIZE-Game::cameraX, tileY*TILE_SIZE, tiles, tileIndex); //draw tile
    }
  }
}