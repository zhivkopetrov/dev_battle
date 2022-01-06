#ifndef GUI_TILE_H_
#define GUI_TILE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"

//Own components headers

//Forward declarations
class SpriteBuffer;
struct TileConfig;
struct TileDebugConfig;

class Tile {
public:
  int32_t init(const TileConfig &cfg);

  void draw();

  void drawOnSpriteBuffer(SpriteBuffer &spriteBuffer);

private:
  Image _tileImg;
  Text _debugText;
};

#endif /* GUI_TILE_H_ */
