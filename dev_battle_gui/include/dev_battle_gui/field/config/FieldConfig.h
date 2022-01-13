#ifndef DEV_BATTLE_GUI_FIELDCONFIG_H_
#define DEV_BATTLE_GUI_FIELDCONFIG_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "utils/drawing/Rectangle.h"

//Own components headers
#include "dev_battle_gui/field/config/TileConfig.h"

//Forward declarations

struct FieldConfig {
  Rectangle fieldDimensions;
  uint64_t tileSurfaceRsrcId = 0;
  uint64_t tileWholeRsrcId = 0;
  uint64_t tileTargetRsrcId = 0;
  uint64_t debugFontRsrcId = 0;
  int32_t tileWidth = 0;
  int32_t tileHeight = 0;
  int32_t rows = 0;
  int32_t cols = 0;
};

#endif /* DEV_BATTLE_GUI_FIELDCONFIG_H_ */

