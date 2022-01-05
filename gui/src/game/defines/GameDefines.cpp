//Corresponding header
#include "game/defines/GameDefines.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "utils/data_type/EnumClassUtils.hpp"
#include "utils/Log.h"

GameMode toGameMode(const int32_t mode) {
  const GameMode gameMode = toEnum<GameMode>(mode);

  switch (gameMode) {
  case GameMode::NORMAL:
  case GameMode::EXTENDED:
  [[fallthrough]];
  case GameMode::SUPER_EXTENDED:
    return gameMode;
  default:
    LOGERR("Received unknown GameMode code: %d", mode);
    return GameMode::UNKNOWN;
  }
}

