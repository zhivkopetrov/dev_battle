#ifndef DEV_BATTLE_GUI_TILE_H_
#define DEV_BATTLE_GUI_TILE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"

//Own components headers

//Forward declarations
class Fbo;
struct TileConfig;
struct TileDebugConfig;

class Tile {
public:
  int32_t init(const TileConfig &cfg);

  void draw();

  void drawOnFbo(Fbo &fbo) const;

private:
  Image _tileImg;
  Text _debugText;
};

#endif /* DEV_BATTLE_GUI_TILE_H_ */
