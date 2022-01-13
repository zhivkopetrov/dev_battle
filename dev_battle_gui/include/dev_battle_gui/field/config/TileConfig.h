#ifndef DEV_BATTLE_GUI_TILECONFIG_H_
#define DEV_BATTLE_GUI_TILECONFIG_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "utils/drawing/Point.h"

//Own components headers

//Forward declarations

struct TileConfig {
  Point screenCoordinates;
  uint64_t tileRsrcId = 0;
  uint64_t debugFontRsrcId = 0;
  int32_t row = 0;
  int32_t col = 0;
};

#endif /* DEV_BATTLE_GUI_TILECONFIG_H_ */

