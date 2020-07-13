#ifndef GUI_TILECONFIG_HPP_
#define GUI_TILECONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declarations

struct TileConfig {
  uint64_t tileRsrcId = 0;
  uint64_t debugFontRsrcId = 0;
  int32_t row = 0;
  int32_t col = 0;
};

#endif /* GUI_TILECONFIG_HPP_ */

