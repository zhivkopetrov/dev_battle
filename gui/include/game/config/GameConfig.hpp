#ifndef GUI_GAMECONFIG_HPP_
#define GUI_GAMECONFIG_HPP_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/defines/GameDefines.h"
#include "game/field/config/FieldConfig.hpp"

//Forward declarations

struct GameConfig {
  GameMode gameMode = GameMode::UNKNOWN;
  FieldConfig fieldCfg;
};

#endif /* GUI_GAMECONFIG_HPP_ */

