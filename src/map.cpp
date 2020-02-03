#include "map.h"
#include "assets.h"

uint16_t Map::cameraX;
uint16_t Map::cameraY;

namespace {
  // tileset;
  const uint8_t *mapPointer;
  uint8_t width;
  uint8_t height;
  bool cameraSign;
};

void Map::init() {  //TODO: take map index as argument
  cameraX = 0;
  cameraY = 0;
  mapPointer = stage1_1;
  width = pgm_read_byte(mapPointer);
  height = pgm_read_byte(mapPointer+1);
  cameraSign = true;
}

uint8_t Map::getTileAt(uint8_t x, uint8_t y) {
  return pgm_read_byte(x+(y*width)+(mapPointer+2));
}

void Map::draw() {
  uint8_t tileIndex;
  uint16_t byteIndex = 0;

  uint8_t startX = cameraX / 8;
  uint8_t startY = cameraY / 8;

   for (uint8_t tileY = startY; tileY <= (startY+(SCREEN_HEIGHT/TILE_SIZE)); tileY++){ //iterate through columns
    for (uint8_t tileX = startX; tileX <= (startX+(SCREEN_WIDTH/TILE_SIZE)); tileX++) { //iterate through tiles
      //determine tile type
      tileIndex = getTileAt(tileX,tileY);

      //draw the tile
      sprites.drawOverwrite(tileX*TILE_SIZE-cameraX, tileY*TILE_SIZE, tiles, tileIndex); //draw tile
    }
  }
  if (cameraSign) {
    cameraX++;
    if (cameraX >= width*(TILE_SIZE)-SCREEN_WIDTH)
      cameraSign=!cameraSign;
  }
  else {
    cameraX--;
    if (cameraX <= 0)
      cameraSign=!cameraSign;
  }
}