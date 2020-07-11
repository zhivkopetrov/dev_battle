#ifndef GUI_FIELDCONFIG_HPP_
#define GUI_FIELDCONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/field/config/TileConfig.hpp"

//Forward declarations

struct FieldConfig {
  TileConfig tileConfig;
  uint64_t tileSurfaceRsrcId = 0;
  uint64_t tileWholeRsrcId = 0;
  uint64_t tileTargetRsrcId = 0;
  int rows = 0;
  int cols = 0;
};

#endif /* GUI_FIELDCONFIG_HPP_ */

