#ifndef GUI_FIELDCONFIG_HPP_
#define GUI_FIELDCONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/field/config/TileConfig.hpp"
#include "utils/drawing/Rectangle.h"

//Forward declarations

struct FieldConfig {
  TileConfig tileConfig;
  Rectangle fieldDimensions;
  uint64_t tileSurfaceRsrcId = 0;
  uint64_t tileWholeRsrcId = 0;
  uint64_t tileTargetRsrcId = 0;
  int32_t tileWidth = 0;
  int32_t tileHeight = 0;
  int32_t rows = 0;
  int32_t cols = 0;
};

#endif /* GUI_FIELDCONFIG_HPP_ */

