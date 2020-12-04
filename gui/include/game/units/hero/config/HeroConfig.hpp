#ifndef GUI_HEROCONFIG_HPP_
#define GUI_HEROCONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>
#include <vector>

//Other libraries headers

//Own components headers
#include "game/units/config/UnitConfig.hpp"

//Forward declarations

struct HeroVitalData {
  UnitVitalData unitVitalData;
  uint8_t maxMana;
  uint8_t maxSpells;
};

struct HeroConfig {
  UnitConfig unitConfig;
  HeroVitalData heroVitalData;
  std::vector<uint64_t> heroActionAnimRsrcIds;
};

#endif /* GUI_HEROCONFIG_HPP_ */

