#ifndef DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_
#define DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_

//System headers
#include <cstdint>

//Other libraries headers
#include "game_engine/config/ApplicationConfig.h"

//Own components headers
#include "dev_battle_gui/config/GuiConfig.h"
#include "utils/ErrorCode.h"

//Forward declarations

class GuiConfigGenerator {
public:
  GuiConfigGenerator() = delete;

  static std::vector<DependencyDescription> generateDependencies(int32_t argc,
                                                                 char **args);

  static std::pair<ApplicationConfig, ErrorCode> generateConfig();
};

#endif /* DEV_BATTLE_GUI_INCLUDE_DEV_BATTLE_GUI_CONFIG_GUICONFIGGENERATOR_H_ */
