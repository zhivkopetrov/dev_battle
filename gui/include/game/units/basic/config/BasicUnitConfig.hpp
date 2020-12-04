#ifndef GUI_BASICUNITCONFIG_HPP_
#define GUI_BASICUNITCONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "game/units/config/UnitConfig.hpp"
#include "game/units/basic/defines/BasicUnitDefines.h"

//Forward declarations

struct BasicUnitConfig {
  UnitConfig unitCfg;
  std::vector<UnitVitalData> unitVitalDataByRank;
};

#endif /* GUI_BASICUNITCONFIG_HPP_ */

