#ifndef DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_
#define DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers
#include "game_engine/engine/config/EngineConfig.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfig.h"

//Forward declarations

class GuiConfigGenerator {
public:
  GuiConfigGenerator() = delete;

  static EngineConfig generateEngineConfig();
  static GuiConfig generateGameConfig();
};

#endif /* DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_ */
